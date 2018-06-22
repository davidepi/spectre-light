//author: Davide Pizzolotto
//license: GNU GPLv3

#include "textures/image_map.hpp"

//------------------------ removed because expf not constexpr in macOS ---------
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
//const std::array<float, EWA_WEIGHTS_SIZE> ImageMap::EWA_WEIGHTS =
//        ewa_lookup_init<EWA_WEIGHTS_SIZE>();
// -----------------------------------------------------------------------------
const float ImageMap::EWA_WEIGHTS[EWA_WEIGHTS_SIZE] =
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
                0.0065472275f, 0.00433036685f, 0.0021481365f, 0.f
        };

void TexelMap::get_texel(unsigned char lvl0, int lvl1, Texel32 *out)const
{
    out->r = ((Texel**)values)[lvl0][lvl1].r;
    out->g = ((Texel**)values)[lvl0][lvl1].g;
    out->b = ((Texel**)values)[lvl0][lvl1].b;
}

void TexelMap::get_color(Texel32& in, ColorRGB* out)const
{
    *out = ColorRGB((unsigned char)in.r,
                    (unsigned char)in.g,
                    (unsigned char)in.b);
}

void TexelMap::get_color(unsigned char lvl0, int lvl1, ColorRGB *out)const
{
    *out = ColorRGB(((Texel**)values)[lvl0][lvl1].r,
                    ((Texel**)values)[lvl0][lvl1].g,
                    ((Texel**)values)[lvl0][lvl1].b);
}

void TexelMap::set_color(unsigned char lvl0, int lvl1, const ColorRGB& val)const
{
    ((Texel**)values)[lvl0][lvl1].r = (uint8_t)(val.r*255);
    ((Texel**)values)[lvl0][lvl1].g = (uint8_t)(val.g*255);
    ((Texel**)values)[lvl0][lvl1].b = (uint8_t)(val.b*255);
}

void TexelMapHigh::get_texel(unsigned char lvl0, int lvl1, Texel32 *out)const
{
    out->r = ((Texel32**)values)[lvl0][lvl1].r;
    out->g = ((Texel32**)values)[lvl0][lvl1].g;
    out->b = ((Texel32**)values)[lvl0][lvl1].b;
}

void TexelMapHigh::get_color(Texel32& in, ColorRGB* out)const
{
    *out = ColorRGB(in.r, in.g, in.b);
}

void TexelMapHigh::get_color(unsigned char lvl0, int lvl1, ColorRGB *out)const
{
    *out = ColorRGB(((Texel32**)values)[lvl0][lvl1].r,
                    ((Texel32**)values)[lvl0][lvl1].g,
                    ((Texel32**)values)[lvl0][lvl1].b);
}

void TexelMapHigh::set_color(unsigned char lvl0, int lvl1,
                             const ColorRGB& val)const
{
    ((Texel32**)values)[lvl0][lvl1].r = val.r*255;
    ((Texel32**)values)[lvl0][lvl1].g = val.g*255;
    ((Texel32**)values)[lvl0][lvl1].b = val.b*255;
}

ImageMap::ImageMap(const uint8_t* values, uint16_t side)
{
    maps_no = (uint8_t)(1+(int)log2f(side));
    ImageMap::side = (uint16_t*)malloc(sizeof(uint16_t)*maps_no);
    MIPmap = TexelMap();
    MIPmap.values = (void**)malloc(sizeof(uint8_t*)*maps_no);
    MIPmap.values[0] = malloc(sizeof(uint8_t)*side*side*3);
    ImageMap::side[0] = side;
    memcpy(MIPmap.values[0],values,sizeof(uint8_t)*side*side*3);
    for(int i=1;i<maps_no;i++)
    {
        ImageMap::side[i] = ImageMap::side[i-1] >> 1;
        MIPmap.values[i] = malloc(sizeof(uint8_t)*
                                  ImageMap::side[i]*
                                  ImageMap::side[i]*3);
        downsample(i-1, i);
    }
    set_filter(UNFILTERED);
}

ImageMap::ImageMap(const float* values, uint16_t side)
{
    maps_no = (uint8_t)(1+(int)log2f(side));
    ImageMap::side = (uint16_t*)malloc(sizeof(uint16_t)*maps_no);
    MIPmap = TexelMapHigh();
    MIPmap.values = (void**)malloc(sizeof(float*)*maps_no);
    MIPmap.values[0] = malloc(sizeof(float)*side*side*3);
    ImageMap::side[0] = side;
    memcpy(MIPmap.values[0],values,sizeof(float)*side*side*3);
    for(int i=1;i<maps_no;i++)
    {
        ImageMap::side[i] = ImageMap::side[i-1] >> 1;
        MIPmap.values[i] = malloc(sizeof(float)*
                                  ImageMap::side[i]*
                                  ImageMap::side[i]*3);
        downsample(i-1, i);
    }
    set_filter(UNFILTERED);
}

