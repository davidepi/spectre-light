//author: Davide Pizzolotto
//license: GNU GPLv3

#include "textures/image_map.hpp"

const FilterLanczos lowpass_filter = FilterLanczos(3.f);

static void downsample(const Texel* in, Texel* out, unsigned short insize,
                       bool hqfilter);

static void downsample(const Texel32* in, Texel32* out, unsigned short insize,
                       bool hqfilter);

static ColorRGB bilinear(float u, float v, unsigned short side, Texel* vals);

static ColorRGB bilinear(float u, float v, unsigned short side, Texel32* vals);

static ColorRGB ewa(float u, float v, float dudx, float dvdx, float dudy,
                    float dvdy, unsigned short side, Texel* vals);

ImageMap::ImageMap(const char* src):path(src)
{
    init();
}

ImageMap::ImageMap(const File& src):path(src)
{
    init();
}

void ImageMap::init()
{
    maps_no = 0;
    values = NULL;
    high_depth = false;
    filter = &ImageMap::unfiltered;
    if(path.readable())
    {
        int width;
        int height;
        dimensions_RGB(path.absolute_path(), path.extension(), &width, &height);
        if(width == height && (height & (height-1)) == 0)
        {
            int res;
            maps_no = (unsigned char)(1+(int)log2f(width));
            side = (unsigned short*)malloc(sizeof(unsigned short*)*maps_no);
            side[0] = (unsigned short)width;
            values = (Texel**)malloc(sizeof(void*)*maps_no);
            float* data = (float*)malloc(width*height*3*sizeof(float));
            res = read_RGB(path.absolute_path(), path.extension(), data, NULL);
            if(res<0)
                Console.critical(MESSAGE_TEXTURE_ERROR, path.absolute_path());
            else
            {
                //check if image fits in 8bit per pixel
                for(int i = 0; i<width*height*3; i++)
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
                    for(int i = 1; i<maps_no; i++)
                    {
                        unsigned short c_side = side[i-1] >> 1;
                        side[i] = c_side;
                        values_high[i] = (Texel32*)malloc(sizeof(Texel32)*
                                                          c_side*c_side);
                        //side *2 because downsample wants the INPUT size
                        downsample(values_high[i-1], values_high[i],
                                   side[i-1], false);
                    }
                }
                else
                {
                    //recalculate every value
                    values[0] = (Texel*)malloc(sizeof(Texel)*width*height);
                    int j = 0;
                    for(int i = 0; i<width*height; i++)
                    {
                        values[0][i].r = (unsigned char)(data[j++]*255.f);
                        values[0][i].g = (unsigned char)(data[j++]*255.f);
                        values[0][i].b = (unsigned char)(data[j++]*255.f);
                    }
                    //calculate pyramid
                    for(int i = 1; i<maps_no; i++)
                    {
                        unsigned short c_side = side[i-1] >> 1;
                        side[i] = c_side;
                        values[i] = (Texel*)malloc(sizeof(Texel)*c_side*c_side);
                        //side *2 because downsample wants the INPUT size
                        downsample(values[i-1], values[i], side[i-1], false);
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
    for(int i = 0; i<maps_no; i++)
        free(values[i]);
    //used only in testing, where a critical error does not initialize anything
    //but also does not kill the program
    if(values != NULL)
        free(values);
}

void ImageMap::set_filter(TextureFilter_t type)
{
    switch(type)
    {
        case UNFILTERED: filter = &ImageMap::unfiltered;break;
        case TRILINEAR: filter = &ImageMap::trilinear_iso;break;
        case EWA: filter = &ImageMap::trilinear_ewa;break;
    }
}

ColorRGB ImageMap::unfiltered(float u, float v, float, float,
                              float, float) const
{
    unsigned short x = (unsigned short)(u*side[0]-0.5f);
    unsigned short y = (unsigned short)(v*side[0]-0.5f);
    ColorRGB res;
    if(high_depth)
    {

        Texel32 hit = values_high[0][y*side[0]+x];
        res = ColorRGB(hit.r,hit.g,hit.b);
    }
    else
    {
        Texel hit = values[0][y*side[0]+x];
        res = ColorRGB(hit.r,hit.g,hit.b);
    }
    return res;
}

ColorRGB ImageMap::trilinear_iso(float u, float v, float dudx, float dvdx,
                             float dudy, float dvdy)const
{
    float width = min(dudx*dudx+dvdx*dvdx, dudy*dudy+dvdy*dvdy);
    //ensures that log2 doesn't give unwanted results
    width = max(width, 1e-5f);
    //choose mipmap
    float chosen = max(0.f,maps_no-1+log2f(width));
    if(chosen<=0.f) //use full size map
        return high_depth?bilinear(u, v, side[0], values_high[0])
                         :bilinear(u, v, side[0], values[0]);
    else if(chosen>maps_no-1) //return the single, most distant pixel
    {
        if(high_depth)
            return ColorRGB(values_high[maps_no-1][0].r,
                                     values_high[maps_no-1][0].g,
                                     values_high[maps_no-1][0].b);
        else
            return ColorRGB(values[maps_no-1][0].r,
                                     values[maps_no-1][0].g,
                                     values[maps_no-1][0].b);
    }
    else //perform trilinear interpolation
    {
        uint8_t chosen_below = (uint8_t)chosen;
        float decimal = chosen-chosen_below;
        if(high_depth)
        {
            ColorRGB p0 = bilinear(u, v, side[chosen_below],
                                   values_high[chosen_below]);
            ColorRGB p1 = bilinear(u, v, side[chosen_below+1],
                                   values_high[chosen_below+1]);
            const float other_decimal = 1.f-decimal;
            p0.r *= other_decimal;
            p0.g *= other_decimal;
            p0.b *= other_decimal;
            p1.r *= decimal;
            p1.g *= decimal;
            p1.b *= decimal;
            p0.r += p1.r;
            p0.g += p1.g;
            p0.b += p1.b;
            return p0;
        }
        else
        {
            ColorRGB p0 = bilinear(u, v, side[chosen_below],
                                   values[chosen_below]);
            ColorRGB p1 = bilinear(u, v, side[chosen_below+1],
                                   values[chosen_below+1]);
            const float other_decimal = 1.f-decimal;
            p0.r *= other_decimal;
            p0.g *= other_decimal;
            p0.b *= other_decimal;
            p1.r *= decimal;
            p1.g *= decimal;
            p1.b *= decimal;
            p0.r += p1.r;
            p0.g += p1.g;
            p0.b += p1.b;
            return p0;
        }
    }
}

ColorRGB ImageMap::trilinear_ewa(float u, float v, float dudx, float dvdx,
                             float dudy, float dvdy)const
{
    float longer_axis = sqrtf(dudx*dudx+dvdx*dvdx);
    float shorter_axis = sqrtf(dudy*dudy+dvdy*dvdy);
    //keep x as the longer axis
    if(longer_axis<shorter_axis)
    {
        swap(&longer_axis,&shorter_axis);
        swap(&dudx,&dudy);
        swap(&dvdx,&dvdy);
    }
    //if the minor axis is zero, return trilinear filter
    if(shorter_axis == 0.f)
    {
        return high_depth?bilinear(u, v, side[0], values_high[0]):
                          bilinear(u, v, side[0], values[0]);
    }
    //if too eccentric increase blurriness and decrease eccentricity by scaling
    //the shorter axis
    else if(shorter_axis*EWA_MAX_ECCENTRICITY<longer_axis)
    {
        float scale = longer_axis/(shorter_axis*EWA_MAX_ECCENTRICITY);
        dudy*=scale;
        dvdy*=scale;
        shorter_axis*=scale;
    }
}

static ColorRGB bilinear(float u, float v, unsigned short side, Texel* vals)
{
    u = u*side-0.5f;
    v = v*side-0.5f;
    unsigned short x = (unsigned short)u;
    unsigned short y = (unsigned short)v;
    float decimal_u = u-x;
    float decimal_v = v-y;
    float rem_u = 1.f-decimal_u;
    float rem_v = 1.f-decimal_v;
    Texel t0 = vals[y*side+x];
    Texel t1 = vals[y*side+x+1];
    Texel t2 = vals[(y+1)*side+x];
    Texel t3 = vals[(y+1)*side+x+1];
    uint8_t r = (uint8_t)((t0.r*rem_u+t1.r*decimal_u)*rem_v+
                          (t2.r*rem_u+t3.r*decimal_u)*decimal_v);
    uint8_t g = (uint8_t)((t0.g*rem_u+t1.g*decimal_u)*rem_v+
                          (t2.g*rem_u+t3.g*decimal_u)*decimal_v);
    uint8_t b = (uint8_t)((t0.b*rem_u+t1.b*decimal_u)*rem_v+
                          (t2.b*rem_u+t3.b*decimal_u)*decimal_v);
    return ColorRGB(r, g, b);
}

static ColorRGB bilinear(float u, float v, unsigned short side, Texel32* vals)
{
    u = u*side-0.5f;
    v = v*side-0.5f;
    unsigned short x = (unsigned short)u;
    unsigned short y = (unsigned short)v;
    float decimal_u = u-x;
    float decimal_v = v-y;
    float rem_u = 1.f-decimal_u;
    float rem_v = 1.f-decimal_v;
    Texel32 t0 = vals[y*side+x];
    Texel32 t1 = vals[y*side+x+1];
    Texel32 t2 = vals[(y+1)*side+x];
    Texel32 t3 = vals[(y+1)*side+x+1];
    float r = (t0.r*rem_u+t1.r*decimal_u)*rem_v+
              (t2.r*rem_u+t3.r*decimal_u)*decimal_v;
    float g = (t0.g*rem_u+t1.g*decimal_u)*rem_v+
              (t2.g*rem_u+t3.g*decimal_u)*decimal_v;
    float b = (t0.b*rem_u+t1.b*decimal_u)*rem_v+
               (t2.b*rem_u+t3.b*decimal_u)*decimal_v;
    return ColorRGB(r, g, b);
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
