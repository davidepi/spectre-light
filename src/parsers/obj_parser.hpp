//Created,  18 Aug 2017
//Last Edit 17 Apr 2018

/**
 *  \file      obj_parser.hpp
 *  \brief     Class definition of a .obj parser
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      17 Apr 2018
 *  \copyright GNU GPLv3
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
#include <cstdlib>

/**
 *  \class ObjParser obj_parser.hpp "parsers/obj_parser.hpp"
 *  \brief A parser for the .obj ASCII format
 *
 *  This class is a parser for the Wavefront .obj format. With the start_parsing
 *  method a new file is read. Then for every call of get_next_obj a mesh
 *  contained in the file is returned, until NULL when the meshes described in
 *  the .obj files are finished.
 *
 *  This class triangulizes the mesh and tries to recreate surface normals when
 *  these are not found in the parsed file, however, it doesn't take into
 *  account the smoothing groups, so the generated file will always have
 *  per-face normal instead of per-vertex ones.
 *
 *  vertex with four components and textures with one or three components are
 *  not supported and will produced undefined results. Freeform elements instead
 *  are not supported and will be silently ignored.
 *
 *  This class assumes the file was created with a complying program, so error
 *  checking is not performed
 *
 */
class ObjParser
{
public:
    
    ///Default constructor
    ObjParser();
    
    ///Default destructor
    ~ObjParser();
    
    /** \brief Initiates parsing
     *
     *  Starts the parsing of a file passed as parameter. Every information
     *  about other files is dropped. It is not checked if the file is ASCII
     *  or binary, nor if it is really an .obj file
     *
     *  \param[in] path Path to the .obj file that will be parsed.
     */
    void start_parsing(const char* path);
    
    /** \brief Ends parsing
     *
     *  Cleanup function after finishing the paring
     */
    void end_parsing();
    
    /** \brief Returns the next Mesh contained in the parsed file
     *
     *  After calling start_parsing, this function will return every mesh
     *  contained in the file passed to start_parsing. Since a single .obj file
     *  could contain multiple meshes, for each invocation this function returns
     *  one in the order they are encountered in the file. When every mesh has
     *  been returned, this function returns a NULL pointer.
     *
     *  \return The next mesh contained in the parsed .obj file
     */
    Mesh* get_next_mesh();
    
    /** \brief Returns the mesh name
     *
     *  Returns the mesh name for the last mesh retrieved by the get_next_mesh()
     *  function
     *
     *  \return The name of the last parsed mesh
     */
    const std::string& get_mesh_name()const;
    
    /** \brief Returns the number of materials used in the mesh
     *
     *  Returns the number of materials used in the last mesh retrieved by the
     *  get_next_mesh() function
     *
     *  \return The number of materials used in the last parsed mesh
     */
    unsigned char get_material_no()const;
    
    /** \brief Returns the materials used in the mesh
     *
     *  Returns the materials used in the last mesh retrieved by the
     *  get_next_mesh() function. Note that the array must be already
     *  initialized.
     *
     *  \param[out] mats The materials used in the last parsed mesh. The array
     *  must be already initialized
     *  \sa get_material_no()
     */
    void get_materials(const Bsdf** mats)const;
    
    /** \brief Returns the number of triangles used in the mesh
     *
     *  Returns the number of triangles used in the last mesh retrieved by the
     *  get_next_mesh() function
     *
     *  \return The number of triangles used in the last parsed mesh
     */
    unsigned int get_face_no()const;
    
    /** \brief Return the material used by every triangle
     *
     *  Return the association n-triangle:material, where the association is
     *  the offset in the material array returned with get_materials(). This
     *  class assumes that the given array is already initialized
     *
     *  \param[out] assoc The association (tris number, material array offset).
     *  The array is assumed to be already allocated with the correct size
     *  \sa get_face_no();
     *  \sa get_materials();
     */
    void get_material_association(unsigned char* assoc)const;

private:
    
    //path of the parsed file
    const char* path;
    //input file
    FILE* fin;
    //buffer containing the read data
    char* buffer_ro;
    //number of bytes read while filling buffer_ro
    int read_bytes;
    //pointer pointing to buffer_ro with the data to be processed
    char* buffer;
    //function used to actually parse the mesh
    bool parse_internal(Mesh* mesh);
    //current_line being read
    int lineno;
    //use `g` keyword as `o` for filenames
    bool groups_as_names;
    //number of faces of the current mesh
    unsigned int face_no;
    //list of the materials used in this object
    std::vector<const Bsdf*> materials;
    //the material associated for every triangle. It is the offset of the
    // materials array
    std::vector<unsigned char> material_association;
    //name of the mesh
    std::string object_name;
    //vertices of every mesh contained in the file
    std::vector<Point3>vertices;
    //texture coord of every mesh contained in the file
    std::vector<Point2>textures;
    //normal of every mesh contained in the file
    std::vector<Normal>normals;
};

#endif
