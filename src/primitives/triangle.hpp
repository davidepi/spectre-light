//Created,   4 Aug 2017
//Last Edit  8 Jun 2017

/**
 *  \file triangle.hpp
 *  \brief     Triangle primitive definition
 *  \details   All the methods to represent a triangle in the space
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      8 Jun 2017
 *  \copyright GNU GPLv3
 */


#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

#include "utility/console.hpp"
#include "utility/utility.hpp"
#include "primitives/shape.hpp"
#include "geometry/point3.hpp"
#include "geometry/point2.hpp"
#include "geometry/vec3.hpp"
#include "geometry/matrix4.hpp"
#include "geometry/AABB.hpp"
#include "geometry/AABB.hpp"
#include <cmath>


///Struct for representing a vertex of the triangle in the space
struct Vertex
{
    ///The 3d coordinates of the vertex
    Point3 p;

    ///The normal of the vertex
    Normal n;

    ///The texture coordinates of the vertex
    Point2 t;
};

/**
 *  \class Triangle triangle.hpp "primitives/triangle.hpp"
 *  \brief Implementation of a triangle primitive
 *
 *  This class contains the definition of a triangle. The triangle is defined
 *  as three arbitrary points in the space, where for each point it is possible
 *  to define a normal. Although intersecting in world space does not change the
 *  complexity of the intersection routine, it is done in object space in order
 *  to keep the parent mesh instanceable.
 */
class Triangle : public Shape
{
public:

    /** \brief Default constructor
     *
     *  This constructor leaves the object uninitialized, however it is needed
     *  in the Mesh class to initialize a stack-allocated array with the new
     *  operator without having the data for the triangles. The new operator
     *  is necessary, because an allocation with the malloc operator would leave
     *  the vtable pointer uninitialized
     */
    Triangle() = default;

    /** \brief Constructor, given the vertices.
     *
     *  Construct a triangle in object space with the given vertices.
     *  The material of this triangle is set as Default material
     *
     *  \param[in] v0 The first vertex of the triangle
     *  \param[in] v1 The second vertex of the triangle
     *  \param[in] v2 The third vertex of the triangle
     */
    Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);

    /** \brief Intersection of a Ray and this triangle
     *
     *  This method tries to intersect a ray passed as a parameter with the
     *  triangle, returning true or false if the intersection happened in the
     *  range defined by the minimum epsilon and the distance parameter.
     *  If the intersection happened, the variables \p distance and \p h
     *  are set based on the result.
     *
     *  \note If there is an intersection, but it is less than the
     *  SELF_INTERSECTION_ERROR constant, or greater than the current distance
     *  value, this method returns false.
     *
     *  \param[in] r A pointer to the ray used to perform the intersection
     *  \param[out] distance The distance of the point of intersection
     *  \param[out] h an HitPoint class containing information about the
     *  intersection point
     */
    bool intersect(const Ray* r, float* distance, HitPoint* h) const;

    /** \brief Calculate the AABB
     *
     *  This method returns an AABB that can fit well on this triangle.
     *
     *  \return an AABB representing the calculated bounding box
     */
    AABB compute_AABB() const;

    /** \brief Calculate the AABB in world space
     *
     *  This method returns an AABB that can fit well on the world space
     *  triangle, without actually transforming it.
     *
     *  \param[in] transform The transform matrix used to transform the triangle
     *  from object space to world space
     *
     *  \return an AABB representing the world space bounding box
     */
    AABB compute_AABB(const Matrix4* transform) const;

    /** \brief Returns the surface of the triangle
     *
     *  This method computes the surface area of the triangle, useful
     *  if it is a light source.
     *
     *  \return A float representing the area of the triangle in object-space
     *  units
     */
    float surface() const;

    /** \brief Return the surface of the triangle considering the scaling factor
     *
     *  This method should compute the surface area of the triangle, useful
     *  if the triangle is a light source. Compared to the other surface()
     *  method, this one accounts also for the scaling factor of the transform
     *  matrix
     *
     *  \param[in] transform The transform matrix
     *
     *  \return A float representing the area of the triangle in world-space
     *  units
     */
    float surface(const Matrix4* transform) const;

    /** \brief Returns a random point on the surface of the triangle
     *
     *  Useful for the light sources, this method returns a random point on the
     *  surface of the triangle.
     *
     *  \param[in] r0 A random value in the interval (0.0,1.0)
     *  \param[in] r1 A random value in the interval (0.0,1.0)
     *  \param[in] densities Unused in the triangle
     *  \param[out] p The computed point in object space
     *  \param[out] n The normal of the computed point
     */
    void sample_point(float r0, float r1, const float* densities, Point3* p,
                      Normal* n) const;

    ///First vertex of the triangle
    Vertex a;

    ///Second vertex of the triangle
    Vertex b;

    ///Third vertex of the triangle
    Vertex c;
};

#endif
