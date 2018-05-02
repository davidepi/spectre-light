#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else
#include <gtest/gtest.h>
#endif

#include "geometry/point2.hpp"
#include "utility/utility.hpp"
#include <climits>
#include <cmath>

SPECTRE_TEST_INIT(Point2_tests)

SPECTRE_TEST(Point2, empty_constructor)
{
    Point2 p;
    EXPECT_EQ(p.x, 0.f);
    EXPECT_EQ(p.y, 0.f);
}

SPECTRE_TEST(Point2, same_value_constructor)
{
    float val = 1.0f;
    Point2 p(val);
    EXPECT_EQ(p.x, val);
    EXPECT_EQ(p.y, val);

    //NaNs, infinity is not an error
    errors_count[ERROR_INDEX] = 0;
    float nan = NAN;
    float infty = INFINITY;
    Point2 p1(nan);
    Point2 p2(infty);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(Point2, components_constructor)
{
    Point2 p(1.0f, -1.0f);
    EXPECT_EQ(p.x, 1.f);
    EXPECT_EQ(p.y, -1.f);

    //NaNs - Infinity is not an error for points
    errors_count[ERROR_INDEX] = 0;
    Point2 p1(NAN, 1.f);
    Point2 p2(1.f, NAN);
    Point2 p3(1.f, 1.f);
    Point2 p4(INFINITY, 1.f);
    Point2 p5(1.f, INFINITY);
    EXPECT_EQ(errors_count[ERROR_INDEX], 2);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(Point2, distance_noinline)
{
    Point2 p0(1, 2);
    Point2 p1(4, 5);
    float distance = p0.distanceTo(p1);
    EXPECT_NEAR(distance, 4.242641f, 1e-5f);
}

SPECTRE_TEST(Point2, max_noinline)
{
    Point2 sample(0.5, 1.5);
    Point2 value;
    Point2 compare;

    //x is max
    value = sample;
    compare = Point2(0.2f, 0.f);
    value.max(compare);
    EXPECT_EQ(value.x, sample.x);
    //x is not max
    value = sample;
    compare = Point2(1.0, 0.f);
    value.max(compare);
    EXPECT_EQ(value.x, compare.x);

    //y is max
    value = sample;
    compare = Point2(0.f, 1.f);
    value.max(compare);
    EXPECT_EQ(value.y, sample.y);
    //y is not max
    value = sample;
    compare = Point2(0.f, 10.f);
    value.max(compare);
    EXPECT_EQ(value.y, compare.y);
}

SPECTRE_TEST(Point2, min_noinline)
{
    Point2 sample(0.5, 1.5);
    Point2 value;
    Point2 compare;

    //x is max
    value = sample;
    compare = Point2(0.2f, 0.f);
    value.min(compare);
    EXPECT_EQ(value.x, compare.x);
    //x is not max
    value = sample;
    compare = Point2(1.0, 0.f);
    value.min(compare);
    EXPECT_EQ(value.x, sample.x);

    //y is max
    value = sample;
    compare = Point2(0.f, 1.f);
    value.min(compare);
    EXPECT_EQ(value.y, compare.y);
    //y is not max
    value = sample;
    compare = Point2(0.f, 10.f);
    value.min(compare);
    EXPECT_EQ(value.y, sample.y);
}

SPECTRE_TEST(Point2, sum_vector)
{
    Point2 v1(1, 2);
    Vec2 v2(4, 5.5);

    Point2 res = v1+v2;
    EXPECT_NEAR(res.x, 5.f, 1e-5f);
    EXPECT_NEAR(res.y, 7.5f, 1e-5f);
}

SPECTRE_TEST(Point2, sum_vector_this)
{
    Point2 v1(1, 2);
    Vec2 v2(4, 5.5);

    v1 += v2;
    EXPECT_NEAR(v1.x, 5.f, 1e-5f);
    EXPECT_NEAR(v1.y, 7.5f, 1e-5f);
}

SPECTRE_TEST(Point2, sub_point)
{
    Point2 v1(1, 2);
    Point2 v2(4, 5.5);
    Vec2 res = v2-v1;
    EXPECT_NEAR(res.x, 3.f, 1e-5f);
    EXPECT_NEAR(res.y, 3.5f, 1e-5f);
}

SPECTRE_TEST(Point2, sub_vector)
{
    Vec2 v1(1, 2);
    Point2 v2(4, 5.5);
    Point2 res = v2-v1;
    EXPECT_NEAR(res.x, 3.f, 1e-5f);
    EXPECT_NEAR(res.y, 3.5f, 1e-5f);
}

SPECTRE_TEST(Point2, sub_vector_this)
{
    Point2 v1(1, 2);
    Vec2 v2(4, 5.5);
    v1 -= v2;
    EXPECT_NEAR(v1.x, -3.f, 1e-5f);
    EXPECT_NEAR(v1.y, -3.5f, 1e-5f);
}

SPECTRE_TEST(Point2, equal)
{
    Point2 v1;
    Point2 v2;

    //[X VALUE] [Y VALUE]
    //[F] [F]
    v1 = Point2(35.93915f, -78.07117f);
    v2 = Point2(-8.50624f, 47.50334f);
    bool res = v1 == v2;
    EXPECT_EQ(res, false);

    //[T] [F]
    v1 = Point2(35.93915f, -78.07117f);
    v2 = Point2(35.93915f, 47.50334f);
    res = v1 == v2;
    EXPECT_EQ(res, false);

    //[F] [T]
    v1 = Point2(35.93915f, -78.07117f);
    v2 = Point2(-8.50624f, -78.07117f);
    res = v1 == v2;
    EXPECT_EQ(res, false);

    //[F] [F]
    v1 = Point2(35.93915f, -78.07117f);
    v2 = Point2(-8.50624f, 47.50334f);
    res = v1 == v2;
    EXPECT_EQ(res, false);

    //Inf which is accepted in Point2 but breaks comparison
    //beacause inf||bool -> true and nan||bool -> true
    errors_count[ERROR_INDEX] = 0;
    v1 = Point2(INFINITY, -78.07117f);
    v2 = Point2(-8.50624f, -78.07117f);
    res = v1 == v2;
    v1 = Point2(35.93915f, INFINITY);
    v2 = Point2(-8.50624f, -78.07117f);
    res = v1 == v2;
    v1 = Point2(35.93915f, -78.07117f);
    v2 = Point2(INFINITY, -78.07117f);
    res = v1 == v2;
    v1 = Point2(35.93915f, -78.07117f);
    v2 = Point2(-8.50624f, INFINITY);
    res = v1 == v2;
    EXPECT_EQ(errors_count[ERROR_INDEX], 4);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(Point2, not_equal)
{
    Point2 v1;
    Point2 v2;

    //[X VALUE] [Y VALUE]
    //[F] [F]
    v1 = Point2(35.93915f, -78.07117f);
    v2 = Point2(-8.50624f, 47.50334f);
    bool res = v1 != v2;
    EXPECT_EQ(res, true);

    //[T] [F]
    v1 = Point2(35.93915f, -78.07117f);
    v2 = Point2(35.93915f, 47.50334f);
    res = v1 != v2;
    EXPECT_EQ(res, true);

    //[F] [T]
    v1 = Point2(35.93915f, -78.07117f);
    v2 = Point2(-8.50624f, -78.07117f);
    res = v1 != v2;
    EXPECT_EQ(res, true);

    //[F] [F]
    v1 = Point2(35.93915f, -78.07117f);
    v2 = Point2(-8.50624f, 47.50334f);
    res = v1 != v2;
    EXPECT_EQ(res, true);

    //Inf which is accepted in Point2 but breaks comparison
    //beacause inf||bool -> true and nan||bool -> true
    errors_count[ERROR_INDEX] = 0;
    v1 = Point2(INFINITY, -78.07117f);
    v2 = Point2(-8.50624f, -78.07117f);
    res = v1 != v2;
    v1 = Point2(35.93915f, INFINITY);
    v2 = Point2(-8.50624f, -78.07117f);
    res = v1 != v2;
    v1 = Point2(35.93915f, -78.07117f);
    v2 = Point2(INFINITY, -78.07117f);
    res = v1 != v2;
    v1 = Point2(35.93915f, -78.07117f);
    v2 = Point2(-8.50624f, INFINITY);
    res = v1 != v2;
    EXPECT_EQ(errors_count[ERROR_INDEX], 4);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(Point2, access)
{
    Point2 v(-72.74395f, -6.04488f);
    EXPECT_EQ(v.x, v[0]);
    EXPECT_EQ(v.y, v[1]);
}

SPECTRE_TEST(Point2, const_access)
{
    const Point2 v2(-72.74395f, -6.04488f);
    EXPECT_EQ(v2.x, v2[0]);
    EXPECT_EQ(v2.y, v2[1]);
}

SPECTRE_TEST(Point2, distance_inline)
{
    Point2 p0(1, 2);
    Point2 p1(4, 5);
    float dist = distance(p0, p1);
    EXPECT_NEAR(dist, 4.242641f, 1e-5f);
}

SPECTRE_TEST(Point2, max_inline)
{
    Point2 sample(0.5, 1.5);
    Point2 value;
    Point2 compare;

    //x is max
    value = sample;
    compare = Point2(0.2f, 0.f);
    value = max(value, compare);
    EXPECT_EQ(value.x, sample.x);
    //x is not max
    value = sample;
    compare = Point2(1.0, 0.f);
    value = max(value, compare);
    EXPECT_EQ(value.x, compare.x);

    //y is max
    value = sample;
    compare = Point2(0.f, 1.f);
    value.max(compare);
    EXPECT_EQ(value.y, sample.y);
    //y is not max
    value = sample;
    compare = Point2(0.f, 10.f);
    value = max(value, compare);
    EXPECT_EQ(value.y, compare.y);
}

SPECTRE_TEST(Point2, min_inline)
{
    Point2 sample(0.5, 1.5);
    Point2 value;
    Point2 compare;

    //x is max
    value = sample;
    compare = Point2(0.2f, 0.f);
    value = min(value, compare);
    EXPECT_EQ(value.x, compare.x);
    //x is not max
    value = sample;
    compare = Point2(1.0, 0.f);
    value = min(value, compare);
    EXPECT_EQ(value.x, sample.x);

    //y is max
    value = sample;
    compare = Point2(0.f, 1.f);
    value = min(value, compare);
    EXPECT_EQ(value.y, compare.y);
    //y is not max
    value = sample;
    compare = Point2(0.f, 10.f);
    value = min(value, compare);
    EXPECT_EQ(value.y, sample.y);
}

SPECTRE_TEST_END(Point2_tests)
