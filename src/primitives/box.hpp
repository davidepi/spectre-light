//Created,   6 May 2017
//Last Edit 11 Jun 2017

/**
 *  \file box.hpp
 *  \brief     Box primitive definition
 *  \details   All the methods to represent a box not aligned with axis
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      11 Jul 2017
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
 *  This class contains the definition of a box. This class expects three Vec3
 *  representing the length of every edge. The front bottom left point is
 *  always centered in (0,0,0). For this reason, a Box will be constructed as an
 *  axis aligned box, and then oriented with the transform matrix.
 */
class Box : public Shape
{
public:
    
    /** \brief Default constructor
     *
     *  Construct an Axis Aligned Box with the bottom left corner in (0,0,0)
     *  and the top right corner in (1,1,1)
     */
    Box();
    
    /** \brief Constructor, given the edges length and the transform matrix.
     *
     *  Construct an axis aligned box with the bottom left corner in (0,0,0)
     *  and the length of the edges as specified by the component of the vector.
     *
     *  \param[in] edges A vector with each component representing the length of
     *  an edge
     */
    Box(Vec3 edges);
    
    /** \brief Intersection of a Ray and this box
     *
     *  This method tries to intersect a ray passed as a parameter with the
     *  box, returning true or false if the intersection happened in the
     *  range defined by the Ray#minext and Ray#maxext. If the intersection
     *  happened, the variables \p distance and \p error are set based on the
     *  result.
     *
     *  \note If there is an intersection, but it is outside the range defined
     *  by Ray#minext and Ray#maxext, this method returns false. The parameter
     *  \p error is unset and \p distance may exhibit undefined behaviour
     *
     *  \warning For the box this method simply returns true. Intersect its AABB
     *  instead
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
     *  \note Use #_LOW_LEVEL_CHECKS_ to notify when the matrix has not been
     *  set
     *
     *  \param[in] transform The transformation matrix used to transform the box
     *  box from object space to world space
     *
     *  \return an AABB representing the world space bounding box
     */
    AABB computeWorldAABB(const Matrix4* transform)const;
    
    /** \brief Return the surface of the box
     *
     *  This method should compute the surface area of the sphere, useful
     *  if the sphere is a light source.
     *
     *  \return A float representing the area of the sphere in world-space units
     */
    float surface()const;
    
private:

    ///The length of the three edges of the box
    Vec3 edges;
};

#endif
