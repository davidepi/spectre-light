
#include <gtest/gtest.h>


#include "materials/lambertian.hpp"
#include "materials/oren_nayar.hpp"
#include "materials/reflection.hpp"
#include "materials/refraction.hpp"
#include "materials/microfacet.hpp"
#include "materials/microfacet_distributions.hpp"
#include "materials/fresnel_conditions.hpp"
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

TEST(Materials,MicrofacetR_flags)
{
    Fresnel* fresnel=new Dielectric(cauchy(1.f,0.f,0.f),cauchy(1.33f,0.f,0.f));
    MicrofacetDist* blinn = new Blinn(100.f);
    MicrofacetR mat(SPECTRUM_ONE,blinn,fresnel);
    EXPECT_EQ(mat.get_flags(),(BRDF|GLOSSY));
    EXPECT_FALSE(mat.is_type(BTDF));
    EXPECT_FALSE(mat.is_type(DIFFUSE));
    EXPECT_TRUE(mat.is_type(BdfFlags(BRDF|GLOSSY)));
    EXPECT_FALSE(mat.is_type(BdfFlags(BTDF|GLOSSY)));
    EXPECT_TRUE(mat.is_type(BdfFlags(BRDF|DIFFUSE|GLOSSY)));
    EXPECT_FALSE(mat.is_type(BdfFlags(BRDF|SPECULAR)));
    EXPECT_FALSE(mat.is_type(GLOSSY));
    EXPECT_FALSE(mat.is_type(SPECULAR));
}

TEST(Materials,MicrofacetR_value)
{
    Fresnel* fresnel=new Dielectric(cauchy(1.f,0.f,0.f),cauchy(1.33f,0.f,0.f));
    MicrofacetDist* blinn = new Blinn(100.f);
    MicrofacetR mat(SPECTRUM_ONE,blinn,fresnel);
    Spectrum res;

    //different hemispheres
    Vec3 wo(-1.f,0.f,-1.f);
    Vec3 wi(-1.f,0.f,1.f);
    res = mat.value(&wo, &wi);
    EXPECT_TRUE(res.is_black());

    //wo parallel to plane
    wo.z = 0.f;
    res = mat.value(&wo, &wi);
    EXPECT_TRUE(res.is_black());

    //wi parallel to plane
    wo.z = 1.f;
    wi.z = 0.f;
    res = mat.value(&wo, &wi);
    EXPECT_TRUE(res.is_black());

    //half vector zero length
    wo = Vec3(-1.f,0.f,-1.f);
    wi = Vec3(1.f,0.f,1.f);
    res = mat.value(&wo, &wi);
    EXPECT_TRUE(res.is_black());

    wo.z = 1.f;
    res = mat.value(&wo, &wi);
    EXPECT_FALSE(res.is_black());
    EXPECT_FLOAT_EQ(res.w[0],0.0814097523f);
    EXPECT_FLOAT_EQ(res.w[1],0.0814097523f);
    EXPECT_FLOAT_EQ(res.w[2],0.0814097523f);
}

TEST(Materials,MicrofacetR_sample_value)
{
    Fresnel* fresnel=new Dielectric(cauchy(1.f,0.f,0.f),cauchy(1.33f,0.f,0.f));
    MicrofacetDist* blinn = new Blinn(100.f);
    MicrofacetR mat(SPECTRUM_ONE,blinn,fresnel);
    Spectrum res;
    float pdf;

    //wi in the other hemisphere
    Vec3 wo(0.6f,0.4f,0.06f);
    Vec3 wi;
    res = mat.sample_value(&wo, &wi, 0.5f, 0.5f, &pdf);
    EXPECT_TRUE(res.is_black());

    //correct value
    wo = Vec3(0.f,0.f,1.f);
    res = mat.sample_value(&wo, &wi, 0.5f, 0.5f, &pdf);
    EXPECT_FALSE(res.is_black());
    EXPECT_FLOAT_EQ(wi.x,-0.231914222f);
    EXPECT_FLOAT_EQ(wi.y,-0.0000000202745856f);
    EXPECT_FLOAT_EQ(wi.z,0.972736239f);
    EXPECT_FLOAT_EQ(res.w[0],0.0421385542f);
    EXPECT_FLOAT_EQ(res.w[1],0.0421385542f);
    EXPECT_FLOAT_EQ(res.w[2],0.0421385542f);
    EXPECT_FLOAT_EQ(pdf,2.05727267f);
}

TEST(Materials,MicrofacetR_pdf)
{
    Fresnel* fresnel=new Dielectric(cauchy(1.f,0.f,0.f),cauchy(1.33f,0.f,0.f));
    MicrofacetDist* blinn = new Blinn(100.f);
    MicrofacetR mat(SPECTRUM_ONE,blinn,fresnel);
    float pdf;

    //different hemispheres
    Vec3 wo(0.6f,0.4f,0.06f);
    Vec3 wi(-0.825808227f,-0.552789986f,-0.111641996f);
    pdf = mat.pdf(&wo, &wi);
    EXPECT_EQ(pdf,0.f);

    //wh zero length
//    wi = Vec3(-0.6f,-0.4f,0.06f);
//    pdf = mat.pdf(&wo, &wi);
//    EXPECT_EQ(pdf,0.f);

    //previous test pdf
    wo = Vec3(0.f,0.f,1.f);
    wi = Vec3(-0.231914222f,-0.0000000202745856f,0.972736239f);
    pdf = mat.pdf(&wo, &wi);
    EXPECT_FLOAT_EQ(pdf,2.057285f);
}

