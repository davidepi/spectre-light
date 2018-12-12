//author: Davide Pizzolotto
//license: GNU GPLv3

#include "textures/image_map.hpp"

static void downsample(const TexelUnion* in, TexelUnion* out,
                       uint16_t input_side);

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
const float ImageMapEWA::EWA_WEIGHTS[EWA_WEIGHTS_SIZE] = {
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

ImageMap::ImageMap(const pixBGRA* values, uint16_t side)
{
    //a bit of memory wasted... this is better than some pointer magic
    TexelUnion* original = (TexelUnion*)malloc(sizeof(TexelUnion)*side*side);
    TexelUnion* reduced = (TexelUnion*)malloc(sizeof(TexelUnion)*side*side);
    memcpy(original, values, sizeof(TexelUnion)*side*side);

    maps_no = (uint8_t)(1+(int)log2f(side));
    ImageMap::side = (uint16_t*)malloc(sizeof(uint16_t)*maps_no);
    MIPmap = new Array2D<TexelUnion>* [maps_no];
    MIPmap[0] = new Array2D<TexelUnion>(original, side);
    ImageMap::side[0] = side;
    for(int i = 1; i<maps_no; i++)
    {
        ImageMap::side[i] = ImageMap::side[i-1] >> 1;
        downsample(original, reduced, ImageMap::side[i-1]);
        MIPmap[i] = new Array2D<TexelUnion>(reduced, ImageMap::side[i]);
        //swap values, so next iteration the input is the output of this one
        TexelUnion* tmp = reduced;
        reduced = original;
        original = tmp;
    }
    free(original);
    free(reduced);
}

uint16_t ImageMap::get_side() const
{
    return side[0];
};

ImageMap::~ImageMap()
{
    for(int i = 0; i<maps_no; i++)
        delete ImageMap::MIPmap[i];
    delete[] ImageMap::MIPmap;
    free(ImageMap::side);
}

TexelUnion ImageMapUnfiltered::filter(float u, float v, float, float,
                                      float, float) const
{
    uint16_t x = (uint16_t)(u*side[0]-0.5f);
    uint16_t y = (uint16_t)(v*side[0]-0.5f);
    return MIPmap[0]->get(x, y);
}

TexelUnion ImageMapTrilinear::filter(float u, float v, float dudx, float dvdx,
                                     float dudy, float dvdy) const
{
    //float width = min(dudx*dudx+dvdx*dvdx, dudy*dudy+dvdy*dvdy);
    float width = max(max(fabsf(dudx), fabsf(dvdx)),
                      max(fabsf(dudy), fabsf(dvdy)));
    //ensures that log2 doesn't give unwanted results
    width = max(width, 1e-5f);
    //choose mipmap
    float chosen = maps_no-1+log2f(width);
    TexelUnion p0; //retval
    if(chosen<=0.f) //use full size map
        p0 = bilinear(u, v, 0);
    else if(chosen>maps_no-1) //return the single, most distant pixel
        p0 = MIPmap[maps_no-1]->get(0, 0);
    else //perform trilinear interpolation
    {
        TexelUnion p1;
        uint8_t chosen_below = (uint8_t)chosen;
        float decimal = chosen-chosen_below;
        p0 = bilinear(u, v, chosen_below);
        p1 = bilinear(u, v, chosen_below+1);
        const float other_decimal = 1.f-decimal;
        p0.bgra_texel.r *= other_decimal;
        p0.bgra_texel.g *= other_decimal;
        p0.bgra_texel.b *= other_decimal;
        p0.bgra_texel.a *= other_decimal;
        p1.bgra_texel.r *= decimal;
        p1.bgra_texel.g *= decimal;
        p1.bgra_texel.b *= decimal;
        p1.bgra_texel.a *= decimal;
        p0.bgra_texel.r += p1.bgra_texel.r;
        p0.bgra_texel.g += p1.bgra_texel.g;
        p0.bgra_texel.b += p1.bgra_texel.b;
        p0.bgra_texel.a += p1.bgra_texel.a;
    }
    return p0;
}

TexelUnion ImageMapEWA::filter(float u, float v, float dudx, float dvdx,
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
        return ImageMap::bilinear(u, v, 0);
    }
        //if too eccentric increase blurriness and decrease eccentricity by
        //scaling the shorter axis
    else if(shorter_axis*EWA_MAX_ECCENTRICITY<longer_axis)
    {
        float scale = longer_axis/(shorter_axis*EWA_MAX_ECCENTRICITY);
        dudy *= scale;
        dvdy *= scale;
        shorter_axis *= scale;
    }
    // shorter axis 0 previously catched in an if
    float chosen = max(0.f, maps_no-1+log2f(shorter_axis));
    TexelUnion p0; //retval
    if(chosen>maps_no-1) //return the single, most distant pixel
        p0 = MIPmap[maps_no-1]->get(0, 0);
    else
    {
        uint8_t chosen_below = (uint8_t)chosen;
        float decimal = chosen-chosen_below;
        p0 = ewa(u, v, dudx, dvdx, dudy, dvdy, chosen_below);
        TexelUnion p1 = ewa(u, v, dudx, dvdx, dudy, dvdy, chosen_below+1);
        const float other_decimal = 1.f-decimal;
        p0.bgra_texel.r *= other_decimal;
        p0.bgra_texel.g *= other_decimal;
        p0.bgra_texel.b *= other_decimal;
        p0.bgra_texel.a *= other_decimal;
        p1.bgra_texel.r *= decimal;
        p1.bgra_texel.g *= decimal;
        p1.bgra_texel.b *= decimal;
        p1.bgra_texel.a *= decimal;
        p0.bgra_texel.r += p1.bgra_texel.r;
        p0.bgra_texel.g += p1.bgra_texel.g;
        p0.bgra_texel.b += p1.bgra_texel.b;
        p0.bgra_texel.a += p1.bgra_texel.a;
    }
    return p0;
}

