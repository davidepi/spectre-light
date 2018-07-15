#include "ppm.h"

#define READ_BUFFER 4096
#define CLAMP(x,y,z) x<0?x:x>z?z:x
#define UNUSED(x) (void)(x)

char ppm_save(const char* name, int width, int height, const uint8_t* array)
{
    FILE* fout = fopen(name, "wb");
    char retval = 0;
    if(fout != NULL)
    {
        fprintf(fout, "P6 %d %d 255 ", width, height);
        fwrite(array, sizeof(uint8_t), width*height*3, fout);
        fclose(fout);
        retval = 1;
    }
    return retval;
}

char ppm_dimensions(const char* name, int* width, int* height)
{
    FILE* fin = fopen(name, "rb");
    char retval = 0;
    if(fin != NULL)
    {
        char magic[2];
        fscanf(fin, "%c%c", magic+0, magic+1);
        if(magic[0] == 'P' && (magic[1] == '3' || magic[1] == '6'))
        {
            fscanf(fin, "%d%d", width, height);
            retval = 1;
        }
        fclose(fin);
    }
    return retval;
}

char ppm_read(const char* name, uint8_t* values, uint8_t* alpha)
{
    UNUSED(alpha); //no alpha in a PPM image
    FILE* fin = fopen(name, "rb");
    char retval = 0;
    if(fin != NULL)
    {
        char magic[2];
        fscanf(fin, "%c%c", magic+0, magic+1);
        //check magic number to determine if ASCII or binary
        if(magic[0] == 'P')
        {
            unsigned int width;
            unsigned int height;
            uint16_t depth_short;
            fscanf(fin, "%u%u%hu", &width, &height, &depth_short);
            //not my fucking problem if the depth is > 65536
            //the specification states that the aforementioned value is the max
            float depth = (float)depth_short;
            if(magic[1] == '3') //ASCII
            {
                char val[6];
                uint16_t num_val;
                for(unsigned int i = 0; i<width*height*3U; i++)
                {
                    fscanf(fin, "%5s", val);
                    sscanf(val, "%hu", &num_val);
                    values[i] = (uint8_t)(CLAMP((num_val/depth),0.f,1.f)*255);
                }
                retval = 1;
            }
            else if(magic[1] == '6') //Binary
            {
                //skip 1 space, after the depth
                //by specification this will ALWAYS be ONE space or newline
                //so no \n\r or other windows shits
                fseek(fin, 1, SEEK_CUR);
                if(depth_short<=255)//1 byte per component
                {
                    uint8_t buffer[READ_BUFFER];
                    unsigned int i = 0;
                    size_t read;
                    //read a pixel block of READ_BUFFER size
                    while((read = fread(buffer, 1, READ_BUFFER, fin))>0)
                    {
                        //read more byte than expected from the image dimensions
                        if(i+read>=width*height*3U)
                        {
                            //set the read as the maximum size - written bytes
                            read = width*height*3U-i;
                        }
                        //everything is normal
                        for(unsigned int j = 0; j<read; j++)
                            values[i++] = (uint8_t)((buffer[j]/depth)*255);
                    }
                }
                else//2 bytes per component, high depth
                {
                    uint16_t buffer[READ_BUFFER];
                    unsigned int i = 0;
                    size_t read;
                    //read a pixel block of READ_BUFFER size
                    while((read = fread(buffer, 2, READ_BUFFER, fin))>0)
                    {
                        //read is written as size_t*count, but I want only count
                        read /= 2;
                        //read more byte than expected from the image dimensions
                        if(i+read>=width*height*3U)
                        {
                            //set the read as the maximum size - written bytes
                            read = width*height*3U-i;
                        }
                        //everything is normal
                        for(unsigned int j = 0; j<read; j++)
                        {
                            uint16_t num_val = ENDIANNESS_BIG16(buffer[j]);
                            values[i++] = (uint8_t)(CLAMP(num_val/depth,0.f,1.f)
                                                    *255);
                        }
                    }
                }
                retval = 1;
            }
        }
        fclose(fin);
    }
    return retval;
}
