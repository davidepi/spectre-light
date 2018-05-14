#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else
#include <gtest/gtest.h>
#endif

#include "geometry/vec3.hpp"
#include "geometry/ray.hpp"
#include "utility/utility.hpp"
#include <climits>

SPECTRE_TEST_INIT(Ray_tests)

SPECTRE_TEST(Ray, default_constructor)
{
    Ray r;
    EXPECT_EQ(r.origin.x, 0.f);
    EXPECT_EQ(r.origin.y, 0.f);
    EXPECT_EQ(r.origin.z, 0.f);
    EXPECT_EQ(r.direction.x, 0.f);
    EXPECT_EQ(r.direction.y, 0.f);
    EXPECT_EQ(r.direction.z, 0.f);
    EXPECT_EQ(r.originX.x, 0.f);
    EXPECT_EQ(r.originX.y, 0.f);
    EXPECT_EQ(r.originX.z, 0.f);
    EXPECT_EQ(r.directionX.x, 0.f);
    EXPECT_EQ(r.directionX.y, 0.f);
    EXPECT_EQ(r.directionX.z, 0.f);
    EXPECT_EQ(r.originY.x, 0.f);
    EXPECT_EQ(r.originY.y, 0.f);
    EXPECT_EQ(r.originY.z, 0.f);
    EXPECT_EQ(r.directionY.x, 0.f);
    EXPECT_EQ(r.directionY.y, 0.f);
    EXPECT_EQ(r.directionY.z, 0.f);
    EXPECT_EQ(r.ricochet, (unsigned char)0);
}

SPECTRE_TEST(Ray, vector_constructor)
{
    Point3 origin(-1.f, 2.4, 5.f);
    Vec3 direction(-8.f, -3.5f, 0.1f);
    Ray r(origin, direction);
    EXPECT_EQ(r.origin.x, origin.x);
    EXPECT_EQ(r.origin.y, origin.y);
    EXPECT_EQ(r.origin.z, origin.z);
    EXPECT_EQ(r.direction.x, direction.x);
    EXPECT_EQ(r.direction.y, direction.y);
    EXPECT_EQ(r.direction.z, direction.z);
    EXPECT_EQ(r.ricochet, (unsigned char)0);
}

SPECTRE_TEST(Ray, component_constructor)
{
    Point3 origin(-1.f, 2.4, 5.f);
    Vec3 direction(-8.f, -3.5f, 0.1f);
    Ray r(origin.x, origin.y, origin.z, direction.x, direction.y, direction.z);
    EXPECT_EQ(r.origin.x, origin.x);
    EXPECT_EQ(r.origin.y, origin.y);
    EXPECT_EQ(r.origin.z, origin.z);
    EXPECT_EQ(r.direction.x, direction.x);
    EXPECT_EQ(r.direction.y, direction.y);
    EXPECT_EQ(r.direction.z, direction.z);
    EXPECT_EQ(r.ricochet, (unsigned char)0);
}

SPECTRE_TEST(Ray, apply)
{
    Point3 o(0, 0, 0);
    Vec3 d(0.408248f, 0.408248f, 0.816497f);
    float distance = 2.5;
    Ray r(o, d);
    Point3 point = r.apply(distance);
    EXPECT_NEAR(point.x, 1.02062f, 1e-5f);
    EXPECT_NEAR(point.y, 1.02062f, 1e-5f);
    EXPECT_NEAR(point.z, 2.0412425f, 1e-5f);
}

