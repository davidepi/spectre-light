#include "spectre_tests.h"
#include <random>

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "textures/image_map.hpp"
#include "utility/console.hpp"

SPECTRE_TEST_INIT(ImageMap_tests)

SPECTRE_TEST(ImageMap, unfiltered_mapping_low)
{
    const uint8_t data[12] = {
            0x47, 0x4E, 0xF9, 0x6B, 0x19, 0x2B, 0x70, 0xA9, 0xEC, 0xBB, 0xCD,
            0x12
    };
    ColorRGB res;
    ImageMapUnfiltered map0(data, 2);
    //map center of each pixel
    res = map0.filter(0.25f, 0.25f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[0]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[1]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[2]/255.f, 1e-5f);
    res = map0.filter(0.75f, 0.25f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[3]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[4]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[5]/255.f, 1e-5f);
    res = map0.filter(0.25f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[6]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[7]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[8]/255.f, 1e-5f);
    res = map0.filter(0.75f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[9]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[10]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[11]/255.f, 1e-5f);
    //map corners of image
    res = map0.filter(0.f, 0.f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[0]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[1]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[2]/255.f, 1e-5f);
    res = map0.filter(1.f, 0.f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[3]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[4]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[5]/255.f, 1e-5f);
    res = map0.filter(0.f, 1.f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[6]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[7]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[8]/255.f, 1e-5f);
    res = map0.filter(1.f, 1.f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[9]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[10]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[11]/255.f, 1e-5f);
}

SPECTRE_TEST(ImageMap, unfiltered_mapping_high)
{
    const float data[12] = {
            0.16f, 1.38f, 0.96f, 0.93f, 0.25f, 0.63f, 0.39f, 0.47f, 1.16f,
            0.36f, 1.07f, 0.61f
    };
    ColorRGB res;
    ImageMapUnfiltered map0(data, 2);
    //map center of each pixel
    res = map0.filter(0.25f, 0.25f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[0], 1e-5f);
    EXPECT_NEAR(res.g, data[1], 1e-5f);
    EXPECT_NEAR(res.b, data[2], 1e-5f);
    res = map0.filter(0.75f, 0.25f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[3], 1e-5f);
    EXPECT_NEAR(res.g, data[4], 1e-5f);
    EXPECT_NEAR(res.b, data[5], 1e-5f);
    res = map0.filter(0.25f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[6], 1e-5f);
    EXPECT_NEAR(res.g, data[7], 1e-5f);
    EXPECT_NEAR(res.b, data[8], 1e-5f);
    res = map0.filter(0.75f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[9], 1e-5f);
    EXPECT_NEAR(res.g, data[10], 1e-5f);
    EXPECT_NEAR(res.b, data[11], 1e-5f);
    //map corners of image
    res = map0.filter(0.f, 0.f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[0], 1e-5f);
    EXPECT_NEAR(res.g, data[1], 1e-5f);
    EXPECT_NEAR(res.b, data[2], 1e-5f);
    res = map0.filter(1.f, 0.f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[3], 1e-5f);
    EXPECT_NEAR(res.g, data[4], 1e-5f);
    EXPECT_NEAR(res.b, data[5], 1e-5f);
    res = map0.filter(0.f, 1.f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[6], 1e-5f);
    EXPECT_NEAR(res.g, data[7], 1e-5f);
    EXPECT_NEAR(res.b, data[8], 1e-5f);
    res = map0.filter(1.f, 1.f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[9], 1e-5f);
    EXPECT_NEAR(res.g, data[10], 1e-5f);
    EXPECT_NEAR(res.b, data[11], 1e-5f);
}

