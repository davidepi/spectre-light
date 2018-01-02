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
    
    float x = offset_x * inv_width;
    float y = offset_y * inv_height;

    float resx = fabsf(x*2.0f);
    if(resx>1.0f)
        resx=((-b-6*c)*resx*resx*resx+(6*b+30*c)*resx*resx+(-12*b-48*c)*resx+(8*b+24*c))*1.f/6.f;
    else
        resx=((12-9*b-6*c)*resx*resx*resx+(-18+12*b+6*c)*resx*resx+(6-2*b))*(1.f/6.f);

    float resy = fabsf(y*2.0f);
    if(resy>1.0f)
        resy=((-b-6*c)*resy*resy*resy+(6*b+30*c)*resy*resy+(-12*b-48*c)*resy+(8*b+24*c))*1.f/6.f;
    else
        resy=((12-9*b-6*c)*resy*resy*resy+(-18+12*b+6*c)*resy*resy+(6-2*b))*(1.f/6.f);

    return resx*resy;
}