ImageMap::~ImageMap()
{
    for(int i = 0; i<maps_no; i++)
        free(MIPmap.values[i]);
    free(MIPmap.values);
}

void ImageMap::set_filter(TextureFilter_t type)
{
    switch(type)
    {
        case UNFILTERED:filter = &ImageMap::unfiltered;
            break;
        case TRILINEAR:filter = &ImageMap::linear_iso;
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
    MIPmap.get_color(0, y*side[0]+x, &res);
    return res;
}

ColorRGB ImageMap::linear_iso(float u, float v, float dudx, float dvdx,
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
        p0 = bilinear(u, v, 0);
    else if(chosen>maps_no-1) //return the single, most distant pixel
        MIPmap.get_color(maps_no-1, 0, &p0);
    else //perform trilinear interpolation
    {
        ColorRGB p1;
        uint8_t chosen_below = (uint8_t)chosen;
        float decimal = chosen-chosen_below;
        p0 = bilinear(u, v, chosen_below);
        p1 = bilinear(u, v, chosen_below+1);
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
        return bilinear(u,v,0);
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
        MIPmap.get_color(maps_no-1, 0, &p0);
    else
    {
        uint8_t chosen_below = (uint8_t)chosen;
        float decimal = chosen-chosen_below;
        p0 = ewa(u,v,dudx,dvdx,dudy,dvdy,chosen_below);
        ColorRGB p1 = ewa(u,v,dudx,dvdx,dudy,dvdy,chosen_below+1);
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

ColorRGB ImageMap::bilinear(float u, float v, uint8_t level)const
{
    u = max(0.f, u*side[level]-0.5f);
    v = max(0.f, v*side[level]-0.5f);
    unsigned short x = (unsigned short)u;
    unsigned short y = (unsigned short)v;
    float decimal_u = u-x;
    float decimal_v = v-y;
    float int_u = 1.f-decimal_u;
    float int_v = 1.f-decimal_v;
    Texel32 t0;
    Texel32 t1;
    Texel32 t2;
    Texel32 t3;
    Texel32 out;
    MIPmap.get_texel(level, y*side[level]+x, &t0);
    MIPmap.get_texel(level, y*side[level]+x+1, &t1);
    MIPmap.get_texel(level, (y+1)*side[level]+x, &t2);
    MIPmap.get_texel(level, (y+1)*side[level]+x+1, &t3);
    ColorRGB retval;
    out.r = (t0.r*int_u+t1.r*decimal_u)*int_v+
            (t2.r*int_u+t3.r*decimal_u)*decimal_v;
    out.g = (t0.g*int_u+t1.g*decimal_u)*int_v+
            (t2.g*int_u+t3.g*decimal_u)*decimal_v;
    out.b = (t0.b*int_u+t1.b*decimal_u)*int_v+
            (t2.b*int_u+t3.b*decimal_u)*decimal_v;
    //out could be either in [0-1] range or [0-255] range, this steps aligns it
    MIPmap.get_color(out, &retval);
    return retval;
}

ColorRGB ImageMap::ewa(float u, float v, float dudx, float dvdx, float dudy,
                       float dvdy, uint8_t level)const
{
    //scale values
    u = max(0.f, u*side[level]-0.5f);
    v = max(0.f, v*side[level]-0.5f);
    dudx *= side[level];
    dvdx *= side[level];
    dudy *= side[level];
    dvdy *= side[level];
    
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
                ColorRGB hit;
                MIPmap.get_color(level, y*side[level]+x, &hit);
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
    return ColorRGB(resr*invweigth,resg*invweigth,resb*invweigth);
}

void ImageMap::downsample(uint8_t input_idx, uint8_t output_idx)
{
    for(int y=0;y<side[output_idx];y++)
    {
        for(int x = 0;x<side[output_idx];x++)
        {
            ColorRGB t0;
            ColorRGB t1;
            ColorRGB t2;
            ColorRGB t3;
            MIPmap.get_color(input_idx, 2*y*side[input_idx]+2*x, &t0);
            MIPmap.get_color(input_idx, (2*y+1)*side[input_idx]+2*x, &t1);
            MIPmap.get_color(input_idx, 2*y*side[input_idx]+(2*x+1), &t2);
            MIPmap.get_color(input_idx, (2*y+1)*side[input_idx]+(2*x+1), &t3);
            ColorRGB out((0.25f*(t0.r+t1.r+t2.r+t3.r)),
                         (0.25f*(t0.g+t1.g+t2.g+t3.g)),
                         (0.25f*(t0.b+t1.b+t2.b+t3.b)));
            MIPmap.set_color(output_idx, y*side[output_idx]+x, out);
        }
    }
}
