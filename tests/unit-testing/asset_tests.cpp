#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "primitives/asset.hpp"
#include "primitives/sphere.hpp"
#include "primitives/box.hpp"
#include "utility/utility.hpp"
#include "materials/single_brdf.hpp"
#include "materials/lambertian.hpp"
#include "textures/texture_uniform.hpp"
#include "textures/texture_library.hpp"
#include <climits>

SPECTRE_TEST_INIT(Asset_tests)

SPECTRE_TEST(Asset, constructor_get_id)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    Asset a(&s, m, 1);
    EXPECT_EQ(a.get_id(), (unsigned int)1);
}

SPECTRE_TEST(Asset, intersect)
{
    Sphere s;
    Matrix4 m;
    m.set_translation(Vec3(-2, 0, 0));
    Asset a(&s, m, 1);
    Ray r(Point3(-2, -10, 0), Vec3(0, 1, 0));
    HitPoint hit;
    MaskBoolean mask;
    float distance = FLT_MAX;

    EXPECT_FALSE(s.intersect(&r, &distance, &hit, &mask));
    ASSERT_TRUE(a.intersect(&r, &distance, &hit));
    EXPECT_EQ(hit.point_h.x, -2.f);
    EXPECT_EQ(hit.point_h.y, -1.f);
    EXPECT_EQ(hit.point_h.z, 0.f);
    distance = 0.1;
    EXPECT_FALSE(a.intersect(&r, &distance, &hit));

    m.set_identity();
    Asset a2(&s, m, 1);
    EXPECT_FALSE(a2.intersect(&r, &distance, &hit));
}

SPECTRE_TEST(Asset, get_AABB)
{
    Sphere s;
    Matrix4 m;
    m.set_translation(Vec3(-2, 0, 0));
    Asset a(&s, m, 1);
    const AABB* box = a.get_AABB();
    EXPECT_EQ(box->bounds[0].x, -3.f);
    EXPECT_EQ(box->bounds[0].y, -1.f);
    EXPECT_EQ(box->bounds[0].z, -1.f);
    EXPECT_EQ(box->bounds[1].x, -1.f);
    EXPECT_EQ(box->bounds[1].y, 1.f);
    EXPECT_EQ(box->bounds[1].z, 1.f);
}

SPECTRE_TEST(Asset, intersect_AABB)
{
    Sphere s;
    Matrix4 m;
    m.set_translation(Vec3(-2, 0, 0));
    Asset a(&s, m, 1);

    Ray success_ray, fail_ray;
    success_ray = Ray(Point3(-2, -10, 0), Vec3(0, 1, 0));
    fail_ray = Ray(Point3(2, -10, 0), Vec3(0, 1, 0));
    float in, out;

    RayProperties properties_success(success_ray);
    RayProperties properties_fail(fail_ray);

    EXPECT_FALSE(a.intersect_AABB(&fail_ray, &properties_fail, &in, &out));
    EXPECT_TRUE(a.intersect_AABB(&success_ray, &properties_success, &in, &out));
    HitPoint h;
    EXPECT_TRUE(a.intersect(&success_ray, &out, &h));
}

SPECTRE_TEST(Asset, material_setter_getter)
{
    TextureLibrary texlib;
    SingleBRDF material(new Lambertian(), texlib.get_dflt_texture());
    Box s;
    Matrix4 m;
    m.set_translation(Vec3(-2, 0, 0));

    //set materials
    SingleBRDF material1(new Lambertian(), texlib.get_dflt_texture());
    SingleBRDF material2(new Lambertian(), texlib.get_dflt_texture());
    SingleBRDF material3(new Lambertian(), texlib.get_dflt_texture());
    SingleBRDF material4(new Lambertian(), texlib.get_dflt_texture());
    const Bsdf* array[] = {&material1, &material2, &material3, &material4};
    const unsigned char indexes[] = {0, 1, 2, 3, 0, 2};
    Asset b(&s, m, 1);
    b.set_materials(array, 4, indexes);
    EXPECT_PTR_EQ(b.get_material(0), (const Bsdf*)&material1);
    EXPECT_PTR_EQ(b.get_material(1), (const Bsdf*)&material2);
    EXPECT_PTR_EQ(b.get_material(2), (const Bsdf*)&material3);
    EXPECT_PTR_EQ(b.get_material(3), (const Bsdf*)&material4);
    EXPECT_PTR_EQ(b.get_material(4), (const Bsdf*)&material1);
    EXPECT_PTR_EQ(b.get_material(5), (const Bsdf*)&material3);
}

SPECTRE_TEST(Asset, is_light)
{
    Sphere s;
    Matrix4 m;
    m.set_translation(Vec3(-2, 0, 0));
    Asset a(&s, m, 1);
    EXPECT_FALSE(a.is_light());
}

SPECTRE_TEST(Asset, mask_setting)
{
    Sphere s;
    Matrix4 m;
    m.set_translation(Vec3(-2, 0, 0));
    Asset a(&s, m, 1);
    TextureUniform black(Spectrum(0));
    MaskBoolean mask(&black, RED, false);

    Ray ray;
    ray = Ray(Point3(-2, -10, 0), Vec3(0, 1, 0));
    float distance = FLT_MAX;
    HitPoint h;
    RayProperties properties_success(ray);
    ASSERT_TRUE(a.intersect(&ray, &distance, &h));
    distance = FLT_MAX;
    a.set_mask(mask);
    EXPECT_FALSE(a.intersect(&ray, &distance, &h));
}

SPECTRE_TEST_END(Asset_tests)
