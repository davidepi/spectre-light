//author: Davide Pizzolotto
//license: GNU GPLv3

#include "box_filter.hpp"

///Number of pixels affected by the box filter on the x axis
#define EXTENT_BOX_FILTER_X 1
///Number of pixels affected by the box filter on the y axis
#define EXTENT_BOX_FILTER_Y 1

BoxFilter::BoxFilter():Filter(EXTENT_BOX_FILTER_X,EXTENT_BOX_FILTER_Y){};

float BoxFilter::weight(float, float)const
{
    return 1.0f;
}
