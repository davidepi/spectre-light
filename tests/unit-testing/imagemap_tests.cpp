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
    EXPECT_EQ(map0.maps_no,2);
    EXPECT_EQ(map0.values[0][0].r,255);
    EXPECT_EQ(map0.values[0][0].g,0);
    EXPECT_EQ(map0.values[0][0].b,0);
    EXPECT_EQ(map0.values[0][1].r,0);
    EXPECT_EQ(map0.values[0][1].g,255);
    EXPECT_EQ(map0.values[0][1].b,0);
    EXPECT_EQ(map0.values[0][2].r,0);
    EXPECT_EQ(map0.values[0][2].g,0);
    EXPECT_EQ(map0.values[0][2].b,255);
    EXPECT_EQ(map0.values[0][3].r,0);
    EXPECT_EQ(map0.values[0][3].g,0);
    EXPECT_EQ(map0.values[0][3].b,0);
    //check mipmap
    EXPECT_EQ(map0.values[1][0].r,63);
    EXPECT_EQ(map0.values[1][0].g,63);
    EXPECT_EQ(map0.values[1][0].b,63);
}

SPECTRE_TEST_END(ImageMap_tests)

