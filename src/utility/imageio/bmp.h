/*  Created,  13 Jul 2018   */
/*  Last Edit 17 Jul 2018   */

/**
 *  \file bmp.h
 *  \brief Bitmap images functions
 *  \details Several functions used to read and write Windows Bitmap images
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date 17 Jul 2018
 *  \copyright MIT
 */


#ifndef __BMP_H__
#define __BMP_H__

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "endianness.h"
#include "packed_struct.h"

/** Structure holding the bmp header. Must be 14 bytes */
PACKED_STRUCT(bmp_header)
{
    /** Magic number of the bmp image. Must be 0x4D42 */
    uint16_t signature;
    /** Total size of the file, including headers */
    uint32_t file_size;
    /** Reserved */
    uint16_t reserved1;
    /** Reserved */
    uint16_t reserved2;
    /** Offset from the beginning of the image to the image data */
    uint32_t data_offset;
};

/** Structure holding the bmp V3 header (BITMAPINFOHEADER). Must be 40 bytes */
PACKED_STRUCT(bmp_dib_v3)
{
    /** Size of the header. Must be 40 bytes */
    uint32_t header_size;
    /** Image width */
    int32_t width;
    /** Image height. Positive for bottom-up row order, negative for top-down */
    int32_t height;
    /** The number of color_planes. Must be 1 */
    uint16_t color_planes;
    /** Number of bits per pixel */
    uint16_t bpp;
    /** Compression method used. Only 0 (uncompressed) is supported */
    uint32_t compression;
    /** Size of the raw data. Note that this value could be also 0 */
    uint32_t raw_size;
    /** Horizontal resolution of the image in pixels per meter */
    int32_t resolution_w;
    /** Vertical resolution of the image in pixels per meter */
    int32_t resolution_h;
    /** Number of colors in the palette. Only 0 (no palette) is supported */
    uint32_t palette_no;
    /** Number of important colors, ignored by this implementation */
    uint32_t important_colors_no;
};

/**
 *  \brief Writes a BMP image
 *
 *   Writes a BMP V3 image. The image is uncompressed and uses 24 bits per pixel
 *   The image is written in top-down order, ignoring the sign of the input
 *   height. This method works on both Big Endian or Little Endian machines
 *
 *  \param[in] name The path on disk where the image will be written.
 *  Existing files will be overwritten
 *  \param[in] width Width of the image
 *  \param[in] height Height of the image. The sign is ignored and a top-down
 *  ordered image will be written
 *  \param[in] data array of 8-bit values containing the image data in
 *  top-down left to right order. The values are in order RGBRGB...
 *  \return 1 if the image was successfully written, 0 otherwise
 */
char bmp_write(const char* name, int width, int height, const uint8_t* data);

/**
 *  \brief Checks if a BMP image is valid
 *
 *  Checks if the header of the file correspond to an actual BMP image
 *  readable by the functions defined in this file.
 *
 *  \note Only the header is checked, so if the file is truncated in the
 *  image data, this function could return 1 and the read could fail
 *
 *  \param[in] name The path on disk where the image can be found
 *  \return 1 if the image header is a valid BMP V3 one, 0 otherwise
 */
char bmp_valid(const char* name);

/**
 *  \brief Returns the width and height of a BMP image
 *
 *  Checks the header of an image and saves the image width and height in
 *  the pointer passed as input. If the image is not readable or the header
 *  not compatible 0 is returned. A bmp file can store the height as a negative
 *  number in some cases. However, the returned value will always be positive.
 *  Images saved in the OS/2 style are not compatible
 *
 *  \param[in] name The path on disk where the image can be found
 *  \param[out] width The width of the image
 *  \param[out] height The height of the image, always positive also for
 *  top-down ordered bitmaps
 *  \return 1 if the width and height was successfully read, 0 otherwise
 */
char bmp_dimensions(const char* name, int* width, int* height);

/**
 *  \brief Reads a BMP image
 *
 *  Reads a BMP image and writes the image data on the values array in
 *  top-down left-right order. This array is expected to be already allocated
 *  with a size of width*height*3. Every channel is written as a single uint8_t
 *  value in the order RGBRGB... with values in the range [0-255].
 *  If the bmp image contains an alpha channel, it will be written in the
 *  alpha array of size width*height. Also this array is expected to be
 *  already allocated and written values will be in the [0-255] range.
 *
 *  \param[in] name The path on disk where the image can be found
 *  \param[out] values The array of values that will be written. This array
 *  must be already allocated, use bmp_dimensions to know the actual size of
 *  the image and to preallocate it
 *  \param[out] alpha The array of alpha values. Also this array is expected
 *  to be already allocated
 *  \return 0 if the read was not successful. Otherwise 1 if the image was
 *  without alpha channel and 2 if the image had one
 */
char bmp_read(const char* name, uint8_t* values, uint8_t* alpha);

#endif
