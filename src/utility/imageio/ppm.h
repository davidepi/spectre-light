/*
15-7-18
17-7-18
*/

#ifndef __PPM_H__
#define __PPM_H__

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "endianness.h"

char ppm_save(const char* name, int width, int height, const uint8_t* data);

char ppm_read(const char* name, uint8_t* values, uint8_t* alpha);

char ppm_dimensions(const char* name, int* width, int* height);

char ppm_valid(const char* name);

#endif
