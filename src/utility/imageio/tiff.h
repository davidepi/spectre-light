/*
21-7-18
21-7-18
*/

#ifndef __TIFF_H__
#define __TIFF_H__

#include <stdint.h>
#include <memory.h>
#include <tiffio.h>

char tiff_write(const char* name, int width, int height, const uint8_t* data);

char tiff_valid(const char* name);

char tiff_dimensions(const char* name, int* width, int* height);

char tiff_read(const char* name, uint8_t* values, uint8_t* alpha);

#endif
