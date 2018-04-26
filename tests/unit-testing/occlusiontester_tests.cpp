#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#else

#include <gtest/gtest.h>

#endif

SPECTRE_TEST_INIT(OcclusionTester_tests)

#include "primitives/sphere.hpp"
#include "materials/lambertian.hpp"
#include "utility/occlusion_tester.hpp"
#include "utility/utility.hpp"
#include <climits>

SPECTRE_TEST(OcclusionTester, is_occluded)
{
    Sphere* sphere = new Sphere;
    Scene scene;
    scene.inherit_shape(sphere);
    Matrix4 m;
    m.set_identity();
    scene.inherit_asset(new Asset(sphere, m, 1));
    m.set_translation(Vec3(-5.f, 0.f, 0.f));
    scene.inherit_asset(new Asset(sphere, m, 1));
    m.set_translation(Vec3(5.f, 0.f, 0.f));
    scene.inherit_asset(new Asset(sphere, m, 1));
    scene.k.buildTree();
    OcclusionTester tester(&scene);

    //not occluded, first bounce, not cached
    Ray r(Point3(3.f, 0.f, 0.f), Vec3(-1.f, 0.f, 0.f));
    HitPoint hit;
    EXPECT_FALSE(tester.is_occluded(&r, 2.f));

    //occluded, first bounce, not cached
    r = Ray(Point3(13.f, 0.f, 0.f), Vec3(-1.f, 0.f, 0.f));
    EXPECT_TRUE(tester.is_occluded(&r, 12.f));

    //occluded, first bounce, cached hit
    r = Ray(Point3(14.f, 0.f, 0.f), Vec3(-1.f, 0.f, 0.f));
    EXPECT_TRUE(tester.is_occluded(&r, 13.f));

    //occluded, first bounce, cached miss
    r = Ray(Point3(-14.f, 0.f, 0.f), Vec3(1.f, 0.f, 0.f));
    EXPECT_TRUE(tester.is_occluded(&r, 13.f));

    //occluded, second bounce, not cached
    r.ricochet++;
    EXPECT_TRUE(tester.is_occluded(&r, 13.f));

    //not intersecting
    r = Ray(Point3(14.f, 0.f, 0.f), Vec3(0.f, 0.f, 1.f));
    EXPECT_FALSE(tester.is_occluded(&r, 2.f));
}

SPECTRE_TEST_END(OcclusionTester_tests)
