//Created,  28 Apr 2017
//Last Edit 28 Apr 2017

/**
 *  \file validator.h
 *  \brief Check the consistency of the settings.h file
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date 28 April 2017
 *  \copyright GNU GPLv3
 */


#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__

#ifndef DEFAULT_BOUNCES
#error DEFAULT_BOUNCES must be defined in settings.h! (The default value is 6)
#endif

#endif
