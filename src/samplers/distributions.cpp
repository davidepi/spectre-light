#include <cstring>
#include <algorithm>
#include "distributions.hpp"

Distribution1D::Distribution1D(const float* data, size_t length)
{
    num = length;
    values = (float*)malloc(sizeof(float)*length);
    cdf = (float*)malloc(sizeof(float)*(length+1));
    cdf[0] = 0.f;
    memcpy(Distribution1D::values, data, sizeof(float)*length);
    const float INVLEN = 1.f/length;
    for(size_t i = 1; i<length+1; i++)
        cdf[i] = cdf[i-1]+values[i-1]*INVLEN;
    integral_value = cdf[length];
    if(integral_value == 0)
    {
        for(size_t i = 1; i<length; i++)
            cdf[i] *= (float)i/(float)length;
    }
    else
    {
        const float INT_INV = 1.f/integral_value;
        for(size_t i = 1; i<length; i++)
            cdf[i] *= INT_INV;
    }
}

Distribution1D::~Distribution1D()
{
    free(values);
    free(cdf);
}

float Distribution1D::sample_continuous(float u, float* pdf) const
{
    int start = 0;
    int end = (int)num;
    int current = 0;
    //find lower_bound
    while(current<end)
    {
        int half = end >> 1;
        int middle = start+half;
        if(cdf[middle]<=u)
        {
            start = middle+1;
            end -= half+1;
        }
        else
            end = half;
    }
    int offset = (int)clamp(start-1, 0, num-2);

    float du = (u-cdf[offset]);
    float du_den = cdf[offset+1]-cdf[offset];
    if(du_den>0)
        du /= du_den;
    if(pdf != NULL)
        *pdf = values[offset]/integral_value;
    return (offset+du)/num;
}

float Distribution1D::get_integral_value() const
{
    return integral_value;
}

float Distribution1D::get_piecewise_value(int index) const
{
    return Distribution1D::values[index];
}

Distribution2D::Distribution2D(const float* data, size_t len_x, size_t len_y)
{
    Distribution2D::marginal_len = len_y;
    conditional = new Distribution1D* [len_y];
    float* marginal_vals = (float*)malloc(sizeof(float)*len_y);
    for(size_t i = 0; i<len_y; i++)
    {
        conditional[i] = new Distribution1D(&(data[i*len_x]), len_x);
        marginal_vals[i] = conditional[i]->get_integral_value();
    }
    marginal = new Distribution1D(marginal_vals, len_y);
    free(marginal_vals);
}

Distribution2D::~Distribution2D()
{
    for(size_t i = 0; i<marginal_len; i++)
        delete conditional[i];
    delete[] conditional;
    delete marginal;
}

Point2 Distribution2D::sample_continuous(float u0, float u1, float* pdf) const
{
    float pdf0;
    float pdf1;
    Point2 res;
    res.y = marginal->sample_continuous(u1, &pdf1);
    int v = (int)clamp((int)(res.y*marginal_len), 0.f, marginal_len-1);
    res.x = conditional[v]->sample_continuous(u0, &pdf0);
    if(pdf != NULL)
        *pdf = pdf0*pdf1;
    return res;
}

float Distribution2D::pdf(Point2 value) const
{
    int u = (int)clamp((int)(value.x*marginal_len), 0, marginal_len-1);
    int v = (int)clamp((int)(value.y*marginal_len), 0, marginal_len-1);
    return conditional[v]->get_piecewise_value(u)/
           marginal->get_integral_value();
}
