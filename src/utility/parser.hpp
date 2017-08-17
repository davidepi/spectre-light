//created 17/08

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "console.hpp"
#include "geometry/vec3.hpp"
#include "geometry/point3.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>

enum camera_type{ORTHOGRAPHIC,PERSPECTIVE};

struct Settings
{
    char* output;
    int resolution[2];
    int spp;
    enum camera_type ct;
    Point3 camera_pos;
    Point3 camera_target;
    Vec3 camera_up;
    float camera_fov;
};

class Parser
{
public:
    Settings parse(const char* filename);
};


#endif
