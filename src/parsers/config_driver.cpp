//created 2-04-18

#include "config_driver.hpp"

ConfigDriver::ConfigDriver()
:camera_pos(0,0,0), camera_tar(0,0,1), camera_up(0,1,0)
{
    output = "out.ppm";
    width = 800;
    height = 600;
    spp = 121;
    sampler_type = SPECTRE_SAMPLER_STRATIFIED;
    camera_type = SPECTRE_CAMERA_PERSPECTIVE;
    camera = NULL;
    fov = 55.f;
    filter = new FilterMitchell(0.33f,0.33f);
    value0 = 0.33f;
    value1 = 0.33f;
    integrator = new PathTracer();
    tex_name = "";
}

Renderer* ConfigDriver::parse(const std::string& f)
{
    Renderer* r = NULL;
    file = f;
    scan_begin();
    yy::ConfigParser parser(*this);
    parser.parse();
    scan_end();
    check_resolution();
    check_spp();
#ifdef DEBUG //single threaded
    r = new Renderer(width,height,spp,output.c_str(),1);
#else //maximum threads
    r = new Renderer(width,height,spp,output.c_str());
#endif
    r->set_sampler(sampler_type);
    build_camera();
    r->inherit_camera(camera);
    r->inherit_filter(filter);
    r->inherit_integrator(integrator);
    build_materials();
    return r;
}

void ConfigDriver::check_resolution()
{
    float rem = width%SPLIT_SIZE;
    if(rem!=0)
    {
        float aspect_ratio = (float)width/(float)height;
        width+=SPLIT_SIZE-rem;
        height+=(int)((SPLIT_SIZE-rem)/aspect_ratio);
        if(height%2!=0)
            height++;
        Console.notice(MESSAGE_RESOLUTION_CHANGED,SPLIT_SIZE,width,height);
    }
}

