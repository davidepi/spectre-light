//author: Davide Pizzolotto
//license: GNU GPLv3

#include "lanczos_filter.hpp"

///Number of pixels affected by the lanczos filter on the x axis
#define EXTENT_LANCZOS_FILTER_X 4
///Number of pixels affected by the lanczos filter on the y axis
#define EXTENT_LANCZOS_FILTER_Y 4

LanczosFilter::LanczosFilter(float tau)
:Filter(EXTENT_LANCZOS_FILTER_X,EXTENT_LANCZOS_FILTER_Y)
{
    LanczosFilter::tau = tau;
}

float LanczosFilter::weight(float offset_x, float offset_y)const
{
    float resx = fabsf(offset_x * (1.f/EXTENT_LANCZOS_FILTER_X));
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
    float resy = fabsf(offset_y * (1.f/EXTENT_LANCZOS_FILTER_Y));
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
