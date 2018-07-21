/*  author: Davide Pizzolotto   */
/*  license: MIT                */

#include "imageio.h"

#define UNUSED(x) (void)(x)

char img_write(const char* name, const char* ext, int width, int height,
               const uint8_t* data)
{
    char retval = 0;
    if(strcmp(ext, "bmp") == 0)
        retval = bmp_write(name, width, height, data);
    else if(strcmp(ext, "tga") == 0)
        retval = tga_write(name, width, height, data);
    else if(strcmp(ext, "ppm") == 0)
        retval = ppm_write(name, width, height, data);
#ifdef JPEG_FOUND
    else if(strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0)
        retval = jpg_write(name, width, height, data);
#endif
#ifdef PNG_FOUND
    else if(strcmp(ext, "png") == 0)
        retval = png_write(name, width, height, data);
#endif
#ifdef TIFF_FOUND
    else if(strcmp(ext, "tif") == 0 || strcmp(ext, "tiff") == 0)
        retval = tiff_write(name, width, height, data);
#endif
    return retval;
}

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
#ifdef JPEG_FOUND
        else if(strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0)
            retval = jpg_valid(name);
#endif
#ifdef PNG_FOUND
        else if(strcmp(ext, "png") == 0)
            retval = png_valid(name);
#endif
#ifdef TIFF_FOUND
        else if(strcmp(ext, "tif") == 0 || strcmp(ext, "tiff") == 0)
            retval = tiff_valid(name);
#endif
    }
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
#ifdef JPEG_FOUND
    else if(strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0)
        retval = jpg_dimensions(name, width, height);
#endif
#ifdef PNG_FOUND
    else if(strcmp(ext, "png") == 0)
        retval = png_dimensions(name, width, height);
#endif
#ifdef JPEG_FOUND
    else if(strcmp(ext, "tif") == 0 || strcmp(ext, "tiff") == 0)
        retval = tiff_dimensions(name, width, height);
#endif
    return retval;
}

char img_read8(const char* name, const char* ext, uint8_t* values,
               uint8_t* alpha)
{
    char retval = 0;
    if(strcmp(ext, "bmp") == 0)
        retval = bmp_read(name, values, alpha);
    else if(strcmp(ext, "tga") == 0)
        retval = tga_read(name, values, alpha);
    else if(strcmp(ext, "ppm") == 0)
        retval = ppm_read(name, values, alpha);
#ifdef JPEG_FOUND
    else if(strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0)
        retval = jpg_read(name, values, alpha);
#endif
#ifdef PNG_FOUND
    else if(strcmp(ext, "png") == 0)
        retval = png_read(name, values, alpha);
#endif
#ifdef TIFF_FOUND
    else if(strcmp(ext, "tif") == 0 || strcmp(ext, "tiff") == 0)
        retval = tiff_read(name, values, alpha);
#endif
    return retval;
}

/*
char img_read32(const char* name, const char* ext, float* values,
                uint8_t* alpha)
{
     Fast explanation:
     - float array required as output, but some functions returns char array
     - image width and height are queried and the support char array is created
     - if the image is not readable the array will have a size of 3 and the
       call to read will fail
     - if the image is not readable at all, a bogus malloc(1) is called
     - the support array is converted to float array if the read was successful
     - in any case it is deallocated, hence the reason of the bogus malloc(1)
       and allocation even if width and height are not determined

    uint8_t* tmp;
    int width = 1;
    int height = 1;
    char retval = 0;
    if(strcmp(ext, "bmp") == 0)
    {
        bmp_dimensions(name, &width, &height);
        tmp = (uint8_t*)malloc(sizeof(float)*width*height*3);
        retval = bmp_read(name, tmp, alpha);
    }
    else if(strcmp(ext, "tga") == 0)
    {
        tga_dimensions(name, &width, &height);
        tmp = (uint8_t*)malloc(sizeof(float)*width*height*3);
        retval = tga_read(name, tmp, alpha);
    }
    else if(strcmp(ext, "ppm") == 0)
    {
        ppm_dimensions(name, &width, &height);
        tmp = (uint8_t*)malloc(sizeof(float)*width*height*3);
        retval = ppm_read(name, tmp, alpha);
    }
#ifdef JPEG_FOUND
    else if(strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0)
    {
        jpg_dimensions(name, &width, &height);
        tmp = (uint8_t*)malloc(sizeof(float)*width*height*3);
        retval = jpg_read(name, tmp, alpha);
    }
#endif
#ifdef PNG_FOUND
    else if(strcmp(ext, "png") == 0)
    {
        png_dimensions(name, &width, &height);
        tmp = (uint8_t*)malloc(sizeof(float)*width*height*3);
        retval = png_read(name, tmp, alpha);
    }
#endif
#ifdef TIFF_FOUND
    else if(strcmp(ext, "tif") == 0 || strcmp(ext, "tiff") == 0)
    {
        tiff_dimensions(name, &width, &height);
        tmp = (uint8_t*)malloc(sizeof(float)*width*height*3);
        retval = tiff_read(name, tmp, alpha);
    }
#endif
    else
    {
        tmp = malloc(1);
    }
    if(retval)
    {
         this step is useless unless new formats with high DPI are added
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
*/
