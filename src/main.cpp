//author: Davide Pizzolotto
//license: GNU GPLv3

#include "utility/console.hpp"
#include "parsers/parser.hpp"
#include "renderer.hpp"
#ifdef IMAGEMAGICK
#include <Magick++.h>
#include <type_traits> //std::is_floating_point
#endif

int main(int argc, char* argv[])
{
#ifdef IMAGEMAGICK
    Magick::InitializeMagick(IMAGEMAGICK);
    std::is_floating_point<Magick::Quantum> is_fp;
    if(!is_fp.value)
        Console.severe(MESSAGE_IM_NOFLOAT);
#endif
    Parser parser;
    Settings settings;
    if(argc < 2)
        Console.critical("Input should be in the form: executable input_file");
    else
        parser.parse(argv[1],&settings);
#ifndef DEBUG
    Renderer renderer(settings.resolution[0],settings.resolution[1],
                      settings.spp,settings.output);
#else
    Renderer renderer(settings.resolution[0], settings.resolution[1],
                      settings.spp,settings.output,1);
#endif

    switch(settings.type_camera)
    {
        case ORTHOGRAPHIC:
        {
            renderer.setOrthographic(settings.camera_pos,settings.camera_target,
                                     settings.camera_up);
            break;
        }
        case PERSPECTIVE:
        {
            renderer.setPerspective(settings.camera_pos, settings.camera_target,
                                    settings.camera_up, settings.camera_fov);
            break;
        }
        case PANORAMA:
        {
            renderer.setPanorama(settings.camera_pos,settings.camera_target,
                                 settings.camera_up);
            break;
        }
    }
    switch(settings.type_sampler)
    {
        case RANDOM:
        {
            renderer.setRandomSampler();
            break;
        }
        case STRATIFIED:
        {
            renderer.setStratifiedSampler();
            break;
        }
    }
    switch(settings.type_filter)
    {
        case BOX:
        {
            renderer.setBoxFilter();
            break;
        }
        case TENT:
        {
            renderer.setTentFilter();
            break;
        }
        case GAUSSIAN:
        {
            renderer.setGaussianFilter(settings.f_val[0]);
            break;
        }
        case MITCHELL:
        {
            renderer.setMitchellFilter(settings.f_val[0],settings.f_val[1]);
            break;
        }
        case LANCZOS:
        {
            renderer.setLanczosSincFilter(settings.f_val[0]);
            break;
        }
    }
    switch(settings.type_integrator)
    {
        case PATH_TRACE:
        {
            renderer.setPathTracer();
            break;
        }
    }

    return renderer.render(settings.scene);
}
