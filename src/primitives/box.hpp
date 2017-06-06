//Created,   6 May 2017
//Last Edit  6 Jun 2017

/**
 *  \file box.hpp
 *  \brief     Box primitive definition
 *  \details   All the methods to represent a box not aligned with axis
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      6 Jun 2017
 *  \copyright GNU GPLv3
 */


#ifndef __BOX_HPP__
#define __BOX_HPP__

#include <cstdio> //sprintf
#include <cstring> //strcpy,strcat
#include "utility.hpp"
#include "vec3.hpp"
#include "shape.hpp"
#include "matrix4.hpp"
#include "AABB.hpp"
#include "console.hpp"

/**
 *  \class Box box.hpp "primitives/box.hpp"
 *  \brief Implementation of a Box
 *
 *  This class contains the definition of a box, a box that is not necessarily
 *  aligned with the world axis. This class expects the bottom left corner and
 *  three Vec3 representing lenght of every edge. For this reason, a Box will be
 *  constructed as an axis aligned box, and then oriented with the transform
 *  matrix.
 *
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
     *  Then stores the transformation matrix, for later use with the
     *  Box::obj2world function.
     *
     *  \param[in] edges A vector with each component representing the length of
     *  an edge
     *  \param[in] transformation A pointer to the transformation matrix
     */
    Box(Vec3* edges, Matrix4* transformation);
    
    /** \brief Constructor, given the position, edges length and the transform
     *  matrix.
     *
     *  Construct an axis aligned box with the bottom left corner in the given
     *  point and the length of the edges as specified by the component of the
     *  vector. Then stores the transformation matrix, for later use with the
     *  Box::obj2world function.
     *
     *  \param[in] bottom_left Position of the bottom left corner of the box
     *  \param[in] edges A vector with each component representing the length of
     *  an edge
     *  \param[in] transformation A pointer to the transformation matrix
     */
    Box(Point3* bottom_left, Vec3* edges, Matrix4* transformation);
    
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
     *  \param[out] error The maximum floating point error in the computation
     */
    bool intersect(const Ray* r,float* distance,float* error)const;
    
    /** \brief Recalculate the AABB
     *
     *  This method return an AABB that can fit well on this possibly oriented 
     *  box.
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
     *  \return an AABB representing the world space bounding box
     */
    AABB computeWorldAABB()const;
    
    /** \brief Return the surface of the box
     *
     *  This method should compute the surface area of the sphere, useful
     *  if the sphere is a light source.
     *
     *  \return A float representing the area of the sphere in world-space units
     */
    float surface()const;
    
    /** \brief Convert the box to world-space
     *
     *  Modify the box corners by using the transformation matrix and convert
     *  the box from object-space to world-space
     *
     *  \note Use #_LOW_LEVEL_CHECKS_ to notify when the matrix has not been
     *  set
     *
     *  \sa world2obj()
     */
    void obj2world();
    
    /** \brief Convert the box to object-space
     *
     *  Modify the box corners by using the transformation matrix and convert
     *  the box from object-space to world-space
     *
     *  \note Use #_LOW_LEVEL_CHECKS_ to notify when the matrix has not been
     *  set
     *
     *  \sa obj2world()
     */
    void world2obj();
    
private:
    //position of the front bottom left corner
    Point3 fbl;
    
    //position of the front bottom right corner
    Point3 fbr;
    
    //position of the front top left corner
    Point3 ftl;
    
    //position of the back bottom left corner
    Point3 bbl;
};

#endif
