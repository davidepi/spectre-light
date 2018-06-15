//author: Davide Pizzolotto
//license: GNU GPLv3

#include "textures/image_map.hpp"

const FilterLanczos lowpass_filter = FilterLanczos(3.f);

static void downsample(const Texel* in, Texel* out, unsigned short input_side,
                       bool hqfilter);

static void downsample(const Texel32* in, Texel32* out,
                       unsigned short input_side, bool hqfilter);

static ColorRGB bilinear(float u, float v, unsigned short side, Texel* vals);

static ColorRGB bilinear(float u, float v, unsigned short side, Texel32* vals);

static ColorRGB ewa(float u, float v, float dudx, float dvdx, float dudy,
                    float dvdy, unsigned short side, Texel* vals);

static ColorRGB ewa(float u, float v, float dudx, float dvdx, float dudy,
                    float dvdy, unsigned short side, Texel32* vals);


//TODO: removed because expf not constexpr in macOS
//constexpr float init_ewa_weight(int step)
//{
//    return expf(-EWA_ALPHA*((float)step/(float)(EWA_WEIGHTS_SIZE-1)))-
//           expf(-EWA_ALPHA);
//}

//black magic to initialize the lookup table at compile time and keep it const
//while using functions
//std::index_sequence is used to index the values of the function
// init_ewa_weight from 0 to EWA_WEIGHT_SIZE-1
//template<std::size_t...I>
//constexpr std::array<float, sizeof...(I)>
//ewa_lookup_init(std::index_sequence<I...>)
//{
//    return std::array<float, sizeof...(I)>{init_ewa_weight(I)...};
//}
//
//template<std::size_t N>
//constexpr std::array<float, N> ewa_lookup_init()
//{
//    return ewa_lookup_init(std::make_index_sequence<N>{});
//}

//actual EWA_WEIGHTS array
const std::array<float, EWA_WEIGHTS_SIZE> ImageMap::EWA_WEIGHTS =
//        ewa_lookup_init<EWA_WEIGHTS_SIZE>();
        {
                0.864664733f, 0.849040031f, 0.83365953f, 0.818519294f,
                0.80361563f, 0.788944781f, 0.774503231f, 0.760287285f,
                0.746293485f, 0.732518315f, 0.718958378f, 0.705610275f,
                0.692470789f, 0.679536581f, 0.666804492f, 0.654271305f,
                0.641933978f, 0.629789352f, 0.617834508f, 0.606066525f,
                0.594482362f, 0.583079159f, 0.571854174f, 0.560804546f,
                0.549927592f, 0.539220572f, 0.528680861f, 0.518305838f,
                0.50809288f, 0.498039544f, 0.488143265f, 0.478401601f,
                0.468812168f, 0.45937258f, 0.450080454f, 0.440933526f,
                0.431929469f, 0.423066139f, 0.414341331f, 0.405752778f,
                0.397298455f, 0.388976216f, 0.380784035f, 0.372719884f,
                0.364781618f, 0.356967449f, 0.34927541f, 0.341703475f,
                0.334249914f, 0.32691282f, 0.319690347f, 0.312580705f,
                0.305582166f, 0.298692942f, 0.291911423f, 0.285235822f,
                0.278664529f, 0.272195935f, 0.265828371f, 0.259560347f,
                0.253390193f, 0.247316495f, 0.241337672f, 0.235452279f,
                0.229658857f, 0.223955944f, 0.21834214f, 0.212816045f,
                0.207376286f, 0.202021524f, 0.196750447f, 0.191561714f,
                0.186454013f, 0.181426153f, 0.176476851f, 0.171604887f,
                0.166809067f, 0.162088141f, 0.157441005f, 0.152866468f,
                0.148363426f, 0.143930718f, 0.139567271f, 0.135272011f,
                0.131043866f, 0.126881793f, 0.122784719f, 0.11875169f,
                0.114781633f, 0.11087364f, 0.107026696f, 0.103239879f,
                0.0995122194f, 0.0958427936f, 0.0922307223f, 0.0886750817f,
                0.0851749927f, 0.0817295909f, 0.0783380121f, 0.0749994367f,
                0.0717130303f, 0.0684779733f, 0.0652934611f, 0.0621587038f,
                0.0590728968f, 0.0560353249f, 0.0530452281f, 0.0501018465f,
                0.0472044498f, 0.0443523228f, 0.0415447652f, 0.0387810767f,
                0.0360605568f, 0.0333825648f, 0.0307464004f, 0.0281514227f,
                0.0255970061f, 0.0230824798f, 0.0206072628f, 0.0181707144f,
                0.0157722086f, 0.013411209f, 0.0110870898f, 0.0087992847f,
                0.0065472275f, 0.00433036685f, 0.0021481365f, 0.f,
};

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
        case UNFILTERED:filter = &ImageMap::unfiltered;
            break;
        case TRILINEAR:filter = &ImageMap::trilinear;
            break;
        case EWA:filter = &ImageMap::linear_ewa;
            break;
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
        res = ColorRGB(hit.r, hit.g, hit.b);
    }
    else
    {
        Texel hit = values[0][y*side[0]+x];
        res = ColorRGB(hit.r, hit.g, hit.b);
    }
    return res;
}