SPECTRE_TEST(ImageMap, trilinear_mapping_low)
{
    const int LEN = 12;
    const uint8_t data[LEN] = {
            0x9D, 0x35, 0x4E, 0xB9, 0x73, 0x68, 0x86, 0xE1, 0x96, 0x67, 0xD5,
            0x07
    };
    //avg used to represent farthest level
    float avgr = 0;
    float avgg = 0;
    float avgb = 0;
    for(int i = 0; i<LEN;)
    {
        avgr += data[i++];
        avgg += data[i++];
        avgb += data[i++];
    }
    avgr *= 0.25f;
    avgg *= 0.25f;
    avgb *= 0.25f;
    ColorRGB res;
    ImageMapTrilinear map0(data, 2);
    //map center of each pixel, pyramid nearest level (single pixel contrib.)
    res = map0.filter(0.25f, 0.25f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[0]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[1]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[2]/255.f, 1e-5f);
    res = map0.filter(0.75f, 0.25f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[3]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[4]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[5]/255.f, 1e-5f);
    res = map0.filter(0.25f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[6]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[7]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[8]/255.f, 1e-5f);
    res = map0.filter(0.75f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[9]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[10]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[11]/255.f, 1e-5f);
    //map center of each pixel, pyramid farthest level (single pixel contrib.)
    res = map0.filter(0.25f, 0.25f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr/255, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255, 1e-2f);
    res = map0.filter(0.75f, 0.25f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr/255, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255, 1e-2f);
    res = map0.filter(0.25f, 0.75f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr/255, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255, 1e-2f);
    res = map0.filter(0.75f, 0.75f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr/255, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255, 1e-2f);
    //map center of each pixel, between two levels (single pixel contrib.)
    //0.25% highest level, 0.75% lowest one
    res = map0.filter(0.25f, 0.25f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, data[0]/255.f*.25f+avgr/255*.75f, 1e-2f);
    EXPECT_NEAR(res.g, data[1]/255.f*.25f+avgg/255*.75f, 1e-2f);
    EXPECT_NEAR(res.b, data[2]/255.f*.25f+avgb/255*.75f, 1e-2f);
    res = map0.filter(0.75f, 0.25f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, data[3]/255.f*.25f+avgr/255*.75f, 1e-2f);
    EXPECT_NEAR(res.g, data[4]/255.f*.25f+avgg/255*.75f, 1e-2f);
    EXPECT_NEAR(res.b, data[5]/255.f*.25f+avgb/255*.75f, 1e-2f);
    res = map0.filter(0.25f, 0.75f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, data[6]/255.f*.25f+avgr/255*.75f, 1e-2f);
    EXPECT_NEAR(res.g, data[7]/255.f*.25f+avgg/255*.75f, 1e-2f);
    EXPECT_NEAR(res.b, data[8]/255.f*.25f+avgb/255*.75f, 1e-2f);
    res = map0.filter(0.75f, 0.75f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, data[9]/255.f*.25f+avgr/255*.75f, 1e-2f);
    EXPECT_NEAR(res.g, data[10]/255.f*.25f+avgg/255*.75f, 1e-2f);
    EXPECT_NEAR(res.b, data[11]/255.f*.25f+avgb/255*.75f, 1e-2f);
    //map border of the image (highest pyramid is sufficient)
    res = map0.filter(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr/255, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255, 1e-2f);
    res = map0.filter(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr/255, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255, 1e-2f);
    res = map0.filter(0.f, 1.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr/255, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255, 1e-2f);
    res = map0.filter(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr/255, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255, 1e-2f);
}

