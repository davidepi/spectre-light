#include "tga.h"

char tga_dimensions(const char* name, int* width, int* height)
{
    FILE* fin = fopen(name, "rb");
    char retval = 0;
    if(fin != NULL)
    {
        struct tga_header header;
        size_t res = fread(&header, sizeof(struct tga_header), 1, fin);
        if(res == sizeof(struct tga_header))
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
        retval = res == sizeof(struct tga_header) &&
                 (header.datatype_code == 2 || header.datatype_code == 10) &&
                 (header.bpp == 24 || header.bpp == 32 || header.bpp == 16) &&
                 (header.colourmap_type == 0 || header.colourmap_type == 1);
        fclose(fin);
    }
    return retval;
}

char tga_save(const char* name, int width, int height, const uint8_t* data)
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
        header.datatype_code = 2; /* uncompressed RGB */
        header.bpp = 24;
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
    /* wrong image */
    if(res != sizeof(struct tga_header))
        goto end;
    /* things not supported */
    if((header.datatype_code == 2 || header.datatype_code == 10) &&
       /* not RGB */
       (header.bpp == 24 || header.bpp == 32 || header.bpp == 16) &&
       /* color depth */
       (header.colourmap_type == 0 || header.colourmap_type == 1)) /* idk */
    {
        /* ensures loop invariant code motion */
        const uint8_t bpp = header.bpp/8;
        const int compressed = header.datatype_code == 2;
        const int width = ENDIANNESS_LITTLE16(header.width);
        const int height = ENDIANNESS_LITTLE16(header.height);
        uint8_t pixel[5];
        int i;
        int rgb_index = 0;
        int alpha_index = 0;
        int skipme = header.id_len;
        skipme += header.colourmap_type*
                  ENDIANNESS_LITTLE16(header.colourmap_length);
        fseek(fin, skipme, SEEK_CUR); /* I don't care about these features */
        for(i = 0; i<width*height; i++)
        {
            if(!compressed)
            {
                res = fread(&pixel, bpp, 1, fin);
                if(res == 0)
                    goto end; /* unexpected EOF, but fd needs to be closed */
                if(bpp == 3)
                {
                    values[rgb_index++] = pixel[2];
                    values[rgb_index++] = pixel[1];
                    values[rgb_index++] = pixel[0];
                }
                else if(bpp == 4)
                {
                    values[rgb_index++] = pixel[2];
                    values[rgb_index++] = pixel[1];
                    values[rgb_index++] = pixel[0];
                    alpha[alpha_index++] = pixel[3];
                }
                else
                {
                    values[rgb_index++] = (uint8_t)((pixel[1] & 0x7C) << 1);
                    values[rgb_index++] = (uint8_t)(((pixel[1] & 0x03) << 6) |
                                                    ((pixel[0] & 0xE0) >> 2));
                    values[rgb_index++] = (uint8_t)((pixel[0] & 0x1F) << 3);
                    alpha[alpha_index++] = (uint8_t)((pixel[1] & 0x80));
                }
            }
            else /* RLE compression */
            {
                res = fread(&pixel, bpp+1, 1, fin);
                if(res == 0)
                    goto end; /* unexpected EOF, but fd needs to be closed */
                if(pixel[0] & 0x80) /* RLE */
                {
                    int rle_len = i+(pixel[0] & 0x7F);
                    while(i<rle_len)
                    {
                        if(bpp == 3)
                        {
                            values[rgb_index++] = pixel[3];
                            values[rgb_index++] = pixel[2];
                            values[rgb_index++] = pixel[1];
                        }
                        else if(bpp == 4)
                        {
                            values[rgb_index++] = pixel[3];
                            values[rgb_index++] = pixel[2];
                            values[rgb_index++] = pixel[1];
                            alpha[alpha_index++] = pixel[4];
                        }
                        else
                        {
                            values[rgb_index++] = (uint8_t)((pixel[2] & 0x7C)
                                    << 1);
                            values[rgb_index++] = (uint8_t)(
                                    ((pixel[2] & 0x03) << 6) |
                                    ((pixel[1] & 0xE0) >> 2));
                            values[rgb_index++] = (uint8_t)((pixel[1] & 0x1F)
                                    << 3);
                            alpha[alpha_index++] = (uint8_t)((pixel[2] & 0x80));
                        }
                        i++;
                    }
                }
                else /* normal */
                {
                    if(bpp == 3)
                    {
                        values[rgb_index++] = pixel[3];
                        values[rgb_index++] = pixel[2];
                        values[rgb_index++] = pixel[1];
                    }
                    else if(bpp == 4)
                    {
                        values[rgb_index++] = pixel[3];
                        values[rgb_index++] = pixel[2];
                        values[rgb_index++] = pixel[1];
                        alpha[alpha_index++] = pixel[4];
                    }
                    else
                    {
                        values[rgb_index++] = (uint8_t)((pixel[2] & 0x7C) << 1);
                        values[rgb_index++] = (uint8_t)(
                                ((pixel[2] & 0x03) << 6) |
                                ((pixel[1] & 0xE0) >> 2));
                        values[rgb_index++] = (uint8_t)((pixel[1] & 0x1F) << 3);
                        alpha[alpha_index++] = (uint8_t)((pixel[2] & 0x80));
                    }
                }

            }
        }
        retval = retval>0?alpha_index != 0+1:0;
    }
    end:
    fclose(fin);
    return retval;
}
