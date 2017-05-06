//Created,  28 Apr 2017
//Last Edit  6 May 2017

/**
 *  \file validator.h
 *  \brief Check the consistency of the settings.h file
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date 6 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__

#ifndef DEFAULT_BOUNCES
#error DEFAULT_BOUNCES must be defined in settings.h! (The default value is 6)
#endif

#ifdef M_PI
#undef M_PI //redefine pi as a floating point
#endif
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923f
#endif


#endif
