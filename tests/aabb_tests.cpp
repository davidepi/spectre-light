
#include <gtest/gtest.h>


#include "geometry/AABB.hpp"
#include "utility/utility.hpp"
#include <climits>
#include <cmath>
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

TEST(AABB,engulf_Point3_pointer)
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
    box.engulf(&addme);
    EXPECT_FLOAT_EQ(box.bounds[0].x,0.f);
    EXPECT_FLOAT_EQ(box.bounds[0].y,-15.f);
    EXPECT_FLOAT_EQ(box.bounds[0].z,0.f);
    EXPECT_EQ(box.bounds[1].x,INFINITY);
    EXPECT_FLOAT_EQ(box.bounds[1].y,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,20.f);
}

TEST(AABB,engulf_Point3_reference)
{
    Point3 p;
    AABB box(p);
    Point3 addme(10,-15,20);
    box.engulf(addme);
    EXPECT_FLOAT_EQ(box.bounds[0].x,0.f);
    EXPECT_FLOAT_EQ(box.bounds[0].y,-15.f);
    EXPECT_FLOAT_EQ(box.bounds[0].z,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].x,10.f);
    EXPECT_FLOAT_EQ(box.bounds[1].y,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,20.f);

    //already inside
    addme = Point3(2,-3,15);
    box.engulf(addme);
    EXPECT_FLOAT_EQ(box.bounds[0].x,0.f);
    EXPECT_FLOAT_EQ(box.bounds[0].y,-15.f);
    EXPECT_FLOAT_EQ(box.bounds[0].z,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].x,10.f);
    EXPECT_FLOAT_EQ(box.bounds[1].y,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,20.f);

    //inf
    addme = Point3(INFINITY,-INFINITY,0);
    box.engulf(addme);
    EXPECT_FLOAT_EQ(box.bounds[0].x,0.f);
    EXPECT_EQ(box.bounds[0].y,-INFINITY);
    EXPECT_FLOAT_EQ(box.bounds[0].z,0.f);
    EXPECT_EQ(box.bounds[1].x,INFINITY);
    EXPECT_FLOAT_EQ(box.bounds[1].y,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,20.f);
}

TEST(AABB,engulf_aabb_pointer)
{
    Point3 p;
    AABB box(p);

    //default
    AABB def;
    box.engulf(&def);
    EXPECT_EQ(box.bounds[0].x, 0.f);
    EXPECT_EQ(box.bounds[0].y, 0.f);
    EXPECT_EQ(box.bounds[0].z, 0.f);
    EXPECT_EQ(box.bounds[1].x, 0.f);
    EXPECT_EQ(box.bounds[1].y, 0.f);
    EXPECT_EQ(box.bounds[1].z, 0.f);

    //outside
    AABB addme(Point3(-59.28244,-3.01509,-47.61078),
               Point3(67.30925,53.29163,82.07844));
    box.engulf(&addme);
    EXPECT_FLOAT_EQ(box.bounds[0].x,addme.bounds[0].x);
    EXPECT_FLOAT_EQ(box.bounds[0].y,addme.bounds[0].y);
    EXPECT_FLOAT_EQ(box.bounds[0].z,addme.bounds[0].z);
    EXPECT_FLOAT_EQ(box.bounds[1].x,addme.bounds[1].x);
    EXPECT_FLOAT_EQ(box.bounds[1].y,addme.bounds[1].y);
    EXPECT_FLOAT_EQ(box.bounds[1].z,addme.bounds[1].z);

    //already inside
    AABB addme2(Point3(-9.30374,8.49896,-35.41399),
               Point3(58.56126,18.59649,37.76507));
    box.engulf(&addme2);
    EXPECT_FLOAT_EQ(box.bounds[0].x,addme.bounds[0].x);
    EXPECT_FLOAT_EQ(box.bounds[0].y,addme.bounds[0].y);
    EXPECT_FLOAT_EQ(box.bounds[0].z,addme.bounds[0].z);
    EXPECT_FLOAT_EQ(box.bounds[1].x,addme.bounds[1].x);
    EXPECT_FLOAT_EQ(box.bounds[1].y,addme.bounds[1].y);
    EXPECT_FLOAT_EQ(box.bounds[1].z,addme.bounds[1].z);

    //inf
    AABB addme3(Point3(-138.73003,-73.22298,INFINITY),
                Point3(-INFINITY,INFINITY,53.70019));
    box.engulf(&addme3);
    EXPECT_FLOAT_EQ(box.bounds[0].x,addme3.bounds[0].x);
    EXPECT_FLOAT_EQ(box.bounds[0].y,addme3.bounds[0].y);
    EXPECT_FLOAT_EQ(box.bounds[0].z,addme.bounds[0].z);
    EXPECT_FLOAT_EQ(box.bounds[1].x,addme.bounds[1].x);
    EXPECT_EQ(box.bounds[1].y, INFINITY);
    EXPECT_FLOAT_EQ(box.bounds[1].z,addme.bounds[1].z);
}

