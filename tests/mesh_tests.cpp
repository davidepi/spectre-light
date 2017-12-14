
#include <gtest/gtest.h>


#include "primitives/mesh.hpp"
#include "utility/utility.hpp"
#include <climits>

//to speedup the max_tris test

TEST(Mesh,add_triangle_points)
{
    Mesh m(1);
    Point3 p0 = Point3(-1,0,0);
    Point3 p1 = Point3(1,0,0);
    Point3 p2 = Point3(0.5,1,0);
    Normal n = Normal(0,0,1);
    Ray r;
    float distance;
    HitPoint hit;
    bool res;

    m.add_triangle(p0, p1, p2, n);

    //perform intersections to assert triangle addition the mesh
    m.finalize();
    r = Ray(Point3(0,-10,1),Vec3(0,1,0));
    distance = FLT_MAX;
    res = m.intersect(&r,&distance,&hit);
    EXPECT_FALSE(res);
    r = Ray(Point3(0,0.5,1),Vec3(0,0,-1));
    distance = FLT_MAX;
    res = m.intersect(&r,&distance,&hit);
    EXPECT_TRUE(res);
}

TEST(Mesh,add_triangle_vertices)
{
    //first triangle (for m and m2)
    Vertex v0;
    Vertex v1;
    Vertex v2;
    v0.p = Point3(-1,0,0);
    v1.p = Point3(1,0,0);
    v2.p = Point3(0.5,1,0);
    v0.n = Normal(0,0,1);
    v1.n = Normal(0,0,1);
    v2.n = Normal(0,0,1);

    //second triangle (for m3)
    Vertex v3;
    Vertex v4;
    Vertex v5;
    v3.p = Point3(-1,0,100);
    v4.p = Point3(1,0,100);
    v5.p = Point3(0.5,1,100);
    v3.n = Normal(0,0,-1);
    v4.n = Normal(0,0,-1);
    v5.n = Normal(0,0,-1);

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
    r = Ray(Point3(0,-10,1),Vec3(0,1,0));
    distance = FLT_MAX;
    res = m3.intersect(&r,&distance,&hit);
    EXPECT_FALSE(res);
    r = Ray(Point3(0,0.5,1),Vec3(0,0,-1));
    distance = FLT_MAX;
    res = m3.intersect(&r,&distance,&hit);
    EXPECT_TRUE(res);
    r = Ray(Point3(0,0.5,1),Vec3(0,0,1));
    distance = FLT_MAX;
    res = m3.intersect(&r,&distance,&hit);
    EXPECT_TRUE(res);

    //no need to realloc
    Mesh m2(1);
    m2.add_triangle(&v0, &v1, &v2);
    m2.finalize();
    r = Ray(Point3(0,-10,1),Vec3(0,1,0));
    distance = FLT_MAX;
    res = m2.intersect(&r,&distance,&hit);
    EXPECT_FALSE(res);
    r = Ray(Point3(0,0.5,1),Vec3(0,0,-1));
    distance = FLT_MAX;
    res = m2.intersect(&r,&distance,&hit);
    EXPECT_TRUE(res);

    //enourmous amount of triangles with realloc, assert no crash
    Mesh m(1);
    for(int i=0;i<_MAX_TRIS_;i++)
        m.add_triangle(&v0, &v1, &v2);
    errors_count[ERROR_INDEX] = 0;
    m.add_triangle(&v0, &v1, &v2);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
    m.finalize(); //otherwise bvh will generate a segfault before destruction
}

TEST(Mesh,resize)
{
    Vertex v0;
    Vertex v1;
    Vertex v2;
    v0.p = Point3(-1,0,0);
    v1.p = Point3(1,0,0);
    v2.p = Point3(0.5,1,0);
    v0.n = Normal(0,0,1);
    v1.n = Normal(0,0,1);
    v2.n = Normal(0,0,1);
    Vertex v3;
    Vertex v4;
    Vertex v5;
    v3.p = Point3(-1,0,100);
    v4.p = Point3(1,0,100);
    v5.p = Point3(0.5,1,100);
    v3.n = Normal(0,0,-1);
    v4.n = Normal(0,0,-1);
    v5.n = Normal(0,0,-1);

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
    r = Ray(Point3(0,-10,1),Vec3(0,1,0));
    distance = FLT_MAX;
    res = m.intersect(&r,&distance,&hit);
    EXPECT_FALSE(res);
    r = Ray(Point3(0,0.5,1),Vec3(0,0,-1));
    distance = FLT_MAX;
    res = m.intersect(&r,&distance,&hit);
    EXPECT_TRUE(res);
    r = Ray(Point3(0,0.5,1),Vec3(0,0,1));
    distance = FLT_MAX;
    res = m.intersect(&r,&distance,&hit);
    EXPECT_TRUE(res);
}

TEST(Mesh,AABB_object_space)
{
    Vertex v0;
    Vertex v1;
    Vertex v2;
    v0.p = Point3(-1,0,0);
    v1.p = Point3(1,0,0);
    v2.p = Point3(0.5,1,0);
    v0.n = Normal(0,0,1);
    v1.n = Normal(0,0,1);
    v2.n = Normal(0,0,1);
    Vertex v3;
    Vertex v4;
    Vertex v5;
    v3.p = Point3(-1,0,100);
    v4.p = Point3(1,0,100);
    v5.p = Point3(0.5,1,100);
    v3.n = Normal(0,0,-1);
    v4.n = Normal(0,0,-1);
    v5.n = Normal(0,0,-1);
    Mesh m(2);
    m.add_triangle(&v0, &v1, &v2);
    m.add_triangle(&v3, &v4, &v5);
    m.finalize();
    AABB box = m.compute_AABB();

    EXPECT_EQ(box.bounds[0].x,-1);
    EXPECT_EQ(box.bounds[0].y,0);
    EXPECT_EQ(box.bounds[0].z,0);
    EXPECT_EQ(box.bounds[1].x,1);
    EXPECT_EQ(box.bounds[1].y,1);
    EXPECT_EQ(box.bounds[1].z,100);
}

