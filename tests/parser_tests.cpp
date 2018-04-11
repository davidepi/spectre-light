
#include <gtest/gtest.h>


#include "parsers/config_driver.hpp"
#include "primitives/asset.hpp"
#include "primitives/sphere.hpp"
#include "renderer.hpp"

TEST(Parser,out)
{
    //set
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/out.txt");
    EXPECT_EQ(strcmp(driver0.output.c_str(),"filename.jpg"),0);
    delete r0;
    //default
    ConfigDriver driver1;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/resolution_ok.txt");
    EXPECT_EQ(strcmp(driver1.output.c_str(),"out.ppm"),0);
    delete r1;
}

TEST(Parser,resolution)
{
    //resolution ok
    ConfigDriver driver0;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver0.width, 1920);
    EXPECT_EQ(driver0.height, 1080);
    delete r0;
    //resolution default
    ConfigDriver driver1;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/out.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver1.width, 800);
    EXPECT_EQ(driver1.height, 600);
    delete r1;
    //not multiple of 32, but height even
    ConfigDriver driver2;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/resolution_even.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver2.width, 6016);
    EXPECT_EQ(driver2.height, 3008);
    delete r2;
    //not multiple of 32, but height odd
    ConfigDriver driver3;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/resolution_odd.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver3.width, 1952);
    EXPECT_EQ(driver3.height, 1098);
    delete r3;
}

TEST(Parser,sampler)
{
    //unset
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt");
    EXPECT_EQ(driver0.sampler_type, SPECTRE_SAMPLER_STRATIFIED);
    delete r0;
    //stratified
    ConfigDriver driver1;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/sampler_stratified.txt");
    EXPECT_EQ(driver1.sampler_type, SPECTRE_SAMPLER_STRATIFIED);
    delete r1;
    //random
    ConfigDriver driver2;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/sampler_random.txt");
    EXPECT_EQ(driver2.sampler_type, SPECTRE_SAMPLER_RANDOM);
    delete r2;
}

TEST(Parser,spp)
{
    //unset
    ConfigDriver driver0;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver0.spp, 121);
    delete r0;
    //perfect_square
    ConfigDriver driver1;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/spp_perfect_square.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver1.spp, 900);
    delete r1;
    //round up
    ConfigDriver driver2;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/spp_change_ceil.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver2.spp, 36);
    delete r2;
    //round down
    ConfigDriver driver3;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/spp_change_floor.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver3.spp, 36);
    delete r3;
    //random sampler, not rounding
    ConfigDriver driver4;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r4 = driver4.parse(TEST_ASSETS "parser/spp_random.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver4.spp, 122);
    delete r4;
}

TEST(Parser,filter)
{
    //unset
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt");
    EXPECT_EQ(driver0.value0, 0.33f);
    EXPECT_EQ(driver0.value1, 0.33f);
    delete r0;
    //box
    ConfigDriver driver1;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/filter_box.txt");
    EXPECT_EQ(driver1.filter_type, SPECTRE_FILTER_BOX);
    delete r1;
    //tent
    ConfigDriver driver2;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/filter_tent.txt");
    EXPECT_EQ(driver2.filter_type, SPECTRE_FILTER_TENT);
    delete r2;
    //gaussian
    ConfigDriver driver3;
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/filter_gaussian_set.txt");
    EXPECT_EQ(driver3.filter_type, SPECTRE_FILTER_GAUSS);
    EXPECT_EQ(driver3.value0, 2.5f);
    delete r3;
    //mitchell
    ConfigDriver driver4;
    Renderer* r4 = driver4.parse(TEST_ASSETS "parser/filter_mitchell_set.txt");
    EXPECT_EQ(driver4.filter_type, SPECTRE_FILTER_MITCHELL);
    EXPECT_EQ(driver4.value0, 3.f);
    EXPECT_EQ(driver4.value1, 0.f);
    delete r4;
    //lanczos
    ConfigDriver driver5;
    Renderer* r5 = driver5.parse(TEST_ASSETS "parser/filter_lanczos_set.txt");
    EXPECT_EQ(driver5.filter_type, SPECTRE_FILTER_LANCZOS);
    EXPECT_EQ(driver5.value0, 2.f);
    delete r5;
}

