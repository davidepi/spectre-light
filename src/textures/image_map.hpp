//  Created by Davide Pizzolotto on 18/05/07.

#ifndef __IMAGE_MAP_HPP__
#define __IMAGE_MAP_HPP__

#include "textures/texture.hpp"
#include "samplers/filter_lanczos.hpp"

struct Texel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct Texel32
{
    float r;
    float g;
    float b;
};

class ImageMap
{
public:
    ImageMap();
    ImageMap(int side);
    ImageMap(const uint8_t* source, int side);
    ImageMap(const float* source, int side);
    ImageMap(const ImageMap &old);
    ImageMap(const ImageMap &old, bool halves);
    ~ImageMap();
    
//private:
    unsigned short size;
    bool high_depth;
    union
    {
        Texel* values;
        Texel32* values_high;
    };
};

#endif
