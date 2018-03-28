//Created,   6 Aug 2017
//Last Edit 28 Mar 2018

/**
 *  \file mesh.hpp
 *  \brief     A collection of triangles
 *  \details   All the methods to represent a triangle mesh in the space
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      28 Mar 2018
 *  \copyright GNU GPLv3
 */


#ifndef __MESH_HPP__
#define __MESH_HPP__

#include "localization.h"
#include "primitives/shape.hpp"
#include "primitives/triangle.hpp"
#include "geometry/matrix4.hpp"
#include "geometry/point3.hpp"
#include "geometry/vec3.hpp"
#include "geometry/AABB.hpp"
#include "utility/console.hpp"
#include "accelerators/bvh.hpp"
#include "materials/bdf.hpp"
#include "materials/material_library.hpp"


/**
 *  \class Mesh mesh.hpp "primitives/mesh.hpp"
 *  \brief Implementation of a collection of triangles
 *
 *  This class contains the definition of several triangles. These triangles
 *  are grouped together in order to form a single shape.
 *
 *  In order to create a Mesh it is necessary to give the number of triangles
 *  as a parameter to the constructor. Then call the Mesh::add_triangle function
 *  for every triangle and in the end the Mesh::finalize function
 */
class Mesh : public Shape
{
public:

    /** \brief Default constructor
     *
     *  \param[in] size The number of triangles of the mesh
     *  \param[in] mat_size The number of materials of the mesh. Immutable
     */
    Mesh(unsigned int size, unsigned char mat_size);

    ///Default destructor
    ~Mesh();

    /** \brief Add a triangle to this Mesh
     *
     *  Add a triangle to this mesh, with differents normal per vertex
     *  The triangles can be added also directly in world-space.
     *
     *  \param[in] a The first vertex
     *  \param[in] b The second vertex
     *  \param[in] c The third vertex
     *  \sa add_triangle(const Point3* a, const Point3* b, const Point3* c,
     *               const Normal* n);
     */
    void add_triangle(const Vertex* a, const Vertex* b, const Vertex* c);

    /** \brief Add a triangle to this Mesh
     *
     *  Add a triangle to this mesh, with the same normal per vertex
     *  The triangles can be added also directly in world-space.
     *
     *  \param[in] a The first vertex position in the space
     *  \param[in] b The second vertex position in the space
     *  \param[in] c The third vertex position in the space
     *  \param[in] n The normal for the three vertices
     *  \sa add_triangle(const Vertex* a, const Vertex* b, const Vertex* c);
     */
    void add_triangle(const Point3& a, const Point3& b, const Point3& c,
                     const Normal& n);

    /** \brief Finalize the mesh
     *
     *  Perform some computation after every vertex has been added. These
     *  computation includes building the acceleration structure and
     *  precomputing the results of some function that will not change during
     *  the execution
     */
    void finalize();

    /** \brief Intersection of a Ray and this mesh
     *
     *  This method tries to intersect a ray passed as a parameter with the
     *  mesh, returning true or false if the intersection happened in the
     *  range defined by the minimum epsilon and the distance parameter.
     *  If the intersection happened, the variables \p distance and \p h
     *  are set based on the result.
     *
     *  The intersection is tried in an acceleration structure and forwarded
     *  to the minimum number of underlying triangle as possible
     *
     *  \param[in] r A pointer to the ray used to perform the intersection
     *  \param[out] distance The distance of the point of intersection
     *  \param[out] h an HitPoint class containing information about the
     *  intersection point
     */
    bool intersect(const Ray* r,float* distance, HitPoint* h)const;

    /** \brief Calculate the AABB
     *
     *  This method returns an AABB that can fit well on this mesh. This AABB
     *  is precomputed in the Mesh::finalize method
     *
     *  \return an AABB representing the calculated bounding box
     */
    AABB compute_AABB()const;

    /** \brief Calculate the AABB in world space
     *
     *  This method returns an AABB that can fit well on the world space
     *  mesh, without actually transforming it. This AABB is precomputed in the
     *  Mesh::finalize method
     *
     *  \param[in] trans The transform matrix used to transform the mesh
     *  from object space to world space
     *
     *  \return an AABB representing the world space bounding box
     */
    AABB compute_AABB(const Matrix4* trans)const;

