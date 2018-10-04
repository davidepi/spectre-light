//Created,   8 Mar 2016
//Last Edit  3 Apr 2018

/**
 *  \file utility.hpp
 *  \brief Utility functions, such as swaps, logs, etc...
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date  3 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#include "settings.h" //ONE_PI
#include "utility/console.hpp"
#include "localization.h"
#include <cstdio> //sprintf
#include <climits>
#include <cmath>
#include <cfloat>
#include <cstdlib> //EXIT_FAILURE
#include <cstring> //strcpy

///Maximum amount of error that can be found in a float comparison
#define EPSILON 1E-5f

///Maximum amount of writable data for the format_seconds function
#define MAX_TIME_FORMAT_LENGTH 17

/** \brief Convert from seconds to a better readable time format
 *
 *  Given a sequence of seconds as input, in the output there will be a string
 *  with the number of days, hours, minutes, and seconds
 *
 *  \note This will write up to 16 characters, so out must be at least 17 bytes
 *  long
 *
 *  \param[in] secs The number of seconds to format
 *  \param[out] out The string where the output will be written
 */
void format_seconds(unsigned int secs, char* out);

/** \brief Swaps two float variables
 *
 *  Given two pointers to float variables, after calling this function their
 *  values will be swapped
 *
 *  \param[in,out] f1 A pointer to the first float
 *  \param[in,out] f2 A pointer to the second float
 */
inline void swap(float* f1, float* f2)
{
    float tmp;
    tmp = *f1;
    *f1 = *f2;
    *f2 = tmp;
}

/** \brief Swaps two 8-bit variables
 *
 *  Given two pointers to 8-bit integer variables, after calling this function
 *  their values will be swapped.
 *
 *  \param[in,out] u1 A pointer to the first value
 *  \param[in,out] u2 A pointer to the second value
 */
inline void swap(uint8_t* u1, uint8_t* u2)
{
    uint8_t tmp;
    tmp = *u1;
    *u1 = *u2;
    *u2 = tmp;
}

/** \brief Convert degrees to radians (float)
 *
 *  Convert a value representing an angle measured in sexagesimal arc degrees to
 *  a value representing an angle measured in radians
 *
 *  \param[in] deg The value to convert
 *  \return The input value in radians
 *  \sa degrees(const float rad)
 */
inline float radians(const float deg)
{
    return (ONE_PI/180.f)*deg;
}

/**
 * \brief Convert degrees to radians (double)
 *
 *  Convert a value representing an angle measured in sexagesimal arc degrees to
 *  a value representing an angle measured in radians
 *
 *  \param[in] deg The value to convert
 *  \return The input value in radians
 *  \sa degrees(const double rad)
 */
inline double radians(const double deg)
{
    return (M_PI/180)*deg;
}

/** \brief Convert radians to degrees
 *
 *  Convert a value representing an angle measured in radians to a value
 *  representing an angle measured in sexagesimal arc degrees
 *
 *  \param[in] rad The value to convert
 *  \return The input value in degrees
 *  \sa radians(const float deg)
 */
inline float degrees(const float rad)
{
    return (180.f/ONE_PI)*rad;
}

/** \brief Convert radians to degrees (double)
 *
 *  Convert a value representing an angle measured in radians to a value
 *  representing an angle measured in sexagesimal arc degrees
 *
 *  \param[in] rad The value to convert
 *  \return The input value in degrees
 *  \sa radians(const double deg)
 */
inline double degrees(const double rad)
{
    return (180/M_PI)*rad;
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
 *  \param[in] i1 An int used for the comparison
 *  \param[in] i2 An int used for the comparison
 *  \return An int containing the minimum value between \p i1 and \p i2
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
    if(value<min)
        return min;
    else if(value>max)
        return max;
    else
        return value;
}

/** \brief Perform linear interpolation
 *
 *  Perform a linear interpolation of a value between [0,1] in order to map it
 *  in an interval [min,max]
 *
 *  \param[in] value The value in the interval [0,1]
 *  \param[in] min The minimum value of the new interval
 *  \param[in] max The maximum value of the new interval
 *  \return The original value mapped in the interval [min,max]
 */
inline float lerp(const float value, const float min, const float max)
{
    return (1-value)*min+value*max;
}

/** \brief Perform the inverse of a linear interpolation
 *
 *  Perform an inverse linear interpolation of a value between [min,max] in
 *  order to map it in an interval [0,1]
 *
 *  \param[in] value The value in the interval [min,max]
 *  \param[in] min The minimum value of the interval
 *  \param[in] max The maximum value of theinterval
 *  \return The original value mapped in the interval [0,1]
 */
inline float inverse_lerp(float value, float min, float max)
{
    return (value-min)/(max-min);
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
    return std::fabs(val1-val2)<=EPSILON;
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

/** \brief Round up to the nearest multiple
 *
 *  Return the nearest multiple of the input value. Only unsigned integers.
 *
 *  \warning it is not checked neither if the multiple is 0 (division by zero)
 *  nor if the function causes an overflow
 *
 *  \param[in] num The input value
 *  \param[in] multiple The multiple that will be searched
 *  \return The nearest multiple
 */
inline unsigned int nearest_uint(unsigned int num, unsigned int multiple)
{
    int res = num+multiple/2;
    return res-res%multiple;
}

/** \brief Solve a linear equation
 *
 *  Solve a linear equation in form \f$ax+b=0\f$
 *
 *  
 *  \param[in] a The coefficient of the unknown variable
 *  \param[in] b The other constant of the equation
 *  \return The value of the unknown variable
 */
inline float equation1(const float a, const float b)
{
#ifdef DEBUG
    if(a == 0)
    {
        Console.severe(MESSAGE_LINEAR_EQUATION_IMPOSSIBLE);
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
    if(delta<=0 && delta+1e-4f>=0) //tanget but with float error
    {                            //happens in area lights
        *sol1 = -b/(a*2);
        *sol2 = *sol1;
        return true;
    }
    else if(delta>=0)
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

/** \brief Swap endianness (32-bit)
 *
 *  Convert a big endian number to a little endian one and vice-versa
 *
 *  \param[in] num The number that will be converted
 *  \return The same number but in another endianness
 */
inline uint32_t swap_endianness(uint32_t num)
{
    return ((num & 0x000000FF) << 24) | ((num & 0x0000FF00) << 8) |
           ((num & 0x00FF0000) >> 8) | ((num & 0xFF000000) >> 24);
}

/** \brief Swap endianness (16-bit)
 *
 *  Convert a big endian number to a little endian one and vice-versa
 *
 *  \param[in] num The number that will be converted
 *  \return The same number but in another endianness
 */
inline uint16_t swap_endianness(uint16_t num)
{
    return ((num & 0x00FF) << 8) | ((num & 0xFF00) >> 8);
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
