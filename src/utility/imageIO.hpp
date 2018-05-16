//Created,  27 Nov 2017
//Last Edit 16 May 2018

/**
 *  \file imageIO.hpp
 *  \brief     Functions to save an array of pixel in different formats
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      16 May 2018
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
///Error code returned when reading OS/2 style images
#define IMAGE_NOT_SUPPORTED -3

#include "console.hpp"
#include "utility.hpp"
#include <cstdio>
#include <cstdlib>
#ifdef IMAGEMAGICK
#include <cstring>
#include <Magick++.h>
#include <type_traits> //std::is_floating_point
#endif

///Initializes ImageMagick routines
void ImageIO_init();

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
 *  the returned value will always be positive. Images saved in the OS/2 style
 *  are not compatible
 *
 *  \param[in] name The path of the image
 *  \param[out] width The width of the image, error code if something went wrong
 *  \param[out] height The height of the image, error code if something went
 *  wrong
 */
void dimensions_bmp(const char* name, int* width, int* height);

/** \brief Read an image in the BMP format (24-bit Windows only)
 *
 *  This method reads an image in the BMP format Version 3, and saves the value
 *  of the pixels in the data array. The data array is an array of length
 *  width*height*3 and stores values as floats in the range [0.0, 1.0].
 *  The components are stored in the order R,G,B and no alpha channel is
 *  supported, hence no 32 bit BMP support is provided.
 *  OS/2 style header and indexed images are also not supported, this being only
 *  a basic reader.
 *  Upon completition the function returns IMAGE_OK if the read succeded, or a
 *  proper error code. The list of error codes can be found at the beginning of
 *  the imageIO.hpp file
 *
 *  \param[in] name The path of the image
 *  \param[out] data An array of size width*height*3 that will hold the values
 *  of the image
 *  \return IMAGE_OK if everything was ok, otherwise a proper error code
 */
int read_bmp(const char* name, float* data);

/** \brief Save an RGB image
 *
 *  Save an image using the ImageMagick API. The output is detected using the
 *  filename extension. The quality is set to be the highest possible given the
 *  requested output format. The image depth is 8 bit per pixel and no alpha
 *  channel is supported.
 *  Note that if ImageMagick is not supported, but the image is a .ppm or .bmp
 *  this method will invoke save_ppm() or save_bmp() respectively
 *
 *  \param[in] name The name of the output file
 *  \param[in] ext The extension of the image
 *  \param[in] width The width of the image
 *  \param[in] height The height of the image
 *  \param[in] data An array of RGB values containing the pixel values in range
 *  0-255
 */
bool save_RGB(const char* name, const char* ext, int width, int height,
              const uint8_t* data);

/** \brief Determine width, height and opacity of an image in a generic format
 *
 *  This method uses the ImageMagick API to determine the width and height of
 *  an image. These values are saved in the area located by the width and height
 *  pointers passed as input. If the image is not readable or ImageMagick is not
 *  supported, the width and height are set to the corresponding error code.
 *  The list of error codes can be found at the beginning of the imageIO.hpp
 *  file. The functions returns a value indicating wether an alpha channel is
 *  present or not.
 *  Note that if ImageMagick is not supported, but the image is a .ppm or .bmp
 *  this method will invoke dimensions_ppm() or dimensions_bmp() respectively
 *
 *  \param[in] name The path of the image
 *  \param[in] ext The extension of the image
 *  \param[out] width The width of the image, error code if something went wrong
 *  \param[out] height The height of the image, error code if something went
 *  wrong
 *  \return True if the image has an alpha channel
 */
bool dimensions_RGB(const char* name, const char* ext, int* width, int* height);

/** \brief Read an image in a generic format
 *
 *  This method uses the ImageMagick API to read an image in a generic format
 *  and save the value of the pixels in the data array. The data array is
 *  a float array of length width*height*3 and stores values as floats in the
 *  range [0.0, 1.0]. The components are stored in the order R,G,B. If the
 *  image contains an alpha channel, this is written in the alpha array of
 *  length width*height. Only one alpha channel is supported and the extent of
 *  these values are in the range [0, 255]; multiple alpha channels will exhibit
 *  undefined behaviour. Images with less than three channels or in CYMK format
 *  are also not supported.
 *  Note that if ImageMagick is not supported, but the image is a .ppm or .bmp
 *  this method will invoke read_ppm() or read_bmp() respectively
 *
 *  \param[in] name The path of the image
 *  \param[in] ext The extension of the image
 *  \param[out] data An array of size width*height*3 that will hold the values
 *  of the image
 *  \param[out] alpha An array of size width*height that will hold the values
 *  of the alpha channel
 *  \return IMAGE_OK if everything was ok, otherwise a proper error code
 */
int read_RGB(const char* name, const char* ext, float* data, uint8_t* alpha);

/** \brief Checks if an image is supported
 *
 *  Since image support is defined at compile time depending on ImageMagick,
 *  this method is used at runtime to know throughout the code if the input file
 *  provided by the user is compatible (r/w). Usually if the file is an image
 *  and ImageMagick was installed at compile time, this function will return
 *  true.
 *
 *  \param[in] extension The extension of the image
 *  \retun true if the image is supported, false otherwise
 */
char image_supported(const char* extension);

/**
 *  \brief Checks wheter an image has a depth higher than 8 bit per pixel or not
 *
 *  This function checks the image depth of the file passed as input. If the
 *  file has a depth higher than 8 bit per pixel it returns true, otherwise
 *  it returns false. It is not checked if the file exist, this should be
 *  handled somewhere else.
 *  If the function encounters any kind of errors (unable to open the file or
 *  unsupported extension) false is returned by default. (Again, errors
 *  should be checked by the read function)
 *
 *  \param[in] name Path to the image that will be checked
 *  \param[in] extension Extesion, without the dot, of the image that will be
 *  checked
 *  \return true if an image has a depth higher than 8 bit per pixel, false
 *  otherwise
 */
bool high_depth(const char* name, const char* extension);

#endif
