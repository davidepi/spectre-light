#include "parser_config.hpp"
#include "utility/spectrum.hpp"
#include "geometry/point3.hpp"
#include "geometry/vec3.hpp"
#include "cameras/camera_orthographic.hpp"
#include "cameras/camera_perspective.hpp"
#include "cameras/camera360.hpp"
#include "samplers/filter_box.hpp"
#include "samplers/filter_tent.hpp"
#include "samplers/filter_gaussian.hpp"
#include "samplers/filter_mitchell.hpp"
#include "samplers/filter_lanczos.hpp"
#include "integrators/path_tracer.hpp"
#include "textures/texture_uniform.hpp"
#include "textures/texture_image.hpp"
#include "textures/texture_normal.hpp"
#include "materials/single_brdf.hpp"
#include "materials/multi_bsdf.hpp"
#include "materials/oren_nayar.hpp"
#include "materials/lambertian.hpp"
#include "materials/reflection.hpp"
#include "materials/refraction.hpp"
#include "materials/fresnel_conditions.hpp"
#include "materials/microfacet.hpp"
#include "materials/microfacet_distributions.hpp"
#include "materials/metals.hpp"
#include "materials/dual.hpp"
#include "parsers/parser_obj.hpp"
#include "primitives/mesh.hpp"
#include "primitives/sphere.hpp"
#include "lights/light_area.hpp"
#include "lights/light_omni.hpp"
#include "lights/light_spot.hpp"
#include "lights/light_sun.hpp"

extern "C" { void parse_config(FILE*, struct ParsedScene*); }

///minimum value for ParsedMaterial::rough_x when the material is not specular
#define MIN_ROUGH 0.001f

/// Struct used to bind a mesh and its materials. A mesh in object space
struct MeshObject
{
    ///The shape in object space. SDLs can also be used
    Shape* mesh;

    ///Array of materials used by this shape
    const Bsdf** materials;

    ///Length of the MeshObject::materials array
    unsigned char materials_len;

    /**
     *  \brief Array of associations triangle-material, represented as offsets
     *  The ith value of this array is the offset in the MeshObject::materials
     *  array to know the material for the ith triangle
     */
    unsigned char* association;
};

/**
 *  \brief Performs checks on the resolution
 *
 *  This function checks if the width is a multiple of SPLIT_SIZE. If this is
 *  not the case, width is INCREASED until the next multiple of SPLIT_SIZE is
 *  reached. The height value is also modified in order to maintain the same
 *  aspect ratio
 *
 *  \param[in,out] width The width of the image
 *  \param[in,out] height The height of the image
 */
static void check_resolution(int* width, int* height)
{
    int rem = *width%SPLIT_SIZE;
    if(rem != 0)
    {
        float aspect_ratio = (float)*width/(float)*height;
        *width += SPLIT_SIZE-rem;
        *height += (int)((SPLIT_SIZE-rem)/aspect_ratio);
        if(*height%2 != 0)
            (*height)++;
        Console.notice(MESSAGE_RESOLUTION_CHANGED, SPLIT_SIZE, width, height);
    }
}

/**
 *  \brief Performs checks on the spps, depending on the used sampler
 *
 *  This function checks if the spp is a perfect square if the stratified
 *  sampler is being used. If this is not the case, the value is rounded to the
 *  NEAREST perfect square
 *
 *  \param[in] sampler_type The type of sampler used
 *  \param[in,out] spp The spp value
 */
void check_spp(enum sampler_t sampler_type, int* spp)
{
    if(sampler_type == STRATIFIED)
    {
        float root = sqrtf((float)*spp);
        if((int)root*(int)root != *spp)
        {
            *spp = static_cast<int>(static_cast<float>(root+.5f));
            *spp *= *spp;
            Console.notice(MESSAGE_SPP_CHANGED, spp);
        }
    }
}

/**
 *  \brief Parse a configuration file and get the raw unprocessed data inside it
 *  \param[in] filename The configuration file that will be parsed
 *  \param[in,out] parsed The result that will hold the parsed raw data, this
 *  struct is assumed to be already initialized with the init_ParsedScene()
 *  method
 */
void parse_rec(const char* filename, ParsedScene* parsed)
{
    FILE* fin = fopen(filename, "r");
    if(fin != NULL)
    {
        parse_config(fin, parsed);
        fclose(fin);
    }
    else
    {
        const unsigned long int LEN =
                strlen(strerror(errno))+strlen(MESSAGE_INPUT_ERROR)+1;
        parsed->error_msg = (char*)malloc(sizeof(char)*LEN);
        sprintf(parsed->error_msg, MESSAGE_INPUT_ERROR, "%s", strerror(errno));
    }
}

