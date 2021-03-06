//Created,  25 Feb 2016
//Last Edit  8 Dec 2017

/**
 *  \file aabb.hpp
 *  \brief     AABB class definition and its inline functions
 *  \details   An Axis Aligned Bounding Box, used to enclose some points
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      8 Dec 2017
 *  \copyright GNU GPLv3
 */


#ifndef __AABBOX_HPP__
#define __AABBOX_HPP__

#include "geometry/point3.hpp"
#include "geometry/ray.hpp"

/**
 * \class AABB AABB.hpp "geometry/AABB.hpp"
 * \brief An axis aligned bounding box
 *
 *  This class represents a bounding volume, a volume that contains a specific
 *  set of objects, in this case points belonging to the Point3 class.
 *  This bounding volume is a Box, as the name implies, and it's aligned with
 *  the axis of scene.
 *
 *  This bounding box is defined by two points defined as private variables:
 *  the point on the front bottom left of the box and the one on the back top
 *  right.
 */
class AABB
{
public:

    ///brief The front bottom left and back top right corner of the box
    Point3 bounds[2];

    /** \brief Default Constructor
     *
     *  Construct a bounding box with the bottom left pointing to Infinity
     *  and the top right pointing to &minus Infinity. This Default bounding
     *  box is degenerated thus it works exactly as an empty box
     */
    AABB();

    /** \brief Constructor, given a Point
     *
     *  Construct a bounding box surrounding exactly one point
     *
     *  \param[in] p The only point that will be surrounded by the bounding box
     */
    AABB(const Point3& p);

    /** \brief Constructor, given bottom left and top right points
     *
     *  Construct a bounding box given, in order the bottom left and the top
     *  right points
     *
     * \warning It is not checked which one of the two points is the maximum or
     *  the minimum. Be sure to pass them in the correct order
     *
     *  \param[in] min A pointer to the point representing the bottom left
     *                 corner of the box
     *  \param[in] max A pointer to the point representing the top right corner
     *                 of the box
     */
    AABB(const Point3* min, const Point3* max);

    /** \brief Constructor, given bottom left and top right points
     *
     *  Construct a bounding box given, in order the bottom left and the top
     *  right points
     *
     * \warning It is not checked which one of the two points is the maximum or
     *  the minimum. Be sure to pass them in the correct order
     *
     *  \param[in] min The point representing the bottom left
     *                 corner of the box
     *  \param[in] max The point representing the top right corner
     *                 of the box
     */
    AABB(const Point3& min, const Point3& max);

    /** \brief Expand the bounding box by a fixed amount
     *
     *  Expands the bounding box by a constant factor
     *
     *  \param[in] value The magnitude of the expansion, in world-space units
     */
    void expand(float value);

    /** \brief Expand the bounding box until the new value is enclosed
     *
     *  Expands the bounding box until it encloses the new point. If the new
     *  point is already inside the bounding box, nothing happens
     *
     *  \param[in] p1 A pointer to the point that will be enclosed
     */
    void engulf(const Point3* p1);

    /** \brief Expand the bounding box until the new value is enclosed
     *
     *  Expands the bounding box until it encloses the new point. If the new
     *  point is already inside the bounding box, nothing happens
     *
     *  \param[in] p1 The point that will be enclosed
     */
    void engulf(const Point3& p1);

    /** \brief Expand the bounding box until the new bounding box is enclosed
     *
     *  Simply performs an union of the two bounding boxes. The new bounding box
     *  will cover an area containing both the old box and the one passed as
     *  input.
     *
     *  \param[in] aabb The bounding box that will be used to perform the union
     */
    void engulf(const AABB* aabb);

    /** \brief Expand the bounding box until the new bounding box is enclosed
     *
     *  Simply performs an union of the two bounding boxes. The new bounding box
     *  will cover an area containing both the old box and the one passed as
     *  input.
     *
     *  \param[in] aabb The bounding box that will be used to perform the union
     */
    void engulf(const AABB& aabb);

