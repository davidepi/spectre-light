//author: Davide Pizzolotto
//license: GNU GPLv3

#include "config_driver.hpp"

///minimum value for ParsedMaterial::rough_x when the material is not specular
#define MIN_ROUGHNESS 0.001f

ParsedMaterial::ParsedMaterial()
{
    elem = METAL_GOLD;
    type = MATTE;
    ior = cauchy(1.45f, 0.f);
    rough_x = 0;
    rough_y = -1;
    dist = SPECTRE_DIST_BECKMANN;
    diffuse = "";
    diffuse_uniform = NULL;
    specular = "";
    specular_uniform = NULL;
    //bump_is_normal = false; //EDIT: removed TextureHeight, so this is true
}

ConfigDriver::ConfigDriver()
        :current_dir("."), camera_pos(0, 0, 0), camera_tar(0, 0, 1),
         camera_up(0, 1, 0)
{
    output = "out.ppm";
    width = 800;
    height = 600;
    spp = 121;
    sampler_type = SPECTRE_SAMPLER_STRATIFIED;
    camera_type = SPECTRE_CAMERA_PERSPECTIVE;
    filter_type = SPECTRE_FILTER_MITCHELL;
    tex_filter = TRILINEAR;
    fov = 55.f;
    value0 = 0.33f;
    value1 = 0.33f;
    integrator = new PathTracer();
    tex_name = "";
    tex_scale = Vec2(1.f);
    tex_shift = Vec2(0.f);
}

Renderer* ConfigDriver::parse(const std::string& f, Scene* scene)
{
    Renderer* r = NULL;
    current_scene = scene;
    current_dir = File(f.c_str()).get_parent();
    file = f;
    scan_begin();
    yy::ConfigParser parser(*this);
    parser.parse();
    scan_end();
    check_resolution();
    check_spp();
#ifdef DEBUG //single threaded
    r = new Renderer(width, height, spp, output.c_str(), 1);
#else //maximum threads
    r = new Renderer(width,height,spp,output.c_str());
#endif
    r->set_sampler(sampler_type);
    r->inherit_camera(build_camera());
    r->inherit_filter(build_filter());
    r->inherit_integrator(integrator);

    //load children files
    //avoid recursive children
    std::vector<std::string> consolidated_children = children;
    children.clear();
    for(unsigned int i = 0; i<consolidated_children.size(); i++)
    {
        File file1 = is_absolute(consolidated_children[i].c_str())?
                     File(consolidated_children[i].c_str()):
                     current_dir.append(consolidated_children[i].c_str());
        file = file1.absolute_path();
        if(file1.exists())
        {
            scan_begin();
            parser.parse();
            scan_end();
        }
        else
            Console.severe(MESSAGE_INPUT_ERROR, file.c_str());
    }
    //free some memory
    consolidated_children.clear();
    consolidated_children.resize(0);
    children.resize(0);

    //build default sphere
    default_sphere = new Sphere();
    current_scene->inherit_shape(default_sphere);

    //build deferred objects
    build_materials();
    build_dualmaterials();
    for(unsigned int i = 0; i<deferred_shapes.size(); i++)
        parse_and_allocate_obj(deferred_shapes[i].c_str());
    build_meshes();

    //delete unused shapes, the ones not inherited by Scene
    //else add them to the scene
    //delete also materials array, since they are copied by the asset
    std::unordered_map<std::string, MeshObject>::iterator shape_it;
    shape_it = shapes.begin();
    while(shape_it != shapes.end())
    {
        if(used_shapes.find(shape_it->first) == used_shapes.end())
            delete shape_it->second.mesh;
        else
            current_scene->inherit_shape(shape_it->second.mesh);
        free(shape_it->second.materials);
        free(shape_it->second.association);
        shape_it++;
    }

    //delete everything else used for parsing
    all_textures.clear();
    children.clear();
    deferred_materials.clear();
    deferred_dualmats.clear();
    shapes.clear();
    deferred_shapes.clear();
    deferred_meshes.clear();
    used_shapes.clear();

    return r;
}

