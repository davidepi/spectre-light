#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "parsers/parser_config.hpp"
#include "samplers/filter_box.hpp"
#include "samplers/filter_tent.hpp"
#include "samplers/filter_mitchell.hpp"
#include "samplers/filter_gaussian.hpp"
#include "samplers/filter_lanczos.hpp"
#include "cameras/camera_orthographic.hpp"
#include "cameras/camera_perspective.hpp"
#include "cameras/camera360.hpp"
#include "primitives/sphere.hpp"
#include "textures/texture_library.hpp"
#include "lights/light_omni.hpp"
#include "lights/light_spot.hpp"
#include "lights/light_sun.hpp"

SPECTRE_TEST_INIT(Parser_tests)

SPECTRE_TEST(Parser, out)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s;

    //set
    ParserConfig driver0(&mtllib, &texlib);
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/out.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    EXPECT_STREQ(r0->film.output.filename(), "filename.bmp");
    delete r0;

    //default
    ParserConfig driver1(&mtllib, &texlib);
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/resolution_ok.txt", &s);
    ASSERT_PTR_NE(r1, NULL);
    EXPECT_STREQ(r1->film.output.filename(), "out.ppm");
    delete r1;
}

SPECTRE_TEST(Parser, errors)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s;
    ParserConfig driver0(&mtllib, &texlib);
    errors_count[CRITICAL_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/error.txt", &s);
    ASSERT_PTR_EQ(r0, NULL);
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
    delete r0;
}

SPECTRE_TEST(Parser, ParsedScene_deinit)
{
    ParsedScene parsed;
    init_ParsedScene(&parsed);
    parsed.output = strdup("test");
    parsed.error_msg = strdup("error_msg");
    parsed.sky = strdup("sky texture path");
    deinit_ParsedScene(&parsed);
    EXPECT_PTR_NULL(parsed.output);
    EXPECT_PTR_NULL(parsed.error_msg);
    EXPECT_PTR_NULL(parsed.sky);
}

SPECTRE_TEST(Parser, resolution)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s;
    //resolution ok
    ParserConfig driver0(&mtllib, &texlib);
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(r0->width, 1920);
    EXPECT_EQ(r0->height, 1080);
    delete r0;

    //resolution default
    ParserConfig driver1(&mtllib, &texlib);
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/out.txt", &s);
    ASSERT_PTR_NE(r1, NULL);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(r1->width, 800);
    EXPECT_EQ(r1->height, 600);
    delete r1;

    //not multiple of 32, but height even
    ParserConfig driver2(&mtllib, &texlib);
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/resolution_even.txt", &s);
    ASSERT_PTR_NE(r2, NULL);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(r2->width, 2016);
    EXPECT_EQ(r2->height, 1512);
    delete r2;

    //not multiple of 32, but height odd
    ParserConfig driver3(&mtllib, &texlib);
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/resolution_odd.txt", &s);
    ASSERT_PTR_NE(r3, NULL);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(r3->width, 1952);
    EXPECT_EQ(r3->height, 1098);
    delete r3;
}

SPECTRE_TEST(Parser, sampler)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s;
    //unset
    ParserConfig driver0(&mtllib, &texlib);
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    EXPECT_EQ((int)r0->sampler_type, (int)STRATIFIED);
    delete r0;

    //stratified
    ParserConfig driver1(&mtllib, &texlib);
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/sampler_stratified.txt",
                                 &s);
    ASSERT_PTR_NE(r1, NULL);
    EXPECT_EQ((int)r1->sampler_type, (int)STRATIFIED);
    delete r1;

    //random
    ParserConfig driver2(&mtllib, &texlib);
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/sampler_random.txt", &s);
    ASSERT_PTR_NE(r2, NULL);
    EXPECT_EQ((int)r2->sampler_type, (int)RANDOM);
    delete r2;
}

SPECTRE_TEST(Parser, spp)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s;
    //unset
    ParserConfig driver0(&mtllib, &texlib);
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(r0->spp, 121);
    delete r0;

    //perfect_square
    ParserConfig driver1(&mtllib, &texlib);
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/spp_perfect_square.txt",
                                 &s);
    ASSERT_PTR_NE(r1, NULL);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(r1->spp, 900);
    delete r1;

    //round up
    ParserConfig driver2(&mtllib, &texlib);
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/spp_change_ceil.txt", &s);
    ASSERT_PTR_NE(r2, NULL);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(r2->spp, 36);
    delete r2;

    //round down
    ParserConfig driver3(&mtllib, &texlib);
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/spp_change_floor.txt", &s);
    ASSERT_PTR_NE(r3, NULL);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(r3->spp, 36);
    delete r3;

    //random sampler, not rounding
    ParserConfig driver4(&mtllib, &texlib);
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r4 = driver4.parse(TEST_ASSETS "parser/spp_random.txt", &s);
    ASSERT_PTR_NE(r4, NULL);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(r4->spp, 122);
    delete r4;
}

