#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "primitives/triangle.hpp"

SPECTRE_TEST_INIT(Triangle_tests)

SPECTRE_TEST(Triangle, AABB_object_space)
{
    Vertex v0;
    Vertex v1;
    Vertex v2;
    v1.p = Point3(1, 0, 0);
    v2.p = Point3(0.5, 1, 0);
    Triangle t(v0, v1, v2);

    AABB box = t.compute_AABB();
    EXPECT_EQ(box.bounds[0].x, 0.f);
    EXPECT_EQ(box.bounds[0].y, 0.f);
    EXPECT_EQ(box.bounds[0].z, 0.f);
    EXPECT_EQ(box.bounds[1].x, 1.f);
    EXPECT_EQ(box.bounds[1].y, 1.f);
    EXPECT_EQ(box.bounds[1].z, 0.f);
}

SPECTRE_TEST(Triangle, AABB_world_space)
{
    Vertex v0;
    Vertex v1;
    Vertex v2;
    v1.p = Point3(1, 0, 0);
    v2.p = Point3(0.5, 1, 0);
    Triangle t(v0, v1, v2);
    Matrix4 m;
    m.set_identity();

    errors_count[ERROR_INDEX] = 0;
    AABB box = t.compute_AABB(NULL);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;

    box = t.compute_AABB(&m);
    EXPECT_EQ(box.bounds[0].x, 0.f);
    EXPECT_EQ(box.bounds[0].y, 0.f);
    EXPECT_EQ(box.bounds[0].z, 0.f);
    EXPECT_EQ(box.bounds[1].x, 1.f);
    EXPECT_EQ(box.bounds[1].y, 1.f);
    EXPECT_EQ(box.bounds[1].z, 0.f);

    m.set_scale(Vec3(1, 2, 3));
    t.compute_AABB(&m);
    box = t.compute_AABB(&m);
    EXPECT_EQ(box.bounds[0].x, 0.f);
    EXPECT_EQ(box.bounds[0].y, 0.f);
    EXPECT_EQ(box.bounds[0].z, 0.f);
    EXPECT_EQ(box.bounds[1].x, 1.f);
    EXPECT_EQ(box.bounds[1].y, 2.f);
    EXPECT_EQ(box.bounds[1].z, 0.f);

    m.set_translation(Vec3(1, -1, 1));
    box = t.compute_AABB(&m);
    EXPECT_EQ(box.bounds[0].x, 1.f);
    EXPECT_EQ(box.bounds[0].y, -1.f);
    EXPECT_EQ(box.bounds[0].z, 1.f);
    EXPECT_EQ(box.bounds[1].x, 2.f);
    EXPECT_EQ(box.bounds[1].y, 0.f);
    EXPECT_EQ(box.bounds[1].z, 1.f);

    m.set_rotate_z(-ONE_PI/2.f);
    box = t.compute_AABB(&m);
    EXPECT_NEAR(box.bounds[0].x, 0.f, 1e-5f);
    EXPECT_EQ(box.bounds[0].y, -1.f);
    EXPECT_EQ(box.bounds[0].z, 0.f);
    EXPECT_NEAR(box.bounds[1].x, 1.f, 1e-5f);
    EXPECT_EQ(box.bounds[1].y, 0.f);
    EXPECT_EQ(box.bounds[1].z, 0.f);
}

SPECTRE_TEST(Triangle, surface_object)
{
    Vertex v0;
    Vertex v1;
    Vertex v2;
    v0.p = Point3(-1, 0, 0);
    v1.p = Point3(1, 0, 0);
    v2.p = Point3(0.5, 1, 0);
    Triangle t(v0, v1, v2);

    EXPECT_EQ(t.surface(), 1.f);
}

SPECTRE_TEST(Triangle, surface_world)
{
    Vertex v0;
    Vertex v1;
    Vertex v2;
    v0.p = Point3(-1, 0, 0);
    v1.p = Point3(1, 0, 0);
    v2.p = Point3(0.5, 1, 0);
    Triangle t(v0, v1, v2);
    Matrix4 m;
    m.set_scale(Vec3(3, 5, 0));
    EXPECT_EQ(t.surface(&m), 15.f);

    m.set_translation(Vec3(3, 5, -8));
    EXPECT_EQ(t.surface(&m), 1.f);

    m.set_rotate_z(-2);
    EXPECT_NEAR(t.surface(&m), 1, 1e-5f);
}

