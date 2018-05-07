#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else
#include <gtest/gtest.h>
#endif

#include "primitives/mesh.hpp"
#include "utility/utility.hpp"
#include <climits>

SPECTRE_TEST_INIT(Mesh_tests)

SPECTRE_TEST(Mesh, add_triangle_points)
{
    Mesh m(1);
    Point3 p0 = Point3(-1, 0, 0);
    Point3 p1 = Point3(1, 0, 0);
    Point3 p2 = Point3(0.5, 1, 0);
    Normal n = Normal(0, 0, 1);
    Ray r;
    float distance;
    HitPoint hit;
    bool res;

    m.add_triangle(p0, p1, p2, n);

    //perform intersections to assert triangle addition the mesh
    m.finalize();
    r = Ray(Point3(0, -10, 1), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = m.intersect(&r, &distance, &hit);
    EXPECT_FALSE(res);
    r = Ray(Point3(0, 0.5, 1), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = m.intersect(&r, &distance, &hit);
    EXPECT_TRUE(res);
}

SPECTRE_TEST(Mesh, add_triangle_vertices)
{
    //first triangle (for m and m2)
    Vertex v0;
    Vertex v1;
    Vertex v2;
    v0.p = Point3(-1, 0, 0);
    v1.p = Point3(1, 0, 0);
    v2.p = Point3(0.5, 1, 0);
    v0.n = Normal(0, 0, 1);
    v1.n = Normal(0, 0, 1);
    v2.n = Normal(0, 0, 1);

    //second triangle (for m3)
    Vertex v3;
    Vertex v4;
    Vertex v5;
    v3.p = Point3(-1, 0, 100);
    v4.p = Point3(1, 0, 100);
    v5.p = Point3(0.5, 1, 100);
    v3.n = Normal(0, 0, -1);
    v4.n = Normal(0, 0, -1);
    v5.n = Normal(0, 0, -1);

    //
    Ray r;
    float distance;
    HitPoint hit;
    bool res;

    //realloc
    Mesh m3(1);
    m3.add_triangle(&v0, &v1, &v2);
    m3.add_triangle(&v3, &v4, &v5);
    m3.finalize();
    r = Ray(Point3(0, -10, 1), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = m3.intersect(&r, &distance, &hit);
    EXPECT_FALSE(res);
    r = Ray(Point3(0, 0.5, 1), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = m3.intersect(&r, &distance, &hit);
    EXPECT_TRUE(res);
    r = Ray(Point3(0, 0.5, 1), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = m3.intersect(&r, &distance, &hit);
    EXPECT_TRUE(res);

    //no need to realloc
    Mesh m2(1);
    m2.add_triangle(&v0, &v1, &v2);
    m2.finalize();
    r = Ray(Point3(0, -10, 1), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = m2.intersect(&r, &distance, &hit);
    EXPECT_FALSE(res);
    r = Ray(Point3(0, 0.5, 1), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = m2.intersect(&r, &distance, &hit);
    EXPECT_TRUE(res);

    //enourmous amount of triangles with realloc, assert no crash
    Mesh m(1);
    for(int i = 0; i<_MAX_TRIS_; i++)
        m.add_triangle(&v0, &v1, &v2);
    errors_count[ERROR_INDEX] = 0;
    m.add_triangle(&v0, &v1, &v2);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
    m.finalize(); //otherwise bvh will generate a segfault before destruction
}

SPECTRE_TEST(Mesh, resize)
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
    Vertex v3;
    Vertex v4;
    Vertex v5;
    v3.p = Point3(-1, 0, 100);
    v4.p = Point3(1, 0, 100);
    v5.p = Point3(0.5, 1, 100);
    v3.n = Normal(0, 0, -1);
    v4.n = Normal(0, 0, -1);
    v5.n = Normal(0, 0, -1);

    //can't be succesfully tested since the Triangle* array is private
    //just checking that reallocating the array does not break the triangles
    Mesh m(10);
    m.add_triangle(&v0, &v1, &v2);
    m.add_triangle(&v3, &v4, &v5);
    m.finalize(); //this should reallocate the Triangle* array

    //
    Ray r;
    float distance;
    HitPoint hit;
    bool res;
    r = Ray(Point3(0, -10, 1), Vec3(0, 1, 0));
    distance = FLT_MAX;
    res = m.intersect(&r, &distance, &hit);
    EXPECT_FALSE(res);
    r = Ray(Point3(0, 0.5, 1), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = m.intersect(&r, &distance, &hit);
    EXPECT_TRUE(res);
    r = Ray(Point3(0, 0.5, 1), Vec3(0, 0, 1));
    distance = FLT_MAX;
    res = m.intersect(&r, &distance, &hit);
    EXPECT_TRUE(res);
}

SPECTRE_TEST(Mesh, AABB_object_space)
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
    Vertex v3;
    Vertex v4;
    Vertex v5;
    v3.p = Point3(-1, 0, 100);
    v4.p = Point3(1, 0, 100);
    v5.p = Point3(0.5, 1, 100);
    v3.n = Normal(0, 0, -1);
    v4.n = Normal(0, 0, -1);
    v5.n = Normal(0, 0, -1);
    Mesh m(2);
    m.add_triangle(&v0, &v1, &v2);
    m.add_triangle(&v3, &v4, &v5);
    m.finalize();
    AABB box = m.compute_AABB();

    EXPECT_EQ(box.bounds[0].x, -1.f);
    EXPECT_EQ(box.bounds[0].y, 0.f);
    EXPECT_EQ(box.bounds[0].z, 0.f);
    EXPECT_EQ(box.bounds[1].x, 1.f);
    EXPECT_EQ(box.bounds[1].y, 1.f);
    EXPECT_EQ(box.bounds[1].z, 100.f);
}

SPECTRE_TEST(Mesh, AABB_world_space)
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
    Vertex v3;
    Vertex v4;
    Vertex v5;
    v3.p = Point3(-1, 0, 100);
    v4.p = Point3(1, 0, 100);
    v5.p = Point3(0.5, 1, 100);
    v3.n = Normal(0, 0, -1);
    v4.n = Normal(0, 0, -1);
    v5.n = Normal(0, 0, -1);
    Mesh m(2);
    m.add_triangle(&v0, &v1, &v2);
    m.add_triangle(&v3, &v4, &v5);
    m.finalize();
    Matrix4 trans;
    trans.set_identity();
    AABB box = m.compute_AABB(&trans);

    EXPECT_EQ(box.bounds[0].x, -1.f);
    EXPECT_EQ(box.bounds[0].y, 0.f);
    EXPECT_EQ(box.bounds[0].z, 0.f);
    EXPECT_EQ(box.bounds[1].x, 1.f);
    EXPECT_EQ(box.bounds[1].y, 1.f);
    EXPECT_EQ(box.bounds[1].z, 100.f);

    trans.set_scale(Vec3(15, 5, 1));
    box = m.compute_AABB(&trans);
    EXPECT_EQ(box.bounds[0].x, -15.f);
    EXPECT_EQ(box.bounds[0].y, 0.f);
    EXPECT_EQ(box.bounds[0].z, 0.f);
    EXPECT_EQ(box.bounds[1].x, 15.f);
    EXPECT_EQ(box.bounds[1].y, 5.f);
    EXPECT_EQ(box.bounds[1].z, 100.f);

    trans.set_translation(Vec3(15, 5, -10));
    box = m.compute_AABB(&trans);
    EXPECT_EQ(box.bounds[0].x, 14.f);
    EXPECT_EQ(box.bounds[0].y, 5.f);
    EXPECT_EQ(box.bounds[0].z, -10.f);
    EXPECT_EQ(box.bounds[1].x, 16.f);
    EXPECT_EQ(box.bounds[1].y, 6.f);
    EXPECT_EQ(box.bounds[1].z, 90.f);

    trans.set_rotate_z(ONE_PI/2.f);
    box = m.compute_AABB(&trans);
    EXPECT_NEAR(box.bounds[0].x, -1, 1e-5f);
    EXPECT_NEAR(box.bounds[0].y, -1, 1e-5f);
    EXPECT_EQ(box.bounds[0].z, 0.f);
    EXPECT_TRUE(flt_equal(box.bounds[1].x, 0)); //fuck floats
    EXPECT_NEAR(box.bounds[1].y, 1, 1e-5f);
    EXPECT_EQ(box.bounds[1].z, 100.f);

    errors_count[ERROR_INDEX] = 0;
    box = m.compute_AABB(NULL);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(Mesh, surface_object)
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
    Vertex v3;
    Vertex v4;
    Vertex v5;
    v3.p = Point3(-1, 0, 100);
    v4.p = Point3(1, 0, 100);
    v5.p = Point3(0.5, 1, 100);
    v3.n = Normal(0, 0, -1);
    v4.n = Normal(0, 0, -1);
    v5.n = Normal(0, 0, -1);
    Triangle t1(v0, v1, v2);
    Triangle t2(v3, v4, v5);
    Mesh m(2);
    m.add_triangle(&v0, &v1, &v2);
    m.add_triangle(&v3, &v4, &v5);
    m.finalize();

    EXPECT_EQ(m.surface(), t1.surface()+t1.surface());
}

SPECTRE_TEST(Mesh, surface_world)
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
    Vertex v3;
    Vertex v4;
    Vertex v5;
    v3.p = Point3(-1, 0, 100);
    v4.p = Point3(1, 0, 100);
    v5.p = Point3(0.5, 1, 100);
    v3.n = Normal(0, 0, -1);
    v4.n = Normal(0, 0, -1);
    v5.n = Normal(0, 0, -1);
    Triangle t1(v0, v1, v2);
    Triangle t2(v3, v4, v5);
    Mesh m(2);
    m.add_triangle(&v0, &v1, &v2);
    m.add_triangle(&v3, &v4, &v5);
    m.finalize();
    Matrix4 trans;
    trans.set_identity();
    float non_scaled_surface = m.surface();
    EXPECT_EQ(m.surface(&trans), t1.surface(&trans)+t2.surface(&trans));

    trans.set_scale(Vec3(15, 5, 1));
    EXPECT_EQ(m.surface(&trans), t1.surface(&trans)+t2.surface(&trans));

    trans.set_translation(Vec3(15, 5, -10));
    EXPECT_EQ(m.surface(&trans), t1.surface(&trans)+t2.surface(&trans));
    EXPECT_EQ(m.surface(&trans), non_scaled_surface);

    trans.set_rotate_z(ONE_PI/2.f);
    EXPECT_EQ(m.surface(&trans), t1.surface(&trans)+t2.surface(&trans));
    EXPECT_EQ(m.surface(&trans), non_scaled_surface);
}

SPECTRE_TEST(Mesh, get_faces_number)
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
    Mesh m(_MAX_TRIS_);
    EXPECT_EQ(m.get_faces_number(), 0);
    for(int i = 0; i<_MAX_TRIS_; i++)
    {
        m.add_triangle(&v1, &v2, &v0);
        EXPECT_EQ(m.get_faces_number(), i+1);
    }
    m.finalize();
}

SPECTRE_TEST(Mesh, get_densities_array)
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
    Mesh m(6);
    m.add_triangle(&v1, &v2, &v0);
    m.add_triangle(&v1, &v2, &v0);
    m.add_triangle(&v1, &v2, &v0);
    m.add_triangle(&v1, &v2, &v0);
    m.add_triangle(&v1, &v2, &v0);
    m.add_triangle(&v1, &v2, &v0);
    m.finalize();
    Triangle t1(v0, v1, v2);
    float densities[6];
    Matrix4 trans;
    trans.set_identity();
    float surface = t1.surface();

    //non-scaled
    m.get_densities_array(&trans, densities);
    for(int i = 0; i<6; i++)
        EXPECT_EQ(densities[i], surface*(i+1));

    //scaled
    trans.set_scale(Vec3(15, 5, 1));
    surface = t1.surface(&trans);
    m.get_densities_array(&trans, densities);
    for(int i = 0; i<6; i++)
        EXPECT_EQ(densities[i], surface*(i+1));

    //non uniform triangles are reordered in the bvh and thus are impossible to
    //test (without checking if the density has been incremented by one of the
    //possible areas of the triangles)
}

SPECTRE_TEST(Mesh, sample_point)
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
    Mesh m(9);
    m.add_triangle(&v1, &v2, &v0);
    m.add_triangle(&v1, &v2, &v0);
    m.add_triangle(&v1, &v2, &v0);
    m.add_triangle(&v1, &v2, &v0);
    m.add_triangle(&v1, &v2, &v0);
    m.add_triangle(&v1, &v2, &v0);
    m.add_triangle(&v1, &v2, &v0);
    m.add_triangle(&v1, &v2, &v0);
    m.add_triangle(&v1, &v2, &v0);
    m.finalize();
    Triangle t1(v0, v1, v2);
    float densities[9];
    Matrix4 trans;
    trans.set_identity();
    trans.set_scale(Vec3(15, 5, 1));
    m.get_densities_array(&trans, densities);
    Point3 p;
    Normal n;
    HitPoint hit;

    //first one
    m.sample_point(0.05f, 0.5f, densities, &p, &n);
    Ray r = Ray(Point3(p.x, p.y, p.z+100), Vec3(0, 0, -1));
    float distance = FLT_MAX;
    bool res = m.intersect(&r, &distance, &hit);
    EXPECT_TRUE(res);

    //last one
    m.sample_point(0.95f, 0.5f, densities, &p, &n);
    r = Ray(Point3(p.x, p.y, p.z+100), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = m.intersect(&r, &distance, &hit);
    EXPECT_TRUE(res);

    //6th position (in order to trigger both jumps of the divide et impera)
    m.sample_point(0.7f, 0.5f, densities, &p, &n);
    r = Ray(Point3(p.x, p.y, p.z+100), Vec3(0, 0, -1));
    distance = FLT_MAX;
    res = m.intersect(&r, &distance, &hit);
    EXPECT_TRUE(res);
}

SPECTRE_TEST_END(Mesh)
