#include "bmp.h"

#define SWAP(a, b) (((a) ^ (b)) && ((b) ^= (a) ^= (b), (a) ^= (b)))

uint32_t bmp_size(int width, int height, short bpp)
{
    return sizeof(struct bmp_header)+
           sizeof(struct bmp_dib_v3)+
           4*(((1 << bpp) & 0xFFFF)+height*((width*bpp+31)/32));
}

char bmp_valid(const char* name)
{
    int retval = 0;
    FILE* fin = fopen(name, "rb");
    if(fin != NULL)
    {
        struct bmp_header header;
        struct bmp_dib_v3 dib;
        size_t res = fread(&header, sizeof(struct bmp_header), 1, fin);
        retval = (res == sizeof(struct bmp_header)) &&
                 ENDIANNESS_LITTLE16(header.signature) == 16973;
        if(retval)
        {
            res = fread(&dib, sizeof(struct bmp_dib_v3), 1, fin);
            retval &= res == sizeof(struct bmp_dib_v3) &&
                      ENDIANNESS_LITTLE32(dib.header_size) == 40 &&
                      dib.compression == 0 && dib.palette_no == 0;
        }
    }
    return retval;
}

char bmp_dimensions(const char* name, int* width, int* height)
{
    int retval = 0;
    FILE* fin = fopen(name, "rb");
    if(fin != NULL)
    {
        struct bmp_header header;
        struct bmp_dib_v3 dib;
        size_t res = fread(&header, sizeof(struct bmp_header), 1, fin);
        if(res == sizeof(struct bmp_header))
        {
            res = fread(&dib, sizeof(struct bmp_dib_v3), 1, fin);
            if(res == sizeof(struct bmp_dib_v3))
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
    header->signature = ENDIANNESS_LITTLE16(16973);
    header->file_size = ENDIANNESS_LITTLE32(bmp_size(width, height, 24));
    header->data_offset = ENDIANNESS_LITTLE32(
                                  sizeof(struct bmp_header)+
                                  sizeof(struct bmp_dib_v3));
    dib->header_size = sizeof(struct bmp_dib_v3);
    dib->width = ENDIANNESS_LITTLE32(width);
    dib->height = ENDIANNESS_LITTLE32(-height);
    dib->color_planes = 1;
    dib->bpp = 24;
}

char bmp_save(const char* name, int width, int height, const uint8_t* data)
{
    int retval = 0;
    FILE* fout = fopen(name, "wb");
    if(fout != NULL)
    {
        struct bmp_header header;
        struct bmp_dib_v3 dib;
        uint8_t pixel[4];
        int x;
        int y;
        create_bmp_header(width, height, &header, &dib);
        fwrite(&header, sizeof(struct bmp_header), 1, fout);
        fwrite(&dib, sizeof(struct bmp_dib_v3), 1, fout);
        pixel[3] = 0x0; /* padding */
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
    if(res == sizeof(struct bmp_header) &&
       ENDIANNESS_LITTLE16(header.signature) == 16973)
    {
        res = fread(&dib, sizeof(struct bmp_dib_v3), 1, fin);
        /* not v3 or other fancy features not supported */
        if(res == sizeof(struct bmp_dib_v3) &&
           ENDIANNESS_LITTLE32(dib.header_size) == 40 &&
           dib.compression == 0 && dib.palette_no == 0)
        {
            int height = ENDIANNESS_LITTLE32(dib.height);
            const char has_alpha = dib.bpp == 32 && alpha != NULL;
            /* negative increment if height is pos */
            int increment = -height/abs(height);
            int min = 0;
            int max = height;
            int rgb_index = 0;
            int alpha_index = 0;
            if(increment<0)
                SWAP(min, max); /* reverse the order of the while */
            while(min != max)
            {
                fread(values+rgb_index, sizeof(uint8_t), 3, fin);
                if(has_alpha) /* hoping fread cached and loop invariant works */
                    fread(alpha+alpha_index++, sizeof(uint8_t), 1, fin);
                SWAP(values[rgb_index], values[rgb_index+2]); /* BGR to RGB */
                min += increment;
                rgb_index += 3;
            }
            retval = has_alpha?2:1;
        }
    }
    fclose(fin);
    return retval;
}
