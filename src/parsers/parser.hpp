//created 17/08
/**
 * \cond
 *  No documentation for files under parser/ folder since they will be replaced
 *  by flex/bison parsing as soon as possible
 */

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "utility/console.hpp"
#include "geometry/vec3.hpp"
#include "geometry/point3.hpp"
#include "utility/scene.hpp"
#include "materials/material_library.hpp"
#include "materials/bdf.hpp"
#include "materials/lambertian.hpp"
#include "materials/oren_nayar.hpp"
#include "materials/refraction.hpp"
#include "materials/reflection.hpp"
#include "parsers/obj_parser.hpp"
#include "utility/scene.hpp"
#include "primitives/shape.hpp"
#include "primitives/sphere.hpp"
#include "primitives/mesh.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>

enum camera_type{ORTHOGRAPHIC,PERSPECTIVE};
enum sampler_type{STRATIFIED,RANDOM};
enum filter_type{BOX,TENT,GAUSSIAN,MITCHELL,LANCZOS};
enum integrator_type{DIRECT_LIGHT,PATH_TRACE};

class Settings
{
public:
    Settings();
    ~Settings();
    char* output;
    int resolution[2];
    int spp;
    enum camera_type ct;
    Point3 camera_pos;
    Point3 camera_target;
    Vec3 camera_up;
    float camera_fov;
    enum sampler_type st;
    enum filter_type ft;
    enum integrator_type it;
    float f_val[2];
    Scene* sc;
};

class Parser
{
public:
    void parse(const char* filename, Settings* out);
private:
    std::unordered_map<std::string,int>shapeids;
};

/**
 * \endcond
 */

#endif
