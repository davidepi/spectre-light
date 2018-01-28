//author: Davide Pizzolotto
//license: GNU GPLv3

#include "imageIO.hpp"
#define READ_BUFFER 4096

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

void dimensions_ppm(const char* name, int* width, int* height)
{
    FILE* fin = fopen(name,"rb");
    if(fin!=NULL)
    {
        char magic[2];
        fscanf(fin,"%c%c",magic+0,magic+1);
        if(magic[0]=='P' && (magic[1]=='3' || magic[1]=='6'))
        {
            fscanf(fin,"%d%d",width,height);
        }
        else
        {
            *width = IMAGE_WRONG_MAGIC;
            *height = IMAGE_WRONG_MAGIC;
        }
        fclose(fin);
    }
    else
    {
        *width = IMAGE_NOT_READABLE;
        *height = IMAGE_NOT_READABLE;
    }
}

int read_ppm(const char* name, float* data)
{
    FILE* fin = fopen(name,"rb");
    int retval;
    if(fin!=NULL)
    {
        char magic[2];
        fscanf(fin,"%c%c",magic+0,magic+1);
        //check magic number to determine if ASCII or binary
        if(magic[0]=='P')
        {
            unsigned int width;
            unsigned int height;
            uint16_t depth_short;
            fscanf(fin,"%u%u%hu",&width,&height,&depth_short);
            //not my fucking problem if the depth is > 65536
            //the specification states that the aforementioned value is the max
            float depth = (float)depth_short;
            if(magic[1]=='3') //ASCII
            {
                char val[6];
                uint16_t num_val;
                for(unsigned int i=0;i<width*height*3U;i++)
                {
                    fscanf(fin,"%5s",val);
                    sscanf(val,"%hu",&num_val);
                    data[i]=num_val/depth;
                }
                retval = IMAGE_OK;
            }
            else if(magic[1]=='6') //Binary
            {
                //skip 1 space, after the depth
                //by specification this will ALWAYS be ONE space or newline
                //so no \n\r or other windows shits
                fseek(fin,1,SEEK_CUR);
                if(depth_short<=255)//1 byte per component
                {
                    uint8_t values[READ_BUFFER];
                    unsigned int i=0;
                    size_t read;
                    //read a pixel block of READ_BUFFER size
                    while((read = fread(values,1,READ_BUFFER,fin))>0)
                    {
                        //read more byte than expected from the image dimensions
                        if(i+read>=width*height*3U)
                        {
                            //set the read as the maximum size - written bytes
                            //-1 because arrays are 0 based
                            read = width*height*3U-1U-i;
                        }
                        //everything is normal
                        for(unsigned int j=0;j<read;j++)
                            data[i++] = values[j]/depth;
                    }
                    retval = IMAGE_OK;
                }
                else//2 bytes per component, high depth
                {
                    uint16_t values[READ_BUFFER];
                    unsigned int i=0;
                    size_t read;
                    //read a pixel block of READ_BUFFER size
                    while((read = fread(values,2,READ_BUFFER,fin))>0)
                    {
                        //read is written as size_t*count, but I want only count
                        read/=2;
                        //read more byte than expected from the image dimensions
                        if(i+read>=width*height*3U)
                        {
                            //set the read as the maximum size - written bytes
                            //-1 because arrays are 0 based
                            read = width*height*3U-1U-i;
                        }
                        //everything is normal
                        for(unsigned int j=0;j<read;j++)
                        {
#ifdef IS_BIG_ENDIAN
                            data[i++] = values[j]/depth;
#else
                            data[i++] = swap_endianness(values[j])/depth;
#endif
                        }
                    }
                    retval = IMAGE_OK;
                }
            }
            else
                retval = IMAGE_WRONG_MAGIC;
        }
        else
            retval = IMAGE_WRONG_MAGIC;
        fclose(fin);
    }
    else
        retval = IMAGE_NOT_READABLE;
    return retval;
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

void dimensions_bmp(const char* name, int* width, int* height)
{
    FILE* fin = fopen(name,"rb");
    if(fin!=NULL)
    {
        uint8_t header[26];
        uint32_t* header32bit = (uint32_t*)(header+2);
        fread(header,1,26,fin);
        if(header[0]=='B' && header[1]=='M')
        {
#ifdef IS_BIG_ENDIAN
            *width = swap_endianness(header32bit[4]);
            *height = swap_endianness(header32bit[5]);
#else
            *width = header32bit[4];
            *height = header32bit[5];
#endif
            if(*height<0)
                *height*=-1;
        }
        else
        {
            *width = IMAGE_WRONG_MAGIC;
            *height = IMAGE_WRONG_MAGIC;
        }
        fclose(fin);
    }
    else
    {
        *width = IMAGE_NOT_READABLE;
        *height = IMAGE_NOT_READABLE;
    }
}
