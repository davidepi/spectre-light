//author: Davide Pizzolotto
//license: GNU GPLv3

#include "filter_lanczos.hpp"
#include "settings.h" //ONE_PI
#include <cmath>

///Number of pixels affected by the lanczos filter on the x axis
#define EXTENT_FILTER_LANCZOS_X 4
///Number of pixels affected by the lanczos filter on the y axis
#define EXTENT_FILTER_LANCZOS_Y 4

FilterLanczos::FilterLanczos(float tau)
        :Filter(EXTENT_FILTER_LANCZOS_X, EXTENT_FILTER_LANCZOS_Y)
{
    FilterLanczos::tau = tau;
}

float FilterLanczos::weight(float offset_x, float offset_y) const
{
    float resx = fabsf(offset_x*(1.f/EXTENT_FILTER_LANCZOS_X));
    float sinc;
    float lanczos;
    if(resx<1E-5f)
        resx = 1.f;
    else if(resx>1.f)
        resx = 0.f;
    else
    {
        resx *= ONE_PI;
        sinc = sinf(resx*FilterLanczos::tau)/(resx*FilterLanczos::tau);
        lanczos = sinf(resx)/resx;
        resx = sinc*lanczos;
    }
    float resy = fabsf(offset_y*(1.f/EXTENT_FILTER_LANCZOS_Y));
    if(resy<1E-5f)
        resy = 1.f;
    else if(resy>1.f)
        resy = 0.f;
    else
    {
        resy *= ONE_PI;
        sinc = sinf(resy*FilterLanczos::tau)/(resy*FilterLanczos::tau);
        lanczos = sinf(resy)/resy;
        resy = sinc*lanczos;
    }
    return resx*resy;
}

float FilterLanczos::get_param0() const
{
    return tau;
}

float FilterLanczos::get_param1() const
{
    return -1.f;
}
