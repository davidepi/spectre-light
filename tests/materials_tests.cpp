
#include <gtest/gtest.h>


#include "materials/lambertian.hpp"
#include "materials/oren_nayar.hpp"
#define EPSILON 1E-5f

TEST(Materials,Lambertian_flags)
{
    Spectrum red(ColorRGB(1.f,0.f,0.f));
    Lambertian mat(red);
    EXPECT_EQ(mat.get_flags(),(BRDF|DIFFUSE));
    EXPECT_FALSE(mat.is_type(BRDF));
    EXPECT_FALSE(mat.is_type(DIFFUSE));
    EXPECT_TRUE(mat.is_type(BdfFlags(BRDF|DIFFUSE)));
    EXPECT_FALSE(mat.is_type(BdfFlags(BRDF|GLOSSY)));
    EXPECT_TRUE(mat.is_type(BdfFlags(BRDF|DIFFUSE|SPECULAR)));
    EXPECT_FALSE(mat.is_type(BTDF));
    EXPECT_FALSE(mat.is_type(GLOSSY));
    EXPECT_FALSE(mat.is_type(SPECULAR));
}

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

TEST(Materials,OrenNayar_flags)
{
    Spectrum red(ColorRGB(1.f,0.f,0.f));
    OrenNayar mat(red,15);
    EXPECT_EQ(mat.get_flags(),(BRDF|DIFFUSE));
    EXPECT_FALSE(mat.is_type(BRDF));
    EXPECT_FALSE(mat.is_type(DIFFUSE));
    EXPECT_TRUE(mat.is_type(BdfFlags(BRDF|DIFFUSE)));
    EXPECT_FALSE(mat.is_type(BdfFlags(BRDF|GLOSSY)));
    EXPECT_TRUE(mat.is_type(BdfFlags(BRDF|DIFFUSE|SPECULAR)));
    EXPECT_FALSE(mat.is_type(BTDF));
    EXPECT_FALSE(mat.is_type(GLOSSY));
    EXPECT_FALSE(mat.is_type(SPECULAR));
}

TEST(Materials,OrenNayar_value)
{
    Spectrum red(ColorRGB(1.f,0.f,0.f));
    OrenNayar mat(red,15.f);

    Vec3 wo(-1.f,0.f,.4f);
    Vec3 wi(1.f,0.f,.6f);
    Spectrum res = mat.value(&wo, &wi);
    EXPECT_EQ(res.w[0], 0.0657406151f);
    EXPECT_EQ(res.w[1], 0.0338975154f);
    EXPECT_EQ(res.w[2], 0.0030815925f);

    wo = Vec3(-1.f,0.f,0.6f);
    wi = Vec3(1.f,0.f,0.4f);
    res = mat.value(&wo, &wi);
    EXPECT_EQ(res.w[0], 0.0657406151f);
    EXPECT_EQ(res.w[1], 0.0338975154f);
    EXPECT_EQ(res.w[2], 0.0030815925f);

    //assert different results by changing incident angles
    wo = Vec3(-.2f,0.5f,0.2f);
    wi = Vec3(0.3f,0.3f,0.3f);
    res = mat.value(&wo, &wi);
    EXPECT_NE(res.w[0], 0.0657406151f);
    EXPECT_NE(res.w[1], 0.0338975154f);
    EXPECT_NE(res.w[2], 0.0030815925f);

    wo = Vec3(-1.f,0.f,1.f);
    wi = Vec3(1.f,0.f,0.5f);
    res = mat.value(&wo, &wi);
    EXPECT_EQ(res.w[0], 0.0657406151f);
    EXPECT_EQ(res.w[1], 0.0338975154f);
    EXPECT_EQ(res.w[2], 0.0030815925f);

    wo = Vec3(-1.f,0.f,0.5f);
    wi = Vec3(1.f,0.f,1.f);
    res = mat.value(&wo, &wi);
    EXPECT_EQ(res.w[0], 0.0657406151f);
    EXPECT_EQ(res.w[1], 0.0338975154f);
    EXPECT_EQ(res.w[2], 0.0030815925f);
}

TEST(Materials,OrenNayar_sample_value)
{
    Spectrum red(ColorRGB(1.f,0.f,0.f));
    OrenNayar mat(red,15);
    const Vec3 wo(-1.f,0.f,.5f);
    Vec3 wi;
    float pdf;
    Spectrum res = mat.sample_value(&wo, &wi, 0.5f, 0.5f, &pdf);
    EXPECT_EQ(sign(wo.z),sign(wi.z));
    EXPECT_EQ(res.w[0],0.116884954f);
    EXPECT_EQ(res.w[1],0.0602688268f);
    EXPECT_EQ(res.w[2],0.00547898421f);
    EXPECT_FLOAT_EQ(pdf,0.22507906f);

    const Vec3 wo2(-1.f,0.f,-0.5f);
    res = mat.sample_value(&wo2, &wi, 0.5f, 0.5f, &pdf);
    EXPECT_EQ(res.w[0],0.116884954f);
    EXPECT_EQ(res.w[1],0.0602688268f);
    EXPECT_EQ(res.w[2],0.00547898421f);
    EXPECT_EQ(sign(wo2.z),sign(wi.z));
    EXPECT_FLOAT_EQ(pdf,0.22507906f);
}

TEST(Materials,OrenNayar_pdf)
{
    Spectrum red(ColorRGB(1.f,0.f,0.f));
    OrenNayar mat(red,15);

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

