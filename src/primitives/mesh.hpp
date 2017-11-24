//Created,   6 Aug 2017
//Last Edit 24 Nov 2017

/**
 *  \file triangle.hpp
 *  \brief     Triangle primitive definition
 *  \details   All the methods to represent a triangle in the space
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date     24 Nov 2017
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


/**
 *  \class Mesh mesh.hpp "primitives/mesh.hpp"
 *  \brief Implementation of a collection of triangles
 *
 *  This class contains the definition of several triangles. These triangles
 *  are grouped together in order to form a single shape. For computational
 *  efficiency, this class caches the results of several functions, and
 *  implements a partitioning intersection routine.
 *
 *  In order to create a Mesh it is necessary to give the number of triangles
 *  as a parameter to the constructor. Then call the Mesh::addTriangle function
 *  for every triangle and in the end the Mesh::finalize function
 */
class Mesh : public Shape
{
public:

    /** \brief Default constructor
     *
     *  \param[in] size The number of triangles of the mesh
     */
    Mesh(unsigned int size);

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
     *  \sa addTriangle(const Point3* a, const Point3* b, const Point3* c,
     *               const Normal* n);
     */
    void addTriangle(const Vertex* a, const Vertex* b, const Vertex* c);

    /** \brief Add a triangle to this Mesh
     *
     *  Add a triangle to this mesh, with the same normal per vertex
     *  The triangles can be added also directly in world-space.
     *
     *  \param[in] a The first vertex position in the space
     *  \param[in] b The second vertex position in the space
     *  \param[in] c The third vertex position in the space
     *  \param[in] n The normal for the three vertices
     *  \sa addTriangle(const Vertex* a, const Vertex* b, const Vertex* c);
     */
    void addTriangle(const Point3* a, const Point3* b, const Point3* c,
                     const Normal* n);

    /** \brief Finalize the mesh
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
    AABB computeAABB()const;

    /** \brief Calculate the AABB in world space
     *
     *  This method returns an AABB that can fit well on the world space
     *  mesh, without actually transforming it. This AABB is precomputed in the
     *  Mesh::finalize method
     *
     *  \note Use #_LOW_LEVEL_CHECKS_ to notify when the matrix has not been
     *  set
     *
     *  \param[in] trans The transform matrix used to transform the mesh
     *  from object space to world space
     *
     *  \return an AABB representing the world space bounding box
     */
    AABB computeWorldAABB(const Matrix4* trans)const;

    /** \brief Returns the surface of the triangle
     *
     *  This method computes the surface area of the mesh, useful if it is a
     *  light source. This value is precomputed int the Mesh::finalize method
     *
     *  \return A float representing the area of the mesh in world-space
     *  units
     */
    float surface()const;
    
    /** \brief Return the number of face of the mesh
     *
     *  This function returns the number of tris composing the mesh
     *
     *  \return The number of faces in a Mesh
     */
    int getNumberOfFaces()const;
    
    /** \brief Populate the Cdf array
     *
     *  This function populates the Cdf array of the class. For each
     *  triangle, ordered, the area of the current triangle is calculated and
     *  added to the previous result. With this array it is possible to random
     *  sample a mesh with differently sized triangles.
     *  For more info checks the Mesh::getRandomPoint method.
     *
     *  The cdf array is not automatically populated because it is needed only
     *  in area lights.
     */
    void calculateCdf();

    /** \brief Returns a random point on the surface of the mesh
     *
     *  Useful for the light sources, this method returns a random point on the
     *  surface of the mesh.
     *  In the Mesh implementation of this method, the random value is lerped
     *  in order to get the random tris. With the cdf array the tris is found
     *  in O(log2(n)) steps, where n is the number of faces. Then the
     *  Triangle::getRandomPoint() function is called
     *
     *  \param[in] r A random value in the interval (0.0,1.0)
     *  \param[in] r1 A random value in the interval (0.0,1.0)
     *  \param[out] p The computed point in object space
     *  \param[out] n The normal of the computed point
     */
    void getRandomPoint(float r, float r1, Point3* p, Normal* n)const;

private:
    
    //array of tris densities. First element is the area of tris[0],
    //second element is the area of tris[0] + the area of tris[1],
    //third one is tris[0]+tris[1]+tris[2] and so on and so forth
    float* cdf;
    
    //array of triangles
    Triangle* tris;

    //precomputed AABB
    AABB aabb;

    //number of triangles
    unsigned int count;

    //number of triangles allocated
    unsigned int alloc;

    //precomputed surface of the mesh
    float area;

    //BVH for faster intersections
    Bvh bvh;
};

#endif
