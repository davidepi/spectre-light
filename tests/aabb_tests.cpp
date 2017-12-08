
#include <gtest/gtest.h>


#include "geometry/AABB.hpp"
#include "utility/utility.hpp"
#include <climits>
#define EPSILON 1E-5f

TEST(AABB,default_constructor)
{
    AABB box;
    EXPECT_TRUE(std::isinf(box.bounds[0].x));
    EXPECT_TRUE(std::isinf(box.bounds[0].y));
    EXPECT_TRUE(std::isinf(box.bounds[0].z));
    EXPECT_TRUE(std::isinf(box.bounds[1].x));
    EXPECT_TRUE(std::isinf(box.bounds[1].y));
    EXPECT_TRUE(std::isinf(box.bounds[1].z));
}

TEST(AABB,single_point_constructor)
{
    Point3 p(76.9907,-31.02559,64.63251);
    AABB box(p);
    EXPECT_EQ(box.bounds[0].x,p.x);
    EXPECT_EQ(box.bounds[0].y,p.y);
    EXPECT_EQ(box.bounds[0].z,p.z);
    EXPECT_EQ(box.bounds[1].x,p.x);
    EXPECT_EQ(box.bounds[1].y,p.y);
    EXPECT_EQ(box.bounds[1].z,p.z);
}

TEST(AABB,double_point_constructor_reference)
{
    Point3 pmin(-60.06347,33.59238,-37.23738);
    Point3 pmax(-21.18293,50.33405,9.33384);
    AABB box(pmin,pmax);
    EXPECT_EQ(box.bounds[0].x,pmin.x);
    EXPECT_EQ(box.bounds[0].y,pmin.y);
    EXPECT_EQ(box.bounds[0].z,pmin.z);
    EXPECT_EQ(box.bounds[1].x,pmax.x);
    EXPECT_EQ(box.bounds[1].y,pmax.y);
    EXPECT_EQ(box.bounds[1].z,pmax.z);

    //assert that the min-max are not respected, otherwise I have to change
    //the doc
    pmin = Point3(-60.06347,33.59238,-37.23738);
    pmax = Point3(-21.18293,-50.33405,9.33384);
    box = AABB(&pmin,&pmax);
    EXPECT_EQ(box.bounds[0].x,pmin.x);
    EXPECT_EQ(box.bounds[0].y,pmin.y);
    EXPECT_EQ(box.bounds[0].z,pmin.z);
    EXPECT_EQ(box.bounds[1].x,pmax.x);
    EXPECT_EQ(box.bounds[1].y,pmax.y);
    EXPECT_EQ(box.bounds[1].z,pmax.z);
}

TEST(AABB,double_point_constructor_pointer)
{
    Point3 pmin(-60.06347,33.59238,-37.23738);
    Point3 pmax(-21.18293,50.33405,9.33384);
    AABB box(pmin,pmax);
    EXPECT_EQ(box.bounds[0].x,pmin.x);
    EXPECT_EQ(box.bounds[0].y,pmin.y);
    EXPECT_EQ(box.bounds[0].z,pmin.z);
    EXPECT_EQ(box.bounds[1].x,pmax.x);
    EXPECT_EQ(box.bounds[1].y,pmax.y);
    EXPECT_EQ(box.bounds[1].z,pmax.z);

    //assert that the min-max are not respected, otherwise I have to change
    //the doc
    pmin = Point3(-60.06347,33.59238,-37.23738);
    pmax = Point3(-21.18293,-50.33405,9.33384);
    box = AABB(&pmin,&pmax);
    EXPECT_EQ(box.bounds[0].x,pmin.x);
    EXPECT_EQ(box.bounds[0].y,pmin.y);
    EXPECT_EQ(box.bounds[0].z,pmin.z);
    EXPECT_EQ(box.bounds[1].x,pmax.x);
    EXPECT_EQ(box.bounds[1].y,pmax.y);
    EXPECT_EQ(box.bounds[1].z,pmax.z);
}

TEST(AABB,expand)
{
    //expand positive
    Point3 p;
    AABB box(p);
    box.expand(50.5f);
    EXPECT_FLOAT_EQ(box.bounds[0].x,-50.5f);
    EXPECT_FLOAT_EQ(box.bounds[0].y,-50.5f);
    EXPECT_FLOAT_EQ(box.bounds[0].z,-50.5f);
    EXPECT_FLOAT_EQ(box.bounds[1].x,50.5f);
    EXPECT_FLOAT_EQ(box.bounds[1].y,50.5f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,50.5f);

    //expand 0
    box.expand(0.f);
    EXPECT_FLOAT_EQ(box.bounds[0].x,-50.5f);
    EXPECT_FLOAT_EQ(box.bounds[0].y,-50.5f);
    EXPECT_FLOAT_EQ(box.bounds[0].z,-50.5f);
    EXPECT_FLOAT_EQ(box.bounds[1].x,50.5f);
    EXPECT_FLOAT_EQ(box.bounds[1].y,50.5f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,50.5f);

    //expand negative
    box.expand(-0.5f);
    EXPECT_FLOAT_EQ(box.bounds[0].x,-50.f);
    EXPECT_FLOAT_EQ(box.bounds[0].y,-50.f);
    EXPECT_FLOAT_EQ(box.bounds[0].z,-50.f);
    EXPECT_FLOAT_EQ(box.bounds[1].x,50.f);
    EXPECT_FLOAT_EQ(box.bounds[1].y,50.f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,50.f);

    //expand degenerate
    box.expand(-200.f);
    EXPECT_FLOAT_EQ(box.bounds[0].x,150.f);
    EXPECT_FLOAT_EQ(box.bounds[0].y,150.f);
    EXPECT_FLOAT_EQ(box.bounds[0].z,150.f);
    EXPECT_FLOAT_EQ(box.bounds[1].x,-150.f);
    EXPECT_FLOAT_EQ(box.bounds[1].y,-150.f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,-150.f);
}

TEST(AABB,engulf_pointer)
{
    Point3 p;
    AABB box(p);
    Point3 addme(10,-15,20);
    box.engulf(&addme);
    EXPECT_FLOAT_EQ(box.bounds[0].x,0.f);
    EXPECT_FLOAT_EQ(box.bounds[0].y,-15.f);
    EXPECT_FLOAT_EQ(box.bounds[0].z,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].x,10.f);
    EXPECT_FLOAT_EQ(box.bounds[1].y,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,20.f);

    //already inside
    addme = Point3(2,-3,15);
    box.engulf(&addme);
    EXPECT_FLOAT_EQ(box.bounds[0].x,0.f);
    EXPECT_FLOAT_EQ(box.bounds[0].y,-15.f);
    EXPECT_FLOAT_EQ(box.bounds[0].z,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].x,10.f);
    EXPECT_FLOAT_EQ(box.bounds[1].y,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,20.f);

    //inf
    addme = Point3(INFINITY,0,0);
    EXPECT_FLOAT_EQ(box.bounds[0].x,0.f);
    EXPECT_FLOAT_EQ(box.bounds[0].y,-15.f);
    EXPECT_FLOAT_EQ(box.bounds[0].z,0.f);
    EXPECT_GT(box.bounds[1].x,1E200);
    EXPECT_FLOAT_EQ(box.bounds[1].y,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,20.f);
}

