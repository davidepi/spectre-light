//Created,   6 May 2017
//Last Edit  6 May 2017

/**
 *  \file obox.hpp
 *  \brief     Oriented Box primitive definition
 *  \details   All the methods to represent a box not aligned with axis
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      6 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __OBOX_HPP__
#define __OBOX_HPP__

#include <cstdio> //sprintf
#include <cstring> //strcpy,strcat
#include "utility.hpp"
#include "vec3.hpp"
#include "shape.hpp"
#include "matrix4.hpp"
#include "AABB.hpp"

/**
 *  \class OBox obox.hpp "primitives/sphere.hpp"
 *  \brief Implementation of an Oriented Box
 *
 *  This class contains the definition of an oriented box, a box that is not
 *  aligned with the world axis. This class expects the bottom left corner and
 *  three Vec3 representing lenght and direction of every edge
 *
 *  Alternatively, by calling the default constructor, an Axis Aligned bounding
 *  Box can be constructed and then oriented by using a transformation matrix
 */
class OBox : Shape
{
public:
    
    /* \brief Default constructor
     *
     *  Construct an Axis Aligned Box with the bottom left corner in (0,0,0)
     *  and the top right corner in (1,1,1)
     */
    OBox();
    
    /* \brief Constructor, given bottom left corner and one vector for each edge
     *
     *  Construct an oriented box with the bottom left corner in the given point
     *  and three vector representing lenght and orientation of each edge
     *
     *  \note The three vectors can be also used as a position of the,
     *  respectively, front-bottom-right corner, front-top-left corner and
     *  back-bottom-left corner
     *
     *  \warning If using #_LOW_LEVEL_CHECKS_, if the box is not consistent
     *  (i.e. bottom left corner on the right of the bottom right corner) it
     *  will be rearranged, leading to probably unwanted results
     *
     *  \param[in] blcorner The bottom left corner
     *  \param[in] xedge A vector where the \a x component is the length of the
     *  x edge, the \a y and \z components are the orientation
     *  \param[in] yedge A vector where the \a y component is the length of the
     *  y edge, the \a x and \z components are the orientation
     */
    OBox(Point3* blcorner, Vec3* xedge, Vec3* yedge, Vec3* zedge);
    
    /* \brief Constructor, given the edges length and the trasnform matrix.
     *
     *  Construct an axis aligned box with the bottom left corner in (0,0,0)
     *  and the length of the edges as specified by the component of the vector.
     *  Then stores the transformation matrix, for later use with the
     *  OBox::obj2world function.
     *
     *  \param[in] edges A vector with each component representing the length of
     *  an edge
     *  \param[in] transformation A pointer to the transformation matrix
     */
    OBox(Vec3* edges, Matrix4* transformation);
    
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
     *  \param[in] r A pointer to the ray used to perform the intersection
     *  \param[out] distance The distance of the point of intersection
     *  \param[out] error The maximum floating point error in the computation
     */
    bool intersect(const Ray* r,float* distance,float* error)const;
    
    /** \brief Recalculate the AABB
     *
     *  This method replaces the current AABB of the box with an updated
     *  version. This procedure has to be performed after every obj2world or
     *  world2obj call.
     *
     *  \note Despite the name of the function contains the word REcompute, the
     *  AABB is not implicitly calculated by whichever constructor
     *
     *  \sa computeAABB()
     *  \sa obj2world()
     *  \sa world2obj()
     */
    void recomputeAABB();
    
    /** \brief Recalculate the AABB
     *
     *  This method return an AABB that can fit well on this oriented box.
     *
     *  \return an AABB representing the calculated bounding box
     *
     *  \sa recomputeAABB()
     */
    AABB computeAABB()const;
    
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
