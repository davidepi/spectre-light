//author: Davide Pizzolotto
//license: GNU GPLv3

#include "textures/image_map.hpp"

const FilterLanczos lowpass_filter = FilterLanczos(3.f);

static void downsample(const Texel* in, Texel* out, unsigned short insize,
                       bool hqfilter);

static void downsample(const Texel32* in, Texel32* out, unsigned short insize,
                       bool hqfilter);

ImageMap::ImageMap(const char* src): path(src)
{
    init();
}

ImageMap::ImageMap(const File& src): path(src)
{
    init();
}

void ImageMap::init()
{
    maps_no = 0;
    values = NULL;
    high_depth = false;
    if(path.readable())
    {
        int width;
        int height;
        dimensions_RGB(path.absolute_path(), path.extension(), &width, &height);
        if(width == height && (height & (height-1)) == 0)
        {
            int res;
            size = (unsigned short)width;
            maps_no = (unsigned char)(1+(int)log2f(width));
            values = (Texel**)malloc(sizeof(void*)*maps_no);
            float* data = (float*)malloc(width*height*3*sizeof(float));
            res = read_RGB(path.absolute_path(), path.extension(), data, NULL);
            if(res<0)
                Console.critical(MESSAGE_TEXTURE_ERROR, path.absolute_path());
            else
            {
                //check if image fits in 8bit per pixel
                for(int i=0;i<width*height*3;i++)
                    if(data[i]>1.f || data[i]<0.f)
                    {
                        high_depth = true;
                        break; //no point in continuing
                    }
                if(high_depth)
                {
                    //exploits the fact that Texel32 is equal to an array of flt
                    values_high[0] = (Texel32*)data;
                    //calculate pyramid
                    for(int i=1;i<maps_no;i++)
                    {
                        unsigned short side = powf(width,1/(int)exp2f(i));
                        values_high[i] = (Texel32*)malloc(sizeof(Texel32)*
                                                          side*side);
                        //side *2 because downsample wants the INPUT size
                        downsample(values_high[i-1], values_high[i],
                                   side<<1, false);
                    }
                }
                else
                {
                    //recalculate every value
                    values[0] = (Texel*)malloc(sizeof(Texel)*width*height);
                    int j = 0;
                    for(int i=0;i<width*height;i++)
                    {
                        values[0][i].r = (unsigned char)(data[j++]*255.f);
                        values[0][i].g = (unsigned char)(data[j++]*255.f);
                        values[0][i].b = (unsigned char)(data[j++]*255.f);
                    }
                    //calculate pyramid
                    for(int i=1;i<maps_no;i++)
                    {
                        unsigned short side = powf(width,1/(int)exp2f(i));
                        values[i] = (Texel*)malloc(sizeof(Texel)*side*side);
                        //side *2 because downsample wants the INPUT size
                        downsample(values[i-1], values[i], side<<1, false);
                    }
                    free(data);
                }
            }
        }
        else
            Console.critical(MESSAGE_TEXTURE_POWER2, path.absolute_path());
    }
    else
        //should be checked by parser, but a check at construction time is ok
        Console.critical(MESSAGE_TEXTURE_ERROR, path.absolute_path());
}

ImageMap::~ImageMap()
{
    for(int i=0;i<maps_no;i++)
        free(values[i]);
    //used only in testing, where a critical error does not initialize anything
    //but also does not kill the program
    if(values!=NULL)
        free(values);
}

static void downsample(const Texel32* in, Texel32* out,
                       unsigned short input_side, bool hqfilter)
{
    unsigned short output_side = (unsigned short)(input_side/2);
    int range_x = (int)lowpass_filter.range_x;
    int range_y = (int)lowpass_filter.range_y;
    float* weights;
    if(hqfilter)
    {
        memset(out, 0, sizeof(Texel32)*output_side*output_side);
        weights = (float*)malloc(sizeof(float)*output_side*output_side);
        memset(weights, 0, sizeof(float)*output_side*output_side);
    }
    for(int y = 0; y<output_side; y++)
    {
        for(int x = 0; x<output_side; x++)
        {
            Texel32 t0 = in[2*y*input_side+2*x];
            Texel32 t1 = in[(2*y+1)*input_side+2*x];
            Texel32 t2 = in[2*y*input_side+(2*x+1)];
            Texel32 t3 = in[(2*y+1)*input_side+(2*x+1)];
            if(!hqfilter) //single pixel (no filter)
            {
                int pixel = y*output_side+x;
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
                        if(val_x<0 || val_x>=output_side || val_y<0 ||
                           val_y>=output_side)
                            continue;
                        int pixel = val_y*output_side+val_x;
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
        for(int i = 0; i<output_side*output_side; i++)
        {
            float weight = 1.f/weights[i];
            out[i].r = max(out[i].r, 0.f)*weight;
            out[i].g = max(out[i].g, 0.f)*weight;
            out[i].b = max(out[i].b, 0.f)*weight;
        }
        free(weights);
    }
}

static void downsample(const Texel* in, Texel* out,
                       unsigned short input_side, bool hqfilter)
{
    unsigned short output_side = (unsigned short)(input_side/2);
    int range_x = (int)lowpass_filter.range_x;
    int range_y = (int)lowpass_filter.range_y;
    Texel32* tmpout;
    float* weights;
    if(hqfilter)
    {
        weights = (float*)malloc(sizeof(float)*output_side*output_side);
        tmpout = (Texel32*)malloc(sizeof(Texel32)*output_side*output_side);
        memset(tmpout, 0, sizeof(Texel32)*output_side*output_side);
        memset(weights, 0, sizeof(float)*output_side*output_side);
    }
    for(int y = 0; y<output_side; y++)
    {
        for(int x = 0; x<output_side; x++)
        {
            Texel t0 = in[2*y*input_side+2*x];
            Texel t1 = in[(2*y+1)*input_side+2*x];
            Texel t2 = in[2*y*input_side+(2*x+1)];
            Texel t3 = in[(2*y+1)*input_side+(2*x+1)];
            if(!hqfilter) //single pixel (no filter)
            {
                int pixel = y*output_side+x;
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
                        if(val_x<0 || val_x>=output_side || val_y<0 ||
                           val_y>=output_side)
                            continue;
                        int pixel = val_y*output_side+val_x;
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
        for(int i = 0; i<output_side*output_side; i++)
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
