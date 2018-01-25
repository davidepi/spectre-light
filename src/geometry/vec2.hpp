//Created, October 2013
//Last Edit  8 Apr 2017

/**
 *  \file vec2.hpp
 *  \brief     Vec2 class definition and its inline functions
 *  \details   A two components vector class
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      8 April 2017
 *  \copyright GNU GPLv3
 */


#ifndef __VEC2_HPP__
#define __VEC2_HPP__

#include "utility/utility.hpp"
#include "utility/console.hpp"
#include <cmath> //std::sqrt
#include <cfloat> //FLT_EPSILON
#include <cstring>
#include <cstdio> //snprintf


/**
 *  \class Vec2 vec2.hpp "geometry/vec2.hpp"
 *  \brief A vector of two components
 *
 *  Vec2 class represents a vector in 2D space and it is used to represent
 *  a point in a bidimensional cartesian space
 *
 *  A Vec2 consist of two coordinates, usually called x, and y.
 */
class Vec2
{
private:
public:

    /** \brief x component
     *
     * A single precision floating point representing the x component
     * of the vector
     */
    float x;

    /** \brief y component
     *
     * A single precision floating point representing the y component
     * of the vector
     */
    float y;


    /**
     *  \brief Default Constructor
     *
     *  Construct a vector of two elements with x = 0 e y = 0
     */
    Vec2();

    /**
     *  \brief Constructor, given x and y
     *
     *  Construct a vector of two elements with the given x and y values
     *
     *  \param[in] x A float representing the x component of the vector
     *  \param[in] y A float representing the y component of the vector
     */
    Vec2(float x, float y);

    /**
     *  \brief Constructor, given equal components
     *  Construct a vector of two elements with the same given value
     *
     *  \param[in] xy A float representing the x and y components
     */
    Vec2(float xy);

    /**
     *  \brief Constructor, given an array
     *
     *  Construct a vector of two elements given an input array
     *
     *  \param[in] xy An input array of floats, containing x in the first
     *               position (0-based) and y in the second one
     *  \warning It is not checked if \p xy is a valid pointer
     */
    Vec2(const float* xy);

    ///Default destructor
    ~Vec2() = default;

    /**
     * \brief Returns the length of the vector
     *
     * \return A float representing the length of this vector
     * \sa lengthSquared()
     */
    float length()const;

    /**
     * \brief Returns the squared length of the vector
     *
     * \return A float representing the squared length of this vector
     * \sa length()
     */
    float lengthSquared()const;

    /** \brief Normalize this vector
     *
     * \warning The input length is not checked, a 0-length vector will result
     *  in a division by zero
     */
    void normalize();

    /**  \brief Check if the current vector is normalized
     *
     *  \return A boolean value indicating whether the vector is normalized or
     *          not
     *  \sa normalize()
     */
    bool is_normalized()const;

    /**
     *  \brief Represent this vector with an array
     *
     *  Copy the components of this vector in an array of floats
     *
     *  \param[out] values An array containing the x value of the vector
     *           in the first position (0-based) and the y value in the second
     *           one
     *  \sa toString()
     */
    void toArray(float* values)const;

    /**
     *  \brief Represent this vector with a C-string
     *
     *  Allocate in the heap a C-string and write the components of the vector
     *  as a string
     *
     *  \return An heap allocated char array containing the values of the
     *           vector
     *  \note A char* is allocated on heap and MUST be deleted
     *  \sa toArray()
     */
    char* toString()const;

    /**
     *  \brief Clamp this vector by restricting it between two boundaries
     *
     *  Restrict the value of the vector in an interval defined by \p min as the
     *  minimum value and \p max as the maximum one
     *
     *  \param[in] min A Vec2 representing the minimum extent of the interval
     *  \param[in] max A Vec2 representing the maximum extent of the interval
     *  \sa saturate()
     */
    void clamp(const Vec2& min, const Vec2& max);

    /**
     *  \brief Clamp this vector in the interval [0-1]
     *  \sa clamp(const Vec2* min, const Vec2* max)
     */
    void saturate();

