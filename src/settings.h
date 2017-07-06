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

///The maximum number of functions (BRDF/BTDF) that a BSDF can contain
#define _MAX_BDF_ 5

///Avoid aliasing by jittering the sampling positions
#define JITTERED_SAMPLER true

///Default extension for the box filter
#define BOX_FILTER_EXTENT 1

///Default extension for the tent filter
#define TENT_FILTER_EXTENT 2

///Default extension for the gaussian filter
#define GAUSSIAN_FILTER_EXTENT 2

///Default extension for the mitchell filter
#define MITCHELL_FILTER_EXTENT 2

///Default extension for the sinc filter
#define LANCZOS_FILTER_EXTENT 4

#include "validator.h"
#endif
