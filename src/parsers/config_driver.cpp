//created 2-04-18

#include "config_driver.hpp"

ConfigDriver::ConfigDriver()
:camera_pos(0,0,0), camera_tar(0,0,1), camera_up(0,1,0)
{
    output = "out.ppm";
    resolution[0] = 800;
    resolution[1] = 600;
    spp = 121;
    sampler_type = SPECTRE_SAMPLER_STRATIFIED;
    camera_type = SPECTRE_CAMERA_PERSPECTIVE;
    fov = 55.f;
    filter = new MitchellFilter(0.33f,0.33f);
    value0 = 0.33f;
    value1 = 0.33f;
    integrator = new PathTracer();
}

int ConfigDriver::parse(const std::string& f, Renderer*)
{
    file = f;
    scan_begin();
    yy::ConfigParser parser(*this);
    parser.parse();
    scan_end();
    return 1;
}

void ConfigDriver::error(const yy::location&, const std::string& m)
{
    Console.critical(m.c_str());
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
                                            resolution[0],resolution[1]);
            break;
        case SPECTRE_CAMERA_PERSPECTIVE:
            camera = new PerspectiveCamera(&camera_pos,&camera_tar,&camera_up,
                                           resolution[0],resolution[1],fov);
            break;
        case SPECTRE_CAMERA_PANORAMA:
            camera = new Camera360(&camera_pos,&camera_tar,&camera_up,
                                           resolution[0], resolution[1]);
            break;
        default:
            /* default is unreachable */
            fprintf(stderr,"Unknown camera type. This is unknown also to the"
                    "Parser so check config_parser.y first\n");
    }
}
