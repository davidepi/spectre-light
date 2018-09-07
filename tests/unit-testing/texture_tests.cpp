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
#include "textures/mask_boolean.hpp"
#include "textures/texture_normal.hpp"
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
    EXPECT_PTR_EQ(tex3.imagemap, tex4.imagemap);
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
    TextureImage tex(TEST_ASSETS "images/correct.bmp", shift, scale,
                     UNFILTERED);
    EXPECT_EQ(tex.get_scale().x, scale.x);
    EXPECT_EQ(tex.get_scale().y, scale.y);
    EXPECT_EQ(tex.get_shift().x, shift.x);
    EXPECT_EQ(tex.get_shift().y, shift.y);
}

SPECTRE_TEST(Texture, Calculate_differentials)
{
    HitPoint hit;
    Ray rx;
    Ray ry;
    //nx>ny,nz
    hit.normal_h = Normal(0.7f, 0.6f, 0.5f);
    hit.point_h = Point3(0.1f, 0.8f, 0.2f);
    hit.dpdu = Vec3(0.9f, 0.4f, 0.6f);
    hit.dpdv = Vec3(0.2f, 0.2f, 0.7f);
    rx.origin = Point3(0.1f, 0.8f, 0.4f);
    rx.direction = Vec3(0.7f, 0.5f, 0.8f);
    ry.origin = Point3(0.9f, 0.8f, 0.4f);
    ry.direction = Vec3(0.1f, 0.5f, 0.7f);
    calculate_differentials(&hit, &rx, &ry);
    EXPECT_NEAR(hit.du.x, -0.349789947f, 1e-5f);
    EXPECT_NEAR(hit.du.y, -1.45312488f, 1e-5f);
    EXPECT_NEAR(hit.dv.x, 0.489495873f, 1e-5f);
    EXPECT_NEAR(hit.dv.y, 0.614583373f, 1e-5f);
    EXPECT_TRUE(hit.differentials);
    //ny>nz
    hit.normal_h = Normal(0.3f, 0.6f, 0.5f);
    calculate_differentials(&hit, &rx, &ry);
    EXPECT_NEAR(hit.du.x, -0.149536714f, 1e-5f);
    EXPECT_NEAR(hit.du.y, 1.08823514f, 1e-5f);
    EXPECT_NEAR(hit.dv.x, 0.288299978f, 1e-5f);
    EXPECT_NEAR(hit.dv.y, -1.14705873f, 1e-5f);
    EXPECT_TRUE(hit.differentials);
    //ny<=nz && nx<=ny && nx<=nz
    hit.normal_h = Normal(0.3f, 0.5f, 0.8f);
    calculate_differentials(&hit, &rx, &ry);
    EXPECT_NEAR(hit.du.x, -0.0581818037f, 1e-5f);
    EXPECT_NEAR(hit.du.y, 1.9809525f, 1e-5f);
    EXPECT_NEAR(hit.dv.x, -0.24727273f, 1e-5f);
    EXPECT_NEAR(hit.dv.y, -5.15238094f, 1e-5f);
    EXPECT_TRUE(hit.differentials);
    //no differentials;
    hit.point_h = Point3(0.318554252f, 0.0149820382f, 0.580925465f);
    hit.normal_h = Normal(0.249578759f, 0.70821166f, 0.150726095f);
    hit.dpdu = Vec3(0.552109361f, 0.940024793f, 0.366022646f);
    hit.dpdv = Vec3(0.197407082f, 0.976550161f, 0.130862013f);
    rx.origin = Point3(0.404442132f, 0.759377062f, 0.687527895f);
    rx.direction = Vec3(0.487480313f, 0.395991176f, 0.807750642f);
    ry.origin = Point3(0.414126188f, 0.553074598f, 0.94479984f);
    ry.direction = Vec3(0.615469813f, 0.925229012f, 0.692291856f);
    calculate_differentials(&hit, &rx, &ry);
    EXPECT_FALSE(hit.differentials);
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
    TextureImage tex(TEST_ASSETS "images/correct.bmp", shift, scale,
                     UNFILTERED);
    //Unfiltered map
    hp.du = Vec2();
    hp.dv = Vec2();
    hp.differentials = true;
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.999f, 0.1f);
    EXPECT_NEAR(color.g, 0.f, 0.1f);
    EXPECT_NEAR(color.b, 0.f, 0.1f);

    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);

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
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.f, 0.1f);
    EXPECT_NEAR(color.g, 0.999f, 0.1f);
    EXPECT_NEAR(color.b, 0.f, 0.1f);

    //Scale v component
    scale = Vec2(1.f, 3.f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.f, 0.1f);
    EXPECT_NEAR(color.g, 0.f, 0.1f);
    EXPECT_NEAR(color.b, 0.999f, 0.1f);

    //Scale uv component
    scale = Vec2(3.f, 3.f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.f, 0.1f);
    EXPECT_NEAR(color.g, 0.f, 0.1f);
    EXPECT_NEAR(color.b, 0.f, 0.1f);

    //shift u component
    scale = Vec2(1.f, 1.f);
    shift = Vec2(1.5f, 0.f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.f, 0.1f);
    EXPECT_NEAR(color.g, 0.999f, 0.1f);
    EXPECT_NEAR(color.b, 0.f, 0.1f);

    //shift v component
    scale = Vec2(1.f, 1.f);
    shift = Vec2(0.f, 1.5f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.f, 0.1f);
    EXPECT_NEAR(color.g, 0.f, 0.1f);
    EXPECT_NEAR(color.b, 0.999f, 0.1f);

    //shift uv component
    scale = Vec2(1.f, 1.f);
    shift = Vec2(1.5f, 1.5f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);
    res = tex.map(&hp);
    color = res.to_xyz().to_sRGB();
    EXPECT_NEAR(color.r, 0.f, 0.1f);
    EXPECT_NEAR(color.g, 0.f, 0.1f);
    EXPECT_NEAR(color.b, 0.f, 0.1f);
}