SPECTRE_TEST(Parser, filter)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s;

    //unset
    ParserConfig driver0(&mtllib, &texlib);
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    ASSERT_PTR_NE(dynamic_cast<const FilterMitchell*>(r0->filter), NULL);
    EXPECT_EQ(r0->filter->get_param0(), 0.33f);
    EXPECT_EQ(r0->filter->get_param1(), 0.33f);
    delete r0;

    //box
    ParserConfig driver1(&mtllib, &texlib);
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/filter_box.txt", &s);
    ASSERT_PTR_NE(r1, NULL);
    ASSERT_PTR_NE(dynamic_cast<const FilterBox*>(r1->filter), NULL);
    EXPECT_EQ(r1->filter->get_param0(), -1.f);
    EXPECT_EQ(r1->filter->get_param1(), -1.f);
    delete r1;

    //tent
    ParserConfig driver2(&mtllib, &texlib);
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/filter_tent.txt", &s);
    ASSERT_PTR_NE(r2, NULL);
    ASSERT_PTR_NE(dynamic_cast<const FilterTent*>(r2->filter), NULL);
    EXPECT_EQ(r2->filter->get_param0(), -1.f);
    EXPECT_EQ(r2->filter->get_param1(), -1.f);
    delete r2;

    //gaussian
    ParserConfig driver3(&mtllib, &texlib);
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/filter_gaussian.txt",
                                 &s);
    ASSERT_PTR_NE(r3, NULL);
    ASSERT_PTR_NE(dynamic_cast<const FilterGaussian*>(r3->filter), NULL);
    EXPECT_EQ(r3->filter->get_param0(), 2.5f);
    EXPECT_EQ(r3->filter->get_param1(), -1.f);
    delete r3;

    //mitchell
    ParserConfig driver4(&mtllib, &texlib);
    Renderer* r4 = driver4.parse(TEST_ASSETS "parser/filter_mitchell.txt",
                                 &s);
    ASSERT_PTR_NE(r4, NULL);
    ASSERT_PTR_NE(dynamic_cast<const FilterMitchell*>(r4->filter), NULL);
    EXPECT_EQ(r4->filter->get_param0(), 3.f);
    EXPECT_EQ(r4->filter->get_param1(), 1.5f);
    delete r4;

    //lanczos
    ParserConfig driver5(&mtllib, &texlib);
    Renderer* r5 = driver5.parse(TEST_ASSETS "parser/filter_lanczos.txt",
                                 &s);
    ASSERT_PTR_NE(r5, NULL);
    ASSERT_PTR_NE(dynamic_cast<const FilterLanczos*>(r5->filter), NULL);
    EXPECT_EQ(r5->filter->get_param0(), 2.f);
    EXPECT_EQ(r5->filter->get_param1(), -1.f);
    delete r5;
}