void ConfigDriver::check_resolution()
{
    int rem = width%SPLIT_SIZE;
    if(rem != 0)
    {
        float aspect_ratio = (float)width/(float)height;
        width += SPLIT_SIZE-rem;
        height += (int)((SPLIT_SIZE-rem)/aspect_ratio);
        if(height%2 != 0)
            height++;
        Console.notice(MESSAGE_RESOLUTION_CHANGED, SPLIT_SIZE, width, height);
    }
}

void ConfigDriver::check_spp()
{
    if(sampler_type == SPECTRE_SAMPLER_STRATIFIED)
    {
        float root = sqrtf((float)spp);
        if((int)root*(int)root != spp)
        {
            spp = static_cast<int>(static_cast<float>(root+.5f));
            spp *= spp;
            Console.notice(MESSAGE_SPP_CHANGED, spp);
        }
    }
}

void ConfigDriver::error(const yy::location& l, const std::string& m)
{
    //tested againts: token len > buffer len
    //line len > buf len
    //token at beginning and line len > buf len
    //token at end and line len > buf len
#define GRN "\x1B[32m"
#define NRM "\x1B[0m"
#define BLD "\x1B[1m"
#define BUFFER 128
    unsigned int end_col = 0<l.end.column?l.end.column-1:0;
    //underline wrong token
    if(l.begin.column<l.end.column && l.begin.line == l.end.line &&
       l.end.column-l.begin.column<=BUFFER-5) //prev. segfault if token len >buf
    {
        char buf[128];
        char under[128];
        int offset = get_line(buf, 128);
        for(unsigned int i = 0; i<l.begin.column-1-offset; i++)
            under[i] = ' ';
        for(unsigned int i = l.begin.column-1-offset; i<end_col-offset; i++)
            under[i] = '~';
        under[end_col-offset] = 0;
        Console.critical("%s:%d.%d: " BLD "%s" NRM "\n%s\n%" GRN "%s" NRM,
                         file.c_str(), l.end.line, end_col, m.c_str(), buf,
                         under);
    }
    else //just print the error
    {
        Console.critical("%s:%d.%d: " BLD "%s" NRM,
                         file.c_str(), l.end.line, end_col, m.c_str());
    }
}

void ConfigDriver::unknown_char(const yy::location& l, char c)
{
    // MESSAGE_SYNTAX_ERROR contains a "%c" (2 letters) that is substituted
    // by a single char gaining 1 space for the \0. Hence the missing +1 in the
    // array alloc.
    char errormsg[sizeof(MESSAGE_SYNTAX_ERROR)]; //constexpr strlen()
    sprintf(errormsg, MESSAGE_SYNTAX_ERROR, c);
    error(l, std::string(errormsg));
}

Filter* ConfigDriver::build_filter()
{
    //not a good practice, but the alternative is moving this switch elsewhere
    Filter* filter;
    switch(filter_type)
    {
        case SPECTRE_FILTER_BOX:filter = new FilterBox();
            break;
        case SPECTRE_FILTER_TENT:filter = new FilterTent();
            break;
        case SPECTRE_FILTER_GAUSS:filter = new FilterGaussian(value0);
            break;
        case SPECTRE_FILTER_LANCZOS:filter = new FilterLanczos(value0);
            break;
        case SPECTRE_FILTER_MITCHELL:
        default:filter = new FilterMitchell(value0, value1);
            break;
    }
    return filter;
}

Camera* ConfigDriver::build_camera()
{
    //not a good practice, but the alternative is moving this switch elsewhere
    Camera* camera;
    switch(camera_type)
    {
        case SPECTRE_CAMERA_ORTHOGRAPHIC:
            camera = new CameraOrthographic(&camera_pos, &camera_tar,
                                            &camera_up,
                                            width, height);
            break;

        case SPECTRE_CAMERA_PANORAMA:
            camera = new Camera360(&camera_pos, &camera_tar, &camera_up,
                                   width, height);
            break;
        case SPECTRE_CAMERA_PERSPECTIVE:
        default:
            camera = new CameraPerspective(&camera_pos, &camera_tar, &camera_up,
                                           width, height, fov);
            break;
    }
    return camera;
}