TEST(Parser,camera)
{
    //unset
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt");
    EXPECT_EQ(driver0.camera_pos.x,0);
    EXPECT_EQ(driver0.camera_pos.y,0);
    EXPECT_EQ(driver0.camera_pos.z,0);
    EXPECT_EQ(driver0.camera_tar.x,0);
    EXPECT_EQ(driver0.camera_tar.y,0);
    EXPECT_EQ(driver0.camera_tar.z,1);
    EXPECT_EQ(driver0.camera_up.x,0);
    EXPECT_EQ(driver0.camera_up.y,1);
    EXPECT_EQ(driver0.camera_up.z,0);
    EXPECT_EQ(driver0.camera_type, SPECTRE_CAMERA_PERSPECTIVE);
    EXPECT_EQ(driver0.fov,55.f);
    delete r0;
    //orthographic
    ConfigDriver driver1;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/camera_orthographic.txt");
    EXPECT_EQ(driver1.camera_pos.x,1);
    EXPECT_EQ(driver1.camera_pos.y,0);
    EXPECT_EQ(driver1.camera_pos.z,0);
    EXPECT_EQ(driver1.camera_tar.x,0);
    EXPECT_EQ(driver1.camera_tar.y,0);
    EXPECT_EQ(driver1.camera_tar.z,-1);
    EXPECT_EQ(driver1.camera_up.x,-1);
    EXPECT_EQ(driver1.camera_up.y,0);
    EXPECT_EQ(driver1.camera_up.z,0);
    EXPECT_EQ(driver1.camera_type, SPECTRE_CAMERA_ORTHOGRAPHIC);
    delete r1;
    //perspective
    ConfigDriver driver2;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/camera_perspective.txt");
    EXPECT_EQ(driver2.camera_pos.x,1);
    EXPECT_EQ(driver2.camera_pos.y,2);
    EXPECT_EQ(driver2.camera_pos.z,3);
    EXPECT_EQ(driver2.camera_tar.x,4);
    EXPECT_EQ(driver2.camera_tar.y,5);
    EXPECT_EQ(driver2.camera_tar.z,6);
    EXPECT_EQ(driver2.camera_up.x,0);
    EXPECT_EQ(driver2.camera_up.y,0);
    EXPECT_EQ(driver2.camera_up.z,1);
    EXPECT_EQ(driver2.camera_type, SPECTRE_CAMERA_PERSPECTIVE);
    EXPECT_EQ(driver2.fov, 90);
    delete r2;
    //panorama
    ConfigDriver driver3;
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/camera_panorama.txt");
    EXPECT_EQ(driver3.camera_pos.x,6);
    EXPECT_EQ(driver3.camera_pos.y,5);
    EXPECT_EQ(driver3.camera_pos.z,4);
    EXPECT_EQ(driver3.camera_tar.x,3);
    EXPECT_EQ(driver3.camera_tar.y,2);
    EXPECT_EQ(driver3.camera_tar.z,1);
    EXPECT_EQ(driver3.camera_up.x,0);
    EXPECT_EQ(driver3.camera_up.y,0);
    EXPECT_EQ(driver3.camera_up.z,1);
    EXPECT_EQ(driver3.camera_type, SPECTRE_CAMERA_PANORAMA);
    delete r3;
}

TEST(Parser,texture)
{
    const char* current_dir = realpath(".",NULL);
    chdir(TEST_ASSETS);
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/textures.txt");
    //check that contains is not broken and returning always true
    EXPECT_FALSE(TexLib.contains("bogus"));
    //check the single texture was added
    EXPECT_TRUE(TexLib.contains("Manually written name"));
    //nameless addition
    EXPECT_TRUE(TexLib.contains("leave_me_here_for_testing.bmp"));
    //check the recursive file was added
    EXPECT_TRUE(TexLib.contains("recursive_load.bmp"));
    if(TexLib.contains("Red"))
    {
        const Texture* tex = TexLib.get("Red");
        Spectrum spectrum = tex->map(0.f,0.f);
        ColorRGB res = spectrum.to_xyz().to_sRGB();
        EXPECT_NEAR(res.r,1.f,1e-3f);
        EXPECT_NEAR(res.g,0.f,1e-3f);
        EXPECT_NEAR(res.b,0.f,1e-3f);
    }
    else
        FAIL();
    if(TexLib.contains("Grey"))
    {
        const Texture* tex = TexLib.get("Grey");
        Spectrum spectrum = tex->map(0.f,0.f);
        ColorRGB res = spectrum.to_xyz().to_sRGB();
        EXPECT_NEAR(res.r,0.501960814f,1e-3f);
        EXPECT_NEAR(res.g,0.501960814f,1e-3f);
        EXPECT_NEAR(res.b,0.501960814f,1e-3f);
    }
    else
        FAIL();
    delete r0;
    ConfigDriver driver1;
    errors_count[WARNING_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/texture_non_existent.txt");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_FALSE(TexLib.contains("I do not exist"));
    free(r1);
    chdir(current_dir);
    free((void*)current_dir);
}

TEST(Parser,material_matte)
{
    Bsdf material_t;
    Sphere s;
    Matrix4 m;
    Vec3 wi;
    Spectrum res;
    m.set_translation(Vec3(-2,0,0));
    Asset a(&s,m,1);
    Ray r(Point3(-2,-10,0),Vec3(0,1,0));
    HitPoint hit;
    float distance = FLT_MAX;
    wi = Vec3(0.f,1.f,0.f);
    wi.normalize();
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));

    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/material_matte.txt");
    EXPECT_TRUE(TexLib.contains("Red"));
    ASSERT_TRUE(MtlLib.contains("Like default"));
    ASSERT_TRUE(MtlLib.contains("Red Oren-Nayar"));
    //TODO: maybe RTTI to get class info?
    const Bsdf* mat0 = MtlLib.get("Like default");
    const Bsdf* mat1 = MtlLib.get("Red Oren-Nayar");

    a.set_material(mat0,1);
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));
    res = a.get_material(1)->value(&r.direction,&hit,&wi,false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[1],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[2],0.318309873f,1e-5f);

    a.set_material(mat1,1);
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));
    res = a.get_material(1)->value(&r.direction,&hit,&wi,false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0],0.0656985715f,1e-5f);
    EXPECT_NEAR(res.w[1],0.0338758416f,1e-5f);
    EXPECT_NEAR(res.w[2],0.00307962182f,1e-5f);
    delete r0;
}

