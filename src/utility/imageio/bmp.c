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
        fclose(fin);
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

char bmp_write(const char* name, int width, int height, const uint32_t* data)
{
    char retval = 0;
    FILE* fout = fopen(name, "wb");
    if(fout != NULL)
    {
        struct bmp_header header;
        struct bmp_dib_v3 dib;
        char bpp;
        char padding;
        int x;
        int y;
        int data_idx = 0;
        uint8_t* row;
        create_bmp_header(width, height, &header, &dib);
        bpp = ENDIANNESS_LITTLE16(dib.bpp) >> 3;
        padding = (width*bpp)%4;
        row = (uint8_t*)malloc(sizeof(uint8_t)*(bpp*width+padding));
        fwrite(&header, sizeof(struct bmp_header), 1, fout);
        fwrite(&dib, sizeof(struct bmp_dib_v3), 1, fout);
        for(y = 0; y<height; y++)
        {
            for(x = 0; x<width; x++)
            {
                row[x*3+0] = data[y*width+x] & 0xFF000000 >> 24; /* Blue  */
                row[x*3+1] = data[y*width+x] & 0x00FF0000 >> 16; /* Green */
                row[x*3+2] = data[y*width+x] & 0x0000FF00 >>  8; /* Red   */
                data_idx+=3;
            }
            fwrite(row, sizeof(uint8_t), bpp*width+padding, fout);
        }
        free(row);
        fclose(fout);
        retval = data_idx == width*height*bpp;
    }
    return retval;
}

char bmp_read(const char* name, uint32_t* values)
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
            const char has_alpha = bpp == 4;
            const char padding = (width*bpp)%4;
            int y;
            int ymax;
            int x;
            int increment = -height/abs(height);
            int written = 0;
            int row_len = bpp*width+padding;
            uint32_t* row = (uint32_t*)malloc(row_len);
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
            while(y != ymax && fread(row, bpp*width+padding, 1, fin))
            {
                if(has_alpha)
                {
                    memcpy(values+y*row_len, row, row_len);
                }
                else
                {
                    x = 0;
                    while(x<width)
                    {
                        /* ensures the alpha is always 0xFF */
                        values[(y*width+x)] = 0xFFFFFFFF;
                        values[(y*width+x)] &= row[x];
                        x++;
                    }
                }
                written += width;
                y += increment;
            }
            free(row);
            retval = written == (height*width);
        }
    }
    fclose(fin);
    return retval;
}