    /**
     *  \brief Compute the distance from another vector
     *
     *  Compute the distance between this vector and another one passed in input
     *
     *  \param[in] target A Vec2 representing the target vector from which the
     *             distance should be calculated
     *  \return A float representing the distance from the \p target vector
     */
    float distanceTo(const Vec2& target)const;

    /**
     *  \brief Compute the dot product
     *
     *  Compute the dot product of this vector and another one. The dot product
     *  is defined as the cosine of the angle between two vectors.
     *
     *  \param[in] target The target Vec2 used to compute the dot product
     *  \return A float representing the dot product
     */
    float dot(const Vec2& target)const;

    /**
     *  \brief Compute the max value between two vectors
     *
     *  Substitute the maximum value in x and y by choosing between the value of
     *  this vector and the one passed as argument
     *
     *  \param[in] vector2 A Vec2 used to compare and choose the x and y values
     *  \sa min(const Vec2 vector2)
     */
    void max(const Vec2& vector2);

    /**
     *  \brief Compute the min value between two vectors
     *
     *  Substitute the minimum value in x and y by choosing between the value of
     *  this vector and the one passed as argument
     *
     *  \param[in] vector2 A Vec2 used to compare and choose the x and y values
     *  \sa max(const Vec2 vector2)
     */
    void min(const Vec2& vector2);

    //------ Operators ---------------------------------------------------------

    ///The addition operation between two vectors
    Vec2 operator+(const Vec2&)const;
    ///The addition operation between a vector and a float
    Vec2 operator+(float)const;
    ///The addition operation between two vectors
    void operator+=(const Vec2&);
    ///The addition operation between a vector and a float
    void operator+=(float);
    ///The subtraction operation between two vectors
    Vec2 operator-(const Vec2&)const;
    ///The subtraction operation between a vector and a float
    Vec2 operator-(float)const;
    ///The subtraction operation between two vectors
    void operator-=(const Vec2&);
    ///The subtraction operation between a vector and a float
    void operator-=(float);
    ///The element-wise multiplication between two vectors
    Vec2 operator*(const Vec2&)const;
    ///The element-wise multiplication between a vector and a float
    Vec2 operator*(float)const;
    ///The element-wise multiplication between two vectors
    void operator*=(const Vec2&);
    ///The element-wise multiplication between a vector and a float
    void operator*=(float);
    ///The element-wise division between two vectors
    Vec2 operator/(const Vec2&)const;
    ///The element-wise division between a vector and a float
    Vec2 operator/(float)const;
    ///The element-wise division between two vectors
    void operator/=(const Vec2&);
    ///The element-wise division between a vector and a float
    void operator/=(float);
    ///The negative of this vector
    Vec2 operator!()const;
    ///The negative of this vector
    Vec2 operator-()const;
    ///Check if two vectors are equal
    bool operator==(const Vec2&)const;
    ///Check if two vector are different
    bool operator!=(const Vec2&)const;

    //--------------------------------------------------------------------------

};


//++++++++++++++++++++++++++++//INLINE FUNCTIONS//++++++++++++++++++++++++++++//

/**
 * \brief Returns the length of the vector
 *
 * \param[in] vector The Vec2 whose length will be computed
 * \return A float representing the length of this Vec2
 * \sa lengthSquared(const Vec2* vector)
 */
