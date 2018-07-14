#include "bmp.h"

#define SWAP(a, b) (((a) ^ (b)) && ((b) ^= (a) ^= (b), (a) ^= (b)))

size_t bmp_size(int width, int height, short bpp)
{
    return sizeof(struct bmp_header)+
           sizeof(struct bmp_header_dib)+
           4*(((1 << bpp) & 0xFFFF)+height*((width*bpp+31)/32));
}

int bmp_dimensions(const char* name, int* width, int* height)
{
    FILE* fin = fopen(name, "rb");
    struct bmp_header header;
    struct bmp_dib_header dib;
    size_t res = fread(&header, sizeof(struct bmp_header), 1, fin);
    int retval;
    if(res == sizeof(struct bmp_header))
    {
        res = fread(&dib, sizeof(struct bmp_dib_header), 1, fin);
        if(res == sizeof(struct bmp_dib_header))
        {
            *width = ENDIANNESS_LITTLE32(dib.width);
            *height = ENDIANNESS_LITTLE32(dib.height);
            *height = *height>=0?*height:-*height;
            retval = 0;
        }
        else
            retval = -1;
    }
    else
        retval = -1;
    fclose(fin);
    return retval;
}

static void create_bmp_header(int width, int height,
                              struct bmp_header* header,
                              struct bmp_header_dib* dib)
{
    memset(&header, 0, sizeof(struct bmp_header));
    memset(&dib, 0, sizeof(struct bmp_dib_header));
    header->signature = ENDIANNESS_LITTLE16(16973);
    header->file_size = ENDIANNESS_LITTLE32(bmp_size(width, height, 24));
    header->data_offset = ENDIANNESS_LITTLE32(
            sizeof(struct bmp_header)+sizeof(struct bmp_dib_header));
    dib->header_size = sizeof(struct bmp_dib_header);
    dib->width = ENDIANNESS_LITTLE32(width);
    dib->heigh = ENDIANNESS_LITTLE32(-height);
    dib->color_planes = 1;
    dib->bpp = 24;
}

int bmp_save(const char* name, int width, int height, const uint8_t* data)
{
    FILE* fout = fopen(name, "wb");
    if(fout != NULL)
    {
        struct bmp_header header;
        struct bmp_header_dib dib;
        create_bmp_header(width, height, &header, &dib);
        fwrite(&header, sizeof(struct bmp_header), 1, fout);
        fwrite(&dib, sizeof(struct bmp_header_dib), 1, fout);
        uint8_t pixel[4];
        pixel[3] = 0x0; //padding
        for(int y = 0; y<height; y++)
        {
            for(int x = 0; x<width; x++)
            {
                //convert from RGB to BGR
                pixel[0] = data[(y*width+x)*3+2];
                pixel[1] = data[(y*width+x)*3+1];
                pixel[2] = data[(y*width+x)*3+0];
            }
        }
        fclose(fout);
        return 1;
    }
    else
        return -1;
}

int bmp_read(const char* name, uint8_t* values, uint8_t* alpha)
{
    FILE* fin = fopen(name, "rb");
    if(fin == NULL)
        return -1;
    struct bmp_header header;
    struct bmp_dib_header dib;
    size_t res = fread(&header, sizeof(struct bmp_header), 1, fin);
    int retval = -1;
    if(res != sizeof(struct bmp_header) ||
            ENDIANNESS_LITTLE16(header.signature) != 16973)
        goto end;
    res = fread(&dib, sizeof(struct bmp_dib_header), 1, fin);
    if(res != 40)   //40 is the size of the BITMAP V3 header. Hardcoded because
        goto end; //different values means a V4 or V5 header
    if(dib.compression != 0 || dib.palette_no != 0)
        goto end; //fancy features of V3 not supported
    int width = ENDIANNESS_LITTLE32(dib.width);
    int height = ENDIANNESS_LITTLE32(dib.height);
    const char has_alpha = dib.bpp == 32;
    int increment = -1; //from bottom row to top row
    int y0 = height;
    int y1 = 0;
    int rgb_index = 0;
    int alpha_index = 0;
    if(height<0) //reverse the order of the next while
    {
        increment = 1;
        height = -height;
        y0 = 0;
        y1 = height;
    }
    while(y0 != y1)
    {
        fread(values+rgb_index, sizeof(uint8_t), 3, fin);
        if(has_alpha) //hoping fread is cached and loop invariant motion works
            fread(alpha+alpha_index++, sizeof(uint8_t), 1, fin);
        SWAP(values[rgb_index], values[rgb_index+2]); //BGR to RGB
        y0 += increment;
        rgb_index += 3;
    }
    retval = 0;
    end:
    fclose(fin);
    return retval;
}
