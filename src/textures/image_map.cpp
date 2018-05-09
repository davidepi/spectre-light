//author: Davide Pizzolotto
//license: GNU GPLv3

#include "textures/image_map.hpp"

const FilterLanczos lowpass_filter = FilterLanczos(3.f);

static void downsample(const Texel* in, Texel* out, unsigned short insize,
                       bool hqfilter);

static void downsample(const Texel32* in, Texel32* out, unsigned short insize,
                       bool hqfilter);

ImageMap::ImageMap()
{
    ImageMap::size = 0;
    ImageMap::high_depth = false;
    ImageMap::values = NULL;
}

void ImageMap::alloc(const uint8_t* source, int side)
{
    ImageMap::size = (unsigned short)side;
    ImageMap::high_depth = false;
    ImageMap::values = (Texel*)malloc(sizeof(Texel)*size*size);
    if(values != NULL)
        values = (Texel*)memcpy(values, source, sizeof(Texel)*size*size);
}

void ImageMap::alloc(const float* source, int side)
{
    ImageMap::size = (unsigned short)side;
    float min_val = 0.f;
    float max_val = 1.f;

    //checks if the image could fit in a 24 bit representation
    for(int i = 0; i<side*side*3; i++)
    {
        min_val = min(min_val, source[i]);
        max_val = max(max_val, source[i]);
    }
    if(min_val == 0.f && max_val == 1.f)
    {
        ImageMap::high_depth = false;
        ImageMap::values = (Texel*)malloc(sizeof(Texel)*size*size);
        //convert every value to 24 bit depth
        if(values != NULL)
        {
            for(int i = 0; i<side*side*3; i += 3)
            {
                values[i/3].r = (unsigned char)(source[i+0]*255.f);
                values[i/3].g = (unsigned char)(source[i+1]*255.f);
                values[i/3].b = (unsigned char)(source[i+2]*255.f);
            }
        }
    }
    else
    {
        ImageMap::high_depth = true;
        ImageMap::values_high = (Texel32*)malloc(sizeof(Texel32)*size*size);
        if(values_high != NULL)
            memcpy(values_high, source, sizeof(Texel32)*size*size);
    }
}

ImageMap::ImageMap(const ImageMap& old)
{
    ImageMap::size = old.size;
    ImageMap::high_depth = old.high_depth;
    if(high_depth)
    {
        ImageMap::values_high = (Texel32*)malloc(sizeof(Texel32)*size*size);
        if(values_high != NULL)
            values_high = (Texel32*)memcpy(values, old.values,
                                           sizeof(Texel32)*size*size);
    }
    else
    {
        ImageMap::values = (Texel*)malloc(sizeof(Texel)*size*size);
        if(values != NULL)
            values = (Texel*)memcpy(values, old.values,
                                    sizeof(Texel)*size*size);
    }
}

void ImageMap::alloc_mipmap(const ImageMap& old, bool hqfilter)
{
    ImageMap::size = (unsigned short)(old.size/2);
    ImageMap::high_depth = old.high_depth;
    if(high_depth)
    {
        ImageMap::values_high = (Texel32*)malloc(sizeof(Texel32)*size*size);
        if(values_high != NULL)
            downsample(old.values_high, values_high, old.size, hqfilter);
    }
    else
    {
        ImageMap::values = (Texel*)malloc(sizeof(Texel)*size*size);
        if(values != NULL)
            downsample(old.values, values, old.size, hqfilter);
    }
}

void ImageMap::dealloc()
{
    if(ImageMap::values == NULL)
        free(ImageMap::values);
    ImageMap::values = NULL;
}

ImageMap::~ImageMap()
{
    if(ImageMap::values != NULL)
        free(ImageMap::values);
}

ColorRGB ImageMap::val(unsigned short x, unsigned short y) const
{
    int pixel = y*size+x;
    ColorRGB retval;
    if(!high_depth)
        retval = ColorRGB(values[pixel].r,
                          values[pixel].g,
                          values[pixel].b);
    else
        retval = ColorRGB(values_high[pixel].r,
                          values_high[pixel].g,
                          values_high[pixel].b);
    return retval;
}

