#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "utility/spectrum.hpp"
#include "textures/texture.hpp"
#include "textures/texture_uniform.hpp"
#include "textures/image_map.hpp"
#include "textures/texture_image.hpp"
#include "samplers/sampler_stratified.hpp"
#include "cameras/camera_orthographic.hpp"
#include <typeinfo>

SPECTRE_TEST_INIT(Texture_tests)

SPECTRE_TEST(Texture, TextureUniform_map)
{
    TextureUniform tex(SPECTRUM_WHITE);
    Spectrum res;
    HitPoint h;

    res = tex.map(&h);
    EXPECT_EQ(res.w[0], SPECTRUM_WHITE.w[0]);
    EXPECT_EQ(res.w[1], SPECTRUM_WHITE.w[1]);
    EXPECT_EQ(res.w[2], SPECTRUM_WHITE.w[2]);
}

SPECTRE_TEST(Texture, TextureImage_constructor)
{
    Vec2 zero(0.f);
    //not readable
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    TextureImage tex0("nonexistent.bmp", zero, zero, UNFILTERED);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    //width != height
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    TextureImage tex1(TEST_ASSETS "images/2by3.bmp", zero, zero, UNFILTERED);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    //width == height but not power of 2
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    TextureImage tex2(TEST_ASSETS "images/3by3.bmp", zero, zero, UNFILTERED);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    //correct execution
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    TextureImage tex3(TEST_ASSETS "images/correct.bmp", zero, zero, UNFILTERED);
    EXPECT_EQ(errors_count[WARNING_INDEX], 0);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_EQ(typeid(*(tex3.imagemap)).hash_code(),
              typeid(ImageMapUnfiltered).hash_code());
    //correct execution, cached
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    TextureImage tex4(TEST_ASSETS "images/correct.bmp", zero, zero, UNFILTERED);
    EXPECT_EQ(errors_count[WARNING_INDEX], 0);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_EQ(tex3.imagemap, tex4.imagemap);
    //trilinear
    TexLib.clear(); //otherwise the texture wil be cached (thus unfiltered)
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    TextureImage tex5(TEST_ASSETS "images/correct.bmp", zero, zero, TRILINEAR);
    EXPECT_EQ(errors_count[WARNING_INDEX], 0);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_EQ(typeid(*(tex5.imagemap)).hash_code(),
              typeid(ImageMapTrilinear).hash_code());
    //ewa
    TexLib.clear(); //otherwise the texture wil be cached (thus unfiltered)
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    TextureImage tex6(TEST_ASSETS "images/correct.bmp", zero, zero, EWA);
    EXPECT_EQ(errors_count[WARNING_INDEX], 0);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_EQ(typeid(*(tex6.imagemap)).hash_code(),
              typeid(ImageMapEWA).hash_code());
}

SPECTRE_TEST(Texture, TextureImage_scale_shift)
{
    errors_count[CRITICAL_INDEX] = 0;
    ASSERT_EQ(errors_count[CRITICAL_INDEX], 0);
    Vec2 scale(0.5, 3.5);
    Vec2 shift(3, 2.5);
    TextureImage tex(TEST_ASSETS "images/correct.bmp", scale, shift,
                     UNFILTERED);
    EXPECT_EQ(tex.get_scale().x, scale.x);
    EXPECT_EQ(tex.get_scale().y, scale.y);
    EXPECT_EQ(tex.get_shift().x, shift.x);
    EXPECT_EQ(tex.get_shift().y, shift.y);
}

SPECTRE_TEST(Texture, differentials_creation)
{
    Ray r0, rx, ry;
    //create sampler
    unsigned int seed[32];
    for(int i = 0; i<32; i++)
        seed[i] = i;
    SamplerStratified sam(0, 2, 0, 2, 4, seed, true);

    //create camera
    Point3 pos(0.f, 0.f, -10.f);
    Point3 target(0.f, 0.f, 100.f);
    Vec3 up(0.f, 1.f, 0.f);

    //square image
    CameraOrthographic camera(&pos, &target, &up, 2, 2);
    Sample samples[4];
    sam.get_samples(samples);

    Sample test = samples[0];
    Sample testdx = samples[0];
    testdx.posx++;
    Sample testdy = samples[0];
    testdy.posy++;

    camera.create_ray(&test, &r0, &rx, &ry);
}


SPECTRE_TEST(Texture, TextureImage_map)
{
    HitPoint hp;
    hp.differentials = false;
    hp.uv = Point2(0.25f, 0.25f);
    errors_count[CRITICAL_INDEX] = 0;
    ASSERT_EQ(errors_count[CRITICAL_INDEX], 0);
    Vec2 scale(1.f, 1.f);
    Vec2 shift(0.f, 0.f);
    Spectrum res;
    ColorRGB color;
    TextureImage tex(TEST_ASSETS "images/correct.bmp", scale, shift,
                     UNFILTERED);

    //Differentials found
    hp.du = Vec2();
    hp.dv = Vec2();
    hp.differentials = true;
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.999f, 0.1f);
    EXPECT_NEAR(color.g, 0.f, 0.1f);
    EXPECT_NEAR(color.b, 0.f, 0.1f);

    //Scale u component
    hp.differentials = false;
    scale = Vec2(3.f, 1.f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", scale, shift,
                       TRILINEAR);
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.f, 0.1f);
    EXPECT_NEAR(color.g, 0.999f, 0.1f);
    EXPECT_NEAR(color.b, 0.f, 0.1f);

    //Scale v component
    scale = Vec2(1.f, 3.f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", scale, shift,
                       TRILINEAR);
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.f, 0.1f);
    EXPECT_NEAR(color.g, 0.f, 0.1f);
    EXPECT_NEAR(color.b, 0.999f, 0.1f);

    //Scale uv component
    scale = Vec2(3.f, 3.f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", scale, shift,
                       TRILINEAR);
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.f, 0.1f);
    EXPECT_NEAR(color.g, 0.f, 0.1f);
    EXPECT_NEAR(color.b, 0.f, 0.1f);

    //shift u component
    scale = Vec2(1.f, 1.f);
    shift = Vec2(1.5f, 0.f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", scale, shift,
                       TRILINEAR);
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.f, 0.1f);
    EXPECT_NEAR(color.g, 0.999f, 0.1f);
    EXPECT_NEAR(color.b, 0.f, 0.1f);

    //shift v component
    scale = Vec2(1.f, 1.f);
    shift = Vec2(0.f, 1.5f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", scale, shift,
                       TRILINEAR);
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.f, 0.1f);
    EXPECT_NEAR(color.g, 0.f, 0.1f);
    EXPECT_NEAR(color.b, 0.999f, 0.1f);

    //shift uv component
    scale = Vec2(1.f, 1.f);
    shift = Vec2(1.5f, 1.5f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", scale, shift,
                       TRILINEAR);
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.f, 0.1f);
    EXPECT_NEAR(color.g, 0.f, 0.1f);
    EXPECT_NEAR(color.b, 0.f, 0.1f);
}

SPECTRE_TEST_END(Texture)
