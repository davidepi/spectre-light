/*
15-7-18
17-7-18
*/

#ifndef __TGA_H__
#define __TGA_H__

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "endianness.h"

struct tga_header
{
    uint8_t id_len;
    uint8_t colourmap_type;
    uint8_t datatype_code;
    uint16_t colourmap_origin;
    uint16_t colourmap_length;
    uint8_t colourmap_depth;
    uint16_t x_origin;
    uint16_t y_origin;
    uint16_t width;
    uint16_t height;
    uint8_t bpp;
    uint8_t img_descriptor;
};

char tga_dimensions(const char* name, int* width, int* height);

char tga_save(const char* name, int width, int height, const uint8_t* data);

char tga_read(const char* name, uint8_t* values, uint8_t* alpha);

char tga_valid(const char* name);

#endif
