/*  Created,  15 Jul 2018   */
/*  Last Edit  4 Aug 2018   */

/**
 *  \file ppm.h
 *  \brief PPM images functions
 *  \details Several functions used to read and write Netpbm Bitmap images
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date 4 Aug 2018
 *  \copyright MIT
 */


#ifndef __PPM_H__
#define __PPM_H__

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "endianness.h"

/**
 *  \brief Writes an image in the PPM format
 *
 *  Writes an image in 24-bit, binary PPM format
 *
 *  \param[in] name The name of the output file
 *  \param[in] width The width of the image
 *  \param[in] height The height of the image
 *  \param[in] data An array of BGRA values of size width*height,
 *  containing the pixel values. The alpha channel of this array is ignored
 */
char ppm_write(const char* name, int width, int height, const uint32_t* data);

/**
 *  \brief Checks the header of a PPM image
 *
 *  This method reads the header of an image to determine if it is an actual
 *  PPM image  or just a renamed file.
 *
 *  \note Only the header of the image is checked, the PPM read function
 *  could fail for other reasons (Unexpected EOF for example)
 *
 *  \param[in] name The path of the image
 *  \return 1 if the header of the image is valid, 0 otherwise
 */
char ppm_valid(const char* name);

/**
 *  \brief Determines width and height of an image in the PPM format
 *
 *  This method opens a saved image in the PPM format, either binary or ASCII,
 *  and saves its width and height in the two pointers passed as input.
 *
 *  \param[in] name The path of the image
 *  \param[out] width The width of the image, error code if something went wrong
 *  \param[out] height The height of the image, error code if something went
 *  wrong
 *  \return 1 if width and height can be determined, 0 otherwise
 */
char ppm_dimensions(const char* name, int* width, int* height);

/**
 *  \brief Reads an image in the PPM format
 *
 *  This method reads an image in the PPM format, either binary or ASCII, and
 *  saves the value of the pixels in the data array. The data array is an array
 *  of length width*height and stores values as uint32_t composed of four bytes
 *  in the range [0-255]. Each byte represents a component.
 *  The components are stored in the order B,G,R,A and given the fact that no
 *  alpha channel is supported due to the PPM specification, the A value will
 *  always be 0xFF. If the binary PPM file has a color depth higher than 24 bits
 *  per pixel, the values are assumed to be in Big Endian order (Most
 *  significant byte first) and converted to an 8-bit representation.
 *
 *  \note Binary PPM are considerably faster to read than ASCII PPM
 *
 *  \param[in] name The path of the image
 *  \param[out] values An array of size width*height that will hold the values
 *  of the image
 *  \return 1 if the image was sucessfully read, 0 otherwise
 */
char ppm_read(const char* name, uint32_t* values);

#endif