SPECTRE_TEST(Parser, camera)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    //TODO: missing fov check for perspective camera
    Scene s;
    Matrix4 cam2world_expected;
    Matrix4 cam2world_actual;
    //unset
    ParserConfig driver0(&mtllib, &texlib);
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    ASSERT_PTR_NE(dynamic_cast<const CameraPerspective*>(r0->camera), NULL);
    EXPECT_EQ(((CameraPerspective*)r0->camera)->get_fov(), radians(55.f));
    cam2world_expected.set_lookAt_inverse(Point3(0.f, 0.f, 0.f),
                                          Point3(0.f, 0.f, 1.f),
                                          Vec3(0.f, 1.f, 0.f));
    r0->camera->get_camera2world(&cam2world_actual);
    EXPECT_EQ(cam2world_actual.m00, cam2world_expected.m00);
    EXPECT_EQ(cam2world_actual.m01, cam2world_expected.m01);
    EXPECT_EQ(cam2world_actual.m02, cam2world_expected.m02);
    EXPECT_EQ(cam2world_actual.m03, cam2world_expected.m03);
    EXPECT_EQ(cam2world_actual.m10, cam2world_expected.m10);
    EXPECT_EQ(cam2world_actual.m11, cam2world_expected.m11);
    EXPECT_EQ(cam2world_actual.m12, cam2world_expected.m12);
    EXPECT_EQ(cam2world_actual.m13, cam2world_expected.m13);
    EXPECT_EQ(cam2world_actual.m20, cam2world_expected.m20);
    EXPECT_EQ(cam2world_actual.m21, cam2world_expected.m21);
    EXPECT_EQ(cam2world_actual.m22, cam2world_expected.m22);
    EXPECT_EQ(cam2world_actual.m23, cam2world_expected.m23);
    EXPECT_EQ(cam2world_actual.m30, cam2world_expected.m30);
    EXPECT_EQ(cam2world_actual.m31, cam2world_expected.m31);
    EXPECT_EQ(cam2world_actual.m32, cam2world_expected.m32);
    EXPECT_EQ(cam2world_actual.m33, cam2world_expected.m33);
    delete r0;

    //orthographic
    ParserConfig driver1(&mtllib, &texlib);
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/camera_orthographic.txt",
                                 &s);
    ASSERT_PTR_NE(r1, NULL);
    ASSERT_PTR_NE(dynamic_cast<const CameraOrthographic*>(r1->camera), NULL);
    cam2world_expected.set_lookAt_inverse(Point3(1.f, 0.f, 0.f),
                                          Point3(0.f, 0.f, -1.f),
                                          Vec3(-1.f, 0.f, 0.f));
    r1->camera->get_camera2world(&cam2world_actual);
    EXPECT_EQ(cam2world_actual.m00, cam2world_expected.m00);
    EXPECT_EQ(cam2world_actual.m01, cam2world_expected.m01);
    EXPECT_EQ(cam2world_actual.m02, cam2world_expected.m02);
    EXPECT_EQ(cam2world_actual.m03, cam2world_expected.m03);
    EXPECT_EQ(cam2world_actual.m10, cam2world_expected.m10);
    EXPECT_EQ(cam2world_actual.m11, cam2world_expected.m11);
    EXPECT_EQ(cam2world_actual.m12, cam2world_expected.m12);
    EXPECT_EQ(cam2world_actual.m13, cam2world_expected.m13);
    EXPECT_EQ(cam2world_actual.m20, cam2world_expected.m20);
    EXPECT_EQ(cam2world_actual.m21, cam2world_expected.m21);
    EXPECT_EQ(cam2world_actual.m22, cam2world_expected.m22);
    EXPECT_EQ(cam2world_actual.m23, cam2world_expected.m23);
    EXPECT_EQ(cam2world_actual.m30, cam2world_expected.m30);
    EXPECT_EQ(cam2world_actual.m31, cam2world_expected.m31);
    EXPECT_EQ(cam2world_actual.m32, cam2world_expected.m32);
    EXPECT_EQ(cam2world_actual.m33, cam2world_expected.m33);
    delete r1;


    //perspective
    ParserConfig driver2(&mtllib, &texlib);
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/camera_perspective.txt",
                                 &s);
    ASSERT_PTR_NE(r2, NULL);
    ASSERT_PTR_NE(dynamic_cast<const CameraPerspective*>(r2->camera), NULL);
    EXPECT_EQ(((CameraPerspective*)r2->camera)->get_fov(), radians(90.f));
    cam2world_expected.set_lookAt_inverse(Point3(1.f, 2.f, 3.f),
                                          Point3(4.f, 5.f, 6.f),
                                          Vec3(0.f, 0.f, 1.f));
    r2->camera->get_camera2world(&cam2world_actual);
    EXPECT_EQ(cam2world_actual.m00, cam2world_expected.m00);
    EXPECT_EQ(cam2world_actual.m01, cam2world_expected.m01);
    EXPECT_EQ(cam2world_actual.m02, cam2world_expected.m02);
    EXPECT_EQ(cam2world_actual.m03, cam2world_expected.m03);
    EXPECT_EQ(cam2world_actual.m10, cam2world_expected.m10);
    EXPECT_EQ(cam2world_actual.m11, cam2world_expected.m11);
    EXPECT_EQ(cam2world_actual.m12, cam2world_expected.m12);
    EXPECT_EQ(cam2world_actual.m13, cam2world_expected.m13);
    EXPECT_EQ(cam2world_actual.m20, cam2world_expected.m20);
    EXPECT_EQ(cam2world_actual.m21, cam2world_expected.m21);
    EXPECT_EQ(cam2world_actual.m22, cam2world_expected.m22);
    EXPECT_EQ(cam2world_actual.m23, cam2world_expected.m23);
    EXPECT_EQ(cam2world_actual.m30, cam2world_expected.m30);
    EXPECT_EQ(cam2world_actual.m31, cam2world_expected.m31);
    EXPECT_EQ(cam2world_actual.m32, cam2world_expected.m32);
    EXPECT_EQ(cam2world_actual.m33, cam2world_expected.m33);
    delete r2;

    //panorama
    ParserConfig driver3(&mtllib, &texlib);
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/camera_panorama.txt", &s);
    ASSERT_PTR_NE(r3, NULL);
    ASSERT_PTR_NE(dynamic_cast<const Camera360*>(r3->camera), NULL);
    cam2world_expected.set_lookAt_inverse(Point3(6.f, 5.f, 4.f),
                                          Point3(3.f, 2.f, 1.f),
                                          Vec3(0.f, 0.f, 1.f));
    r3->camera->get_camera2world(&cam2world_actual);
    EXPECT_EQ(cam2world_actual.m00, cam2world_expected.m00);
    EXPECT_EQ(cam2world_actual.m01, cam2world_expected.m01);
    EXPECT_EQ(cam2world_actual.m02, cam2world_expected.m02);
    EXPECT_EQ(cam2world_actual.m03, cam2world_expected.m03);
    EXPECT_EQ(cam2world_actual.m10, cam2world_expected.m10);
    EXPECT_EQ(cam2world_actual.m11, cam2world_expected.m11);
    EXPECT_EQ(cam2world_actual.m12, cam2world_expected.m12);
    EXPECT_EQ(cam2world_actual.m13, cam2world_expected.m13);
    EXPECT_EQ(cam2world_actual.m20, cam2world_expected.m20);
    EXPECT_EQ(cam2world_actual.m21, cam2world_expected.m21);
    EXPECT_EQ(cam2world_actual.m22, cam2world_expected.m22);
    EXPECT_EQ(cam2world_actual.m23, cam2world_expected.m23);
    EXPECT_EQ(cam2world_actual.m30, cam2world_expected.m30);
    EXPECT_EQ(cam2world_actual.m31, cam2world_expected.m31);
    EXPECT_EQ(cam2world_actual.m32, cam2world_expected.m32);
    EXPECT_EQ(cam2world_actual.m33, cam2world_expected.m33);
    delete r3;
}