const TextureUniform* ConfigDriver::load_texture_uniform()
{
    tex_color.clamp(Vec3(0, 0, 0), Vec3(255, 255, 255));
    ColorRGB rgb((unsigned char)tex_color.x,
                 (unsigned char)tex_color.y,
                 (unsigned char)tex_color.z);
    Spectrum color(rgb, false);
    TextureUniform* val = new TextureUniform(color);
    TexLib.inherit_texture(val);
    return val;
}

const TextureImage* ConfigDriver::load_texture(const std::string& path)
{

    File cur_file = current_dir;
    const TextureImage* addme;
    if(is_absolute(path.c_str()))
        //TODO: avoid recreating the cur_file class
        cur_file = File(path.c_str());
    else
        cur_file.append(path.c_str());
    //resolve texture name
    if(tex_name.empty())
        tex_name = cur_file.filename();
    if(TexLib.contains_texture(tex_name))
        //TexLib already contains TextureImage
        addme = (TextureImage*)TexLib.get_texture(tex_name);
    else if(cur_file.exists() && cur_file.readable() && !           cur_file.is_folder() &&
       img_valid(cur_file.absolute_path(), cur_file.extension()))
    {
        //Texture Image will deal with same file but different texture names
        addme = new TextureImage(cur_file, tex_shift, tex_scale, tex_filter);
        TexLib.inherit_texture(tex_name, addme);
    }
    else
    {
        Console.warning(MESSAGE_TEXTURE_ERROR, cur_file.absolute_path());
        addme = TexLib.get_dflt_teximage();
    }
    tex_name.clear(); //reset name for next texture
    tex_scale = Vec2(1.f); //reset scaling for next texture
    tex_shift = Vec2(); //reset shifting for next texture
    return addme;
}