/**
 *  \brief Allocates the camera with parsed parameters
 *  \param[in] parsed The struct containing parsed raw values
 */
CHECK_RETVAL_USED
static const Camera* build_camera(const ParsedScene* parsed)
{
    //not a good practice, but the alternative is moving this switch elsewhere
    const Camera* camera = NULL;
    Point3 position(parsed->camera_pos[0],
                    parsed->camera_pos[1],
                    parsed->camera_pos[2]);
    Point3 target(parsed->camera_tar[0],
                  parsed->camera_tar[1],
                  parsed->camera_tar[2]);
    Vec3 up(parsed->camera_up[0],
            parsed->camera_up[1],
            parsed->camera_up[2]);
    switch(parsed->camera_type)
    {
        case ORTHOGRAPHIC:
            camera = new CameraOrthographic(position, target, up,
                                            parsed->width, parsed->height);
            break;

        case PANORAMA:
            camera = new Camera360(position, target, up,
                                   parsed->width, parsed->height);
            break;
        case PERSPECTIVE:
            camera = new CameraPerspective(position, target, up,
                                           parsed->width, parsed->height,
                                           radians(parsed->fov));
            break;
    }
    return camera;
}

/**
 *  \brief Allocates the filter with parsed parameters
 *  \param[in] parsed The struct containing parsed raw values
 */
CHECK_RETVAL_USED
static const Filter* build_filter(const ParsedScene* parsed)
{
    //not a good practice, but the alternative is moving this switch elsewhere
    const Filter* filter = NULL;
    switch(parsed->filter_type)
    {
        case BOX:filter = new FilterBox();
            break;
        case TENT:filter = new FilterTent();
            break;
        case GAUSS:filter = new FilterGaussian(parsed->value0);
            break;
        case LANCZOS:filter = new FilterLanczos(parsed->value0);
            break;
        case MITCHELL:
        default:filter = new FilterMitchell(parsed->value0, parsed->value1);
            break;
    }
    return filter;
}

/**
 *  \brief Parse every texture contained in the parsed_textures
 *
 *  Add every material contained inside the parsed_textures stack of the
 *  ParsedScene into the TextureLibrary. The parsed_textures stack is emptied
 *  during this process
 *
 *  \param[in] parsed The struct containing parsed raw values
 */
static void build_textures(ParsedScene* parsed, const File* current_dir)
{
    while(!empty_ResizableParsed(&parsed->parsed_textures))
    {
        ParsedElement tex_union;
        top_ResizableParsed(&parsed->parsed_textures, &tex_union);
        pop_ResizableParsed(&parsed->parsed_textures);
        if(tex_union.tex.src == NULL)
        {
            //uniform
            if(tex_union.tex.name != NULL)
            {
                //uint8_t grants that tex.color[x] is in 0-255 range
                Spectrum color(ColorRGB(tex_union.tex.color[0],
                                        tex_union.tex.color[1],
                                        tex_union.tex.color[2]), false);
                TextureUniform* val = new TextureUniform(color);
                TexLib.inherit_texture(tex_union.tex.name, val);
                free(tex_union.tex.name);
            }
            else
                Console.notice("%s\n", MESSAGE_TEXTURE_NONAME);
        }
        else
        {
            //texture image
            File cur_file(current_dir, tex_union.tex.src);
            const char* tex_name;
            if(tex_union.tex.name != NULL)
                tex_name = tex_union.tex.name;
            else
                tex_name = cur_file.filename();
            if(!TexLib.contains_texture(tex_name) && cur_file.exists() &&
               cur_file.readable() && !cur_file.is_folder() &&
               img_valid(cur_file.absolute_path(), cur_file.extension()))
            {
                Vec2 shift(tex_union.tex.shift[0], tex_union.tex.shift[1]);
                Vec2 scale(tex_union.tex.scale[1], tex_union.tex.scale[1]);
                TextureImage* addme = new TextureImage(cur_file, shift, scale,
                                                       tex_union.tex.filter);
                TexLib.inherit_texture(tex_name, addme);
            }
            else
                Console.warning(MESSAGE_TEXTURE_ERROR,
                                cur_file.absolute_path());
            free(tex_union.tex.src);
            if(tex_union.tex.name != NULL)
                free(tex_union.tex.name);
        }
    }
}

/**
 *  \brief Parse every material contained in the parsed_materials
 *
 *  Add every material contained inside the parsed_materials stack of the
 *  ParsedScene into the MaterialLibrary. The parsed_materials stack is emptied
 *  during this process
 *
 *  \param[in] parsed The struct containing parsed raw values
 */