SPECTRE_TEST(Parser, texture)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s;
    ParserConfig driver0(&mtllib, &texlib);
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/texture.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    HitPoint h;
    const Texture* got;
    const TextureImage* img;

    //check that contains is not broken and returning always true
    EXPECT_FALSE(texlib.contains_texture("bogus"));
    //check the single texture was added
    ASSERT_TRUE(texlib.contains_texture("Manually written name"));
    EXPECT_TRUE(texlib.contains_texture("correct.bmp"));
    //this trick is used to remove a .. from the TEST_ASSETS macro on vs.
    File src(TEST_ASSETS "images/correct.bmp");
    //check that the map is actually added
    EXPECT_TRUE(texlib.contains_map(src.absolute_path()));
    got = texlib.get_texture("Manually written name");
    img = dynamic_cast<const TextureImage*>(got);
    ASSERT_PTR_NE(img, NULL);
    //check default values
    EXPECT_EQ(img->get_shift().x, 0.f);
    EXPECT_EQ(img->get_shift().y, 0.f);
    EXPECT_EQ(img->get_scale().x, 1.f);
    EXPECT_EQ(img->get_scale().y, 1.f);

    //check additional values
    got = texlib.get_texture("Additional values");
    img = dynamic_cast<const TextureImage*>(got);
    ASSERT_PTR_NE(img, NULL);
    EXPECT_EQ(img->get_shift().x, 1.f);
    EXPECT_EQ(img->get_shift().y, 1.4f);
    EXPECT_EQ(img->get_scale().x, .5f);
    EXPECT_EQ(img->get_scale().y, .5f);
    got = texlib.get_texture("Uniform scale");
    img = dynamic_cast<const TextureImage*>(got);
    ASSERT_PTR_NE(img, NULL);
    EXPECT_EQ(img->get_shift().x, 0.f);
    EXPECT_EQ(img->get_shift().y, 0.f);
    EXPECT_EQ(img->get_scale().x, 4.f);
    EXPECT_EQ(img->get_scale().y, 4.f);
    delete r0;

    //non existent
    ParserConfig driver1(&mtllib, &texlib);
    errors_count[WARNING_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/texture_non_existent.txt",
                                 &s);
    ASSERT_PTR_NE(r1, NULL);
    EXPECT_EQ(errors_count[WARNING_INDEX], 2);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_FALSE(texlib.contains_texture("I do not exist"));
    delete r1;

    //already existing name
    ASSERT_TRUE(texlib.contains_texture("Manually written name"));
    ParserConfig driver2(&mtllib, &texlib);
    const Texture* img0 = texlib.get_texture("Manually written name");
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/texture.txt", &s);
    const Texture* img1 = texlib.get_texture("Manually written name");
    EXPECT_PTR_EQ(img0, img1);
    delete r2;

    texlib.clear();

    //anonymous textures
    ASSERT_FALSE(texlib.contains_texture("Blue"));
    errors_count[NOTICE_INDEX] = 0;
    ParserConfig driver3(&mtllib, &texlib);
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/texture_anon.txt", &s);
    EXPECT_TRUE(texlib.contains_texture("Blue"));
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    delete r3;
}

SPECTRE_TEST(Parser, bump)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s;
    ParserConfig driver0(&mtllib, &texlib);
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/bump.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    ASSERT_TRUE(mtllib.contains("With normal map"));
    ASSERT_TRUE(mtllib.contains("No bump"));
    delete r0;
}

SPECTRE_TEST(Parser, material_textures)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s;
    Sphere sphere;
    Matrix4 m;
    Vec3 wi;
    Spectrum res;
    unsigned char association = 0;
    m.set_translation(Vec3(-2, 0, 0));
    Asset a(&sphere, m, 1);
    Ray r(Point3(-2, -10, 0), Vec3(0, 1, 0));
    HitPoint hit;
    ShadingSpace matrix;
    Normal shading_normal;
    float distance = FLT_MAX;
    wi = Vec3(0.f, 1.f, 0.f);
    wi.normalize();
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));

    ParserConfig driver0(&mtllib, &texlib);
    errors_count[WARNING_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS
                                 "parser/material_texture.txt",
                                 &s);
    ASSERT_PTR_NE(r0, NULL);
    EXPECT_EQ(errors_count[WARNING_INDEX], 2);
    errors_count[WARNING_INDEX] = 0;
    ASSERT_TRUE(mtllib.contains("Diffuse color"));
    ASSERT_TRUE(mtllib.contains("Specular color"));
    ASSERT_TRUE(mtllib.contains("Not found diffuse"));
    ASSERT_TRUE(mtllib.contains("Not found specular"));
    const Bsdf* mat0 = mtllib.get("Diffuse color");
    const Bsdf* mat1 = mtllib.get("Specular color");
    const Bsdf* mat2 = mtllib.get("Not found diffuse");
    const Bsdf* mat3 = mtllib.get("Not found specular");

    a.set_materials((const Bsdf**)&mat0, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.0656985715f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.0338758416f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.00307962182f, 1e-5f);

    a.set_materials((const Bsdf**)&mat1, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.319684714f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.319018781f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.318374306f, 1e-5f);

    a.set_materials((const Bsdf**)&mat2, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.159286112f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.159286112f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.159286112f, 1e-5f);

    a.set_materials((const Bsdf**)&mat3, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.159286112f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.159286112f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.159286112f, 1e-5f);

    texlib.clear();
    mtllib.clear();
    delete r0;
}

