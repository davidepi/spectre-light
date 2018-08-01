/*  author: Davide Pizzolotto   */
/*  license: MIT                */

#include "tga.h"

enum tga_datatype
{
    TGA_COLORMAP = 0x1,
    TGA_RGB = 0x2,
    TGA_GRAYSCALE = 0x3,
    TGA_COLORMAP_RLE = 0x9,
    TGA_RGB_RLE = 0xA,
    TGA_GRAYSCALE_RLE = 0xB
};

#define TGA_UPPER_ORIGIN 0x20

static char valid_header(struct tga_header* header)
{
    char retval = 1;
    uint8_t descriptor;
    switch(header->datatype_code)
    {
        case TGA_RGB:
        case TGA_RGB_RLE:break;
        case TGA_GRAYSCALE:
        case TGA_GRAYSCALE_RLE:
        case TGA_COLORMAP_RLE:
        case TGA_COLORMAP:
        default:retval = 0;
    }
    /* first three bytes are the alpha depth, I don't care */
    descriptor = header->img_descriptor & 0xF0;
    retval &= (header->bpp == 24 || header->bpp == 32 ||
               header->bpp == 16 || header->bpp == 15);
    retval &= header->colourmap_type == 0;
    retval &= descriptor == 0 || descriptor == TGA_UPPER_ORIGIN;
    return retval;
}

char tga_dimensions(const char* name, int* width, int* height)
{
    FILE* fin = fopen(name, "rb");
    char retval = 0;
    if(fin != NULL)
    {
        struct tga_header header;
        size_t res = fread(&header, sizeof(struct tga_header), 1, fin);
        if(res && valid_header(&header))
        {
            *width = ENDIANNESS_LITTLE16(header.width);
            *height = ENDIANNESS_LITTLE16(header.height);
            retval = 1;
        }
        fclose(fin);
    }
    return retval;
}

char tga_valid(const char* name)
{
    int retval = 0;
    FILE* fin = fopen(name, "rb");
    if(fin != NULL)
    {
        struct tga_header header;
        size_t res = fread(&header, sizeof(struct tga_header), 1, fin);
        retval = res && valid_header(&header);
        fclose(fin);
    }
    return retval;
}

char tga_write(const char* name, int width, int height, const uint8_t* data)
{
    char retval = 0;
    FILE* fout = fopen(name, "wb");
    if(fout != NULL)
    {
        struct tga_header header;
        int x;
        int y;
        uint8_t pixel[3];
        memset(&header, 0, sizeof(struct tga_header));
        header.width = ENDIANNESS_LITTLE16((uint16_t)width);
        header.height = ENDIANNESS_LITTLE16((uint16_t)height);
        header.datatype_code = TGA_RGB; /* uncompressed RGB */
        header.bpp = 24;
        header.img_descriptor = TGA_UPPER_ORIGIN;
        fwrite(&header, sizeof(struct tga_header), 1, fout);
        for(y = 0; y<height; y++)
        {
            for(x = 0; x<width; x++)
            {
                /* convert from RGB to BGR */
                pixel[0] = data[(y*width+x)*3+2];
                pixel[1] = data[(y*width+x)*3+1];
                pixel[2] = data[(y*width+x)*3+0];
                fwrite(&pixel, sizeof(pixel), 1, fout);
            }
        }
        fclose(fout);
        retval = 1;
    }
    return retval;
}

