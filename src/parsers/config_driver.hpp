//created 31 mar 2018

#ifndef __CONFIG_DRIVER_HPP__
#define __CONFIG_DRIVER_HPP__

#include <string>
#include "utility/console.hpp"
#include "utility/utility.hpp"
#include "utility/file.hpp"
#include "utility/imageIO.hpp"
#include "geometry/vec3.hpp"
#include "geometry/point3.hpp"
#include "cameras/camera_orthographic.hpp"
#include "cameras/camera_perspective.hpp"
#include "cameras/camera360.hpp"
#include "samplers/filter_box.hpp"
#include "samplers/filter_tent.hpp"
#include "samplers/filter_gaussian.hpp"
#include "samplers/filter_mitchell.hpp"
#include "samplers/filter_lanczos.hpp"
#include "integrators/path_tracer.hpp"
#include "parsers/config_parser.tab.hh"
#include "textures/texture_library.hpp"
#include "renderer.hpp"

#define YY_DECL \
yy::ConfigParser::symbol_type yylex(ConfigDriver& driver)
YY_DECL;

class ConfigDriver
{
public:
    ConfigDriver();
    virtual ~ConfigDriver() = default;
    
    int parse(const std::string& f, Renderer*);
    std::string file;
    std::string output;
    int width;
    int height;
    void check_resolution();
    int spp;
    void check_spp();
    
    //camera
    Camera* camera;
    Point3 camera_pos;
    Point3 camera_tar;
    Vec3 camera_up;
    float fov;
    char camera_type;
    void build_camera();
    
    //sampler
    char sampler_type;
    
    //filter stored values
    Filter* filter;
    char filter_type;
    float value0;
    float value1;
    void build_filter();
    
    //integrator
    LightIntegrator* integrator;
    
    //texture
    std::string tex_name;
    void load_texture_single(std::string& src);
    void load_texture_folder(std::string& src);
    
    void error(const yy::location& l, const std::string& m);
    void error(const std::string& m);
    
private:
    void scan_begin();
    void scan_end();
    int get_line(char* buf, int len, int col);
};

#endif
