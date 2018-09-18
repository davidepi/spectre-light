#include "parser_config.hpp"

extern "C" { void parse_config(FILE*, struct ParsedScene*); }

///minimum value for ParsedMaterial::rough_x when the material is not specular
#define MIN_ROUGH 0.001f

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
    //TODO: check NULL
    parse_config(fin, parsed);
    fclose(fin);
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
                                           parsed->fov);
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
    const Bump* normal;
    float rough_x;
    float rough_y;
    while(!empty_ResizableParsed(&parsed->parsed_materials))
    {
        ParsedElement union_m;
        top_ResizableParsed(&parsed->parsed_materials, &union_m);
        pop_ResizableParsed(&parsed->parsed_materials);

        //free everything and continue if materials is unnamed or already exists
        if(union_m.mat.name == NULL || MtlLib.contains(union_m.mat.name))
        {
            if(union_m.mat.name != NULL)
                free(union_m.mat.name);
            if(union_m.mat.diffuse != NULL)
                free(union_m.mat.diffuse);
            if(union_m.mat.specular != NULL)
                free(union_m.mat.specular);
            if(union_m.mat.normal != NULL)
                free(union_m.mat.normal);
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

        //resolve normal map
        if(union_m.mat.specular != NULL)
        {
            const Texture* bumptex = TexLib.get_texture(union_m.mat.normal);
            if(bumptex == NULL)
            {
                bumptex = TexLib.get_dflt_texture();
                Console.warning(MESSAGE_TEXTURE_NOT_FOUND_MTL,
                                union_m.mat.normal, union_m.mat.name);
            }
            free(union_m.mat.normal);
            normal = new TextureNormal(bumptex);
        }
        else
            normal = new Bump();

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
        bsdf->inherit_bump(normal);
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

Renderer* ParserConfig::parse(const char* filename, Scene* scene)
{
    ParsedScene parsed;
    init_ParsedScene(&parsed);
    //first pass
    parse_rec(filename, &parsed);

    //set up everything
    check_resolution(&parsed.width, &parsed.height);
    check_spp(parsed.sampler_type, &parsed.spp);
    Renderer* renderer;
#ifdef DEBUG
    renderer = new Renderer(parsed.width, parsed.height, parsed.spp,
                            parsed.output, 0);
#else
    renderer = new Renderer(parsed.width, parsed.height, parsed.spp, parsed.output);
#endif
    const File CONFIG_DIR = File(parsed.output).get_parent();
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
            parse_rec(path.absolute_path(), &parsed);
        else
            Console.severe(MESSAGE_INPUT_ERROR, path.absolute_path());
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

    return renderer;
}
