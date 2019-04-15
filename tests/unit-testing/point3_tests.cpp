#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else
#include <gtest/gtest.h>
#endif

#include "geometry/point3.hpp"
#include "utility/utility.hpp"
#include <climits>
#include <cmath>

SPECTRE_TEST_INIT(Point3_tests)

SPECTRE_TEST(Point3, empty_constructor)
{
    Point3 p;
    EXPECT_EQ(p.x, 0.f);
    EXPECT_EQ(p.y, 0.f);
    EXPECT_EQ(p.z, 0.f);
}

SPECTRE_TEST(Point3, same_value_constructor)
{
    float val = 1.0f;
    Point3 p(val);
    EXPECT_EQ(p.x, val);
    EXPECT_EQ(p.y, val);
    EXPECT_EQ(p.z, val);

    //NaNs, infinity is not an error
    errors_count[ERROR_INDEX] = 0;
    float nan = NAN;
    float infty = INFINITY;
    Point3 p1(nan);
    Point3 p2(infty);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(Point3, components_constructor)
{
    Point3 p(1.0f, -1.0f, 0.0f);
    EXPECT_EQ(p.x, 1.f);
    EXPECT_EQ(p.y, -1.f);
    EXPECT_EQ(p.z, 0.f);

    //NaNs - Infinity is not an error for points
    errors_count[ERROR_INDEX] = 0;
    Point3 p1(NAN, 1.f, 1.f);
    Point3 p2(1.f, NAN, 1.f);
    Point3 p3(1.f, 1.f, NAN);
    Point3 p4(INFINITY, 1.f, 1.f);
    Point3 p5(1.f, INFINITY, 1.f);
    Point3 p6(1.f, 1.f, INFINITY);
    EXPECT_EQ(errors_count[ERROR_INDEX], 3);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(Point3, distance_noinline)
{
    Point3 p0(1, 2, 3);
    Point3 p1(4, 5, 6);
    float distance = p0.distance(p1);
    EXPECT_NEAR(distance, 5.1961524227f, 1e-5f);
}

SPECTRE_TEST(Point3, max_noinline)
{
    Point3 sample(0.5, 1.5, -3.5);
    Point3 value;
    Point3 compare;

    //x is max
    value = sample;
    compare = Point3(0.2f, 0.f, 0.f);
    value.max(compare);
    EXPECT_EQ(value.x, sample.x);
    //x is not max
    value = sample;
    compare = Point3(1.0, 0.f, 0.f);
    value.max(compare);
    EXPECT_EQ(value.x, compare.x);

    //y is max
    value = sample;
    compare = Point3(0.f, 1.f, 0.f);
    value.max(compare);
    EXPECT_EQ(value.y, sample.y);
    //y is not max
    value = sample;
    compare = Point3(0.f, 10.f, 0.f);
    value.max(compare);
    EXPECT_EQ(value.y, compare.y);

    //z is max
    value = sample;
    compare = Point3(0.f, 0.f, -5.f);
    value.max(compare);
    EXPECT_EQ(value.z, sample.z);
    //z is not max
    value = sample;
    compare = Point3(0.f, 0.f, 0.f);
    value.max(compare);
    EXPECT_EQ(value.z, compare.z);
}

SPECTRE_TEST(Point3, min_noinline)
{
    Point3 sample(0.5, 1.5, -3.5);
    Point3 value;
    Point3 compare;

    //x is max
    value = sample;
    compare = Point3(0.2f, 0.f, 0.f);
    value.min(compare);
    EXPECT_EQ(value.x, compare.x);
    //x is not max
    value = sample;
    compare = Point3(1.0, 0.f, 0.f);
    value.min(compare);
    EXPECT_EQ(value.x, sample.x);

    //y is max
    value = sample;
    compare = Point3(0.f, 1.f, 0.f);
    value.min(compare);
    EXPECT_EQ(value.y, compare.y);
    //y is not max
    value = sample;
    compare = Point3(0.f, 10.f, 0.f);
    value.min(compare);
    EXPECT_EQ(value.y, sample.y);

    //z is max
    value = sample;
    compare = Point3(0.f, 0.f, -5.f);
    value.min(compare);
    EXPECT_EQ(value.z, compare.z);
    //z is not max
    value = sample;
    compare = Point3(0.f, 0.f, 0.f);
    value.min(compare);
    EXPECT_EQ(value.z, sample.z);
}

SPECTRE_TEST(Point3, sum_vector)
{
    Point3 v1(1, 2, 3);
    Vec3 v2(4, 5.5, -3);

    Point3 res = v1+v2;
    EXPECT_NEAR(res.x, 5.f, 1e-5f);
    EXPECT_NEAR(res.y, 7.5f, 1e-5f);
    EXPECT_NEAR(res.z, 0.f, 1e-5f);
}

SPECTRE_TEST(Point3, sum_vector_this)
{
    Point3 v1(1, 2, 3);
    Vec3 v2(4, 5.5, -3);

    v1 += v2;
    EXPECT_NEAR(v1.x, 5.f, 1e-5f);
    EXPECT_NEAR(v1.y, 7.5f, 1e-5f);
    EXPECT_NEAR(v1.z, 0.f, 1e-5f);
}

SPECTRE_TEST(Point3, sub_point)
{
    Point3 v1(1, 2, 3);
    Point3 v2(4, 5.5, -3);
    Vec3 res = v2-v1;
    EXPECT_NEAR(res.x, 3.f, 1e-5f);
    EXPECT_NEAR(res.y, 3.5f, 1e-5f);
    EXPECT_NEAR(res.z, -6.f, 1e-5f);
}

SPECTRE_TEST(Point3, sub_vector)
{
    Vec3 v1(1, 2, 3);
    Point3 v2(4, 5.5, -3);
    Point3 res = v2-v1;
    EXPECT_NEAR(res.x, 3.f, 1e-5f);
    EXPECT_NEAR(res.y, 3.5f, 1e-5f);
    EXPECT_NEAR(res.z, -6.f, 1e-5f);
}

SPECTRE_TEST(Point3, sub_vector_this)
{
    Point3 v1(1, 2, 3);
    Vec3 v2(4, 5.5, -3);
    v1 -= v2;
    EXPECT_NEAR(v1.x, -3.f, 1e-5f);
    EXPECT_NEAR(v1.y, -3.5f, 1e-5f);
    EXPECT_NEAR(v1.z, 6.f, 1e-5f);
}

SPECTRE_TEST(Point3, equal)
{
    Point3 v1;
    Point3 v2;

    //[X VALUE] [Y VALUE] [Z VALUE]
    //[F] [F] [F]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, 47.50334f, 30.28772f);
    bool res = v1 == v2;
    EXPECT_EQ(res, false);

    //[T] [F] [F]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(35.93915f, 47.50334f, 30.28772f);
    res = v1 == v2;
    EXPECT_EQ(res, false);

    //[F] [T] [F]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, -78.07117f, 30.28772f);
    res = v1 == v2;
    EXPECT_EQ(res, false);

    //[F] [F] [T]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, 47.50334f, -87.74657f);
    res = v1 == v2;
    EXPECT_EQ(res, false);

    //[T] [T] [F]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(35.93915f, -78.07117f, 30.28772f);
    res = v1 == v2;
    EXPECT_EQ(res, false);

    //[T] [F] [T]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(35.93915f, 47.50334f, -87.74657f);
    res = v1 == v2;
    EXPECT_EQ(res, false);

    //[F] [T] [T]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, -78.07117f, -87.74657f);
    res = v1 == v2;
    EXPECT_EQ(res, false);

    //[T] [T] [T]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(35.93915f, -78.07117f, -87.74657f);
    res = v1 == v2;
    EXPECT_EQ(res, true);

    //Inf which is accepted in Point3 but breaks comparison
    //beacause inf||bool -> true and nan||bool -> true
    errors_count[ERROR_INDEX] = 0;
    v1 = Point3(INFINITY, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, -78.07117f, -87.74657f);
    res = v1 == v2;
    v1 = Point3(35.93915f, INFINITY, -87.74657f);
    v2 = Point3(-8.50624f, -78.07117f, -87.74657f);
    res = v1 == v2;
    v1 = Point3(35.93915f, -78.07117f, INFINITY);
    v2 = Point3(-8.50624f, -78.07117f, -87.74657f);
    res = v1 == v2;
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(INFINITY, -78.07117f, -87.74657f);
    res = v1 == v2;
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, INFINITY, -87.74657f);
    res = v1 == v2;
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, -78.07117f, INFINITY);
    res = v1 == v2;
    EXPECT_EQ(errors_count[ERROR_INDEX], 6);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(Point3, not_equal)
{
    Point3 v1;
    Point3 v2;

    //[X VALUE] [Y VALUE] [Z VALUE]
    //[F] [F] [F]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, 47.50334f, 30.28772f);
    bool res = v1 != v2;
    EXPECT_EQ(res, true);

    //[T] [F] [F]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(35.93915f, 47.50334f, 30.28772f);
    res = v1 != v2;
    EXPECT_EQ(res, true);

    //[F] [T] [F]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, -78.07117f, 30.28772f);
    res = v1 != v2;
    EXPECT_EQ(res, true);

    //[F] [F] [T]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, 47.50334f, -87.74657f);
    res = v1 != v2;
    EXPECT_EQ(res, true);

    //[T] [T] [F]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(35.93915f, -78.07117f, 30.28772f);
    res = v1 != v2;
    EXPECT_EQ(res, true);

    //[T] [F] [T]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(35.93915f, 47.50334f, -87.74657f);
    res = v1 != v2;
    EXPECT_EQ(res, true);

    //[F] [T] [T]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, -78.07117f, -87.74657f);
    res = v1 != v2;
    EXPECT_EQ(res, true);

    //[T] [T] [T]
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(35.93915f, -78.07117f, -87.74657f);
    res = v1 != v2;
    EXPECT_EQ(res, false);

    //Inf which is accepted in Point3 but breaks comparison
    //beacause inf||bool -> true and nan||bool -> true
    errors_count[ERROR_INDEX] = 0;
    v1 = Point3(INFINITY, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, -78.07117f, -87.74657f);
    res = v1 != v2;
    v1 = Point3(35.93915f, INFINITY, -87.74657f);
    v2 = Point3(-8.50624f, -78.07117f, -87.74657f);
    res = v1 != v2;
    v1 = Point3(35.93915f, -78.07117f, INFINITY);
    v2 = Point3(-8.50624f, -78.07117f, -87.74657f);
    res = v1 != v2;
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(INFINITY, -78.07117f, -87.74657f);
    res = v1 != v2;
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, INFINITY, -87.74657f);
    res = v1 != v2;
    v1 = Point3(35.93915f, -78.07117f, -87.74657f);
    v2 = Point3(-8.50624f, -78.07117f, INFINITY);
    res = v1 != v2;
    EXPECT_EQ(errors_count[ERROR_INDEX], 6);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(Point3, access)
{
    Point3 v(-72.74395f, -6.04488f, -51.11608f);
    EXPECT_EQ(v.x, v[0]);
    EXPECT_EQ(v.y, v[1]);
    EXPECT_EQ(v.z, v[2]);
}

SPECTRE_TEST(Point3, const_access)
{
    const Point3 v2(-72.74395f, -6.04488f, -51.11608f);
    EXPECT_EQ(v2.x, v2[0]);
    EXPECT_EQ(v2.y, v2[1]);
    EXPECT_EQ(v2.z, v2[2]);
}

SPECTRE_TEST(Point3, serialization)
{
    Point3 p(128.7f, 435.4f, -34.f);
    Chunk serialized;
    p.serialize(&serialized);

    Point3 deserialized(&serialized);
    EXPECT_EQ(p.x, deserialized.x);
    EXPECT_EQ(p.y, deserialized.y);
    EXPECT_EQ(p.z, deserialized.z);
}

SPECTRE_TEST(Point3, distance_inline)
{
    Point3 p0(1, 2, 3);
    Point3 p1(4, 5, 6);
    float dist = distance(p0, p1);
    EXPECT_NEAR(dist, 5.1961524227f, 1e-5f);
}

SPECTRE_TEST(Point3, max_inline)
{
    Point3 sample(0.5, 1.5, -3.5);
    Point3 value;
    Point3 compare;

    //x is max
    value = sample;
    compare = Point3(0.2f, 0.f, 0.f);
    value = max(value, compare);
    EXPECT_EQ(value.x, sample.x);
    //x is not max
    value = sample;
    compare = Point3(1.0, 0.f, 0.f);
    value = max(value, compare);
    EXPECT_EQ(value.x, compare.x);

    //y is max
    value = sample;
    compare = Point3(0.f, 1.f, 0.f);
    value.max(compare);
    EXPECT_EQ(value.y, sample.y);
    //y is not max
    value = sample;
    compare = Point3(0.f, 10.f, 0.f);
    value = max(value, compare);
    EXPECT_EQ(value.y, compare.y);

    //z is max
    value = sample;
    compare = Point3(0.f, 0.f, -5.f);
    value.max(compare);
    EXPECT_EQ(value.z, sample.z);
    //z is not max
    value = sample;
    compare = Point3(0.f, 0.f, 0.f);
    value = max(value, compare);
    EXPECT_EQ(value.z, compare.z);
}

SPECTRE_TEST(Point3, min_inline)
{
    Point3 sample(0.5, 1.5, -3.5);
    Point3 value;
    Point3 compare;

    //x is max
    value = sample;
    compare = Point3(0.2f, 0.f, 0.f);
    value = min(value, compare);
    EXPECT_EQ(value.x, compare.x);
    //x is not max
    value = sample;
    compare = Point3(1.0, 0.f, 0.f);
    value = min(value, compare);
    EXPECT_EQ(value.x, sample.x);

    //y is max
    value = sample;
    compare = Point3(0.f, 1.f, 0.f);
    value = min(value, compare);
    EXPECT_EQ(value.y, compare.y);
    //y is not max
    value = sample;
    compare = Point3(0.f, 10.f, 0.f);
    value = min(value, compare);
    EXPECT_EQ(value.y, sample.y);

    //z is max
    value = sample;
    compare = Point3(0.f, 0.f, -5.f);
    value = min(value, compare);
    EXPECT_EQ(value.z, compare.z);
    //z is not max
    value = sample;
    compare = Point3(0.f, 0.f, 0.f);
    value = min(value, compare);
    EXPECT_EQ(value.z, sample.z);
}

SPECTRE_TEST_END(Point3_tests)
