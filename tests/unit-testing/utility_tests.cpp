#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "utility/utility.hpp"
#include "utility/array2D.hpp"
#include <climits>

SPECTRE_TEST_INIT(Utility_tests)

SPECTRE_TEST(Utility, format_secs)
{
    char out[MAX_TIME_FORMAT_LENGTH];

    //more than 100d
    format_seconds(8640000, out);
    EXPECT_STREQ(out, MESSAGE_MORE_THAN_100_DAYS);

    //less than 1s
    format_seconds(0, out);
    EXPECT_STREQ(out, MESSAGE_LESS_THAN_1_SECOND);

    //max length for days, hours, mins and s
    format_seconds(8639999, out);
    EXPECT_STREQ(out, "99d 23h 59m 59s ");

    //only some seconds
    format_seconds(41, out);
    EXPECT_STREQ(out, "41s ");

    //five minutes
    format_seconds(300, out);
    EXPECT_STREQ(out, "5m ");
}

SPECTRE_TEST(Utility, swap_float)
{
    float f1_original = 0.5f;
    float f2_original = -0.5f;
    float f1 = f1_original;
    float f2 = f2_original;
    swap(&f1, &f2);
    EXPECT_EQ(f1, f2_original);
    EXPECT_EQ(f2, f1_original);
}

SPECTRE_TEST(Utility, swap_uint8)
{
    uint8_t f1_original = 5;
    uint8_t f2_original = -5;
    uint8_t f1 = f1_original;
    uint8_t f2 = f2_original;
    swap(&f1, &f2);
    EXPECT_EQ(f1, f2_original);
    EXPECT_EQ(f2, f1_original);
}

SPECTRE_TEST(Utility, radians_inline_float)
{
    EXPECT_NEAR(radians(0.f), 0.f, 1e-5f);
    EXPECT_NEAR(radians(90.f), ONE_PI/2.f, 1e-5f);
    EXPECT_NEAR(radians(180.f), ONE_PI, 1e-5f);
    EXPECT_NEAR(radians(270.f), ONE_PI*3.f/2.f, 1e-5f);
    EXPECT_NEAR(radians(360.f), TWO_PI, 1e-5f);
    EXPECT_NEAR(radians(450.f), TWO_PI+ONE_PI/2.f, 1e-5f);
}

SPECTRE_TEST(Utility, radians_inline_double)
{
    EXPECT_NEAR(radians(0.0), 0.0, 1e-5);
    EXPECT_NEAR(radians(90.0), M_PI/2.0, 1e-5);
    EXPECT_NEAR(radians(180.0), M_PI, 1e-5);
    EXPECT_NEAR(radians(270.0), M_PI*3.0/2.0, 1e-5);
    EXPECT_NEAR(radians(360.0), 2*M_PI, 1e-5f);
    EXPECT_NEAR(radians(450.0), 2*M_PI+M_PI/2.0, 1e-5);
}

SPECTRE_TEST(Utility, degrees_inline_float)
{
    EXPECT_NEAR(degrees(0.f), 0.f, 1e-5f);
    EXPECT_NEAR(degrees(ONE_PI/2.f), 90.f, 1e-5f);
    EXPECT_NEAR(degrees(ONE_PI), 180.f, 1e-5f);
    EXPECT_NEAR(degrees(ONE_PI*3.f/2.f), 270.f, 1e-5f);
    EXPECT_NEAR(degrees(TWO_PI), 360.f, 1e-5f);
    EXPECT_NEAR(degrees(TWO_PI+ONE_PI/2.f), 450.f, 1e-5f);
}

SPECTRE_TEST(Utility, degrees_inline_double)
{
    EXPECT_NEAR(degrees(0.0), 0.0, 1e-5);
    EXPECT_NEAR(degrees(M_PI/2.0), 90.0, 1e-5);
    EXPECT_NEAR(degrees(M_PI), 180.0, 1e-5);
    EXPECT_NEAR(degrees(M_PI*3.0/2.0), 270.0, 1e-5);
    EXPECT_NEAR(degrees(2*M_PI), 360.0, 1e-5);
    EXPECT_NEAR(degrees(2*M_PI+M_PI/2.0), 450.0, 1e-5);
}


SPECTRE_TEST(Utility, min_float)
{
    float a = 0.5f;
    float b = 1.5f;
    EXPECT_EQ(min(a, b), a);
    EXPECT_EQ(min(b, a), a);
}

SPECTRE_TEST(Utility, max_float)
{
    float a = 0.5f;
    float b = 1.5f;
    EXPECT_EQ(max(a, b), b);
    EXPECT_EQ(max(b, a), b);
}

