//author: Davide Pizzolotto
//license: GNU GPLv3

#include "filter_tent.hpp"
#include "utility/utility.hpp"

///Number of pixels affected by the tent filter on the x axis
#define EXTENT_FILTER_TENT_X 2
///Number of pixels affected by the tent filter on the y axis
#define EXTENT_FILTER_TENT_Y 2

FilterTent::FilterTent():Filter(EXTENT_FILTER_TENT_X, EXTENT_FILTER_TENT_Y)
{}

float FilterTent::weight(float offset_x, float offset_y) const
{
    return max(0.f, EXTENT_FILTER_TENT_X-fabsf(offset_x))/EXTENT_FILTER_TENT_X*
           max(0.f, EXTENT_FILTER_TENT_Y-fabsf(offset_y))/EXTENT_FILTER_TENT_Y;
}

float FilterTent::get_param0() const
{
    return -1.f;
}

float FilterTent::get_param1() const
{
    return -1.f;
}