SPECTRE_TEST(Parser, material_duplicate)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s;
    Sphere sphere;
    Matrix4 m;
    Vec3 wi;
    Spectrum res;
    Normal shading_normal;
    unsigned char association = 0;
    m.set_translation(Vec3(-2, 0, 0));
    Asset a(&sphere, m, 1);
    Ray r(Point3(-2, -10, 0), Vec3(0, 1, 0));
    HitPoint hit;
    ShadingSpace matrix;
    float distance = FLT_MAX;
    wi = Vec3(0.f, 1.f, 0.f);
    wi.normalize();
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));

    ParserConfig driver0(&mtllib, &texlib);
    errors_count[WARNING_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS
                                 "parser/material_duplicate.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    ASSERT_TRUE(mtllib.contains("Red Oren-Nayar"));
    const Bsdf* mat0 = mtllib.get("Red Oren-Nayar");
    a.set_materials((const Bsdf**)&mat0, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.0656985715f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.0338758416f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.00307962182f, 1e-5f);

    delete r0;
    mtllib.clear();
    texlib.clear();
}

SPECTRE_TEST(Parser, material_matte)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s;
    Sphere sphere;
    Matrix4 m;
    Vec3 wi;
    Spectrum res;
    Normal shading_normal;
    unsigned char association = 0;
    m.set_translation(Vec3(-2, 0, 0));
    Asset a(&sphere, m, 1);
    Ray r(Point3(-2, -10, 0), Vec3(0, 1, 0));
    HitPoint hit;
    ShadingSpace matrix;
    float distance = FLT_MAX;
    wi = Vec3(0.f, 1.f, 0.f);
    wi.normalize();
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));

    ParserConfig driver0(&mtllib, &texlib);
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/material_matte.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    ASSERT_TRUE(mtllib.contains("Red Oren-Nayar"));
    const Bsdf* mat0 = mtllib.get("Red Oren-Nayar");
    a.set_materials((const Bsdf**)&mat0, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.0656985715f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.0338758416f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.00307962182f, 1e-5f);

    ASSERT_TRUE(mtllib.contains("Red Lambertian"));
    const Bsdf* mat1 = mtllib.get("Red Lambertian");
    a.set_materials((const Bsdf**)&mat1, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.131289f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.067696f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.006154f, 1e-5f);

    delete r0;
}

SPECTRE_TEST(Parser, material_glossy)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    unsigned char association = 0;
    Scene s;
    Sphere sphere;
    Matrix4 m;
    Vec3 wi;
    Spectrum res;
    Normal shading_normal;
    m.set_translation(Vec3(-2, 0, 0));
    Asset a(&sphere, m, 1);
    Ray r(Point3(-2, -10, 0), Vec3(0, 1, 0));
    HitPoint hit;
    ShadingSpace matrix;
    float distance = FLT_MAX;
    wi = Vec3(0.f, 1.f, 0.f);
    wi.normalize();
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));

    ParserConfig driver0(&mtllib, &texlib);
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/material_glossy.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    ASSERT_TRUE(mtllib.contains("Anisotropic"));
    ASSERT_TRUE(mtllib.contains("Blinn"));
    ASSERT_TRUE(mtllib.contains("Beckmann"));
    ASSERT_TRUE(mtllib.contains("Ggx"));
    //TODO: maybe RTTI to get class info?
    const Bsdf* mat0 = mtllib.get("Anisotropic");
    const Bsdf* mat1 = mtllib.get("Blinn");
    const Bsdf* mat2 = mtllib.get("Beckmann");
    const Bsdf* mat3 = mtllib.get("Ggx");

    a.set_materials((const Bsdf**)&mat0, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.319684714f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.319018781f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.318374306f, 1e-5f);

    a.set_materials((const Bsdf**)&mat1, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.193397462f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.307217479f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.117517456f, 1e-5f);

    //TODO: these values are not convincing, but the roughness is 0.001
    //so it should be fine... need to check again visually
    a.set_materials((const Bsdf**)&mat2, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 3183.22998f, 1e-5f);
    EXPECT_NEAR(res.w[1], 3183.16626f, 1e-5f);
    EXPECT_NEAR(res.w[2], 3183.10474f, 1e-5f);

    a.set_materials((const Bsdf**)&mat3, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.0606181398f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.0261571147f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.305674285f, 1e-5f);

    delete r0;
}

SPECTRE_TEST(Parser, material_glass)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    unsigned char association = 0;
    Scene s;
    Sphere sphere;
    Matrix4 m;
    Vec3 wi;
    Spectrum res;
    Normal shading_normal;
    float pdf;
    bool spec;
    m.set_translation(Vec3(-2, 0, 0));
    Asset a(&sphere, m, 1);
    Ray r(Point3(-2, -10, 0), Vec3(0, 1, 0));
    HitPoint hit;
    ShadingSpace matrix;
    float distance = FLT_MAX;
    wi = Vec3(0.f, 1.f, 0.f);
    wi.normalize();
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));

    ParserConfig driver0(&mtllib, &texlib);
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/material_glass.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    ASSERT_TRUE(mtllib.contains("spec"));
    ASSERT_TRUE(mtllib.contains("aniso"));
    ASSERT_TRUE(mtllib.contains("blinn"));
    ASSERT_TRUE(mtllib.contains("beckmann"));
    ASSERT_TRUE(mtllib.contains("ggx"));
    //TODO: maybe RTTI to get class info?
    const Bsdf* mat0 = mtllib.get("spec");
    const Bsdf* mat1 = mtllib.get("aniso");
    const Bsdf* mat2 = mtllib.get("blinn");
    const Bsdf* mat3 = mtllib.get("beckmann");
    const Bsdf* mat4 = mtllib.get("ggx");

    a.set_materials((const Bsdf**)&mat0, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    mat0->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat0->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 0.0337359607f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.0337359644f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.0337359607f, 1e-5f);

    mat1->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat1->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 0.00702887168f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.0140577434f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.00234295661f, 1e-5f);

    mat2->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat2->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 0.0190198198f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.0190198198f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.0190198198f, 1e-5f);

    mat3->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat3->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 0.00172365177f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.000689460721f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.00907789823f, 1e-5f);

    mat4->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat4->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 0.0132098505f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.0132098505f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.0132098505f, 1e-5f);

    delete r0;
}