TEST(AABB,engulf_aabb_reference)
{
    Point3 p;
    AABB box(p);

    //default
    AABB def;
    box.engulf(def);
    EXPECT_EQ(box.bounds[0].x, 0.f);
    EXPECT_EQ(box.bounds[0].y, 0.f);
    EXPECT_EQ(box.bounds[0].z, 0.f);
    EXPECT_EQ(box.bounds[1].x, 0.f);
    EXPECT_EQ(box.bounds[1].y, 0.f);
    EXPECT_EQ(box.bounds[1].z, 0.f);

    //outside
    AABB addme(Point3(-59.28244,-3.01509,-47.61078),
               Point3(67.30925,53.29163,82.07844));
    box.engulf(addme);
    EXPECT_FLOAT_EQ(box.bounds[0].x,addme.bounds[0].x);
    EXPECT_FLOAT_EQ(box.bounds[0].y,addme.bounds[0].y);
    EXPECT_FLOAT_EQ(box.bounds[0].z,addme.bounds[0].z);
    EXPECT_FLOAT_EQ(box.bounds[1].x,addme.bounds[1].x);
    EXPECT_FLOAT_EQ(box.bounds[1].y,addme.bounds[1].y);
    EXPECT_FLOAT_EQ(box.bounds[1].z,addme.bounds[1].z);

    //already inside
    AABB addme2(Point3(-9.30374,8.49896,-35.41399),
                Point3(58.56126,18.59649,37.76507));
    box.engulf(addme2);
    EXPECT_FLOAT_EQ(box.bounds[0].x,addme.bounds[0].x);
    EXPECT_FLOAT_EQ(box.bounds[0].y,addme.bounds[0].y);
    EXPECT_FLOAT_EQ(box.bounds[0].z,addme.bounds[0].z);
    EXPECT_FLOAT_EQ(box.bounds[1].x,addme.bounds[1].x);
    EXPECT_FLOAT_EQ(box.bounds[1].y,addme.bounds[1].y);
    EXPECT_FLOAT_EQ(box.bounds[1].z,addme.bounds[1].z);

    //inf
    AABB addme3(Point3(-138.73003,-73.22298,INFINITY),
                Point3(-INFINITY,INFINITY,53.70019));
    box.engulf(addme3);
    EXPECT_FLOAT_EQ(box.bounds[0].x,addme3.bounds[0].x);
    EXPECT_FLOAT_EQ(box.bounds[0].y,addme3.bounds[0].y);
    EXPECT_FLOAT_EQ(box.bounds[0].z,addme.bounds[0].z);
    EXPECT_FLOAT_EQ(box.bounds[1].x,addme.bounds[1].x);
    EXPECT_EQ(box.bounds[1].y, INFINITY);
    EXPECT_FLOAT_EQ(box.bounds[1].z,addme.bounds[1].z);
}

TEST(AABB,inside)
{
    AABB box(Point3(-10,-10,-10),Point3(10,10,10));

    //point inside
    Point3 ins(-5,-5,-5);
    EXPECT_TRUE(box.inside(&ins));

    //point inside border
    Point3 border(10,10,10);
    EXPECT_TRUE(box.inside(&border));

    //point outside only x
    Point3 outx(-10.000001f,-5,-5);
    EXPECT_FALSE(box.inside(&outx));

    //point outside only y
    Point3 outy(-5,-10.000001f,-5);
    EXPECT_FALSE(box.inside(&outy));

    //point outside only z
    Point3 outz(-5,-5,-10.000001f);
    EXPECT_FALSE(box.inside(&outz));

    //point outside every point
    Point3 outall(11,11,11);
    EXPECT_FALSE(box.inside(&outall));

    //point outside infinite
    Point3 inf(INFINITY,0,0);
    Point3 minf(0,-INFINITY,0);
    Point3 inf2(0,0,INFINITY);
    EXPECT_FALSE(box.inside(&inf));
    EXPECT_FALSE(box.inside(&minf));
    EXPECT_FALSE(box.inside(&inf2));
}

