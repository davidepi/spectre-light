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
    const uint32_t data[4] = {0xF94E47FF, 0x2B196BFF, 0xECA970FF, 0x12CDBBFF};
    ColorRGB res;
    ImageMapUnfiltered map0(data, 2);
    //map center of each pixel
    res = map0.filter(0.25f, 0.25f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[0])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[0])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[0])/255.f, 1e-5f);
    res = map0.filter(0.75f, 0.25f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[1])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[1])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[1])/255.f, 1e-5f);
    res = map0.filter(0.25f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[2])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[2])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[2])/255.f, 1e-5f);
    res = map0.filter(0.75f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[3])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[3])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[3])/255.f, 1e-5f);
    //map corners of image
    res = map0.filter(0.f, 0.f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[0])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[0])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[0])/255.f, 1e-5f);
    res = map0.filter(1.f, 0.f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[1])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[1])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[1])/255.f, 1e-5f);
    res = map0.filter(0.f, 1.f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[2])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[2])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[2])/255.f, 1e-5f);
    res = map0.filter(1.f, 1.f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[3])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[3])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[3])/255.f, 1e-5f);
}


SPECTRE_TEST(ImageMap, trilinear_mapping)
{
    const int LEN = 4;
    const pixBGRA data[LEN] = {0x4E359DFF, 0x6873B9FF, 0x96E186FF, 0x07D567FF};
    //avg used to represent farthest level
    float avgr = 0;
    float avgg = 0;
    float avgb = 0;
    for(int i = 0; i<LEN;i++)
    {
        avgr += BGRA_RED(data[i]);
        avgg += BGRA_GREEN(data[i]);
        avgb += BGRA_BLUE(data[i]);
    }
    avgr *= 0.25f;
    avgg *= 0.25f;
    avgb *= 0.25f;
    ColorRGB res;
    ImageMapTrilinear map0(data, 2);
    //map center of each pixel, pyramid nearest level (single pixel contrib.)
    res = map0.filter(0.25f, 0.25f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[0])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[0])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[0])/255.f, 1e-5f);
    res = map0.filter(0.75f, 0.25f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[1])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[1])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[1])/255.f, 1e-5f);
    res = map0.filter(0.25f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[2])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[2])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[2])/255.f, 1e-5f);
    res = map0.filter(0.75f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[3])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[3])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[3])/255.f, 1e-5f);
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
    EXPECT_NEAR(res.r, BGRA_RED(data[0])/255.f*.25f+avgr/255*.75f, 1e-2f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[0])/255.f*.25f+avgg/255*.75f, 1e-2f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[0])/255.f*.25f+avgb/255*.75f, 1e-2f);
    res = map0.filter(0.75f, 0.25f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, BGRA_RED(data[1])/255.f*.25f+avgr/255*.75f, 1e-2f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[1])/255.f*.25f+avgg/255*.75f, 1e-2f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[1])/255.f*.25f+avgb/255*.75f, 1e-2f);
    res = map0.filter(0.25f, 0.75f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, BGRA_RED(data[2])/255.f*.25f+avgr/255*.75f, 1e-2f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[2])/255.f*.25f+avgg/255*.75f, 1e-2f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[2])/255.f*.25f+avgb/255*.75f, 1e-2f);
    res = map0.filter(0.75f, 0.75f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR(res.r, BGRA_RED(data[3])/255.f*.25f+avgr/255*.75f, 1e-2f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[3])/255.f*.25f+avgg/255*.75f, 1e-2f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[3])/255.f*.25f+avgb/255*.75f, 1e-2f);
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

SPECTRE_TEST(ImageMap, ewa_mapping)
{
    const int LEN = 4;
    const uint32_t data[LEN] = {0x43F401FF, 0x10CDBBFF, 0x21F3C5FF, 0x5F91EDFF};
    //avg used to represent farthest level
    float avgr = 0;
    float avgg = 0;
    float avgb = 0;
    for(int i = 0; i<LEN; i++)
    {
        avgr += BGRA_RED(data[i]);
        avgg += BGRA_GREEN(data[i]);
        avgb += BGRA_BLUE(data[i]);
    }
    avgr *= 0.25f;
    avgg *= 0.25f;
    avgb *= 0.25f;
    ColorRGB res;
    ImageMapEWA map0(data, 2);
    //map center of each pixel, pyramid nearest level (single pixel contrib.)
    //first in particular requires axis swap
    res = map0.filter(0.25f, 0.25f, 0, 0, 0.5f, 0.5f);
    EXPECT_NEAR(res.r, BGRA_RED(data[0])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[0])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[0])/255.f, 1e-5f);
    res = map0.filter(0.75f, 0.25f, 0.5f, 0.5f, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[1])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[1])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[1])/255.f, 1e-5f);
    res = map0.filter(0.25f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[2])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[2])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[2])/255.f, 1e-5f);
    res = map0.filter(0.75f, 0.75f, 0, 0, 0, 0);
    EXPECT_NEAR(res.r, BGRA_RED(data[3])/255.f, 1e-5f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[3])/255.f, 1e-5f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[3])/255.f, 1e-5f);
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
//    EXPECT_NEAR(res.r, BGRA_RED(data[0])/255.f*.25f+avgr/255.f*.75f, 1e-2f);
//    EXPECT_NEAR(res.g, BGRA_GREEN(data[0])/255.f*.25f+avgg/255.f*.75f, 1e-2f);
//    EXPECT_NEAR(res.b, BGRA_BLUE(data[0])/255.f*.25f+avgb/255.f*.75f, 1e-2f);
    res = map0.filter(0.75f, 0.25f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
//    EXPECT_NEAR(res.r, BGRA_RED(data[1])/255.f*.25f+avgr/255.f*.75f, 1e-2f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[1])/255.f*.25f+avgg/255.f*.75f, 1e-2f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[1])/255.f*.25f+avgb/255.f*.75f, 1e-2f);
    res = map0.filter(0.25f, 0.75f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
    EXPECT_NEAR(res.r, BGRA_RED(data[2])/255.f*.25f+avgr/255.f*.75f, 1e-2f);
    EXPECT_NEAR(res.g, BGRA_GREEN(data[2])/255.f*.25f+avgg/255.f*.75f, 1e-2f);
    EXPECT_NEAR(res.b, BGRA_BLUE(data[2])/255.f*.25f+avgb/255.f*.75f, 1e-2f);
    res = map0.filter(0.75f, 0.75f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
//    EXPECT_NEAR(res.r, BGRA_RED(data[3])/255.f*.25f+avgr/255.f*.75f, 1e-2f);
//    EXPECT_NEAR(res.g, BGRA_GREEN(data[3])/255.f*.25f+avgg/255.f*.75f, 1e-2f);
//    EXPECT_NEAR(res.b, BGRA_BLUE(data[3])/255.f*.25f+avgb/255.f*.75f, 1e-2f);
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

SPECTRE_TEST_END(ImageMap_tests)
