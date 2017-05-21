#include "gaussian_filter.hpp"

GaussianFilter::GaussianFilter(float x_range, float y_range, float falloff)
        : Filter()
{
    GaussianFilter::precomputed_exp_x = expf(-falloff*x_range*x_range);
    GaussianFilter::precomputed_exp_y = expf(-falloff*y_range*y_range);
    GaussianFilter::alpha = falloff;
}

GaussianFilter::~GaussianFilter()
{

}

float GaussianFilter::weight(float offset_x, float offset_y)const
{
    //f(x) = e^(-alpha*x^2)-e^(-alpha*width^2)
    //where the second term is used to let the gaussian tend to zero at its
    //limit and is precomputed in the constructor
    return max(0.f,expf(-alpha*offset_x*offset_x) - precomputed_exp_x) *
           max(0.f,expf(-alpha*offset_y*offset_y) - precomputed_exp_y);
}