static void build_materials(ParsedScene* parsed)
{
    Bsdf* bsdf;
    const Texture* diffuse;
    const Texture* specular;
    float rough_x;
    float rough_y;
    while(!empty_ResizableParsed(&parsed->parsed_materials))
    {
        ParsedElement union_m;
        top_ResizableParsed(&parsed->parsed_materials, &union_m);
        pop_ResizableParsed(&parsed->parsed_materials);

        //free everything and continue if materials is unnamed or already exists
        bool already_existing = MtlLib.contains(union_m.mat.name);
        if(union_m.mat.name == NULL || already_existing)
        {
            if(union_m.mat.name != NULL)
                free(union_m.mat.name);
            if(union_m.mat.diffuse != NULL)
                free(union_m.mat.diffuse);
            if(union_m.mat.specular != NULL)
                free(union_m.mat.specular);
            if(union_m.mat.normal != NULL)
                free(union_m.mat.normal);
            if(already_existing)
                Console.warning(MESSAGE_DUPLICATE_MATERIAL, union_m.mat.name);
            continue;
        }

        //resolve diffuse texture
        if(union_m.mat.diffuse != NULL)
        {
            diffuse = TexLib.get_texture(union_m.mat.diffuse);
            if(diffuse == NULL)
            {
                diffuse = TexLib.get_dflt_texture();
                Console.warning(MESSAGE_TEXTURE_NOT_FOUND_MTL,
                                union_m.mat.diffuse, union_m.mat.name);
            }
            free(union_m.mat.diffuse);
        }
        else
            diffuse = TexLib.get_dflt_texture();

        //resolve specular texture
        if(union_m.mat.specular != NULL)
        {
            specular = TexLib.get_texture(union_m.mat.specular);
            if(specular == NULL)
            {
                specular = TexLib.get_dflt_texture();
                Console.warning(MESSAGE_TEXTURE_NOT_FOUND_MTL,
                                union_m.mat.specular, union_m.mat.name);
            }
            free(union_m.mat.specular);
        }
        else
            specular = TexLib.get_dflt_texture();

        //resolve normal map at the end of the function!!!

        //resolve anisotropy. If isotropic -> rough_x = val, rough_y = -1
        rough_x = clamp(union_m.mat.rough_x, 0.f, 1.f);
        rough_y = union_m.mat.rough_y;
        if(rough_y == rough_x)
            rough_y = -1.f;
        if(rough_y != -1.f)
        {
            //cannot be specular if rough_y is set
            rough_x = clamp(rough_x, MIN_ROUGH, 1.f);
            rough_y = clamp(rough_y, MIN_ROUGH, 1.f);

        }

        //now that the dependency are done, create the actual material
        switch(union_m.mat.type)
        {
            case MATTE:
            {
                if(rough_x != 0)
                {
                    //convert roughness from 0-1 scale to 0-100 scale;
                    float roughness = lerp(rough_x, 0.f, 100.f);
                    bsdf = new SingleBRDF(new OrenNayar(roughness), diffuse);
                }
                else
                    bsdf = new SingleBRDF(new Lambertian, diffuse);
                break;
            }
            case GLOSSY:
            {
                MultiBSDF* multimat = new MultiBSDF();
                Fresnel* fresnel = new Dielectric(cauchy(1.f, 0.f),
                                                  cauchy(1.5f, 0.f));
                MicrofacetDist* dist;
                multimat->inherit_bdf(new Lambertian, diffuse);
                //in glossy in particular, specular cannot exist
                //but in other it can, so this check is performed only here
                if(rough_x == 0)
                    rough_x = MIN_ROUGH;
                if(rough_y == -1)
                {
                    switch(union_m.mat.dist)
                    {
                        case BLINN:
                            //In a paper this was the formula roughness to alpha
                            //I don't recall which one though
                            dist = new Blinn(2.f/(rough_x*rough_x)-2.f);
                            break;
                        case BECKMANN:dist = new Beckmann(rough_x);
                            break;
                        case GGX:dist = new GGXiso(rough_x);
                            break;
                    }
                }
                else
                    dist = new GGXaniso(rough_x, rough_y);
                multimat->inherit_bdf(new MicrofacetR(dist, fresnel), specular);
                bsdf = (Bsdf*)multimat;
                break;
            }
            case GLASS:
            {
                MultiBSDF* multimat = new MultiBSDF();
                Bdf* reflective;
                Bdf* refractive;
                Spectrum etai = cauchy(1.f, 0.f);
                Spectrum ior = cauchy(union_m.mat.ior[0], union_m.mat.ior[1],
                                      union_m.mat.ior[2]);
                if(rough_x == 0 && rough_y == -1) //spec
                {
                    reflective = new DielectricReflection(etai, ior);
                    refractive = new Refraction(etai, ior);
                }
                else
                {
                    MicrofacetDist* dist_r;
                    MicrofacetDist* dist_t;
                    Fresnel* fresnel_r = new Dielectric(etai, ior);
                    if(rough_y == -1)
                    {
                        switch(union_m.mat.dist)
                        {
                            case BLINN:
                            {
                                dist_r = new Blinn(2.f/(rough_x*rough_x)-2.f);
                                dist_t = new Blinn(2.f/(rough_x*rough_x)-2.f);
                                break;
                            }
                            case BECKMANN:
                            {
                                dist_r = new Beckmann(rough_x);
                                dist_t = new Beckmann(rough_x);
                                break;
                            }
                            case GGX:
                            {
                                dist_r = new GGXiso(rough_x);
                                dist_t = new GGXiso(rough_x);
                                break;
                            }
                        }
                    }
                    else
                    {
                        dist_r = new GGXaniso(rough_x, rough_y);
                        dist_t = new GGXaniso(rough_x, rough_y);
                    }
                    reflective = new MicrofacetR(dist_r, fresnel_r);
                    refractive = new MicrofacetT(dist_t, etai, ior);
                }
                multimat->inherit_bdf(refractive, diffuse);
                multimat->inherit_bdf(reflective, specular);
                bsdf = (Bsdf*)multimat;
                break;
            }
            case METAL:
            {
                Spectrum ior;
                Spectrum absorption;
                Bdf* bdf;
                MicrofacetDist* dist;
                Fresnel* fresnel;
                ior = Spectrum(METALS[union_m.mat.elem].n);
                absorption = Spectrum(METALS[union_m.mat.elem].k);
                if(rough_x == 0 && rough_y == -1)
                    bdf = new ConductorReflection(ior, absorption);
                else
                {
                    if(rough_y == -1)
                    {
                        switch(union_m.mat.dist)
                        {
                            case BLINN:
                                dist = new Blinn(2.f/(rough_x*rough_x)-2.f);
                                break;
                            case BECKMANN:dist = new Beckmann(rough_x);
                                break;
                            case GGX:dist = new GGXiso(rough_x);
                                break;
                        }
                    }
                    else
                        dist = new GGXaniso(rough_x, rough_y);
                    fresnel = new Conductor(ior, absorption);
                    bdf = new MicrofacetR(dist, fresnel);
                }
                bsdf = new SingleBRDF(bdf);
                break;
            }
        }
        //resolve normalmap now that the material has been allocated
        if(union_m.mat.normal != NULL)
        {
            const Texture* bumptex = TexLib.get_texture(union_m.mat.normal);
            if(bumptex == NULL)
            {
                bumptex = TexLib.get_dflt_texture();
                Console.warning(MESSAGE_TEXTURE_NOT_FOUND_MTL,
                                union_m.mat.normal, union_m.mat.name);
            }
            free(union_m.mat.normal);
            bsdf->inherit_bump(new TextureNormal(bumptex));
        }
        MtlLib.add_inherit(union_m.mat.name, bsdf);
        free(union_m.mat.name);
    }
}

