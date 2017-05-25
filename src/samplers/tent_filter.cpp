#include "tent_filter.hpp"

TentFilter::TentFilter(float x_r, float y_r) : Filter(x_r, y_r)
{
    
}

TentFilter::~TentFilter()
{

}

float TentFilter::weight(float offset_x, float offset_y)const
{
    return max(0.f,x_range-fabsf(offset_x)) * max(0.f,y_range-fabsf(offset_y));
}
