/*  Created,  16 Jul 2018   */
/*  Last Edit 18 Jul 2018   */

/**
 *  \file imageio.h
 *  \brief Wrapper for image input and output
 *  \details Wraps the content of bmp.h, ppm.h, tga.h in single read/write
 *  functions
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date 18 Jul 2018
 *  \copyright MIT
 */


#ifndef __IMAGEIO_H__
#define __IMAGEIO_H__

#include "bmp.h"
#include "ppm.h"
#include "tga.h"
#include <stdlib.h>

#ifdef JPEG_FOUND

#include "jpg.h"

#endif
#ifdef PNG_FOUND

#include "png.h"

#endif
#ifdef TIFF_FOUND

#include "tiff.h"

#endif

/**
 *  \brief Writes an image in a generic format
 *
 *  This method writes an image passed as an array of values to the disk. The
 *  ext value is used to determine the actual type of image that will be written
 *
 *  \param[in] name Path where the image will be written
 *  \param[in] ext Extension of the image, like "bmp" or "tga"
 *  \param[in] width Width of the image
 *  \param[in] height Height of the image
 *  \param[in] data Image data, as an array of size width*height*3 with
 *  uint8_t values in range [0-255] ordered top-down left-right and channels
 *  as RGBRGB...
 *  \return 1 if the image was successfully written, 0 otherwise
 */
char img_write(const char* name, const char* ext, int width, int height,
               const uint8_t* data);

/**
 *  \brief Checks if an image header is valid
 *
 *  Checks if the header of an image on disk correspond to the type of image
 *  determined by the input extension or not. This does not grant that the
 *  final image will be readable
 *
 *  \param[in] name Path of the image on disk
 *  \param[in] ext Extension of the image, like "bmp" or "tga"
 *  \return 1 if the image is valid, 0 otherwise
 */
char img_valid(const char* name, const char* ext);

/**
 *  \brief Determines an image width and height
 *
 *  This method determines an image dimensions, width and height, by opening
 *  the given path and reading the image header. The width and height are
 *  then set into the two pointer passed as input.
 *
 *  \param[in] name Path of the image on disk
 *  \param[in] ext Extension of the image, like "bmp" or "tga"
 *  \param[out] width Width of the image
 *  \param[out] height Height of the image
 *  \return 1 if the width and height could be determined, 0 otherwise
 */
char img_dimensions(const char* name, const char* ext,
                    int* width, int* height);

/**
 *  \brief Reads an image from disk
 *
 *  This method reads an image from the disk and writes the read data in the
 *  given array. If the input image has a depth higher than 8 bit per pixel
 *  it will be converted. The values array should be already allocated with a
 *  size of width*height*3. Values will be written as uint8_t in range
 *  [0-255] in top-down left-right order and channel as RGBRGB...
 *  If the image contains an alpha channel it will be written in the alpha
 *  array, provided it is not NULL. The alpha array size should be width*height
 *
 *  \param[in] name Path of the image on disk
 *  \param[in] ext Extension of the image, like "bmp" or "tga"
 *  \param[in] values Array of size width*height*3 that will contain every
 *  image value in range [0-255], top-down left-right order with channel as
 *  RGBRGB...
 *  \param[out] alpha Array of size width*height containing the alpha channel
 *  of the image, unused if the image has no alpha channel. If this is NULL
 *  and the image has an alpha channel, the channel is discarded
 *  \return 0 if the function encountered any kind of errors, 1 if the image
 *  was successfully read and didn't have an alpha channel, 2 if the image
 *  was successfully read and had an alpha channel
 */
char img_read8(const char* name, const char* ext, uint8_t* values,
               uint8_t* alpha);

/*
 Maybe this will be readded in future
 char img_read32(const char* name, const char* ext, float* values,
                uint8_t* alpha);
*/

#endif
