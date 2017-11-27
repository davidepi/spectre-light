#include "imageIO.hpp"

bool savePPM(const char* name, int width, int height, const uint8_t* array)
{
    FILE* fout = fopen(name,"wb"); //save as ppm
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

bool saveBMP(const char*, int, int, const uint8_t*)
{
    return false;
}
