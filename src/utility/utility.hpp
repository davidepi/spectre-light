//Created,   8 Mar 2016
//Last Edit 28 Apr 2017

/**
 *  \file utility.hpp
 *  \brief Utility functions, such as swaps, logs, etc...
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date 28 April 2017
 *  \copyright GNU GPLv3
 */


#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#include <cstdio>
#include <climits>
#include <cmath>
#include <cfloat>
#include <cstdlib> //EXIT_FAILURE

/**
 *  \brief Enables asserts for low level classes
 *  This flag enables checks for classes such as Vec3, Vec2, Matrix4, etc..
 *  The checks that are enabled range from warnings of non-normalized vector
 *  to critical errors like divisions by zero or null-pointers dereferencing
 */

/** \brief Log a message
 *
 *  Log a message in the console
 *
 *  \param[in] message The message to be logged
 *  \param[in] verbose The message to be logged if the program is launched in
 *             verbose mode. If this parameter is NULL the normal message will
 *             be logged.
 *
 *  \note The newline character is not needed
 *
 *  \sa log(bool condition, const char* message, const char* verbose)
 *  \sa notice  (const char* message)
 *  \sa warning (const char* message)
 *  \sa severe  (const char* message)
 *  \sa critical(const char* message)
 */
void log(const char* message, const char* verbose);

/** \brief Log a message
 *
 *  Log a message in the console with a severity of "Notice"
 *
 *  \param[in] message The message to be logged
 *
 *  \note The newline character is not needed
 *
 *  \sa notice(bool condition, const char* message)
 *  \sa log (const char* message, const char* verbose)
 *  \sa warning (const char* message)
 *  \sa severe  (const char* message)
 *  \sa critical(const char* message)
 */
void notice(const char* message);

/** \brief Log a message
 *
 *  Log a message in the console with a severity of "Warning"
 *
 *  \param[in] message The message to be logged
 *
 *  \note The newline character is not needed
 *
 *  \sa warning(bool condition, const char* message)
 *  \sa log (const char* message, const char* verbose)
 *  \sa notice (const char* message)
 *  \sa severe  (const char* message)
 *  \sa critical(const char* message)
 */
void warning(const char* message);

/** \brief Log a message
 *
 *  Log a message in the console with a severity of "Error"
 *
 *  \param[in] message The message to be logged
 *
 *  \note The newline character is not needed
 *
 *  \sa severe(bool condition, const char* message)
 *  \sa log (const char* message, const char* verbose)
 *  \sa notice (const char* message)
 *  \sa warning  (const char* message)
 *  \sa critical(const char* message)
 */
void severe(const char* message);

/** \brief Log a message and kill the program
 *
 *  Log a message in the console with a severity of "Critical", then quit the
 *  program with an exit(EXIT_FAILURE)
 *
 *  \param[in] message The message to be logged
 *
 *  \note The newline character is not needed
 *
 *  \sa critical(bool condition, const char* message)
 *  \sa log (const char* message, const char* verbose)
 *  \sa notice (const char* message)
 *  \sa warning  (const char* message)
 *  \sa severe(const char* message)
 */
void critical(const char* message);

/** \brief Log a message, after evaluating a condition
 *
 *  Evaluate a condition, and if it is true, log a message in the console
 *
 *  \param[in] condition The condition to be evaluated
 *  \param[in] message The message to be logged
 *  \param[in] verbose The message to be logged if the program is launched in
 *             verbose mode. If this parameter is NULL the normal message will
 *             be logged.
 *
 *  \note The newline character is not needed
 *
 *  \sa log(const char* message, const char* verbose)
 *  \sa notice  (bool condition, const char* message)
 *  \sa warning (bool condition, const char* message)
 *  \sa severe  (bool condition, const char* message)
 *  \sa critical(bool condition, const char* message)
 */
void log(bool condition, const char* message, const char* verbose);

/** \brief Log a message, after evaluating a condition
 *
 *  Evaluate a condition, and if it is true, log a message in the console with a
 *  severity of "Notice"
 *
 *  \param[in] condition The condition to be evaluated
 *  \param[in] message The message to be logged
 *
 *  \note The newline character is not needed
 *
 *  \sa notice(const char* message)
 *  \sa log (bool condition, const char* message, const char* verbose)
 *  \sa warning (bool condition, const char* message)
 *  \sa severe  (bool condition, const char* message)
 *  \sa critical(bool condition, const char* message)
 */
void notice(bool condition, const char* message);

/** \brief Log a message, after evaluating a condition
 *
 *  Evaluate a condition, and if it is true, log a message in the console with a
 *  severity of "Warning"
 *
 *  \param[in] condition The condition to be evaluated
 *  \param[in] message The message to be logged
 *
 *  \note The newline character is not needed
 *
 *  \sa warning(const char* message)
 *  \sa log (bool condition, const char* message, const char* verbose)
 *  \sa notice (bool condition, const char* message)
 *  \sa severe  (bool condition, const char* message)
 *  \sa critical(bool condition, const char* message)
 */
void warning (bool condition, const char* message);

/** \brief Log a message, after evaluating a condition
 *
 *  Evaluate a condition, and if it is true, log a message in the console with a
 *  severity of "Error"
 *
 *  \param[in] condition The condition to be evaluated
 *  \param[in] message The message to be logged
 *
 *  \note The newline character is not needed
 *
 *  \sa severe(const char* message)
 *  \sa log (bool condition, const char* message, const char* verbose)
 *  \sa notice (bool condition, const char* message)
 *  \sa warning  (bool condition, const char* message)
 *  \sa critical(bool condition, const char* message)
 */
void severe  (bool condition, const char* message);

/** \brief Log a message, after evaluating a condition, then kill the program
 *
 *  Evaluate a condition, and if it is true, log a message in the console with a
 *  severity of "Critical". If the condition is true, this function quits the
 *  program with an exit(EXIT_FAILURE)
 *
 *  \param[in] condition The condition to be evaluated
 *  \param[in] message The message to be logged
 *
 *  \note The newline character is not needed
 *
 *  \sa critical(const char* message)
 *  \sa log (bool condition, const char* message, const char* verbose)
 *  \sa notice (bool condition, const char* message)
 *  \sa warning  (bool condition, const char* message)
 *  \sa severe(bool condition, const char* message)
 */
void critical(bool condition, const char* message);


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
 *  \sa max(float f1, float f2)
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
 *  \sa min(float f1, float f2)
 */
inline float max(const float f1, const float f2)
{
    return f1>f2?f1:f2;
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
        severe("Trying to solve the linear equation ax+b=0 with a=0");
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
