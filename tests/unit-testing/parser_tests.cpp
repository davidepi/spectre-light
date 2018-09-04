#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "parsers/config_driver.hpp"

SPECTRE_TEST_INIT(Parser_tests)

SPECTRE_TEST(Parser, out)
{
    Scene s;
    //set
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/out.txt", &s);
    EXPECT_STREQ(driver0.output.c_str(), "filename.jpg");
    delete r0;
    //default
    ConfigDriver driver1;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/resolution_ok.txt", &s);
    EXPECT_STREQ(driver1.output.c_str(), "out.ppm");
    delete r1;
}

SPECTRE_TEST(Parser, errors)
{
    Scene s;
    ConfigDriver driver0;
    errors_count[CRITICAL_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/error.txt", &s);
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 2);
    errors_count[CRITICAL_INDEX] = 0;
    delete r0;
}

SPECTRE_TEST(Parser, resolution)
{
    Scene s;
    //resolution ok
    ConfigDriver driver0;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt", &s);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver0.width, 1920);
    EXPECT_EQ(driver0.height, 1080);
    delete r0;
    //resolution default
    ConfigDriver driver1;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/out.txt", &s);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver1.width, 800);
    EXPECT_EQ(driver1.height, 600);
    delete r1;
    //not multiple of 32, but height even
    ConfigDriver driver2;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/resolution_even.txt", &s);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver2.width, 3008);
    EXPECT_EQ(driver2.height, 1504);
    delete r2;
    //not multiple of 32, but height odd
    ConfigDriver driver3;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/resolution_odd.txt", &s);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver3.width, 1952);
    EXPECT_EQ(driver3.height, 1098);
    delete r3;
}

SPECTRE_TEST(Parser, sampler)
{
    Scene s;
    //unset
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt", &s);
    EXPECT_EQ(driver0.sampler_type, (char)SPECTRE_SAMPLER_STRATIFIED);
    delete r0;
    //stratified
    ConfigDriver driver1;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/sampler_stratified.txt",
                                 &s);
    EXPECT_EQ(driver1.sampler_type, (char)SPECTRE_SAMPLER_STRATIFIED);
    delete r1;
    //random
    ConfigDriver driver2;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/sampler_random.txt", &s);
    EXPECT_EQ(driver2.sampler_type, (char)SPECTRE_SAMPLER_RANDOM);
    delete r2;
}

SPECTRE_TEST(Parser, spp)
{
    Scene s;
    //unset
    ConfigDriver driver0;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt", &s);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver0.spp, 121);
    delete r0;
    //perfect_square
    ConfigDriver driver1;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/spp_perfect_square.txt",
                                 &s);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver1.spp, 900);
    delete r1;
    //round up
    ConfigDriver driver2;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/spp_change_ceil.txt", &s);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver2.spp, 36);
    delete r2;
    //round down
    ConfigDriver driver3;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/spp_change_floor.txt", &s);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver3.spp, 36);
    delete r3;
    //random sampler, not rounding
    ConfigDriver driver4;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r4 = driver4.parse(TEST_ASSETS "parser/spp_random.txt", &s);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver4.spp, 122);
    delete r4;
}

SPECTRE_TEST(Parser, filter)
{
    Scene s;
    //unset
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt", &s);
    EXPECT_EQ(driver0.value0, 0.33f);
    EXPECT_EQ(driver0.value1, 0.33f);
    EXPECT_TRUE(driver0.tex_filter == TRILINEAR);
    delete r0;
    //box
    ConfigDriver driver1;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/filter_box.txt", &s);
    EXPECT_EQ(driver1.filter_type, (char)SPECTRE_FILTER_BOX);
    EXPECT_TRUE(driver1.tex_filter == UNFILTERED);
    delete r1;
    //tent
    ConfigDriver driver2;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/filter_tent.txt", &s);
    EXPECT_EQ(driver2.filter_type, (char)SPECTRE_FILTER_TENT);
    EXPECT_TRUE(driver2.tex_filter == TRILINEAR);
    delete r2;
    //gaussian
    ConfigDriver driver3;
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/filter_gaussian_set.txt",
                                 &s);
    EXPECT_EQ(driver3.filter_type, (char)SPECTRE_FILTER_GAUSS);
    EXPECT_EQ(driver3.value0, 2.5f);
    delete r3;
    //mitchell
    ConfigDriver driver4;
    Renderer* r4 = driver4.parse(TEST_ASSETS "parser/filter_mitchell_set.txt",
                                 &s);
    EXPECT_EQ(driver4.filter_type, (char)SPECTRE_FILTER_MITCHELL);
    EXPECT_EQ(driver4.value0, 3.f);
    EXPECT_EQ(driver4.value1, 0.f);
    delete r4;
    //lanczos
    ConfigDriver driver5;
    Renderer* r5 = driver5.parse(TEST_ASSETS "parser/filter_lanczos_set.txt",
                                 &s);
    EXPECT_EQ(driver5.filter_type, (char)SPECTRE_FILTER_LANCZOS);
    EXPECT_EQ(driver5.value0, 2.f);
    delete r5;
}