SPECTRE_TEST(Parser, material_metal)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    unsigned char association = 0;
    Scene s;
    Sphere sphere;
    Matrix4 m;
    Vec3 wi;
    Spectrum res;
    Normal shading_normal;
    m.set_translation(Vec3(-2, 0, 0));
    Asset a(&sphere, m, 1);
    Ray r(Point3(-2, -10, 0), Vec3(0, 1, 0));
    HitPoint hit;
    ShadingSpace matrix;
    float distance = FLT_MAX;
    float pdf;
    bool spec;
    wi = Vec3(0.f, 1.f, 0.f);
    wi.normalize();
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));

    ParserConfig driver0(&mtllib, &texlib);
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/material_metal.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    errors_count[WARNING_INDEX] = 0;
    ASSERT_TRUE(mtllib.contains("Silver"));
    ASSERT_TRUE(mtllib.contains("Aluminium"));
    ASSERT_TRUE(mtllib.contains("Gold"));
    ASSERT_TRUE(mtllib.contains("Copper"));
    ASSERT_TRUE(mtllib.contains("Iron"));
    ASSERT_TRUE(mtllib.contains("Mercury"));
    ASSERT_TRUE(mtllib.contains("Lead"));
    ASSERT_TRUE(mtllib.contains("Platinum"));
    ASSERT_TRUE(mtllib.contains("Tungsten"));
    const Bsdf* mat0 = mtllib.get("Silver");
    const Bsdf* mat1 = mtllib.get("Aluminium");
    const Bsdf* mat2 = mtllib.get("Gold");
    const Bsdf* mat3 = mtllib.get("Copper");
    const Bsdf* mat4 = mtllib.get("Iron");
    const Bsdf* mat5 = mtllib.get("Mercury");
    const Bsdf* mat6 = mtllib.get("Lead");
    const Bsdf* mat7 = mtllib.get("Platinum");
    const Bsdf* mat8 = mtllib.get("Tungsten");

    a.set_materials((const Bsdf**)&mat0, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    mat0->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat0->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 1.02331078f, 1e-5f);
    EXPECT_NEAR(res.w[1], 1.01512516f, 1e-5f);
    EXPECT_NEAR(res.w[2], 1.00878441f, 1e-5f);

    mat1->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat1->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    //TODO: these does not seems corrects. However increasing roughness by a
    //factor 10 decreases values by a factor 10, so I guess is ok
    EXPECT_NEAR(res.w[0], 53.6285095f, 1e-5f);
    EXPECT_NEAR(res.w[1], 53.2028809f, 1e-5f);
    EXPECT_NEAR(res.w[2], 52.4990005f, 1e-5f);

    mat2->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat2->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 0.439082593f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.854520261f, 1e-5f);
    EXPECT_NEAR(res.w[2], 1.02771819f, 1e-5f);

    mat3->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat3->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 0.0810785815f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.103847116f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.142712966f, 1e-5f);

    mat4->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat4->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 0.0904954969f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.0942749753f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.0979211553f, 1e-5f);

    mat5->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat5->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 1.28624129f, 1e-5f);
    EXPECT_NEAR(res.w[1], 1.28329968f, 1e-5f);
    EXPECT_NEAR(res.w[2], 1.27962887f, 1e-5f);

    mat6->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat6->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 1.07706308f, 1e-5f);
    EXPECT_NEAR(res.w[1], 1.09061503f, 1e-5f);
    EXPECT_NEAR(res.w[2], 1.10157096f, 1e-5f);

    mat7->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat7->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 1.19391644f, 1e-5f);
    EXPECT_NEAR(res.w[1], 1.0686053f, 1e-5f);
    EXPECT_NEAR(res.w[2], 1.04458189f, 1e-5f);

    mat8->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat8->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 1.3052932f, 1e-5f);
    EXPECT_NEAR(res.w[1], 1.18112957f, 1e-5f);
    EXPECT_NEAR(res.w[2], 1.07088006f, 1e-5f);
    delete r0;
}

