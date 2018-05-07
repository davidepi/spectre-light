#include "textures/image_map.hpp"

ImageMap::filter = FilterLanczos(2.f);

ImageMap::ImageMap()
{
    ImageMap::width = 0;
    ImageMap::height = 0;
    ImageMap::values = NULL;
}

ImageMap::ImageMap(const unsigned char* source, int width, int height)
{
    ImageMap::width = (unsigned short)width;
    ImageMap::height = (unsigned short)height;
    ImageMap::values = (Texel*)malloc(sizeof(Texel)*width*height);
    if(values!=NULL)
        values = memcpy(values, source, sizeof(Texel)*width*height);
}

ImageMap::ImageMap(const ImageMap &old)
{
    ImageMap::width = old.width;
    ImageMap::height = old.height;
    ImageMap::values = (Texel*)malloc(sizeof(Texel)*width*height);
    if(values!=NULL)
        values = memcpy(values, old.values, sizeof(Texel)*width*height);
}

ImageMap::ImageMap(const ImageMap &old, bool halves)
{
    if(!halves)
    {
        ImageMap::width = old.width;
        ImageMap::height = old.height;
        ImageMap::values = (Texel*)malloc(sizeof(Texel)*width*height);
        if(values!=NULL)
            values = memcpy(values, old.values, sizeof(Texel)*width*height);
    }
    else
    {
        ImageMap::width = old.width/2;
        ImageMap::height = old.height/2;
        ImageMap::values = (Texel*)malloc(sizeof(Texel)*width*height);
        if(values!=NULL)
            //TODO: resample
    }
}

ImageMap::~ImageMap()
{
    if(ImageMap::values!=NULL)
        free(ImageMap::values)
}