TexelUnion ImageMap::bilinear(float u, float v, uint8_t level) const
{
    u = u*side[level]-0.5f;
    v = v*side[level]-0.5f;
    int x = (int)u;
    int y = (int)v;
    float decimal_u = fabsf(u-x); //to avoid corner case where this can be -0.5f
    float decimal_v = fabsf(v-y);
    float int_u = 1.f-decimal_u;
    float int_v = 1.f-decimal_v;
    //wraps texture if filtering happens outside bounds (val+1) = out of texture
    int next_x = (x+1)<=side[level]-1?(x+1):0;
    int next_y = (y+1)<=side[level]-1?(y+1):0;
    const Texel T0 = MIPmap[level]->get(x, y).bgra_texel;
    const Texel T1 = MIPmap[level]->get(next_x, y).bgra_texel;
    const Texel T2 = MIPmap[level]->get(x, next_y).bgra_texel;
    const Texel T3 = MIPmap[level]->get(next_x, next_y).bgra_texel;
    TexelUnion res;
    res.bgra_texel.r = (uint8_t)((T0.r*int_u+T1.r*decimal_u)*int_v+
                                 (T2.r*int_u+T3.r*decimal_u)*decimal_v);
    res.bgra_texel.g = (uint8_t)((T0.g*int_u+T1.g*decimal_u)*int_v+
                                 (T2.g*int_u+T3.g*decimal_u)*decimal_v);
    res.bgra_texel.b = (uint8_t)((T0.b*int_u+T1.b*decimal_u)*int_v+
                                 (T2.b*int_u+T3.b*decimal_u)*decimal_v);
    res.bgra_texel.a = (uint8_t)((T0.a*int_u+T1.a*decimal_u)*int_v+
                                 (T2.a*int_u+T3.a*decimal_u)*decimal_v);

    return res;
}