/**
 *  \brief Parse every dualmaterial contained in the parsed_dualmaterials
 *
 *  Add every material contained inside the parsed_dualmaterials stack of the
 *  ParsedScene into the MaterialLibrary. The parsed_dualmaterials stack is
 *  emptied during this process
 *
 *  \param[in] parsed The struct containing parsed raw values
 */
static void build_dualmaterials(ParsedScene* parsed)
{
    const Bsdf* first;
    const Bsdf* second;
    const Texture* mask_tex;
    while(!empty_ResizableParsed(&parsed->parsed_dualmaterials))
    {
        ParsedElement union_m;
        top_ResizableParsed(&parsed->parsed_dualmaterials, &union_m);
        pop_ResizableParsed(&parsed->parsed_dualmaterials);
        if(union_m.dualmat.name == NULL ||
           MtlLib.contains(union_m.dualmat.name))
        {
            //no name -> to the trash we go!
            if(union_m.dualmat.first != NULL)
                free(union_m.dualmat.first);
            if(union_m.dualmat.second != NULL)
                free(union_m.dualmat.second);
            if(union_m.dualmat.mask.mask_tex != NULL)
                free(union_m.dualmat.mask.mask_tex);
            continue;
        }

        //resolve first material
        if(union_m.dualmat.first != NULL)
        {
            first = MtlLib.get(union_m.dualmat.first);
            if(first == NULL)
            {
                Console.warning(MESSAGE_MISSING_MATERIAL, union_m.dualmat.first,
                                union_m.dualmat.name);
                first = MtlLib.get_default();
            }
            free(union_m.dualmat.first);
        }
        else
            first = MtlLib.get_default();

        //resolve second material
        if(union_m.dualmat.second != NULL)
        {
            second = MtlLib.get(union_m.dualmat.second);
            if(second == NULL)
            {
                Console.warning(MESSAGE_MISSING_MATERIAL,
                                union_m.dualmat.second, union_m.dualmat.name);
                second = MtlLib.get_default();
            }
            free(union_m.dualmat.second);
        }
        else
            second = MtlLib.get_default();

        //resolve mask
        if(union_m.dualmat.mask.mask_tex != NULL)
        {
            mask_tex = TexLib.get_texture(union_m.dualmat.mask.mask_tex);
            if(mask_tex == NULL)
            {
                Console.warning(MESSAGE_TEXTURE_NOT_FOUND_MTL,
                                union_m.dualmat.mask.mask_tex,
                                union_m.dualmat.name);
                mask_tex = TexLib.get_dflt_texture();
            }
            free(union_m.dualmat.mask.mask_tex);
        }
        else
            mask_tex = TexLib.get_dflt_texture();
        MaskBoolean mask(mask_tex, union_m.dualmat.mask.mask_chn,
                         union_m.dualmat.mask.mask_inv);
        MtlLib.add_inherit(union_m.dualmat.name,
                           new DualBsdf(first, second, mask));
        free(union_m.dualmat.name);
    }
}

