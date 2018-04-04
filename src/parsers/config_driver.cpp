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
    fov = 55.f;
    filter = new MitchellFilter(0.33f,0.33f);
    value0 = 0.33f;
    value1 = 0.33f;
    integrator = new PathTracer();
}

int ConfigDriver::parse(const std::string& f, Renderer* r)
{
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
    r->inherit_camera(camera);
    r->inherit_filter(filter);
    r->inherit_integrator(integrator);
    return 1;
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
#define GRN "\x1B[32m"
#define NRM "\x1B[0m"
#define BLD "\x1B[1m"
    
    unsigned int end_col = 0 < l.end.column ? l.end.column - 1 : 0;
    //underline wrong token
    if(l.begin.column<l.end.column && l.begin.line==l.end.line)
    {
        char buf[128];
        char under[128];
        get_line(buf,128,end_col);
        for(unsigned int i=0;i<l.begin.column-1;i++)
            under[i] = ' ';
        for(unsigned int i=l.begin.column-1;i<end_col;i++)
            under[i] = '~';
        under[end_col] = 0;
        Console.critical("%s:%d.%d: " BLD "%s" NRM "\n%s\n%" GRN "%s" NRM,
                         file.c_str(),l.end.line,end_col,m.c_str(),buf,under);
    }
    else //just print the error
    {
        Console.critical("%s:%d.%d: " BLD "%s" NRM,
                         file.c_str(),l.end.line,end_col,m.c_str());
    }
}

void ConfigDriver::error(const std::string& m)
{
    Console.critical(m.c_str());
}

void ConfigDriver::build_filter()
{
    delete filter;
    switch(filter_type)
    {
        case SPECTRE_FILTER_BOX:
            filter = new BoxFilter();
            break;
        case SPECTRE_FILTER_TENT:
            filter = new TentFilter();
            break;
        case SPECTRE_FILTER_GAUSS:
            filter = new GaussianFilter(value0);
            break;
        case SPECTRE_FILTER_MITCHELL:
            filter = new MitchellFilter(value0,value1);
            break;
        case SPECTRE_FILTER_LANCZOS:
            filter = new LanczosFilter(value0);
            break;
        default:
            /* default is unreachable */
            fprintf(stderr,"Unknown filter type. This is unknown also to the"
                    "Parser so check config_parser.y first\n");
    }
}

void ConfigDriver::build_camera()
{
    delete camera;
    switch(camera_type)
    {
        case SPECTRE_CAMERA_ORTHOGRAPHIC:
            camera = new OrthographicCamera(&camera_pos,&camera_tar,&camera_up,
                                            width,height);
            break;
        case SPECTRE_CAMERA_PERSPECTIVE:
            camera = new PerspectiveCamera(&camera_pos,&camera_tar,&camera_up,
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