TEST(Parser,material_metal)
{
    Bsdf material_t;
    Sphere s;
    Matrix4 m;
    Vec3 wi;
    Spectrum res;
    m.set_translation(Vec3(-2,0,0));
    Asset a(&s,m,1);
    Ray r(Point3(-2,-10,0),Vec3(0,1,0));
    HitPoint hit;
    float distance = FLT_MAX;
    wi = Vec3(0.f,1.f,0.f);
    wi.normalize();
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));

    ConfigDriver driver0;
    errors_count[WARNING_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/material_metal.txt");
    EXPECT_EQ(errors_count[WARNING_INDEX],1);
    errors_count[WARNING_INDEX] = 0;
    ASSERT_TRUE(MtlLib.contains("Silver"));
    ASSERT_TRUE(MtlLib.contains("Aluminium"));
    ASSERT_TRUE(MtlLib.contains("Gold"));
    ASSERT_TRUE(MtlLib.contains("Copper"));
    ASSERT_TRUE(MtlLib.contains("Iron"));
    ASSERT_TRUE(MtlLib.contains("Mercury"));
    ASSERT_TRUE(MtlLib.contains("Lead"));
    ASSERT_TRUE(MtlLib.contains("Platinum"));
    ASSERT_TRUE(MtlLib.contains("Non-existent"));
    const Bsdf* mat0 = MtlLib.get("Silver");
    const Bsdf* mat1 = MtlLib.get("Aluminium");
    const Bsdf* mat2 = MtlLib.get("Gold");
    const Bsdf* mat3 = MtlLib.get("Copper");
    const Bsdf* mat4 = MtlLib.get("Iron");
    const Bsdf* mat5 = MtlLib.get("Mercury");
    const Bsdf* mat6 = MtlLib.get("Lead");
    const Bsdf* mat7 = MtlLib.get("Platinum");
    const Bsdf* mat8 = MtlLib.get("Non-existent");

    a.set_material(mat0,1);
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));
    res = a.get_material(1)->value(&r.direction,&hit,&wi,false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[1],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[2],0.318309873f,1e-5f);

    a.set_material(mat1,1);
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));
    res = a.get_material(1)->value(&r.direction,&hit,&wi,false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[1],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[2],0.318309873f,1e-5f);

    a.set_material(mat2,1);
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));
    res = a.get_material(1)->value(&r.direction,&hit,&wi,false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[1],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[2],0.318309873f,1e-5f);

    a.set_material(mat8,1);
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));
    res = a.get_material(1)->value(&r.direction,&hit,&wi,false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[1],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[2],0.318309873f,1e-5f);

    a.set_material(mat3,1);
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));
    res = a.get_material(1)->value(&r.direction,&hit,&wi,false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[1],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[2],0.318309873f,1e-5f);

    a.set_material(mat4,1);
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));
    res = a.get_material(1)->value(&r.direction,&hit,&wi,false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[1],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[2],0.318309873f,1e-5f);

    a.set_material(mat5,1);
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));
    res = a.get_material(1)->value(&r.direction,&hit,&wi,false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[1],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[2],0.318309873f,1e-5f);

    a.set_material(mat6,1);
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));
    res = a.get_material(1)->value(&r.direction,&hit,&wi,false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[1],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[2],0.318309873f,1e-5f);

    a.set_material(mat7,1);
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));
    res = a.get_material(1)->value(&r.direction,&hit,&wi,false);
    EXPECT_FALSE(res.is_black());
    EXPECT_NEAR(res.w[0],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[1],0.318309873f,1e-5f);
    EXPECT_NEAR(res.w[2],0.318309873f,1e-5f);
}

