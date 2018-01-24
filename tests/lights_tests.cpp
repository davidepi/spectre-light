
#include <gtest/gtest.h>


#include "lights/area_light.hpp"
#include "primitives/sphere.hpp"
#include <random>

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

TEST(Lights,AreaLight_sample_visible_surface)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    AreaLight light(&s,m,SPECTRUM_ONE);
    Vec3 wi;
    Point3 pos;
    Spectrum res;
    float pdf;
    float distance;

    //infinite pdf
    pos = Point3(0.851531326f,1.80135107f,-0.733865023f);
    res = light.sample_visible_surface(0.347596973f,
            0.318250597f,&pos,&wi,&pdf,&distance);
    EXPECT_EQ(distance, FLT_MAX);
    EXPECT_EQ(pdf, 0.f);
    EXPECT_TRUE(res.is_black());

    //cos<0 (ray and hit point has an extreme wide angle)
    //for example hit point on the complete top-left of the sphere
    //and the ray was on the bottom. cos(ray.dir,normal)<0
    pos = Point3(-0.230133832f,0.528588295f,0.25484854f);
    res = light.sample_visible_surface(0.0228148624f,
                0.17381911f,&pos,&wi,&pdf,&distance);
    EXPECT_TRUE(res.is_black());

    //correct execution
    pos = Point3(-0.560985684f,0.542458057f,-1.82760262f);
    res = light.sample_visible_surface(0.5f,0.5f,&pos,&wi,
                                       &pdf,&distance);
    EXPECT_FLOAT_EQ(res.w[0], 1.f);
    EXPECT_FLOAT_EQ(res.w[1], 1.f);
    EXPECT_FLOAT_EQ(res.w[2], 1.f);
    EXPECT_FLOAT_EQ(wi.x,-0.22441007f);
    EXPECT_FLOAT_EQ(wi.y,-0.27728724f);
    EXPECT_FLOAT_EQ(wi.z,0.934212f);
    EXPECT_FLOAT_EQ(pdf, 0.80584496f);
}

TEST(Lights,AreaLight_pdf_surface_visible)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    AreaLight light(&s,m,SPECTRUM_ONE);
    Vec3 wi;
    Point3 pos;
    float pdf;

    //execution ok
    pos = Point3(-0.560985684f,0.542458057f,-1.82760262f);
    wi = Vec3(-0.224410, -0.277287, 0.934212);
    pdf = light.pdf(&pos,&wi);
    EXPECT_FLOAT_EQ(pdf, 0.8058424f);

    //totally random ray
    pos = Point3(-0.560985684f,0.542458057f,-1.82760262f);
    wi = Vec3(-1.f, 0.f, 0.f);
    pdf = light.pdf(&pos,&wi);
    EXPECT_FLOAT_EQ(pdf,0.f);
}