/**
 *  \brief Parse every path to obj files contained in the raw data
 *
 *  This method parses every obj file contained in the raw data obtained from
 *  the bison parser and adss them to a temporary std::unordere_map. This is
 *  done because then it is possible to purge unreferenced shapes and delete
 *  them before beginning the actual rendering.
 *
 *  \param[in,out] parsed Raw data obtained from the bison parser
 *  \param[in] cur_dir File class representing the current directory
 *  \param[out] shapes array of shapes that will be used to temporary store
 *  every shape
 */
static void build_mesh_object(ParsedScene* parsed, const File* cur_dir,
                              std::unordered_map<std::string, MeshObject>* shapes)
{
    while(!empty_ResizableStack(&parsed->parsed_mesh_object))
    {
        char* path;
        path = (char*)top_ResizableStack(&parsed->parsed_mesh_object);
        pop_ResizableStack(&parsed->parsed_mesh_object);
        File cur_obj(cur_dir, path);
        if(strcmp(cur_obj.extension(), "obj") != 0)
        {
            Console.severe(MESSAGE_OBJ_ERROR, cur_obj.absolute_path(),
                           cur_obj.extension());
            free(path);
            continue;
        }
        ParserObj parser_obj;
        parser_obj.start_parsing(cur_obj.absolute_path());
        //get_next_mesh() requires the mesh to be already allocated and simply
        //add triangles. since the mesh should survive after this function, it
        //is heap allocated
        Mesh* m = new Mesh(1);
        while(parser_obj.get_next_mesh(m))
        {
            MeshObject insertme;

            insertme.mesh = m;
            insertme.materials_len = parser_obj.get_material_no();
            insertme.materials = (const Bsdf**)malloc(sizeof(const Bsdf*)*
                                                      insertme.materials_len);
            insertme.association = (unsigned char*)malloc(
                    parser_obj.get_face_no());
            parser_obj.get_materials(insertme.materials);
            parser_obj.get_material_association(insertme.association);
            std::string name = parser_obj.get_mesh_name();
            std::unordered_map<std::string, MeshObject>::const_iterator it;
            it = shapes->find(name);
            if(it == shapes->end())
                shapes->insert({{name, insertme}});
            else
            {
                Console.warning(MESSAGE_DUPLICATE_SHAPE, name.c_str());
                delete m; //delete the mesh since it is unused
                free(insertme.materials);
                free(insertme.association);
            }
            //create next object
            m = new Mesh(1);
        }
        //allocated mesh but they were finished
        delete m;
        free(path);
        parser_obj.end_parsing();
    }
}

/**
 *  \brief Parse every mesh in world space contained in the raw data
 *
 *  After parsing the configuration file, this method can be used to place world
 *  space meshes inside the scene. This method tracks which mesh has been used
 *  and which not
 *
 *  \param[in,out] parsed The raw data obtained by parsing the config file
 *  \param[in] shapes The object space meshes that can be positioned in world
 *  space
 *  \param[in] used_shapes A stack containing the shapes used in the scene
 *  \param[out] scene The scene that will be initialized with the world space
 *  meshes
 */