SPECTRE_TEST(Ray, RayProperties_constructor)
{
    //dir x+
    Ray r(Point3(0, 0, 0), Vec3(2, 0, 0));
    RayProperties rp(r);
    EXPECT_EQ(rp.inverseX, 0.5f);
    EXPECT_EQ(rp.inverseY, INFINITY);
    EXPECT_EQ(rp.inverseZ, INFINITY);
    EXPECT_FALSE(rp.isXInvNeg);
    EXPECT_FALSE(rp.isYInvNeg);
    EXPECT_FALSE(rp.isZInvNeg);

    //dir x-
    r = Ray(Point3(0, 0, 0), Vec3(-2, 0, 0));
    rp = RayProperties(r);
    EXPECT_EQ(rp.inverseX, -0.5f);
    EXPECT_EQ(rp.inverseY, INFINITY);
    EXPECT_EQ(rp.inverseZ, INFINITY);
    EXPECT_TRUE(rp.isXInvNeg);
    EXPECT_FALSE(rp.isYInvNeg);
    EXPECT_FALSE(rp.isZInvNeg);

    //dir y+
    r = Ray(Point3(0, 0, 0), Vec3(0, 2, 0));
    rp = RayProperties(r);
    EXPECT_EQ(rp.inverseX, INFINITY);
    EXPECT_EQ(rp.inverseY, 0.5f);
    EXPECT_EQ(rp.inverseZ, INFINITY);
    EXPECT_FALSE(rp.isXInvNeg);
    EXPECT_FALSE(rp.isYInvNeg);
    EXPECT_FALSE(rp.isZInvNeg);

    //dir y-
    r = Ray(Point3(0, 0, 0), Vec3(0, -2, 0));
    rp = RayProperties(r);
    EXPECT_EQ(rp.inverseX, INFINITY);
    EXPECT_EQ(rp.inverseY, -0.5f);
    EXPECT_EQ(rp.inverseZ, INFINITY);
    EXPECT_FALSE(rp.isXInvNeg);
    EXPECT_TRUE(rp.isYInvNeg);
    EXPECT_FALSE(rp.isZInvNeg);

    //dir z+
    r = Ray(Point3(0, 0, 0), Vec3(0, 0, 2));
    rp = RayProperties(r);
    EXPECT_EQ(rp.inverseX, INFINITY);
    EXPECT_EQ(rp.inverseY, INFINITY);
    EXPECT_EQ(rp.inverseZ, 0.5f);
    EXPECT_FALSE(rp.isXInvNeg);
    EXPECT_FALSE(rp.isYInvNeg);
    EXPECT_FALSE(rp.isZInvNeg);

    //dir y-
    r = Ray(Point3(0, 0, 0), Vec3(0, 0, -2));
    rp = RayProperties(r);
    EXPECT_EQ(rp.inverseX, INFINITY);
    EXPECT_EQ(rp.inverseY, INFINITY);
    EXPECT_EQ(rp.inverseZ, -0.5f);
    EXPECT_FALSE(rp.isXInvNeg);
    EXPECT_FALSE(rp.isYInvNeg);
    EXPECT_TRUE(rp.isZInvNeg);
}

SPECTRE_TEST(Ray,constructor_no_differentials)
{
    Point3 origin(-1.f, 2.4, 5.f);
    Vec3 direction(-8.f, -3.5f, 0.1f);
    Ray r(origin,direction);
    EXPECT_EQ(r.origin.x, origin.x);
    EXPECT_EQ(r.origin.y, origin.y);
    EXPECT_EQ(r.origin.z, origin.z);
    EXPECT_EQ(r.direction.x, direction.x);
    EXPECT_EQ(r.direction.y, direction.y);
    EXPECT_EQ(r.direction.z, direction.z);
    EXPECT_EQ(r.originX.x, origin.x);
    EXPECT_EQ(r.originX.y, origin.y);
    EXPECT_EQ(r.originX.z, origin.z);
    EXPECT_EQ(r.directionX.x, direction.x);
    EXPECT_EQ(r.directionX.y, direction.y);
    EXPECT_EQ(r.directionX.z, direction.z);
    EXPECT_EQ(r.originY.x, origin.x);
    EXPECT_EQ(r.originY.y, origin.y);
    EXPECT_EQ(r.originY.z, origin.z);
    EXPECT_EQ(r.directionY.x, direction.x);
    EXPECT_EQ(r.directionY.y, direction.y);
    EXPECT_EQ(r.directionY.z, direction.z);
    EXPECT_EQ(r.ricochet, (unsigned char)0);
}

SPECTRE_TEST(Ray, constructor)
{
    Point3 origin(-1.f, 2.4, 5.f);
    Point3 originX(-1.1f, 2.5, 5.1f);
    Point3 originY(-1.2f, 2.6, 5.2f);
    Vec3 direction(-8.f, -3.5f, 0.1f);
    Vec3 directionX(-8.1f, -3.6f, 0.2f);
    Vec3 directionY(-8.2f, -3.7f, 0.3f);
    Ray r(origin,direction,originX,directionX,originY,directionY);
    EXPECT_EQ(r.origin.x, origin.x);
    EXPECT_EQ(r.origin.y, origin.y);
    EXPECT_EQ(r.origin.z, origin.z);
    EXPECT_EQ(r.direction.x, direction.x);
    EXPECT_EQ(r.direction.y, direction.y);
    EXPECT_EQ(r.direction.z, direction.z);
    EXPECT_EQ(r.originX.x, originX.x);
    EXPECT_EQ(r.originX.y, originX.y);
    EXPECT_EQ(r.originX.z, originX.z);
    EXPECT_EQ(r.directionX.x, directionX.x);
    EXPECT_EQ(r.directionX.y, directionX.y);
    EXPECT_EQ(r.directionX.z, directionX.z);
    EXPECT_EQ(r.originY.x, originY.x);
    EXPECT_EQ(r.originY.y, originY.y);
    EXPECT_EQ(r.originY.z, originY.z);
    EXPECT_EQ(r.directionY.x, directionY.x);
    EXPECT_EQ(r.directionY.y, directionY.y);
    EXPECT_EQ(r.directionY.z, directionY.z);
    EXPECT_EQ(r.ricochet, (unsigned char)0);
}

SPECTRE_TEST_END(Ray_tests)