SPECTRE_TEST(Parser, material_dualmaterial)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s0;
    Scene s1;
    Scene s2;
    Sphere sphere;
    Matrix4 m;
    Vec3 wi;
    Spectrum res;
    Normal shading_normal;
    unsigned char association = 0;
    m.set_translation(Vec3(-2, 0, 0));
    Asset a(&sphere, m, 1);
    Ray r(Point3(-2, -10, 0), Vec3(0, 1, 0));
    HitPoint hit;
    ShadingSpace matrix;
    float distance = FLT_MAX;
    wi = Vec3(0.f, 1.f, 0.f);
    wi.normalize();
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));

    ParserConfig driver0(&mtllib, &texlib);
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/dualmat.txt", &s0);
    ASSERT_PTR_NE(r0, NULL);
    ASSERT_EQ(mtllib.size(), 4U);
    ASSERT_TRUE(mtllib.contains("Red"));
    ASSERT_TRUE(mtllib.contains("Blue"));
    ASSERT_TRUE(mtllib.contains("Inverted"));
    ASSERT_TRUE(mtllib.contains("Non-inverted"));

    const Bsdf* mat0 = mtllib.get("Inverted");
    a.set_materials((const Bsdf**)&mat0, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.318310f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.318310f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.318310f, 1e-5f);

    const Bsdf* mat1 = mtllib.get("Non-inverted");
    a.set_materials((const Bsdf**)&mat1, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.318310f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.318310f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.318310f, 1e-5f);

    mtllib.clear();
    texlib.clear();
    delete r0;

    //duplicate materials
    ASSERT_EQ(mtllib.size(), 0);
    //TODO: check with valgrind
    ParserConfig driver1(&mtllib, &texlib);
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/dualmat_duplicate.txt",
                                 &s1);
    ASSERT_PTR_NE(r1, NULL);
    EXPECT_EQ(mtllib.size(), 3U);
    delete r1;

    //not found
    mtllib.clear();
    errors_count[WARNING_INDEX] = 0;
    ParserConfig driver2(&mtllib, &texlib);
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/dualmat_not_found.txt",
                                 &s2);
    ASSERT_PTR_NE(r2, NULL);
    EXPECT_EQ(mtllib.size(), 1U);
    EXPECT_EQ(errors_count[WARNING_INDEX], 2);
    delete r2;

}

SPECTRE_TEST(Parser, children)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s;
    ParserConfig driver0(&mtllib, &texlib);
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/children.txt", &s);
    ASSERT_PTR_NE(r0, NULL);
    EXPECT_TRUE(mtllib.contains("Red Oren-Nayar"));
    mtllib.clear();
    delete r0;
    //children not existent
    ParserConfig driver1(&mtllib, &texlib);
    errors_count[ERROR_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/children_absolute.txt",
                                 &s);
    ASSERT_PTR_NE(r1, NULL);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
    delete r1;
    //not recursive children
    ParserConfig driver2(&mtllib, &texlib);
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/children_recursive.txt",
                                 &s);
    ASSERT_PTR_NE(r2, NULL);
    EXPECT_TRUE(mtllib.contains("Red mat")); //directly parsed
    EXPECT_FALSE(mtllib.contains("Red Oren-Nayar")); //recursively parsed
    delete r2;
}

SPECTRE_TEST(Parser, shape)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Scene s0;
    Scene s1;
    Scene s2;
    //existing relative path + non existing absolute path
    ParserConfig driver0(&mtllib, &texlib);
    EXPECT_EQ(s0.size_shapes(), 0U);
    errors_count[ERROR_INDEX] = 0; //for the non-existing root folder obj
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/shape.txt", &s0);
    ASSERT_PTR_NE(r0, NULL);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    EXPECT_EQ(s0.size_shapes(), 1U); //only sphere should be added
    errors_count[ERROR_INDEX] = 0;
    delete r0;

    //wrong extension
    ParserConfig driver1(&mtllib, &texlib);
    errors_count[ERROR_INDEX] = 0;
    EXPECT_EQ(s1.size_shapes(), 0U);
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/shape_wrong_ext.txt", &s1);
    ASSERT_PTR_NE(r1, NULL);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
    EXPECT_EQ(s1.size_shapes(), 1U); //only sphere should be added
    delete r1;

    //duplicate
    ParserConfig driver2(&mtllib, &texlib);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_EQ(s2.size_shapes(), 0U);
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/shape_duplicate.txt", &s2);
    ASSERT_PTR_NE(r2, NULL);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_EQ(s2.size_shapes(), 1U); //only sphere should be added
    delete r2;
}

SPECTRE_TEST(Parser, world)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    const AABB* box;
    HitPoint hp;
    Ray ray;
    bool res;
    const Bsdf* material;

    Scene s0;
    ParserConfig driver0(&mtllib, &texlib);
    errors_count[WARNING_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/world.txt", &s0);
    ASSERT_PTR_NE(r0, NULL);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);//material not found
    errors_count[WARNING_INDEX] = 0;
    EXPECT_EQ(s0.size_shapes(), 2U);
    EXPECT_EQ(s0.size_assets(), 7U);
