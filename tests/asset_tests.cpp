
#include <gtest/gtest.h>


#include "primitives/asset.hpp"
#include "primitives/sphere.hpp"
#include "utility/utility.hpp"
#include <climits>

TEST(Asset,constructor_get_id)
{
    Sphere s;
    Matrix4 m;
    m.set_identity();
    Asset a(&s,m,1);
    EXPECT_EQ(a.get_id(),1);
}

TEST(Asset,intersect)
{
    Sphere s;
    Matrix4 m;
    m.set_translation(Vec3(-2,0,0));
    Asset a(&s,m,1);
    Ray r(Point3(-2,-10,0),Vec3(0,1,0));
    HitPoint hit;
    float distance = FLT_MAX;

    EXPECT_FALSE(s.intersect(&r, &distance, &hit));
    EXPECT_TRUE(a.intersect(&r,&distance,&hit));
    EXPECT_EQ(hit.point_h.x,-2);
    EXPECT_EQ(hit.point_h.y,-1);
    EXPECT_EQ(hit.point_h.z,0);
    EXPECT_TRUE(hit.cross.is_normalized());
    distance = 0.1;
    EXPECT_FALSE(a.intersect(&r, &distance, &hit));

    m.set_identity();
    Asset a2(&s,m,1);
    EXPECT_FALSE(a2.intersect(&r,&distance,&hit));
}

TEST(Asset,get_AABB)
{
    Sphere s;
    Matrix4 m;
    m.set_translation(Vec3(-2,0,0));
    Asset a(&s,m,1);
    const AABB* box = a.get_AABB();
    EXPECT_EQ(box->bounds[0].x, -3);
    EXPECT_EQ(box->bounds[0].y, -1);
    EXPECT_EQ(box->bounds[0].z, -1);
    EXPECT_EQ(box->bounds[1].x, -1);
    EXPECT_EQ(box->bounds[1].y, 1);
    EXPECT_EQ(box->bounds[1].z, 1);
}

TEST(Asset,intersect_AABB)
{
    Sphere s;
    Matrix4 m;
    m.set_translation(Vec3(-2,0,0));
    Asset a(&s,m,1);

    Ray success_ray,fail_ray;
    success_ray = Ray(Point3(-2,-10,0),Vec3(0,1,0));
    fail_ray = Ray(Point3(2,-10,0),Vec3(0,1,0));
    float in,out;

    RayProperties properties_success(success_ray);
    RayProperties properties_fail(fail_ray);

    EXPECT_FALSE(a.intersect_AABB(&fail_ray,&properties_fail,&in,&out));
    EXPECT_TRUE(a.intersect_AABB(&success_ray,&properties_success,&in,&out));
    HitPoint h;
    EXPECT_TRUE(a.intersect(&success_ray,&out,&h));
}

TEST(Asset,material_setter_getter)
{
    Bsdf material;
    material.inherit_bdf(new Lambertian(SPECTRUM_ONE));
    Sphere s;
    Matrix4 m;
    m.set_translation(Vec3(-2,0,0));
    Asset a(&s,m,1);

    a.set_material(&material,1);
    EXPECT_EQ(a.get_material(1), &material);
}

TEST(Asset,is_light)
{
    Sphere s;
    Matrix4 m;
    m.set_translation(Vec3(-2,0,0));
    Asset a(&s,m,1);
    EXPECT_FALSE(a.is_light());
}