TEST(AABB,surface)
{
    AABB box;

    //zero length
    Point3 p(-0.53123,-24.29362,84.26433);
    box = AABB(p);
    EXPECT_EQ(box.surface(), 0.f);

    //normal length
    box = AABB(Point3(-1,-1,-1),
               Point3(3,4,5));
    EXPECT_EQ(box.surface(),148);

    //infinite length
    box = AABB(Point3(-1,-1,-1),
               Point3(1,1,INFINITY));
    EXPECT_EQ(box.surface(), INFINITY);
    box = AABB(Point3(-INFINITY,-INFINITY,-INFINITY),
               Point3(INFINITY,INFINITY,INFINITY));
    EXPECT_EQ(box.surface(), INFINITY);
}

TEST(AABB,volume)
{
    AABB box;

    //zero length
    Point3 p(-0.53123,-24.29362,84.26433);
    box = AABB(p);
    EXPECT_EQ(box.volume(), 0.f);

    //normal length
    box = AABB(Point3(-1,-1,-1),
               Point3(3,4,5));
    EXPECT_EQ(box.volume(),120);

    //infinite length
    box = AABB(Point3(-1,-1,-1),
               Point3(1,1,INFINITY));
    EXPECT_EQ(box.volume(), INFINITY);
    box = AABB(Point3(-INFINITY,-INFINITY,-INFINITY),
               Point3(INFINITY,INFINITY,INFINITY));
    EXPECT_EQ(box.volume(), INFINITY);
}

TEST(AABB,longest_axis)
{
    AABB box;

    //zero length -> return x
    Point3 p(-0.53123,-24.29362,84.26433);
    box = AABB(p);
    EXPECT_EQ(box.longest_axis(), 0);

    //longest x - non inf
    box = AABB(Point3(-85.77731,5.98468,-10.75332),
               Point3(74.13619,99.79995,37.72758));
    EXPECT_EQ(box.longest_axis(),0);

    //longest y - non inf
    box = AABB(Point3(-27.68684,-73.58186,-69.54105),
               Point3(65.46841,95.43746,-51.04507));
    EXPECT_EQ(box.longest_axis(),1);

    //longest z - non inf
    box = AABB(Point3(17.90233,-6.71415,-88.93419),
               Point3(76.75507,50.73106,95.81359));
    EXPECT_EQ(box.longest_axis(),2);

    //longest x - inf
    box = AABB(Point3(-INFINITY,5.98468,-10.75332),
               Point3(74.13619,99.79995,37.72758));
    EXPECT_EQ(box.longest_axis(),0);

    //longest y - inf
    box = AABB(Point3(-27.68684,-73.58186,-69.54105),
               Point3(65.46841,INFINITY,-51.04507));
    EXPECT_EQ(box.longest_axis(),1);

    //longest z - inf
    box = AABB(Point3(17.90233,-46.71415,-INFINITY),
               Point3(76.75507,90.73106,95.81359));
    EXPECT_EQ(box.longest_axis(),2);

    //everything infinite
    box = AABB(Point3(-INFINITY,-INFINITY,-INFINITY),
               Point3(INFINITY,INFINITY,INFINITY));
    EXPECT_EQ(box.longest_axis(), 0);
}

TEST(AABB,center)
{
    AABB box;
    Point3 center;

    //zero length
    Point3 p(-0.53123,-24.29362,84.26433);
    box = AABB(p);
    center = box.center();
    EXPECT_FLOAT_EQ(center.x,p.x);
    EXPECT_FLOAT_EQ(center.y,p.y);
    EXPECT_FLOAT_EQ(center.z,p.z);

    //normal box
    box = AABB(Point3(-1,-1,-1),
               Point3(1,1,1));
    center = box.center();
    EXPECT_FLOAT_EQ(center.x,0.f);
    EXPECT_FLOAT_EQ(center.y,0.f);
    EXPECT_FLOAT_EQ(center.z,0.f);

    //1 inf val box
    box = AABB(Point3(-1,-INFINITY,-1),
               Point3(1,-1,1));
    center = box.center();
    EXPECT_FLOAT_EQ(center.x,0.f);
    EXPECT_EQ(center.y,-INFINITY);
    EXPECT_FLOAT_EQ(center.z,0.f);
    box = AABB(Point3(-1,-1,-1),
               Point3(1,1,INFINITY));
    center = box.center();
    EXPECT_FLOAT_EQ(center.x,0.f);
    EXPECT_FLOAT_EQ(center.y,0.f);
    EXPECT_EQ(center.z,INFINITY);

    //infinite box
    box = AABB(Point3(-INFINITY,-INFINITY,-INFINITY),
               Point3(INFINITY,INFINITY,INFINITY));
    center=box.center();
    EXPECT_TRUE(std::isnan(center.x));
    EXPECT_TRUE(std::isnan(center.y));
    EXPECT_TRUE(std::isnan(center.z));
}

