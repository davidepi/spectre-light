/*  author: Davide Pizzolotto   */
/*  license: MIT                */

#include "ppm.h"

#define CLAMP(x, y, z) ((x)<0)?0:(x)>(z)?(z):(x)

char ppm_write(const char* name, int width, int height, const uint32_t* array)
{
    FILE* fout = fopen(name, "wb");
    char retval = 0;
    int i;
    if(fout != NULL)
    {
        fprintf(fout, "P6 %d %d 255 ", width, height);
        size_t written = 0;
        for(i=0;i<width*height;i++)
        {
            /* convert BGRA to RGB */
            uint8_t pixel[3];
            pixel[0] = (array[i] & 0x0000FF00) >> 8;
            pixel[1] = (array[i] & 0x00FF0000) >> 16;
            pixel[2] = (array[i] & 0xFF000000) >> 24;
            written += fwrite(&pixel, sizeof(uint8_t), 3, fout);
        }
        fclose(fout);
        retval = written==width*height*3;
    }
    return retval;
}

char ppm_dimensions(const char* name, int* width, int* height)
{
    FILE* fin = fopen(name, "rb");
    char retval = 0;
    if(fin != NULL)
    {
        char magic[2];
        fscanf(fin, "%c%c", magic+0, magic+1);
        if(magic[0] == 'P' && (magic[1] == '3' || magic[1] == '6'))
        {
            fscanf(fin, "%d%d", width, height);
            retval = 1;
        }
        fclose(fin);
    }
    return retval;
}

char ppm_valid(const char* name)
{
    char retval = 0;
    FILE* fin = fopen(name, "rb");
    if(fin != NULL)
    {
        char magic[2];
        fscanf(fin, "%c%c", magic+0, magic+1);
        fclose(fin);
        retval = magic[0] == 'P' && (magic[1] == '3' || magic[1] == '6');
    }
    return retval;
}

char ppm_read(const char* name, uint32_t* values)
{
    FILE* fin = fopen(name, "rb");
    char retval = 0;
    if(fin != NULL)
    {
        char magic[2];
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        fscanf(fin, "%c%c", magic+0, magic+1);
        /* check magic number to determine if ASCII or binary */
        if(magic[0] == 'P')
        {
            unsigned int width;
            unsigned int height;
            float depth;
            uint16_t depth_short;
            fscanf(fin, "%u%u%hu", &width, &height, &depth_short);
            /* not my fucking problem if the depth is > 65536, the specification
             states that the aforementioned value is the max */
            depth = (float)depth_short;
            if(magic[1] == '3') /* ASCII */
            {
                char val[6];
                uint16_t num_val;
                unsigned int i;
                for(i = 0; i<width*height; i++)
                {
                    values[i] = 0x000000FF;
                    fscanf(fin, "%5s", val);
                    sscanf(val, "%hu", &num_val);
                    red = (uint8_t)(CLAMP((num_val/depth), 0.f, 1.f)*255);
                    fscanf(fin, "%5s", val);
                    sscanf(val, "%hu", &num_val);
                    green = (uint8_t)(CLAMP((num_val/depth), 0.f, 1.f)*255);
                    fscanf(fin, "%5s", val);
                    sscanf(val, "%hu", &num_val);
                    blue = (uint8_t)(CLAMP((num_val/depth), 0.f, 1.f)*255);
                    values[i] |= red << 8;
                    values[i] |= green << 16;
                    values[i] |= blue << 24;
                }
                retval = 1;
            }
            else if(magic[1] == '6') /* Binary */
            {
                unsigned int x = 0;
                unsigned int y = 0;
                unsigned int row_idx = 0;
                unsigned int output_idx = 0;
                /* skip 1 space, after the depth
                   by specification this will ALWAYS be ONE space or newline
                   so no \n\r or other windows shits */
                fseek(fin, 1, SEEK_CUR);
                size_t read;
                if(depth_short<=255)/* 1 byte per component */
                {
                    uint8_t* row = (uint8_t*)malloc(sizeof(uint8_t)*width*3);
                    /* read a pixel block of READ_BUFFER size */
                    while(y<height &&
                          fread(row, sizeof(uint8_t)*(width*3), 1, fin))
                    {
                        row_idx = 0;
                        x = 0;
                        while(x<width)
                        {
                            red = (uint8_t)((row[row_idx++]/depth)*255);
                            green = (uint8_t)((row[row_idx++]/depth)*255);
                            blue = (uint8_t)((row[row_idx++]/depth)*255);
                            values[output_idx] = 0x000000FF;
                            values[output_idx] |= red << 8;
                            values[output_idx] |= green << 16;
                            values[output_idx++] |= blue << 24;
                            x++;
                        }
                        y++;
                    }
                    free(row);
                }
                else/* 2 bytes per component, high depth */
                {
                    uint16_t* row = (uint16_t*)malloc(sizeof(uint16_t)*width*3);
                    /* read a pixel block of READ_BUFFER size */
                    while(y<height &&
                          fread(row, sizeof(uint16_t)*(width*3), 1, fin))
                    {
                        row_idx = 0;
                        x = 0;
                        while(x<width)
                        {
                            uint16_t val;
                            val = ENDIANNESS_BIG16(row[row_idx]);
                            row_idx++;
                            red = (uint8_t)(CLAMP(val/depth, 0.f, 1.f)*255);
                            val = ENDIANNESS_BIG16(row[row_idx]);
                            row_idx++;
                            green = (uint8_t)(CLAMP(val/depth, 0.f, 1.f)*255);
                            val = ENDIANNESS_BIG16(row[row_idx]);
                            row_idx++;
                            blue = (uint8_t)(CLAMP(val/depth, 0.f, 1.f)*255);
                            values[output_idx] = 0x000000FF;
                            values[output_idx] |= red << 8;
                            values[output_idx] |= green << 16;
                            values[output_idx++] |= blue << 24;
                            x++;
                        }
                        y++;
                    }
                    free(row);
                }
                retval = output_idx == width*height;
            }
        }
        fclose(fin);
    }
    return retval;
}
