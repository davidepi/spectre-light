/*  Created,  16 Jul 2018   */
/*  Last Edit  4 Aug 2018   */

/**
 *  \file imageio.h
 *  \brief Wrapper for image input and output
 *  \details Wraps the content of bmp.h, ppm.h, tga.h in single read/write
 *  functions
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date 4 Aug 2018
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

/** Never forget channel order! */
typedef uint32_t pixBGRA;

/** Red channel mask in a BGRA uint32_t number */
#define BGRA_RED_MASK 0x0000FF00

/** Green channel mask in a BGRA uint32_t number */
#define BGRA_GREEN_MASK 0x00FF0000

/** Blue channel mask in a BGRA uint32_t number */
#define BGRA_BLUE_MASK 0xFF000000

/** Alpha channel mask in a BGRA uint32_t number */
#define BGRA_ALPHA_MASK 0x000000FF

/** Get the Red channel value */
#define BGRA_RED(x) ((x & BGRA_RED_MASK)>>8)

/** Get the Green channel value */
#define BGRA_GREEN(x) ((x & BGRA_GREEN_MASK)>>16)

/** Get the Blue channel value */
#define BGRA_BLUE(x) ((x & BGRA_BLUE_MASK)>>24)

/** Get the Alpha channel value */
#define BGRA_ALPHA(x) ((x & BGRA_ALPHA_MASK))

/**
 *  \brief Writes an image in a generic format
 *
 *  This method writes an image passed as an array of values to the disk. The
 *  ext value is used to determine the actual type of image that will be written
 *
 *  \param[in] name Path where the image will be written
 *  \param[in] ext Extension of the image, like "bmp" or "tga", without dot
 *  \param[in] width Width of the image
 *  \param[in] height Height of the image
 *  \param[in] data Image data, as an array of size width*height with
 *  uint32_t values containing the representation of a pixel. Each pixel is
 *  composed of four values in range [0-255] ordered top-down left-right and
 *  ordered as 0xBBGGRRAA
 *  \return 1 if the image was successfully written, 0 otherwise
 */
char img_write(const char* name, const char* ext, int width, int height,
               const pixBGRA* data);

/**
 *  \brief Checks if an image header is valid
 *
 *  Checks if the header of an image on disk correspond to the type of image
 *  determined by the input extension or not. This does not grant that the
 *  final image will be readable
 *
 *  \param[in] name Path of the image on disk
 *  \param[in] ext Extension of the image, like "bmp" or "tga", without dot
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
 *  \param[in] ext Extension of the image, like "bmp" or "tga", without dot
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
 *  size of width*height. Values will be written as uint32_t composed by four
 *  values in range [0-255], in top-down left-right order. The four channels are
 *  ordered as 0xBBGGRRAA.
 *
 *  \param[in] name Path of the image on disk
 *  \param[in] ext Extension of the image, like "bmp" or "tga", without dot
 *  \param[in] values Array of size width*height that will contain every
 *  image value in range [0-255], top-down left-right order with channel as
 *  BGRA. Each pixel is an uint32_value composed of the four BGRA channels.
 *  \return 0 if the function encountered any kind of errors, 1 if the read was
 *  completed successfully
 */
char img_read8(const char* name, const char* ext, pixBGRA* values);

/**
 * \brief Checks if this library can handle the image
 *
 *  Briefly checks if the type of image with the given extension can be managed
 *  by this library. Note that even if this function returns 1, a particular
 *  version could be unsupported and unreadable
 *
 * \param[in] ext The extension of the image that will be checked, without dot
 * \return 1 if the library can handle the given kind of images, 0 otherwise
 */
char img_supported(const char* ext);

/**
 *  \brief Converts a 0xBBGGRRAA array to an RGB one
 *
 *  \param[out] out An array of size len*3, already allocated, that will hold
 *  the RGB values extracted from the 0xBBGGRRAA one
 *  \param[in] in The array that will be converted
 *  \param[in] len The length of the input array
 */
void BGRAtoRGB(uint8_t* out, const uint32_t* in, size_t len);

/**
 *  \brief Converts an RGB array to a 0xBBGGRRAA one
 *
 *  \param[out] out An array of size len/3, already allocated, that will hold
 *  the BGRA values extracted from the RGB one. Alpha will always be 255.
 *  \param[in] in The array that will be converted
 *  \param[in] len The length of the input array
 */
void RGBtoBGRA(uint32_t* out, const uint8_t* in, size_t len);

/*
 Maybe this will be readded in future
 char img_read32(const char* name, const char* ext, float* values,
                uint8_t* alpha);
*/

#endif
