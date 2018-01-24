//Created,  24 Feb 2016
//Last Edit  7 Dec 2017

/**
 *  \file point3.hpp
 *  \brief     Point3 class definition and its inline
 *             functions
 *  \details   Definition and implementation of a point in a three dimensional
 *             and its interaction with the Vec3 class
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      7 Dec 2017
 *  \copyright GNU GPLv3
 */


#ifndef __POINT_HPP__
#define __POINT_HPP__

#include "utility/console.hpp"
#include "utility/utility.hpp"
#include "geometry/vec3.hpp"
#include <cmath>

/**
 *  \class Point3 point3.hpp "geometry/point3.hpp"
 *  \brief Three points representing a location in space
 *
 *  Point3 class represents a zero dimensional location in a three dimensional
 *  cartesian space. It is designed as a separate class because by representing
 *  a location, and not a direction, it shows a different behaviour in some
 *  situations. Its implementation is a ripoff of the vector class, missing some
 *  methods like dot and cross. However, for the sake of simplicity, it has not
 *  been designed as an inherited class.
 *
 *  A Point3 consists of three coordinates, usually called x, y and z.
 */
class Point3
{
public:
    
    /** \brief x coordinate
     *
     *  A single precision floating point representing the x coordinate of the
     *  point
     */
    float x;
    
    /** \brief y coordinate
     *
     *  A single precision floating point representing the y coordinate of the
     *  point
     */
    float y;
    
    /** \brief z coordinate
     *
     *  A single precision floating point representing the z coordinate of the
     *  point
     */
    float z;
    
    /** \brief Default Constructor
     *  Construct a point in the Origin of the cartesian space, with
     *  coordinate (0,0,0)
     */
    Point3();
    
    ///Default destructor
    ~Point3() = default;
    
    /**  \brief Constructor, given equal coordinates
     *
     *  Construct a point in the space with the \p x coordinate equals to \p y
     *  and \p z
     *
     *  \param[in] xyz A float representing the x, y and z coordinates
     */
    Point3(float xyz);
    
    /**
     *  /brief Constructor, given x, y and z
     *
     *  Construct a point given a position in the space in form (x,y,z)
     *
     *  \param[in] x The value of the x coordinate
     *  \param[in] y The value of the y coordinate
     *  \param[in] z The value of the z coordinate
     */
    Point3(float x, float y, float z);
    
    /**  \brief Compute the distance to another point
     *
     *  Compute the euclidean distance between this point and another one
     *  passed as input. This distance is the length of the segment connecting
     *  them
     *
     *  \param[in] p A Point3 representing the point to which the
     *             distance should be calculated
     */
    float distanceTo(const Point3& p)const;
    
    /**  \brief Compute the maxium value between this point and another one
     *
     *  Substitute the maximum value in x, y and z by choosing between the value
     *  of this point and the one passed as argument
     *
     *  \param[in] p A Point3 used to compare and choose the x, y and z values
     *  \sa min(const Point3& p)
     */
    void max(const Point3& p);
    
    /**  \brief Compute the minimum value between this point and another one
     *
     *  Substitute the minimum value in x, y and z by choosing between the value
     *  of this point and the one passed as argument
     *
     *  \param[in] p A Point3 used to compare and choose the x, y and z values
     *  \sa max(const Point3& p)
     */
    void min(const Point3& p);
    
    //------ Operators ---------------------------------------------------------
    
    ///Offsets the point along a direction
    Point3 operator+ (const Vec3&  v)const;
    ///Offsets the point along a direction
    void  operator+= (const Vec3&  v);
    ///Returns the segment between two points
    Vec3  operator-  (const Point3& p)const;
    ///Offsets the point in the opposite of the given direction
    Point3 operator- (const Vec3&  v)const;
    ///Offsets the point in the opposite of the given direction
    void operator-= (const Vec3&  v);
    ///Check if two points are in the same spot
    bool operator==  (const Point3&)const;
    ///Check if two points are in different places
    bool operator!=  (const Point3&)const;
    ///Access a component of the point
    float operator[] (int)const;
    ///Access a component of the point, non-const version
    float& operator[](int);
    
    /* Useless operations.
     i.e.: Cannot offset a point by a point
     But if I remove these, I will surely forgot why
     //Point3 operator+ (const Point3& p)const;
     //void  operator+=(const Point3&  v);
     //Point3 operator* (const float f)const;
     //void operator-=(const Point3&  p); <- super useless, point - point = vec
     */
    
    //--------------------------------------------------------------------------
    
};


//++++++++++++++++++++++++++++//INLINE FUNCTIONS//++++++++++++++++++++++++++++//

/**  \brief Compute the distance between two points
 *
 *  Compute the euclidean distance between two points, by computing the length
 *  of the segment between them
 *
 *  \param[in] p1 A Point3 representing the point from which the
 *             distance should be calculated
 *  \param[in] p2 A Point3 representing the point to which the
 *             distance should be calculated
 *  \return A float representing the distance from \p p1 to \p p2
 */
inline float distance(const Point3& p1, const Point3& p2)
{
    float x = p1.x - p2.x;
    float y = p1.y - p2.y;
    float z = p1.z - p2.z;
    
    return std::sqrt((x * x) + (y * y) + (z*z));
}

/**  \brief Compute the min value between two vectors
 *
 *  Return a new Point3 where the x, y and z coordinate are the minimum value
 *  between the first and the second point passed in input
 *
 *  \param[in] p1 A Point3 used to compare and choose the x, y and z values
 *  \param[in] p2 A Point3 used to compare and choose the x, y and z values
 *  \return A Point3 with minimized coordinates, chosen between the inputs
 *  \sa max(const Point3 p1, const Point3 p2)
 */
inline Point3 min(const Point3& p1, const Point3& p2)
{
    return
    Point3(min(p1.x,p2.x),min(p1.y,p2.y),min(p1.z,p2.z));
}

/**  \brief Compute the max value between two vectors
 *
 *  Return a new Point3 where the x, y and z coordinate are the maximum value
 *  between the first and the second point passed in input
 *
 *  \param[in] p1 A Point3 used to compare and choose the x, y and z values
 *  \param[in] p2 A Point3 used to compare and choose the x, y and z values
 *  \return A Point3 with maximized coordinates, chosen between the inputs
 *  \sa min(const Point3 p1, const Point3 p2)
 */
inline Point3 max(const Point3& p1, const Point3& p2)
{
    return
    Point3(max(p1.x,p2.x),max(p1.y,p2.y),max(p1.z,p2.z));
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

#endif
