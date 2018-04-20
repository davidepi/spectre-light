//created 31 mar 2018

#ifndef __CONFIG_DRIVER_HPP__
#define __CONFIG_DRIVER_HPP__

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "parsers/parser_obj.hpp"
#include "primitives/mesh.hpp"
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
#include "materials/bdf.hpp"
#include "materials/metals.hpp"
#include "materials/lambertian.hpp"
#include "materials/oren_nayar.hpp"
#include "materials/microfacet.hpp"
#include "materials/microfacet_distributions.hpp"
#include "materials/reflection.hpp"
#include "materials/refraction.hpp"
#include "renderer.hpp"

#define YY_DECL \
yy::ConfigParser::symbol_type yylex(ConfigDriver& driver)
YY_DECL;

enum mat_t {MATTE,GLOSSY,METAL,GLASS};

class ParsedMaterial
{
public:
    std::string name;
    metal_t elem;
    mat_t type;
    Spectrum ior;
    float rough_x;
    float rough_y;
    char dist;
    std::string diffuse;
    std::string specular;
    
    ParsedMaterial();
};

//bind mesh and materials
struct MeshAgglomerate
{
    Mesh* mesh;
    const Bsdf** materials;
    unsigned char materials_len;
    unsigned char* association;
    unsigned int association_len;
};

class WorldMesh
{
public:
    std::string name;
    std::string material_name;
    Point3 position;
    Vec3 rotation;
    Vec3 scale;

    WorldMesh():scale(1){};
};

class ConfigDriver
{
public:
    ConfigDriver();
    virtual ~ConfigDriver() = default;
    
    Renderer* parse(const std::string& f);
    std::string file;
    File current_dir;
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
    std::string tex_src;
    Vec3 tex_color;
    void load_texture_single();
    void load_texture_folder();
    void load_texture_uniform();
    
    //materials
    ParsedMaterial cur_mat;
    //deferred because depending on textures
    std::vector<ParsedMaterial>deferred_materials;
    void build_materials();
    std::vector<std::string> children;

    //shapes
    void allocate_shape(const char* obj_file);
    //deferred because depending on materials
    std::vector<std::string> deferred_shapes;
    std::unordered_map<std::string,MeshAgglomerate> shapes;

    //world and lights
    WorldMesh cur_mesh;
    //deferred becuse depending on materials and objects
    std::vector<WorldMesh> deferred_meshes;
    std::unordered_set<std::string> used_shapes;
    void build_meshes();


    void error(const yy::location& l, const std::string& m);
    void unknown_char(const yy::location& l, char c);
private:
    void scan_begin();
    void scan_end();
    int get_line(char* buf, int len);
};

#endif
