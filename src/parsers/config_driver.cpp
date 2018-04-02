//created 2-04-18

#include "config_driver.hpp"

ConfigDriver::ConfigDriver()
:camera_position(0,0,0), camera_target(0,0,1), camera_up(0,1,0)
{
    output = "out.ppm";
    resolution[0] = 800;
    resolution[1] = 600;
    spp = 121;
    sampler_type = SPECTRE_STRATIFIED_SAMPLER;
    camera_type = SPECTRE_CAMERA_PERSPECTIVE;
    filter = new MitchellFilter(0.33f,0.33f);
    integrator = new PathTracer();
}

void ConfigDriver::error(const yy::location&, const std::string& m)
{
    Console.critical(m.c_str());
}

void ConfigDriver::error(const std::string& m)
{
    Console.critical(m.c_str());
}
