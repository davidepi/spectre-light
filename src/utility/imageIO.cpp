//author: Davide Pizzolotto
//license: GNU GPLv3

#include "imageIO.hpp"

bool save_ppm(const char* name, int width, int height, const uint8_t* array)
{
    FILE* fout = fopen(name,"wb");
    if(fout != NULL)
    {
        fprintf(fout,"P6 %d %d 255 ",width,height);
        fwrite(array, sizeof(uint8_t), (size_t)(width*height*3), fout);
        fclose(fout);
        return true;
    }
    else
    {
        Console.critical(MESSAGE_W_DENIED_RC);
        return false;
    }
}

bool save_bmp(const char* name, int width, int height, const uint8_t* data)
{
    FILE* fout = fopen(name,"wb");
    if(fout != NULL)
    {
        int image_size = width*height*3+54;
        uint8_t header[54];
        uint32_t* header32bit;
        uint16_t* header16bit;

#ifndef IS_BIG_ENDIAN
        //file header
        header[0] = 'B'; //magic numbers
        header[1] = 'M';
        header32bit = (uint32_t*)(header+2);
        header32bit[0] = image_size; //file size
        header32bit[1] = 0; //reserved
        header32bit[2] = 54; //data section offset

        //image header
        header32bit[3] = 40; //image header size
        header32bit[4] = width; //image width
        header32bit[5] = -height; //image height, negative for top-bottom order
        header16bit = (uint16_t*)(header+26);
        header16bit[0] = 1; //must be 1
        header16bit[1] = 24; //color depth
        header32bit = (uint32_t*)(header+30);
        header32bit[0] = 0; //compression
        header32bit[1] = 0; //uncompressed size of the image data
        header32bit[2] = 0; //preferred horizontal res in pixel per meter
        header32bit[3] = 0; //preferred vertical res in pixel per meter
        header32bit[4] = 0; //maximum number of colors in indexed image
        header32bit[5] = 0; //colors considered important
#else
        header[0] = 'B';
        header[1] = 'M';
        header32bit = (uint32_t*)(header+2);
        header32bit[0] = swap_endianness(image_size);
        header32bit[1] = 0;
        header32bit[2] = swap_endianness(54);
        header32bit[3] = swap_endianness(40);
        header32bit[4] = swap_endianness(width);
        header32bit[5] = swap_endianness(-height);
        header16bit = (uint16_t*)(header+26);
        header16bit[0] = swap_endianness(1);
        header16bit[1] = swap_endianness(24);
        header32bit = (uint32_t*)(header+30);
        header32bit[0] = 0;
        header32bit[1] = 0;
        header32bit[2] = 0;
        header32bit[3] = 0;
        header32bit[4] = 0;
        header32bit[5] = 0;
#endif

        //color table : EMPTY since it is not indexed
        //pixel data already in data
        //write the header
        fwrite(header, sizeof(uint8_t), (size_t)(54), fout);
        //write the data
#ifndef IS_BIG_ENDIAN
        char pixel[3];
        int i = 0;
        while(i<width*height*3)
        {
            pixel[2] = data[i++];
            pixel[1] = data[i++];
            pixel[0] = data[i++];
            fwrite(pixel,sizeof(uint8_t),(size_t)3,fout);
        }
#else
        fwrite(data, sizeof(uint8_t), (size_t)(width*height*3), fout);
#endif
        fclose(fout);
        return true;
    }
    else
    {
        Console.critical(MESSAGE_W_DENIED_RC);
        return false;
    }
}
