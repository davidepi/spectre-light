#include "parser_config.hpp"

extern "C" { void parse_config(FILE*, struct ParsedScene*); }

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
                                                       tex_union.tex.filtering);
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

    build_textures(&parsed, &CONFIG_DIR);
    deinit_ResizableParsed(&parsed.parsed_textures);

    return renderer;
}
