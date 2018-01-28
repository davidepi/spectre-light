//Created,  27 Nov 2017
//Last Edit 28 Jan 2018

/**
 *  \file imageIO.hpp
 *  \brief     Functions to save an array of pixel in different formats
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      28 Jan 2018
 *  \copyright GNU GPLv3
 */


#ifndef __IMAGEIO_HPP__
#define __IMAGEIO_HPP__

///Image read succesfully
#define IMAGE_OK 0
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
 *  This method opens a saved image in the PPM format, either binary or ASCII,
 *  and saves its width and height in the two pointers passed as input. If the
 *  image is not readable or not a PPM file, the width and height are set to the
 *  corresponding error code.
 *  The list of error codes can be found at the beginning of the imageIO.hpp
 *  file
 *
 *  \param[in] name The path of the image
 *  \param[out] width The width of the image, error code if something went wrong
 *  \param[out] height The height of the image, error code if something went
 *  wrong
 */
void dimensions_ppm(const char* name, int* width, int* height);

/** \brief Read an image in the PPM format
 *
 *  This method reads an image in the PPM format, either binary or ASCII, and
 *  saves the value of the pixels in the data array. The data array is an array
 *  of length width*height*3 and stores values as floats in the range [0.0, 1.0]
 *  The components are stored in the order R,G,B and no alpha channel is
 *  supported due to the PPM specification. If the binary PPM file has a color
 *  depth higher than 24 bits per pixel, the values are assumed to be in Big
 *  Endian orded (Most significant byte first). Upon completition the function
 *  returns IMAGE_OK if the read succeded, or a proper error code. The list of
 *  error codes can be found at the beginning of the imageIO.hpp file
 *
 *  \note Binary PPM are considerably faster to read than ASCII PPM
 *
 *  \param[in] name The path of the image
 *  \param[out] data An array of size width*height*3 that will hold the values
 *  of the image
 *  \return IMAGE_OK if everything was ok, otherwise a proper error code
 */
int read_ppm(const char* name, float* data);

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

/** \brief Determine width and height of an image in the BMP format
 *
 *  This method opens a saved image in the BMP format Version 3, and saves its
 *  width and height in the two pointers passed as input. If the image is not
 *  readable or not a BMP file, the width and height are set to the
 *  corresponding error code.
 *  The list of error codes can be found at the beginning of the imageIO.hpp
 *  file.
 *  A bmp file can store the height as a negative number in some cases. However,
 *  the returned value will always be positive.
 *
 *  \param[in] name The path of the image
 *  \param[out] width The width of the image, error code if something went wrong
 *  \param[out] height The height of the image, error code if something went
 *  wrong
 */
void dimensions_bmp(const char* name, int* width, int* height);

#endif