ColorRGB ImageMap::trilinear(float u, float v, float dudx, float dvdx,
                             float dudy, float dvdy) const
{
    //float width = min(dudx*dudx+dvdx*dvdx, dudy*dudy+dvdy*dvdy);
    float width = max(max(fabsf(dudx), fabsf(dvdx)),
                      max(fabsf(dudy), fabsf(dvdy)));
    //ensures that log2 doesn't give unwanted results
    width = max(width, 1e-5f);
    //choose mipmap
    float chosen = maps_no-1+log2f(width);
    ColorRGB p0; //retval
    if(chosen<=0.f) //use full size map
        p0 = high_depth?bilinear(u, v, side[0], values_high[0])
                       :bilinear(u, v, side[0], values[0]);
    else if(chosen>maps_no-1) //return the single, most distant pixel
    {
        if(high_depth)
            p0 = ColorRGB(values_high[maps_no-1][0].r,
                          values_high[maps_no-1][0].g,
                          values_high[maps_no-1][0].b);
        else
            p0 = ColorRGB(values[maps_no-1][0].r,
                          values[maps_no-1][0].g,
                          values[maps_no-1][0].b);
    }
    else //perform trilinear interpolation
    {
        ColorRGB p1;
        uint8_t chosen_below = (uint8_t)chosen;
        float decimal = chosen-chosen_below;
        if(high_depth)
        {
            p0 = bilinear(u, v, side[chosen_below],
                          values_high[chosen_below]);
            p1 = bilinear(u, v, side[chosen_below+1],
                          values_high[chosen_below+1]);
        }
        else
        {
            p0 = bilinear(u, v, side[chosen_below],
                          values[chosen_below]);
            p1 = bilinear(u, v, side[chosen_below+1],
                          values[chosen_below+1]);
        }
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
    return p0;
}


ColorRGB ImageMap::linear_ewa(float u, float v, float dudx, float dvdx,
                              float dudy, float dvdy) const
{
    float longer_axis = sqrtf(dudx*dudx+dvdx*dvdx);
    float shorter_axis = sqrtf(dudy*dudy+dvdy*dvdy);
    //keep x as the longer axis
    if(longer_axis<shorter_axis)
    {
        swap(&longer_axis, &shorter_axis);
        swap(&dudx, &dudy);
        swap(&dvdx, &dvdy);
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
        dudy *= scale;
        dvdy *= scale;
        shorter_axis *= scale;
    }
    // shorter axis 0 previously catched in an if
    float chosen = max(0.f, maps_no-1+log2f(shorter_axis));
    ColorRGB p0; //retval
    if(chosen>maps_no-1) //return the single, most distant pixel
    {
        if(high_depth)
            p0 = ColorRGB(values_high[maps_no-1][0].r,
                          values_high[maps_no-1][0].g,
                          values_high[maps_no-1][0].b);
        else
            p0 = ColorRGB(values[maps_no-1][0].r,
                          values[maps_no-1][0].g,
                          values[maps_no-1][0].b);
    }
    else
    {
        uint8_t chosen_below = (uint8_t)chosen;
        float decimal = chosen-chosen_below;
        ColorRGB p1;
        if(high_depth)
        {
            p0 = ewa(u, v, dudx, dvdx, dudy, dvdy, side[chosen_below],
                     values_high[chosen_below]);
            p1 = ewa(u, v, dudx, dvdx, dudy, dvdy, side[chosen_below+1],
                     values_high[chosen_below+1]);
        }
        else
        {
            p0 = ewa(u, v, dudx, dvdx, dudy, dvdy, side[chosen_below],
                     values[chosen_below]);
            p1 = ewa(u, v, dudx, dvdx, dudy, dvdy, side[chosen_below+1],
                     values[chosen_below+1]);
        }
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
    }
    return p0;
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
    u = max(0.f, u*side-0.5f);
    v = max(0.f, v*side-0.5f);
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

static ColorRGB ewa(float u, float v, float dudx, float dvdx, float dudy,
                    float dvdy, unsigned short side, Texel* vals)
{
    //scale values
    u = max(0.f, u*side-0.5f);
    v = max(0.f, v*side-0.5f);
    dudx *= side;
    dvdx *= side;
    dudy *= side;
    dvdy *= side;

    //calulate ellipse coefficients
    float a = dvdx*dvdx*+dvdy*dvdy+1.f;
    float b = -2.f*dudx*dvdx+dudy*dvdy;
    float c = dudx*dudx+dudy*dudy+1.f;
    const float invf = 1.f/(a*c-b*b*.25f);
    a *= invf;
    b *= invf;
    c *= invf;

    //found the ellipse aabb
    const float delta = -b*b+4.f*a*c;
    const float invdelta = 1.f/delta;
    const float x0 = sqrtf(delta*c);
    const float x1 = sqrtf(delta*a);
    int u0 = (int)ceilf(u-2.f*invdelta*x0);
    int u1 = (int)floorf(u+2.f*invdelta*x0);
    int v0 = (int)ceilf(v-2.f*invdelta*x1);
    int v1 = (int)floorf(v+2.f*invdelta*x1);

    //loops over the AABB, if the point is inside the ellipse, filter it
    float resr = 0.f;
    float resg = 0.f;
    float resb = 0.f;
    float total_weight = 0.f;
    for(int y = v0; y<=v1; y++)
    {
        const float voff = y-v;
        for(int x = u0; x<=u1; x++)
        {
            const float uoff = x-u;
            const float radius2 = a*uoff*uoff+b*voff*uoff+c*voff*voff;
            if(radius2<1.f)
            {
                const Texel hit = vals[y*side+x];
                //found the correct value for the lookup table, or the most
                // distant one
                const int index = min((int)(radius2*EWA_WEIGHTS_SIZE),
                                      EWA_WEIGHTS_SIZE-1);
                const float weight = ImageMap::EWA_WEIGHTS[index];
                resr += hit.r*weight;
                resg += hit.g*weight;
                resb += hit.b*weight;
                total_weight += weight;
            }
        }
    }
    float invweigth = 1.f/total_weight;
    return ColorRGB((unsigned char)(resr*invweigth),
                    (unsigned char)(resg*invweigth),
                    (unsigned char)(resb*invweigth));
}

static ColorRGB ewa(float u, float v, float dudx, float dvdx, float dudy,
                    float dvdy, unsigned short side, Texel32* vals)
{
    //scale values
    u = u*side-0.5f;
    v = v*side-0.5f;
    dudx *= side;
    dvdx *= side;
    dudy *= side;
    dvdy *= side;

    //calulate ellipse coefficients
    float a = dvdx*dvdx*+dvdy*dvdy+1.f;
    float b = -2.f*dudx*dvdx+dudy*dvdy;
    float c = dudx*dudx+dudy*dudy+1.f;
    const float invf = 1.f/(a*c-b*b*.25f);
    a *= invf;
    b *= invf;
    c *= invf;

    //found the ellipse aabb
    const float delta = -b*b+4.f*a*c;
    const float invdelta = 1.f/delta;
    const float x0 = sqrtf(delta*c);
    const float x1 = sqrtf(delta*a);
    int u0 = (int)ceilf(u-2.f*invdelta*x0);
    int u1 = (int)floorf(u+2.f*invdelta*x0);
    int v0 = (int)ceilf(v-2.f*invdelta*x1);
    int v1 = (int)floorf(v+2.f*invdelta*x1);

    //loops over the AABB, if the point is inside the ellipse, filter it
    float resr = 0.f;
    float resg = 0.f;
    float resb = 0.f;
    float total_weight = 0.f;
    for(int y = v0; y<=v1; y++)
    {
        const float voff = y-v;
        for(int x = u0; x<=u1; x++)
        {
            const float uoff = x-u;
            const float radius2 = a*uoff*uoff+b*voff*uoff+c*voff*voff;
            if(radius2<1.f)
            {
                const Texel32 hit = vals[y*side+x];
                //found the correct value for the lookup table, or the most
                // distant one
                const int index = min((int)(radius2*EWA_WEIGHTS_SIZE),
                                      EWA_WEIGHTS_SIZE-1);
                const float weight = ImageMap::EWA_WEIGHTS[index];
                resr += hit.r*weight;
                resg += hit.g*weight;
                resb += hit.b*weight;
                total_weight += weight;
            }
        }
    }
    float invweigth = 1.f/total_weight;
    return ColorRGB(resr*invweigth, resg*invweigth, resb*invweigth);
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
