//author: Davide Pizzolotto
//license: GNU GPLv3

#include "box_filter.hpp"

BoxFilter::BoxFilter(float x_r, float y_r) : Filter(x_r,y_r)
{

}

float BoxFilter::weight(float, float)const
{
    return 1.0f;
}
