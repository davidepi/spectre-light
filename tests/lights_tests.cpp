
#include <gtest/gtest.h>


#include "lights/area_light.hpp"
#include "primitives/sphere.hpp"

TEST(Lights,AreaLight_is_light)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    AreaLight light(&s,m,SPECTRUM_ONE);
    EXPECT_TRUE(light.is_light());
}

TEST(Lights,AreaLight_emissive_spectrum)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    AreaLight light(&s,m,SPECTRUM_ONE);
    Spectrum res = light.emissive_spectrum();
    EXPECT_FLOAT_EQ(res.w[0],1.f);
    EXPECT_FLOAT_EQ(res.w[1],1.f);
    EXPECT_FLOAT_EQ(res.w[2],1.f);
}

TEST(Lights,AreaLight_sample_surface)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    AreaLight light(&s,m,SPECTRUM_ONE);
    Ray out_ray;
    float pdf = 0.f;
    Spectrum res;

    //sampled ok
    res = light.sample_surface(0.5f, 0.5f, 0.5f, 0.5f, &out_ray, &pdf);
    EXPECT_FLOAT_EQ(res.w[0],1.f);
    EXPECT_FLOAT_EQ(res.w[1],1.f);
    EXPECT_FLOAT_EQ(res.w[2],1.f);
    EXPECT_FLOAT_EQ(pdf,0.012665147f);

    //sampled wrong direction
    res = light.sample_surface(0.5f, 0.5f, 0.1f, 0.f, &out_ray, &pdf);
    EXPECT_FLOAT_EQ(res.w[0],1.f);
    EXPECT_FLOAT_EQ(res.w[1],1.f);
    EXPECT_FLOAT_EQ(res.w[2],1.f);
    EXPECT_FLOAT_EQ(pdf,0.012665147f);
}

TEST(Lights,AreaLight_pdf_surface)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    AreaLight light(&s,m,SPECTRUM_ONE);
    Ray ray(Point3(-1.f,0.f,0.f),Vec3(-0.302774, 0.931841, 0.200000));
    float pdf = light.pdf(&ray);
    EXPECT_FLOAT_EQ(pdf,0.012665147f);
}

