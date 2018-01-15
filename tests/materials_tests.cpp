
#include <gtest/gtest.h>


#include "materials/lambertian.hpp"
#define EPSILON 1E-5f

TEST(Materials,Lambertian_value)
{
    Spectrum red(ColorRGB(1.f,0.f,0.f));
    ColorXYZ color = red.to_xyz();
    Lambertian mat(red);
    const Vec3 wo(-1.f,0.f,.5f);
    const Vec3 wi(1.f,0.f,.5f);
    Spectrum res = mat.value(&wo, &wi);
    EXPECT_EQ(res.w[0], color.r/ONE_PI);
    EXPECT_EQ(res.w[1], color.g/ONE_PI);
    EXPECT_EQ(res.w[2], color.b/ONE_PI);
}

TEST(Materials,Lambertian_sample_value)
{
    Spectrum red(ColorRGB(1.f,0.f,0.f));
    ColorXYZ color = red.to_xyz();
    Lambertian mat(red);
    const Vec3 wo(-1.f,0.f,.5f);
    Vec3 wi;
    float pdf;
    Spectrum res = mat.sample_value(&wo, &wi, 0.5f, 0.5f, &pdf);
    EXPECT_EQ(res.w[0], color.r/ONE_PI);
    EXPECT_EQ(res.w[1], color.g/ONE_PI);
    EXPECT_EQ(res.w[2], color.b/ONE_PI);
    EXPECT_EQ(sign(wo.z),sign(wi.z));
    EXPECT_FLOAT_EQ(pdf,0.22507906f);

    const Vec3 wo2(-1.f,0.f,-0.5f);
    res = mat.sample_value(&wo2, &wi, 0.5f, 0.5f, &pdf);
    EXPECT_EQ(res.w[0], color.r/ONE_PI);
    EXPECT_EQ(res.w[1], color.g/ONE_PI);
    EXPECT_EQ(res.w[2], color.b/ONE_PI);
    EXPECT_EQ(sign(wo2.z),sign(wi.z));
    EXPECT_FLOAT_EQ(pdf,0.22507906f);
}

TEST(Materials,Lambertian_pdf)
{
    Spectrum red(ColorRGB(1.f,0.f,0.f));
    Lambertian mat(red);

    //same hemisphere
    const Vec3 wo(-1.f,0.f,.5f);
    const Vec3 wi(-0.707106769f,-0.0000000618172393f,0.707106769f);
    float pdf;
    pdf = mat.pdf(&wo, &wi);
    EXPECT_FLOAT_EQ(pdf,0.22507906f);

    const Vec3 wo2(-1.f,0.f,-0.5f);
    pdf = mat.pdf(&wo2,&wi);
    EXPECT_EQ(pdf, 0.f);
}

