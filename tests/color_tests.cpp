
#include <gtest/gtest.h>


#include "utility/color.hpp"
#include "utility/utility.hpp"
#include <climits>

TEST(Color,constructor_empty)
{
    Color c;
    EXPECT_EQ(c.r, 0);
    EXPECT_EQ(c.g, 0);
    EXPECT_EQ(c.b, 0);
}

TEST(Color,constructor_components)
{
    Color c(0.5,0.3,0.2);
    EXPECT_EQ(c.r, 0.5);
    EXPECT_FLOAT_EQ(c.g, 0.3);
    EXPECT_FLOAT_EQ(c.b, 0.2);
}

TEST(Color,single_component)
{
    Color c(0.5);
    EXPECT_EQ(c.r, 0.5);
    EXPECT_EQ(c.g, 0.5);
    EXPECT_EQ(c.b, 0.5);
}

TEST(Color,is_black)
{
    Color c(0.f);
    EXPECT_TRUE(c.is_black());
}

TEST(Color,sum_color)
{
    Color c(0.5,0.3,0.2);
    Color res = c+c;
    EXPECT_EQ(res.r, 1.f);
    EXPECT_EQ(res.g, .6f);
    EXPECT_EQ(res.b, .4f);
}

TEST(Color,sum_color_this)
{
    Color c(0.5,0.3,0.2);
    c+=c;
    EXPECT_EQ(c.r, 1.f);
    EXPECT_EQ(c.g, .6f);
    EXPECT_EQ(c.b, .4f);
}

TEST(Color,sub_color)
{
    Color c(0.5,0.3,0.2);
    Color res = c-c;
    EXPECT_TRUE(res.is_black());
}

TEST(Color,sub_color_this)
{
    Color c(0.5,0.3,0.2);
    c-=c;
    EXPECT_TRUE(c.is_black());
}

TEST(Color,mul_color)
{
    Color c(0.5,0.3,0.2);
    Color res = c*c;
    EXPECT_EQ(res.r, .25f);
    EXPECT_EQ(res.g, .09f);
    EXPECT_FLOAT_EQ(res.b, .04f);
}

TEST(Color,mul_color_this)
{
    Color c(0.5,0.3,0.2);
    c*=c;
    EXPECT_EQ(c.r, .25f);
    EXPECT_EQ(c.g, .09f);
    EXPECT_FLOAT_EQ(c.b, .04f);
}

TEST(Color,div_color)
{
    Color c(0.5,0.3,0.2);
    Color res = c/c;
    EXPECT_EQ(res.r, 1.f);
    EXPECT_EQ(res.g, 1.f);
    EXPECT_EQ(res.b, 1.f);
}

TEST(Color,div_color_this)
{
    Color c(0.5,0.3,0.2);
    c/=c;
    EXPECT_EQ(c.r, 1.f);
    EXPECT_EQ(c.g, 1.f);
    EXPECT_EQ(c.b, 1.f);
}

TEST(Color,sum_float)
{
    Color c(0.5,0.3,0.2);
    float val = 0.15f;
    Color res = c+val;
    EXPECT_EQ(res.r, .65f);
    EXPECT_FLOAT_EQ(res.g, .45f);
    EXPECT_FLOAT_EQ(res.b, .35f);
}

TEST(Color,sum_float_this)
{
    Color c(0.5,0.3,0.2);
    float val = 0.15f;
    c+=val;
    EXPECT_EQ(c.r, .65f);
    EXPECT_FLOAT_EQ(c.g, .45f);
    EXPECT_FLOAT_EQ(c.b, .35f);
}

TEST(Color,sub_float)
{
    Color c(0.5,0.3,0.2);
    float val = 0.15f;
    Color res = c-val;
    EXPECT_EQ(res.r, .35f);
    EXPECT_EQ(res.g, .15f);
    EXPECT_FLOAT_EQ(res.b, .05f);
}

TEST(Color,sub_float_this)
{
    Color c(0.5,0.3,0.2);
    float val = 0.15f;
    c-=val;
    EXPECT_EQ(c.r, .35f);
    EXPECT_EQ(c.g, .15f);
    EXPECT_FLOAT_EQ(c.b, .05f);
}

