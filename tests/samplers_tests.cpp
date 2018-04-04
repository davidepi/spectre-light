
#include <gtest/gtest.h>


#include "samplers/sampler.hpp"
#include "samplers/sampler_stratified.hpp"
#include "samplers/sampler_random.hpp"

TEST(Sampler,get_random_numbers)
{
    unsigned int seed[32];
    for(int i=0;i<32;i++)
        seed[i]=i;
    SamplerStratified sam(0,1,0,1,10,seed,true);
    float values[1000];
    sam.get_random_numbers(values, 1000);
    for(int i=0;i<1000;i++)
    {
        EXPECT_GT(values[i], 0.f);
        EXPECT_LT(values[i], 1.f);
    }
}

TEST(Sampler,Stratified_get_samples)
{
    unsigned int seed[32];
    for(int i=0;i<32;i++)
        seed[i]=i;
    SamplerStratified sam(0,2,0,2,100,seed,true);
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
    SamplerStratified sam2(0,2,0,2,100,seed,false);
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

TEST(Sampler,Random_get_samples)
{
    unsigned int seed[32];
    for(int i=0;i<32;i++)
        seed[i]=i;
    SamplerRandom sam(0,2,0,2,100,seed);
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

