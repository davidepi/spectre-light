
#include <gtest/gtest.h>


#include "materials/lambertian.hpp"
#include "materials/oren_nayar.hpp"
#include "materials/reflection.hpp"
#include "materials/refraction.hpp"
#include "materials/metals.hpp"
#include "utility/spectrum.hpp"

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

TEST(Materials,SpecularReflection_flags)
{
    ConductorReflection cond(SPECTRUM_ONE,SILVER.n,SILVER.k);
    DielectricReflection diel(SPECTRUM_ONE,1.f,1.33f);
    EXPECT_EQ(cond.get_flags(),(BRDF|SPECULAR));
    EXPECT_FALSE(cond.is_type(BRDF));
    EXPECT_FALSE(cond.is_type(DIFFUSE));
    EXPECT_TRUE(cond.is_type(BdfFlags(BRDF|SPECULAR)));
    EXPECT_FALSE(cond.is_type(BdfFlags(BRDF|GLOSSY)));
    EXPECT_TRUE(cond.is_type(BdfFlags(BRDF|DIFFUSE|SPECULAR)));
    EXPECT_FALSE(cond.is_type(BTDF));
    EXPECT_FALSE(cond.is_type(GLOSSY));
    EXPECT_FALSE(cond.is_type(SPECULAR));
    EXPECT_EQ(diel.get_flags(),(BRDF|SPECULAR));
    EXPECT_FALSE(diel.is_type(BRDF));
    EXPECT_FALSE(diel.is_type(DIFFUSE));
    EXPECT_TRUE(diel.is_type(BdfFlags(BRDF|SPECULAR)));
    EXPECT_FALSE(diel.is_type(BdfFlags(BRDF|GLOSSY)));
    EXPECT_TRUE(diel.is_type(BdfFlags(BRDF|DIFFUSE|SPECULAR)));
    EXPECT_FALSE(diel.is_type(BTDF));
    EXPECT_FALSE(diel.is_type(GLOSSY));
    EXPECT_FALSE(diel.is_type(SPECULAR));
}

TEST(Materials,SpecularReflection_value)
{
    ConductorReflection cond(SPECTRUM_ONE,COPPER.n,COPPER.k);
    DielectricReflection diel(SPECTRUM_ONE,1.f,1.33f);
    const Vec3 wo(-1.f,0.f,.4f);
    const Vec3 wi(1.f,0.f,.6f);
    Spectrum res1 = cond.value(&wo, &wi);
    Spectrum res2 = diel.value(&wo, &wi);
    EXPECT_TRUE(res1.is_black());
    EXPECT_TRUE(res2.is_black());
}

TEST(Materials,SpecularReflection_sample_value)
{
    ConductorReflection cond(SPECTRUM_ONE,COPPER.n,COPPER.k);
    DielectricReflection diel(SPECTRUM_ONE,1.f,1.33f);

    //outside, conductor
    const Vec3 wo(-1.f,0.f,.4f);
    Vec3 wi;
    float pdf;
    Spectrum res = cond.sample_value(&wo,&wi,0.5f,0.5f,&pdf);
    EXPECT_EQ(wi.x,-wo.x);
    EXPECT_EQ(wi.y,-wo.y);
    EXPECT_EQ(wi.z,wo.z);
    EXPECT_FLOAT_EQ(pdf,1.f);
    //TODO: fix blue copper before 0.2.0
//    EXPECT_EQ(res.w[0],0.116884954f);
//    EXPECT_EQ(res.w[1],0.0602688268f);
//    EXPECT_EQ(res.w[2],0.00547898421f);

    //inside conductor
    const Vec3 wo2(-1.f,0.f,-0.5f);
    res = cond.sample_value(&wo2, &wi, 0.5f, 0.5f, &pdf);
    EXPECT_EQ(wi.x,-wo2.x);
    EXPECT_EQ(wi.y,-wo2.y);
    EXPECT_EQ(wi.z,wo2.z);
    EXPECT_EQ(sign(wo2.z),sign(wi.z));
    EXPECT_FLOAT_EQ(pdf,1.f);

    //outside dielectric
    res = diel.sample_value(&wo,&wi,0.5f,0.5f,&pdf);
    EXPECT_EQ(wi.x,-wo.x);
    EXPECT_EQ(wi.y,-wo.y);
    EXPECT_EQ(wi.z,wo.z);
    EXPECT_EQ(wi.z,wo.z);
    EXPECT_FLOAT_EQ(pdf,1.f);

    //inside dielectric, tir
    res = diel.sample_value(&wo2,&wi,0.5f,0.5f,&pdf);
    EXPECT_EQ(wi.x,-wo2.x);
    EXPECT_EQ(wi.y,-wo2.y);
    EXPECT_EQ(wi.z,wo2.z);
    EXPECT_EQ(sign(wo2.z),sign(wi.z));
    EXPECT_FLOAT_EQ(pdf,1.f);

    //inside dielectric, no tir
    const Vec3 wo3(-1.f,0.f,-0.9f);
    res = diel.sample_value(&wo3,&wi,0.5f,0.5f,&pdf);
    EXPECT_EQ(wi.x,-wo3.x);
    EXPECT_EQ(wi.y,-wo3.y);
    EXPECT_EQ(wi.z,wo3.z);
    EXPECT_EQ(sign(wo3.z),sign(wi.z));
    EXPECT_FLOAT_EQ(pdf,1.f);
}

