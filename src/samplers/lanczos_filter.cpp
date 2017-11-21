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
    float sinc;
    float lanczos;
    if(resx < 1E-5f)
        resx = 1.f;
    else if(resx > 1.f)
        resx = 0.f;
    else
    {
        resx *= ONE_PI;
        sinc = sinf(resx * LanczosFilter::tau) / (resx * LanczosFilter::tau);
        lanczos = sinf(resx) / resx;
        resx = sinc * lanczos;
    }
    float resy = fabsf(offset_y * LanczosFilter::inverse_height);
    if (resy < 1E-5f)
        resy = 1.f;
    else if(resy > 1.f)
        resy = 0.f;
    else
    {
        resy *= ONE_PI;
        sinc = sinf(resy * LanczosFilter::tau) / (resy * LanczosFilter::tau);
        lanczos = sinf(resy) / resy;
        resy = sinc * lanczos;
    }
    return resx * resy;
}