SPECTRE_TEST(Texture, TextureImage_map_channel)
{
    HitPoint hp;
    hp.differentials = false;
    hp.uv = Point2(0.25f, 0.25f);
    errors_count[CRITICAL_INDEX] = 0;
    ASSERT_EQ(errors_count[CRITICAL_INDEX], 0);
    Vec2 scale(1.f, 1.f);
    Vec2 shift(0.f, 0.f);
    TexelUnion res;
    ColorRGB color;
    TextureImage tex(TEST_ASSETS "images/correct.bmp", shift, scale,
                     UNFILTERED);
    //Unfiltered map
    hp.du = Vec2();
    hp.dv = Vec2();
    hp.differentials = true;
    res = tex.map_value(&hp);
    EXPECT_EQ(res.bgra_texel.r, 255U);
    EXPECT_EQ(res.bgra_texel.g, 0U);
    EXPECT_EQ(res.bgra_texel.b, 0U);
    EXPECT_EQ(res.bgra_texel.a, 255U);

    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);

    //Differentials found
    hp.du = Vec2();
    hp.dv = Vec2();
    hp.differentials = true;
    res = tex.map_value(&hp);
    EXPECT_EQ(res.bgra_texel.r, 255U);
    EXPECT_EQ(res.bgra_texel.g, 0U);
    EXPECT_EQ(res.bgra_texel.b, 0U);
    EXPECT_EQ(res.bgra_texel.a, 255U);

    //Scale u component
    hp.differentials = false;
    scale = Vec2(3.f, 1.f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);
    res = tex.map_value(&hp);
    EXPECT_EQ(res.bgra_texel.r, 0U);
    EXPECT_EQ(res.bgra_texel.g, 255U);
    EXPECT_EQ(res.bgra_texel.b, 0U);
    EXPECT_EQ(res.bgra_texel.a, 255U);

    //Scale v component
    scale = Vec2(1.f, 3.f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);
    res = tex.map_value(&hp);
    EXPECT_EQ(res.bgra_texel.r, 0U);
    EXPECT_EQ(res.bgra_texel.g, 0U);
    EXPECT_EQ(res.bgra_texel.b, 255U);
    EXPECT_EQ(res.bgra_texel.a, 255U);

    //Scale uv component
    scale = Vec2(3.f, 3.f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);
    res = tex.map_value(&hp);
    EXPECT_EQ(res.bgra_texel.r, 0U);
    EXPECT_EQ(res.bgra_texel.g, 0U);
    EXPECT_EQ(res.bgra_texel.b, 0U);
    EXPECT_EQ(res.bgra_texel.a, 255U);

    //shift u component
    scale = Vec2(1.f, 1.f);
    shift = Vec2(1.5f, 0.f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);
    res = tex.map_value(&hp);
    EXPECT_EQ(res.bgra_texel.r, 0U);
    EXPECT_EQ(res.bgra_texel.g, 255U);
    EXPECT_EQ(res.bgra_texel.b, 0U);
    EXPECT_EQ(res.bgra_texel.a, 255U);

    //shift v component
    scale = Vec2(1.f, 1.f);
    shift = Vec2(0.f, 1.5f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);
    res = tex.map_value(&hp);
    EXPECT_EQ(res.bgra_texel.r, 0U);
    EXPECT_EQ(res.bgra_texel.g, 0U);
    EXPECT_EQ(res.bgra_texel.b, 255U);
    EXPECT_EQ(res.bgra_texel.a, 255U);

    //shift uv component
    scale = Vec2(1.f, 1.f);
    shift = Vec2(1.5f, 1.5f);
    tex = TextureImage(TEST_ASSETS "images/correct.bmp", shift, scale,
                       TRILINEAR);
    res = tex.map_value(&hp);
    EXPECT_EQ(res.bgra_texel.r, 0U);
    EXPECT_EQ(res.bgra_texel.g, 0U);
    EXPECT_EQ(res.bgra_texel.b, 0U);
    EXPECT_EQ(res.bgra_texel.a, 255U);
}

