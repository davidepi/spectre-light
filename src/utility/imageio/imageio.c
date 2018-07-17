#include "imageio.h"

#define UNUSED(x) (void)(x)

char img_valid(const char* name, const char* ext)
{
    char retval = 0;
    /* pos less than 4 chr expected for an extension */
    if(ext != NULL && strcmp(ext, "") != 0)
    {
        if(strcmp(ext, "bmp") == 0)
            retval = bmp_valid(name);
        else if(strcmp(ext, "tga") == 0)
            retval = tga_valid(name);
        else if(strcmp(ext, "ppm") == 0)
            retval = ppm_valid(name);
    }
    return retval;
}

char img_save(const char* name, const char* ext, int width, int height,
              const uint8_t* data)
{
    char retval = 0;
    if(strcmp(ext, "bmp") == 0)
        retval = bmp_save(name, width, height, data);
    else if(strcmp(ext, "tga") == 0)
        retval = tga_save(name, width, height, data);
    else if(strcmp(ext, "ppm") == 0)
        retval = ppm_save(name, width, height, data);
    return retval;
}

char img_read8(const char* name, const char* ext, int width, int height,
               uint8_t* values, uint8_t* alpha)
{
    char retval = 0;
    UNUSED(width);
    UNUSED(height);
    if(strcmp(ext, "bmp") == 0)
        retval = bmp_read(name, values, alpha);
    else if(strcmp(ext, "tga") == 0)
        retval = tga_read(name, values, alpha);
    else if(strcmp(ext, "ppm") == 0)
        retval = ppm_read(name, values, alpha);
    return retval;
}

char img_read32(const char* name, const char* ext, int width, int height,
                float* values, uint8_t* alpha)
{
    uint8_t* tmp = (uint8_t*)malloc(sizeof(uint8_t)*width*height*3);
    char retval = 0;
    if(strcmp(ext, "bmp") == 0)
        retval = bmp_read(name, tmp, alpha);
    else if(strcmp(ext, "tga") == 0)
        retval = tga_read(name, tmp, alpha);
    else if(strcmp(ext, "ppm") == 0)
        retval = ppm_read(name, tmp, alpha);
    if(retval)
    {
        /* this step is useless unless new formats with high DPI are added */
        int i = 0;
        while(i<width*height*3)
        {
            values[i] = ((float)(tmp[i]))/255.f;
            i++;
        }
    }
    free(tmp);
    return retval;
}

char img_dimensions(const char* name, const char* ext,
                    int* width, int* height)
{
    char retval = 0;
    if(strcmp(ext, "bmp") == 0)
        retval = bmp_dimensions(name, width, height);
    else if(strcmp(ext, "tga") == 0)
        retval = tga_dimensions(name, width, height);
    else if(strcmp(ext, "ppm") == 0)
        retval = ppm_dimensions(name, width, height);
    return retval;
}
