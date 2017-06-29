//Created,  24 Apr 2017
//Last Edit 10 May 2017

/**
 *  \file settings.h
 *  \brief User defined global definitions
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date 10 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __SETTINGS_H__
#define __SETTINGS_H__

///The number of bounces before discarding the ray
#define DEFAULT_BOUNCES 6
///If defined performs several checks to avoid Nan values
#define _LOW_LEVEL_CHECKS_
///If defined, instead of writing errors in the console, writes them in a struct
//#define _TEST_
///The amount of floating point rounding error that can cause self-intersections
#define SELF_INTERSECT_ERROR 0.0001f

///Defines the max number of assets
#define _MAX_ASSETS_ 4096

#include "validator.h"
#endif
