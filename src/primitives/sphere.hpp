//Created,  22 Mar 2016
//Last Edit  4 May 2017

/**
 *  \file sphere.hpp
 *  \brief     Sphere primitive definition
 *  \details   All the methods to represent a sphere in the space
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      4 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include "utility.hpp"
#include "shape.hpp"
#include "matrix4.hpp"
#include "AABB.hpp"

/**
 *  \class Sphere sphere.hpp "primitives/sphere.hpp"
 *  \brief Implementation of a sphere primitive
 *
 *  This class contains the definition of a sphere, centered in (0,0,0) with
 *  a given radius. To center the sphere somewhere else, the
 *  Shape#transformMatrix matrix should be set. If the matrix contains a
 *  non-uniform scaling value, this class will rely upon the \a x value
 *
 */
class Sphere : Shape
{
public:
    
    /* \brief Constructor, given the radius.
     *
     *  Construct a sphere with the given radius and centered in (0,0,0)
     *
     *  \param[in] radius The radius of the sphere
     */
    Sphere(float radius);
    
    /* \brief Constructor, given the radius and the trasnform matrix.
     *
     *  Construct a sphere with the given radius and centered in (0,0,0)
     *  The input matrix will be used when transforming the sphere from
     *  object-space to world-space
     *
     *  \param[in] radius The radius of the sphere
     *  \param[in] transformation A pointer to the transformation matrix
     */
    Sphere(float radius, Matrix4* transformation);
    
    /** \brief Intersection of a Ray and this sphere
     *
     *  This method tries to intersect a ray passed as a parameter with the
     *  sphere, returning true or false if the intersection happened in the
     *  range defined by the Ray#minext and Ray#maxext. If the intersection
     *  happened, the variables \p distance and \p error are set based on the
     *  result.
     *
     *  \note If there is an intersection, but it is outside the range defined
     *  by Ray#minext and Ray#maxext, this method returns false. The parameter
     *  \p error is unset and \p distance may exhibit undefined behaviour
     *
     *  \param[in] r A pointer to the ray used to perform the intersection
     *  \param[out] distance The distance of the point of intersection
     *  \param[out] error The maximum floating point error in the computation
     */
    bool intersect(const Ray* r,float* distance,float* error)const;
    
    /** \brief Recalculate the AABB
     *
     *  This method replaces the current AABB of the sphere with an updated
     *  version. This procedure has to be performed after every obj2world or
     *  world2obj call.
     *
     *  \sa computeAABB()
     *  \sa obj2world()
     *  \sa world2obj()
     */
    void recomputeAABB();
    
    /** \brief Recalculate the AABB
     *
     *  This method return an AABB that can fit well on this sphere.
     *
     *  \return an AABB representing the calculated bounding box
     *
     *  \sa recomputeAABB()
     */
    AABB computeAABB()const;
    
    /** \brief Return the surface of the sphere
     *
     *  This method should compute the surface area of the sphere, useful
     *  if the sphere is a light source.
     *
     *  \return A float representing the area of the sphere in world-space units
     */
    float surface()const;
    
    /** \brief Convert the sphere to world-space
     *
     *  Modify the sphere radius and centre by using the transformation matrix
     *  and convert the sphere from object-space to world-space
     *
     *  \parblock
     *  \note If the supplied matrix contains non-uniform scaling, the \a x
     *  value will be chosen
     *  \endparblock
     *  \parblock
     *  \note Use #_LOW_LEVEL_CHECKS_ to notify when the matrix has not been
     *  set
     *  \endparblock
     *
     *  \sa world2obj()
     */
    void obj2world();
    
    /** \brief Convert the sphere to object-space
     *
     *  Modify the sphere radius and centre by using the transformation matrix
     *  and convert the sphere from object-space to world-space
     *
     *  \parblock
     *  \note If the supplied matrix contains non-uniform scaling, the \a x
     *  value will be chosen
     *  \endparblock
     *  \parblock
     *  \note Use #_LOW_LEVEL_CHECKS_ to notify when the matrix has not been
     *  set
     *  \endparblock
     *
     *  \sa obj2world()
     */
    void world2obj();
    
private:
    //centre of the sphere
    Point3 centre;
    
    //radius of the sphere
    float radius;
};

#endif