static void build_mesh_world(ParsedScene* parsed,
                             const std::unordered_map<std::string, MeshObject>* shapes,
                             std::unordered_set<std::string>* used_shapes,
                             Scene* scene)
{
    std::unordered_map<std::string, MeshObject>::const_iterator mesh_i;
    while(!empty_ResizableParsed(&parsed->parsed_mesh_world))
    {
        ParsedElement union_m;
        MeshObject mesh_o;
        top_ResizableParsed(&parsed->parsed_mesh_world, &union_m);
        pop_ResizableParsed(&parsed->parsed_mesh_world);
        if(union_m.mesh.name == NULL)
        {
            //BEGONE THOT!
            if(union_m.mesh.material_name != NULL)
                free(union_m.mesh.material_name);
            if(union_m.mesh.mask.mask_tex != NULL)
                free(union_m.mesh.mask.mask_tex);
            continue;
        }
        //parsed obj that will be deleted if not used
        mesh_i = shapes->find(union_m.mesh.name);
        if(mesh_i != shapes->end())
        {
            mesh_o = mesh_i->second;
            used_shapes->insert(union_m.mesh.name);
        }
        else
        {
            Console.warning(MESSAGE_SHAPE_NOT_FOUND, union_m.mesh.name);
            free(union_m.mesh.name);
            if(union_m.mesh.material_name != NULL)
                free(union_m.mesh.material_name);
            if(union_m.mesh.mask.mask_tex != NULL)
                free(union_m.mesh.mask.mask_tex);
            continue; //otherwise it would be an if-else nightmare
        }

        Matrix4 transform;
        Matrix4 position_matrix;
        Matrix4 rotation_matrix;
        Matrix4 rotx_matrix;
        Matrix4 roty_matrix;
        Matrix4 rotz_matrix;
        Matrix4 scale_matrix;
        Vec3 position(union_m.mesh.position[0],
                      union_m.mesh.position[1],
                      union_m.mesh.position[2]);
        Vec3 scale(union_m.mesh.scale[0],
                   union_m.mesh.scale[1],
                   union_m.mesh.scale[2]);
        position_matrix.set_translation(position);
        rotx_matrix.set_rotate_x(union_m.mesh.rotation[0]);
        roty_matrix.set_rotate_y(union_m.mesh.rotation[1]);
        rotz_matrix.set_rotate_z(union_m.mesh.rotation[2]);
        rotation_matrix = rotz_matrix*roty_matrix*rotx_matrix;
        scale_matrix.set_scale(scale);
        //watchout the order!!!
        transform = position_matrix*rotation_matrix*scale_matrix;
        Asset* current_asset = new Asset(mesh_o.mesh, transform, 1);

        //use parsed materials
        if(union_m.mesh.material_name == NULL)
        {
            current_asset->set_materials(mesh_o.materials,
                                         mesh_o.materials_len,
                                         mesh_o.association);
        }
        else //override materials
        {
            const Bsdf* overridden_material;
            overridden_material = MtlLib.get(union_m.mesh.material_name);
            if(overridden_material == NULL)
            {
                //use default if the material is missing
                overridden_material = MtlLib.get_default();
                Console.warning(MESSAGE_MISSING_MATERIAL_OVERRIDE,
                                union_m.mesh.material_name,
                                union_m.mesh.name);
            }
            const Bsdf* materials[1];
            materials[0] = overridden_material;
            unsigned char* associations;
            associations = (unsigned char*)malloc
                    (mesh_o.mesh->get_faces_number());
            memset(associations, 0, mesh_o.mesh->get_faces_number());
            current_asset->set_materials(materials, 1, associations);
            free(associations);
            free(union_m.mesh.material_name);
        }
        //resolve the mask
        if(union_m.mesh.mask.mask_tex != NULL)
        {
            const Texture* mask_tex;
            mask_tex = TexLib.get_texture(union_m.mesh.mask.mask_tex);
            if(mask_tex == NULL)
            {
                Console.warning(MESSAGE_TEXTURE_NOT_FOUND_MTL,
                                union_m.mesh.mask.mask_tex,
                                union_m.mesh.name);
                mask_tex = TexLib.get_dflt_texture();
            }
            free(union_m.mesh.mask.mask_tex);
            MaskBoolean mask(mask_tex, union_m.mesh.mask.mask_chn,
                             union_m.mesh.mask.mask_inv);
            current_asset->set_mask(mask);
        }
        scene->inherit_asset(current_asset);
        free(union_m.mesh.name);
    }
}

