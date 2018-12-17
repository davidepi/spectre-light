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
#include "lights/light_sun.hpp"
#include "lights/light_omni.hpp"
#include "lights/light_spot.hpp"
#include "lights/light_sky.hpp"

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

SPECTRE_TEST(Light, LightSpot_sample_surface)
{
    Vec3 position(1, 2, 3);
    Matrix4 translation;
    translation.set_translation(position);
    LightSpot light(SPECTRUM_WHITE, translation, 0.25f, 0.5f);

    Ray r;
    float pdf;
    Spectrum res = light.sample_surface(0.f, 0.25f, 0.5f, 1.f, &r, &pdf);
    EXPECT_EQ(r.origin.x, 1.f);
    EXPECT_EQ(r.origin.y, 2.f);
    EXPECT_EQ(r.origin.z, 3.f);
    EXPECT_NEAR(r.direction.x, 0.f, 1e-5f);
    EXPECT_NEAR(r.direction.y, 0.f, 1e-5f);
    EXPECT_NEAR(r.direction.z, 1.f, 1e-5f);
    EXPECT_NEAR(pdf, 1.f/(2.f*ONE_PI*0.4f), 1e-5f);
    EXPECT_EQ(res.w[0], SPECTRUM_WHITE.w[0]);
    EXPECT_EQ(res.w[1], SPECTRUM_WHITE.w[1]);
    EXPECT_EQ(res.w[2], SPECTRUM_WHITE.w[2]);
}

SPECTRE_TEST(Light, LightSpot_pdf_surface)
{
    Vec3 position(1, 1, 1);
    Matrix4 translation;
    translation.set_translation(position);
    LightSpot light(SPECTRUM_WHITE, translation, 0.25f, 0.5f);

    Ray r(Point3(2, 2, 2), Vec3(0, 0, 1));

    EXPECT_NEAR(light.pdf(&r), 1.f/(2.f*ONE_PI*0.4f), 1e-5f);
}

SPECTRE_TEST(Light, LightSpot_sample_visible_surface)
{
    Vec3 position(1, 1, 1);
    Matrix4 translation;
    translation.set_translation(position);
    LightSpot light(SPECTRUM_WHITE, translation, 0.25f, 0.5f);

    Point3 pos(0, 1, 0);
    Vec3 wi;
    float pdf;
    float distance = FLT_MAX;
    Spectrum res = light.sample_visible_surface(0.f, 0.5f, &pos, &wi, &pdf,
                                                &distance);

    Spectrum check = SPECTRUM_WHITE*0.020706f/2.f;
    Vec3 wi_check = Vec3(1, 0, 1).normalize();
    EXPECT_NEAR(distance, sqrtf(2), 1e-5f);
    EXPECT_NEAR(res.w[0], check.w[0], 1e-5f);
    EXPECT_NEAR(res.w[1], check.w[1], 1e-5f);
    EXPECT_NEAR(res.w[2], check.w[2], 1e-5f);
    EXPECT_NEAR(wi.x, wi_check.x, 1e-5f);
    EXPECT_NEAR(wi.y, wi_check.y, 1e-5f);
    EXPECT_NEAR(wi.z, wi_check.z, 1e-5f);
    EXPECT_EQ(pdf, 1.f);
}

SPECTRE_TEST(Light, LightSpot_pdf_surface_visible)
{
    Vec3 position(1, 1, 1);
    Matrix4 translation;
    translation.set_translation(position);
    LightSpot light(SPECTRUM_WHITE, translation, 0.f, 0.f);

    Point3 origin(2, 2, 2);
    Vec3 direction(0, 0, 1);

    EXPECT_EQ(light.pdf(&origin, &direction), 0.f);
}

SPECTRE_TEST(Light, LightSpot_renderable)
{
    Vec3 position(1, 1, 1);
    Matrix4 translation;
    translation.set_translation(position);
    LightSpot light(SPECTRUM_WHITE, translation, 0.f, 0.f);
    EXPECT_FALSE(light.renderable());
}

