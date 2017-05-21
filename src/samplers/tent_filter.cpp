#include "tent_filter.hpp"

TentFilter::TentFilter(float x_range, float y_range) : Filter()
{
    TentFilter::width = x_range;
    TentFilter::height = y_range;
}

TentFilter::~TentFilter()
{

}

float TentFilter::weight(float offset_x, float offset_y)const
{
    return max(0.f,width-fabsf(offset_x)) * max(0.f,height-fabsf(offset_y));
}