TEST(AABB,sum_point)
{
    Point3 p;
    AABB box(p);
    Point3 addme(10,-15,20);
    AABB res = box + addme;
    EXPECT_FLOAT_EQ(res.bounds[0].x,0.f);
    EXPECT_FLOAT_EQ(res.bounds[0].y,-15.f);
    EXPECT_FLOAT_EQ(res.bounds[0].z,0.f);
    EXPECT_FLOAT_EQ(res.bounds[1].x,10.f);
    EXPECT_FLOAT_EQ(res.bounds[1].y,0.f);
    EXPECT_FLOAT_EQ(res.bounds[1].z,20.f);

    //already inside
    addme = Point3(2,-3,15);
    res = res + addme;
    EXPECT_FLOAT_EQ(res.bounds[0].x,0.f);
    EXPECT_FLOAT_EQ(res.bounds[0].y,-15.f);
    EXPECT_FLOAT_EQ(res.bounds[0].z,0.f);
    EXPECT_FLOAT_EQ(res.bounds[1].x,10.f);
    EXPECT_FLOAT_EQ(res.bounds[1].y,0.f);
    EXPECT_FLOAT_EQ(res.bounds[1].z,20.f);

    //inf
    addme = Point3(INFINITY,-INFINITY,0);
    res = res + addme;
    EXPECT_FLOAT_EQ(res.bounds[0].x,0.f);
    EXPECT_EQ(res.bounds[0].y,-INFINITY);
    EXPECT_FLOAT_EQ(res.bounds[0].z,0.f);
    EXPECT_EQ(res.bounds[1].x,INFINITY);
    EXPECT_FLOAT_EQ(res.bounds[1].y,0.f);
    EXPECT_FLOAT_EQ(res.bounds[1].z,20.f);
}

TEST(AABB,sum_point_this)
{
    Point3 p;
    AABB box(p);
    Point3 addme(10,-15,20);
    box += addme;
    EXPECT_FLOAT_EQ(box.bounds[0].x,0.f);
    EXPECT_FLOAT_EQ(box.bounds[0].y,-15.f);
    EXPECT_FLOAT_EQ(box.bounds[0].z,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].x,10.f);
    EXPECT_FLOAT_EQ(box.bounds[1].y,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,20.f);

    //already inside
    addme = Point3(2,-3,15);
    box += addme;
    EXPECT_FLOAT_EQ(box.bounds[0].x,0.f);
    EXPECT_FLOAT_EQ(box.bounds[0].y,-15.f);
    EXPECT_FLOAT_EQ(box.bounds[0].z,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].x,10.f);
    EXPECT_FLOAT_EQ(box.bounds[1].y,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,20.f);

    //inf
    addme = Point3(INFINITY,-INFINITY,0);
    box += addme;
    EXPECT_FLOAT_EQ(box.bounds[0].x,0.f);
    EXPECT_EQ(box.bounds[0].y,-INFINITY);
    EXPECT_FLOAT_EQ(box.bounds[0].z,0.f);
    EXPECT_EQ(box.bounds[1].x,INFINITY);
    EXPECT_FLOAT_EQ(box.bounds[1].y,0.f);
    EXPECT_FLOAT_EQ(box.bounds[1].z,20.f);
}

