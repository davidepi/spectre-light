//author: Davide Pizzolotto
//license: GNU GPLv3

#include "tent_filter.hpp"

TentFilter::TentFilter(float x_range, float y_range) : Filter(x_range, y_range)
{
    
}

float TentFilter::weight(float offset_x, float offset_y)const
{
    return max(0.f,x_range-fabsf(offset_x))/x_range *
           max(0.f,y_range-fabsf(offset_y))/y_range;
}