SPECTRE_TEST(Utility, min_int)
{
    int a = 1;
    int b = 2;
    EXPECT_EQ(min(a, b), a);
    EXPECT_EQ(min(b, a), a);
}

SPECTRE_TEST(Utility, max_int)
{
    int a = 1;
    int b = 2;
    EXPECT_EQ(max(a, b), b);
    EXPECT_EQ(max(b, a), b);
}

SPECTRE_TEST(Utility, clamp_inline)
{
    float a;
    float res;

    //in range
    a = 0.75f;
    res = clamp(a, 0.5f, 2.f);
    EXPECT_EQ(res, a);

    //lower
    a = -.5f;
    res = clamp(a, 0.5f, 2.f);
    EXPECT_EQ(res, 0.5f);

    //higher
    a = 3.5f;
    res = clamp(a, 0.5f, 2.f);
    EXPECT_EQ(res, 2.f);
}

SPECTRE_TEST(Utility, lerp_inline)
{
    float a = 0.25f;
    float res = lerp(a, 0.f, 1.f);
    EXPECT_EQ(res, a);

    res = lerp(a, -1.f, 2.f);
    EXPECT_EQ(res, -0.25f);
}

SPECTRE_TEST(Utility, inverse_lerp_inline)
{
    float a = 0.25f;
    float res = inverse_lerp(0.25, 0.f, 1.f);
    EXPECT_EQ(res, a);

    res = inverse_lerp(-0.25, -1.f, 2.f);
    EXPECT_EQ(res, a);
}

SPECTRE_TEST(Utility, flt_equal_inline)
{
    float a = 0.1;
    float b = 0.1+FLT_EPSILON;
    EXPECT_NE(a, b);
    EXPECT_TRUE(flt_equal(a, b));

    b += 1E-4f;
    EXPECT_NE(a, b);
    EXPECT_FALSE(flt_equal(a, b));
}

SPECTRE_TEST(Utility, sign_inline)
{
    float a = -.5f;
    float b = .5f;
    float zero = 0.f;

    EXPECT_EQ(sign(a), -1);
    EXPECT_EQ(sign(b), 1);
    EXPECT_EQ(sign(zero), 1);
}

SPECTRE_TEST(Utility, nearest_uint_inline)
{
    EXPECT_EQ(nearest_uint(800, 32), (unsigned int)800);
    EXPECT_EQ(nearest_uint(799, 32), (unsigned int)800);
    EXPECT_EQ(nearest_uint(801, 32), (unsigned int)800);
    EXPECT_EQ(nearest_uint(0, 32), (unsigned int)0);
}

SPECTRE_TEST(Utility, equation1_inline)
{
    EXPECT_EQ(equation1(2.f, 1.f), -0.5f);

    errors_count[ERROR_INDEX] = 0;
    equation1(0, 1.f);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(Utility, equation2_inline)
{
    float sol1;
    float sol2;
    bool res;

    //2 sol
    res = equation2(1.f, -1.f, -2.f, &sol1, &sol2);
    if(sol1>sol2)
        swap(&sol1, &sol2);
    EXPECT_EQ(sol1, -1.f);
    EXPECT_EQ(sol2, 2.f);
    EXPECT_TRUE(res);

    //1 sol
    res = equation2(-3.f, -24.f, -48.f, &sol1, &sol2);
    EXPECT_EQ(sol1, -4.f);
    EXPECT_EQ(sol2, -4.f);
    EXPECT_TRUE(res);

    //0 sol
    res = equation2(1.f, -1.f, 2.f, &sol1, &sol2);
    EXPECT_FALSE(res);

    //delta<0 but fp error (1e-4)
    res = equation2(1.00000012f, -2.62480998f, 1.72240686f, &sol1, &sol2);
    EXPECT_NEAR(sol1, 1.31240487f, 1e-5f);
    EXPECT_NEAR(sol2, 1.31240487f, 1e-5f);
    EXPECT_TRUE(res);
}

SPECTRE_TEST(Utility, swap_endianness_32_bit)
{
    uint32_t a = 1518819910U;
    uint32_t res = swap_endianness(a);
    EXPECT_EQ(res, 1180338010U);
}

SPECTRE_TEST(Utility, swap_endianness_16_bit)
{
    uint16_t a = 41515U;
    uint16_t res = swap_endianness(a);
    //this does not work with EXPECT_EQ under windows
    EXPECT_TRUE(res == (uint16_t)11170);
}

SPECTRE_TEST_END(Utility_tests)