SPECTRE_TEST(Triangle, intersection)
{
    Vertex v0;
    Vertex v1;
    Vertex v2;
    v0.p = Point3(-1, 0, 0);
    v1.p = Point3(1, 0, 0);
    v2.p = Point3(0.5, 1, 0);
    v0.n = Normal(0, 0, 1);
    v1.n = Normal(0, 0, 1);
    v2.n = Normal(0, 0, 1);
    v0.t = Point2(0, 0);
    v1.t = Point2(1, 0);
    v2.t = Point2(1, 1);
    Triangle t(v0, v1, v2);
    Ray r;
    float distance;
    HitPoint hit;
    bool res;
    MaskBoolean mask;

    //ray parallel to triangle
    r = Ray(Point3(0, -10, 1), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = t.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //ray origin left of the triangle, dir perpendicular
    //u<0
    r = Ray(Point3(-2, 0, 1), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = t.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //ray origin right of the triangle, dir perpendicular
    //u>1
    r = Ray(Point3(1.1, 0, 1), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = t.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //ray origin near the border, dir almost touches the edge of the triangle
    //v<0
    r = Ray(Point3(0.3, 0.1, 1), Vec3(-0.57735f, -0.57735f, -0.57735f));
    distance = FLT_MAX;
    res = t.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //ray origin near the border, dir almost touches the edge of the triangle
    //u+v>1
    r = Ray(Point3(0.3, 0.1, 1), Vec3(0.57735f, 0.57735f, -0.57735f));
    distance = FLT_MAX;
    res = t.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //hit but it's a self intersection
    r = Ray(Point3(0.5, 0.5, 1E-8), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = t.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //hit but I already have a closer hit
    r = Ray(Point3(0.5, 0.5, 3), Vec3(0, 0, -1));
    distance = 1;
    res = t.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //normal hit
    r = Ray(Point3(0.5, 0.5, 1.f), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = t.intersect(&r, &distance, &hit, &mask);
    ASSERT_TRUE(res);
    EXPECT_EQ(hit.point_h.x, 0.5f);
    EXPECT_EQ(hit.point_h.y, 0.5f);
    EXPECT_EQ(hit.point_h.z, 0.f);
    EXPECT_EQ(distance, 1.f);
    EXPECT_EQ(hit.normal_g.x, 0.f);
    EXPECT_EQ(hit.normal_g.y, 0.f);
    EXPECT_EQ(hit.normal_g.z, 1.f);
    hit.dpdu.normalize();
    EXPECT_EQ(hit.dpdu.x, 1.f);
    EXPECT_EQ(hit.dpdu.y, 0.f);
    EXPECT_EQ(hit.dpdu.z, 0.f);
}

SPECTRE_TEST(Triangle, sample_point)
{
    Vertex v0;
    Vertex v1;
    Vertex v2;
    v0.p = Point3(-1, 0, 0);
    v1.p = Point3(1, 0, 0);
    v2.p = Point3(0.5, 1, 0);
    v0.n = Normal(0, 0, 1);
    v1.n = Normal(0, 0, 1);
    v2.n = Normal(0, 0, 1);
    Triangle t(v0, v1, v2);

    Point3 p;
    Normal n;
    HitPoint hit;
    Ray r;
    float distance;
    bool res;
    MaskBoolean mask;

    //normal case, intersect from above the originated point
    t.sample_point(0.5, 0.5, NULL, &p, &n);
    r = Ray(Point3(p.x, p.y, p.z+1), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = t.intersect(&r, &distance, &hit, &mask);
    EXPECT_TRUE(res);

    //corner case, r0 a bit less than 0
    t.sample_point(0.f-FLT_EPSILON, 0.f, NULL, &p, &n);
    EXPECT_FALSE(std::isnan(p.x));
    EXPECT_FALSE(std::isnan(p.y));
    EXPECT_FALSE(std::isnan(p.z));

    //corner case, r0 a bit more than 1
    t.sample_point(1.f+FLT_EPSILON, 1.f, NULL, &p, &n);
    r = Ray(Point3(p.x, p.y, p.z+1), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = t.intersect(&r, &distance, &hit, &mask);
    EXPECT_TRUE(res);

    //corner case, r1 a bit less than 0
    t.sample_point(0.f, 0.f-FLT_EPSILON, NULL, &p, &n);
    r = Ray(Point3(p.x, p.y, p.z+1), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = t.intersect(&r, &distance, &hit, &mask);
    EXPECT_TRUE(res);

    //corner case, r1 a bit more than 1
    t.sample_point(1.f, 1.f-FLT_EPSILON, NULL, &p, &n);
    r = Ray(Point3(p.x, p.y, p.z+1), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = t.intersect(&r, &distance, &hit, &mask);
    EXPECT_TRUE(res);
}

SPECTRE_TEST(Triangle, inherited_methods)
{
    Triangle t;
    EXPECT_GT(t.get_id(), 0); //depends on the tests orderq
    EXPECT_EQ(t.get_faces_number(), 1);
    t.get_densities_array(NULL, NULL);
}

SPECTRE_TEST_END(Triangle_tests)
