//Created,  24 Apr 2017
//Last Edit  4 May 2017

/**
 *  \file settings.h
 *  \brief Some global definitions
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date 4 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#define DEFAULT_BOUNCES 6
#define _LOW_LEVEL_CHECKS_
//#define _TEST_

#ifdef M_PI
#undef M_PI //define pi as a floating point
#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923f
#endif

#include "validator.h"
#endif
