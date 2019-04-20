//Created,  25 Feb 2016
//Last Edit 14 Apr 2019

/**
 *  \file ray.hpp
 *  \brief Ray class definition
 *  \details A class representing a Ray in a three-dimensional space
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date 14 Apr 2019
 *  \copyright GNU GPLv3
 */


#ifndef __RAY_HPP__
#define __RAY_HPP__


#include "geometry/point3.hpp"

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

    /**
     * \brief Construct a Ray by deserializing a Chunk
     * \param[in] data The chunk containing the data.
     */
    Ray(Chunk* data);

    /** \brief Find a point along a ray
     *
     *  Find a point at a particular position along a ray, at distance \a t from
     *  the origin of the ray
     *
     *  \param[in] t the distance of the point from the origin
     */
    Point3 apply(float t) const;

    /**
     * \brief Serialize this class to a Chunk
     * \param[out] data The chunk that will contain the data
     */
    void serialize(Chunk* data) const;
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
    RayProperties(const Ray& v):
            invx(1.f/v.direction.x),
            invy(1.f/v.direction.y),
            invz(1.f/v.direction.z),
            is_invx_neg(invx<0),
            is_invy_neg(invy<0),
            is_invz_neg(invz<0)
    {

    }

    ///The inverse of the \a x component of the ray's direction
    float invx;

    ///The inverse of the \a y component of the ray's direction
    float invy;

    ///The inverse of the \a z component of the ray's direction
    float invz;

    ///true if the sign of the inverse of the \a x component is negative
    bool is_invx_neg;

    ///true if the sign of the inverse of the \a y component is negative
    bool is_invy_neg;

    ///true if the sign of the inverse of the \a z component is negative
    bool is_invz_neg;
};

#endif
