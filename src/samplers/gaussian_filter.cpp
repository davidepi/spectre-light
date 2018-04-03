//author: Davide Pizzolotto
//license: GNU GPLv3

#include "gaussian_filter.hpp"

///Number of pixels affected by the gaussian filter on the x axis
#define EXTENT_GAUSSIAN_FILTER_X 2
///Number of pixels affected by the gaussian filter on the y axis
#define EXTENT_GAUSSIAN_FILTER_Y 2

GaussianFilter::GaussianFilter(float falloff)
:Filter(EXTENT_GAUSSIAN_FILTER_X,EXTENT_GAUSSIAN_FILTER_Y)
{
    GaussianFilter::precomputed_exp_x =
    expf(-falloff*EXTENT_GAUSSIAN_FILTER_X*EXTENT_GAUSSIAN_FILTER_X);
    GaussianFilter::precomputed_exp_y =
    expf(-falloff*EXTENT_GAUSSIAN_FILTER_Y*EXTENT_GAUSSIAN_FILTER_Y);
    GaussianFilter::alpha = falloff;
}

float GaussianFilter::weight(float offset_x, float offset_y)const
{
    //f(x) = e^(-alpha*x^2)-e^(-alpha*width^2)
    //where the second term is used to let the gaussian tend to zero at its
    //limit and is precomputed in the constructor
    return max(0.f,expf(-alpha*offset_x*offset_x) - precomputed_exp_x) *
           max(0.f,expf(-alpha*offset_y*offset_y) - precomputed_exp_y);
}
