//author: Davide Pizzolotto
//license: GNU GPLv3

#include "box_filter.hpp"

BoxFilter::BoxFilter(float x_range, float y_range) : Filter(x_range,y_range)
{

}

float BoxFilter::weight(float, float)const
{
    return 1.0f;
}
