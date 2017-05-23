#ifndef __IMAGE_OUTPUT_HPP__
#define __IMAGE_OUTPUT_HPP__

#include "filter.hpp"
#include "sampler.hpp"
#include "color.hpp"
#include <cstring>

struct Pixel
{
    float r;
    float g;
    float b;
    int samples;
};

class ImageOutput
{
public:
    ImageOutput(int width, int height, const char* filename);
    ~ImageOutput();
    
    void addPixel(Sample*, Color*);
    void setFilter(Filter* f);
    bool saveImage()const;
private:
    Filter* f;
    Pixel* image;
    char* filename;
};

#endif