void ConfigDriver::build_materials()
{
    ParsedMaterial* mat;
    Bsdf* material;
    const Texture* diffuse;
    const Texture* specular;
    const Bump* bump_map;
    for(int i = 0; i<(int)deferred_materials.size(); i++)
    {
        mat = &deferred_materials[i];

        //avoid processing if material already exists
        if(MtlLib.contains(mat->name))
        {
            Console.warning(MESSAGE_DUPLICATE_MATERIAL, mat->name.c_str());
            continue;
        }

        //resolve textures
        //diffuse
        if(mat->diffuse_uniform == NULL) //use non uniform texture
        {
            if(mat->diffuse.empty())
                diffuse = TexLib.get_dflt_teximage();
            else
                diffuse = load_texture(mat->diffuse);
        }
        else
            diffuse = mat->diffuse_uniform;

        //specular
        if(mat->specular_uniform == NULL) //use non uniform texture
        {
            if(mat->specular.empty())
                specular = TexLib.get_dflt_teximage();
            else
                specular = load_texture(mat->specular);
        }
        else
            specular = mat->specular_uniform;

        if(!mat->bump.empty())
        {
            /* OLD PIECE OF CODE CONSIDERING THE HEIGHT MAP IMPLEMENTATION
             * now the TextureHeight is not used because I cannot figure out
             * why it does not work
             ```
             if(TexLib.contains_texture(mat->bump))
               if(mat->bump_is_normal)
                 bump_map = new TextureNormal(
                   (const TextureImage*)TexLib.get_texture(mat->bump));
                 else
                   bump_map = new TextureHeight(
                             (const TextureImage*)TexLib.get_texture(mat->bump),
                               RED);
                 else if(mat->bump_is_normal)
                   bump_map = new TextureNormal(
                               (const TextureImage*)load_texture(mat->bump));
                 else
                     bump_map = new TextureHeight(
                       (const TextureImage*)load_texture(mat->bump), RED);
            ```
             */
            bump_map = new TextureNormal((const TextureImage*)load_texture(mat->bump));
        }
        else
            bump_map = new Bump();

        //isotropic element, no point in using anisotropic one
        mat->rough_x = clamp(mat->rough_x, 0.f, 1.f);
        if(mat->rough_y == mat->rough_x)
            mat->rough_y = -1;
        if(mat->rough_y != -1)
        {
            //cannot be specular so avoid 0
            mat->rough_x = clamp(mat->rough_x, MIN_ROUGHNESS, 1.f);
            mat->rough_y = clamp(mat->rough_y, MIN_ROUGHNESS, 1.f);
        }

        switch(mat->type)
        {
            case MATTE:
            {
                if(mat->rough_x != 0)
                {
                    float roughness = lerp(mat->rough_x, 0.f, 100.f);
                    material = new SingleBRDF(new OrenNayar(roughness),
                                              diffuse);
                }
                else
                    material = new SingleBRDF(new Lambertian, diffuse);
                break;
            }
            case GLOSSY:
            {
                MultiBSDF* multimat = new MultiBSDF();
                Fresnel* fresnel = new Dielectric(cauchy(1.f, 0),
                                                  cauchy(1.5f, 0));
                MicrofacetDist* dist;
                multimat->inherit_bdf(new Lambertian(), diffuse);
                //no specular in glossy, avoid division by zero
                if(mat->rough_x == 0)
                    mat->rough_x = MIN_ROUGHNESS;
                if(mat->rough_y != -1)
                    dist = new GGXaniso(mat->rough_x, mat->rough_y);
                else
                {
                    if(mat->dist == SPECTRE_DIST_BLINN)
                        dist = new Blinn(2.f/(mat->rough_x*mat->rough_x)-2);
                    else if(mat->dist == SPECTRE_DIST_BECKMANN)
                        dist = new Beckmann(mat->rough_x);
                    else
                        dist = new GGXiso(mat->rough_x);
                }
                multimat->inherit_bdf(new MicrofacetR(dist, fresnel), specular);
                material = (Bsdf*)multimat;
                break;
            }
            case GLASS:
            {
                MultiBSDF* multimat = new MultiBSDF();
                Bdf* reflective;
                Bdf* refractive;
                Spectrum etai = cauchy(1.f, 0.f);
                if(mat->rough_x == 0 && mat->rough_y == -1) //spec
                {
                    reflective = new DielectricReflection(etai, mat->ior);
                    refractive = new Refraction(etai, mat->ior);
                }
                else
                {
                    MicrofacetDist* dist_r;
                    MicrofacetDist* dist_t;
                    Fresnel* fresnel_r = new Dielectric(etai, mat->ior);
                    if(mat->rough_y != -1)
                    {
                        dist_r = new GGXaniso(mat->rough_x, mat->rough_y);
                        dist_t = new GGXaniso(mat->rough_x, mat->rough_y);
                    }
                    else
                    {
                        if(mat->dist == SPECTRE_DIST_BLINN)
                        {
                            dist_r = new Blinn(
                                    2.f/(mat->rough_x*mat->rough_x)-2);
                            dist_t = new Blinn(
                                    2.f/(mat->rough_x*mat->rough_x)-2);
                        }
                        else if(mat->dist == SPECTRE_DIST_BECKMANN)
                        {
                            dist_r = new Beckmann(mat->rough_x);
                            dist_t = new Beckmann(mat->rough_x);
                        }
                        else
                        {
                            dist_r = new GGXiso(mat->rough_x);
                            dist_t = new GGXiso(mat->rough_x);
                        }
                    }
                    reflective = new MicrofacetR(dist_r, fresnel_r);
                    refractive = new MicrofacetT(dist_t, etai, mat->ior);
                }
                multimat->inherit_bdf(refractive, diffuse);
                multimat->inherit_bdf(reflective, specular);
                material = (Bsdf*)multimat;
                break;
            }
            case METAL:
            {
                Spectrum ior;
                Spectrum absorption;
                Bdf* bdf;
                MicrofacetDist* dist;
                Fresnel* fresnel;
                ior = Spectrum(METALS[mat->elem].n);
                absorption = Spectrum(METALS[mat->elem].k);
                if(mat->rough_x == 0 && mat->rough_y == -1) //specular
                    bdf = new ConductorReflection(ior, absorption);
                else
                {

                    if(mat->rough_x != 0 &&
                       mat->rough_y != -1) //anisotropic microf
                        dist = new GGXaniso(mat->rough_x, mat->rough_y);
                    else
                    {
                        if(mat->dist == SPECTRE_DIST_BLINN)
                            dist = new Blinn(2.f/(mat->rough_x*mat->rough_x)-2);
                        else if(mat->dist == SPECTRE_DIST_BECKMANN)
                            dist = new Beckmann(mat->rough_x);
                        else
                            dist = new GGXiso(mat->rough_x);
                    }
                    fresnel = new Conductor(ior, absorption);
                    bdf = new MicrofacetR(dist, fresnel);
                }
                material = new SingleBRDF(bdf);
                break;
            }
        }
        material->inherit_bump(bump_map);
        MtlLib.add_inherit(mat->name, material);
    }
}

