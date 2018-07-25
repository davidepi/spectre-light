/*  author: Davide Pizzolotto   */
/*  license: MIT                */

#include "tiff.h"

char tiff_write(const char* name, int width, int height, const uint8_t* data)
{
    char retval = 0;
    TIFF* fout = TIFFOpen(name, "w");
    if(fout != NULL)
    {
        int y = 0;
        uint8_t* row;
        TIFFSetField(fout, TIFFTAG_IMAGEWIDTH, width);
        TIFFSetField(fout, TIFFTAG_IMAGELENGTH, height);
        TIFFSetField(fout, TIFFTAG_SAMPLESPERPIXEL, 3);
        TIFFSetField(fout, TIFFTAG_BITSPERSAMPLE, 8);
        TIFFSetField(fout, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField(fout, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(fout, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
        row = (uint8_t*)_TIFFmalloc(TIFFScanlineSize(fout));
        while(y<height)
        {
            row = memcpy(row, data+y*width*3, width*3);
            if(TIFFWriteScanline(fout, row, y++, 0)<0)
                break;
        }
        _TIFFfree(row);
        TIFFClose(fout);
        retval = y == height;
    }
    return retval;
}

char tiff_valid(const char* name)
{
    char retval = 0;
    TIFF* fin = TIFFOpen(name, "r");
    if(fin != NULL)
    {
        retval = 1;
        TIFFClose(fin);
    }
    return retval;
}

char tiff_dimensions(const char* name, int* width, int* height)
{
    char retval = 0;
    TIFF* fin = TIFFOpen(name, "r");
    if(fin != NULL)
    {
        *width = TIFFGetField(fin, TIFFTAG_IMAGEWIDTH);
        *height = TIFFGetField(fin, TIFFTAG_IMAGELENGTH);
        retval = 1;
        TIFFClose(fin);
    }
    return retval;
}

char tiff_read(const char* name, uint8_t* values, uint8_t* alpha)
{
    char retval = 0;
    TIFF* fin = TIFFOpen(name, "r");
    if(fin != NULL)
    {
        int width;
        int height;
        uint32_t* data;
        TIFFGetField(fin, TIFFTAG_IMAGEWIDTH, &width);
        TIFFGetField(fin, TIFFTAG_IMAGELENGTH, &height);
        data = (uint32_t*)_TIFFmalloc(sizeof(uint32_t)*width*height);
        if(TIFFReadRGBAImage(fin, width, height, data, 0))
        {
            int x;
            int y;
            const int has_alpha =
                    TIFFGetField(fin, TIFFTAG_SAMPLESPERPIXEL) == 4;
            /* reorder in top-down order and process alpha */
            for(y = 0; y<height; y++)
            {
                for(x = 0; x<width; x++)
                {
                    int index = y*width+x;
                    values[index*3+0] = (uint8_t)TIFFGetR(data[index]);
                    values[index*3+1] = (uint8_t)TIFFGetG(data[index]);
                    values[index*3+2] = (uint8_t)TIFFGetB(data[index]);
                    if(has_alpha)
                        alpha[index] = (uint8_t)TIFFGetA(data[index]);
                }
            }
            retval = 1;
        }
        _TIFFfree(data);
        TIFFClose(fin);
    }
    return retval;
}
