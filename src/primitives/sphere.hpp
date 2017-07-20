//Created,  22 Mar 2016
//Last Edit 20 Jul 2017

/**
 *  \file sphere.hpp
 *  \brief     Sphere primitive definition
 *  \details   All the methods to represent a sphere in the space
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      20 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include "utility/console.hpp"
#include "utility/utility.hpp"
#include "primitives/shape.hpp"
#include "geometry/matrix4.hpp"
#include "geometry/AABB.hpp"
#include "geometry/AABB.hpp"
#include <cmath>

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
class Sphere : public Shape
{
public:
    
    /** \brief Constructor, given the radius.
     *
     *  Construct a sphere with the given radius and centered in (0,0,0)
     *
     *  \param[in] radius The radius of the sphere
     */
    Sphere(float radius);
    
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
     *  \param[out] h an HitPoint class containing information about the
     *  intersection point
     */
    bool intersect(const Ray* r,float* distance, HitPoint* h)const;
    
    /** \brief Calculate the AABB
     *
     *  This method return an AABB that can fit well on this sphere.
     *
     *  \return an AABB representing the calculated bounding box
     */
    AABB computeAABB()const;
    
    /** \brief Calculate the AABB in world space
     *
     *  This method return an AABB that can fit well on the world space sphere,
     *  without actually transforming the sphere.
     *
     *  \note Use #_LOW_LEVEL_CHECKS_ to notify when the matrix has not been
     *  set
     *
     *  \param[in] transform The transform matrix used to transform the Sphere
     *  from object space to world space
     *
     *  \return an AABB representing the world space bounding box
     */
    AABB computeWorldAABB(const Matrix4* transform)const;
    
    /** \brief Return the surface of the sphere
     *
     *  This method should compute the surface area of the sphere, useful
     *  if the sphere is a light source.
     *
     *  \return A float representing the area of the sphere in world-space units
     */
    float surface()const;

    /** \brief Returns a random point on the surface of the sphere
     *
     *  Useful for the light sources, this method returns a random point on the
     *  surface of the shape. The normal is always pointing outside the sphere
     *
     *  \param[in] r0 A random value in the interval (0.0,1.0)
     *  \param[in] r1 A random value in the interval (0.0,1.0)
     *  \param[out] p The computed point in object space
     *  \param[out] n The normal of the computed point
     */
    void getRandomPoint(float r0, float r1, Point3* p, Normal* n)const;
    
private:
    
    //radius of the sphere
    float radius;
};

#endif
