//Created,  25 Feb 2016
//Last Edit 11 Jul 2017

/**
 *  \file shape.hpp
 *  \brief     Shape abstract class definition
 *  \details   The superclass from which every shape inherit
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      11 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __SHAPE_HPP_
#define __SHAPE_HPP_

#include "geometry/ray.hpp"
#include "geometry/matrix4.hpp"
#include "geometry/AABB.hpp"

struct HitPoint;

/**
 *  \class Shape shape.hpp "primitives/shape.hpp"
 *  \brief An abstract class used as a template for every primitive
 *
 *  The Shape class contains all the methods that will be used by the various
 *  primitives. A primitive must inherit from this class and override all the
 *  functions to perform intersection, AABB computing and surface area
 *  calculation
 */
class Shape
{
public:
    
    ///Default constructor
    Shape();
    
    ///Default destructor
    virtual ~Shape() = default;
    
    /** \brief Return the ID of this shape
     *  \return A unsigned int representing the ID of this shape
     */
    unsigned int getID()const;
    
    /** \brief Intersection of a Ray and this shape
     *
     *  In its implementations, this method should try to intersect a ray passed
     *  as a parameter with the shape, returning true or false if the
     *  intersection happened in the range defined by the minimum epsilon and
     *  the current distance.
     *  If the intersection happened, the variables \p distance and \p h should
     *  be set based on the result.
     *
     *  \note If there is an intersection, but it is outside the range defined
     *  by SELF_INTERSECTION_ERROR and the current distance value, this method
     *  should returns false.
     *
     *  \param[in] r A pointer to the ray used to perform the intersection
     *  \param[out] distance The distance of the point of intersection
     *  \param[out] h Details on the hit point on the surface
     */
    virtual bool intersect(const Ray* r,float* distance, HitPoint* h)const=0;
    
    /** \brief Recalculate the AABB
     *
     *  In its implementations, this method should return an AABB that can fit
     *  well on this shape. Object space.
     *
     *  \return an AABB representing the calculated bounding box
     */
    virtual AABB computeAABB()const = 0;
    
    /** \brief Recalculate the AABB, in world space units
     *
     *  In its implementations, this method should return an AABB that can fit
     *  well on the world space representation of this shape, without
     *  transforming the shape
     *
     *  \param[in] trans The matrix4 used for the transforming the Shape from
     *  object space to world space
     *
     *  \return an AABB representing the world space bounding box
     */
    virtual AABB computeWorldAABB(const Matrix4* trans) const = 0;
    
    /** \brief Return the surface of the shape
     *
     *  In its implementations, this method should compute the surface area of
     *  the shape
     *
     *  \return A float representing the area of the shape in world-space units
     */
    virtual float surface()const = 0;

    /** \brief Returns a random point on the surface of the shape
     *
     *  Useful for the light sources, this method returns a random point on the
     *  surface of the shape. Its implementation may chose a point that is
     *  actually facing the viewer, in order to reduce variance
     *
     *  \param[in] r A random value in the interval (0.0,1.0)
     *  \param[in] r1 A random value in the interval (0.0,1.0)
     *  \param[out] p The computed point
     *  \param[out] n The normal of the computed point
     */
    virtual void getRandomPoint(float r, float r1, Point3* p, Normal* n)const=0;
    
    
private:
    //id of the shape
    const unsigned int id;
};

//this will be defined in another file, but I need a pointer to it in HitPoint
//but HitPoint is required by Shape::intersect
class Asset;

///Struct containing the data of the intersection between a Ray and a Shape
struct HitPoint
{
    ///The hit point
    Point3 h;

    ///The normal of the hit point
    Normal n;

    ///Right direction, perpendicular to the normal
    Vec3 right;

    ///Cross between normal and right
    Vec3 cross;

    ///u coordinate for texture
    //float u;

    ///v coordinate for texture
    //float v;

    ///Hit asset
    const Asset* hit;
};

#endif
