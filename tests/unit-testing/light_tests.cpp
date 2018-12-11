#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "lights/light_area.hpp"
#include "primitives/sphere.hpp"
#include <random>
#include "lights/light_sun.hpp"
#include "lights/light_omni.hpp"

SPECTRE_TEST_INIT(Light_tests)

SPECTRE_TEST(Light, LightArea_is_light)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    LightArea light(&s, m, SPECTRUM_ONE);
    EXPECT_TRUE(light.is_light());
}

SPECTRE_TEST(Light, LightArea_emissive_spectrum)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    LightArea light(&s, m, SPECTRUM_ONE);
    Spectrum res = light.emissive_spectrum();
    EXPECT_NEAR(res.w[0], 1.f, 1e-5f);
    EXPECT_NEAR(res.w[1], 1.f, 1e-5f);
    EXPECT_NEAR(res.w[2], 1.f, 1e-5f);
}

SPECTRE_TEST(Light, LightArea_sample_surface)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    LightArea light(&s, m, SPECTRUM_ONE);
    Ray out_ray;
    float pdf = 0.f;
    Spectrum res;

    //sampled ok
    res = light.sample_surface(0.5f, 0.5f, 0.5f, 0.5f, &out_ray, &pdf);
    EXPECT_NEAR(res.w[0], 1.f, 1e-5f);
    EXPECT_NEAR(res.w[1], 1.f, 1e-5f);
    EXPECT_NEAR(res.w[2], 1.f, 1e-5f);
    EXPECT_NEAR(pdf, 0.012665147f, 1e-5f);

    //sampled wrong direction
    res = light.sample_surface(0.5f, 0.5f, 0.1f, 0.f, &out_ray, &pdf);
    EXPECT_NEAR(res.w[0], 1.f, 1e-5f);
    EXPECT_NEAR(res.w[1], 1.f, 1e-5f);
    EXPECT_NEAR(res.w[2], 1.f, 1e-5f);
    EXPECT_NEAR(pdf, 0.012665147f, 1e-5f);
}

SPECTRE_TEST(Light, LightArea_pdf_surface)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    LightArea light(&s, m, SPECTRUM_ONE);
    Ray ray(Point3(-1.f, 0.f, 0.f), Vec3(-0.302774f, 0.931841f, 0.200000f));
    float pdf = light.pdf(&ray);
    EXPECT_NEAR(pdf, 0.012665147f, 1e-5f);
}

SPECTRE_TEST(Light, LightArea_sample_visible_surface)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    LightArea light(&s, m, SPECTRUM_ONE);
    Vec3 wi;
    Point3 pos;
    Spectrum res;
    float pdf;
    float distance;

    //infinite pdf
    pos = Point3(0.851531326f, 1.80135107f, -0.733865023f);
    res = light.sample_visible_surface(0.347596973f,
                                       0.318250597f, &pos, &wi, &pdf,
                                       &distance);
    EXPECT_EQ(distance, FLT_MAX);
    EXPECT_EQ(pdf, 0.f);
    EXPECT_TRUE(res.is_black());

    //cos<0 (ray and hit point has an extreme wide angle)
    //for example hit point on the complete top-left of the sphere
    //and the ray was on the bottom. cos(ray.dir,normal)<0
    pos = Point3(-0.230133832f, 0.528588295f, 0.25484854f);
    res = light.sample_visible_surface(0.0228148624f,
                                       0.17381911f, &pos, &wi, &pdf, &distance);
    EXPECT_TRUE(res.is_black());

    //correct execution
    pos = Point3(-0.560985684f, 0.542458057f, -1.82760262f);
    res = light.sample_visible_surface(0.5f, 0.5f, &pos, &wi,
                                       &pdf, &distance);
    EXPECT_NEAR(res.w[0], 1.f, 1e-5f);
    EXPECT_NEAR(res.w[1], 1.f, 1e-5f);
    EXPECT_NEAR(res.w[2], 1.f, 1e-5f);
    EXPECT_NEAR(wi.x, -0.22441007f, 1e-5f);
    EXPECT_NEAR(wi.y, -0.27728724f, 1e-5f);
    EXPECT_NEAR(wi.z, 0.934212f, 1e-5f);
    EXPECT_NEAR(pdf, 0.80584496f, 1e-5f);
}

