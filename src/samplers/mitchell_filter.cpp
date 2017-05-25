#include "mitchell_filter.hpp"

MitchellFilter::MitchellFilter(float x_r, float y_r, float b, float c)
: Filter(x_r,y_r)
{
    MitchellFilter::inv_width = 1.0f/x_r;
    MitchellFilter::inv_height = 1.0f/y_r;
    MitchellFilter::b = b;
    MitchellFilter::c = c;
}

MitchellFilter::~MitchellFilter()
{

}

float MitchellFilter::weight(float offset_x, float offset_y)const
{
    float x = offset_x * inv_width;
    float y = offset_x * inv_height;

    float resx = fabsf(x*2.0f);
    if(resx>1.0f)
        resx=((-b-6*c)*x*x*x+(6*b+30*c)*x*x+(-12*b-48*c)*x+(8*b+24*c))*1.f/6.f;
    else
        resx=((12-9*b-6*c)*x*x*x+(-18+12*b+6*c)*x*x+(6-2*b))*(1.f/6.f);

    float resy = fabsf(y*2.0f);
    if(resy>1.0f)
        resy=((-b-6*c)*y*y*y+(6*b+30*c)*y*y+(-12*b-48*c)*y+(8*b+24*c))*1.f/6.f;
    else
        resy=((12-9*b-6*c)*y*y*y+(-18+12*b+6*c)*y*y+(6-2*b))*(1.f/6.f);

    return resx*resy;
}