/**
 *  \brief Parse every light contained in the raw data
 *
 *  This method is very similar to build_mesh_world, since a light can also
 *  inherit from the Asset class. However, in addition, this method can set
 *  additional variables such as light temperature or other light types
 *
 *  \param[in,out] parsed The raw data obtained by parsing the config file
 *  \param[in] shapes The object space meshes that can be positioned in world
 *  space
 *  \param[in] used_shapes A stack containing the shapes used in the scene
 *  \param[out] scene The scene that will be initialized with the world space
 *  meshes
 */
static void build_lights(ParsedScene* parsed,
                         const std::unordered_map<std::string, MeshObject>* shapes,
                         std::unordered_set<std::string>* used_shapes,
                         Scene* scene, const Point3* cam_pos)
{
    std::unordered_map<std::string, MeshObject>::const_iterator mesh_i;
    std::vector<ParsedLight> sunlights;
    while(!empty_ResizableParsed(&parsed->parsed_lights))
    {
        ParsedElement union_l;
        top_ResizableParsed(&parsed->parsed_lights, &union_l);
        pop_ResizableParsed(&parsed->parsed_lights);

        //set color of the light
        Spectrum intensity;
        //blackbody
        if(union_l.light.temperature>=0)
            intensity = Spectrum(union_l.light.temperature);
        else
        {
            ColorRGB color(union_l.light.color[0],
                           union_l.light.color[1],
                           union_l.light.color[2]); // color is parsed a uint8_t
            intensity = Spectrum(color, true);
        }

        //position the light into the scene
        Matrix4 transform;
        Matrix4 position_matrix;
        Matrix4 rotation_matrix;
        Matrix4 rotx_matrix;
        Matrix4 roty_matrix;
        Matrix4 rotz_matrix;
        Matrix4 scale_matrix;
        Matrix4 pos_rot_matrix;
        Vec3 position(union_l.light.position[0],
                      union_l.light.position[1],
                      union_l.light.position[2]);
        Vec3 scale(union_l.light.scale[0],
                   union_l.light.scale[1],
                   union_l.light.scale[2]);
        position_matrix.set_translation(position);
        rotx_matrix.set_rotate_x(union_l.light.rotation[0]);
        roty_matrix.set_rotate_y(union_l.light.rotation[1]);
        rotz_matrix.set_rotate_z(union_l.light.rotation[2]);
        rotation_matrix = rotz_matrix*roty_matrix*rotx_matrix;
        scale_matrix.set_scale(scale);
        pos_rot_matrix = position_matrix*rotation_matrix;
        transform = pos_rot_matrix*scale_matrix;

        switch(union_l.light.type)
        {
            case AREA:
            {
                Shape* shape;
                if(union_l.light.name == NULL)
                {
                    //no name?
                    //we can't expect god to do all the work '̿'\̵͇̿̿\з=( ͠° ͟ʖ ͡°)=ε/̵͇̿̿/'̿
                    continue;
                }
                //same code of build_meshed, check that one for comments
                mesh_i = shapes->find(union_l.light.name);
                if(mesh_i != shapes->end())
                {
                    shape = mesh_i->second.mesh;
                    used_shapes->insert(union_l.light.name);
                }
                else
                {
                    Console.warning(MESSAGE_SHAPE_NOT_FOUND,
                                    union_l.light.name);
                    break;
                }
                Asset* current_asset = new LightArea(shape, transform,
                                                     intensity);
                //create a default material for cameras
                const Bsdf* materials[1];
                materials[0] = MtlLib.get_default();
                unsigned char* associations;
                associations = (unsigned char*)malloc
                        (shape->get_faces_number());
                memset(associations, 0, shape->get_faces_number());
                current_asset->set_materials(materials, 1, associations);
                free(associations);
                scene->inherit_arealight((LightArea*)current_asset);
                break;
            }
            case OMNI:
            {
                Light* omni = new LightOmni(intensity, position_matrix);
                scene->inherit_light(omni);
                break;
            }
            case SPOT:
            {
                Light* spot = new LightSpot(intensity, pos_rot_matrix,
                                            union_l.light.radius,
                                            union_l.light.falloff);
                scene->inherit_light(spot);
                break;
            }
            case SUN:
            {
                //delay this, because the sunlight needs to have scene size
                sunlights.push_back(union_l.light);
            }
        }
        if(union_l.light.name != NULL)
            free(union_l.light.name);
    }
    //at this point the scene size should be known
    for(ParsedLight& light : sunlights)
    {
        Date time;
        if(light.time != NULL)
        {
            time = Date(light.time);
            free(light.time);
            light.time = NULL;
        }
        //this is repeated in this single case, but likeley there will be
        //just a single sunlight
        Spectrum intensity;
        if(light.temperature>=0)
            intensity = Spectrum(light.temperature);
        else
        {
            ColorRGB color(light.color[0],
                           light.color[1],
                           light.color[2]); // color is parsed a uint8_t
            intensity = Spectrum(color, true);
        }
        Light* sun = new LightSun(intensity, cam_pos,
                                  scene->radius(), time, light.position[0],
                                  light.position[1], light.position[2]);
        scene->inherit_light(sun);
    }
}

