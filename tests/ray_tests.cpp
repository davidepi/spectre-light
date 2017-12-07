
#include <gtest/gtest.h>


#include "geometry/vec3.hpp"
#include "geometry/ray.hpp"
#include "utility/utility.hpp"
#include <climits>
#define EPSILON 1E-5f

TEST(Ray,default_constructor)
{
    Ray r;
    EXPECT_EQ(r.origin.x,0.f);
    EXPECT_EQ(r.origin.y,0.f);
    EXPECT_EQ(r.origin.z,0.f);
    EXPECT_EQ(r.direction.x,0.f);
    EXPECT_EQ(r.direction.y,0.f);
    EXPECT_EQ(r.direction.z,0.f);
    EXPECT_EQ(r.ricochet,0.f);
}

TEST(Ray,vector_constructor)
{
    Point3 origin(-1.f,2.4,5.f);
    Vec3 direction(-8.f,-3.5f,0.1f);
    Ray r(origin,direction);
    EXPECT_EQ(r.origin.x,origin.x);
    EXPECT_EQ(r.origin.y,origin.y);
    EXPECT_EQ(r.origin.z,origin.z);
    EXPECT_EQ(r.direction.x,direction.x);
    EXPECT_EQ(r.direction.y,direction.y);
    EXPECT_EQ(r.direction.z,direction.z);
    EXPECT_EQ(r.ricochet,0.f);
}

TEST(Ray,component_constructor)
{
    Point3 origin(-1.f,2.4,5.f);
    Vec3 direction(-8.f,-3.5f,0.1f);
    Ray r(origin.x,origin.y,origin.z,direction.x,direction.y,direction.z);
    EXPECT_EQ(r.origin.x,origin.x);
    EXPECT_EQ(r.origin.y,origin.y);
    EXPECT_EQ(r.origin.z,origin.z);
    EXPECT_EQ(r.direction.x,direction.x);
    EXPECT_EQ(r.direction.y,direction.y);
    EXPECT_EQ(r.direction.z,direction.z);
    EXPECT_EQ(r.ricochet,0.f);
}

TEST(Ray,apply)
{
    Point3 o(0,0,0);
    Vec3 d(0.408248f,0.408248f,0.816497f);
    float distance = 2.5;
    Ray r(o,d);
    Point3 point = r.apply(distance);
    EXPECT_FLOAT_EQ(point.x, 1.02062f);
    EXPECT_FLOAT_EQ(point.y, 1.02062f);
    EXPECT_FLOAT_EQ(point.z, 2.0412425f);
}