SPECTRE_TEST(Light, LightArea_pdf_surface_visible)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    LightArea light(&s, m, SPECTRUM_ONE);
    Vec3 wi;
    Point3 pos;
    float pdf;

    //execution ok
    pos = Point3(-0.560985684f, 0.542458057f, -1.82760262f);
    wi = Vec3(-0.224410, -0.277287, 0.934212);
    pdf = light.pdf(&pos, &wi);
    EXPECT_NEAR(pdf, 0.8058424f, 1e-5f);

    //totally random ray
    pos = Point3(-0.560985684f, 0.542458057f, -1.82760262f);
    wi = Vec3(-1.f, 0.f, 0.f);
    pdf = light.pdf(&pos, &wi);
    EXPECT_NEAR(pdf, 0.f, 1e-5f);
}

SPECTRE_TEST(Light, LightArea_renderable)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    LightArea light(&s, m, SPECTRUM_ONE);
    EXPECT_TRUE(light.renderable());
}

SPECTRE_TEST(Light, LightOmni_sample_surface)
{
    Vec3 position(1, 2, 3);
    Matrix4 translation;
    translation.set_translation(position);
    LightOmni light(SPECTRUM_WHITE, translation);

    Ray r;
    float pdf;
    Spectrum res = light.sample_surface(0.f, 0.5f, 1.f, 0.f, &r, &pdf);

    EXPECT_NEAR(res.w[0], SPECTRUM_WHITE.w[0], 1e-5f);
    EXPECT_NEAR(res.w[1], SPECTRUM_WHITE.w[1], 1e-5f);
    EXPECT_NEAR(res.w[2], SPECTRUM_WHITE.w[2], 1e-5f);
    EXPECT_EQ(r.origin.x, 1.f);
    EXPECT_EQ(r.origin.y, 2.f);
    EXPECT_EQ(r.origin.z, 3.f);
    EXPECT_NEAR(r.direction.x, 0.f, 1e-5f);
    EXPECT_NEAR(r.direction.y, 0.f, 1e-5f);
    EXPECT_NEAR(r.direction.z, 1.f, 1e-5f);
    EXPECT_EQ(pdf, INV_FOURPI);
}

SPECTRE_TEST(Light, LightOmni_pdf_surface)
{
    Vec3 position(1, 1, 1);
    Matrix4 translation;
    translation.set_translation(position);
    LightOmni light(SPECTRUM_WHITE, translation);
    Ray r(Point3(2, 2, 2), Vec3(0, 0, 1));

    EXPECT_EQ(light.pdf(&r), INV_FOURPI);
}

SPECTRE_TEST(Light, LightOmni_sample_visible_surface)
{
    Vec3 position(1, 2, 3);
    Matrix4 translation;
    translation.set_translation(position);
    LightOmni light(SPECTRUM_WHITE, translation);

    Point3 pos(0, 1, 0);
    Vec3 wi;
    float pdf;
    float distance = FLT_MAX;
    Spectrum res = light.sample_visible_surface(0.f, 0.5f, &pos, &wi, &pdf,
                                                &distance);

    Spectrum check = SPECTRUM_WHITE/(distance*distance);
    Vec3 wi_check = Vec3(1.f, 1.f, 3.f).normalize();
    EXPECT_NEAR(distance, 3.31662488f, 1e-5f);
    EXPECT_NEAR(res.w[0], check.w[0], 1e-5f);
    EXPECT_NEAR(res.w[1], check.w[1], 1e-5f);
    EXPECT_NEAR(res.w[2], check.w[2], 1e-5f);
    EXPECT_NEAR(wi.x, wi_check.x, 1e-5f);
    EXPECT_NEAR(wi.y, wi_check.y, 1e-5f);
    EXPECT_NEAR(wi.z, wi_check.z, 1e-5f);
    EXPECT_EQ(pdf, 1.f);
}

SPECTRE_TEST(Light, LightOmni_pdf_surface_visible)
{
    Vec3 position(1, 1, 1);
    Matrix4 translation;
    translation.set_translation(position);
    LightOmni light(SPECTRUM_WHITE, translation);

    Point3 origin(2, 2, 2);
    Vec3 direction(0, 0, 1);

    EXPECT_EQ(light.pdf(&origin, &direction), 0.f);
}

SPECTRE_TEST(Light, LightOmni_renderable)
{
    Vec3 position(1, 1, 1);
    Matrix4 translation;
    translation.set_translation(position);
    LightOmni light(SPECTRUM_WHITE, translation);
    EXPECT_FALSE(light.renderable());
}

SPECTRE_TEST(Light, LightSun_sun_position)
{
    Date time(2003, 10, 17, 19, 30, 30);
//    LightSun ls(SPECTRUM_ONE, time, 39.742476f, -105.1786f, 1830.14f);
}

SPECTRE_TEST_END(Light)
