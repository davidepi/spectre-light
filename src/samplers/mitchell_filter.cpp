//author: Davide Pizzolotto
//license: GNU GPLv3

#include "mitchell_filter.hpp"

MitchellFilter::MitchellFilter(float x_range, float y_range, float b, float c)
: Filter(x_range,y_range)
{
    MitchellFilter::inv_width = 1.0f/x_range;
    MitchellFilter::inv_height = 1.0f/y_range;
    MitchellFilter::b = b;
    MitchellFilter::c = c;
}

float MitchellFilter::weight(float offset_x, float offset_y)const
{
    constexpr const float DENOMINATOR = 1.f/6.f;
    const float x = fabsf(offset_x * inv_width * 2.0f);
    const float y = fabsf(offset_y * inv_height * 2.0f);
    float resx;
    float resy;
    if(x>1.0f)
    {
        resx  = (-b-6*c)*x*x*x;
        resx += (6*b+30*c)*x*x;
        resx += (-12*b-48*c)*x;
        resx += (8*b+24*c);
        resx *= DENOMINATOR;
    }
    else
    {
        resx  = (12-9*b-6*c)*x*x*x;
        resx += (-18+12*b+6*c)*x*x;
        resx += (6-2*b);
        resx *= DENOMINATOR;
    }
    if(y>1.0f)
    {
        resy  = (-b-6*c)*y*y*y;
        resy += (6*b+30*c)*y*y;
        resy += (-12*b-48*c)*y;
        resy += (8*b+24*c);
        resy *= DENOMINATOR;
    }
    else
    {
        resy  = (12-9*b-6*c)*y*y*y;
        resy += (-18+12*b+6*c)*y*y;
        resy += (6-2*b);
        resy *= DENOMINATOR;
    }
    return resx*resy;
}
