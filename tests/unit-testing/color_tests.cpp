#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else
#include <gtest/gtest.h>
#endif

#include "utility/color.hpp"
#include "utility/utility.hpp"
#include <climits>

SPECTRE_TEST_INIT(Color_tests)

SPECTRE_TEST(Color, constructor_empty)
{
    Color c;
    EXPECT_EQ(c.r, 0.f);
    EXPECT_EQ(c.g, 0.f);
    EXPECT_EQ(c.b, 0.f);
}

SPECTRE_TEST(Color, constructor_components)
{
    Color c(0.5, 0.3, 0.2);
    EXPECT_NEAR(c.r, 0.5f, 1e-5f);
    EXPECT_NEAR(c.g, 0.3f, 1e-5f);
    EXPECT_NEAR(c.b, 0.2f, 1e-5f);
}

SPECTRE_TEST(Color, single_component)
{
    Color c(0.5);
    EXPECT_EQ(c.r, 0.5f);
    EXPECT_EQ(c.g, 0.5f);
    EXPECT_EQ(c.b, 0.5f);
}

SPECTRE_TEST(Color, is_black)
{
    Color c(0.f);
    EXPECT_TRUE(c.is_black());
}

SPECTRE_TEST(Color, sum_color)
{
    Color c(0.5, 0.3, 0.2);
    Color res = c+c;
    EXPECT_EQ(res.r, 1.f);
    EXPECT_EQ(res.g, .6f);
    EXPECT_EQ(res.b, .4f);
}

SPECTRE_TEST(Color, sum_color_this)
{
    Color c(0.5, 0.3, 0.2);
    c += c;
    EXPECT_EQ(c.r, 1.f);
    EXPECT_EQ(c.g, .6f);
    EXPECT_EQ(c.b, .4f);
}

SPECTRE_TEST(Color, sub_color)
{
    Color c(0.5, 0.3, 0.2);
    Color res = c-c;
    EXPECT_TRUE(res.is_black());
}

SPECTRE_TEST(Color, sub_color_this)
{
    Color c(0.5, 0.3, 0.2);
    c -= c;
    EXPECT_TRUE(c.is_black());
}

SPECTRE_TEST(Color, mul_color)
{
    Color c(0.5, 0.3, 0.2);
    Color res = c*c;
    EXPECT_EQ(res.r, .25f);
    EXPECT_EQ(res.g, .09f);
    EXPECT_NEAR(res.b, .04f, 1e-5f);
}

SPECTRE_TEST(Color, mul_color_this)
{
    Color c(0.5, 0.3, 0.2);
    c *= c;
    EXPECT_EQ(c.r, .25f);
    EXPECT_EQ(c.g, .09f);
    EXPECT_NEAR(c.b, .04f, 1e-5f);
}

SPECTRE_TEST(Color, div_color)
{
    Color c(0.5, 0.3, 0.2);
    Color res = c/c;
    EXPECT_EQ(res.r, 1.f);
    EXPECT_EQ(res.g, 1.f);
    EXPECT_EQ(res.b, 1.f);
}

SPECTRE_TEST(Color, div_Color_this)
{
    Color c(0.5, 0.3, 0.2);
    c /= c;
    EXPECT_EQ(c.r, 1.f);
    EXPECT_EQ(c.g, 1.f);
    EXPECT_EQ(c.b, 1.f);
}

SPECTRE_TEST(Color, sum_float)
{
    Color c(0.5, 0.3, 0.2);
    float val = 0.15f;
    Color res = c+val;
    EXPECT_EQ(res.r, .65f);
    EXPECT_NEAR(res.g, .45f, 1e-5f);
    EXPECT_NEAR(res.b, .35f, 1e-5f);
}

SPECTRE_TEST(Color, sum_float_this)
{
    Color c(0.5, 0.3, 0.2);
    float val = 0.15f;
    c += val;
    EXPECT_EQ(c.r, .65f);
    EXPECT_NEAR(c.g, .45f, 1e-5f);
    EXPECT_NEAR(c.b, .35f, 1e-5f);
}

SPECTRE_TEST(Color, sub_float)
{
    Color c(0.5, 0.3, 0.2);
    float val = 0.15f;
    Color res = c-val;
    EXPECT_EQ(res.r, .35f);
    EXPECT_EQ(res.g, .15f);
    EXPECT_NEAR(res.b, .05f, 1e-5f);
}

SPECTRE_TEST(Color, sub_float_this)
{
    Color c(0.5, 0.3, 0.2);
    float val = 0.15f;
    c -= val;
    EXPECT_EQ(c.r, .35f);
    EXPECT_EQ(c.g, .15f);
    EXPECT_NEAR(c.b, .05f, 1e-5f);
}

SPECTRE_TEST(Color, mul_float)
{
    Color c(0.5, 0.3, 0.2);
    float val = 0.15f;
    Color res = c*val;
    EXPECT_EQ(res.r, .075f);
    EXPECT_EQ(res.g, .045f);
    EXPECT_NEAR(res.b, .03f, 1e-5f);
}