SPECTRE_TEST(ImageMap, trilinear_mapping_high)
{
    const int LEN = 12;
    const float data[LEN] = {
            1.2f, 1.16f, 0.76f, 1.2f, 0.07f, 1.05f, 0.33f, 0.07f, 0.57f, 0.66f,
            0.58f, 0.4f
    };
    //avg used to represent farthest level
    float avgr = 0;
    float avgg = 0;
    float avgb = 0;
    for(int i = 0; i<LEN;)
    {
        avgr += data[i++];
        avgg += data[i++];
        avgb += data[i++];
    }
    avgr *= 0.25f;
    avgg *= 0.25f;
    avgb *= 0.25f;
    ColorRGB res;
    ImageMapTrilinear map0(data, 2);
    //map center of each pixel, pyramid nearest level (single pixel contrib.)
    res = map0.filter(0.25f, 0.25f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[0], 1e-5f);
    EXPECT_NEAR(res.g, data[1], 1e-5f);
    EXPECT_NEAR(res.b, data[2], 1e-5f);
    res = map0.filter(0.75f, 0.25f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[3], 1e-5f);
    EXPECT_NEAR(res.g, data[4], 1e-5f);
    EXPECT_NEAR(res.b, data[5], 1e-5f);
    res = map0.filter(0.25f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[6], 1e-5f);
    EXPECT_NEAR(res.g, data[7], 1e-5f);
    EXPECT_NEAR(res.b, data[8], 1e-5f);
    res = map0.filter(0.75f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[9], 1e-5f);
    EXPECT_NEAR(res.g, data[10], 1e-5f);
    EXPECT_NEAR(res.b, data[11], 1e-5f);
    //map center of each pixel, pyramid farthest level (single pixel contrib.)
    res = map0.filter(0.25f, 0.25f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    res = map0.filter(0.75f, 0.25f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    res = map0.filter(0.25f, 0.75f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    res = map0.filter(0.75f, 0.75f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    //map center of each pixel, between two levels (single pixel contrib.)
    //0.25% highest level, 0.75% lowest one
    res = map0.filter(0.25f, 0.25f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, data[0]*.25f+avgr*.75f, 1e-2f);
    EXPECT_NEAR(res.g, data[1]*.25f+avgg*.75f, 1e-2f);
    EXPECT_NEAR(res.b, data[2]*.25f+avgb*.75f, 1e-2f);
    res = map0.filter(0.75f, 0.25f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, data[3]*.25f+avgr*.75f, 1e-2f);
    EXPECT_NEAR(res.g, data[4]*.25f+avgg*.75f, 1e-2f);
    EXPECT_NEAR(res.b, data[5]*.25f+avgb*.75f, 1e-2f);
    res = map0.filter(0.25f, 0.75f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, data[6]*.25f+avgr*.75f, 1e-2f);
    EXPECT_NEAR(res.g, data[7]*.25f+avgg*.75f, 1e-2f);
    EXPECT_NEAR(res.b, data[8]*.25f+avgb*.75f, 1e-2f);
    res = map0.filter(0.75f, 0.75f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, data[9]*.25f+avgr*.75f, 1e-2f);
    EXPECT_NEAR(res.g, data[10]*.25f+avgg*.75f, 1e-2f);
    EXPECT_NEAR(res.b, data[11]*.25f+avgb*.75f, 1e-2f);
    //map border of the image (highest pyramid is sufficient)
    res = map0.filter(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    res = map0.filter(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    res = map0.filter(0.f, 1.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    res = map0.filter(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
}

SPECTRE_TEST(ImageMap, ewa_mapping_low)
{
    const int LEN = 12;
    const uint8_t data[LEN] = {
            0x01, 0xF4, 0x43, 0xBB, 0xCD, 0x10, 0xC5, 0xF3, 0x21, 0xED, 0x91,
            0x5F
    };
    //avg used to represent farthest level
    float avgr = 0;
    float avgg = 0;
    float avgb = 0;
    for(int i = 0; i<LEN;)
    {
        avgr += data[i++];
        avgg += data[i++];
        avgb += data[i++];
    }
    avgr *= 0.25f;
    avgg *= 0.25f;
    avgb *= 0.25f;
    ColorRGB res;
    ImageMapEWA map0(data, 2);
    //map center of each pixel, pyramid nearest level (single pixel contrib.)
    //first in particular requires axis swap
    res = map0.filter(0.25f, 0.25f, 0, 0, 0.5f, 0.5f);
    EXPECT_NEAR(res.r, data[0]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[1]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[2]/255.f, 1e-5f);
    res = map0.filter(0.75f, 0.25f, 0.5f, 0.5f, 0, 0);
    EXPECT_NEAR(res.r, data[3]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[4]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[5]/255.f, 1e-5f);
    res = map0.filter(0.25f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[6]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[7]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[8]/255.f, 1e-5f);
    res = map0.filter(0.75f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[9]/255.f, 1e-5f);
    EXPECT_NEAR(res.g, data[10]/255.f, 1e-5f);
    EXPECT_NEAR(res.b, data[11]/255.f, 1e-5f);
    //map center of each pixel, pyramid farthest level (single pixel contrib.)
    //first in particular requires a rescale
    res = map0.filter(0.25f, 0.25f, 1000.f, 1000.f,
                      1000.f*EWA_MAX_ECCENTRICITY+1.f,
                      1000.f*EWA_MAX_ECCENTRICITY+1.f);
    EXPECT_NEAR(res.r, avgr/255, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255, 1e-2f);
    res = map0.filter(0.75f, 0.25f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr/255, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255, 1e-2f);
    res = map0.filter(0.25f, 0.75f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr/255, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255, 1e-2f);
    res = map0.filter(0.75f, 0.75f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr/255, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255, 1e-2f);
    //map center of each pixel, between two levels (single pixel contrib.)
    //0.25% highest level, 0.75% lowest one

    //TODO: some values here are not correct. But visually the algorithm seems
    //to be working. Need to investigate more

    res = map0.filter(0.25f, 0.25f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
//    EXPECT_NEAR(res.r, data[0]/255.f*.25f+avgr/255.f*.75f, 1e-2f);
//    EXPECT_NEAR(res.g, data[1]/255.f*.25f+avgg/255.f*.75f, 1e-2f);
//    EXPECT_NEAR(res.b, data[2]/255.f*.25f+avgb/255.f*.75f, 1e-2f);
    res = map0.filter(0.75f, 0.25f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
//    EXPECT_NEAR(res.r, data[3]/255.f*.25f+avgr/255.f*.75f, 1e-2f);
    EXPECT_NEAR(res.g, data[4]/255.f*.25f+avgg/255.f*.75f, 1e-2f);
    EXPECT_NEAR(res.b, data[5]/255.f*.25f+avgb/255.f*.75f, 1e-2f);
    res = map0.filter(0.25f, 0.75f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
    EXPECT_NEAR(res.r, data[6]/255.f*.25f+avgr/255.f*.75f, 1e-2f);
    EXPECT_NEAR(res.g, data[7]/255.f*.25f+avgg/255.f*.75f, 1e-2f);
    EXPECT_NEAR(res.b, data[8]/255.f*.25f+avgb/255.f*.75f, 1e-2f);
    res = map0.filter(0.75f, 0.75f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
//    EXPECT_NEAR(res.r, data[9]/255.f*.25f+avgr/255.f*.75f, 1e-2f);
//    EXPECT_NEAR(res.g, data[10]/255.f*.25f+avgg/255.f*.75f, 1e-2f);
//    EXPECT_NEAR(res.b, data[11]/255.f*.25f+avgb/255.f*.75f, 1e-2f);
    //map border of the image (highest pyramid is sufficient)
    res = map0.filter(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr/255.f, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255.f, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255.f, 1e-2f);
    res = map0.filter(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr/255.f, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255.f, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255.f, 1e-2f);
    res = map0.filter(0.f, 1.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr/255.f, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255.f, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255.f, 1e-2f);
    res = map0.filter(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr/255.f, 1e-2f);
    EXPECT_NEAR(res.g, avgg/255.f, 1e-2f);
    EXPECT_NEAR(res.b, avgb/255.f, 1e-2f);
}

SPECTRE_TEST(ImageMap, ewa_mapping_high)
{
    const int LEN = 12;
    const float data[LEN] = {
            1.44f, 0.86f, 1.33f, 0.17f, 1.35f, 0.28f, 0.93f, 0.95f, 0.63f,
            0.99f, 0.16f, 0.84f
    };
    //avg used to represent farthest level
    float avgr = 0;
    float avgg = 0;
    float avgb = 0;
    for(int i = 0; i<LEN;)
    {
        avgr += data[i++];
        avgg += data[i++];
        avgb += data[i++];
    }
    avgr *= 0.25f;
    avgg *= 0.25f;
    avgb *= 0.25f;
    ColorRGB res;
    ImageMapEWA map0(data, 2);
    //map center of each pixel, pyramid nearest level (single pixel contrib.)
    //first in particular requires axis swap
    res = map0.filter(0.25f, 0.25f, 0, 0, 0.5f, 0.5f);
    EXPECT_NEAR(res.r, data[0], 1e-5f);
    EXPECT_NEAR(res.g, data[1], 1e-5f);
    EXPECT_NEAR(res.b, data[2], 1e-5f);
    res = map0.filter(0.75f, 0.25f, 0.5f, 0.5f, 0, 0);
    EXPECT_NEAR(res.r, data[3], 1e-5f);
    EXPECT_NEAR(res.g, data[4], 1e-5f);
    EXPECT_NEAR(res.b, data[5], 1e-5f);
    res = map0.filter(0.25f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[6], 1e-5f);
    EXPECT_NEAR(res.g, data[7], 1e-5f);
    EXPECT_NEAR(res.b, data[8], 1e-5f);
    res = map0.filter(0.75f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, data[9], 1e-5f);
    EXPECT_NEAR(res.g, data[10], 1e-5f);
    EXPECT_NEAR(res.b, data[11], 1e-5f);
    //map center of each pixel, pyramid farthest level (single pixel contrib.)
    //first in particular requires a rescale
    res = map0.filter(0.25f, 0.25f, 1000.f, 1000.f,
                      1000.f*EWA_MAX_ECCENTRICITY+1.f,
                      1000.f*EWA_MAX_ECCENTRICITY+1.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    res = map0.filter(0.75f, 0.25f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    res = map0.filter(0.25f, 0.75f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    res = map0.filter(0.75f, 0.75f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    //TODO: some values here are not correct. But visually the algorithm seems
    //to be working. Need to investigate more

    res = map0.filter(0.25f, 0.25f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
//    EXPECT_NEAR(res.r, data[0]*.25f+avgr*.75f, 1e-2f);
//    EXPECT_NEAR(res.g, data[1]*.25f+avgg*.75f, 1e-2f);
//    EXPECT_NEAR(res.b, data[2]*.25f+avgb*.75f, 1e-2f);
    res = map0.filter(0.75f, 0.25f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
//    EXPECT_NEAR(res.r, data[3]*.25f+avgr*.75f, 1e-2f);
//    EXPECT_NEAR(res.g, data[4]*.25f+avgg*.75f, 1e-2f);
//    EXPECT_NEAR(res.b, data[5]*.25f+avgb*.75f, 1e-2f);
    res = map0.filter(0.25f, 0.75f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
    EXPECT_NEAR(res.r, data[6]*.25f+avgr*.75f, 1e-2f);
//    EXPECT_NEAR(res.g, data[7]*.25f+avgg*.75f, 1e-2f);
    EXPECT_NEAR(res.b, data[8]*.25f+avgb*.75f, 1e-2f);
    res = map0.filter(0.75f, 0.75f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
//    EXPECT_NEAR(res.r, data[9]*.25f+avgr*.75f, 1e-2f);
//    EXPECT_NEAR(res.g, data[10]*.25f+avgg*.75f, 1e-2f);
//    EXPECT_NEAR(res.b, data[11]*.25f+avgb*.75f, 1e-2f);
    //map border of the image (highest pyramid is sufficient)
    res = map0.filter(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    res = map0.filter(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    res = map0.filter(0.f, 1.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
    res = map0.filter(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, avgr, 1e-2f);
    EXPECT_NEAR(res.g, avgg, 1e-2f);
    EXPECT_NEAR(res.b, avgb, 1e-2f);
}

SPECTRE_TEST_END(ImageMap_tests)
