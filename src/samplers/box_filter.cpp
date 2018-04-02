//author: Davide Pizzolotto
//license: GNU GPLv3

#include "box_filter.hpp"

BoxFilter::BoxFilter():Filter(EXTENT_BOX_FILTER_X,EXTENT_BOX_FILTER_Y){};

float BoxFilter::weight(float, float)const
{
    return 1.0f;
}
