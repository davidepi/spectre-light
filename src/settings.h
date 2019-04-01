//Created,  24 Apr 2017
//Last Edit  2 Apr 2018

/**
 *  \file settings.h
 *  \brief User defined global definitions
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date 2 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __SETTINGS_H__
#define __SETTINGS_H__

///The number of bounces before discarding the ray
#define DEFAULT_BOUNCES 5

///The amount of floating point rounding error that can cause self-intersections
#define SELF_INTERSECT_ERROR 1e-2f

///The amount of error to consider when comparing shadow ray distance
#define OCCLUSION_INTERSECT_ERROR 1e-3f

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

///Only for debug
//#define FORCED_SEED 1542433404

///The number pi, defined as a floating point
#define ONE_PI 3.14159265358979323846264338327950288419716939937510582097494459f

///Define the number pi as double, since M_PI is not standard
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288419716939937510582097494459
#endif

///define the inverse of the pi
#define INV_PI 0.318309886183790671537767526745028724068919291480912897495f

///define 2 * pi, used extensively in sphere computations
#define TWO_PI 6.283185307179586476925286766559005768394338798750211641949f

///define the inverse of 2 * pi
#define INV_TWOPI 0.159154943091895335768883763372514362034459645740456448747f

///define 4 * pi
#define FOUR_PI 12.56637061435917295385057353311801153678867759750042328389f

///define the inverse of 4 * pi
#define INV_FOURPI 0.079577471545947667884441881686257181017229822870228224373f

///define Planck's constant
#define PLANCK_H 6.62606957E-34f

///define Boltzmann constant
#define BOLTZMANN_K 1.38064852E-23f

//deprecated function, compatible with vs
#ifdef _MSC_VER
///Tells the compiler about a deprecated function (Visual Studio style)
#define DEPRECATED __declspec(deprecated)
#else
///Tells the compiler about a deprecated function (GCC style)
#define DEPRECATED __attribute__((deprecated))
#endif

#ifdef _MSC_VER
#if _MSC_VER >= 1700
///Checks that the return value is used
#define CHECK_RETVAL_USED _Check_return_
#else
///Checks that the return value is used
#define CHECK_RETVAL_USED
#endif
#else
///Checks that the return value is used
#define CHECK_RETVAL_USED __attribute__((warn_unused_result))
#endif

#define UNUSED(X) (void)X

#endif
