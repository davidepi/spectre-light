#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "samplers/sampler.hpp"
#include "samplers/sampler_stratified.hpp"
#include "samplers/sampler_random.hpp"
#include "samplers/distributions.hpp"

SPECTRE_TEST_INIT(Sampler_tests)

SPECTRE_TEST(Sampler, get_random_numbers)
{
    unsigned int seed[32];
    for(int i = 0; i<32; i++)
        seed[i] = i;
    SamplerStratified sam(0, 1, 0, 1, 10, seed, true);
    float values[1000];
    sam.get_random_numbers(values, 1000);
    for(int i = 0; i<1000; i++)
    {
        EXPECT_GT(values[i], 0.f);
        EXPECT_LT(values[i], 1.f);
    }
}

SPECTRE_TEST(Sampler, Stratified_get_samples)
{
    unsigned int seed[32];
    for(int i = 0; i<32; i++)
        seed[i] = i;
    SamplerStratified sam(0, 2, 0, 2, 100, seed, true);
    Sample samples[100];
    bool res;

    //jittered
    res = sam.get_samples(samples);
    EXPECT_TRUE(res);
    res = sam.get_samples(samples);
    EXPECT_TRUE(res);
    res = sam.get_samples(samples);
    EXPECT_TRUE(res);
    res = sam.get_samples(samples);
    EXPECT_TRUE(res);
    res = sam.get_samples(samples);
    EXPECT_FALSE(res);

    //non jittered
    SamplerStratified sam2(0, 2, 0, 2, 100, seed, false);
    res = sam2.get_samples(samples);
    EXPECT_TRUE(res);
    res = sam2.get_samples(samples);
    EXPECT_TRUE(res);
    res = sam2.get_samples(samples);
    EXPECT_TRUE(res);
    res = sam2.get_samples(samples);
    EXPECT_TRUE(res);
    res = sam2.get_samples(samples);
    EXPECT_FALSE(res);
}

SPECTRE_TEST(Sampler, Random_get_samples)
{
    unsigned int seed[32];
    for(int i = 0; i<32; i++)
        seed[i] = i;
    SamplerRandom sam(0, 2, 0, 2, 100, seed);
    Sample samples[100];
    bool res;

    res = sam.get_samples(samples);
    EXPECT_TRUE(res);
    res = sam.get_samples(samples);
    EXPECT_TRUE(res);
    res = sam.get_samples(samples);
    EXPECT_TRUE(res);
    res = sam.get_samples(samples);
    EXPECT_TRUE(res);
    res = sam.get_samples(samples);
    EXPECT_FALSE(res);
}

SPECTRE_TEST(Sampler, Distribution1D_sample_continuous)
{
    float vals[] = {1, 2, 3, 4, 5, 6};
    Distribution1D dist(vals, 6);
    float pdf;
    EXPECT_EQ(dist.sample_continuous(0.f), 0.f);
    EXPECT_NEAR(dist.sample_continuous(0.5f, &pdf), 0.68333f, 1e-2f);
    EXPECT_NEAR(pdf, 1.428f, 1e-3f);
}

SPECTRE_TEST(Sampler, Distribution1D_get_integral_value)
{
    float vals[] = {1, 2, 3, 4, 5, 6};
    Distribution1D dist(vals, 6);
    EXPECT_EQ(dist.get_integral_value(), 3.5f);

    //integral 0
    float vals2[] = {0, 0, 0, 0, 0};
    Distribution1D dist2(vals2, 5);
    EXPECT_EQ(dist2.get_integral_value(), 0.f);
}

SPECTRE_TEST(Sampler, Distribution1D_get_piecewise_value)
{
    float vals[] = {1, 2, 3, 4, 5, 6};
    Distribution1D dist(vals, 6);
    EXPECT_EQ(dist.get_piecewise_value(0), 1.f);
    EXPECT_EQ(dist.get_piecewise_value(1), 2.f);
    EXPECT_EQ(dist.get_piecewise_value(2), 3.f);
    EXPECT_EQ(dist.get_piecewise_value(3), 4.f);
    EXPECT_EQ(dist.get_piecewise_value(4), 5.f);
    EXPECT_EQ(dist.get_piecewise_value(5), 6.f);
}

SPECTRE_TEST(Sampler, Distribution2D_sample_continuous)
{
    float vals[] = {0, 0, 0, 0,
                    0, 1, 1, 0,
                    0, 1, 1, 0,
                    0, 0, 0, 0};
    Distribution2D dist(vals, 4, 4);
    float pdf;
    Point2 res;
    Point2 check(0.25f, 0.25f);
    res = dist.sample_continuous(0.f, 0.f);
    EXPECT_EQ(res.x, check.x);
    EXPECT_EQ(res.y, check.y);

    check = Point2(0.5f, 0.5f);
    res = dist.sample_continuous(.5f, .5f, &pdf);
    EXPECT_EQ(res.x, check.x);
    EXPECT_EQ(res.y, check.y);
    EXPECT_EQ(pdf, 4.f);
}

SPECTRE_TEST(Sampler, Distribution2D_pdf)
{
    float vals[] = {0, 0, 0, 0,
                    0, 1, 1, 0,
                    0, 1, 1, 0,
                    0, 0, 0, 0};
    Distribution2D dist(vals, 4, 4);
    float pdf = dist.pdf(Point2(0.5f, 0.5f));
    EXPECT_EQ(pdf, 4.f);
}

SPECTRE_TEST_END(Sampler_tests)