void ConfigDriver::build_dualmaterials()
{
    ParsedDualMaterial* mat;
    DualBsdf* material;
    const Bsdf* first;
    const Bsdf* second;
    for(int i = 0; i<(int)deferred_dualmats.size(); i++)
    {
        mat = &deferred_dualmats[i];
        if(MtlLib.contains(mat->first))
            first = MtlLib.get(mat->first);
        else
            first = MtlLib.get_default();
        if(MtlLib.contains(mat->second))
            second = MtlLib.get(mat->second);
        else
            second = MtlLib.get_default();
        material = new DualBsdf(first, second, build_mask(mat->mask));
        MtlLib.add_inherit(mat->name, material);
    }
}

void ConfigDriver::parse_and_allocate_obj(const char* obj_file)
{
    //existence check is left to ParserObj class
    File f = current_dir;
    if(!is_absolute(obj_file))
        f.append(obj_file);
    else
        f = File(obj_file);
    if(strcmp(f.extension(), "obj") != 0)
    {
        Console.severe(MESSAGE_OBJ_ERROR, f.absolute_path(), f.extension());
        return;
    }
    ParserObj p;
    p.start_parsing(f.absolute_path());
    Mesh* m = new Mesh(1);
    while(p.get_next_mesh(m))
    {
        MeshObject insertme;
        insertme.mesh = m;
        insertme.materials_len = p.get_material_no();
        insertme.materials = (const Bsdf**)malloc(sizeof(const Bsdf*)*
                                                  p.get_material_no());
        insertme.association = (unsigned char*)malloc(p.get_face_no());
        p.get_materials(insertme.materials);
        p.get_material_association(insertme.association);
        std::string name = p.get_mesh_name();
        std::unordered_map<std::string, MeshObject>::const_iterator it;
        it = shapes.find(name);
        if(it == shapes.end())
        {
            shapes.insert({{name, insertme}});
            //give ownership to scene. So the shape will be deleted
            //current_scene->inherit_shape(m); <- THIS IS WRONG HERE
            //because some shapes inside the scene will be cleaned if not used
            //and at program termination, boom, double free.
            //shape inheriting is done IF the shape is used, in the parse func
            //This comment is left here to prevent the readdition of this stmt
        }
        else
        {
            Console.warning(MESSAGE_DUPLICATE_SHAPE, name.c_str());
            delete m;
        }
        m = new Mesh(1);
    }
    //allocated mesh but they were finished
    delete m;
}

