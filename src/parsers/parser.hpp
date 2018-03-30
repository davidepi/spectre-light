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
#include "materials/microfacet.hpp"
#include "materials/microfacet_distributions.hpp"
#include "materials/metals.hpp"
#include "materials/refraction.hpp"
#include "materials/reflection.hpp"
#include "utility/scene.hpp"
#include "primitives/shape.hpp"
#include "primitives/sphere.hpp"
#include "primitives/box.hpp"
#include "primitives/mesh.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <chrono>

enum camera_t{ORTHOGRAPHIC,PERSPECTIVE,PANORAMA};
enum sampler_t{STRATIFIED,RANDOM};
enum filter_t{BOX,TENT,GAUSSIAN,MITCHELL,LANCZOS};
enum integrator_t{DIRECT_LIGHT,PATH_TRACE};

class Settings
{
public:
    Settings();
    ~Settings();
    char* output;
    int resolution[2];
    int spp;
    enum camera_t type_camera;
    Point3 camera_pos;
    Point3 camera_target;
    Vec3 camera_up;
    float camera_fov;
    enum sampler_t type_sampler;
    enum filter_t type_filter;
    enum integrator_t type_integrator;
    float f_val[2];
    Scene* scene;
};

class Parser
{
public:
    void parse(const char* filename, Settings* out);
private:
    std::unordered_map<std::string,int>shapeids;
};

#endif

/**
 * \endcond
 */
