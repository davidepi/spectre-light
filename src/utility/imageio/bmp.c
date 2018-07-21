/*  author: Davide Pizzolotto   */
/*  license: MIT                */

#include "bmp.h"

#define BMP_MAGIC 19778

uint32_t bmp_size(int width, int height, short bpp)
{
    return sizeof(struct bmp_header)+
           sizeof(struct bmp_dib_v3)+
           4*(((1 << bpp) & 0xFFFF)+height*((width*bpp+31)/32));
}

char bmp_valid(const char* name)
{
    char retval = 0;
    FILE* fin = fopen(name, "rb");
    if(fin != NULL)
    {
        struct bmp_header header;
        struct bmp_dib_v3 dib;
        size_t res = fread(&header, sizeof(struct bmp_header), 1, fin);
        retval = res && ENDIANNESS_LITTLE16(header.signature) == BMP_MAGIC;
        if(retval)
        {
            res = fread(&dib, sizeof(struct bmp_dib_v3), 1, fin);
            retval &= res && dib.compression == 0 && dib.palette_no == 0 &&
                      (dib.bpp == 24 || dib.bpp == 32);
        }
    }
    return retval;
}

char bmp_dimensions(const char* name, int* width, int* height)
{
    char retval = 0;
    FILE* fin = fopen(name, "rb");
    if(fin != NULL)
    {
        struct bmp_header header;
        struct bmp_dib_v3 dib;
        size_t res = fread(&header, sizeof(struct bmp_header), 1, fin);
        if(res)
        {
            res = fread(&dib, sizeof(struct bmp_dib_v3), 1, fin);
            if(res && ENDIANNESS_LITTLE16(header.signature) == BMP_MAGIC)
            {
                *width = ENDIANNESS_LITTLE32(dib.width);
                *height = ENDIANNESS_LITTLE32(dib.height);
                *height = *height>=0?*height:-*height;
                retval = 1;
            }
        }
        fclose(fin);
    }
    return retval;
}

static void create_bmp_header(int width, int height,
                              struct bmp_header* header,
                              struct bmp_dib_v3* dib)
{
    memset(header, 0, sizeof(struct bmp_header));
    memset(dib, 0, sizeof(struct bmp_dib_v3));
    header->signature = ENDIANNESS_LITTLE16(BMP_MAGIC);
    header->file_size = ENDIANNESS_LITTLE32(bmp_size(width, height, 24));
    header->data_offset = ENDIANNESS_LITTLE32(
                                  sizeof(struct bmp_header)+
                                  sizeof(struct bmp_dib_v3));
    dib->header_size = sizeof(struct bmp_dib_v3);
    dib->width = ENDIANNESS_LITTLE32(width);
    dib->height = ENDIANNESS_LITTLE32(-abs(height));
    dib->color_planes = 1;
    dib->bpp = 24;
}

char bmp_write(const char* name, int width, int height, const uint8_t* data)
{
    char retval = 0;
    FILE* fout = fopen(name, "wb");
    if(fout != NULL)
    {
        struct bmp_header header;
        struct bmp_dib_v3 dib;
        uint8_t pixel[3];
        const char padding = (width*(ENDIANNESS_LITTLE16(dib.bpp) >> 3))%4;
        int x;
        int y;
        create_bmp_header(width, height, &header, &dib);
        fwrite(&header, sizeof(struct bmp_header), 1, fout);
        fwrite(&dib, sizeof(struct bmp_dib_v3), 1, fout);
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
            fwrite(&pixel, sizeof(uint8_t), padding, fout); /* random data */

        }
        fclose(fout);
        retval = 1;
    }
    return retval;
}

char bmp_read(const char* name, uint8_t* values, uint8_t* alpha)
{
    FILE* fin = fopen(name, "rb");
    struct bmp_header header;
    struct bmp_dib_v3 dib;
    size_t res;
    char retval = 0;
    if(fin == NULL)
        return 0;
    res = fread(&header, sizeof(struct bmp_header), 1, fin);
    if(res && ENDIANNESS_LITTLE16(header.signature) == BMP_MAGIC)
    {
        res = fread(&dib, sizeof(struct bmp_dib_v3), 1, fin);
        /* not v3 or other fancy features not supported */
        if(res && dib.compression == 0 && dib.palette_no == 0 &&
           (ENDIANNESS_LITTLE16(dib.bpp) == 24 ||
            ENDIANNESS_LITTLE16(dib.bpp) == 32))
        {
            int height = ENDIANNESS_LITTLE32(dib.height);
            const int width = ENDIANNESS_LITTLE32(dib.width);
            const int bpp = ENDIANNESS_LITTLE16(dib.bpp) >> 3;
            const char has_alpha = bpp == 4 && alpha != NULL;
            int y;
            int ymax;
            int x;
            int increment = -height/abs(height);
            int padding = (width*bpp)%4;
            int written = 0;
            uint8_t pixel[4];
            if(increment<0)
            {
                ymax = -1;
                y = height-1;
            }
            else
            {
                height = -height;
                ymax = height;
                y = 0;
            }
            fseek(fin, ENDIANNESS_LITTLE32(header.data_offset), SEEK_SET);
            while(y != ymax)
            {
                x = 0;
                while(x<width && fread(&pixel, bpp, 1, fin))
                {
                    values[(y*width+x)*3+0] = pixel[2];
                    values[(y*width+x)*3+1] = pixel[1];
                    values[(y*width+x)*3+2] = pixel[0];
                    /* hoping fread is cached and loop invariant works */
                    if(has_alpha)
                        alpha[(y*width+x)] = pixel[3];
                    written++;
                    x++;
                }
                fread(&pixel, sizeof(uint8_t), padding, fin);
                y += increment;
            }
            retval = written == (height*width)?has_alpha?2:1:0;
        }
    }
    fclose(fin);
    return retval;
}
