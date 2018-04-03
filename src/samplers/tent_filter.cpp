//author: Davide Pizzolotto
//license: GNU GPLv3

#include "tent_filter.hpp"

///Number of pixels affected by the tent filter on the x axis
#define EXTENT_TENT_FILTER_X 2
///Number of pixels affected by the tent filter on the y axis
#define EXTENT_TENT_FILTER_Y 2

TentFilter::TentFilter():Filter(EXTENT_TENT_FILTER_X,EXTENT_TENT_FILTER_Y){};

float TentFilter::weight(float offset_x, float offset_y)const
{
    return max(0.f,EXTENT_TENT_FILTER_X-fabsf(offset_x))/EXTENT_TENT_FILTER_X *
           max(0.f,EXTENT_TENT_FILTER_Y-fabsf(offset_y))/EXTENT_TENT_FILTER_Y;
}