SPECTRE_TEST(Light, LightSpot_corner_cases)
{
    Vec3 position(1, 1, 1);
    Matrix4 translation;
    translation.set_translation(position);

    Point3 pos(0, 1, 0);
    Vec3 wi;
    float pdf;
    float distance = FLT_MAX;

    //wrong order of outer/inner
    LightSpot light2(SPECTRUM_WHITE, translation, 0.5f, 0.25f);

    Spectrum res = light2.sample_visible_surface(0.f, 0.5f, &pos, &wi, &pdf,
                                                 &distance);
    Spectrum check = SPECTRUM_WHITE*0.020706f/2.f;
    Vec3 wi_check = Vec3(1, 0, 1).normalize();
    EXPECT_NEAR(distance, sqrtf(2), 1e-5f);
    EXPECT_NEAR(res.w[0], check.w[0], 1e-5f);
    EXPECT_NEAR(res.w[1], check.w[1], 1e-5f);
    EXPECT_NEAR(res.w[2], check.w[2], 1e-5f);
    EXPECT_NEAR(wi.x, wi_check.x, 1e-5f);
    EXPECT_NEAR(wi.y, wi_check.y, 1e-5f);
    EXPECT_NEAR(wi.z, wi_check.z, 1e-5f);
    EXPECT_EQ(pdf, 1.f);

    //cost < cos_outer
    LightSpot light3(SPECTRUM_WHITE, translation, 0.f, 1e-5f);

    res = light3.sample_visible_surface(0.f, 0.5f, &pos, &wi, &pdf,
                                        &distance);
    EXPECT_TRUE(res.is_black());
    EXPECT_EQ(pdf, 1.f);

    //inner = outer
    LightSpot light4(SPECTRUM_WHITE, translation, 1e-5f, 1e-5f);

    res = light4.sample_visible_surface(0.f, 0.5f, &pos, &wi, &pdf,
                                        &distance);
    EXPECT_TRUE(res.is_black());
    EXPECT_EQ(pdf, 1.f);
}

SPECTRE_TEST(Light, LightSun_sample_surface)
{
    LightSun light(SPECTRUM_WHITE, Ray(Point3(10, 11, 12), Vec3(0, -1, 0)), 5);
    Ray r;
    float pdf;
    Spectrum res = light.sample_surface(0., 0., 0., 0., &r, &pdf);
    EXPECT_EQ(pdf, 1.f);
    EXPECT_EQ(res.w[0], SPECTRUM_WHITE.w[0]);
    EXPECT_EQ(res.w[1], SPECTRUM_WHITE.w[1]);
    EXPECT_EQ(res.w[2], SPECTRUM_WHITE.w[2]);
    EXPECT_EQ(r.origin.x, 10.f);
    EXPECT_EQ(r.origin.y, 11.f);
    EXPECT_EQ(r.origin.z, 12.f);
    EXPECT_EQ(r.direction.x, 0.f);
    EXPECT_EQ(r.direction.y, -1.f);
    EXPECT_EQ(r.direction.z, 0.f);
}

SPECTRE_TEST(Light, LightSun_pdf_surface)
{
    LightSun light(SPECTRUM_WHITE, Ray(Point3(10, 10, 10), Vec3(0, -1, 0)), 5);
    Ray r(Point3(2, 2, 2), Vec3(0, 0, 1));
    EXPECT_EQ(light.pdf(&r), 1.f);
}

SPECTRE_TEST(Light, LightSun_sample_visible_surface)
{
    LightSun light(SPECTRUM_WHITE, Ray(Point3(10, 11, 12), Vec3(0, -1, 0)), 5);
    Point3 pos(10, 0, 12);
    Vec3 wi;
    float pdf;
    float distance;
    Spectrum res = light.sample_visible_surface(0.f, 0.f, &pos, &wi, &pdf,
                                                &distance);
    EXPECT_EQ(wi.x, 0.f);
    EXPECT_EQ(wi.y, 1.f);
    EXPECT_EQ(wi.z, 0.f);
    EXPECT_EQ(res.w[0], SPECTRUM_WHITE.w[0]);
    EXPECT_EQ(res.w[1], SPECTRUM_WHITE.w[1]);
    EXPECT_EQ(res.w[2], SPECTRUM_WHITE.w[2]);
    EXPECT_EQ(pdf, 1.f);
    EXPECT_NEAR(distance, 11.f, 1e-5f);
}

