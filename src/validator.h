//Created,  28 Apr 2017
//Last Edit 18 May 2017

/**
 *  \file validator.h
 *  \brief Check the consistency of the settings.h file and add some definitions
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date 18 May 2017
 *  \copyright GNU GPLv3
 */

/** 
 *  \cond
 */

#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__

#ifndef DEFAULT_BOUNCES
#error DEFAULT_BOUNCES must be defined in settings.h! (The default value is 6)
#endif

#ifndef _MAX_ASSETS_
#define _MAX_ASSETS_ 4096
#endif
#if _MAX_ASSETS_ <= 1
#undef _MAX_ASSETS_
#define _MAX_ASSETS_ 4096
#endif

//for vs
#ifdef M_PI
#undef M_PI //redefine pi as a floating point
#endif
#ifndef M_PI
///The number π, redefined as a floating point
#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923f
#endif
///define the inverse of the pi
#define INV_PI 1.f/M_PI
///define 2 * π, used extensively in sphere computations
#define TWO_PI 6.283185307179586476925286766559005768394338798750211641949f
//define 4 * π
#define FOUR_PI 12.56637061435917295385057353311801153678867759750042328389f

//deprecated function, compatible with vs
#ifdef _MSC_VER
///Tells the compiler about a deprecated function (Visual Studio style)
#define DEPRECATED __declspec(deprecated)
#else
///Tells the compiler about a deprecated function (GCC style)
#define DEPRECATED __attribute__((deprecated))
#endif

#endif

/**
 *  \endcond
 */
