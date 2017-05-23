#include "image_output.hpp"

ImageOutput::ImageOutput(int width, int height, const char* fn)
{
    ImageOutput::image = (Pixel*)malloc(sizeof(Pixel)*width*height);
    ImageOutput::filename = NULL;
    if(fn != NULL)
    {
        ImageOutput::filename = (char*)malloc(sizeof(char)*(strlen(fn)+1));
        memcpy(filename,fn,sizeof(char)*(strlen(fn)+1));
    }
}

ImageOutput::~ImageOutput()
{
    free(ImageOutput::image);
}

void ImageOutput::addPixel(Sample* s, Color* c)
{
    
}

void ImageOutput::setFilter(Filter* f)
{
    ImageOutput::f = dynamic_cast<Filter*>(f);
}

bool ImageOutput::saveImage()const
{
    return false;
}