TEST(Materials,SpecularReflection_pdf)
{
    ConductorReflection cond(SPECTRUM_ONE,COPPER.n,COPPER.k);
    DielectricReflection diel(SPECTRUM_ONE,1.f,1.33f);

    //same hemisphere
    const Vec3 wo(-1.f,0.f,.4f);
    const Vec3 wi(1.f,0.f,.6f);
    float pdf;
    pdf = cond.pdf(&wo, &wi);
    EXPECT_FLOAT_EQ(pdf,0.f);
    pdf = diel.pdf(&wo, &wi);
    EXPECT_FLOAT_EQ(pdf,0.f);

    const Vec3 wo2(-1.f,0.f,-0.5f);
    pdf = cond.pdf(&wo2,&wi);
    EXPECT_EQ(pdf, 0.f);
    pdf = diel.pdf(&wo, &wi);
    EXPECT_FLOAT_EQ(pdf,0.f);
}

TEST(Materials,SpecularRefraction_flags)
{
    Refraction diel(SPECTRUM_ONE,cauchy(1.f,0,0),cauchy(1.33f,0,0));
    EXPECT_EQ(diel.get_flags(),(BTDF|SPECULAR));
    EXPECT_FALSE(diel.is_type(BTDF));
    EXPECT_FALSE(diel.is_type(DIFFUSE));
    EXPECT_TRUE(diel.is_type(BdfFlags(BTDF|SPECULAR)));
    EXPECT_FALSE(diel.is_type(BdfFlags(BTDF|GLOSSY)));
    EXPECT_TRUE(diel.is_type(BdfFlags(BTDF|DIFFUSE|SPECULAR)));
    EXPECT_FALSE(diel.is_type(BdfFlags(BRDF|SPECULAR)));
    EXPECT_FALSE(diel.is_type(GLOSSY));
    EXPECT_FALSE(diel.is_type(SPECULAR));
}

TEST(Materials,SpecularRefraction_value)
{
    Refraction diel(SPECTRUM_ONE,cauchy(1.f,0,0),cauchy(1.33f,0,0));
    const Vec3 wo(-1.f,0.f,.4f);
    const Vec3 wi(1.f,0.f,.6f);
    Spectrum res = diel.value(&wo, &wi);
    EXPECT_TRUE(res.is_black());
}

TEST(Materials,SpecularRefraction_cauchy_sellmeier_equations)
{
    Spectrum c = cauchy(1.33f,0,0);
    EXPECT_EQ(c.w[0], 1.33f);

    Spectrum sm = sellmeier(1.03961212f,0.231792344f,1.01046945f,
                            6.00069867E-3f,2.00179144E-2f,103.560653f);
    EXPECT_EQ(sm.w[0], 1.5197562f);

}

TEST(Materials,SpecularRefraction_sample_value)
{
    Refraction diel(SPECTRUM_ONE,cauchy(1.f,0,0),cauchy(1.33f,0,0));
    const Vec3 wo(-1.f,0.f,.4f);
    Vec3 wi;
    float pdf;

    //outside dielectric
    Spectrum res = diel.sample_value(&wo,&wi,0.5f,0.5f,&pdf);
    EXPECT_EQ(wi.x,0.751879692f);
    EXPECT_EQ(wi.y,0.f);
    EXPECT_EQ(wi.z,-0.724657595f);
    EXPECT_EQ(res.w[0],0.704294562f);
    EXPECT_EQ(res.w[1],0.704294562f);
    EXPECT_EQ(res.w[2],0.704294562f);
    EXPECT_NE(sign(wo.z), sign(wi.z));
    EXPECT_EQ(pdf,1.f);

    //inside dielectric, tir
    const Vec3 wo2(-1.f,0.f,-.5f);
    res = diel.sample_value(&wo2,&wi,0.5f,0.5f,&pdf);
    EXPECT_TRUE(res.is_black());
    EXPECT_EQ(pdf,0.f);

    //inside dielectric, no tir
    const Vec3 wo3(-1.f,0.f,-0.9f);
    res = diel.sample_value(&wo3,&wi,0.5f,0.5f,&pdf);
    EXPECT_EQ(wi.x,1.33000004f);
    EXPECT_EQ(wi.y,0.f);
    EXPECT_EQ(wi.z,0.814805984f);
    EXPECT_EQ(res.w[0],2.12246299f);
    EXPECT_EQ(res.w[1],2.12246299f);
    EXPECT_EQ(res.w[2],2.12246299f);
    EXPECT_NE(sign(wo3.z),sign(wi.z));
    EXPECT_EQ(pdf,1.f);
}

TEST(Materials,SpecularRefraction_pdf)
{
    Refraction diel(SPECTRUM_ONE,cauchy(1.f,0,0),cauchy(1.33f,0,0));

    //same hemisphere
    const Vec3 wo(-1.f,0.f,.4f);
    const Vec3 wi(1.f,0.f,.6f);
    float pdf;
    pdf = diel.pdf(&wo, &wi);
    EXPECT_EQ(pdf,0.f);

    const Vec3 wo2(-1.f,0.f,-0.5f);
    pdf = diel.pdf(&wo, &wi);
    EXPECT_EQ(pdf,0.f);
}

