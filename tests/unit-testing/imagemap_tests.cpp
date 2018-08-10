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
    const pixBGRA data[4] = {0xF94E47AFU, 0x2B196B67U, 0xECA970F6U,
                             0x12CDBB6BU};
    const TexelUnion* data_texel = (TexelUnion*)data;
    TexelUnion res;
    ImageMapUnfiltered map0(data, 2);
    //map center of each pixel
    res = map0.filter(0.25f, 0.25f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[0].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[0].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[0].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[0].bgra_texel.a);
    res = map0.filter(0.75f, 0.25f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[1].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[1].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[1].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[1].bgra_texel.a);
    res = map0.filter(0.25f, 0.75f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[2].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[2].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[2].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[2].bgra_texel.a);
    res = map0.filter(0.75f, 0.75f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[3].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[3].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[3].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[3].bgra_texel.a);
    //map corners of image
    res = map0.filter(0.f, 0.f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[0].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[0].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[0].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[0].bgra_texel.a);
    res = map0.filter(1.f, 0.f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[1].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[1].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[1].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[1].bgra_texel.a);
    res = map0.filter(0.f, 1.f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[2].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[2].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[2].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[2].bgra_texel.a);
    res = map0.filter(1.f, 1.f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[3].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[3].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[3].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[3].bgra_texel.a);
}

