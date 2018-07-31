/*  Created,  15 Jul 2018   */
/*  Last Edit 25 Jul 2018   */

/**
 *  \file tga.h
 *  \brief TARGA images functions
 *  \details Several functions used to read and write Truevision TGA images
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date 25 Jul 2018
 *  \copyright MIT
 */


#ifndef __TGA_H__
#define __TGA_H__

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "endianness.h"
#include "packed_struct.h"

/** Structure holding the tga header, must be 18 bytes */
PACKED_STRUCT(tga_header)
{
    /** Length of image ID field */
    uint8_t id_len;
    /** Whether a color map is included */
    uint8_t colourmap_type;
    /** Type of image (RLE, RGB, Colourmap, Greyscale) */
    uint8_t datatype_code;
    /** Index of the first colourmap */
    uint16_t colourmap_origin;
    /** Number of entries in the colourmap */
    uint16_t colourmap_length;
    /** Bits per pixel of the colourmap values */
    uint8_t colourmap_depth;
    /** idk */
    uint16_t x_origin;
    /** idk */
    uint16_t y_origin;
    /** Width of the image */
    uint16_t width;
    /** Height of the image */
    uint16_t height;
    /** Bits per pixel */
    uint8_t bpp;
    /** bits 0-3 alpha depth, bit 4 if true the image is top-down */
    uint8_t img_descriptor;
};
END_PACKED_STRUCT

/**
 *  \brief Writes a tga image
 *
 *   Writes a tga image. The image is uncompressed and uses 24 bits per pixel
 *   The image is written in top-down order.
 *   This method works on both Big Endian or Little Endian machines
 *
 *  \param[in] name The path on disk where the image will be written.
 *  Existing files will be overwritten
 *  \param[in] width Width of the image
 *  \param[in] height Height of the image
 *  \param[in] data array of 8-bit values containing the image data in
 *  top-down left to right order. The values are in order RGBRGB...
 *  \return 1 if the image was successfully written, 0 otherwise
 */
char tga_write(const char* name, int width, int height, const uint8_t* data);

/**
 *  \brief Checks if a tga image is valid
 *
 *  Checks if the header of the file correspond to an actual tga image
 *  readable by the functions defined in this file.
 *
 *  \note Only the header is checked, so if the file is truncated in the
 *  image data, this function could return 1 and the read could fail
 *
 *  \param[in] name The path on disk where the image can be found
 *  \return 1 if the image header is a valid tga one, 0 otherwise
 */
char tga_valid(const char* name);

/**
 *  \brief Returns the width and height of a tga image
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
char tga_dimensions(const char* name, int* width, int* height);

/**
 *  \brief Reads a tga image
 *
 *  Reads a tga image and writes the image data on the values array in
 *  top-down left-right order. This array is expected to be already allocated
 *  with a size of width*height*3. Every channel is written as a single uint8_t
 *  value in the order RGBRGB... with values in the range [0-255].
 *  If the tga image contains an alpha channel, it will be written in the
 *  alpha array of size width*height. Also this array is expected to be
 *  already allocated and written values will be in the [0-255] range.
 *  This method supports 16-bit, 24-bit and 32-bit images, both uncompressed
 *  and compressed. If a 16 bit image is found, values will still be in the
 *  [0-255] range
 *
 *  \param[in] name The path on disk where the image can be found
 *  \param[out] values The array of values that will be written. This array
 *  must be already allocated, use tga_dimensions to know the actual size of
 *  the image and to preallocate it
 *  \param[out] alpha The array of alpha values. Also this array is expected
 *  to be already allocated
 *  \return 0 if the read was not successful. Otherwise 1 if the image was
 *  without alpha channel and 2 if the image had one
 */
char tga_read(const char* name, uint8_t* values, uint8_t* alpha);

#endif
