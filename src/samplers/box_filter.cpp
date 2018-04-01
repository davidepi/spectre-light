//author: Davide Pizzolotto
//license: GNU GPLv3

#include "box_filter.hpp"

float BoxFilter::weight(float, float)const
{
    return 1.0f;
}