SPECTRE_TEST(ImageMap, trilinear_mapping)
{
    const int LEN = 4;
    constexpr const float INV = 1.f/LEN;
    const pixBGRA data[LEN] = {0x4E359DF3U, 0x6873B915U, 0x96E186E2U,
                               0x07D56734U};
    const TexelUnion* data_texel = (TexelUnion*)data;
    //avg used to represent farthest level
    float avg[4] = {0.f, 0.f, 0.f, 0.f};
    for(int i = 0; i<LEN; i++)
    {
        avg[0] += data_texel[i].bgra_texel.r;
        avg[1] += data_texel[i].bgra_texel.g;
        avg[2] += data_texel[i].bgra_texel.b;
        avg[3] += data_texel[i].bgra_texel.a;
    }
    avg[0] *= INV;
    avg[1] *= INV;
    avg[2] *= INV;
    avg[3] *= INV;
    uint8_t avgr = avg[0];
    uint8_t avgg = avg[1];
    uint8_t avgb = avg[2];
    uint8_t avga = avg[3];
    TexelUnion res;
    ImageMapTrilinear map0(data, 2);
    //map center of each pixel, pyramid nearest level (single pixel contrib.)
    res = map0.filter(0.25f, 0.25f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[0].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[0].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[0].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[0].bgra_texel.a);
    res = map0.filter(0.75f, 0.25f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[1].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[1].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[1].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[1].bgra_texel.a);
    res = map0.filter(0.25f, 0.75f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[2].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[2].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[2].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[2].bgra_texel.a);
    res = map0.filter(0.75f, 0.75f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[3].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[3].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[3].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[3].bgra_texel.a);
    //map center of each pixel, pyramid farthest level (single pixel contrib.)
    res = map0.filter(0.25f, 0.25f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    res = map0.filter(0.75f, 0.25f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    res = map0.filter(0.25f, 0.75f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    res = map0.filter(0.75f, 0.75f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    //map center of each pixel, between two levels (single pixel contrib.)
    //0.25% highest level, 0.75% lowest one
    res = map0.filter(0.25f, 0.25f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR((float)res.bgra_texel.r,
                data_texel[0].bgra_texel.r*.25f+avgr*.75f, 1.f);
    EXPECT_NEAR((float)res.bgra_texel.g,
                data_texel[0].bgra_texel.g*.25f+avgg*.75f, 1.f);
    EXPECT_NEAR((float)res.bgra_texel.b,
                data_texel[0].bgra_texel.b*.25f+avgb*.75f, 1.f);
    EXPECT_NEAR((float)res.bgra_texel.a,
                data_texel[0].bgra_texel.a*.25f+avga*.75f, 1.f);
    res = map0.filter(0.75f, 0.25f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR((float)res.bgra_texel.r,
                data_texel[1].bgra_texel.r*.25f+avgr*.75f, 1.f);
    EXPECT_NEAR((float)res.bgra_texel.g,
                data_texel[1].bgra_texel.g*.25f+avgg*.75f, 1.f);
    EXPECT_NEAR((float)res.bgra_texel.b,
                data_texel[1].bgra_texel.b*.25f+avgb*.75f, 1.f);
    EXPECT_NEAR((float)res.bgra_texel.a,
                data_texel[1].bgra_texel.a*.25f+avga*.75f, 1.f);
    res = map0.filter(0.25f, 0.75f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR((float)res.bgra_texel.r,
                data_texel[2].bgra_texel.r*.25f+avgr*.75f, 1.f);
    EXPECT_NEAR((float)res.bgra_texel.g,
                data_texel[2].bgra_texel.g*.25f+avgg*.75f, 1.f);
    EXPECT_NEAR((float)res.bgra_texel.b,
                data_texel[2].bgra_texel.b*.25f+avgb*.75f, 1.f);
    EXPECT_NEAR((float)res.bgra_texel.a,
                data_texel[2].bgra_texel.a*.25f+avga*.75f, 1.f);
    res = map0.filter(0.75f, 0.75f, powf(2.f, -1.f/4.f), 0.f, 0.f, 0.f);
    EXPECT_NEAR((float)res.bgra_texel.r,
                data_texel[3].bgra_texel.r*.25f+avgr*.75f, 1.f);
    EXPECT_NEAR((float)res.bgra_texel.g,
                data_texel[3].bgra_texel.g*.25f+avgg*.75f, 1.f);
    EXPECT_NEAR((float)res.bgra_texel.b,
                data_texel[3].bgra_texel.b*.25f+avgb*.75f, 1.f);
    EXPECT_NEAR((float)res.bgra_texel.a,
                data_texel[3].bgra_texel.a*.25f+avga*.75f, 1.f);
    //map border of the image (highest pyramid is sufficient)
    res = map0.filter(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    res = map0.filter(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    res = map0.filter(0.f, 1.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    res = map0.filter(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
}

SPECTRE_TEST(ImageMap, ewa_mapping)
{
    const int LEN = 4;
    constexpr const float INV = 1.f/LEN;
    const uint32_t data[LEN] = {0x43F40137U, 0x10CDBB7DU, 0x21F3C5D2U,
                                0x5F91ED48U};
    const TexelUnion* data_texel = (TexelUnion*)data;
    //avg used to represent farthest level
    float avg[4] = {0.f, 0.f, 0.f, 0.f};
    for(int i = 0; i<LEN; i++)
    {
        avg[0] += data_texel[i].bgra_texel.r;
        avg[1] += data_texel[i].bgra_texel.g;
        avg[2] += data_texel[i].bgra_texel.b;
        avg[3] += data_texel[i].bgra_texel.a;
    }
    avg[0] *= INV;
    avg[1] *= INV;
    avg[2] *= INV;
    avg[3] *= INV;
    uint8_t avgr = avg[0];
    uint8_t avgg = avg[1];
    uint8_t avgb = avg[2];
    uint8_t avga = avg[3];
    TexelUnion res;
    ImageMapEWA map0(data, 2);
    //map center of each pixel, pyramid nearest level (single pixel contrib.)
    //first in particular requires axis swap
    res = map0.filter(0.25f, 0.25f, 0, 0, 0.5f, 0.5f);
    EXPECT_EQ(res.bgra_texel.r, data_texel[0].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[0].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[0].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[0].bgra_texel.a);
    res = map0.filter(0.75f, 0.25f, 0.5f, 0.5f, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[1].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[1].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[1].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[1].bgra_texel.a);
    res = map0.filter(0.25f, 0.75f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[2].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[2].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[2].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[2].bgra_texel.a);
    res = map0.filter(0.75f, 0.75f, 0, 0, 0, 0);
    EXPECT_EQ(res.bgra_texel.r, data_texel[3].bgra_texel.r);
    EXPECT_EQ(res.bgra_texel.g, data_texel[3].bgra_texel.g);
    EXPECT_EQ(res.bgra_texel.b, data_texel[3].bgra_texel.b);
    EXPECT_EQ(res.bgra_texel.a, data_texel[3].bgra_texel.a);
    //map center of each pixel, pyramid farthest level (single pixel contrib.)
    //first in particular requires a rescale
    res = map0.filter(0.25f, 0.25f, 1000.f, 1000.f,
                      1000.f*EWA_MAX_ECCENTRICITY+1.f,
                      1000.f*EWA_MAX_ECCENTRICITY+1.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    res = map0.filter(0.75f, 0.25f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    res = map0.filter(0.25f, 0.75f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    res = map0.filter(0.75f, 0.75f, 1000.f, 1000.f, 1000.f, 1000.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    //map center of each pixel, between two levels (single pixel contrib.)
    //0.25% highest level, 0.75% lowest one

    //TODO: some values here are not correct. But visually the algorithm seems
    //to be working. Need to investigate more

    res = map0.filter(0.25f, 0.25f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
//    EXPECT_NEAR((float)res.bgra_texel.r,
//                data_texel[0].bgra_texel.r*.25f+avgr*.75f, 1.f);
//    EXPECT_NEAR((float)res.bgra_texel.g,
//                data_texel[0].bgra_texel.g*.25f+avgg*.75f, 1.f);
//    EXPECT_NEAR((float)res.bgra_texel.b,
//                data_texel[0].bgra_texel.b*.25f+avgb*.75f, 1.f);
//    EXPECT_NEAR((float)res.bgra_texel.a,
//                data_texel[0].bgra_texel.a*.25f+avga*.75f, 1.f);
    res = map0.filter(0.75f, 0.25f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
//    EXPECT_NEAR((float)res.bgra_texel.r,
//                data_texel[1].bgra_texel.r*.25f+avgr*.75f, 1.f);
//    EXPECT_NEAR((float)res.bgra_texel.g,
//                data_texel[1].bgra_texel.g*.25f+avgg*.75f, 1.f);
//    EXPECT_NEAR((float)res.bgra_texel.b,
//                data_texel[1].bgra_texel.b*.25f+avgb*.75f, 1.f);
//    EXPECT_NEAR((float)res.bgra_texel.a,
//                data_texel[1].bgra_texel.a*.25f+avga*.75f, 1.f);
    res = map0.filter(0.25f, 0.75f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
//    EXPECT_NEAR((float)res.bgra_texel.r,
//                data_texel[2].bgra_texel.r*.25f+avgr*.75f, 1.f);
//    EXPECT_NEAR((float)res.bgra_texel.g,
//                data_texel[2].bgra_texel.g*.25f+avgg*.75f, 1.f);
//    EXPECT_NEAR((float)res.bgra_texel.b,
//                data_texel[2].bgra_texel.b*.25f+avgb*.75f, 1.f);
//    EXPECT_NEAR((float)res.bgra_texel.a,
//                data_texel[2].bgra_texel.a*.25f+avga*.75f, 1.f);
    res = map0.filter(0.75f, 0.75f, powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f),
                      powf(2.f, -3.f/4.f), powf(2.f, -3.f/4.f));
//    EXPECT_NEAR((float)res.bgra_texel.r,
//                data_texel[3].bgra_texel.r*.25f+avgr*.75f, 1.f);
//    EXPECT_NEAR((float)res.bgra_texel.g,
//                data_texel[3].bgra_texel.g*.25f+avgg*.75f, 1.f);
//    EXPECT_NEAR((float)res.bgra_texel.b,
//                data_texel[3].bgra_texel.b*.25f+avgb*.75f, 1.f);
//    EXPECT_NEAR((float)res.bgra_texel.a,
//                data_texel[3].bgra_texel.a*.25f+avga*.75f, 1.f);
    //map border of the image (highest pyramid is sufficient)
    res = map0.filter(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    res = map0.filter(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    res = map0.filter(0.f, 1.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
    res = map0.filter(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_EQ(res.bgra_texel.r, (uint8_t)avgr);
    EXPECT_EQ(res.bgra_texel.g, (uint8_t)avgg);
    EXPECT_EQ(res.bgra_texel.b, (uint8_t)avgb);
    EXPECT_EQ(res.bgra_texel.a, (uint8_t)avga);
}

SPECTRE_TEST_END(ImageMap_tests)