TEST(Materials,MicrofacetT_flags)
{
    MicrofacetDist* beckmann = new Beckmann(0.3f);
    MicrofacetT mat(SPECTRUM_ONE,beckmann,
                    cauchy(1.f,0.f,0.f),cauchy(1.33f,0.f,0.f));
    EXPECT_EQ(mat.get_flags(),(BTDF|GLOSSY));
    EXPECT_FALSE(mat.is_type(BRDF));
    EXPECT_FALSE(mat.is_type(DIFFUSE));
    EXPECT_TRUE(mat.is_type(BdfFlags(BTDF|GLOSSY)));
    EXPECT_FALSE(mat.is_type(BdfFlags(BRDF|GLOSSY)));
    EXPECT_TRUE(mat.is_type(BdfFlags(BTDF|DIFFUSE|GLOSSY)));
    EXPECT_FALSE(mat.is_type(BdfFlags(BTDF|SPECULAR)));
    EXPECT_FALSE(mat.is_type(GLOSSY));
    EXPECT_FALSE(mat.is_type(SPECULAR));
}

TEST(Materials,MicrofacetT_value)
{
    MicrofacetDist* beckmann = new Beckmann(0.3f);
    MicrofacetT mat(SPECTRUM_ONE,beckmann,
                    cauchy(1.f,0.f,0.f),cauchy(1.33f,0.f,0.f));
    Spectrum res;

    //same hemispheres
    Vec3 wo(-1.f,0.f,1.f);
    Vec3 wi(-1.f,0.f,1.f);
    res = mat.value(&wo, &wi);
    EXPECT_TRUE(res.is_black());

    //wo parallel to plane
    wo.z = 0.f;
    res = mat.value(&wo, &wi);
    EXPECT_TRUE(res.is_black());

    //wi parallel to plane
    wo.z = 1.f;
    wi.z = 0.f;
    res = mat.value(&wo, &wi);
    EXPECT_TRUE(res.is_black());

    //half vector zero length
    wo = Vec3(-1.f,0.f,-1.f);
    wi = Vec3(1.33f,0.f,1.33f);
    res = mat.value(&wo, &wi);
    EXPECT_TRUE(res.is_black());

    //D*G = 0
    wo = Vec3(0.6f,0.4f,0.06f);
    wi.z = -1.f;
    res = mat.value(&wo, &wi);
    EXPECT_TRUE(res.is_black());

    //wh negative
    wo = Vec3(-1.f,0.f,1.f);
    wi = Vec3(1.f,0.f,-0.06f);
    res = mat.value(&wo,&wi);
    EXPECT_FALSE(res.is_black());

    //execution from outside
    wo = Vec3(0.6f,0.4f,0.06f);
    wi = Vec3(-0.321353912f,-0.351839572f,-0.879170417f);
    res = mat.value(&wo,&wi);
    EXPECT_FLOAT_EQ(res.w[0],0.109290525f);
    EXPECT_FLOAT_EQ(res.w[1],0.109290525f);
    EXPECT_FLOAT_EQ(res.w[2],0.109290525f);

    //execution from inside
    wo.z = -0.9f;
    wi = Vec3(-0.659094095f,-0.404581398f,0.63396281f);
    res = mat.value(&wo,&wi);
    EXPECT_FLOAT_EQ(res.w[0],2.83526969f);
    EXPECT_FLOAT_EQ(res.w[1],2.83526969f);
    EXPECT_FLOAT_EQ(res.w[2],2.83526969f);
}

