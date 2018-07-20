/*
18-7-18
20-7-18
*/

#ifndef __JPG_H__
#define __JPG_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <jpeglib.h>

char jpg_write(const char* name, int width, int height, const uint8_t* data);

char jpg_valid(const char* name);

char jpg_dimensions(const char* name, int* width, int* height);

char jpg_read(const char* name, uint8_t* values, uint8_t* alpha);


#endif