//    EXPECT_EQ(driver0.deferred_meshes.size(), (size_t)0);
    s0.k.buildTree();

    //test position changed for last sphere
    ray = Ray(Point3(5, 5, 5), Vec3(0, 0, 1));
    res = s0.k.intersect(&ray, &hp);
    ASSERT_TRUE(res);
    // only way to get private info about position
    box = hp.asset_h->get_AABB();
    EXPECT_EQ(box->bounds[0].x, 4.f);
    EXPECT_EQ(box->bounds[0].y, 4.f);
    EXPECT_EQ(box->bounds[0].z, 4.f);
    EXPECT_EQ(box->bounds[1].x, 6.f);
    EXPECT_EQ(box->bounds[1].y, 6.f);
    EXPECT_EQ(box->bounds[1].z, 6.f);

    //test scale changed for last sphere
    ray = Ray(Point3(15, -15, 15), Vec3(0, 0, 1));
    res = s0.k.intersect(&ray, &hp);
    ASSERT_TRUE(res);
    box = hp.asset_h->get_AABB();
    EXPECT_EQ(box->bounds[0].x, 13.f);
    EXPECT_EQ(box->bounds[0].y, -17.f);
    EXPECT_EQ(box->bounds[0].z, 13.f);
    EXPECT_EQ(box->bounds[1].x, 17.f);
    EXPECT_EQ(box->bounds[1].y, -13.f);
    EXPECT_EQ(box->bounds[1].z, 17.f);

    //test material overriden for second sphere
    ray = Ray(Point3(-10, -10, -9.5), Vec3(0, 0, 1));
    res = s0.k.intersect(&ray, &hp);
    ASSERT_TRUE(res);
    material = hp.asset_h->get_material(hp.index);
    EXPECT_PTR_NE(material, mtllib.get_default()); //overridden
    EXPECT_PTR_EQ(material, mtllib.get("Red Oren-Nayar"));

    //test material default when not found
    ray = Ray(Point3(5, 5, 5), Vec3(0, 0, 1));
    res = s0.k.intersect(&ray, &hp);
    ASSERT_TRUE(res);
    material = hp.asset_h->get_material(hp.index);
    EXPECT_PTR_NE(material, mtllib.get("Blue"));
    EXPECT_PTR_EQ(material, mtllib.get_default());

    //mask black
    ray = Ray(Point3(30, 30, 30), Vec3(0, 0, 1));
    res = s0.k.intersect(&ray, &hp);
    ASSERT_FALSE(res);

    //mask white
    ray = Ray(Point3(-30, -30, -30), Vec3(0, 0, 1));
    res = s0.k.intersect(&ray, &hp);
    ASSERT_TRUE(res);

    delete r0;

    //not found
    Scene s1;
    ParserConfig driver1(&mtllib, &texlib);
    errors_count[WARNING_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/world_not_found.txt", &s1);
    ASSERT_PTR_NE(r1, NULL);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    delete r1;

}

SPECTRE_TEST(Parser, light)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    HitPoint hp;
    Ray ray;
    bool res;
    Spectrum emitted;

    Scene s0;
    ParserConfig driver0(&mtllib, &texlib);
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/light.txt", &s0);
    ASSERT_PTR_NE(r0, NULL);
    EXPECT_EQ(s0.size_lights(), 7U);
    EXPECT_EQ(s0.size_shapes(), 2U);
    EXPECT_EQ(s0.size_assets(), 4U);
//    EXPECT_EQ(driver0.deferred_meshes.size(), (size_t)0);
    s0.k.buildTree();

    //test position changed for last sphere
    ray = Ray(Point3(0, 0, 0), Vec3(0, 0, 1));
    res = s0.k.intersect(&ray, &hp);
    ASSERT_TRUE(res);
    ASSERT_TRUE(hp.asset_h->is_light());
    emitted = ((LightArea*)hp.asset_h)->emissive_spectrum();
    EXPECT_NEAR(emitted.w[0], 0.95047003f, 1e-5f);
    EXPECT_NEAR(emitted.w[1], 1.00000012f, 1e-5f);
    EXPECT_NEAR(emitted.w[2], 1.08882999f, 1e-5f);

    ray = Ray(Point3(5, 5, 5), Vec3(0, 0, 1));
    res = s0.k.intersect(&ray, &hp);
    ASSERT_TRUE(res);
    ASSERT_TRUE(hp.asset_h->is_light());
    emitted = ((LightArea*)hp.asset_h)->emissive_spectrum();
    EXPECT_NEAR(emitted.w[0], 0.92846781f, 1e-5f);
    EXPECT_NEAR(emitted.w[1], 0.940558672f, 1e-5f);
    EXPECT_NEAR(emitted.w[2], 0.694520294f, 1e-5f);

    ray = Ray(Point3(10, 10, 10), Vec3(0, 0, 1));
    res = s0.k.intersect(&ray, &hp);
    ASSERT_TRUE(res);
    ASSERT_TRUE(hp.asset_h->is_light());
    emitted = ((LightArea*)hp.asset_h)->emissive_spectrum();
    EXPECT_NEAR(emitted.w[0], 0.359375685f, 1e-5f);
    EXPECT_NEAR(emitted.w[1], 0.716016769f, 1e-5f);
    EXPECT_NEAR(emitted.w[2], 0.12213511f, 1e-5f);

    //assert that sun is created
    const Light* sun = s0.get_light(6);
    EXPECT_EQ(typeid(*(sun)).hash_code(),
              typeid(LightSun).hash_code());

    //assert that omni is created
    const Light* omni = s0.get_light(1);
    EXPECT_EQ(typeid(*(omni)).hash_code(),
              typeid(LightOmni).hash_code());

    //assert that spot is created
    const Light* spot = s0.get_light(0);
    EXPECT_EQ(typeid(*(spot)).hash_code(),
              typeid(LightSpot).hash_code());

    //assert that no sky is created
    EXPECT_TRUE(s0.get_escaped_radiance(&ray).is_black());

    delete r0;

    //not found
    Scene s1;
    ParserConfig driver1(&mtllib, &texlib);
    errors_count[WARNING_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/light_not_found.txt", &s1);
    ASSERT_PTR_NE(r1, NULL);
    EXPECT_EQ(errors_count[WARNING_INDEX], 2);
    errors_count[WARNING_INDEX] = 0;

    //assert that the sky is created even if the texture was not found
    EXPECT_FALSE(s1.get_escaped_radiance(&ray).is_black());
    delete r1;
}

SPECTRE_TEST_END(Parser_tests)
