
#include <gtest/gtest.h>


#include "primitives/sphere.hpp"
#include "materials/lambertian.hpp"
#include "utility/occlusion_tester.hpp"
#include "utility/utility.hpp"
#include <climits>

TEST(OcclusionTester,is_occluded)
{
    Sphere* sphere = new Sphere;
    Scene scene;
    unsigned int id = scene.inherit_shape(sphere);
    Matrix4 m;
    m.set_identity();
    scene.add_asset(id, m);
    m.set_translation(Vec3(-5,0,0));
    scene.add_asset(id, m);
    m.set_translation(Vec3(5,0,0));
    scene.add_asset(id, m);
    scene.k.buildTree();
    OcclusionTester tester(&scene);

    //not occluded, first bounce, not cached
    Ray r(Point3(3,0,0),Vec3(-1,0,0));
    HitPoint hit;
    EXPECT_FALSE(tester.is_occluded(&r, 2.f));

    //occluded, first bounce, not cached
    r = Ray(Point3(13,0,0),Vec3(-1,0,0));
    EXPECT_TRUE(tester.is_occluded(&r, 12.f));

    //occluded, first bounce, cached
    r = Ray(Point3(14,0,0),Vec3(-1,0,0));
    EXPECT_TRUE(tester.is_occluded(&r, 13.f));

    //occluded, second bounce, not cached
    r.ricochet++;
    EXPECT_TRUE(tester.is_occluded(&r, 13.f));

    //not intersecting
    r = Ray(Point3(14,0,0),Vec3(0,0,1));
    EXPECT_FALSE(tester.is_occluded(&r, 2.f));
}

