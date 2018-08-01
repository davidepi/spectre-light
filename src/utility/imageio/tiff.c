/*  author: Davide Pizzolotto   */
/*  license: MIT                */

#include "tiff.h"

char tiff_write(const char* name, int width, int height, const uint8_t* data)
{
    char retval = 0;
    TIFF* fout;
    TIFFSetWarningHandler(NULL);
    TIFFSetErrorHandler(NULL);
    fout = TIFFOpen(name, "w");
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
    TIFF* fin;
    TIFFSetWarningHandler(NULL);
    TIFFSetErrorHandler(NULL);
    fin = TIFFOpen(name, "r");
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
    TIFF* fin;
    TIFFSetWarningHandler(NULL);
    TIFFSetErrorHandler(NULL);
    fin = TIFFOpen(name, "r");
    if(fin != NULL)
    {
        retval |= TIFFGetField(fin, TIFFTAG_IMAGEWIDTH, width);
        retval &= TIFFGetField(fin, TIFFTAG_IMAGELENGTH, height);
        TIFFClose(fin);
    }
    return retval;
}

char tiff_read(const char* name, uint8_t* values, uint8_t* alpha)
{
    char retval = 0;
    TIFF* fin;
    TIFFSetWarningHandler(NULL);
    TIFFSetErrorHandler(NULL);
    fin = TIFFOpen(name, "r");
    if(fin != NULL)
    {
        int width = 0;
        int height = 0;
        int channels = 0;
        uint32_t* data;
        retval |= TIFFGetField(fin, TIFFTAG_IMAGEWIDTH, &width);
        retval &= TIFFGetField(fin, TIFFTAG_IMAGELENGTH, &height);
        retval &= TIFFGetField(fin, TIFFTAG_SAMPLESPERPIXEL, &channels);
        data = (uint32_t*)_TIFFmalloc(sizeof(uint32_t)*width*height);
        /* The first retval is used to ensure channels/width/height are valid */
        if(retval && (channels == 3 || channels == 4) &&
           TIFFReadRGBAImage(fin, width, height, data, 0))
        {
            int x;
            int y;
            const char has_alpha = channels == 4;
            /* reorder in top-down order and process alpha */
            for(y = 0; y<height; y++)
            {
                for(x = 0; x<width; x++)
                {
                    int index = y*width+x;
                    int tif_index = (height-1-y)*width+x;
                    values[index*3+0] = (uint8_t)TIFFGetR(data[tif_index]);
                    values[index*3+1] = (uint8_t)TIFFGetG(data[tif_index]);
                    values[index*3+2] = (uint8_t)TIFFGetB(data[tif_index]);
                    if(has_alpha)
                        alpha[index] = (uint8_t)TIFFGetA(data[tif_index]);
                }
            }
            retval = has_alpha?2:1;
        }
        else
            retval = 0;
        _TIFFfree(data);
        TIFFClose(fin);
    }
    return retval;
}