    /** \brief Check if a point is inside the bounding box
     *
     *  \param[in] p A pointer to the point that will be checked
     *  \return A true value if the point is inside the bounding box
     */
    bool inside(const Point3* p) const;

    /** \brief Calculate the surface of the bounding box
     *
     *  \return A float representing the surface of the bounding box in world
     *  space units
     */
    float surface() const;

    /** \brief Calculate the volume of the bounding box
     *
     *  \return A float representing the volume of the bounding box in world
     *  space units
     */
    float volume() const;

    /** \brief Calculate the longest axis of the bouding box
     *
     *  Determine which axis belonging to the bounding box, whether \a x, \a y
     *  or \a z, is the longest.
     *
     *  \return An integer value, 0 if the \a x axis is the longest, 1 if it is
     *  the \a y axis or 2 if it is the \a z axis
     */
    char longest_axis() const;

    /** \brief Calculate the centroid of this AABB
     *
     *  Determine the centroid of this AABB.
     *
     *  \warning If an AABB extends from -&infin; to &infin; will generate a
     *  NaN as center for that component
     *
     *  \return The centroid of the AABB
     */
    Point3 center() const;

    /** \brief Intersection of a Ray and this AABB
     *
     *  This method tries to intersect a ray passed as a parameter with the
     *  AABB, returning true or false if the intersection happened. If this is
     *  true, the variables \p p1 and \p p2 are set based on the result.
     *
     *  \note If the ray intersects the box but the origin is greater than the
     *  maximum plane of the box the values p1 and p2 will be negative.
     *  In this case the result will be true but the intersection is not in the
     *  bounds of the ray
     *
     *  \param[in] r A pointer to the ray used to perform the intersection
     *  \param[out] p1 The distance of the first point of intersection. Negative
     *  if the origin is inside the box
     *  \param[out] p2 The distance of the second point of intersection.
     *  Negative if the origin is greater than the AABB, but the direction would
     *  intersect it
     *  \return true if the ray intersects the AABB, even if the origin is
     *   greater than the box
     */
    bool intersect(const Ray* r, float* p1, float* p2) const;

    /** \brief Faster Intersection of a Ray and this AABB
     *
     *  This function has the same purpose of
     *  AABB::intersect(const Ray* r, float* p1, float* p2)const, however, when
     *  used on a large amount of AABBs, this one is more efficient
     *
     *  \note If the ray intersects the box but the origin is greater than the
     *  maximum plane of the box the values p1 and p2 will be negative.
     *  In this case the result will be true but the intersection is not in the
     *  bounds of the ray
     *
     *  \param[in] r A pointer to the ray used to perform the intersection
     *  \param[in] rp A struct containing the inverse of the ray components
     *  \param[out] p1 The distance of the first point of intersection
     *  \param[out] p2 The distance of the second point of intersection
     *  \return true if the ray intersects the AABB, even if the origin is
     *   greater than the box
     */
    bool intersect(const Ray* r, const RayProperties* rp, float* p1, float* p2)
    const;

    //------ Operators ---------------------------------------------------------

    ///Return a new AABB including the old one and the input point
    AABB operator+(const Point3& p) const;

    ///Include the input point in the AABB
    void operator+=(const Point3& p);

    ///Return a new AABB including the old one and the input AABB
    AABB operator+(const AABB& aabb) const;

    ///Computes the union of the two AABBs
    void operator+=(const AABB& aabb);

    ///Determine which AABB has the lowest surface
    bool operator<(const AABB& a) const;

    ///Determine which AABB has the greatest surface
    bool operator>(const AABB& a) const;

    ///Determine if the AABB has lower or equal surface than the input one
    bool operator<=(const AABB& b) const;

    ///Determine if the AABB has higher or equal surface than the input one
    bool operator>=(const AABB& b) const;

    ///Determine if the two AABBs have the same surface
    bool operator==(const AABB& a) const;

    ///Determine if the two AABBs have different surfaces
    bool operator!=(const AABB& b) const;

    //--------------------------------------------------------------------------
};

#endif
