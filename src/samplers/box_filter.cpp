#include "box_filter.hpp"

BoxFilter::BoxFilter() : Filter()
{

}

BoxFilter::~BoxFilter() : ~Filter()
{

}

float BoxFilter::weight(float offset_x, float offset_y)
{
    return 1.0f;
}