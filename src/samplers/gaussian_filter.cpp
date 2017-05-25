#include "gaussian_filter.hpp"

GaussianFilter::GaussianFilter(float x_r, float y_r, float falloff)
        : Filter(x_r,y_r)
{
    GaussianFilter::precomputed_exp_x = expf(-falloff*x_r*x_r);
    GaussianFilter::precomputed_exp_y = expf(-falloff*y_r*y_r);
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