SPECTRE_TEST(Parser, camera)
{
    Scene s;
    //unset
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt", &s);
    EXPECT_EQ(driver0.camera_pos.x, 0.f);
    EXPECT_EQ(driver0.camera_pos.y, 0.f);
    EXPECT_EQ(driver0.camera_pos.z, 0.f);
    EXPECT_EQ(driver0.camera_tar.x, 0.f);
    EXPECT_EQ(driver0.camera_tar.y, 0.f);
    EXPECT_EQ(driver0.camera_tar.z, 1.f);
    EXPECT_EQ(driver0.camera_up.x, 0.f);
    EXPECT_EQ(driver0.camera_up.y, 1.f);
    EXPECT_EQ(driver0.camera_up.z, 0.f);
    EXPECT_EQ(driver0.camera_type, (char)SPECTRE_CAMERA_PERSPECTIVE);
    EXPECT_EQ(driver0.fov, 55.f);
    delete r0;
    //orthographic
    ConfigDriver driver1;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/camera_orthographic.txt",
                                 &s);
    EXPECT_EQ(driver1.camera_pos.x, 1.f);
    EXPECT_EQ(driver1.camera_pos.y, 0.f);
    EXPECT_EQ(driver1.camera_pos.z, 0.f);
    EXPECT_EQ(driver1.camera_tar.x, 0.f);
    EXPECT_EQ(driver1.camera_tar.y, 0.f);
    EXPECT_EQ(driver1.camera_tar.z, -1.f);
    EXPECT_EQ(driver1.camera_up.x, -1.f);
    EXPECT_EQ(driver1.camera_up.y, 0.f);
    EXPECT_EQ(driver1.camera_up.z, 0.f);
    EXPECT_EQ(driver1.camera_type, (char)SPECTRE_CAMERA_ORTHOGRAPHIC);
    delete r1;
    //perspective
    ConfigDriver driver2;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/camera_perspective.txt",
                                 &s);
    EXPECT_EQ(driver2.camera_pos.x, 1.f);
    EXPECT_EQ(driver2.camera_pos.y, 2.f);
    EXPECT_EQ(driver2.camera_pos.z, 3.f);
    EXPECT_EQ(driver2.camera_tar.x, 4.f);
    EXPECT_EQ(driver2.camera_tar.y, 5.f);
    EXPECT_EQ(driver2.camera_tar.z, 6.f);
    EXPECT_EQ(driver2.camera_up.x, 0.f);
    EXPECT_EQ(driver2.camera_up.y, 0.f);
    EXPECT_EQ(driver2.camera_up.z, 1.f);
    EXPECT_EQ(driver2.camera_type, (char)SPECTRE_CAMERA_PERSPECTIVE);
    EXPECT_EQ(driver2.fov, 90.f);
    delete r2;
    //panorama
    ConfigDriver driver3;
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/camera_panorama.txt", &s);
    EXPECT_EQ(driver3.camera_pos.x, 6.f);
    EXPECT_EQ(driver3.camera_pos.y, 5.f);
    EXPECT_EQ(driver3.camera_pos.z, 4.f);
    EXPECT_EQ(driver3.camera_tar.x, 3.f);
    EXPECT_EQ(driver3.camera_tar.y, 2.f);
    EXPECT_EQ(driver3.camera_tar.z, 1.f);
    EXPECT_EQ(driver3.camera_up.x, 0.f);
    EXPECT_EQ(driver3.camera_up.y, 0.f);
    EXPECT_EQ(driver3.camera_up.z, 1.f);
    EXPECT_EQ(driver3.camera_type, (char)SPECTRE_CAMERA_PANORAMA);
    delete r3;
}