SPECTRE_TEST(Light, LightSun_pdf_surface_visible)
{
    LightSun light(SPECTRUM_WHITE, Ray(Point3(10, 10, 10), Vec3(0, -1, 0)), 5);
    Point3 origin(2, 2, 2);
    Vec3 direction(0, 0, 1);
    EXPECT_EQ(light.pdf(&origin, &direction), 0.f);
}

SPECTRE_TEST(Light, LightSun_renderable)
{
    LightSun light(SPECTRUM_WHITE, Ray(Point3(10, 10, 10), Vec3(0, -1, 0)), 5);
    EXPECT_FALSE(light.renderable());
}

SPECTRE_TEST(Light, LightSun_sunpos)
{
    //azimuth and elevation checked against NOAA data
    Date d(2018, 12, 13, 11, 47, 46);
    Point3 centre(0, 0, 0);
    LightSun light(SPECTRUM_WHITE, &centre, 1, d, 41.54f, -12.29f, 13.f);
    Ray r;
    float pdf;
    light.sample_surface(0., 0.f, 0.f, 0.f, &r, &pdf);
    EXPECT_NEAR(r.direction.x, 0.898704, 1e-5f);
    EXPECT_NEAR(r.direction.y, -0.37717, 1e-5f);
    EXPECT_NEAR(r.direction.z, -0.22376, 1e-5f);

    //day, north
    LightSun north(SPECTRUM_WHITE, &centre, 1, d, 64.12f, -21.92f, 0.f);
    north.sample_surface(0.f, 0.f, 0.f, 0.f, &r, &pdf);
    EXPECT_TRUE(r.direction.y<0);

    //day, south
    LightSun south(SPECTRUM_WHITE, &centre, 1, d, -33.91f, 18.09f, 1.f);
    south.sample_surface(0.f, 0.f, 0.f, 0.f, &r, &pdf);
    EXPECT_TRUE(r.direction.y<0);

    //night, north
    LightSun north_night(SPECTRUM_WHITE, &centre, 1, d, 36.84f, 139.30f, 1269);
    north_night.sample_surface(0.f, 0.f, 0.f, 0.f, &r, &pdf);
    EXPECT_TRUE(r.direction.y>0);

    //night, south
    LightSun south_night(SPECTRUM_WHITE, &centre, 1, d, -36.86f, 174.58f, 0.f);
    south_night.sample_surface(0.f, 0.f, 0.f, 0.f, &r, &pdf);
    EXPECT_TRUE(r.direction.y>0);
}

SPECTRE_TEST(Light, LightSky_sample_surface)
{
    const Texture* tex = new TextureUniform(SPECTRUM_WHITE);
    LightSky sky(tex, 1.f);
    Spectrum res = sky.sample_surface(0.f, 0.f, 0.f, 0.f, NULL, NULL);
    EXPECT_TRUE(res.is_black());
    delete tex;
}

SPECTRE_TEST(Light, LightSky_pdf_surface)
{
    const Texture* tex = new TextureUniform(SPECTRUM_WHITE);
    LightSky sky(tex, 1.f);
    float pdf = sky.pdf(NULL);
    EXPECT_EQ(pdf, 0.f);
    delete tex;
}

SPECTRE_TEST(Light, LightSky_sample_visible_surface)
{
    Vec2 zero(0.f);
    Vec2 one(1.f);
    errors_count[WARNING_INDEX] = 0;
    const Texture* tex = new TextureImage(TEST_ASSETS "images/correct.bmp",
                                          zero, one, UNFILTERED);
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    LightSky sky(tex, 1.f);
    Point3 pos(0, 0, 0);
    Vec3 wi;
    float pdf;
    float distance;

    Spectrum res = sky.sample_visible_surface(0.5f, 0.2f, &pos, &wi, &pdf,
                                              &distance);
    EXPECT_NEAR(pdf, 0.06101f, 1e-5f);
    EXPECT_NEAR(res.w[0], 0.41245f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.21267f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.01933f, 1e-5f);

    //pdf = 0
    res = res = sky.sample_visible_surface(1.f, 0.f, &pos, &wi, &pdf,
                                           &distance);
    EXPECT_EQ(pdf, 0.f);
    EXPECT_NEAR(res.w[0], 0.35757f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.71515f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.11919f, 1e-5f);

    //TODO: couldn't reproduce the texture pdf == 0

    delete tex;
}

