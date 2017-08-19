#include "parsers/parser.hpp"
#include "utility/console.hpp"
#include "renderer.hpp"

int main(int argc, char* argv[])
{
    Parser p;
    Settings s;
    if(argc < 2)
        Console.critical("Input should be in the form: executable input_file");
    else
        p.parse(argv[1],&s);

    Renderer r(s.resolution[0],s.resolution[1],s.spp,s.output);
    Scene* scene = s.sc;
    scene->k.buildTree(); //build kd-tree

    switch (s.ct)
    {
        case ORTHOGRAPHIC:r.setOrthographic(s.camera_pos,s.camera_target,
                                            s.camera_up);break;
        case PERSPECTIVE:r.setPerspective(s.camera_pos,s.camera_target,
                                          s.camera_up,s.camera_fov);break;
    }
    switch(s.st)
    {
        case RANDOM:r.setRandomSampler();break;
        case STRATIFIED:r.setStratifiedSampler();break;
    }
    switch(s.ft)
    {
        case BOX:r.setBoxFilter();break;
        case TENT:r.setTentFilter();break;
        case GAUSSIAN:r.setGaussianFilter(s.f_val[0]);break;
        case MITCHELL:r.setMitchellFilter(s.f_val[0],s.f_val[1]);break;
        case LANCZOS:r.setLanczosSincFilter(s.f_val[0]);break;
    }
    switch(s.it)
    {
        case DIRECT_LIGHT:r.setRayTracer();break;
        case PATH_TRACE:r.setPathTracer();break;
    }

    return r.render(scene);
}
