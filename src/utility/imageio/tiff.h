/*  Created,  21 Jul 2018   */
/*  Last Edit 21 Jul 2018   */

/**
 *  \file tiff.h
 *  \brief Wrapper for libtiff
 *  \details Several functions used to read and write tiff images, with the
 *  aid of libtiff
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date 21 Jul 2018
 *  \copyright MIT
 */


#ifndef __TIFF_H__
#define __TIFF_H__

#include <stdint.h>
#include <memory.h>
#include <tiffio.h>

/**
 *  \brief Writes a tiff image
 *
 *   Writes a tiff image with 24 bits per pixel, default compression and no
 *   alpha channels
 *
 *  \param[in] name The path on disk where the image will be written.
 *  Existing files will be overwritten
 *  \param[in] width Width of the image
 *  \param[in] height Height of the image
 *  \param[in] data array of 8-bit values containing the image data in
 *  top-down left to right order. The values are in order RGBRGB...
 *  \return 1 if the image was successfully written, 0 otherwise
 */
char tiff_write(const char* name, int width, int height, const uint8_t* data);

/**
 *  \brief Checks if a tiff image is valid
 *
 *  Checks if the header of the file correspond to an actual tiff image
 *  readable by the functions defined in this file.
 *
 *  \note Only the header is checked, so if the file is truncated in the
 *  image data, this function could return 1 and the read could fail
 *
 *  \param[in] name The path on disk where the image can be found
 *  \return 1 if the image header is a valid tiff one, 0 otherwise
 */
char tiff_valid(const char* name);

/**
 *  \brief Returns the width and height of a tiff image
 *
 *  Checks the header of an image and saves the image width and height in
 *  the pointer passed as input. If the image is not readable or the header
 *  not compatible 0 is returned.
 *
 *  \param[in] name The path on disk where the image can be found
 *  \param[out] width The width of the image
 *  \param[out] height The height of the image
 *  \return 1 if the width and height was successfully read, 0 otherwise
 */
char tiff_dimensions(const char* name, int* width, int* height);

/**
 *  \brief Reads a tiff image
 *
 *  Reads a tiff image and writes the image data on the values array in
 *  top-down left-right order. This array is expected to be already allocated
 *  with a size of width*height*3. Every channel is written as a single uint8_t
 *  value in the order RGBRGB... with values in the range [0-255].
 *  If the tiff image contains an alpha channel, it will be written in the
 *  alpha array of size width*height. Also this array is expected to be
 *  already allocated and written values will be in the [0-255] range.
 *
 *  \param[in] name The path on disk where the image can be found
 *  \param[out] values The array of values that will be written. This array
 *  must be already allocated, use tiff_dimensions to know the actual size of
 *  the image and to preallocate it
 *  \param[out] alpha The array of alpha values. Also this array is expected
 *  to be already allocated
 *  \return 0 if the read was not successful. Otherwise 1 if the image was
 *  without alpha channel and 2 if the image had one
 */
char tiff_read(const char* name, uint8_t* values, uint8_t* alpha);

#endif
