#ifndef __IMAGE_OUTPUT_HPP__
#define __IMAGE_OUTPUT_HPP__

#include "filter.hpp"
#include "sampler.hpp"
#include "color.hpp"
#include "console.hpp"
#include <cstring>
#include <cmath>
#include <mutex>
#include <cstdio>
struct Pixel
{
    float r;
    float g;
    float b;
    float samples;
};

class ImageOutput
{
public:
    ImageOutput(int width, int height, const char* filename);
    ~ImageOutput();
    
    void addPixel(Sample*, Color*);
    void setFilter(Filter* f);
    void test();
    bool saveImage();
private:
    const int width;
    const int height;
    Filter* f;
    Pixel* image;
    char* filename;
    std::mutex mtx;
};

#endif