inline float length(const Vec2 vector)
{
    return std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

/**
 * \brief Returns the squared length of the vector
 *
 * \param[in] vector The Vec2 whose length will be computed
 * \return A float representing the squared length of this Vec2
 * \sa length(const Vec2* vector)
 */
inline float lengthSquared(const Vec2 vector)
{
    return (vector.x * vector.x) + (vector.y * vector.y);
}

/**
 * \brief Returns the normalized vector
 *
 * \param[in] vector The Vec2 that will be normalized
 * \return The normalized Vec2
 * \warning The input length is not checked, a 0-length vector will result in a
 *          division by zero error
 */
inline Vec2 normalize(const Vec2 vector)
{
    float len = length(vector);
#ifdef DEBUG
    if(len==0)
    {
        Console.critical("Trying to normalize a zero-length vector");
        return Vec2();
    }
#endif
    float inv = 1/len;
    return Vec2(vector.x * inv,vector.y * inv);
}

/**
 *  \brief Clamp the input vector by restricting it between two boundaries
 *
 *  Restrict the value of the vector in an interval defined by \p min as the
 *  minimum value and \p max as the maximum one
 *
 *  \param[in] vector The Vec2 that will be clamped
 *  \param[in] min A Vec2 representing the minimum extent of the interval
 *  \param[in] max A Vec2 representing the maximum extent of the interval
 *  \return The clamped Vec2
 *  \sa saturate(const Vec2 vector)
 */
inline Vec2 clamp(const Vec2 vector, const Vec2 min, const Vec2 max)
{
    float x,y;
    if (vector.x < min.x) x = min.x;
    else if (vector.x > max.x) x = max.x;
    else x = vector.x;
    if (vector.y < min.y) y = min.y;
    else if (vector.y > max.y) y = max.y;
    else y = vector.y;
    return Vec2(x,y);
}

/**
 *  \brief Clamp this vector in the interval [0-1]
 *
 *  \param[in] vector The Vec2 that will be clamped
 *  \return The clamped Vec2
 *  \sa clamp(const Vec2 vector, const Vec2 min, const Vec2 max)
 */
inline Vec2 saturate(const Vec2 vector)
{
    float x,y;
    if (vector.x < .0f) x = .0f;
    else if (vector.x > 1.0f) x = 1.0f;
    else x = vector.x;
    if (vector.y < .0f) y = .0f;
    else if (vector.y > 1.0f) y = 1.0f;
    else y = vector.y;
    return Vec2(x,y);
}

/**
 *  \brief Compute the distance from another vector
 *
 *  Compute the distance between two input vectors
 *
 *  \param[in] source A Vec2 representing the target vector from which the
 *             distance should be calculated
 *  \param[in] target A Vec2 representing the target vector to which the
 *             distance should be calculated
 *  \return A float representing the distance from the \p target vector
 */
inline float distance(const Vec2 source, const Vec2 target)
{
    float x = target.x - source.x;
    float y = target.y - source.y;

    return std::sqrt((x * x) + (y * y));
}

/**
 *  \brief Compute the dot product
 *
 *  Compute the dot product of two input vectors. The dot product
 *  is defined as the cosine of the angle between the two vectors;
 *
 *  The order of source and target doesn't change the output
 *  \param[in] source The first Vec2 used to compute the dot product
 *  \param[in] target The second Vec2 used to compute the dot product
 *  \return A float representing the dot product
 */
inline float dot(const Vec2 source, const Vec2 target)
{
    return ((source.x * target.x) + (source.y * target.y));
}

/**
 *  \brief Compute the maximum value between two vectors
 *
 *  Return a vector containing the maximum value in x and y by choosing between
 *  the value of the two input vectors
 *
 *  \param[in] vector1 A Vec2 used to compare and choose the x and y values
 *  \param[in] vector2 A Vec2 used to compare and choose the x and y values
 *  \return A Vec2 containing the maximum value of the two input vectors
 *  \sa min(const Vec2 vector1, const Vec2 vector2)
 */
inline Vec2 max(const Vec2 vector1, const Vec2 vector2)
{
    float x, y;
    if (vector1.x > vector2.x)
        x = vector1.x;
    else
        x = vector2.x;
    if (vector1.y > vector2.y)
        y = vector1.y;
    else
        y = vector2.y;

    return Vec2(x,y);
}

/**
 *  \brief Compute the minimum value between two vectors
 *
 *  Return a vector containing the minimum value in x and y by choosing between
 *  the value of the two input vectors
 *
 *  \param[in] vector1 A Vec2 used to compare and choose the x and y values
 *  \param[in] vector2 A Vec2 used to compare and choose the x and y values
 *  \return A Vec2 containing the minimum value of the two input vectors
 *  \sa max(const Vec2 vector1, const Vec2 vector2)
 */
inline Vec2 min (const Vec2 vector1, const Vec2 vector2)
{
    float x, y;
    if (vector1.x < vector2.x)
        x = vector1.x;
    else
        x = vector2.x;
    if (vector1.y < vector2.y)
        y = vector1.y;
    else
        y = vector2.y;

    return Vec2(x,y);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

#endif
