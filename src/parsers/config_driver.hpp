//created 31 mar 2018

#ifndef __CONFIG_DRIVER_HPP__
#define __CONFIG_DRIVER_HPP__

#include <string>
#include "utility/console.hpp"
#include "geometry/vec3.hpp"
#include "geometry/point3.hpp"
#include "cameras/orthographic_camera.hpp"
#include "cameras/perspective_camera.hpp"
#include "cameras/camera360.hpp"
#include "samplers/box_filter.hpp"
#include "samplers/tent_filter.hpp"
#include "samplers/gaussian_filter.hpp"
#include "samplers/mitchell_filter.hpp"
#include "samplers/lanczos_filter.hpp"
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
    int parse(const std::string& f, Renderer*);
    std::string file;
    std::string output;
    int resolution[2];
    int spp;
    //camera stored values
    Camera* camera;
    Point3 camera_pos;
    Point3 camera_tar;
    Vec3 camera_up;
    float fov;
    char camera_type;
    void build_camera();
    //sampler type
    char sampler_type;
    //filter stored values
    Filter* filter;
    char filter_type;
    float value0;
    float value1;
    void build_filter();
    LightIntegrator* integrator;
    
    void error(const yy::location& l, const std::string& m);
    void error(const std::string& m);
};

#endif
