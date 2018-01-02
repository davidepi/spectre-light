
#include <gtest/gtest.h>


#include "samplers/filter.hpp"
#include "samplers/box_filter.hpp"
#include "samplers/tent_filter.hpp"
#include "samplers/gaussian_filter.hpp"
#include "samplers/mitchell_filter.hpp"
#include "samplers/lanczos_filter.hpp"
#include "utility/utility.hpp"
#define PRECISION 0.001f

TEST(Filter,box_filter)
{
    BoxFilter f(1.f,1.f);
    EXPECT_EQ(f.weight(1.f, 1.f), 1.f);

    float mean = 0.f;
    float stddev= 0.f;
    float extent = BOX_FILTER_EXTENT;
    //+2 for the bounds
    int samples = (extent*2)/PRECISION+2;

    //mean, x fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
        mean+= f.weight(i, 0);
    mean/=samples;

    //stddev, x fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
    {
        float sample = f.weight(i, 0) - mean;
        stddev+=sample*sample;
    }
    stddev = sqrtf(stddev/samples);

    EXPECT_EQ(mean, 1.f);
    EXPECT_EQ(stddev, 0.f);

    //mean, y fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
        mean+= f.weight(0, i);
    mean/=samples;

    mean = 0.f;
    stddev = 0.f;
    //stddev, y fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
    {
        float sample = f.weight(0, i) - mean;
        stddev+=sample*sample;
    }
    stddev = sqrtf(stddev/samples);

    EXPECT_EQ(mean, 1.f);
    EXPECT_EQ(stddev, 0.f);

}

TEST(Filter,tent_filter)
{
    TentFilter f(4.f,4.f);
    EXPECT_EQ(f.weight(0.f, 0.f), 1.f);
    EXPECT_EQ(f.weight(0.f,2.f), 0.5f);
    EXPECT_EQ(f.weight(2.f,0.f), 0.5f);
    EXPECT_EQ(f.weight(2.f,2.f), 0.25f);
    EXPECT_EQ(f.weight(4.f,4.f), 0.f);
    EXPECT_EQ(f.weight(5.f,2.f), 0.f);

    float mean = 0.f;
    float stddev= 0.f;
    float extent = TENT_FILTER_EXTENT;
    //+2 for the bounds
    int samples = (extent*2)/PRECISION+2;
    //mean, x fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
        mean+= f.weight(i, 0);
    mean/=samples;
    //stddev, x fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
    {
        float sample = f.weight(i, 0) - mean;
        stddev+=sample*sample;
    }
    stddev = sqrtf(stddev/samples);
    EXPECT_FLOAT_EQ(mean, .5f);
    EXPECT_FLOAT_EQ(stddev, .2886268f);
    //mean, y fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
        mean+= f.weight(0, i);
    mean/=samples;
    mean = 0.f;
    stddev = 0.f;
    //stddev, y fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
    {
        float sample = f.weight(0, i) - mean;
        stddev+=sample*sample;
    }
    stddev = sqrtf(stddev/samples);
    EXPECT_FLOAT_EQ(mean, .5f);
    EXPECT_FLOAT_EQ(stddev, .2886268f);
}

TEST(Filter,gaussian_filter)
{
    GaussianFilter f(2.f,2.f,2.f);
    EXPECT_GT(f.weight(0.f,0.f), 0.999f);
    EXPECT_LT(f.weight(0.f,0.f), 1.f);
    EXPECT_NE(f.weight(0.5f,0.5f),0.5f); // assert non linearity
    EXPECT_GT(f.weight(0.9f,0.9f), 0); //non negative tails
    EXPECT_EQ(f.weight(2.f,2.f),0.f);
}

TEST(Filter,mitchell_filter)
{
    MitchellFilter f(2.f,2.f,0.33f,0.33f);
    f.weight(-1.5f,0.f);
    EXPECT_GT(f.weight(0.f,0.f), 0.999f);
    EXPECT_LT(f.weight(0.f,0.f), 1.f);
    EXPECT_NE(f.weight(0.5f,0.5f),0.5f); // assert non linearity
    EXPECT_LT(f.weight(1.5f,1.5f), 0); //non negative tails
    EXPECT_EQ(f.weight(2.f,2.f),0.f);

}

