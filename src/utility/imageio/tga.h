//15-7-18
//15-7-18

#ifndef __TGA_H__
#define __TGA_H__

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "endianness.h"

struct tga_header
{
    uint8_t  idlength;
    uint8_t  colourmap_type;
    uint8_t  datatypecode;
    uint16_t colourmap_origin;
    uint16_t colourmap_length;
    uint8_t  colourmap_depth;
    uint16_t x_origin;
    uint16_t y_origin;
    uint16_t width;
    uint16_t height;
    uint8_t  bpp;
    uint8_t  img_descriptor;
};

int tga_dimensions(const char* name, int* width, int* height);
int tga_save(const char* name, int width, int height, const uint8_t* data);
int tga_read(const char* name, uint8_t* values, uint8_t* alpha);

#endif
