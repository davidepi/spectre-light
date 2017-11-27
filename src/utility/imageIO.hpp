//Created,  27 Nov 2017
//Last Edit 27 Nov 2017

/**
 *  \file imageIO.hpp
 *  \brief     Functions to save an array of pixel in different formats
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      27 Nov 2017
 *  \copyright GNU GPLv3
 */


#ifndef __IMAGEIO_HPP__
#define __IMAGEIO_HPP__

#include "console.hpp"
#include <cstdio>

/** \brief Save an image in the PPM format
 *
 *  Save an image in 24-bit, binary PPM format
 *
 *  \param[in] name The name of the output file
 *  \param[in] width The width of the image
 *  \param[in] height The height of the image
 *  \param[in] array An array of RGB values containing the pixel values
 */
bool savePPM(const char* name, int width, int height, const uint8_t* array);
bool saveBMP(const char* name, int width, int height, const uint8_t* array);

#endif
