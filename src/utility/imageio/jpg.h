/*  Created,  18 Jul 2018   */
/*  Last Edit  4 Aug 2018   */

/**
 *  \file tga.h
 *  \brief Wrapper for libjpeg
 *  \details Several functions used to read and write JPG images, with the
 *  aid of libjpeg
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date  4 Aug 2018
 *  \copyright MIT
 */


#ifndef __JPG_H__
#define __JPG_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <jpeglib.h>

/**
 *  \brief Writes a jpg image
 *
 *  \param[in] name The path on disk where the image will be written.
 *  Existing files will be overwritten
 *  \param[in] width Width of the image
 *  \param[in] height Height of the image
 *  \param[in] data array of 32-bit values containing the image data in
 *  top-down left to right order. Each value contains color components in
 *  BGRA order. The alpha channel is ignored, since JPG does not support it
 *  \return 1 if the image was successfully written, 0 otherwise
 */
char jpg_write(const char* name, int width, int height, const uint32_t* data);

/**
 *  \brief Checks if a jpg image is valid
 *
 *  Checks if the header of the file correspond to an actual jpg image
 *  readable by the functions defined in this file.
 *
 *  \note Only the header is checked, so if the file is truncated in the
 *  image data, this function could return 1 and the read could fail
 *
 *  \param[in] name The path on disk where the image can be found
 *  \return 1 if the image header is a valid jpg one, 0 otherwise
 */
char jpg_valid(const char* name);

/**
 *  \brief Returns the width and height of a jpg image
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
char jpg_dimensions(const char* name, int* width, int* height);

/**
 *  \brief Reads a jpg image
 *
 *  Reads a jpg image and writes the image data on the values array in
 *  top-down left-right order. This array is expected to be already allocated
 *  with a size of width*height. Every channel is written in a uint32_t
 *  value in the order BGRA with values in the range [0-255]. The alpha value
 *  however, will always be 0xFF due to JPG restrictions.
 *
 *  \param[in] name The path on disk where the image can be found
 *  \param[out] values The array of values that will be written. This array
 *  must be already allocated, use jpg_dimensions to know the actual size of
 *  the image and to preallocate it
 *  \return 0 if the read was not successful, 1 otherwise
 */
char jpg_read(const char* name, uint32_t* values);

#endif