SPECTRE_TEST(Color, mul_float_this)
{
    Color c(0.5, 0.3, 0.2);
    float val = 0.15f;
    c *= val;
    EXPECT_EQ(c.r, .075f);
    EXPECT_EQ(c.g, .045f);
    EXPECT_NEAR(c.b, .03f, 1e-5f);
}

SPECTRE_TEST(Color, div_float)
{
    Color c(0.5, 0.3, 0.2);
    float val = 0.6f;
    Color res = c/val;
    EXPECT_NEAR(res.r, 0.833333333f, 1e-5f);
    EXPECT_EQ(res.g, .5f);
    EXPECT_NEAR(res.b, 0.333333333f, 1e-5f);
}

SPECTRE_TEST(Color, div_float_this)
{
    Color c(0.5, 0.3, 0.2);
    float val = 0.6f;
    c /= val;
    EXPECT_NEAR(c.r, 0.833333333f, 1e-5f);
    EXPECT_EQ(c.g, .5f);
    EXPECT_NEAR(c.b, 0.333333333f, 1e-5f);
}

SPECTRE_TEST(Color, XYZ_constructor_empty)
{
    ColorXYZ c;
    EXPECT_EQ(c.r, 0.f);
    EXPECT_EQ(c.g, 0.f);
    EXPECT_EQ(c.b, 0.f);
}

SPECTRE_TEST(Color, XYZ_constructor_components)
{
    ColorXYZ c(0.5, 0.3, 0.2);
    EXPECT_EQ(c.r, 0.5f);
    EXPECT_NEAR(c.g, 0.3f, 1e-5f);
    EXPECT_NEAR(c.b, 0.2f, 1e-5f);
}

SPECTRE_TEST(Color, XYZ_single_component)
{
    ColorXYZ c(0.5);
    EXPECT_EQ(c.r, 0.5f);
    EXPECT_EQ(c.g, 0.5f);
    EXPECT_EQ(c.b, 0.5f);
}

SPECTRE_TEST(Color, RGB_constructor_empty)
{
    ColorRGB c;
    EXPECT_EQ(c.r, 0.f);
    EXPECT_EQ(c.g, 0.f);
    EXPECT_EQ(c.b, 0.f);
}

SPECTRE_TEST(Color, RGB_constructor_components_floats)
{
    ColorRGB c(0.5f, 0.3f, 0.2f);
    EXPECT_EQ(c.r, 0.5f);
    EXPECT_NEAR(c.g, 0.3f, 1e-5f);
    EXPECT_NEAR(c.b, 0.2f, 1e-5f);
}

SPECTRE_TEST(Color, RGB_constructor_components_bytes)
{
    ColorRGB c((unsigned char)128, (unsigned char)0, (unsigned char)255);
    EXPECT_NEAR(c.r, .501960814f, 1e-5f);
    EXPECT_EQ(c.g, 0.f);
    EXPECT_EQ(c.b, 1.f);
}

SPECTRE_TEST(Color, RGB_single_component)
{
    ColorRGB c(0.5);
    EXPECT_EQ(c.r, 0.5f);
    EXPECT_EQ(c.g, 0.5f);
    EXPECT_EQ(c.b, 0.5f);
}

SPECTRE_TEST(Color, XYZ_to_sRGB)
{
    ColorXYZ c(0.18f, 0.139f, 0.0595f);
    ColorRGB res = c.to_sRGB();
    EXPECT_NEAR(res.r, 0.61799586f, 1e-5f);
    EXPECT_NEAR(res.g, 0.32961869f, 1e-5f);
    EXPECT_NEAR(res.b, 0.23361403f, 1e-5f);

    ColorXYZ c2(0.002f, 0.002f, 0.002f);
    ColorRGB res2 = c2.to_sRGB();
    EXPECT_NEAR(res2.r, 0.031131625f, 1e-5f);
    EXPECT_NEAR(res2.g, 0.024504095f, 1e-5f);
    EXPECT_NEAR(res2.b, 0.023484498f, 1e-5f);
}

SPECTRE_TEST(Color, XYZ_to_Adobe_rgb)
{
    ColorXYZ c(0.08f, 0.149f, 0.0595f);
    ColorRGB res = c.to_AdobeRGB();
    EXPECT_NEAR(res.r, 0.27532971f, 1e-5f);
    EXPECT_NEAR(res.g, 0.48534867f, 1e-5f);
    EXPECT_NEAR(res.b, 0.285955f, 1e-5f);
}

SPECTRE_TEST(Color, RGB_to_XYZ)
{
    ColorRGB c((unsigned char)158, (unsigned char)24, (unsigned char)67);
    ColorXYZ res = c.to_XYZ();
    EXPECT_NEAR(res.r, 0.15441862f, 1e-5f);
    EXPECT_NEAR(res.g, 0.083299257f, 1e-5f);
    EXPECT_NEAR(res.b, 0.061038386f, 1e-5f);

    ColorRGB c2(0.03f, 0.03f, 0.03f);
    ColorXYZ res2 = c2.to_XYZ();
    EXPECT_NEAR(res2.r, 0.0022069735f, 1e-5f);
    EXPECT_NEAR(res2.g, 0.0023219816f, 1e-5f);
    EXPECT_NEAR(res2.b, 0.002528243f, 1e-5f);
}

SPECTRE_TEST_END(Color_tests)