char tga_read(const char* name, uint8_t* values, uint8_t* alpha)
{
    char retval = 0;
    struct tga_header header;
    size_t res;
    FILE* fin = fopen(name, "rb");
    if(fin == NULL)
        return 0;
    res = fread(&header, sizeof(struct tga_header), 1, fin);
    /* things not supported */
    if(res && valid_header(&header))
    {
        /* ensures loop invariant code motion */
        /* i want bpp in bytes, 15-bit values are a variant of 16-bit ones */
        const uint8_t bpp = header.bpp == 15?2:header.bpp >> 3;
        const char compressed = header.datatype_code == TGA_RGB_RLE;
        const char alpha_null = alpha == NULL;
        const int width = ENDIANNESS_LITTLE16(header.width);
        const int height = ENDIANNESS_LITTLE16(header.height);
        uint8_t pixel[5];
        int x = 0;
        int y = 0;
        int ymax;
        int increment;
        int rgb_idx;
        int alpha_idx = 0;
        int skipme = header.id_len;
        int i = 0;
        int rle;
        skipme += header.colourmap_type*
                  ENDIANNESS_LITTLE16(header.colourmap_length);
        if(header.img_descriptor & TGA_UPPER_ORIGIN) /* top-down */
        {
            increment = 1;
            ymax = height;
            y = 0;
        }
        else
        {
            increment = -1;
            ymax = -1;
            y = height-1;
        }
        fseek(fin, skipme, SEEK_CUR); /* I don't care about these features */
        while(y != ymax)
        {
            rgb_idx = y*width*3;
            alpha_idx = y*width;
            x = 0;
            while(x<width && fread(&pixel, bpp+compressed, 1, fin))
            {
                if(!compressed)
                {
                    if(bpp == 3) /* 24 bit no RLE */
                    {
                        values[rgb_idx++] = pixel[2];
                        values[rgb_idx++] = pixel[1];
                        values[rgb_idx++] = pixel[0];
                    }
                    else if(bpp == 4) /* 32 bit no RLE */
                    {
                        values[rgb_idx++] = pixel[2];
                        values[rgb_idx++] = pixel[1];
                        values[rgb_idx++] = pixel[0];
                        if(!alpha_null)
                            alpha[alpha_idx++] = pixel[3];
                    }
                    else /* 16 bit no RLE */
                    {
                        /* the shift is a multiplication by 8 */
                        /* used to map a value from 0-31 to 0-255 */
                        values[rgb_idx++] = (pixel[1] & 0x7C) << 1;
                        values[rgb_idx++] = (pixel[1] & 0x03) << 6 |
                                            (pixel[0] & 0xE0) >> 2;
                        values[rgb_idx++] = (pixel[0] & 0x1F) << 3;
                    }
                    i++;
                    x++;
                }
                else /* RLE compression */
                {
                    if(pixel[0] & 0x80) /* RLE */
                    {
                        int rle_len = 1+(pixel[0] & 0x7F);
                        for(rle = 0; rle<rle_len; rle++)
                        {
                            if(bpp == 3)
                            {
                                values[rgb_idx++] = pixel[3];
                                values[rgb_idx++] = pixel[2];
                                values[rgb_idx++] = pixel[1];
                            }
                            else if(bpp == 4)
                            {
                                values[rgb_idx++] = pixel[3];
                                values[rgb_idx++] = pixel[2];
                                values[rgb_idx++] = pixel[1];
                                if(!alpha_null)
                                    alpha[alpha_idx++] = pixel[4];
                            }
                            else
                            {
                                /* the shift is a multiplication by 8 */
                                /* used to map a value from 0-31 to 0-255 */
                                values[rgb_idx++] = (pixel[2] & 0x7C) << 1;
                                values[rgb_idx++] = (pixel[2] & 0x03) << 6 |
                                                    (pixel[1] & 0xE0) >> 2;
                                values[rgb_idx++] = (pixel[1] & 0x1F) << 3;
                            }
                            x++;
                            i++;
                            if(x == width) /* wrap line */
                            {
                                y += increment;
                                if(y == ymax) /* endgame */
                                {
                                    /* set condition to break both loops */
                                    y = ymax-increment;
                                    x = width;
                                }
                                else
                                    x = 0;
                                rgb_idx = y*width*3;
                                alpha_idx = y*width;
                            }
                        }
                    }
                    else /* normal */
                    {
                        if(bpp == 3)
                        {
                            values[rgb_idx++] = pixel[3];
                            values[rgb_idx++] = pixel[2];
                            values[rgb_idx++] = pixel[1];
                        }
                        else if(bpp == 4)
                        {
                            values[rgb_idx++] = pixel[3];
                            values[rgb_idx++] = pixel[2];
                            values[rgb_idx++] = pixel[1];
                            if(!alpha_null)
                                alpha[alpha_idx++] = pixel[4];
                        }
                        else
                        {
                            /* the shift is a multiplication by 8 */
                            /* used to map a value from 0-31 to 0-255 */
                            values[rgb_idx++] = (pixel[2] & 0x7C) << 1;
                            values[rgb_idx++] = (pixel[2] & 0x03) << 6 |
                                                (pixel[1] & 0xE0) >> 2;
                            values[rgb_idx++] = (pixel[1] & 0x1F) << 3;
                        }
                        i++;
                        x++;
                    }

                }
            }
            y += increment;
        }
        retval = width*height == i;
        /* if retval > 0 then retval = 1 without alpha and 2 with alpha */
        retval = retval>0?(!alpha_null && bpp == 4)+1:0;
    }
    fclose(fin);
    return retval;
}
