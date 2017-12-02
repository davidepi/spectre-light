//Created,   6 May 2017
//Last Edit 26 Nov 2017

/**
 *  \file box.hpp
 *  \brief     Box primitive definition
 *  \details   All the methods to represent a box not aligned with axis
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      26 Nov 2017
 *  \copyright GNU GPLv3
 */


#ifndef __BOX_HPP__
#define __BOX_HPP__


#include "utility/utility.hpp"
#include "geometry/vec3.hpp"
#include "primitives/shape.hpp"
#include "geometry/matrix4.hpp"
#include "geometry/AABB.hpp"
#include "utility/console.hpp"
#include <cstdio> //sprintf
#include <cstring> //strcpy,strcat

/**
 *  \class Box box.hpp "primitives/box.hpp"
 *  \brief Implementation of a Box
 *
 *  This class contains the definition of a box.The front bottom left point is
 *  always centered in (0,0,0) and the back top right point in (1,1,1).
 *  For this reason, a Box will be constructed as an axis aligned box, and then
 *  oriented with the transform matrix.
 */
class Box : public Shape
{
public:
    
    /** \brief Default constructor
     *
     *  Construct an Axis Aligned Box with the bottom left corner in (0,0,0)
     *  and the top right corner in (1,1,1)
     */
    Box() = default;
    
    /** \brief Intersection of a Ray and this box
     *
     *  This method tries to intersect a ray passed as a parameter with the
     *  box, returning true or false if the intersection happened in the
     *  range defined by the minimum epsilon and the current distance.
     *  If the intersection happened, the variables \p distance and \p h are set
     *  based on the result.
     *
     *  \note If there is an intersection, but it is outside the range defined
     *  by SELF_INTERSECTION_ERROR and the current distance value, this method
     *  returns false.
     *
     *  \param[in] r A pointer to the ray used to perform the intersection
     *  \param[out] distance The distance of the point of intersection
     *  \param[out] hp The HitPoint structure containing information about the
     *  intersection point
     */
    bool intersect(const Ray* r,float* distance, HitPoint* hp)const;
    
    /** \brief Recalculate the AABB
     *
     *  This method return an AABB that can fit well on this box. Since the box
     *  is actually an Axis Aligned Bounding Box, the AABB returned will be the
     *  box itself
     *
     *  \return an AABB representing the calculated bounding box
     */
    AABB computeAABB()const;
    
    /** \brief Calculate the AABB in world space
     *
     *  This method return an AABB that can fit well on the world space box,
     *  without actually transforming the box.
     *
     *  \param[in] transform The transformation matrix used to transform the box
     *  box from object space to world space
     *
     *  \return an AABB representing the world space bounding box
     */
    AABB computeWorldAABB(const Matrix4* transform)const;
    
    /** \brief Return the number of face of the box
     *
     *  Useful only for Mesh objects, this function returns the number of tris
     *  composing the shape. It returns 1 if the shape is a Sphere, 6 if the
     *  Shape is a Box
     *
     *  \return The number of faces in a Mesh, 1 in an sdl, 6 in a Box
     */
    int getNumberOfFaces()const;
    
    /** \brief Return the surface of the box
     *
     *  This method should compute the surface area of the box, useful
     *  if the box is a light source.
     *
     *  \return A float representing the area of the box in objects-space units
     */
    float surface()const;
    
    /** \brief Return the surface of the box accounting for the scaling factor
     *
     *  This method should compute the surface area of the box, useful
     *  if the box is a light source. Compared to the other surface() method,
     *  this one accounts also for the scaling factor of the transform matrix
     *
     *  \return A float representing the area of the box in world-space units
     */
    float surface(const Matrix4* transform)const;
    
    /** \brief Populate the array of cumulative densities
     *
     *  This function populates the densities array. Every cell represent a
     *  face in the following order: front, back, top, bottom, left, right.
     *  The densities are cumulative, the third cell for example contains the
     *  surface for the front, back and top faces. Every surface is calculated
     *  considering the world-space transformed shape
     *
     *  \param[in] transform The object to world space matrix
     *  \param[out] array The array of cumulative densities
     */
    void getDensitiesArray(const Matrix4* transform,float* array)const;
    
    /** \brief Returns a random point on the surface of the box
     *
     *  Useful for the light sources, this method returns a random point on the
     *  surface of the shape. The normal is always pointing outside the box.
     *  The cd array is required in order to weight the sample correctly with
     *  respect to non-uniform scaling
     *
     *  \param[in] r0 A random value in the interval (0.0,1.0)
     *  \param[in] r1 A random value in the interval (0.0,1.0)
     *  \param[in] densities An array of densities calculated with the
     *  getDensitiesArray method
     *  \param[out] p The computed point in object space
     *  \param[out] n The normal of the computed point
     */
    void getRandomPoint(float r0, float r1, const float* densities, Point3* p,
                        Normal* n)const;
};

#endif