SPECTRE_TEST(Parser, texture)
{
    Scene s;
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/texture.txt", &s);
    HitPoint h;

    //check that contains is not broken and returning always true
    EXPECT_FALSE(TexLib.contains_texture("bogus"));
    //check the single texture was added
    ASSERT_TRUE(TexLib.contains_texture("Manually written name"));
    EXPECT_TRUE(TexLib.contains_texture("correct.bmp"));
    //check that the map is actually added
    EXPECT_TRUE(TexLib.contains_map(TEST_ASSETS
                        "images/correct.bmp"));
    const Texture* got = TexLib.get_texture("Manually written name");
    const TextureImage* img = dynamic_cast<const TextureImage*>(got);
    //check default values
    EXPECT_STREQ(driver0.tex_name.c_str(), "");
    EXPECT_EQ(img->get_shift().x, 0.f);
    EXPECT_EQ(img->get_shift().y, 0.f);
    EXPECT_EQ(img->get_scale().x, 1.f);
    EXPECT_EQ(img->get_scale().y, 1.f);

    //check additional values
    got = TexLib.get_texture("Additional values");
    img = dynamic_cast<const TextureImage*>(got);
    EXPECT_EQ(img->get_shift().x, 1.f);
    EXPECT_EQ(img->get_shift().y, 1.4f);
    EXPECT_EQ(img->get_scale().x, .5f);
    EXPECT_EQ(img->get_scale().y, .5f);
    got = TexLib.get_texture("Uniform scale");
    img = dynamic_cast<const TextureImage*>(got);
    EXPECT_EQ(img->get_shift().x, 0.f);
    EXPECT_EQ(img->get_shift().y, 0.f);
    EXPECT_EQ(img->get_scale().x, 4.f);
    EXPECT_EQ(img->get_scale().y, 4.f);
    delete r0;

    //non existent
    ConfigDriver driver1;
    errors_count[WARNING_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/texture_non_existent.txt",
                                 &s);
    EXPECT_EQ(errors_count[WARNING_INDEX], 2);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_FALSE(TexLib.contains_texture("I do not exist"));
    delete r1;

    //duplicate
    //removed test: -> if same texture with same name will be ignored by library
    //              -> if same texture with different name, TextureLib will
    //                 handle it
//    TexLib.clear();
//    ConfigDriver driver2;
//    errors_count[WARNING_INDEX] = 0;
//    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/texture_duplicate.txt",
//                                 &s);
//    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
//    errors_count[WARNING_INDEX] = 0;
//    EXPECT_TRUE(TexLib.contains_texture("Manually written name"));
//    delete r2;
}

SPECTRE_TEST(Parser, material_textures)
{
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

    ConfigDriver driver0;
    errors_count[WARNING_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS
                                 "parser/material_texture.txt",
                                 &s);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    ASSERT_TRUE(MtlLib.contains("Diffuse color"));
    ASSERT_TRUE(MtlLib.contains("Specular color"));
    ASSERT_TRUE(MtlLib.contains("Not found diffuse"));
    const Bsdf* mat0 = MtlLib.get("Diffuse color");
    const Bsdf* mat1 = MtlLib.get("Specular color");
    const Bsdf* mat2 = MtlLib.get("Not found diffuse");

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

    //TODO: missing tests with actual imagemaps

    delete r0;
}

SPECTRE_TEST(Parser, material_duplicate)
{
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

    ConfigDriver driver0;
    errors_count[WARNING_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS
                                 "parser/material_duplicate.txt", &s);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    ASSERT_TRUE(MtlLib.contains("Red Oren-Nayar"));
    const Bsdf* mat0 = MtlLib.get("Red Oren-Nayar");
    a.set_materials((const Bsdf**)&mat0, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.0656985715f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.0338758416f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.00307962182f, 1e-5f);

    delete r0;
    MtlLib.clear();
    TexLib.clear();
}

SPECTRE_TEST(Parser, material_matte)
{
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

    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/material_matte.txt", &s);
    ASSERT_TRUE(MtlLib.contains("Red Oren-Nayar"));
    const Bsdf* mat0 = MtlLib.get("Red Oren-Nayar");

    a.set_materials((const Bsdf**)&mat0, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    a.get_material(0)->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = a.get_material(0)->value(&r.direction, &hit, &wi, &matrix, false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0], 0.0656985715f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.0338758416f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.00307962182f, 1e-5f);

    delete r0;
    TexLib.clear();
    MtlLib.clear();
}

SPECTRE_TEST(Parser, material_glossy)
{
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

    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/material_glossy.txt", &s);
    ASSERT_TRUE(MtlLib.contains("Anisotropic"));
    ASSERT_TRUE(MtlLib.contains("Blinn"));
    ASSERT_TRUE(MtlLib.contains("Beckmann"));
    ASSERT_TRUE(MtlLib.contains("Ggx"));
    //TODO: maybe RTTI to get class info?
    const Bsdf* mat0 = MtlLib.get("Anisotropic");
    const Bsdf* mat1 = MtlLib.get("Blinn");
    const Bsdf* mat2 = MtlLib.get("Beckmann");
    const Bsdf* mat3 = MtlLib.get("Ggx");

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
    MtlLib.clear();
    TexLib.clear();
}

