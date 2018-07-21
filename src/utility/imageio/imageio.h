/*
16-7-18
18-7-18
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

char img_write(const char* name, const char* ext, int width, int height,
               const uint8_t* data);

char img_valid(const char* name, const char* ext);

char img_dimensions(const char* name, const char* ext,
                    int* width, int* height);

char img_read8(const char* name, const char* ext, uint8_t* values,
               uint8_t* alpha);

char img_read32(const char* name, const char* ext, float* values,
                uint8_t* alpha);

#endif
