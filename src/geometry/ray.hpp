//Created,  25 Feb 2016
//Last Edit 14 May 2018

/**
 *  \file ray.hpp
 *  \brief Ray class definition
 *  \details A class representing a Ray in a three-dimensional space
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date 14 May 2018
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
 *  Additionally a Ray contains also the origin and direction offsetted by one
 *  pixel on the x coordinate and y coordinate. These value are used for
 *  antialiasing purposes in the ImageMap and TextureImage classes
 *
 *   Ricochet is the "Time-to-Live" of the ray. At every bounce it is increased
 *   by one and when it reaches a determined amount, the ray is destroyed.
 */
class Ray
{
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
    Vec3 direction;
    
    ///Origin of the ray ofsetted by 1 pixel in the X axis
    Point3 originX;
    
    ///Direction of the ray ofsetted by 1 pixel in the X axis
    Vec3 directionX;
    
    ///Origin of the ray ofsetted by 1 pixel in the Y axis
    Point3 originY;
    
    ///Direction of the ray ofsetted by 1 pixel in the Y axis
    Vec3 directionY;

    /** \brief Maximum number of bounces for this ray
     *
     *  An unsigned char representing the maximum number of bounces for this
     *  ray. In a raytrace-based renderer, rays bounces from a surface to
     *  another until they are absorbed. However, if the scene is full of
     *  specular reflecting surfaces, a ray could bounce for a lot of time, if
     *  not forever. This value is a sort of "Time-to-live" for the ray: when it
     *  reaches a determined value, the ray must be destroyed.
     */
    unsigned char ricochet;


    /** \brief Default constructor
     *
     *  Construct a Ray with origin and direction in (0,0,0).
     */
    Ray();

    /** \brief Constructor, given origin and direction
     *
     *  Construct a Ray given a Point3 representing the starting point and a
     *  Vec3 representing the direction of the Ray.
     *
     *  \param[in] origin a Point3 representing the starting point of the Ray
     *  \param[in] direction a Vec3 representing the direction of the Ray
     */
    Ray(const Point3& origin, const Vec3& direction);

    /** \brief Constructor, given some floats
     *
     *  Construct a Ray given three floats representing the starting point
     *  and three floats representing the direction of the Ray.
     *
     *  \param[in] ox a float representing the x component of the origin point
     *  \param[in] oy a float representing the y component of the origin point
     *  \param[in] oz a float representing the z component of the origin point
     *  \param[in] dx a float representing the x component of the direction
     *  \param[in] dy a float representing the y component of the direction
     *  \param[in] dz a float representing the z component of the direction
     */
    Ray(float ox, float oy, float oz, float dx, float dy, float dz);
    
    /** \brief Constructor, given origins and directions
     *
     *  Construct a RayDiff given a Point3 representing the starting point and a
     *  Vec3 representing the direction of the Ray. These components are given
     *  also for the offsetted rays
     *
     *  \param[in] o a Point3 representing the starting point of the Ray
     *  \param[in] d a Vec3 representing the direction of the Ray
     *  \param[in] ox a Point3 representing the starting point of the Ray
     *  offsetted by 1 pixel in the x direction
     *  \param[in] dx a Vec3 representing the direction of the Ray offsetted by
     *  1 pixel in the x direction
     *  \param[in] oy a Point3 representing the starting point of the Ray
     *  offsetted by 1 pixel in the y direction
     *  \param[in] dy a Vec3 representing the direction of the Ray offsetted by
     *  1 pixel in the y direction
     */
    Ray(const Point3& o, const Vec3& d, const Point3& ox, const Vec3& dx,
        const Point3& oy, const Vec3& dy);

    /** \brief Find a point along a ray
     *
     *  Find a point at a particular position along a ray, at distance \a t from
     *  the origin of the ray
     *
     *  \param[in] t the distance of the point from the origin
     */
    Point3 apply(float t) const;
};

/**
 *  \brief Class used for multiple AABB checking
 *  
 *  The AABB intersection routine relies in several computations, which are not
 *  really time consuming on their own, but when performed on an enourmus amount
 *  of AABBs can lead to a noticeable performance hit. Since the result of these
 *  computations is needed only for AABB intersection testing and does not
 *  change for a given ray, instead of modifying the Ray class, is stored in
 *  this class.
 */
class RayProperties
{
public:

    /** \brief Constructor, given a ray
     *
     *  \param[in] v The ray for which this helper class must be created
     */
    RayProperties(const Ray& v)
    {
        RayProperties::inverseX = 1.f/v.direction.x;
        RayProperties::inverseY = 1.f/v.direction.y;
        RayProperties::inverseZ = 1.f/v.direction.z;
        RayProperties::isXInvNeg = RayProperties::inverseX<0;
        RayProperties::isYInvNeg = RayProperties::inverseY<0;
        RayProperties::isZInvNeg = RayProperties::inverseZ<0;
    }

    ///The inverse of the \a x component of the ray's direction
    float inverseX;
    ///The inverse of the \a y component of the ray's direction
    float inverseY;
    ///The inverse of the \a z component of the ray's direction
    float inverseZ;
    ///true if the sign of the inverse of the \a x component is negative
    bool isXInvNeg;
    ///true if the sign of the inverse of the \a y component is negative
    bool isYInvNeg;
    ///true if the sign of the inverse of the \a z component is negative
    bool isZInvNeg;
};

#endif