TEST(AABB,sum_aabb)
{
    Point3 p;
    AABB box(p);
    AABB res;

    //default
    AABB def;
    res = box + def;
    EXPECT_EQ(res.bounds[0].x, 0.f);
    EXPECT_EQ(res.bounds[0].y, 0.f);
    EXPECT_EQ(res.bounds[0].z, 0.f);
    EXPECT_EQ(res.bounds[1].x, 0.f);
    EXPECT_EQ(res.bounds[1].y, 0.f);
    EXPECT_EQ(res.bounds[1].z, 0.f);

    //outside
    AABB addme(Point3(-59.28244,-3.01509,-47.61078),
               Point3(67.30925,53.29163,82.07844));
    res = res + addme;
    EXPECT_FLOAT_EQ(res.bounds[0].x,addme.bounds[0].x);
    EXPECT_FLOAT_EQ(res.bounds[0].y,addme.bounds[0].y);
    EXPECT_FLOAT_EQ(res.bounds[0].z,addme.bounds[0].z);
    EXPECT_FLOAT_EQ(res.bounds[1].x,addme.bounds[1].x);
    EXPECT_FLOAT_EQ(res.bounds[1].y,addme.bounds[1].y);
    EXPECT_FLOAT_EQ(res.bounds[1].z,addme.bounds[1].z);

    //already inside
    AABB addme2(Point3(-9.30374,8.49896,-35.41399),
                Point3(58.56126,18.59649,37.76507));
    res = res + addme2;
    EXPECT_FLOAT_EQ(res.bounds[0].x,addme.bounds[0].x);
    EXPECT_FLOAT_EQ(res.bounds[0].y,addme.bounds[0].y);
    EXPECT_FLOAT_EQ(res.bounds[0].z,addme.bounds[0].z);
    EXPECT_FLOAT_EQ(res.bounds[1].x,addme.bounds[1].x);
    EXPECT_FLOAT_EQ(res.bounds[1].y,addme.bounds[1].y);
    EXPECT_FLOAT_EQ(res.bounds[1].z,addme.bounds[1].z);

    //inf
    AABB addme3(Point3(-138.73003,-73.22298,INFINITY),
                Point3(-INFINITY,INFINITY,53.70019));
    res = res + addme3;
    EXPECT_FLOAT_EQ(res.bounds[0].x,addme3.bounds[0].x);
    EXPECT_FLOAT_EQ(res.bounds[0].y,addme3.bounds[0].y);
    EXPECT_FLOAT_EQ(res.bounds[0].z,addme.bounds[0].z);
    EXPECT_FLOAT_EQ(res.bounds[1].x,addme.bounds[1].x);
    EXPECT_EQ(res.bounds[1].y, INFINITY);
    EXPECT_FLOAT_EQ(res.bounds[1].z,addme.bounds[1].z);
}

TEST(AABB,sum_aabb_this)
{
    Point3 p;
    AABB box(p);

    //default
    AABB def;
    box += def;
    EXPECT_EQ(box.bounds[0].x, 0.f);
    EXPECT_EQ(box.bounds[0].y, 0.f);
    EXPECT_EQ(box.bounds[0].z, 0.f);
    EXPECT_EQ(box.bounds[1].x, 0.f);
    EXPECT_EQ(box.bounds[1].y, 0.f);
    EXPECT_EQ(box.bounds[1].z, 0.f);

    //outside
    AABB addme(Point3(-59.28244,-3.01509,-47.61078),
               Point3(67.30925,53.29163,82.07844));
    box += addme;
    EXPECT_FLOAT_EQ(box.bounds[0].x,addme.bounds[0].x);
    EXPECT_FLOAT_EQ(box.bounds[0].y,addme.bounds[0].y);
    EXPECT_FLOAT_EQ(box.bounds[0].z,addme.bounds[0].z);
    EXPECT_FLOAT_EQ(box.bounds[1].x,addme.bounds[1].x);
    EXPECT_FLOAT_EQ(box.bounds[1].y,addme.bounds[1].y);
    EXPECT_FLOAT_EQ(box.bounds[1].z,addme.bounds[1].z);

    //already inside
    AABB addme2(Point3(-9.30374,8.49896,-35.41399),
                Point3(58.56126,18.59649,37.76507));
    box += addme2;
    EXPECT_FLOAT_EQ(box.bounds[0].x,addme.bounds[0].x);
    EXPECT_FLOAT_EQ(box.bounds[0].y,addme.bounds[0].y);
    EXPECT_FLOAT_EQ(box.bounds[0].z,addme.bounds[0].z);
    EXPECT_FLOAT_EQ(box.bounds[1].x,addme.bounds[1].x);
    EXPECT_FLOAT_EQ(box.bounds[1].y,addme.bounds[1].y);
    EXPECT_FLOAT_EQ(box.bounds[1].z,addme.bounds[1].z);

    //inf
    AABB addme3(Point3(-138.73003,-73.22298,INFINITY),
                Point3(-INFINITY,INFINITY,53.70019));
    box += addme3;
    EXPECT_FLOAT_EQ(box.bounds[0].x,addme3.bounds[0].x);
    EXPECT_FLOAT_EQ(box.bounds[0].y,addme3.bounds[0].y);
    EXPECT_FLOAT_EQ(box.bounds[0].z,addme.bounds[0].z);
    EXPECT_FLOAT_EQ(box.bounds[1].x,addme.bounds[1].x);
    EXPECT_EQ(box.bounds[1].y, INFINITY);
    EXPECT_FLOAT_EQ(box.bounds[1].z,addme.bounds[1].z);
}

