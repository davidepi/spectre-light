/*
18-7-18
20-7-18
*/

#ifndef __PNG_H__
#define __PNG_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <png.h>

char png_write(const char* name, int width, int height, const uint8_t* data);

char png_valid(const char* name);

char png_dimensions(const char* name, int* width, int* height);

char png_read(const char* name, uint8_t* values, uint8_t* alpha);

#endif
