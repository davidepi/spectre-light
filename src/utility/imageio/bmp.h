/*
13-7-18
17-7-18
*/

#ifndef __BMP_H__
#define __BMP_H__

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "endianness.h"
#include "packed_struct.h"

PACKED_STRUCT(bmp_header)
{
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t data_offset;
};

PACKED_STRUCT(bmp_dib_v3)
{
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t color_planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t raw_size;
    int32_t resolution_w;
    int32_t resolution_h;
    uint32_t palette_no;
    uint32_t important_colors_no;
};

char bmp_write(const char* name, int width, int height, const uint8_t* data);

char bmp_valid(const char* name);

char bmp_dimensions(const char* name, int* width, int* height);

char bmp_read(const char* name, uint8_t* values, uint8_t* alpha);


#endif