SPECTRE_TEST(Light, LightSky_pdf_surface_visible)
{
    Vec2 zero(0.f);
    Vec2 one(1.f);
    errors_count[WARNING_INDEX] = 0;
    const Texture* tex = new TextureImage(TEST_ASSETS "images/correct.bmp",
                                          zero, one, UNFILTERED);
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    LightSky sky(tex, 1.f);
    Point3 pos(0, 0, 0);

    //phi > 0
    Vec3 wi = Vec3(1, 1, 0).normalize();
    float pdf = sky.pdf(&pos, &wi);
    EXPECT_NEAR(pdf, 0.82842f, 1e-5f);
    //phi <0
    wi = Vec3(1, -1, 0).normalize();
    pdf = sky.pdf(&pos, &wi);
    EXPECT_NEAR(pdf, 0.82842f, 1e-5f);
    //pdf=0
    wi = Vec3(0, 1, 0).normalize();
    pdf = sky.pdf(&pos, &wi);
    EXPECT_EQ(pdf, 0.f);
    delete tex;
}

SPECTRE_TEST(Light, LightSky_renderable)
{
    const Texture* tex = new TextureUniform(SPECTRUM_WHITE);
    LightSky sky(tex, 1.f);
    EXPECT_TRUE(sky.renderable());
    delete tex;
}

SPECTRE_TEST(Light, LightSky_radiance_escaped)
{
    Vec2 zero(0.f);
    Vec2 one(1.f);
    const Texture* tex = new TextureImage(TEST_ASSETS "images/correct.bmp",
                                          zero, one, UNFILTERED);
    LightSky sky(tex, 1.f);
    //generate rays pointing in two different quadrants in the sky.
    //per correct.bmp texture, one should be red, the other should be green.
    Ray north_east(Point3(0, 0, 0), Vec3(1, 1, 1).normalize());
    Ray north_west(Point3(0, 0, 0), Vec3(-1, 1, 1).normalize());
    Spectrum res = sky.radiance_escaped(&north_east);
    EXPECT_NEAR(res.w[0], 0.35757, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.71515, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.11919, 1e-5f);
    res = sky.radiance_escaped(&north_west);
    EXPECT_NEAR(res.w[0], 0.41245, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.21267, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.01933, 1e-5f);
    delete tex;
}

SPECTRE_TEST(Light, LightSky_constructor_warnings)
{
    Vec2 zero(0.f);
    Vec2 one(1.f);
    Texture* tex_ok = new TextureImage(TEST_ASSETS "images/correct.bmp",
                                       zero, one, UNFILTERED);
    Texture* tex_sc_x = new TextureImage(TEST_ASSETS "images/correct.bmp",
                                         zero, Vec2(2.f, 1.f), UNFILTERED);
    Texture* tex_sc_y = new TextureImage(TEST_ASSETS "images/correct.bmp",
                                         zero, Vec2(1.f, 2.f), UNFILTERED);
    Texture* tex_sh_x = new TextureImage(TEST_ASSETS "images/correct.bmp",
                                         Vec2(1.f, 0.f), one, UNFILTERED);
    Texture* tex_sh_y = new TextureImage(TEST_ASSETS "images/correct.bmp",
                                         Vec2(0.f, 1.f), one, UNFILTERED);
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    LightSky sky0(tex_ok, 1.f);
    EXPECT_EQ(errors_count[WARNING_INDEX], 0);
    LightSky sky1(tex_sc_x, 1.f);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    LightSky sky2(tex_sc_y, 1.f);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    LightSky sky3(tex_sh_x, 1.f);
    EXPECT_EQ(errors_count[WARNING_INDEX], 0);
    LightSky sky4(tex_sh_y, 1.f);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;

    delete tex_sc_x;
    delete tex_sc_y;
    delete tex_sh_x;
    delete tex_sh_y;
}

SPECTRE_TEST_END(Light)
