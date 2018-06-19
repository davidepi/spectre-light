#include "spectre_tests.h"

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

SPECTRE_TEST(ImageMap, init_not_readable)
{
    errors_count[CRITICAL_INDEX] = 0;
    ImageMap map0(TEST_ASSETS "images/nonexistent.bmp");
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

SPECTRE_TEST(ImageMap, init_not_power2)
{
    //width!=height
    errors_count[CRITICAL_INDEX] = 0;
    ImageMap map0(TEST_ASSETS "images/2by3.bmp");
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;

    //not power of 2
    errors_count[CRITICAL_INDEX] = 0;
    ImageMap map1(TEST_ASSETS "images/3by3.bmp");
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

SPECTRE_TEST(ImageMap, init_normal_depth)
{
    errors_count[CRITICAL_INDEX] = 0;
    ImageMap map0(TEST_ASSETS "images/correct.bmp");
    ASSERT_EQ(errors_count[CRITICAL_INDEX], 0);
    EXPECT_EQ(map0.maps_no, 2);
    EXPECT_EQ(map0.side[0], 2);
    EXPECT_EQ(map0.side[1], 1);
    EXPECT_EQ(map0.values[0][0].r, 255);
    EXPECT_EQ(map0.values[0][0].g, 0);
    EXPECT_EQ(map0.values[0][0].b, 0);
    EXPECT_EQ(map0.values[0][1].r, 0);
    EXPECT_EQ(map0.values[0][1].g, 255);
    EXPECT_EQ(map0.values[0][1].b, 0);
    EXPECT_EQ(map0.values[0][2].r, 0);
    EXPECT_EQ(map0.values[0][2].g, 0);
    EXPECT_EQ(map0.values[0][2].b, 255);
    EXPECT_EQ(map0.values[0][3].r, 0);
    EXPECT_EQ(map0.values[0][3].g, 0);
    EXPECT_EQ(map0.values[0][3].b, 0);
    //check mipmap
    EXPECT_EQ(map0.values[1][0].r, 63);
    EXPECT_EQ(map0.values[1][0].g, 63);
    EXPECT_EQ(map0.values[1][0].b, 63);
}

SPECTRE_TEST(ImageMap, unfiltered_normal_depth)
{
    ImageMap map0(TEST_ASSETS "images/correct.bmp");
    ColorRGB color = map0.unfiltered(0.25f, 0.25f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(color.r, 0.999f, 0.1f);
    EXPECT_NEAR(color.g, 0.f, 0.1f);
    EXPECT_NEAR(color.b, 0.f, 0.1f);
}

SPECTRE_TEST(ImageMap, trilinear_normal_depth)
{
    ImageMap map0(TEST_ASSETS "images/correct.bmp");
    ColorRGB color;
    
    //large filter
    color = map0.trilinear(0.25f, 0.25f, 5.f, 5.f, 5.f, 5.f);
    EXPECT_NEAR(color.r, 0.2470588235f, 1e-3f);
    EXPECT_NEAR(color.g, 0.2470588235f, 1e-3f);
    EXPECT_NEAR(color.b, 0.2470588235f, 1e-3f);
    
    //small filter
    color = map0.trilinear(0.25f, 0.25f, 0.f, 0.f, 0.f, 0.f);
    EXPECT_NEAR(color.r, 1.f, 1e-3f);
    EXPECT_NEAR(color.g, 0.f, 1e-3f);
    EXPECT_NEAR(color.b, 0.f, 1e-3f);
    
    //in between, no bilinear filter, only interpolation
    color = map0.trilinear(0.05f, 0.05f, 0.2f, 0.6f, 0.2f, 0.2f);
    float component1 = 1+log2f(0.6f); //chosen mipmap
    float component0 = 1.f-component1;
    //expected values = mipmap[0]*component0+mipmap[1]*component1 -> linear int.
    float expected_r = 1.f*component0+0.2470588235f*component1;
    float expected_g = 0.f*component0+0.2470588235f*component1;
    float expected_b = 0.f*component0+0.2470588235f*component1;
    EXPECT_NEAR(color.r, expected_r, 1e-3f);
    EXPECT_NEAR(color.g, expected_g, 1e-3f);
    EXPECT_NEAR(color.b, expected_b, 1e-3f);
    
    //in between, also with bilinear filter
    color = map0.trilinear(0.45f, 0.45f, 0.2f, 0.6f, 0.2f, 0.2f);
    component1 = 1+log2f(0.6f); //chosen mipmap
    component0 = 1.f-component1;
    //hardcoded values, but they have been manually checked
    expected_r = 0.356862754f*component0+0.2470588235f*component1;
    expected_g = 0.239215702f*component0+0.2470588235f*component1;
    expected_b = 0.239215702f*component0+0.2470588235f*component1;
    EXPECT_NEAR(color.r, expected_r, 1e-3f);
    EXPECT_NEAR(color.g, expected_g, 1e-3f);
    EXPECT_NEAR(color.b, expected_b, 1e-3f);
}

SPECTRE_TEST_END(ImageMap_tests)

