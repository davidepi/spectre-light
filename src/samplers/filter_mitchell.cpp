//author: Davide Pizzolotto
//license: GNU GPLv3

#include "filter_mitchell.hpp"

///Number of pixels affected by the mitchell filter on the x axis
#define EXTENT_FILTER_MITCHELL_X 2
///Number of pixels affected by the mitchell filter on the y axis
#define EXTENT_FILTER_MITCHELL_Y 2

FilterMitchell::FilterMitchell(float b, float c)
        :Filter(EXTENT_FILTER_MITCHELL_X, EXTENT_FILTER_MITCHELL_Y)
{
    FilterMitchell::b = b;
    FilterMitchell::c = c;
}

float FilterMitchell::weight(float offset_x, float offset_y) const
{
    constexpr const float DENOMINATOR = 1.f/6.f;
    const float x = fabsf(offset_x*(1.f/EXTENT_FILTER_MITCHELL_X)*2.0f);
    const float y = fabsf(offset_y*(1.f/EXTENT_FILTER_MITCHELL_Y)*2.0f);
    float resx;
    float resy;
    if(x>1.0f)
    {
        resx = (-b-6*c)*x*x*x;
        resx += (6*b+30*c)*x*x;
        resx += (-12*b-48*c)*x;
        resx += (8*b+24*c);
        resx *= DENOMINATOR;
    }
    else
    {
        resx = (12-9*b-6*c)*x*x*x;
        resx += (-18+12*b+6*c)*x*x;
        resx += (6-2*b);
        resx *= DENOMINATOR;
    }
    if(y>1.0f)
    {
        resy = (-b-6*c)*y*y*y;
        resy += (6*b+30*c)*y*y;
        resy += (-12*b-48*c)*y;
        resy += (8*b+24*c);
        resy *= DENOMINATOR;
    }
    else
    {
        resy = (12-9*b-6*c)*y*y*y;
        resy += (-18+12*b+6*c)*y*y;
        resy += (6-2*b);
        resy *= DENOMINATOR;
    }
    return resx*resy;
}
