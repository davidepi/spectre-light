//Created,  28 Apr 2017
//Last Edit 16 Jul 2017

/**
 *  \file validator.h
 *  \brief Check the consistency of the settings.h file and add some definitions
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date 16 Jul 2017
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



/**
 *  \endcond
 */
