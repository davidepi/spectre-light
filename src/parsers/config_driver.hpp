//created 31 mar 2018

#ifndef __CONFIG_DRIVER_HPP__
#define __CONFIG_DRIVER_HPP__

#include <string>
#include "utility/console.hpp"
#include "geometry/vec3.hpp"
#include "geometry/point3.hpp"
#include "cameras/perspective_camera.hpp"
#include "samplers/mitchell_filter.hpp"
#include "integrators/path_tracer.hpp"
#include "parsers/config_parser.tab.hh"
#include "renderer.hpp"

#define YY_DECL \
yy::ConfigParser::symbol_type yylex(ConfigDriver& driver)
YY_DECL;

class ConfigDriver
{
public:
    ConfigDriver();
    virtual ~ConfigDriver() = default;
    
    void scan_begin();
    void scan_end();
    int parse(const std::string& f, Renderer*)
    {
        file = f;
        scan_begin();
        yy::ConfigParser parser(*this);
        parser.parse();
        scan_end();
        return 1;
    }
    std::string file;
    std::string output;
    int resolution[2];
    int spp;
    //camera constructor needs the resolution (for aspect ration reasons) so
    //it needs to be constructed at the end of the parsing routine
    Point3 camera_position;
    Point3 camera_target;
    Vec3 camera_up;
    float camera_fov;
    char camera_type;
    //sampler is created and destroyed multiple types during rendering, so
    //the type of sampler is requested, instead of the sampler itself
    char sampler_type;
    Filter* filter;
    LightIntegrator* integrator;
    
    void error(const yy::location& l, const std::string& m);
    void error(const std::string& m);
};

#endif