TEST(AABB,intersect)
{
    //hit diagonally, dir positive
    AABB box(Point3(1,1,1),Point3(2,2,2));
    Ray ray(Point3(0,0,0),Vec3(1,1,1));
    float near,far;
    EXPECT_FALSE(box.inside(&(ray.origin)));
    bool res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit diagonally, dir negative
    ray = Ray(Point3(3,3,3),Vec3(-1,-1,-1));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit x, point left
    ray = Ray(Point3(0,1.5,1.5),Vec3(1,0,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit x, point right
    ray = Ray(Point3(3,1.5,1.5),Vec3(-1,0,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit y, point front
    ray = Ray(Point3(1.5,0,1.5),Vec3(0,1,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit y, point back
    ray = Ray(Point3(1.5,3,1.5),Vec3(0,-1,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit z, point above
    ray = Ray(Point3(1.5,1.5,0),Vec3(0,0,1));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit z, point below
    ray = Ray(Point3(1.5,1.5,3),Vec3(0,0,-1));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit in line with the aabb, but wrong direction of the ray (x-)
    ray = Ray(Point3(0,1.5,1.5),Vec3(-1,0,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_LT(far, 0);

    //hit in line with the aabb, but wrong direction of the ray (x+)
    ray = Ray(Point3(3,1.5,1.5),Vec3(1,0,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_LT(far, 0);

    //hit in line with the aabb, but wrong direction of the ray (y-)
    ray = Ray(Point3(1.5,0,1.5),Vec3(0,-1,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_LT(far, 0);

    //hit in line with the aabb, but wrong direction of the ray (y+)
    ray = Ray(Point3(1.5,3,1.5),Vec3(0,1,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_LT(far, 0);

    //hit in line with the aabb, but wrong direction of the ray (z-)
    ray = Ray(Point3(1.5,1.5,0),Vec3(0,0,-1));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_LT(far, 0);

    //hit in line with the aabb, but wrong direction of the ray (z+)
    ray = Ray(Point3(1.5,1.5,3),Vec3(0,0,1));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_LT(far, 0);

    //complete miss, point back, x+ direction
    ray = Ray(Point3(1.5,3,1.5),Vec3(1,0,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point back, x- direction
    ray = Ray(Point3(1.5,3,1.5),Vec3(-1,0,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point below, x+ direction
    ray = Ray(Point3(1.5,1.5,3),Vec3(1,0,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point below, x- direction
    ray = Ray(Point3(1.5,1.5,3),Vec3(-1,0,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point front, x+ direction
    ray = Ray(Point3(1.5,0,1.5),Vec3(1,0,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point front, x- direction
    ray = Ray(Point3(1.5,0,1.5),Vec3(-1,0,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point above, x+ direction
    ray = Ray(Point3(1.5,1.5,3),Vec3(1,0,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point above, x- direction
    ray = Ray(Point3(1.5,1.5,3),Vec3(-1,0,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point left, y+ direction
    ray = Ray(Point3(0,1.5,1.5),Vec3(0,1,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point left, y- direction
    ray = Ray(Point3(0,1.5,1.5),Vec3(0,-1,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point below, y+ direction
    ray = Ray(Point3(1.5,1.5,0),Vec3(0,1,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point below, y- direction
    ray = Ray(Point3(1.5,1.5,0),Vec3(0,-1,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point right, y+ direction
    ray = Ray(Point3(3,1.5,1.5),Vec3(0,1,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point right, y- direction
    ray = Ray(Point3(3,1.5,1.5),Vec3(0,-1,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point above, y+ direction
    ray = Ray(Point3(1.5,1.5,3),Vec3(0,1,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point above, y- direction
    ray = Ray(Point3(1.5,1.5,3),Vec3(0,-1,0));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point left, z+ direction
    ray = Ray(Point3(0,1.5,1.5),Vec3(0,0,1));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point left, z- direction
    ray = Ray(Point3(0,1.5,1.5),Vec3(0,0,-1));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point back, z+ direction
    ray = Ray(Point3(1.5,3,1.5),Vec3(0,0,1));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point back, z- direction
    ray = Ray(Point3(1.5,3,1.5),Vec3(0,0,-1));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point right, z+ direction
    ray = Ray(Point3(3,1.5,1.5),Vec3(0,0,1));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point right, z- direction
    ray = Ray(Point3(3,1.5,1.5),Vec3(0,0,-1));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point front, z direction
    ray = Ray(Point3(1.5,0,1.5),Vec3(0,0,1));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point front, z- direction
    ray = Ray(Point3(1.5,0,1.5),Vec3(0,0,-1));
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,false);

    //start inside, x+
    ray = Ray(Point3(1.5,1.5,1.5),Vec3(1,0,0));
    EXPECT_TRUE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_GT(far, 0);

    //start inside, x-
    ray = Ray(Point3(1.5,1.5,1.5),Vec3(-1,0,0));
    EXPECT_TRUE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_GT(far, 0);

    //start inside, y+
    ray = Ray(Point3(1.5,1.5,1.5),Vec3(0,1,0));
    EXPECT_TRUE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_GT(far, 0);

    //start inside, y-
    ray = Ray(Point3(1.5,1.5,1.5),Vec3(0,-1,0));
    EXPECT_TRUE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_GT(far, 0);

    //start inside, z+
    ray = Ray(Point3(1.5,1.5,1.5),Vec3(0,0,1));
    EXPECT_TRUE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_GT(far, 0);

    //start inside, z-
    ray = Ray(Point3(1.5,1.5,1.5),Vec3(0,0,-1));
    EXPECT_TRUE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_GT(far, 0);
}

TEST(AABB,intersect_fast)
{
    //hit diagonally, dir positive
    AABB box(Point3(1,1,1),Point3(2,2,2));
    Ray ray(Point3(0,0,0),Vec3(1,1,1));
    RayProperties rp = RayProperties(ray);
    float near,far;
    EXPECT_FALSE(box.inside(&(ray.origin)));
    bool res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit diagonally, dir negative
    ray = Ray(Point3(3,3,3),Vec3(-1,-1,-1));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit x, point left
    ray = Ray(Point3(0,1.5,1.5),Vec3(1,0,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit x, point right
    ray = Ray(Point3(3,1.5,1.5),Vec3(-1,0,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit y, point front
    ray = Ray(Point3(1.5,0,1.5),Vec3(0,1,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit y, point back
    ray = Ray(Point3(1.5,3,1.5),Vec3(0,-1,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit z, point above
    ray = Ray(Point3(1.5,1.5,0),Vec3(0,0,1));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit z, point below
    ray = Ray(Point3(1.5,1.5,3),Vec3(0,0,-1));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_GT(near, 0);
    EXPECT_GT(far, 0);

    //hit in line with the aabb, but wrong direction of the ray (x-)
    ray = Ray(Point3(0,1.5,1.5),Vec3(-1,0,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_LT(far, 0);

    //hit in line with the aabb, but wrong direction of the ray (x+)
    ray = Ray(Point3(3,1.5,1.5),Vec3(1,0,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_LT(far, 0);

    //hit in line with the aabb, but wrong direction of the ray (y-)
    ray = Ray(Point3(1.5,0,1.5),Vec3(0,-1,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_LT(far, 0);

    //hit in line with the aabb, but wrong direction of the ray (y+)
    ray = Ray(Point3(1.5,3,1.5),Vec3(0,1,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_LT(far, 0);

    //hit in line with the aabb, but wrong direction of the ray (z-)
    ray = Ray(Point3(1.5,1.5,0),Vec3(0,0,-1));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_LT(far, 0);

    //hit in line with the aabb, but wrong direction of the ray (z+)
    ray = Ray(Point3(1.5,1.5,3),Vec3(0,0,1));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_LT(far, 0);

    //complete miss, point back, x+ direction
    ray = Ray(Point3(1.5,3,1.5),Vec3(1,0,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point front, x- direction
    ray = Ray(Point3(1.5,3,1.5),Vec3(-1,0,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point above, x+ direction
    ray = Ray(Point3(1.5,1.5,3),Vec3(1,0,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point above, x- direction
    ray = Ray(Point3(1.5,1.5,3),Vec3(-1,0,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point back, x+ direction
    ray = Ray(Point3(1.5,0,1.5),Vec3(1,0,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point back, x- direction
    ray = Ray(Point3(1.5,0,1.5),Vec3(-1,0,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point below, x+ direction
    ray = Ray(Point3(1.5,1.5,3),Vec3(1,0,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point below, x- direction
    ray = Ray(Point3(1.5,1.5,3),Vec3(-1,0,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point left, y+ direction
    ray = Ray(Point3(0,1.5,1.5),Vec3(0,1,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point left, y- direction
    ray = Ray(Point3(0,1.5,1.5),Vec3(0,-1,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point below, y+ direction
    ray = Ray(Point3(1.5,1.5,0),Vec3(0,1,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point below, y- direction
    ray = Ray(Point3(1.5,1.5,0),Vec3(0,-1,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point right, y+ direction
    ray = Ray(Point3(3,1.5,1.5),Vec3(0,1,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point right, y- direction
    ray = Ray(Point3(3,1.5,1.5),Vec3(0,-1,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point above, y+ direction
    ray = Ray(Point3(1.5,1.5,3),Vec3(0,1,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point above, y- direction
    ray = Ray(Point3(1.5,1.5,3),Vec3(0,-1,0));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point left, z+ direction
    ray = Ray(Point3(0,1.5,1.5),Vec3(0,0,1));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point left, z- direction
    ray = Ray(Point3(0,1.5,1.5),Vec3(0,0,-1));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point back, z+ direction
    ray = Ray(Point3(1.5,3,1.5),Vec3(0,0,1));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point back, z- direction
    ray = Ray(Point3(1.5,3,1.5),Vec3(0,0,-1));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point right, z+ direction
    ray = Ray(Point3(3,1.5,1.5),Vec3(0,0,1));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point right, z- direction
    ray = Ray(Point3(3,1.5,1.5),Vec3(0,0,-1));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point front, z direction
    ray = Ray(Point3(1.5,0,1.5),Vec3(0,0,1));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //complete miss, point front, z- direction
    ray = Ray(Point3(1.5,0,1.5),Vec3(0,0,-1));
    rp = RayProperties(ray);
    EXPECT_FALSE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,false);

    //start inside, x+
    ray = Ray(Point3(1.5,1.5,1.5),Vec3(1,0,0));
    rp = RayProperties(ray);
    EXPECT_TRUE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_GT(far, 0);

    //start inside, x-
    ray = Ray(Point3(1.5,1.5,1.5),Vec3(-1,0,0));
    rp = RayProperties(ray);
    EXPECT_TRUE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_GT(far, 0);

    //start inside, y+
    ray = Ray(Point3(1.5,1.5,1.5),Vec3(0,1,0));
    rp = RayProperties(ray);
    EXPECT_TRUE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_GT(far, 0);

    //start inside, y-
    ray = Ray(Point3(1.5,1.5,1.5),Vec3(0,-1,0));
    rp = RayProperties(ray);
    EXPECT_TRUE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_GT(far, 0);

    //start inside, z+
    ray = Ray(Point3(1.5,1.5,1.5),Vec3(0,0,1));
    rp = RayProperties(ray);
    EXPECT_TRUE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_GT(far, 0);

    //start inside, z-
    ray = Ray(Point3(1.5,1.5,1.5),Vec3(0,0,-1));
    rp = RayProperties(ray);
    EXPECT_TRUE(box.inside(&(ray.origin)));
    res = box.intersect(&ray,&rp,&near,&far);
    EXPECT_EQ(res,true);
    EXPECT_LT(near, 0);
    EXPECT_GT(far, 0);
}

TEST(AABB,less)
{
    AABB small(Point3(-0.53123,-0.29362,-0.26433),
               Point3(0.14842,0.6715,0.59818));
    AABB big(Point3(-1,-1,-1),Point3(3,4,5));
    EXPECT_TRUE(small<big);
    EXPECT_FALSE(big<small);
    EXPECT_FALSE(small<small);
}

TEST(AABB,greater)
{
    AABB small(Point3(-0.53123,-0.29362,-0.26433),
               Point3(0.14842,0.6715,0.59818));
    AABB big(Point3(-1,-1,-1),Point3(3,4,5));
    EXPECT_TRUE(big>small);
    EXPECT_FALSE(small>big);
    EXPECT_FALSE(big>big);
}

TEST(AABB,less_equal)
{
    AABB small(Point3(-0.53123,-0.29362,-0.26433),
               Point3(0.14842,0.6715,0.59818));
    AABB big(Point3(-1,-1,-1),Point3(3,4,5));
    EXPECT_TRUE(small<big);
    EXPECT_FALSE(big<small);
    EXPECT_TRUE(small<=small);
    EXPECT_FALSE(big<=small);
}

TEST(AABB,greater_equal)
{
    AABB small(Point3(-0.53123,-0.29362,-0.26433),
               Point3(0.14842,0.6715,0.59818));
    AABB big(Point3(-1,-1,-1),Point3(3,4,5));
    EXPECT_TRUE(big>small);
    EXPECT_FALSE(small>big);
    EXPECT_TRUE(big>=big);
    EXPECT_FALSE(small>=big);
}

TEST(AABB,equal)
{
    AABB small(Point3(-1,0,-2),
               Point3(1,1,1));
    AABB small_again(Point3(2,2,2),
                     Point3(5,4,3));
    AABB big(Point3(-100,0,-2),
               Point3(1,1,100));
    EXPECT_TRUE(small==small);
    EXPECT_TRUE(small==small_again);
    EXPECT_FALSE(small==big);
}

TEST(AABB,not_equal)
{
    AABB small(Point3(-1,0,-2),
               Point3(1,1,1));
    AABB small_again(Point3(2,2,2),
                     Point3(5,4,3));
    AABB big(Point3(-100,0,-2),
             Point3(1,1,100));
    EXPECT_FALSE(small!=small);
    EXPECT_FALSE(small!=small_again);
    EXPECT_TRUE(small!=big);
}

