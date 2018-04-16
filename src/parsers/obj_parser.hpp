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
#include "materials/bdf.hpp"
#include "materials/material_library.hpp"
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib> //strtof

class ObjParser
{
public:
    ObjParser(const char* path);
    ~ObjParser() = default;

    Mesh* parse();
    unsigned char get_material_no()const;
    void get_materials(const Bsdf**)const;
    unsigned int get_face_no()const;
    void get_material_association(unsigned char*)const;

private:
    const char* path;
    bool parse_internal(Mesh* mesh);
    int lineno;
    unsigned int face_no;
    //list of the materials used in this object
    std::vector<const Bsdf*> materials;
    //the material associated for every triangle. It is the offset of the
    // materials array
    std::vector<unsigned char> material_association;
};

#endif

/**
 * \endcond
 */
