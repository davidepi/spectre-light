#include "textures/image_map.hpp"

static void downsample_box(const Texel* in, Texel* out, unsigned short insize)
{
    unsigned short outsize = insize/2;
    for(int y=0;y<outsize;y++)
    {
        for(int x=0;x<outsize;x++)
        {
            Texel t0 = in[2*y*insize+2*x];
            Texel t1 = in[(2*y+1)*insize+2*x];
            Texel t2 = in[2*y*insize+(2*x+1)];
            Texel t3 = in[(2*y+1)*insize+(2*x+1)];
            out[y*outsize+x].r = (unsigned char)(0.25f*(t0.r+t1.r+t2.r+t3.r));
            out[y*outsize+x].g = (unsigned char)(0.25f*(t0.g+t1.g+t2.g+t3.g));
            out[y*outsize+x].b = (unsigned char)(0.25f*(t0.b+t1.b+t2.b+t3.b));
        }
    }
}

ImageMap::ImageMap()
{
    ImageMap::size = 0;
    ImageMap::values = NULL;
}

ImageMap::ImageMap(int side)
{
    ImageMap::size = side;
    ImageMap::values = NULL;
}

ImageMap::ImageMap(const unsigned char* source, int side)
{
    ImageMap::size = (unsigned short)side;
    ImageMap::values = (Texel*)malloc(sizeof(Texel)*size*size);
    if(values!=NULL)
        values = (Texel*)memcpy(values, source, sizeof(Texel)*size*size);
}

ImageMap::ImageMap(const float* source, int side)
{
    ImageMap::size = (unsigned short)side;
    ImageMap::values = (Texel*)malloc(sizeof(Texel)*size*size);
    if(values!=NULL)
        for(int i=0;i<side*side*3;i+=3)
        {
            values[i/3].r = (unsigned char)(clamp(source[i+0],0.f,1.f)*255.f);
            values[i/3].g = (unsigned char)(clamp(source[i+1],0.f,1.f)*255.f);
            values[i/3].b = (unsigned char)(clamp(source[i+2],0.f,1.f)*255.f);
        }
}

ImageMap::ImageMap(const ImageMap &old)
{
    ImageMap::size = old.size;
    ImageMap::values = (Texel*)malloc(sizeof(Texel)*size*size);
    if(values!=NULL)
        values = (Texel*)memcpy(values, old.values, sizeof(Texel)*size*size);
}

ImageMap::ImageMap(const ImageMap &old, bool halves)
{
    if(!halves)
    {
        ImageMap::size = old.size;
        ImageMap::values = (Texel*)malloc(sizeof(Texel)*size*size);
        if(values!=NULL)
            values = (Texel*)memcpy(values, old.values, sizeof(Texel)*size*size);
    }
    else
    {
        ImageMap::size = old.size/2;
        ImageMap::values = (Texel*)malloc(sizeof(Texel)*size*size);
        if(values!=NULL)
            downsample_box(old.values, values, old.size);
    }
}

ImageMap::~ImageMap()
{
    if(ImageMap::values!=NULL)
        free(ImageMap::values);
}
