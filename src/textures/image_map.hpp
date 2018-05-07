//  Created by Davide Pizzolotto on 18/05/07.

#ifndef __IMAGE_MAP_HPP__
#define __IMAGE_MAP_HPP__

#include "textures/texture.hpp"
#include "samplers/filter_lanczos.hpp"

struct Texel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

class ImageMap
{
public:
    ImageMap();
    ImageMap(const unsigned char* source, int width, int height);
    ImageMap(const ImageMap &old);
    ImageMap(const ImageMap &old, bool halves);
    ~ImageMap();
    
    bool is_valid()const {return values!=NULL;}
    
private:
    
    const static FilterLanczos downsample_filter;
    unsigned short width;
    unsigned short height;
    Texel* values;
};

#endif
