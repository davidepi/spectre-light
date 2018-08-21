#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "primitives/box.hpp"
#include "utility/utility.hpp"
#include <climits>

SPECTRE_TEST_INIT(Box_tests)

SPECTRE_TEST(Box, AABB_object_space)
{
    Box box;
    AABB aabb = box.compute_AABB();
    EXPECT_EQ(aabb.bounds[0].x, 0.f);
    EXPECT_EQ(aabb.bounds[0].y, 0.f);
    EXPECT_EQ(aabb.bounds[0].z, 0.f);
    EXPECT_EQ(aabb.bounds[1].x, 1.f);
    EXPECT_EQ(aabb.bounds[1].y, 1.f);
    EXPECT_EQ(aabb.bounds[1].z, 1.f);
}

SPECTRE_TEST(Box, AABB_world_space)
{
    //scale
    Box b;
    Matrix4 transform;
    transform.set_scale(3.f);
    AABB box = b.compute_AABB(&transform);
    EXPECT_EQ(box.bounds[0].x, 0.f);
    EXPECT_EQ(box.bounds[0].y, 0.f);
    EXPECT_EQ(box.bounds[0].z, 0.f);
    EXPECT_EQ(box.bounds[1].x, 3.f);
    EXPECT_EQ(box.bounds[1].y, 3.f);
    EXPECT_EQ(box.bounds[1].z, 3.f);

    //translation
    transform.set_translation(Vec3(-1, 10, 3.5));
    box = b.compute_AABB(&transform);
    EXPECT_EQ(box.bounds[0].x, -1.f);
    EXPECT_EQ(box.bounds[0].y, 10.f);
    EXPECT_EQ(box.bounds[0].z, 3.5f);
    EXPECT_EQ(box.bounds[1].x, 0.f);
    EXPECT_EQ(box.bounds[1].y, 11.f);
    EXPECT_EQ(box.bounds[1].z, 4.5f);

    //rotation -> the pivot is in (0,0,0)
    transform.set_rotate_z(ONE_PI/2.f);
    box = b.compute_AABB(&transform);
    EXPECT_NEAR(box.bounds[0].x, -1.f, 1e-5f);
    EXPECT_NEAR(box.bounds[0].y, 0.f, 1e-5f);
    EXPECT_NEAR(box.bounds[0].z, 0.f, 1e-5f);
    EXPECT_NEAR(box.bounds[1].x, 0.f, 1e-5f);
    EXPECT_NEAR(box.bounds[1].y, 1.f, 1e-5f);
    EXPECT_NEAR(box.bounds[1].z, 1.f, 1e-5f);

    //null transform
    errors_count[ERROR_INDEX] = 0;
    box = b.compute_AABB(NULL);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(Box, get_faces_number)
{
    Box b;
    EXPECT_EQ(b.get_faces_number(), 6);
}

SPECTRE_TEST(Box, surface_object)
{
    Box b;
    EXPECT_EQ(b.surface(), 6.f);
}

SPECTRE_TEST(Box, surface_world)
{
    Box b;
    Matrix4 m;
    m.set_scale(2.5f);
    EXPECT_NEAR(b.surface(&m), 37.5f, 1e-5f);

    m.set_scale(Vec3(1, 2, 3));
    EXPECT_NEAR(b.surface(&m), 22.f, 1e-5f);
}

SPECTRE_TEST(Box, intersect)
{
    //if these are not granted the normal will always be wrong
    ASSERT_EQ(sign(10), 1);
    ASSERT_EQ(sign(0), 1);
    ASSERT_EQ(sign(-10), -1);
    MaskBoolean mask;

    Box box;
    Ray r;
    float distance;
    HitPoint hit;
    bool res;

    //point front, hit front
    r = Ray(Point3(0.5f, -10.f, 0.5f), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    ASSERT_TRUE(res);
    EXPECT_EQ(distance, 10.f);
    EXPECT_EQ(hit.point_h.x, 0.5f);
    EXPECT_EQ(hit.point_h.y, 0.f);
    EXPECT_EQ(hit.point_h.z, 0.5f);
    EXPECT_EQ(hit.geometric.n.x, 0.f);
    EXPECT_EQ(hit.geometric.n.y, -1.f);
    EXPECT_EQ(hit.geometric.n.z, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.x, 1.f);
    EXPECT_EQ(hit.geometric.dpdu.y, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.z, 0.f);

    //point back hit back
    r = Ray(Point3(0.5f, 10.f, 0.5f), Vec3(0, -1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    ASSERT_TRUE(res);
    EXPECT_EQ(distance, 9.f);
    EXPECT_EQ(hit.point_h.x, 0.5f);
    EXPECT_EQ(hit.point_h.y, 1.f);
    EXPECT_EQ(hit.point_h.z, 0.5f);
    EXPECT_EQ(hit.geometric.n.x, 0.f);
    EXPECT_EQ(hit.geometric.n.y, 1.f);
    EXPECT_EQ(hit.geometric.n.z, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.x, -1.f);
    EXPECT_EQ(hit.geometric.dpdu.y, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.z, 0.f);

    //point right hit right
    r = Ray(Point3(5, 0.5, 0.5), Vec3(-1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    ASSERT_TRUE(res);
    EXPECT_EQ(distance, 4.f);
    EXPECT_EQ(hit.point_h.x, 1.f);
    EXPECT_EQ(hit.point_h.y, 0.5f);
    EXPECT_EQ(hit.point_h.z, 0.5f);
    EXPECT_EQ(hit.geometric.n.x, 1.f);
    EXPECT_EQ(hit.geometric.n.y, 0.f);
    EXPECT_EQ(hit.geometric.n.z, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.x, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.y, 1.f);
    EXPECT_EQ(hit.geometric.dpdu.z, 0.f);

    //point left hit left
    r = Ray(Point3(-5, 0.5, 0.5), Vec3(1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    ASSERT_TRUE(res);
    EXPECT_EQ(distance, 5.f);
    EXPECT_EQ(hit.point_h.x, 0.f);
    EXPECT_EQ(hit.point_h.y, 0.5f);
    EXPECT_EQ(hit.point_h.z, 0.5f);
    EXPECT_EQ(hit.geometric.n.x, -1.f);
    EXPECT_EQ(hit.geometric.n.y, 0.f);
    EXPECT_EQ(hit.geometric.n.z, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.x, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.y, -1.f);
    EXPECT_EQ(hit.geometric.dpdu.z, 0.f);

    //point top hit top
    r = Ray(Point3(0.5, 0.5, 3), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    ASSERT_TRUE(res);
    EXPECT_EQ(distance, 2.f);
    EXPECT_EQ(hit.point_h.x, 0.5f);
    EXPECT_EQ(hit.point_h.y, 0.5f);
    EXPECT_EQ(hit.point_h.z, 1.f);
    EXPECT_EQ(hit.geometric.n.x, 0.f);
    EXPECT_EQ(hit.geometric.n.y, 0.f);
    EXPECT_EQ(hit.geometric.n.z, 1.f);
    EXPECT_EQ(hit.geometric.dpdu.x, 1.f);
    EXPECT_EQ(hit.geometric.dpdu.y, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.z, 0.f);

    //point bottom hit bottom
    r = Ray(Point3(0.5, 0.5, -3), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    ASSERT_TRUE(res);
    EXPECT_EQ(distance, 3.f);
    EXPECT_EQ(hit.point_h.x, 0.5f);
    EXPECT_EQ(hit.point_h.y, 0.5f);
    EXPECT_EQ(hit.point_h.z, 0.f);
    EXPECT_EQ(hit.geometric.n.x, 0.f);
    EXPECT_EQ(hit.geometric.n.y, 0.f);
    EXPECT_EQ(hit.geometric.n.z, -1.f);
    EXPECT_EQ(hit.geometric.dpdu.x, -1.f);
    EXPECT_EQ(hit.geometric.dpdu.y, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.z, 0.f);

    //inside hit front
    r = Ray(Point3(0.5f, 0.5f, 0.5f), Vec3(0, -1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    ASSERT_TRUE(res);
    EXPECT_EQ(distance, 0.5f);
    EXPECT_EQ(hit.point_h.x, 0.5f);
    EXPECT_EQ(hit.point_h.y, 0.f);
    EXPECT_EQ(hit.point_h.z, 0.5f);
    EXPECT_EQ(hit.geometric.n.x, 0.f);
    EXPECT_EQ(hit.geometric.n.y, -1.f);
    EXPECT_EQ(hit.geometric.n.z, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.x, 1.f);
    EXPECT_EQ(hit.geometric.dpdu.y, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.z, 0.f);

    //inside hit back
    r = Ray(Point3(0.5f, 0.5f, 0.5f), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    ASSERT_TRUE(res);
    EXPECT_EQ(distance, 0.5f);
    EXPECT_EQ(hit.point_h.x, 0.5f);
    EXPECT_EQ(hit.point_h.y, 1.f);
    EXPECT_EQ(hit.point_h.z, 0.5f);
    EXPECT_EQ(hit.geometric.n.x, 0.f);
    EXPECT_EQ(hit.geometric.n.y, 1.f);
    EXPECT_EQ(hit.geometric.n.z, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.x, -1.f);
    EXPECT_EQ(hit.geometric.dpdu.y, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.z, 0.f);

    //inside hit right
    r = Ray(Point3(0.5f, 0.5f, 0.5f), Vec3(1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    ASSERT_TRUE(res);
    EXPECT_EQ(distance, 0.5f);
    EXPECT_EQ(hit.point_h.x, 1.f);
    EXPECT_EQ(hit.point_h.y, 0.5f);
    EXPECT_EQ(hit.point_h.z, 0.5f);
    EXPECT_EQ(hit.geometric.n.x, 1.f);
    EXPECT_EQ(hit.geometric.n.y, 0.f);
    EXPECT_EQ(hit.geometric.n.z, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.x, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.y, 1.f);
    EXPECT_EQ(hit.geometric.dpdu.z, 0.f);

    //inside hit left
    r = Ray(Point3(0.5f, 0.5f, 0.5f), Vec3(-1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    ASSERT_TRUE(res);
    EXPECT_EQ(distance, 0.5f);
    EXPECT_EQ(hit.point_h.x, 0.f);
    EXPECT_EQ(hit.point_h.y, 0.5f);
    EXPECT_EQ(hit.point_h.z, 0.5f);
    EXPECT_EQ(hit.geometric.n.x, -1.f);
    EXPECT_EQ(hit.geometric.n.y, 0.f);
    EXPECT_EQ(hit.geometric.n.z, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.x, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.y, -1.f);
    EXPECT_EQ(hit.geometric.dpdu.z, 0.f);

    //inside hit top
    r = Ray(Point3(0.5, 0.5, 0.5), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    ASSERT_TRUE(res);
    EXPECT_EQ(distance, 0.5f);
    EXPECT_EQ(hit.point_h.x, 0.5f);
    EXPECT_EQ(hit.point_h.y, 0.5f);
    EXPECT_EQ(hit.point_h.z, 1.f);
    EXPECT_EQ(hit.geometric.n.x, 0.f);
    EXPECT_EQ(hit.geometric.n.y, 0.f);
    EXPECT_EQ(hit.geometric.n.z, 1.f);
    EXPECT_EQ(hit.geometric.dpdu.x, 1.f);
    EXPECT_EQ(hit.geometric.dpdu.y, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.z, 0.f);

    //inside hit bottom
    r = Ray(Point3(0.5, 0.5, 0.5), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    ASSERT_TRUE(res);
    EXPECT_EQ(distance, 0.5f);
    EXPECT_EQ(hit.point_h.x, 0.5f);
    EXPECT_EQ(hit.point_h.y, 0.5f);
    EXPECT_EQ(hit.point_h.z, 0.f);
    EXPECT_EQ(hit.geometric.n.x, 0.f);
    EXPECT_EQ(hit.geometric.n.y, 0.f);
    EXPECT_EQ(hit.geometric.n.z, -1.f);
    EXPECT_EQ(hit.geometric.dpdu.x, -1.f);
    EXPECT_EQ(hit.geometric.dpdu.y, 0.f);
    EXPECT_EQ(hit.geometric.dpdu.z, 0.f);

    //point left, dir left
    r = Ray(Point3(-5, 0.5, 0.5), Vec3(-1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point left dir above
    r = Ray(Point3(-5, 0.5, 0.5), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point left dir below
    r = Ray(Point3(-5, 0.5, 0.5), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point left dir front
    r = Ray(Point3(-5, 0.5, 0.5), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point left dir back
    r = Ray(Point3(-5, 0.5, 0.5), Vec3(0, -1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point right, dir right
    r = Ray(Point3(5, 0.5, 0.5), Vec3(1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point right, dir above
    r = Ray(Point3(5, 0.5, 0.5), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point right, dir below
    r = Ray(Point3(5, 0.5, 0.5), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point right, dir front
    r = Ray(Point3(5, 0.5, 0.5), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point right, dir back
    r = Ray(Point3(5, 0.5, 0.5), Vec3(0, -1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point back, dir back
    r = Ray(Point3(0.5, 5, 0.5), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point back, dir left
    r = Ray(Point3(0.5, 5, 0.5), Vec3(-1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point back, dir right
    r = Ray(Point3(0.5, 5, 0.5), Vec3(1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point back, dir top
    r = Ray(Point3(0.5, 5, 0.5), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point back, dir bottom
    r = Ray(Point3(0.5, 5, 0.5), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point front, dir front
    r = Ray(Point3(0.5, -5, 0.5), Vec3(0, -1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point front, dir left
    r = Ray(Point3(0.5, -5, 0.5), Vec3(-1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point front, dir right
    r = Ray(Point3(0.5, -5, 0.5), Vec3(1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point front, dir up
    r = Ray(Point3(0.5, -5, 0.5), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point front, dir down
    r = Ray(Point3(0.5, -5, 0.5), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point above, dir up
    r = Ray(Point3(0.5f, 0.5f, 5), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point above, dir left
    r = Ray(Point3(0.5f, 0.5f, 5), Vec3(1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point above, dir right
    r = Ray(Point3(0.5f, 0.5f, 5), Vec3(-1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point above, dir front
    r = Ray(Point3(0.5f, 0.5f, 5), Vec3(0, -1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point above, dir back
    r = Ray(Point3(0.5f, 0.5f, 5), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point below, dir down
    r = Ray(Point3(0.5f, 0.5f, -5), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point below, dir left
    r = Ray(Point3(0.5f, 0.5f, -5), Vec3(1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point below, dir right
    r = Ray(Point3(0.5f, 0.5f, -5), Vec3(-1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point below, dir front
    r = Ray(Point3(0.5f, 0.5f, -5), Vec3(0, -1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //point below, dir back
    r = Ray(Point3(0.5f, 0.5f, -5), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point left, dir left
    r = Ray(Point3(-5, -5, -5), Vec3(-1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point left, dir right
    r = Ray(Point3(-5, -5, -5), Vec3(1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point left dir above
    r = Ray(Point3(-5, -5, -5), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point left dir below
    r = Ray(Point3(-5, -5, -5), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point left dir front
    r = Ray(Point3(-5, -5, -5), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point left dir back
    r = Ray(Point3(-5, -5, -5), Vec3(0, -1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point right, dir right
    r = Ray(Point3(5, 5, 5), Vec3(1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point right, dir left
    r = Ray(Point3(5, 5, 5), Vec3(-1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point right, dir above
    r = Ray(Point3(5, 5, 5), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point right, dir below
    r = Ray(Point3(5, 5, 5), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point right, dir front
    r = Ray(Point3(5, 5, 5), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point right, dir back
    r = Ray(Point3(5, 5, 5), Vec3(0, -1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point back, dir back
    r = Ray(Point3(5, 5, 5), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point back, dir front
    r = Ray(Point3(5, 5, 5), Vec3(0, -1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point back, dir left
    r = Ray(Point3(5, 5, 5), Vec3(-1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point back, dir right
    r = Ray(Point3(5, 5, 5), Vec3(1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point back, dir top
    r = Ray(Point3(5, 5, 5), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point back, dir bottom
    r = Ray(Point3(5, 5, 5), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point front, dir front
    r = Ray(Point3(-5, -5, -5), Vec3(0, -1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point front, dir back
    r = Ray(Point3(-5, -5, -5), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point front, dir left
    r = Ray(Point3(-5, -5, -5), Vec3(-1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point front, dir right
    r = Ray(Point3(-5, -5, -5), Vec3(1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point front, dir up
    r = Ray(Point3(-5, -5, -5), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point front, dir down
    r = Ray(Point3(-5, -5, -5), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point above, dir up
    r = Ray(Point3(5, 5, 5), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point above, dir down
    r = Ray(Point3(5, 5, 5), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point above, dir left
    r = Ray(Point3(5, 5, 5), Vec3(1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point above, dir right
    r = Ray(Point3(5, 5, 5), Vec3(-1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point above, dir front
    r = Ray(Point3(5, 5, 5), Vec3(0, -1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point above, dir back
    r = Ray(Point3(5, 5, 5), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point below, dir down
    r = Ray(Point3(-5, -5, -5), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point below, dir up
    r = Ray(Point3(-5, -5, -5), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point below, dir left
    r = Ray(Point3(-5, -5, -5), Vec3(1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point below, dir right
    r = Ray(Point3(-5, -5, -5), Vec3(-1, 0, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point below, dir front
    r = Ray(Point3(-5, -5, -5), Vec3(0, -1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //miss point below, dir back
    r = Ray(Point3(-5, -5, -5), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);

    //already found closer one from inside
    r = Ray(Point3(0.5f, 0.5f, 0.5f), Vec3(0, -1, 0));
    distance = 0.3f;
    res = box.intersect(&r, &distance, &hit, &mask);
    EXPECT_FALSE(res);
    EXPECT_EQ(distance, 0.3f);
}

SPECTRE_TEST(Box, get_densities_array)
{
    Box b;
    Matrix4 m;
    m.set_scale(Vec3(1, 2, 3));
    float densities[6];
    b.get_densities_array(&m, densities);
    EXPECT_EQ(densities[0], 2.f);
    EXPECT_EQ(densities[1], 4.f);
    EXPECT_EQ(densities[2], 7.f);
    EXPECT_EQ(densities[3], 10.f);
    EXPECT_EQ(densities[4], 16.f);
    EXPECT_EQ(densities[5], 22.f);
    EXPECT_EQ(densities[5], b.surface(&m));
}

SPECTRE_TEST(Box, get_random_point)
{
    Box b;
    Matrix4 m;
    Point3 p;
    Normal n;
    m.set_scale(Vec3(1, 2, 3));
    float densities[6];
    b.get_densities_array(&m, densities);

    //top face //0,2 density interval
    b.sample_point(0.05f, 0.5f, densities, &p, &n);
    EXPECT_GE(p.x, 0.f);
    EXPECT_LE(p.x, 1.f);
    EXPECT_EQ(p.y, 0.5f);
    EXPECT_EQ(p.z, 1.f);
    EXPECT_EQ(n.x, 0.f);
    EXPECT_EQ(n.y, 0.f);
    EXPECT_EQ(n.z, 1.f);

    //bottom face //2,4 density interval
    b.sample_point(0.1f, 0.5f, densities, &p, &n);
    EXPECT_GE(p.x, 0.f);
    EXPECT_LE(p.x, 1.f);
    EXPECT_EQ(p.y, 0.5f);
    EXPECT_EQ(p.z, 0.f);
    EXPECT_EQ(n.x, 0.f);
    EXPECT_EQ(n.y, 0.f);
    EXPECT_EQ(n.z, -1.f);

    //front face //4,7 density interval
    b.sample_point(0.2f, 0.5f, densities, &p, &n);
    EXPECT_GE(p.x, 0.f);
    EXPECT_LE(p.x, 1.f);
    EXPECT_EQ(p.y, 0.f);
    EXPECT_EQ(p.z, 0.5f);
    EXPECT_EQ(n.x, 0.f);
    EXPECT_EQ(n.y, -1.f);
    EXPECT_EQ(n.z, 0.f);

    //back face //7,10 density interval
    b.sample_point(0.35f, 0.5f, densities, &p, &n);
    EXPECT_GE(p.x, 0.f);
    EXPECT_LE(p.x, 1.f);
    EXPECT_EQ(p.y, 1.f);
    EXPECT_EQ(p.z, 0.5f);
    EXPECT_EQ(n.x, 0.f);
    EXPECT_EQ(n.y, 1.f);
    EXPECT_EQ(n.z, 0.f);

    //left face //10,16 density interval
    b.sample_point(0.5f, 0.5f, densities, &p, &n);
    EXPECT_EQ(p.x, 0.f);
    EXPECT_EQ(p.y, 0.5f);
    EXPECT_GE(p.z, 0.f);
    EXPECT_LE(p.z, 1.f);
    EXPECT_EQ(n.x, -1.f);
    EXPECT_EQ(n.y, 0.f);
    EXPECT_EQ(n.z, 0.f);

    //right face //16,22 density interval
    b.sample_point(0.9f, 0.5f, densities, &p, &n);
    EXPECT_EQ(p.x, 1.f);
    EXPECT_EQ(p.y, 0.5f);
    EXPECT_GE(p.z, 0.f);
    EXPECT_LE(p.z, 1.f);
    EXPECT_EQ(n.x, 1.f);
    EXPECT_EQ(n.y, 0.f);
    EXPECT_EQ(n.z, 0.f);
}

SPECTRE_TEST(Box, inherited_methods)
{
    Box b;
    EXPECT_GT(b.get_id(), 0); //depends on the tests order
    EXPECT_EQ(b.get_faces_number(), 6);
}

SPECTRE_TEST_END(Box_tests)
