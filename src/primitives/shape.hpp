//Created,  25 Feb 2016
//Last Edit 10 Jun 2017

/**
 *  \file shape.hpp
 *  \brief     Shape abstract class definition
 *  \details   The superclass from which every shape inherit
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      10 Jun 2017
 *  \copyright GNU GPLv3
 */


#ifndef __SHAPE_HPP_
#define __SHAPE_HPP_

#include "ray.hpp"
#include "matrix4.hpp"
#include "AABB.hpp"

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
    ~Shape();
    
    /** \brief The transformation matrix that should be used on the vertices
     *
     *  A pointer to the transformation matrix used to scale, translate and
     *  rotate and project the shape. Since a shape is in object-space this
     *  matrix MUST be used before rendering the actual shape
     */
    Matrix4* transformMatrix;
    
    /** \brief Return the ID of this shape
     *  \return A unsigned int representing the ID of this shape
     */
    unsigned int getID()const;
    
    /** \brief Intersection of a Ray and this shape
     *
     *  In its implementations, this method should try to intersect a ray passed
     *  as a parameter with the shape, returning true or false if the
     *  intersection happened in the range defined by the Ray#minext and
     *  Ray#maxext. If the intersection happened, the variables \p distance and
     *  \p h should be set based on the result.
     *
     *  \note If there is an intersection, but it is outside the range defined
     *  by Ray#minext and Ray#maxext, this method should return false, and
     *  it should avoid setting the \p distance and \p error parameters
     *
     *  \param[in] r A pointer to the ray used to perform the intersection
     *  \param[out] distance The distance of the point of intersection
     *  \param[out] h Details on the hit point on the surface
     */
    virtual bool intersect(const Ray* r,float* distance, HitPoint* h)const=0;
    
    /** \brief Recalculate the AABB
     *
     *  In its implementations, this method should return an AABB that can fit
     *  well on this shape.
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
     *  \return an AABB representing the world space bounding box
     */
    virtual AABB computeWorldAABB() const = 0;
    
    /** \brief Return the surface of the shape
     *
     *  In its implementations, this method should compute the surface area of
     *  the shape
     *
     *  \return A float representing the area of the shape in world-space units
     */
    virtual float surface()const = 0;
    
    /** \brief Convert the shape to world-space
     *
     *  In its implementations, this method should replace the object-space
     *  definition of the object with its world-space
     *
     *  \sa world2obj()
     */
    virtual void obj2world() = 0;
    
    /** \brief Convert the shape to object-space
     *
     *  In its implementations, this method should replace the world-space
     *  definition of the object with its object-space
     *
     *  \sa obj2world()
     */
    virtual void world2obj() = 0;
    
    
private:
    //id of the shape
    const unsigned int id;
};


///Struct containing the data of the intersection between a Ray and a Shape
struct HitPoint
{
    ///The hit point
    Point3 h;

    ///The normal of the hit point
    Normal n;

    ///u coordinate for texture
    float u;

    ///v coordinate for texture
    float v;

    ///The hit shape
    const Shape* sp;
};

#endif
