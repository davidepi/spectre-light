//Created,  15 Apr 2018
//Last Edit 15 Apr 2018

/**
 *  \file point2.hpp
 *  \brief     Point2 class definition and its inline
 *             functions
 *  \details   Definition and implementation of point in two dimensional space
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      15 Apr 2017
 *  \copyright GNU GPLv3
 */


#ifndef __POINT2_HPP__
#define __POINT2_HPP__

#include "utility/console.hpp"
#include "utility/utility.hpp"
#include "geometry/vec3.hpp"
#include <cmath>

/**
 *  \class Point2 point2.hpp "geometry/point2.hpp"
 *  \brief Two points representing a location in space
 *
 *  Point2 class represents a zero dimensional location in a two dimensional
 *  cartesian space. It is designed as a separate class because by representing
 *  a location, and not a direction, it shows a different behaviour in some
 *  situations. Its implementation is a ripoff of the vector class, missing some
 *  methods like dot and cross. However, for the sake of simplicity, it has not
 *  been designed as an inherited class.
 *
 *  A Point2 consists of two coordinates, usually called x and y
 */
class Point2
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

    /** \brief Default Constructor
     *  Construct a point in the Origin of the cartesian space, with
     *  coordinates (0,0)
     */
    Point2();

    ///Default destructor
    ~Point2() = default;

    /**  \brief Constructor, given equal coordinates
     *
     *  Construct a point in the space with the \p x coordinate equals to \p y
     *
     *  \param[in] xy A float representing the x and y coordinates
     */
    Point2(float xy);

    /**
     *  /brief Constructor, given x and y
     *
     *  Construct a point given a position in the space in form (x,y)
     *
     *  \param[in] x The value of the x coordinate
     *  \param[in] y The value of the y coordinate
     */
    Point2(float x, float y);

    /**  \brief Compute the distance to another point
     *
     *  Compute the euclidean distance between this point and another one
     *  passed as input. This distance is the length of the segment connecting
     *  them
     *
     *  \param[in] p A Point2 representing the point to which the
     *             distance should be calculated
     */
    float distanceTo(const Point2& p)const;

    /**  \brief Compute the maxium value between this point and another one
     *
     *  Substitute the maximum value in x and y by choosing between the value
     *  of this point and the one passed as argument
     *
     *  \param[in] p A Point2 used to compare and choose the x and y values
     *  \sa min(const Point2& p)
     */
    void max(const Point2& p);

    /**  \brief Compute the minimum value between this point and another one
     *
     *  Substitute the minimum value in x and y by choosing between the value
     *  of this point and the one passed as argument
     *
     *  \param[in] p A Point2 used to compare and choose the x and y values
     *  \sa max(const Point2& p)
     */
    void min(const Point2& p);

    //------ Operators ---------------------------------------------------------

    ///Offsets the point along a direction
    Point2 operator+ (const Vec2&  v)const;
    ///Offsets the point along a direction
    void  operator+= (const Vec2&  v);
    ///Returns the segment between two points
    Vec2  operator-  (const Point2& p)const;
    ///Offsets the point in the opposite of the given direction
    Point2 operator- (const Vec2&  v)const;
    ///Offsets the point in the opposite of the given direction
    void operator-= (const Vec2&  v);
    ///Check if two points are in the same spot
    bool operator==  (const Point2&)const;
    ///Check if two points are in different places
    bool operator!=  (const Point2&)const;
    ///Access a component of the point
    float operator[] (int)const;
    ///Access a component of the point, non-const version
    float& operator[](int);

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
inline float distance(const Point2& p1, const Point2& p2)
{
    float x = p1.x - p2.x;
    float y = p1.y - p2.y;

    return std::sqrt((x * x) + (y * y));
}

/**  \brief Compute the min value between two points
 *
 *  Return a new Point2 where the x and y coordinates are the minimum value
 *  between the first and the second point passed in input
 *
 *  \param[in] p1 A Point2 used to compare and choose the x and y values
 *  \param[in] p2 A Point2 used to compare and choose the x and y values
 *  \return A Point2 with minimized coordinates, chosen between the inputs
 *  \sa max(const Point2 p1, const Point2 p2)
 */
inline Point2 min(const Point2& p1, const Point2& p2)
{
    return
            Point2(min(p1.x,p2.x),min(p1.y,p2.y));
}

/**  \brief Compute the max value between two points
 *
 *  Return a new Point2 where the x and y coordinate are the maximum value
 *  between the first and the second point passed in input
 *
 *  \param[in] p1 A Point2 used to compare and choose the x and y values
 *  \param[in] p2 A Point2 used to compare and choose the x and y values
 *  \return A Point2 with maximized coordinates, chosen between the inputs
 *  \sa min(const Point2 p1, const Point2 p2)
 */
inline Point2 max(const Point2& p1, const Point2& p2)
{
    return
            Point2(max(p1.x,p2.x),max(p1.y,p2.y));
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

#endif