TEST(Color,mul_float)
{
    Color c(0.5,0.3,0.2);
    float val = 0.15f;
    Color res = c*val;
    EXPECT_EQ(res.r, .075f);
    EXPECT_EQ(res.g, .045f);
    EXPECT_FLOAT_EQ(res.b, .03f);
}

TEST(Color,mul_float_this)
{
    Color c(0.5,0.3,0.2);
    float val = 0.15f;
    c*=val;
    EXPECT_EQ(c.r, .075f);
    EXPECT_EQ(c.g, .045f);
    EXPECT_FLOAT_EQ(c.b, .03f);
}

TEST(Color,div_float)
{
    Color c(0.5,0.3,0.2);
    float val = 0.6f;
    Color res = c/val;
    EXPECT_FLOAT_EQ(res.r,0.833333333f);
    EXPECT_EQ(res.g,.5f);
    EXPECT_FLOAT_EQ(res.b,0.333333333f);
}

TEST(Color,div_float_this)
{
    Color c(0.5,0.3,0.2);
    float val = 0.6f;
    c/=val;
    EXPECT_FLOAT_EQ(c.r,0.833333333f);
    EXPECT_EQ(c.g,.5f);
    EXPECT_FLOAT_EQ(c.b,0.333333333f);
}

TEST(Color,XYZ_constructor_empty)
{
    ColorXYZ c;
    EXPECT_EQ(c.r, 0);
    EXPECT_EQ(c.g, 0);
    EXPECT_EQ(c.b, 0);
}

TEST(Color,XYZ_constructor_components)
{
    ColorXYZ c(0.5,0.3,0.2);
    EXPECT_EQ(c.r, 0.5);
    EXPECT_FLOAT_EQ(c.g, 0.3);
    EXPECT_FLOAT_EQ(c.b, 0.2);
}

TEST(Color,XYZ_single_component)
{
    ColorXYZ c(0.5);
    EXPECT_EQ(c.r, 0.5);
    EXPECT_EQ(c.g, 0.5);
    EXPECT_EQ(c.b, 0.5);
}

TEST(Color,RGB_constructor_empty)
{
    ColorRGB c;
    EXPECT_EQ(c.r, 0);
    EXPECT_EQ(c.g, 0);
    EXPECT_EQ(c.b, 0);
}

TEST(Color,RGB_constructor_components_floats)
{
    ColorRGB c(0.5f,0.3f,0.2f);
    EXPECT_EQ(c.r, 0.5);
    EXPECT_FLOAT_EQ(c.g, 0.3);
    EXPECT_FLOAT_EQ(c.b, 0.2);
}

TEST(Color,RGB_constructor_components_bytes)
{
    ColorRGB c((unsigned char)128,(unsigned char)0,(unsigned char)255);
    EXPECT_FLOAT_EQ(c.r, .501960814f); //fuck floats
    EXPECT_EQ(c.g, 0.f);
    EXPECT_EQ(c.b, 1.f);
}

TEST(Color,RGB_single_component)
{
    ColorRGB c(0.5);
    EXPECT_EQ(c.r, 0.5);
    EXPECT_EQ(c.g, 0.5);
    EXPECT_EQ(c.b, 0.5);
}

TEST(Color,XYZ_to_sRGB)
{
    ColorXYZ c(0.08f,0.149f,0.0595f);
    ColorRGB res = c.to_sRGB();
    EXPECT_FLOAT_EQ(res.r, 0.0069778757f);
    EXPECT_FLOAT_EQ(res.g, 0.48950666f);
    EXPECT_FLOAT_EQ(res.b, 0.21196666f);
}

TEST(Color,XYZ_to_Adobe_rgb)
{
    ColorXYZ c(0.08f,0.149f,0.0595f);
    ColorRGB res = c.to_AdobeRGB();
    EXPECT_FLOAT_EQ(res.r, 0.27532971f);
    EXPECT_FLOAT_EQ(res.g, 0.48534867);
    EXPECT_FLOAT_EQ(res.b, 0.285955f);
}

TEST(Color,RGB_to_XYZ)
{
    ColorRGB c((unsigned char)158,(unsigned char)24,(unsigned char)67);
    ColorXYZ res = c.to_XYZ();
    EXPECT_FLOAT_EQ(res.r, 0.15441862f);
    EXPECT_FLOAT_EQ(res.g, 0.083299257f);
    EXPECT_FLOAT_EQ(res.b, 0.061038386f);
}