TexelUnion
ImageMapEWA::ewa(float u, float v, float dudx, float dvdx, float dudy,
                 float dvdy, uint8_t level) const
{
    //scale values
    u = u*side[level]-0.5f;
    v = v*side[level]-0.5f;
    dudx *= side[level];
    dvdx *= side[level];
    dudy *= side[level];
    dvdy *= side[level];

    //calulate ellipse coefficients
    float a = dvdx*dvdx*+dvdy*dvdy+1.f;
    float b = -2.f*(dudx*dvdx+dudy*dvdy);
    float c = dudx*dudx+dudy*dudy+1.f;
    const float invf = 1.f/(a*c-b*b*.25f);
    a *= invf;
    b *= invf;
    c *= invf;

    //found the ellipse aabb
    const float delta = -b*b+4.f*a*c;
    const float invdelta = 1.f/delta;
    const float x0 = sqrtf(delta*c);
    const float y0 = sqrtf(delta*a);
    int u0 = (int)ceilf(u-2.f*invdelta*x0);
    int u1 = (int)floorf(u+2.f*invdelta*x0);
    int v0 = (int)ceilf(v-2.f*invdelta*y0);
    int v1 = (int)floorf(v+2.f*invdelta*y0);

    //loops over the AABB, if the point is inside the ellipse, filter it
    float resr = 0.f;
    float resg = 0.f;
    float resb = 0.f;
    float resa = 0.f;
    float total_weight = 0.f;
    for(int y = v0; y<=v1; y++)
    {
        //wraps texture if ellipse is outside bounds
        int newy = y<0?side[level]+y:y>side[level]-1?y%side[level]:y;
        const float voff = newy-v;
        for(int x = u0; x<=u1; x++)
        {
            //wraps texture if ellipse is outside bounds
            int newx = x<0?side[level]+x:x>side[level]-1?x%side[level]:x;
            const float uoff = newx-u;
            const float radius2 = a*uoff*uoff+b*voff*uoff+c*voff*voff;
            if(radius2<1.f)
            {
                TexelUnion hit = MIPmap[level]->get(newx, newy);
                //found the correct value for the lookup table, or the most
                // distant one
                const int index = min((int)(radius2*EWA_WEIGHTS_SIZE),
                                      EWA_WEIGHTS_SIZE-1);
                const float weight = ImageMapEWA::EWA_WEIGHTS[index];
                resr += hit.bgra_texel.r*weight;
                resg += hit.bgra_texel.g*weight;
                resb += hit.bgra_texel.b*weight;
                resa += hit.bgra_texel.a*weight;
                total_weight += weight;
            }
        }
    }
    float invweigth = 1.f/total_weight;
    TexelUnion retval;
    retval.bgra_texel.r = resr*invweigth;
    retval.bgra_texel.g = resg*invweigth;
    retval.bgra_texel.b = resb*invweigth;
    retval.bgra_texel.a = resa*invweigth;
    return retval;
}

static void
downsample(const TexelUnion* in, TexelUnion* out, uint16_t input_side)
{
    uint16_t output_side = input_side >> 1;
    for(int y = 0; y<output_side; y++)
    {
        for(int x = 0; x<output_side; x++)
        {
            const Texel T0 = in[2*y*input_side+2*x].bgra_texel;
            const Texel T1 = in[(2*y+1)*input_side+2*x].bgra_texel;
            const Texel T2 = in[2*y*input_side+(2*x+1)].bgra_texel;
            const Texel T3 = in[(2*y+1)*input_side+(2*x+1)].bgra_texel;
            Texel res;
            res.r = (uint8_t)(0.25f*(T0.r+T1.r+T2.r+T3.r));
            res.g = (uint8_t)(0.25f*(T0.g+T1.g+T2.g+T3.g));
            res.b = (uint8_t)(0.25f*(T0.b+T1.b+T2.b+T3.b));
            res.a = (uint8_t)(0.25f*(T0.a+T1.a+T2.a+T3.a));
            out[y*output_side+x].bgra_texel = res;
        }
    }
}
