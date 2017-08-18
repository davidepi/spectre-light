//created 17/08

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "console.hpp"
#include "geometry/vec3.hpp"
#include "geometry/point3.hpp"
#include "utility/scene.hpp"
#include "materials/material_library.hpp"
#include "materials/bdf.hpp"
#include "materials/lambertian.hpp"
#include "materials/oren_nayar.hpp"
#include "materials/refraction.hpp"
#include "materials/reflection.hpp"
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
};

class Parser
{
public:
    Settings parse(const char* filename);
};


#endif
