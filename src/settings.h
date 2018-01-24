//Created,  24 Apr 2017
//Last Edit 108Sep 2017

/**
 *  \file settings.h
 *  \brief User defined global definitions
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date 18 Sep 2017
 *  \copyright GNU GPLv3
 */


#ifndef __SETTINGS_H__
#define __SETTINGS_H__

///The number of bounces before discarding the ray
#define DEFAULT_BOUNCES 5

///The amount of floating point rounding error that can cause self-intersections
#define SELF_INTERSECT_ERROR 1e-5f

///The amount of error to consider when comparing shadow ray distance
#define OCCLUSION_INTERSECT_ERROR SELF_INTERSECT_ERROR

///Defines the max number of assets in the scene
#define _MAX_ASSETS_ 4096

///Defines the max number of lights in the scene
#define _MAX_LIGHTS_ 32

#ifdef TESTS
#define _MAX_TRIS_ 65 //low num because it is faster to check limit cases
#else
///Defines the max number of triangles per mesh
#define _MAX_TRIS_ 1000000u
#endif

///The maximum number of functions (BRDF/BTDF) that a BSDF can contain
#define _MAX_BDF_ 5

///The overall image will be divided in subimages of SPLIT_SIZE width and height
#define SPLIT_SIZE 32

///Avoid aliasing by jittering the sampling positions
#define JITTERED_SAMPLER true

///The number of seconds elapsed between each update of the progress bar
#define PROGRESS_BAR_UPDATE_SECONDS 1

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

///Only for debug
//#define FORCED_SEED 0

#include "validator.h"
#endif
