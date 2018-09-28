//author: Davide Pizzolotto
//license: GNU GPLv3

#include "filter_gaussian.hpp"

///Number of pixels affected by the gaussian filter on the x axis
#define EXTENT_FILTER_GAUSSIAN_X 2
///Number of pixels affected by the gaussian filter on the y axis
#define EXTENT_FILTER_GAUSSIAN_Y 2

FilterGaussian::FilterGaussian(float falloff)
        :Filter(EXTENT_FILTER_GAUSSIAN_X, EXTENT_FILTER_GAUSSIAN_Y)
{
    FilterGaussian::precomputed_exp_x =
            expf(-falloff*EXTENT_FILTER_GAUSSIAN_X*EXTENT_FILTER_GAUSSIAN_X);
    FilterGaussian::precomputed_exp_y =
            expf(-falloff*EXTENT_FILTER_GAUSSIAN_Y*EXTENT_FILTER_GAUSSIAN_Y);
    FilterGaussian::alpha = falloff;
}

float FilterGaussian::weight(float offset_x, float offset_y) const
{
    //f(x) = e^(-alpha*x^2)-e^(-alpha*width^2)
    //where the second term is used to let the gaussian tend to zero at its
    //limit and is precomputed in the constructor
    return max(0.f, expf(-alpha*offset_x*offset_x)-precomputed_exp_x)*
           max(0.f, expf(-alpha*offset_y*offset_y)-precomputed_exp_y);
}

float FilterGaussian::get_param0() const
{
    return alpha;
}

float FilterGaussian::get_param1() const
{
    return -1.f;
}
