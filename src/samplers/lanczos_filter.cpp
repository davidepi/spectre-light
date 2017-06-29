#include "lanczos_filter.hpp"

LanczosFilter::LanczosFilter(float x_r, float y_r, float tau)
: Filter(x_r,y_r)
{
    LanczosFilter::inverse_width = 1.0f/x_r;
    LanczosFilter::inverse_height = 1.0f/y_r;
    LanczosFilter::tau = tau;
}

float LanczosFilter::weight(float offset_x, float offset_y)const
{
    float resx = fabsf(offset_x * LanczosFilter::inverse_width);
    if(resx < 1E-5)
        return 1.f;
    if(resx > 1.f)
        return 0.f;
    resx *= M_PI;
    float sinc = sinf(resx * LanczosFilter::tau) / (resx * LanczosFilter::tau);
    float lanczos = sinf(resx)/resx;
    resx = sinc * lanczos;
    float resy = fabsf(offset_y * LanczosFilter::inverse_height);
    if (resy < 1E-5)
        return 1.f;
    if(resy > 1.f)
        return 0.f;
    resy *= M_PI;
    sinc = sinf(resy * LanczosFilter::tau) / (resy * LanczosFilter::tau);
    lanczos = sinf(resy)/resy;
    resy = sinc * lanczos;
    return resx * resy;
}