TEST(Materials,MicrofacetT_sample_value)
{
    MicrofacetDist* beckmann = new Beckmann(0.3f);
    MicrofacetT mat(SPECTRUM_ONE,beckmann,
                    cauchy(1.f,0.f,0.f),cauchy(1.33f,0.f,0.f));
    Spectrum res;
    float pdf;
    Vec3 wi;

    //parallel to plane
    pdf = 1.f;
    Vec3 wo(-1.f,0.f,0.f);
    res = mat.sample_value(&wo, &wi, 0.5f, 0.5f, &pdf);
    EXPECT_EQ(pdf, 0.f);
    EXPECT_TRUE(res.is_black());

    //tir
    pdf = 1.f;
    wo = Vec3(0.6f,0.4f,-0.5f);
    res = mat.sample_value(&wo, &wi, 0.6f, 0.4f, &pdf);
    EXPECT_EQ(pdf, 0.f);
    EXPECT_TRUE(res.is_black());

    //correct from outside
    pdf = 1.f;
    wo = Vec3(0.6f,0.4f,0.06f);
    wo.normalize();
    res = mat.sample_value(&wo, &wi, 0.6f, 0.4f, &pdf);
    EXPECT_FLOAT_EQ(wi.x,-0.473553061f);
    EXPECT_FLOAT_EQ(wi.y,-0.524536133f);
    EXPECT_FLOAT_EQ(wi.z,-0.707537591f);
    EXPECT_FLOAT_EQ(res.w[0],0.0087483963f);
    EXPECT_FLOAT_EQ(res.w[1],0.0087483963f);
    EXPECT_FLOAT_EQ(res.w[2],0.0087483963f);
    EXPECT_FLOAT_EQ(pdf,0.0126143619f);

    //correct from inside
    pdf = 1.f;
    wo = Vec3(0.6f,0.4f,-0.9f);
    wo.normalize();
    res = mat.sample_value(&wo, &wi, 0.6f, 0.4f, &pdf);
    EXPECT_FLOAT_EQ(wi.x,-0.59114027f);
    EXPECT_FLOAT_EQ(wi.y,-0.534547925f);
    EXPECT_FLOAT_EQ(wi.z,0.603996515f);
    EXPECT_FLOAT_EQ(res.w[0],5.97027016f);
    EXPECT_FLOAT_EQ(res.w[1],5.97027016f);
    EXPECT_FLOAT_EQ(res.w[2],5.97027016f);
    EXPECT_FLOAT_EQ(pdf,4.47990608f);
}

TEST(Materials,MicrofacetT_pdf)
{
    MicrofacetDist* beckmann = new Beckmann(0.3f);
    MicrofacetT mat(SPECTRUM_ONE,beckmann,
                    cauchy(1.f,0.f,0.f),cauchy(1.33f,0.f,0.f));
    float pdf;

    //same hemispheres
    Vec3 wo(-1.f,0.f,1.f);
    Vec3 wi(-1.f,0.f,1.f);
    pdf = mat.pdf(&wo, &wi);
    EXPECT_EQ(pdf,0.f);

    //wo parallel to plane
    wo.z = 0.f;
    pdf = mat.pdf(&wo, &wi);
    EXPECT_EQ(pdf,0.f);

    //wi parallel to plane
    wo.z = 1.f;
    wi.z = 0.f;
    pdf = mat.pdf(&wo, &wi);
    EXPECT_EQ(pdf,0.f);

    //half vector zero length
    wo = Vec3(-1.f,0.f,-1.f);
    wi = Vec3(1.33f,0.f,1.33f);
    pdf = mat.pdf(&wo, &wi);
    EXPECT_EQ(pdf,0.f);

    pdf = 1.f;
    wo = Vec3(0.6f,0.4f,0.06f);
    wo.normalize();
    wi = Vec3(-0.473553061f,-0.524536133f,-0.707537591f);
    pdf = mat.pdf(&wo, &wi);
    EXPECT_FLOAT_EQ(pdf,0.012614323f);

    //correct from inside
    pdf = 1.f;
    wo = Vec3(0.6f,0.4f,-0.9f);
    wo.normalize();
    wi = Vec3(-0.59114027f,-0.534547925f,0.603996515f);
    pdf = mat.pdf(&wo, &wi);
    EXPECT_FLOAT_EQ(pdf,4.47991657f);
}

TEST(Materials,FresnelConditions_Conductor_eval)
{
    Conductor cond(COPPER.n,COPPER.k);
    Spectrum res = cond.eval(0.5f);
    EXPECT_FLOAT_EQ(res.w[0], 0.548298597f);
    EXPECT_FLOAT_EQ(res.w[1], 0.688397527f);
    EXPECT_FLOAT_EQ(res.w[2], 0.937712908f);
}

TEST(Materials,FresnelConditions_Dielectric_eval)
{
    Dielectric diel(cauchy(1.f,0.f,0.f),cauchy(1.33f,0.f,0.f));
    Spectrum res;

    //get_eta
    EXPECT_FLOAT_EQ(diel.get_eta_incident(), 1.f);
    EXPECT_FLOAT_EQ(diel.get_eta_transmitted(), 1.33f);

    //outside
    res = diel.eval(0.5f);
    EXPECT_FLOAT_EQ(res.w[0], 0.0591256134f);
    EXPECT_FLOAT_EQ(res.w[1], 0.0591256134f);
    EXPECT_FLOAT_EQ(res.w[2], 0.0591256134f);

    //inside no tir
    res = diel.eval(-0.9f);
    EXPECT_FLOAT_EQ(res.w[0], 0.0223328397f);
    EXPECT_FLOAT_EQ(res.w[1], 0.0223328397f);
    EXPECT_FLOAT_EQ(res.w[2], 0.0223328397f);

    //inside tir
    res = diel.eval(-0.4f);
    EXPECT_EQ(res.w[0],1.f);
    EXPECT_EQ(res.w[1],1.f);
    EXPECT_EQ(res.w[2],1.f);
}