    /** \brief Returns the surface of the mesh
     *
     *  This method computes the surface area of the mesh, useful if it is a
     *  light source.
     *
     *  \return A float representing the area of the mesh in obbject-space
     *  units
     */
    float surface()const;

    /** \brief Return the surface of the mesh considering the scaling factor
     *
     *  This method computes the surface area of the mesh, useful if the mesh is
     *  a light source. Compared to the other surface() method, this one
     *  accounts also for the scaling factor of the transform matrix
     *
     *  \param[in] transform The transform matrix
     *
     *  \return A float representing the area of the mesh in world-space units
     */
    float surface(const Matrix4* transform)const;

    /** \brief Return the number of face of the mesh
     *
     *  This function returns the number of tris composing the mesh
     *
     *  \return The number of faces in a Mesh
     */
    int get_faces_number()const;

    /** \brief Populate the array of cumulative densities
     *
     *  This function populates the densities array. For each triangle, ordered,
     *  the area of the current triangle is calculated and added to the previous
     *  result. With this array it is possible to random sample a mesh with
     *  differently sized triangles. Every surface is calculated considering
     *  the world-space transformed shape
     *
     *  \param[in] transform The object to world space matrix
     *  \param[out] array The array of cumulative densities
     */
    void get_densities_array(const Matrix4* transform, float* array)const;

    /** \brief Returns a random point on the surface of the mesh
     *
     *  Useful for the light sources, this method returns a random point on the
     *  surface of the mesh.
     *  In the Mesh implementation of this method, the random value is lerped
     *  in order to get the random tris. With the cd array the tris is found
     *  in O(log2(n)) steps, where n is the number of faces. Then the
     *  Triangle::getRandomPoint() function is called
     *
     *  \param[in] r A random value in the interval (0.0,1.0)
     *  \param[in] r1 A random value in the interval (0.0,1.0)
     *  \param[in] densities The array generated from the getDensitiesArray
     *  function
     *  \param[out] p The computed point in object space
     *  \param[out] n The normal of the computed point
     */
    void sample_point(float r, float r1, const float* densities, Point3* p,
                        Normal* n)const;
    
    /** \brief Add a material to the set of materials used in this Mesh
     *
     *  More than the usage of this function it is important to understand the
     *  reason of it.
     *  - Storing the material name for every triangle inside the Mesh and then
     *    perform a lookup in the hash map at each intersection would be too
     *    much computationally and memory expensive
     *  - Storing directly a pointer to the material inside each triangle would
     *    be too much computationally expensive (8KB every 1K triangles in
     *    64-bit systems)
     *
     *  These problems are solved by keeping every material used in the Mesh
     *  into an array. Every triangle stores an unsigned char that acts as an
     *  offset of this array to find the corresponding material. With this
     *  method 1KB of data is used every 1K triangles + the actual size of the
     *  pointers (from 16 byte for a single material mesh up to 2K for mesh with
     *  255 materials)
     *
     *  This method is used to set the material at the ith index to be
     *  referenced by the triangles contained into the mesh. The 0th material
     *  should be the Default material since every Triangle without a material
     *  is assigned the index 0.
     *
     *  \warning This method does not allocate a bigger array if the index is
     *  outside the referenced area. The parser should take care of not writing
     *  outside the array bounds
     *
     *  \param[in] index The index at which the material is assigned. Index 0
     *  represents the default material
     *  \param[in] material A pointer to the material assigned to the given
     *  index
     */
    void set_bsdf(unsigned char index, const Bsdf* material);

private:

    //array of triangles
    Triangle* tris;
    
    //materials used in the Mesh (since storing a pointer for
    //each face would be way too memory expensive)
    const Bsdf** materials;

    //precomputed AABB
    AABB aabb;

    //number of triangles
    unsigned int count;

    //number of triangles allocated
    unsigned int alloc;

    //BVH for faster intersections
    Bvh bvh;
};

#endif