void ConfigDriver::check_spp()
{
    if(sampler_type==SPECTRE_SAMPLER_STRATIFIED)
    {
        float root = sqrtf(spp);
        if((int)root*(int)root!=spp)
        {
            spp = static_cast<int>(static_cast<float>(root+.5f));
            spp*=spp;
            Console.notice(MESSAGE_SPP_CHANGED,spp);
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
    unsigned int end_col = 0 < l.end.column ? l.end.column - 1 : 0;
    //underline wrong token
    if(l.begin.column<l.end.column && l.begin.line==l.end.line &&
       l.end.column-l.begin.column<=BUFFER-5) //prev. segfault if token len >buf
    {
        char buf[128];
        char under[128];
        int offset = get_line(buf,128);
        for(unsigned int i=0;i<l.begin.column-1-offset;i++)
            under[i] = ' ';
        for(unsigned int i=l.begin.column-1-offset;i<end_col-offset;i++)
            under[i] = '~';
        under[end_col-offset] = 0;
        Console.critical("%s:%d.%d: " BLD "%s" NRM "\n%s\n%" GRN "%s" NRM,
                         file.c_str(),l.end.line,end_col,m.c_str(),buf,under);
    }
    else //just print the error
    {
        Console.critical("%s:%d.%d: " BLD "%s" NRM,
                         file.c_str(),l.end.line,end_col,m.c_str());
    }
}

void ConfigDriver::unknown_char(const yy::location& l, char c)
{
    //MESSAGE_SYNTAX_ERROR constains a %c that is substituted by a sinlge char
    //gaining 1 space for the \0. Hence the missing +1 in the array alloc.
    char errormsg[sizeof(MESSAGE_SYNTAX_ERROR)]; //constexpr strlen()
    sprintf(errormsg,MESSAGE_SYNTAX_ERROR,c);
    error(l,std::string(errormsg));
}

void ConfigDriver::build_filter()
{
    delete filter;
    switch(filter_type)
    {
        case SPECTRE_FILTER_BOX:
            filter = new FilterBox();
            break;
        case SPECTRE_FILTER_TENT:
            filter = new FilterTent();
            break;
        case SPECTRE_FILTER_GAUSS:
            filter = new FilterGaussian(value0);
            break;
        case SPECTRE_FILTER_MITCHELL:
            filter = new FilterMitchell(value0,value1);
            break;
        case SPECTRE_FILTER_LANCZOS:
            filter = new FilterLanczos(value0);
            break;
        default:
            /* default is unreachable */
            fprintf(stderr,"Unknown filter type. This is unknown also to the"
                    "Parser so check config_parser.y first\n");
    }
}

void ConfigDriver::build_camera()
{
    if(camera!=NULL)
        delete camera;
    switch(camera_type)
    {
        case SPECTRE_CAMERA_ORTHOGRAPHIC:
            camera = new CameraOrthographic(&camera_pos,&camera_tar,&camera_up,
                                            width,height);
            break;
        case SPECTRE_CAMERA_PERSPECTIVE:
            camera = new CameraPerspective(&camera_pos,&camera_tar,&camera_up,
                                           width,height,fov);
            break;
        case SPECTRE_CAMERA_PANORAMA:
            camera = new Camera360(&camera_pos,&camera_tar,&camera_up,
                                   width,height);
            break;
        default:
            /* default is unreachable */
            fprintf(stderr,"Unknown camera type. This is unknown also to the"
                    "Parser so check config_parser.y first\n");
    }
}

static void load_texture_rec(File& src)
{
    if(src.exists() && src.readable())
    {
        if(src.is_folder()) //recursive call if folder
        {
            std::vector<File> res;
            src.ls(&res);
            for(int i=0;i<(int)res.size();i++)
                load_texture_rec(res.at(i));
        }
        else
        {
            if(image_supported(src.extension())>=0) //check extension
            {
                printf("load texture %s\n",src.filename());
                //TODO: placeholder because the texture class is not ready
                //TOOD: check texture not already loaded
                Texture* addme = new UniformTexture(SPECTRUM_WHITE);
                TexLib.add_inherit(src.filename(), addme);
            }
            else
                /* silently skip unsupported texture */;
        }
    }
}

void ConfigDriver::load_texture_folder()
{
    File current_file(tex_src.c_str());
    load_texture_rec(current_file);
}

void ConfigDriver::load_texture_uniform()
{
    if(!tex_name.empty())
    {
        tex_color.clamp(Vec3(0,0,0), Vec3(255,255,255));
        ColorRGB rgb((unsigned char)tex_color.x,
                     (unsigned char)tex_color.y,
                     (unsigned char)tex_color.z);
        Spectrum color(rgb,false);
        TexLib.add_inherit(tex_name, new UniformTexture(color));
        tex_name.clear();
    }
}

void ConfigDriver::load_texture_single()
{
    File cur_file(tex_src.c_str());
    if(cur_file.exists() && cur_file.readable() && !cur_file.is_folder() &&
       image_supported(cur_file.extension())>=0)
    {
        //TODO: placeholder because the texture class is not ready
        //TOOD: check texture not already loaded (MESSAGE_DUPLICATE_TEXTURE)
        if(tex_name.empty())
            tex_name = cur_file.filename();
        Texture* addme = new UniformTexture(SPECTRUM_WHITE);
        TexLib.add_inherit(tex_name, addme);
        tex_name.clear(); //reset name for next texture
    }
    else
        Console.warning(MESSAGE_TEXTURE_ERROR,cur_file.absolute_path());
}

void ConfigDriver::build_materials()
{
    ParsedMaterial* mat;
    Bsdf* material;
    const Texture* diffuse;
    const Texture* specular;
    for(int i=0;i<(int)deferred_materials.size();i++)
    {
        mat = &deferred_materials[i];
        //isotropic element, no point in using anisotropic one
        if(mat->rough_y==mat->rough_x)
            mat->rough_y=-1;
        mat->rough_x = clamp(mat->rough_x,0.f,1.f);
        if(mat->rough_y!=-1)
        {
            //cannot be specular so avoid 0
            mat->rough_x = clamp(mat->rough_x,0.0001f,1.f);
            mat->rough_y = clamp(mat->rough_y,0.0001f,1.f);
        }
        switch(mat->type)
        {
            case MATTE:
            {
                material = new SingleBRDF();
                if(TexLib.contains(mat->diffuse))
                    diffuse = TexLib.get(mat->diffuse);
                else
                {
                    Console.warning(MESSAGE_TEXTURE_NOT_FOUND,
                                    mat->diffuse.c_str(),mat->name.c_str());
                    diffuse = TexLib.get("Default");
                }
                if(mat->rough_x!=0)
                {
                    float roughness = lerp(mat->rough_x, 0.f, 100.f);
                    material->inherit_bdf(new OrenNayar(roughness),diffuse);
                }
                else
                    material->inherit_bdf(new Lambertian,diffuse);
                break;
            }
            case GLOSSY:
            {
                material = new Bsdf();
                Fresnel* fresnel = new Dielectric(cauchy(1.f,0),cauchy(1.5f,0));
                MicrofacetDist* dist;
                if(TexLib.contains(mat->diffuse))
                    diffuse = TexLib.get(mat->diffuse);
                else
                {
                    Console.warning(MESSAGE_TEXTURE_NOT_FOUND,
                                    mat->diffuse.c_str(),mat->name.c_str());
                    diffuse = TexLib.get("Default");
                }
                if(TexLib.contains(mat->specular))
                    diffuse = TexLib.get(mat->specular);
                else
                {
                    Console.warning(MESSAGE_TEXTURE_NOT_FOUND,
                                    mat->specular.c_str(),mat->name.c_str());
                    diffuse = TexLib.get("Default");
                }
                material->inherit_bdf(new Lambertian(),diffuse);
                //no specular in glossy, avoid division by zero
                if(mat->rough_x==0)
                    mat->rough_x = 0.0001;
                if(mat->rough_y!=-1)
                    dist = new GGXaniso(mat->rough_x,mat->rough_y);
                else
                {
                    if(mat->dist == SPECTRE_DIST_BLINN)
                        dist = new Blinn(2.f/(mat->rough_x*mat->rough_x)-2);
                    else if(mat->dist == SPECTRE_DIST_BECKMANN)
                        dist = new Beckmann(mat->rough_x);
                    else
                        dist = new GGXiso(mat->rough_x);
                }
                material->inherit_bdf(new MicrofacetR(dist,fresnel),specular);
            }
            case GLASS:
            {
                if(TexLib.contains(mat->diffuse))
                    diffuse = TexLib.get(mat->diffuse);
                else
                {
                    Console.warning(MESSAGE_TEXTURE_NOT_FOUND,
                                    mat->diffuse.c_str(),mat->name.c_str());
                    diffuse = TexLib.get("Default");
                }
                if(TexLib.contains(mat->specular))
                    diffuse = TexLib.get(mat->specular);
                else
                {
                    Console.warning(MESSAGE_TEXTURE_NOT_FOUND,
                                    mat->specular.c_str(),mat->name.c_str());
                    diffuse = TexLib.get("Default");
                }
                material = new Bsdf();
                Bdf* reflective;
                Bdf* refractive;
                Spectrum etai = cauchy(1.f,0.f);
                if(mat->rough_x==0 && mat->rough_y==-1) //spec
                {
                    reflective = new DielectricReflection(etai,mat->ior);
                    refractive = new Refraction(etai,mat->ior);
                }
                else
                {
                    MicrofacetDist* dist_r;
                    MicrofacetDist* dist_t;
                    Fresnel* fresnel_r = new Dielectric(etai,mat->ior);
                    if(mat->rough_y!=-1)
                    {
                        dist_r = new GGXaniso(mat->rough_x,mat->rough_y);
                        dist_t = new GGXaniso(mat->rough_x,mat->rough_y);
                    }
                    else
                    {
                        if(mat->dist == SPECTRE_DIST_BLINN)
                        {
                            dist_r=new Blinn(2.f/(mat->rough_x*mat->rough_x)-2);
                            dist_t=new Blinn(2.f/(mat->rough_x*mat->rough_x)-2);
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
                    reflective = new MicrofacetR(dist_r,fresnel_r);
                    refractive = new MicrofacetT(dist_t,etai,mat->ior);
                }
                material->inherit_bdf(refractive,diffuse);
                material->inherit_bdf(reflective,specular);
            }
            case METAL:
            {
                Spectrum ior;
                Spectrum absorption;
                Bdf* bdf;
                MicrofacetDist* dist;
                Fresnel* fresnel;
                material = new SingleBRDF();
                ior = Spectrum(METALS[mat->elem].n);
                absorption = Spectrum(METALS[mat->elem].k);
                if(mat->rough_x==0 && mat->rough_y==-1) //specular
                    bdf = new ConductorReflection(ior,absorption);
                else
                {
                    
                    if(mat->rough_x!=0 && mat->rough_y!=-1) //anisotropic microf
                        dist = new GGXaniso(mat->rough_x,mat->rough_y);
                    else
                    {
                        if(mat->dist == SPECTRE_DIST_BLINN)
                            dist = new Blinn(2.f/(mat->rough_x*mat->rough_x)-2);
                        else if(mat->dist == SPECTRE_DIST_BECKMANN)
                            dist = new Beckmann(mat->rough_x);
                        else
                            dist = new GGXiso(mat->rough_x);
                    }
                    fresnel = new Conductor(ior,absorption);
                    bdf = new MicrofacetR(dist,fresnel);
                }
                material->inherit_bdf(bdf);
            }
        }
        if(!MtlLib.contains(mat->name))
            MtlLib.add_inherit(mat->name,material);
        else
        {
            Console.warning(MESSAGE_DUPLICATE_MATERIAL,mat->name.c_str());
            delete material; //already existent, prevents memory leaks
        }
    }
}

ParsedMaterial::ParsedMaterial()
{
    name = "";
    elem = METAL_GOLD;
    type = MATTE;
    ior = cauchy(1.45f, 0.f);
    rough_x = 0;
    rough_y = -1;
    dist = SPECTRE_DIST_BECKMANN;
    diffuse = "Default";
    specular = "Default";
}
