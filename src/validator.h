//Created,  28 Apr 2017
//Last Edit  5 May 2017

/**
 *  \file validator.h
 *  \brief Check the consistency of the settings.h file and add some definitions
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date 5 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__

#ifndef DEFAULT_BOUNCES
#error DEFAULT_BOUNCES must be defined in settings.h! (The default value is 6)
#endif

//for vs
#ifndef M_PI
#define M_PI 3.1415f
#endif

//deprecated function, compatible with vs
#ifdef _MSC_VER
#define DEPRECATED __declspec(deprecated)
#else
#define DEPRECATED __attribute__((deprecated))
#endif

#endif