void ConfigDriver::build_meshes()
{
    while(!deferred_meshes.empty())
    {
        MeshObject mesh_o;
        MeshWorld mesh_w = deferred_meshes.back();
        deferred_meshes.pop_back();
        std::unordered_map<std::string, MeshObject>::const_iterator mesh_i;

        //differentiate between sdl or mesh
        if(mesh_w.name != "Sphere")
        {
            //parsed obj that will be deleted if not used
            mesh_i = shapes.find(mesh_w.name);
            if(mesh_i != shapes.end())
            {
                mesh_o = mesh_i->second;
                //this step should not be performed by sdl: since they are not
                //in the array of the parsed shapes and will always be removed
                //when cleaning the Scene of unused meshes
                used_shapes.insert(mesh_w.name);
            }
            else
            {
                Console.warning(MESSAGE_SHAPE_NOT_FOUND, mesh_w.name.c_str());
                continue; //otherwise it would be an if-else nightmare
            }
        }
        else
        {
            //sdl that will always stays in the scene
            //construct the MeshObject (which is the parsed .obj) in place
            mesh_o.mesh = default_sphere;
            mesh_o.materials = (const Bsdf**)malloc(sizeof(const Bsdf*));
            mesh_o.materials[0] = MtlLib.get_default();
            mesh_o.materials_len = 1;
            mesh_o.association = (unsigned char*)malloc(1);
            mesh_o.association[0] = 0;
        }

        Matrix4 transform;
        Matrix4 position_matrix;
        Matrix4 rotation_matrix;
        Matrix4 rotx_matrix;
        Matrix4 roty_matrix;
        Matrix4 rotz_matrix;
        Matrix4 scale_matrix;
        position_matrix.set_translation(mesh_w.position);
        rotx_matrix.set_rotate_x(mesh_w.rotation.x);
        roty_matrix.set_rotate_y(mesh_w.rotation.y);
        rotz_matrix.set_rotate_z(mesh_w.rotation.z);
        rotation_matrix = rotz_matrix*roty_matrix*rotx_matrix;
        scale_matrix.set_scale(mesh_w.scale);
        //watchout the order!!!
        transform = position_matrix*rotation_matrix*scale_matrix;
        Asset* current_asset;
        if(!mesh_w.is_light)
        {
            current_asset = new Asset(mesh_o.mesh, transform, 1);

            //use parsed materials
            if(mesh_w.material_name.empty())
            {
                current_asset->set_materials(mesh_o.materials,
                                             mesh_o.materials_len,
                                             mesh_o.association);
            }
            else //override materials
            {
                const Bsdf* overridden_material;
                overridden_material = MtlLib.get(mesh_w.material_name);
                if(overridden_material == NULL)
                {
                    //use default if the material is missing
                    overridden_material = MtlLib.get_default();
                    Console.warning(MESSAGE_MISSING_MATERIAL_OVERRIDE,
                                    mesh_w.material_name.c_str(),
                                    mesh_w.name.c_str());
                }
                const Bsdf* materials[1];
                materials[0] = overridden_material;
                unsigned char* associations;
                associations = (unsigned char*)malloc
                        (mesh_o.mesh->get_faces_number());
                memset(associations, 0, mesh_o.mesh->get_faces_number());
                current_asset->set_materials(materials, 1, associations);
                free(associations);
            }
            current_scene->inherit_asset(current_asset);
        }
        else
        {
            //blackbody
            if(mesh_w.temperature>=0)
                current_asset = new LightArea(mesh_o.mesh, transform,
                                              mesh_w.temperature);
            else
            {
                unsigned char r;
                unsigned char g;
                unsigned char b;
                r = (unsigned char)clamp(mesh_w.color.x, 0.f, 255.f);
                g = (unsigned char)clamp(mesh_w.color.y, 0.f, 255.f);
                b = (unsigned char)clamp(mesh_w.color.z, 0.f, 255.f);
                Spectrum color(ColorRGB(r, g, b), true);
                current_asset = new LightArea(mesh_o.mesh, transform, color);
            }
            //create a default material for cameras
            const Bsdf* materials[1];
            materials[0] = MtlLib.get_default();
            unsigned char* associations;
            associations = (unsigned char*)malloc
                    (mesh_o.mesh->get_faces_number());
            memset(associations, 0, mesh_o.mesh->get_faces_number());
            current_asset->set_materials(materials, 1, associations);
            free(associations);
            current_scene->inherit_arealight((LightArea*)current_asset);
        }
        //resolve the mask
        current_asset->set_mask(build_mask(mesh_w.mask));
    }
}

MaskBoolean ConfigDriver::build_mask(const ParsedMask& mask)
{
    const TextureImage* map;
    if(mask.mask_tex.empty())
        map = NULL;
    else
    {
        map = load_texture(mask.mask_tex);
    }
    return MaskBoolean(map, mask.mask_chn, mask.mask_inv);
}

ParsedMask::ParsedMask()
{
    mask_inv = false;
    mask_chn = ALPHA;
}
