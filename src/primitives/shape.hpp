//Created,  25 Feb 2016
//Last Edit  3 May 2017

/**
 *  \file shape.hpp
 *  \brief     Shape abstract class definition
 *  \details   The superclass from which every shape inherit
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      3 May 2017
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
class Shape;
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
     *  \p error should be set based on the result.
     *
     *  \note If there is an intersection, but it is outside the range defined
     *  by Ray#minext and Ray#maxext, this method should return false, and
     *  it should avoid setting the \p distance and \p error parameters
     *
     *  \param[in] r A pointer to the ray used to perform the intersection
     *  \param[out] distance The distance of the point of intersection
     *  \param[out] error The maximum floating point error in the computation
     */
    virtual bool intersect(const Ray* r,float* distance,float* error)const=0;
    
    /** \brief Recalculate the AABB
     *
     *  In its implementations, this method should replace the current AABB of
     *  the shape with an updated version. A procedure that has to be performed
     *  after moving or transforming the shape
     *
     *  \sa computeAABB()
     */
    virtual void recomputeAABB() = 0;
    
    /** \brief Recalculate the AABB
     *
     *  In its implementations, this method should return an AABB that can fit
     *  well on this shape.
     *
     *  \return an AABB representing the calculated bounding box
     *
     *  \sa recomputeAABB()
     */
    virtual AABB computeAABB()const = 0;
    
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
    
protected:
    //bounding box of the shape
    AABB aabb;
    
private:
    //id of the shape
    const unsigned int id;
};

#endif
