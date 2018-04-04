
#include <gtest/gtest.h>


#include "samplers/filter.hpp"
#include "samplers/filter_box.hpp"
#include "samplers/filter_tent.hpp"
#include "samplers/filter_gaussian.hpp"
#include "samplers/filter_mitchell.hpp"
#include "samplers/filter_lanczos.hpp"
#include "utility/utility.hpp"
#define PRECISION 0.001f

TEST(Filter,box_filter)
{
    const float extent = 1;
    FilterBox f;
    EXPECT_EQ(f.weight(1.f, 1.f), 1.f);

    float mean = 0.f;
    float stddev= 0.f;
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

    mean = 0.f;
    stddev = 0.f;
    //mean, y fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
        mean+= f.weight(0, i);
    mean/=samples;

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
    const float extent = 2;
    FilterTent f;
    EXPECT_EQ(f.weight(0.f, 0.f), 1.f);
    EXPECT_EQ(f.weight(0.f,extent/2), 1/2.f);
    EXPECT_EQ(f.weight(extent/2,0.f), 1/2.f);
    EXPECT_EQ(f.weight(extent/2,extent/2), 1/4.f);
    EXPECT_EQ(f.weight(extent,extent), 0.f);
    EXPECT_EQ(f.weight(extent+1,extent/2.f), 0.f);

    float mean = 0.f;
    float stddev= 0.f;
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
    EXPECT_FLOAT_EQ(mean, .49987236f);
    EXPECT_FLOAT_EQ(stddev, .2886439f);
    mean = 0.f;
    stddev = 0.f;
    //mean, y fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
        mean+= f.weight(0, i);
    mean/=samples;
    //stddev, y fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
    {
        float sample = f.weight(0, i) - mean;
        stddev+=sample*sample;
    }
    stddev = sqrtf(stddev/samples);
    EXPECT_FLOAT_EQ(mean, .49987236f);
    EXPECT_FLOAT_EQ(stddev, .2886439f);
}

TEST(Filter,gaussian_filter)
{
    const float extent = 2;
    FilterGaussian f(2.f);
    EXPECT_GT(f.weight(0.f,0.f), 0.999f);
    EXPECT_LT(f.weight(0.f,0.f), 1.f);
    EXPECT_NE(f.weight(0.5f,0.5f),0.5f); // assert non linearity
    EXPECT_GT(f.weight(0.9f,0.9f), 0); //non negative tails
    EXPECT_EQ(f.weight(2.f,2.f),0.f);

    float mean = 0.f;
    float stddev= 0.f;
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
    EXPECT_FLOAT_EQ(mean, .31279147f);
    EXPECT_FLOAT_EQ(stddev, .35111403f);
    mean = 0.f;
    stddev = 0.f;
    //mean, y fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
        mean+= f.weight(0, i);
    mean/=samples;
    //stddev, y fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
    {
        float sample = f.weight(0, i) - mean;
        stddev+=sample*sample;
    }
    stddev = sqrtf(stddev/samples);
    EXPECT_FLOAT_EQ(mean, .31279147f);
    EXPECT_FLOAT_EQ(stddev, .35111403f);
}

TEST(Filter,mitchell_filter)
{
    const float extent = 2;
    FilterMitchell f(0.33f,0.33f);
    EXPECT_GT(f.weight(0.f,0.f), 0.75f);
    EXPECT_LT(f.weight(0.f,0.f), 1.f);
    EXPECT_NE(f.weight(0.5f,0.f),0.5f); // assert non linearity
    EXPECT_LT(f.weight(1.5f,0.f), 0.f); //negative tails
    //fuck you gtest, 1e-07 != 0 with expect_float_eq
    EXPECT_TRUE(flt_equal(f.weight(extent,0.f),0.f)); //zeroed end


    float mean = 0.f;
    float stddev= 0.f;
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
    EXPECT_FLOAT_EQ(mean, .22244677f);
    EXPECT_FLOAT_EQ(stddev, .29243484f);
    mean = 0.f;
    stddev = 0.f;
    //mean, y fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
        mean+= f.weight(0, i);
    mean/=samples;
    //stddev, y fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
    {
        float sample = f.weight(0, i) - mean;
        stddev+=sample*sample;
    }
    stddev = sqrtf(stddev/samples);
    EXPECT_FLOAT_EQ(mean, .22244677f);
    EXPECT_FLOAT_EQ(stddev, .29243484f);
}

TEST(Filter,lanczos_filter)
{
    const float extent = 4;
    FilterLanczos f(3.f);
    EXPECT_GT(f.weight(0.f,0.f), 0.999f);
    EXPECT_LT(f.weight(0.f,0.f), 1.001f);
    EXPECT_NE(f.weight(0.5f,0.f),0.5f); // assert non linearity
    EXPECT_LT(f.weight(2.f,0.f), 0.f); //negative tails
    EXPECT_GT(f.weight(3.5f,0.f), 0.f); //then positive tails
    //fuck you again gtest, 1e-17 != 0 with expect_float_eq
    EXPECT_TRUE(flt_equal(f.weight(extent,0.f),0.f)); //finish at 0
    EXPECT_EQ(f.weight(2.f,4+1.f),0.f); //out of bounds
    EXPECT_EQ(f.weight(4+1.f,2.f),0.f); //out of bounds

    float mean = 0.f;
    float stddev= 0.f;
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
    EXPECT_FLOAT_EQ(mean, .1661562f);
    EXPECT_FLOAT_EQ(stddev, .3470515f);
    mean = 0.f;
    stddev = 0.f;
    //mean, y fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
        mean+= f.weight(0, i);
    mean/=samples;
    //stddev, y fixed
    for(float i=-extent;i<=extent;i+=PRECISION)
    {
        float sample = f.weight(0, i) - mean;
        stddev+=sample*sample;
    }
    stddev = sqrtf(stddev/samples);
    EXPECT_FLOAT_EQ(mean, .1661562f);
    EXPECT_FLOAT_EQ(stddev, .3470515f);
}