SPECTRE_TEST(Parser, material_glass)
{
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

    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/material_glass.txt", &s);
    ASSERT_TRUE(MtlLib.contains("spec"));
    ASSERT_TRUE(MtlLib.contains("aniso"));
    ASSERT_TRUE(MtlLib.contains("blinn"));
    ASSERT_TRUE(MtlLib.contains("beckmann"));
    ASSERT_TRUE(MtlLib.contains("ggx"));
    //TODO: maybe RTTI to get class info?
    const Bsdf* mat0 = MtlLib.get("spec");
    const Bsdf* mat1 = MtlLib.get("aniso");
    const Bsdf* mat2 = MtlLib.get("blinn");
    const Bsdf* mat3 = MtlLib.get("beckmann");
    const Bsdf* mat4 = MtlLib.get("ggx");

    a.set_materials((const Bsdf**)&mat0, 1, &association);
    EXPECT_TRUE(a.intersect(&r, &distance, &hit));
    mat0->gen_shading_matrix(&hit, &matrix, &shading_normal);
    res = mat0->sample_value(0.5f, 0.5f, 0.5f, &(r.direction), &hit, &matrix,
                             &wi,
                             &pdf, true, &spec);
    EXPECT_NEAR(res.w[0], 0.0337359607f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.0337359607f, 1e-5f);
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
    EXPECT_NEAR(res.w[0], 0.0132096251f, 1e-5f);
    EXPECT_NEAR(res.w[1], 0.0132096251f, 1e-5f);
    EXPECT_NEAR(res.w[2], 0.0132096251f, 1e-5f);

    delete r0;
    MtlLib.clear();
    TexLib.clear();
}

SPECTRE_TEST(Parser, material_metal)
{
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

    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/material_metal.txt", &s);
    errors_count[WARNING_INDEX] = 0;
    ASSERT_TRUE(MtlLib.contains("Silver"));
    ASSERT_TRUE(MtlLib.contains("Aluminium"));
    ASSERT_TRUE(MtlLib.contains("Gold"));
    ASSERT_TRUE(MtlLib.contains("Copper"));
    ASSERT_TRUE(MtlLib.contains("Iron"));
    ASSERT_TRUE(MtlLib.contains("Mercury"));
    ASSERT_TRUE(MtlLib.contains("Lead"));
    ASSERT_TRUE(MtlLib.contains("Platinum"));
    ASSERT_TRUE(MtlLib.contains("Tungsten"));
    const Bsdf* mat0 = MtlLib.get("Silver");
    const Bsdf* mat1 = MtlLib.get("Aluminium");
    const Bsdf* mat2 = MtlLib.get("Gold");
    const Bsdf* mat3 = MtlLib.get("Copper");
    const Bsdf* mat4 = MtlLib.get("Iron");
    const Bsdf* mat5 = MtlLib.get("Mercury");
    const Bsdf* mat6 = MtlLib.get("Lead");
    const Bsdf* mat7 = MtlLib.get("Platinum");
    const Bsdf* mat8 = MtlLib.get("Tungsten");

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
    MtlLib.clear();
    TexLib.clear();
    delete r0;
}

SPECTRE_TEST(Parser, children)
{
    Scene s;
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/children.txt", &s);
    EXPECT_TRUE(MtlLib.contains("Red Oren-Nayar"));
    MtlLib.clear();
    delete r0;
    //children not existent
    ConfigDriver driver1;
    errors_count[ERROR_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/children_absolute.txt",
                                 &s);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
    delete r1;
    //not recursive children
    ConfigDriver driver2;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/children_recursive.txt",
                                 &s);
    EXPECT_TRUE(MtlLib.contains("Red mat")); //directly parsed
    EXPECT_FALSE(MtlLib.contains("Red Oren-Nayar")); //recursively parsed
    delete r2;
    MtlLib.clear();
}

