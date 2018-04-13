// Created on 18/08/17.

/**
 * \cond
 *  No documentation for files under parser/ folder since they will be replaced
 *  by flex/bison parsing as soon as possible
 */

#ifndef __OBJ_PARSER_HPP__
#define __OBJ_PARSER_HPP__

#include "primitives/mesh.hpp"
#include "primitives/triangle.hpp"
#include "geometry/point3.hpp"
#include "geometry/vec3.hpp"
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>

    //only tris, mandatory normals, no check on errors
    //very restrictive, yet temporary, parser for debug purposes
    Mesh* parseObj(const char* path);

#endif

/**
 * \endcond
 */