SPECTRE_TEST(Mask, MaskBoolean_dflt)
{
    HitPoint hp;
    hp.differentials = false;
    errors_count[CRITICAL_INDEX] = 0;
    ASSERT_EQ(errors_count[CRITICAL_INDEX], 0);
    MaskBoolean mask;
    hp.uv = Point2(0.25f, 0.25f);
    EXPECT_TRUE(mask.is_visible(&hp));
    EXPECT_FALSE(mask.is_masked(&hp));
    hp.uv = Point2(0.75, 0.25);
    EXPECT_TRUE(mask.is_visible(&hp));
    EXPECT_FALSE(mask.is_masked(&hp));
    hp.uv = Point2(0.25, 0.75);
    EXPECT_TRUE(mask.is_visible(&hp));
    EXPECT_FALSE(mask.is_masked(&hp));
    hp.uv = Point2(0.75, 0.75);
    EXPECT_TRUE(mask.is_visible(&hp));
    EXPECT_FALSE(mask.is_masked(&hp));
}

SPECTRE_TEST(Mask, MaskBoolean_texture)
{
    HitPoint hp;
    hp.differentials = false;
    errors_count[CRITICAL_INDEX] = 0;
    ASSERT_EQ(errors_count[CRITICAL_INDEX], 0);
    Vec2 scale(1.f, 1.f);
    Vec2 shift(0.f, 0.f);
    TextureImage tx(TEST_ASSETS "images/correct.bmp", shift, scale, UNFILTERED);

    MaskBoolean mask(&tx, RED, false);
    hp.uv = Point2(0.25f, 0.25f);
    EXPECT_TRUE(mask.is_visible(&hp));
    EXPECT_FALSE(mask.is_masked(&hp));
    hp.uv = Point2(0.75, 0.25);
    EXPECT_FALSE(mask.is_visible(&hp));
    EXPECT_TRUE(mask.is_masked(&hp));
    hp.uv = Point2(0.25, 0.75);
    EXPECT_FALSE(mask.is_visible(&hp));
    EXPECT_TRUE(mask.is_masked(&hp));
    hp.uv = Point2(0.75, 0.75);
    EXPECT_FALSE(mask.is_visible(&hp));
    EXPECT_TRUE(mask.is_masked(&hp));

    MaskBoolean inverted_mask(&tx, RED, true);
    hp.uv = Point2(0.25f, 0.25f);
    EXPECT_FALSE(inverted_mask.is_visible(&hp));
    EXPECT_TRUE(inverted_mask.is_masked(&hp));
    hp.uv = Point2(0.75, 0.25);
    EXPECT_TRUE(inverted_mask.is_visible(&hp));
    EXPECT_FALSE(inverted_mask.is_masked(&hp));
    hp.uv = Point2(0.25, 0.75);
    EXPECT_TRUE(inverted_mask.is_visible(&hp));
    EXPECT_FALSE(inverted_mask.is_masked(&hp));
    hp.uv = Point2(0.75, 0.75);
    EXPECT_TRUE(inverted_mask.is_visible(&hp));
    EXPECT_FALSE(inverted_mask.is_masked(&hp));
}

SPECTRE_TEST(Texture, TextureNormal_bump)
{
    HitPoint hp;
    ShadingSpace matrix;
    Normal normal;

    hp.normal_h = Normal(0, 0, 1);
    normal = hp.normal_h;
    hp.uv = Point2(0.75, 0.25);
    hp.dpdu = Vec3(1, 0, 0);
    hp.dpdv = Vec3(0, 1, 0);

    Vec2 shift(0.f);
    Vec2 scale(1.f);
    TextureImage tx(TEST_ASSETS "images/correct.bmp", shift, scale, UNFILTERED);
    TextureNormal tn(&tx);
    tn.bump(&hp, &matrix, &normal);
    EXPECT_NEAR(normal.x, 0.577350259f, 1e-5f);
    EXPECT_NEAR(normal.y, 0.577350259f, 1e-5f);
    EXPECT_NEAR(normal.z, 0.577350259f, 1e-5f);
}

SPECTRE_TEST_END(Texture)
