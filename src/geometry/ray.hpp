//Created,  25 Feb 2016
//Last Edit 29 Jul 2017

/**
 *  \file ray.hpp
 *  \brief Ray class definition
 *  \details A class representing a Ray in a three-dimensional space
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date 29 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "geometry/point3.hpp"
#include "geometry/vec3.hpp"
#include "settings.h"

/**
 *  \class Ray ray.hpp "geometry/ray.hpp"
 *  \brief A ray composed by two \a Vec3, origin and destination
 *
 *  Ray class represents a semi-infinite line. A Ray is denoted by a Point o,
 *  its origin and a Vec3 d, its direction.
 *
 *   Ricochet is the "Time-to-Live" of the ray. At every bounce it is increased
 *   by one and when it reaches a determined amount, the ray is destroyed.
 */
class Ray
{
private:
public:
    
    /** \brief origin
     *
     *  A \a Point representing the origin of the ray in the space
     */
    Point3 origin;
    
    /** \brief direction
     *
     *  A \a Vec3 representing the direction (orientation) of the ray in the
     *  space
     */
    Vec3  direction;
    
    /** \brief Maximum number of bounces for this ray
     *
     *  An unsigned char representing the maximum number of bounces for this
     *  ray. In a raytrace-based renderer, rays bounces from a surface to
     *  another until they are absorbed. However, if the scene is full of
     *  specular reflecting surfaces, a ray will bounce for a lot of time, if
     *  not forever. This value is a sort of "Time-to-live" for the ray: when it
     *  reaches a determined value, the ray must be destroyed.
     *  Despite the fact that in pathtrace-based algorithms rays are guaranteed
     *  to be eventually destroyed, due to the russian roulette, this value can
     *  be used as a minimum number of bounces before starting the russian
     *  roulette
     */
    unsigned char ricochet;
    
    
    /** \brief Default constructor
     *
     *  Construct a Ray with origin and direction in (0,0,0).
     *  Its minimum extent will be 0 and maximum extent will be infinity.
     */
    Ray();
    
    /** \brief Constructor, given origin and direction
     *
     *  Construct a Ray given a Point3 representing the starting point and a
     *  Vec3 representing the direction of the Ray.
     *  Its minimum extent will be 0 and maximum extent will be infinity.
     *
     *  \param[in] origin a Point3 representing the starting point of the Ray
     *  \param[in] direction a Vec3 representing the direction of the Ray
     */
    Ray(const Point3 origin, const Vec3 direction);
    
    /** \brief Constructor, given origin and direction
     *
     *  Construct a Ray given a Point3 representing the starting point, a
     *  Vec3 representing the direction of the Ray and a float reprenting
     *  the time-to-live of the ray
     *  Its minimum extent will be 0 and maximum extent will be infinity.
     *
     *  \param[in] origin a Point3 representing the starting point of the Ray
     *  \param[in] direction a Vec3 representing the direction of the Ray
     *  \param[in] bounces an int representing the remaining bounces of the Ray
     */
    Ray(const Point3 origin, const Vec3 direction, unsigned char bounces);
    
    /** \brief Constructor, given some floats
     *
     *  Construct a Ray given three floats representing the starting point
     *  and three floats representing the direction of the Ray.
     *  Its minimum extent will be 0 and maximum extent will be infinity.
     *
     *  \param[in] ox a float representing the x component of the origin point
     *  \param[in] oy a float representing the y component of the origin point
     *  \param[in] oz a float representing the z component of the origin point
     *  \param[in] dx a float representing the x component of the direction
     *  \param[in] dy a float representing the y component of the direction
     *  \param[in] dz a float representing the z component of the direction
     *
     *  \note Use #_LOW_LEVEL_CHECKS_ to notify when the input values are NaN or
     *        Infinity
     */
    Ray(float ox, float oy, float oz, float dx, float dy, float dz);
    
    
    /** \brief Find a point along a ray
     *
     * Find a point at a particular position along a ray, at distance \a t from
     * the origin of the ray
     *
     *  \param[in] t the distance of the point from the origin
     */
    Point3 apply(float t)const;

};

/**
 *  \brief Structure used for multiple AABB checking
 *  
 *  The AABB intersection routine relies in several computations, which are not
 *  really time consuming on their own, but when performed on an enourmus amount
 *  of AABBs can lead to a noticeable performance hit. Since the result of these
 *  computations is needed only for AABB intersection testing and does not
 *  change for a given ray, instead of modifying the Ray class, is stored in
 *  this struct.
 */
struct RayProperties
{
    ///The inverse of the \a x component of the ray
    float inverseX;
    ///The inverse of the \a y component of the ray
    float inverseY;
    ///The inverse of the \a z component of the ray
    float inverseZ;
    ///true if the sign of the inverse of the \a x component is negative
    bool isXInvNeg;
    ///true if the sign of the inverse of the \a y component is negative
    bool isYInvNeg;
    ///true if the sign of the inverse of the \a z component is negative
    bool isZInvNeg;
};
#endif