SPECTRE_TEST(Parser, shape)
{
    Scene s0;
    Scene s1;
    Scene s2;
    //existing relative path + non existing absolute path
    ConfigDriver driver0;
    EXPECT_EQ(s0.size_shapes(), 0U);
    errors_count[ERROR_INDEX] = 0; //for the non-existing root folder obj
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/shape.txt", &s0);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    EXPECT_EQ(s0.size_shapes(), 1U); //only sphere should be added
    errors_count[ERROR_INDEX] = 0;
    delete r0;

    //wrong extension
    ConfigDriver driver1;
    errors_count[ERROR_INDEX] = 0;
    EXPECT_EQ(s1.size_shapes(), 0U);
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/shape_wrong_ext.txt", &s1);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
    EXPECT_TRUE(driver1.shapes.find("SquarePyr") == driver1.shapes.end());
    EXPECT_EQ(s1.size_shapes(), 1U); //only sphere should be added
    delete r1;

    //duplicate
    ConfigDriver driver2;
    errors_count[WARNING_INDEX] = 0;
    EXPECT_EQ(s2.size_shapes(), 0U);
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/shape_duplicate.txt", &s2);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_EQ(s2.size_shapes(), 1U); //only sphere should be added
    delete r2;
}

SPECTRE_TEST(Parser, world)
{
    const AABB* box;
    HitPoint hp;
    Ray ray;
    bool res;
    const Bsdf* material;

    Scene s0;
    ConfigDriver driver0;
    errors_count[WARNING_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/world.txt", &s0);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);//material not found
    errors_count[WARNING_INDEX] = 0;
    EXPECT_EQ(s0.size_shapes(), 2U);
    EXPECT_EQ(s0.size_assets(), 5U);
    EXPECT_EQ(driver0.deferred_meshes.size(), (size_t)0);
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
    EXPECT_PTR_NE(material, MtlLib.get_default()); //overridden
    EXPECT_PTR_EQ(material, MtlLib.get("Red Oren-Nayar"));

    //test material default when not found
    ray = Ray(Point3(5, 5, 5), Vec3(0, 0, 1));
    res = s0.k.intersect(&ray, &hp);
    ASSERT_TRUE(res);
    material = hp.asset_h->get_material(hp.index);
    EXPECT_PTR_NE(material, MtlLib.get("Blue"));
    EXPECT_PTR_EQ(material, MtlLib.get_default());
    delete r0;

    //not found
    Scene s1;
    ConfigDriver driver1;
    errors_count[WARNING_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/world_not_found.txt", &s1);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    delete r1;
}

SPECTRE_TEST(Parser, light)
{
    HitPoint hp;
    Ray ray;
    bool res;
    Spectrum emitted;

    Scene s0;
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/light.txt", &s0);
    EXPECT_EQ(s0.size_shapes(), 2U);
    EXPECT_EQ(s0.size_assets(), 4U);
    EXPECT_EQ(driver0.deferred_meshes.size(), (size_t)0);
    s0.k.buildTree();

    //test position changed for last sphere
    ray = Ray(Point3(0, 0, 0), Vec3(0, 0, 1));
    res = s0.k.intersect(&ray, &hp);
    ASSERT_TRUE(res);
    ASSERT_TRUE(hp.asset_h->is_light());
    emitted = ((AreaLight*)hp.asset_h)->emissive_spectrum();
    EXPECT_NEAR(emitted.w[0], 0.95047003f, 1e-5f);
    EXPECT_NEAR(emitted.w[1], 1.00000012f, 1e-5f);
    EXPECT_NEAR(emitted.w[2], 1.08882999f, 1e-5f);

    ray = Ray(Point3(5, 5, 5), Vec3(0, 0, 1));
    res = s0.k.intersect(&ray, &hp);
    ASSERT_TRUE(res);
    ASSERT_TRUE(hp.asset_h->is_light());
    emitted = ((AreaLight*)hp.asset_h)->emissive_spectrum();
    EXPECT_NEAR(emitted.w[0], 0.92846781f, 1e-5f);
    EXPECT_NEAR(emitted.w[1], 0.940558672f, 1e-5f);
    EXPECT_NEAR(emitted.w[2], 0.694520294f, 1e-5f);

    ray = Ray(Point3(10, 10, 10), Vec3(0, 0, 1));
    res = s0.k.intersect(&ray, &hp);
    ASSERT_TRUE(res);
    ASSERT_TRUE(hp.asset_h->is_light());
    emitted = ((AreaLight*)hp.asset_h)->emissive_spectrum();
    EXPECT_NEAR(emitted.w[0], 0.359375685f, 1e-5f);
    EXPECT_NEAR(emitted.w[1], 0.716016769f, 1e-5f);
    EXPECT_NEAR(emitted.w[2], 0.12213511f, 1e-5f);
    delete r0;

    //not found
    Scene s1;
    ConfigDriver driver1;
    errors_count[WARNING_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/light_not_found.txt", &s1);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    delete r1;
}

SPECTRE_TEST_END(Parser_tests)
