//author: Davide Pizzolotto
//license: GNU GPLv3

#include "filter_box.hpp"

///Number of pixels affected by the box filter on the x axis
#define EXTENT_FILTER_BOX_X 1
///Number of pixels affected by the box filter on the y axis
#define EXTENT_FILTER_BOX_Y 1

FilterBox::FilterBox():Filter(EXTENT_FILTER_BOX_X,EXTENT_FILTER_BOX_Y){};

float FilterBox::weight(float, float)const
{
    return 1.0f;
}
