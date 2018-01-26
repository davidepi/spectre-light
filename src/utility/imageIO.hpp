//Created,  27 Nov 2017
//Last Edit 26 Jan 2018

/**
 *  \file imageIO.hpp
 *  \brief     Functions to save an array of pixel in different formats
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      26 Jan 2018
 *  \copyright GNU GPLv3
 */


#ifndef __IMAGEIO_HPP__
#define __IMAGEIO_HPP__

///Error code used when the image is not found or not readable
#define IMAGE_NOT_READABLE -1
///Error code used when the image extension does not match the magic number
#define IMAGE_WRONG_MAGIC -2

#include "console.hpp"
#include "utility.hpp"
#include <cstdio>
#include <cstdlib>

/** \brief Save an image in the PPM format
 *
 *  Save an image in 24-bit, binary PPM format
 *
 *  \param[in] name The name of the output file
 *  \param[in] width The width of the image
 *  \param[in] height The height of the image
 *  \param[in] data An array of RGB values containing the pixel values
 */
bool save_ppm(const char* name, int width, int height, const uint8_t* data);

/** \brief Determine width and height of an image in the PPM format
 *
 *  This method opens a saved image in the PPM format, either binary of ASCII,
 *  and saves its width and height in the two pointers passed as input. If the
 *  image is not readable or not a PPM file, the width and height are set to the
 *  corresponding error code.
 *  The list of error codes can be found at the beginning of the imageIO.hpp
 *  file
 *
 *  \param[in] name The path of the image
 *  \param[out] width The width of the image
 *  \param[out] height The height of the image
 */
void dimensions_ppm(const char* name, int* width, int* height);

/** \brief Save an image in the BMP format
 *
 *  Save an image in 24-bit, binary BMP Version 3.0, Windows format, works on
 *  both big endian and little endian machines
 *
 *  \param[in] name The name of the output file
 *  \param[in] width The width of the image
 *  \param[in] height The height of the image
 *  \param[in] data An array of RGB values containing the pixel values
 */
bool save_bmp(const char* name, int width, int height, const uint8_t* data);

#endif