static void downsample(const Texel32* in, Texel32* out, unsigned short insize,
                       bool hqfilter)
{
    unsigned short outsize = (unsigned short)(insize/2);
    int range_x = (int)lowpass_filter.range_x;
    int range_y = (int)lowpass_filter.range_y;
    float* weights;
    if(hqfilter)
    {
        memset(out, 0, sizeof(Texel32)*outsize*outsize);
        weights = (float*)malloc(sizeof(float)*outsize*outsize);
        memset(weights, 0, sizeof(float)*outsize*outsize);
    }
    for(int y = 0; y<outsize; y++)
    {
        for(int x = 0; x<outsize; x++)
        {
            Texel32 t0 = in[2*y*insize+2*x];
            Texel32 t1 = in[(2*y+1)*insize+2*x];
            Texel32 t2 = in[2*y*insize+(2*x+1)];
            Texel32 t3 = in[(2*y+1)*insize+(2*x+1)];
            if(!hqfilter) //single pixel (no filter)
            {
                int pixel = y*outsize+x;
                out[pixel].r = 0.25f*(t0.r+t1.r+t2.r+t3.r);
                out[pixel].g = 0.25f*(t0.g+t1.g+t2.g+t3.g);
                out[pixel].b = 0.25f*(t0.b+t1.b+t2.b+t3.b);
            }
            else //filter also neighbours (lanczos filter)
            {
                for(int oy = -range_y; oy<=range_y; oy++)
                    for(int ox = -range_x; ox<=range_x; ox++)
                    {
                        //compute values of x and y
                        int val_x = x+ox;
                        int val_y = y+oy;
                        //if they are outside the image, skip this pixel
                        if(val_x<0 || val_x>=outsize || val_y<0 ||
                           val_y>=outsize)
                            continue;
                        int pixel = val_y*outsize+val_x;
                        float weight = lowpass_filter.weight((float)ox,
                                                             (float)oy);
                        out[pixel].r += 0.25f*(t0.r+t1.r+t2.r+t3.r)*weight;
                        out[pixel].g += 0.25f*(t0.g+t1.g+t2.g+t3.g)*weight;
                        out[pixel].b += 0.25f*(t0.b+t1.b+t2.b+t3.b)*weight;
                        weights[pixel] += weight;
                    }
            }
        }
    }
    if(hqfilter)
    {
        //reweights samples
        for(int i = 0; i<outsize*outsize; i++)
        {
            float weight = 1.f/weights[i];
            out[i].r = max(out[i].r, 0.f)*weight;
            out[i].g = max(out[i].g, 0.f)*weight;
            out[i].b = max(out[i].b, 0.f)*weight;
        }
        free(weights);
    }
}

static void downsample(const Texel* in, Texel* out, unsigned short insize,
                       bool hqfilter)
{
    unsigned short outsize = (unsigned short)(insize/2);
    int range_x = (int)lowpass_filter.range_x;
    int range_y = (int)lowpass_filter.range_y;
    Texel32* tmpout;
    float* weights;
    if(hqfilter)
    {
        weights = (float*)malloc(sizeof(float)*outsize*outsize);
        tmpout = (Texel32*)malloc(sizeof(Texel32)*outsize*outsize);
        memset(tmpout, 0, sizeof(Texel32)*outsize*outsize);
        memset(weights, 0, sizeof(float)*outsize*outsize);
    }
    for(int y = 0; y<outsize; y++)
    {
        for(int x = 0; x<outsize; x++)
        {
            Texel t0 = in[2*y*insize+2*x];
            Texel t1 = in[(2*y+1)*insize+2*x];
            Texel t2 = in[2*y*insize+(2*x+1)];
            Texel t3 = in[(2*y+1)*insize+(2*x+1)];
            if(!hqfilter) //single pixel (no filter)
            {
                int pixel = y*outsize+x;
                out[pixel].r = (uint8_t)(0.25f*(t0.r+t1.r+t2.r+t3.r));
                out[pixel].g = (uint8_t)(0.25f*(t0.g+t1.g+t2.g+t3.g));
                out[pixel].b = (uint8_t)(0.25f*(t0.b+t1.b+t2.b+t3.b));
            }
            else //filter also neighbours (lanczos filter)
            {
                for(int oy = -range_y; oy<=range_y; oy++)
                    for(int ox = -range_x; ox<=range_x; ox++)
                    {
                        //compute values of x and y
                        int val_x = x+ox;
                        int val_y = y+oy;
                        //if they are outside the image, skip this pixel
                        if(val_x<0 || val_x>=outsize || val_y<0 ||
                           val_y>=outsize)
                            continue;
                        int pixel = val_y*outsize+val_x;
                        float weight = lowpass_filter.weight((float)ox,
                                                             (float)oy);
                        tmpout[pixel].r += 0.25f*(t0.r+t1.r+t2.r+t3.r)*weight;
                        tmpout[pixel].g += 0.25f*(t0.g+t1.g+t2.g+t3.g)*weight;
                        tmpout[pixel].b += 0.25f*(t0.b+t1.b+t2.b+t3.b)*weight;
                        weights[pixel] += weight;
                    }
            }
        }
    }
    if(hqfilter)
    {
        //reweights samples
        for(int i = 0; i<outsize*outsize; i++)
        {
            float weight = 1.f/weights[i];
            out[i].r = (uint8_t)clamp(tmpout[i].r*weight, 0.f, 255.f);
            out[i].g = (uint8_t)clamp(tmpout[i].g*weight, 0.f, 255.f);
            out[i].b = (uint8_t)clamp(tmpout[i].b*weight, 0.f, 255.f);
        }
        free(tmpout);
        free(weights);
    }
}