Renderer* ParserConfig::parse(const char* filename, Scene* scene)
{
    ParsedScene parsed;
    init_ParsedScene(&parsed);
    //first pass
    parse_rec(filename, &parsed);
    Renderer* renderer;
    if(!parsed.successful)
    {
        Console.critical(parsed.error_msg, filename);
        deinit_ParsedScene(&parsed);
        return NULL;
    }

    //set up everything
    if(parsed.output == NULL)
        parsed.output = strdup("out.ppm");
    check_resolution(&parsed.width, &parsed.height);
    check_spp(parsed.sampler_type, &parsed.spp);
#ifdef DEBUG
    renderer = new Renderer(parsed.width, parsed.height, parsed.spp,
                            parsed.output, 0);
#else
    renderer = new Renderer(parsed.width, parsed.height, parsed.spp,
                            parsed.output);
#endif
    free(parsed.output);
    parsed.output = NULL;
    const File CONFIG_DIR = File(filename).get_parent();
    renderer->set_sampler(parsed.sampler_type);
    renderer->inherit_camera(build_camera(&parsed));
    renderer->inherit_filter(build_filter(&parsed));
    renderer->inherit_integrator(new PathTracer());

    //handle children -> add more data in the original parsed struct
    while(!empty_ResizableStack(&parsed.children))
    {
        char* child = (char*)top_ResizableStack(&parsed.children);
        pop_ResizableStack(&parsed.children);
        File path(&CONFIG_DIR, child);
        //child was allocated in the bison parser. I hate decoupled malloc/free
        free(child);
        if(path.exists())
        {
            ParsedScene parsed_child;
            init_ParsedScene(&parsed_child);
            parse_rec(path.absolute_path(), &parsed_child);
            if(parsed_child.successful)
                merge_ParsedScene(&parsed, &parsed_child);
            else
                Console.severe(parsed_child.error_msg, path.absolute_path());
            deinit_ParsedScene(&parsed_child);
        }
        else
            Console.severe(MESSAGE_INPUT_ERROR_NO_FILE, path.absolute_path());
    }
    deinit_ResizableStack(&parsed.children);

    //handle textures
    build_textures(&parsed, &CONFIG_DIR);
    deinit_ResizableParsed(&parsed.parsed_textures);
    //handle materials
    build_materials(&parsed);
    deinit_ResizableParsed(&parsed.parsed_materials);
    //handle dualmaterials
    build_dualmaterials(&parsed);
    deinit_ResizableParsed(&parsed.parsed_dualmaterials);
    //not every shape will be used. This thing is used to purge unused shape so
    //they don't even see the scene if not referenced at least one time
    std::unordered_map<std::string, MeshObject> shapes;
    std::unordered_set<std::string> used_shapes;
    MeshObject default_sphere;
    default_sphere.mesh = new Sphere();
    default_sphere.materials = (const Bsdf**)malloc(sizeof(const Bsdf*));
    default_sphere.materials[0] = MtlLib.get_default();
    default_sphere.materials_len = 1;
    default_sphere.association = (unsigned char*)malloc(1);
    default_sphere.association[0] = 0;
    shapes.insert({{"Sphere", default_sphere}});
    build_mesh_object(&parsed, &CONFIG_DIR, &shapes);
    deinit_ResizableStack(&parsed.parsed_mesh_object);
    build_mesh_world(&parsed, &shapes, &used_shapes, scene);
    deinit_ResizableParsed(&parsed.parsed_mesh_world);
    Point3 cam_pos(parsed.camera_pos[0], parsed.camera_pos[1],
                   parsed.camera_pos[2]);
    build_lights(&parsed, &shapes, &used_shapes, scene, &cam_pos);
    deinit_ResizableParsed(&parsed.parsed_lights);

    //cleanup
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
            scene->inherit_shape(shape_it->second.mesh);
        free(shape_it->second.materials); //every mesh copies these
        free(shape_it->second.association);
        shape_it++;
    }
    deinit_ParsedScene(&parsed);
    return renderer;
}
