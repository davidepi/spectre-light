//Created,   8 Mar 2016
//Last Edit 15 Jun 2017

/**
 *  \file utility.hpp
 *  \brief Utility functions, such as swaps, logs, etc...
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date  15 Jun 2017
 *  \copyright GNU GPLv3
 */


#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#include <cstdio>
#include <climits>
#include <cmath>
#include <cfloat>
#include <cstdlib> //EXIT_FAILURE
#include "settings.h" //M_PI
#include "console.hpp"

/**
 *  \brief Enables asserts for low level classes
 *  This flag enables checks for classes such as Vec3, Vec2, Matrix4, etc..
 *  The checks that are enabled range from warnings of non-normalized vector
 *  to critical errors like divisions by zero or null-pointers dereferencing
 */

/** \brief Swaps two float variables
 *
 *  Given two pointers to float variables, after calling this function their
 *  values will be swapped
 *
 *  \param[in,out] f1 A pointer to the first float
 *  \param[in,out] f2 A pointer to the second float
 */
inline void swap(float *f1, float *f2)
{
    float tmp;
    tmp = *f1;
    *f1 = *f2;
    *f2 = tmp;
}

/** \brief Convert degrees to radians
 *
 *  Convert a value representing an angle measured in sexagesimal arc degrees to
 *  a value representing an angle measured in radians
 *
 *  \param[in] deg The value to convert
 *  \return The input value in radians
 *  \sa toDeg(const float rad)
 */
inline float toRad(const float deg)
{
    return ((float)M_PI/180.f) * deg;
}

/** \brief Convert radians to degrees
 *
 *  Convert a value representing an angle measured in radians to a value
 *  representing an angle measured in sexagesimal arc degrees
 *
 *  \param[in] rad The value to convert
 *  \return The input value in degrees
 *  \sa toRad(const float deg)
 */
inline float toDeg(const float rad)
{
    return (180.f/(float)M_PI) * rad;
}

/**
 *  \brief Compute the minimum value between two floats
 *  Return a float containing the minimum of the two input values
 *
 *  \param[in] f1 A float used for the comparison
 *  \param[in] f2 A float used for the comparison
 *  \return A float containing the minimum value between \p f1 and \p f2
 *  \sa max(const float f1, const float f2)
 */
inline float min(const float f1, const float f2)
{
    return f1<f2?f1:f2;
}

/**
 *  \brief Compute the maximum value between two floats
 *  Return a float containing the maximum of the two input values
 *
 *  \param[in] f1 A float used for the comparison
 *  \param[in] f2 A float used for the comparison
 *  \return A float containing the maximum value between \p f1 and \p f2
 *  \sa min(const float f1, const float f2)
 */
inline float max(const float f1, const float f2)
{
    return f1>f2?f1:f2;
}

/**
 *  \brief Compute the minimum value between two integers
 *  Return An int containing the minimum of the two input values
 *
 *  \param[in] i1 A float used for the comparison
 *  \param[in] i2 A float used for the comparison
 *  \return A float containing the minimum value between \p f1 and \p f2
 *  \sa max(const int i1, const int i2)
 */
inline int min(const int i1, const int i2)
{
    return i1<i2?i1:i2;
}

/**
 *  \brief Compute the maximum value between two integers
 *  Return An int containing the maximum of the two input values
 *
 *  \param[in] i1 An int used for the comparison
 *  \param[in] i2 An int used for the comparison
 *  \return An int containing the maximum value between \p i1 and \p i2
 *  \sa min(const int i1, const int i2)
 */
inline int max(const int i1, const int i2)
{
    return i1>i2?i1:i2;
}

/**
 *  \brief Clamp the input float by restricting it between two boundaries
 *  Restrict the value of the input float in an interval defined by \p min as
 *  the minimum value and \p max as the maximum one
 *
 *  \param[in] value The float that will be clamped
 *  \param[in] min A float representing the minimum extent of the interval
 *  \param[in] max A float representing the maximum extent of the interval
 *  \return The clamped float
 */
inline float clamp(const float value, const float min, const float max)
{
    if(value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

/**
 *  \brief Check if two floats are the same value
 *
 *  Compare two floats and check if they are equal with the precision specified
 *  by the host machine
 *
 *  \param[in] val1 A float used for the comparison
 *  \param[in] val2 A float used for the comparison
 *  \return A bool set to true if the two values are equal, false otherwise
 */
inline bool flt_equal(const float val1, const float val2)
{
    return std::fabs(val1-val2) <= FLT_EPSILON;
}

/** \brief Determine the sign of the given number
 *
 *  Determine the sign of the given number and return 1 if positive and -1 if
 *  negative. If the number is 0, 1 is returned
 *
 *  \param[in] a The number for which is required to determine the sign
 *  \return 1 if poisitive, -1 if negative
 */
inline int sign(float a)
{
    return (a>=0)?1:-1;
}

/** \brief Solve a linear equation
 *
 *  Solve a linear equation in form \f$ax+b=0\f$
 *
 *  \note use #_LOW_LEVEL_CHECKS_ to check if \p a is zero
 *  
 *  \param[in] a The coefficient of the unknown variable
 *  \param[in] b The other constant of the equation
 *  \return The value of the unknown variable
 */
inline float equation1(const float a, const float b)
{
#ifdef _LOW_LEVEL_CHECKS_
    if(a==0)
    {
        Console.severe("Trying to solve the linear equation ax+b=0 with a=0");
        return b;
    }
#endif
    return -b/a;
}

/** \brief Solve a quadratic equation
 *
 *  Solve a quadratic equation in form \f$ax^2+bx+c=0\f$
 *
 *  \param[in] a The coefficient of the unknown squared variable
 *  \param[in] b The coefficient of the unknown variable
 *  \param[in] c The other constant of the equation
 *  \param[out] sol1 The first solution of the equation
 *  \param[out] sol2 The second solution of the equation
 *  \return false if the equation has no solution, true otherwise
 */
inline bool equation2(const float a, const float b, const float c,
                      float* sol1, float* sol2)
{
    float delta = b*b-4.0f*a*c;
    if(delta>=0)//TODO: even with an added epsilon this has some problems if = 0
    {
        float q;
        if(b<0)
            q = -0.5f*(b-sqrtf(delta));
        else
            q = -0.5f*(b+sqrtf(delta));
        *sol1 = q/a;
        *sol2 = c/q;
        return true;
    }
    else
        return false;
}

//define some structures useful to check if the program fired any kind of errors
#ifdef _TEST_
#define LOG_INDEX 0
#define NOTICE_INDEX 1
#define WARNING_INDEX 2
#define ERROR_INDEX 3
#define CRITICAL_INDEX 4
extern int Errors_count[5];
#endif

#endif
