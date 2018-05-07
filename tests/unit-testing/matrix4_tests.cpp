#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else
#include <gtest/gtest.h>
#endif

#include "geometry/matrix4.hpp"
#include "utility/utility.hpp"
#include <climits>
#include <cmath>

SPECTRE_TEST_INIT(Matrix4_tests)

SPECTRE_TEST(Matrix4, float_constructor)
{
    float vals[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    Matrix4 m(vals);
    EXPECT_EQ(m.m00, vals[0]);
    EXPECT_EQ(m.m01, vals[1]);
    EXPECT_EQ(m.m02, vals[2]);
    EXPECT_EQ(m.m03, vals[3]);
    EXPECT_EQ(m.m10, vals[4]);
    EXPECT_EQ(m.m11, vals[5]);
    EXPECT_EQ(m.m12, vals[6]);
    EXPECT_EQ(m.m13, vals[7]);
    EXPECT_EQ(m.m20, vals[8]);
    EXPECT_EQ(m.m21, vals[9]);
    EXPECT_EQ(m.m22, vals[10]);
    EXPECT_EQ(m.m23, vals[11]);
    EXPECT_EQ(m.m30, vals[12]);
    EXPECT_EQ(m.m31, vals[13]);
    EXPECT_EQ(m.m32, vals[14]);
    EXPECT_EQ(m.m33, vals[15]);

    errors_count[WARNING_INDEX] = 0;
    float* nullval = NULL;
    Matrix4 m2(nullval);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
}

SPECTRE_TEST(Matrix4, toString)
{
    float vals[16] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    Matrix4 m(vals);
    std::string output = m.to_string();
    EXPECT_STREQ(output.c_str(),
                 "Matrix4[0.000000, 1.000000, 0.000000, 1.000000]\n"\
                          "       [0.000000, 1.000000, 0.000000, 1.000000]\n"\
                          "       [0.000000, 1.000000, 0.000000, 1.000000]\n"\
                          "       [0.000000, 1.000000, 0.000000, 1.000000]\n");
}

SPECTRE_TEST(Matrix4, toArray)
{
    float vals[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    Matrix4 m(vals);
    float res[16];
    m.to_array(res);
    EXPECT_EQ(vals[0], res[0]);
    EXPECT_EQ(vals[1], res[1]);
    EXPECT_EQ(vals[2], res[2]);
    EXPECT_EQ(vals[3], res[3]);
    EXPECT_EQ(vals[4], res[4]);
    EXPECT_EQ(vals[5], res[5]);
    EXPECT_EQ(vals[6], res[6]);
    EXPECT_EQ(vals[7], res[7]);
    EXPECT_EQ(vals[8], res[8]);
    EXPECT_EQ(vals[9], res[9]);
    EXPECT_EQ(vals[10], res[10]);
    EXPECT_EQ(vals[11], res[11]);
    EXPECT_EQ(vals[12], res[12]);
    EXPECT_EQ(vals[13], res[13]);
    EXPECT_EQ(vals[14], res[14]);
    EXPECT_EQ(vals[15], res[15]);
}

SPECTRE_TEST(Matrix4, set_zero)
{
    Matrix4 m;
    m.set_zero();
    EXPECT_EQ(m.m00, 0.f);
    EXPECT_EQ(m.m01, 0.f);
    EXPECT_EQ(m.m02, 0.f);
    EXPECT_EQ(m.m03, 0.f);
    EXPECT_EQ(m.m10, 0.f);
    EXPECT_EQ(m.m11, 0.f);
    EXPECT_EQ(m.m12, 0.f);
    EXPECT_EQ(m.m13, 0.f);
    EXPECT_EQ(m.m20, 0.f);
    EXPECT_EQ(m.m21, 0.f);
    EXPECT_EQ(m.m22, 0.f);
    EXPECT_EQ(m.m23, 0.f);
    EXPECT_EQ(m.m30, 0.f);
    EXPECT_EQ(m.m31, 0.f);
    EXPECT_EQ(m.m32, 0.f);
    EXPECT_EQ(m.m33, 0.f);
}

SPECTRE_TEST(Matrix4, set_identity)
{
    Matrix4 m;
    m.set_identity();
    EXPECT_EQ(m.m00, 1.f);
    EXPECT_EQ(m.m01, 0.f);
    EXPECT_EQ(m.m02, 0.f);
    EXPECT_EQ(m.m03, 0.f);
    EXPECT_EQ(m.m10, 0.f);
    EXPECT_EQ(m.m11, 1.f);
    EXPECT_EQ(m.m12, 0.f);
    EXPECT_EQ(m.m13, 0.f);
    EXPECT_EQ(m.m20, 0.f);
    EXPECT_EQ(m.m21, 0.f);
    EXPECT_EQ(m.m22, 1.f);
    EXPECT_EQ(m.m23, 0.f);
    EXPECT_EQ(m.m30, 0.f);
    EXPECT_EQ(m.m31, 0.f);
    EXPECT_EQ(m.m32, 0.f);
    EXPECT_EQ(m.m33, 1.f);
}

SPECTRE_TEST(Matrix4, set_translation)
{
    Matrix4 m;
    Vec3 trans(-87.39175f, 8.35182f, -93.43325f);
    m.set_translation(trans);
    EXPECT_EQ(m.m00, 1.f);
    EXPECT_EQ(m.m01, 0.f);
    EXPECT_EQ(m.m02, 0.f);
    EXPECT_EQ(m.m03, trans.x);
    EXPECT_EQ(m.m10, 0.f);
    EXPECT_EQ(m.m11, 1.f);
    EXPECT_EQ(m.m12, 0.f);
    EXPECT_EQ(m.m13, trans.y);
    EXPECT_EQ(m.m20, 0.f);
    EXPECT_EQ(m.m21, 0.f);
    EXPECT_EQ(m.m22, 1.f);
    EXPECT_EQ(m.m23, trans.z);
    EXPECT_EQ(m.m30, 0.f);
    EXPECT_EQ(m.m31, 0.f);
    EXPECT_EQ(m.m32, 0.f);
    EXPECT_EQ(m.m33, 1.f);
}

SPECTRE_TEST(Matrix4, set_scale_uniform)
{
    Matrix4 m;
    float magnitude = 73.35321f;
    m.set_scale(magnitude);
    EXPECT_EQ(m.m00, magnitude);
    EXPECT_EQ(m.m01, 0.f);
    EXPECT_EQ(m.m02, 0.f);
    EXPECT_EQ(m.m03, 0.f);
    EXPECT_EQ(m.m10, 0.f);
    EXPECT_EQ(m.m11, magnitude);
    EXPECT_EQ(m.m12, 0.f);
    EXPECT_EQ(m.m13, 0.f);
    EXPECT_EQ(m.m20, 0.f);
    EXPECT_EQ(m.m21, 0.f);
    EXPECT_EQ(m.m22, magnitude);
    EXPECT_EQ(m.m23, 0.f);
    EXPECT_EQ(m.m30, 0.f);
    EXPECT_EQ(m.m31, 0.f);
    EXPECT_EQ(m.m32, 0.f);
    EXPECT_EQ(m.m33, 1.f);
}

SPECTRE_TEST(Matrix4, set_scale_non_uniform)
{
    Matrix4 m;
    Vec3 magnitude(41.24096, -93.12313, 31.83295);
    m.set_scale(magnitude);
    EXPECT_EQ(m.m00, magnitude.x);
    EXPECT_EQ(m.m01, 0.f);
    EXPECT_EQ(m.m02, 0.f);
    EXPECT_EQ(m.m03, 0.f);
    EXPECT_EQ(m.m10, 0.f);
    EXPECT_EQ(m.m11, magnitude.y);
    EXPECT_EQ(m.m12, 0.f);
    EXPECT_EQ(m.m13, 0.f);
    EXPECT_EQ(m.m20, 0.f);
    EXPECT_EQ(m.m21, 0.f);
    EXPECT_EQ(m.m22, magnitude.z);
    EXPECT_EQ(m.m23, 0.f);
    EXPECT_EQ(m.m30, 0.f);
    EXPECT_EQ(m.m31, 0.f);
    EXPECT_EQ(m.m32, 0.f);
    EXPECT_EQ(m.m33, 1.f);
}

SPECTRE_TEST(Matrix4, set_rotate_x)
{
    Matrix4 m;
    float val = 3.f/4.f*ONE_PI;
    m.set_rotate_x(val);
    EXPECT_EQ(m.m00, 1.f);
    EXPECT_EQ(m.m01, 0.f);
    EXPECT_EQ(m.m02, 0.f);
    EXPECT_EQ(m.m03, 0.f);
    EXPECT_EQ(m.m10, 0.f);
    EXPECT_NEAR(m.m11, -1.f/sqrtf(2), 1e-5f);
    EXPECT_NEAR(m.m12, -1.f/sqrtf(2), 1e-5f);
    EXPECT_EQ(m.m13, 0.f);
    EXPECT_EQ(m.m20, 0.f);
    EXPECT_NEAR(m.m21, 1.f/sqrtf(2), 1e-5f);
    EXPECT_NEAR(m.m22, -1.f/sqrtf(2), 1e-5f);
    EXPECT_EQ(m.m23, 0.f);
    EXPECT_EQ(m.m30, 0.f);
    EXPECT_EQ(m.m31, 0.f);
    EXPECT_EQ(m.m32, 0.f);
    EXPECT_EQ(m.m33, 1.f);
}

SPECTRE_TEST(Matrix4, set_rotate_y)
{
    Matrix4 m;
    float val = 3.f/4.f*ONE_PI;
    m.set_rotate_y(val);
    EXPECT_NEAR(m.m00, -1.f/sqrtf(2), 1e-5f);
    EXPECT_EQ(m.m01, 0.f);
    EXPECT_NEAR(m.m02, 1.f/sqrtf(2), 1e-5f);
    EXPECT_EQ(m.m03, 0.f);
    EXPECT_EQ(m.m10, 0.f);
    EXPECT_EQ(m.m11, 1.f);
    EXPECT_EQ(m.m12, 0.f);
    EXPECT_EQ(m.m13, 0.f);
    EXPECT_NEAR(m.m20, -1.f/sqrtf(2), 1e-5f);
    EXPECT_EQ(m.m21, 0.f);
    EXPECT_NEAR(m.m22, -1.f/sqrtf(2), 1e-5f);
    EXPECT_EQ(m.m23, 0.f);
    EXPECT_EQ(m.m30, 0.f);
    EXPECT_EQ(m.m31, 0.f);
    EXPECT_EQ(m.m32, 0.f);
    EXPECT_EQ(m.m33, 1.f);
}

SPECTRE_TEST(Matrix4, set_rotate_z)
{
    Matrix4 m;
    float val = 3.f/4.f*ONE_PI;
    m.set_rotate_z(val);
    EXPECT_NEAR(m.m00, -1.f/sqrtf(2), 1e-5f);
    EXPECT_NEAR(m.m01, -1.f/sqrtf(2), 1e-5f);
    EXPECT_EQ(m.m02, 0.f);
    EXPECT_EQ(m.m03, 0.f);
    EXPECT_NEAR(m.m10, 1.f/sqrtf(2), 1e-5f);
    EXPECT_NEAR(m.m11, -1.f/sqrtf(2), 1e-5f);
    EXPECT_EQ(m.m12, 0.f);
    EXPECT_EQ(m.m13, 0.f);
    EXPECT_EQ(m.m20, 0.f);
    EXPECT_EQ(m.m21, 0.f);
    EXPECT_EQ(m.m22, 1.f);
    EXPECT_EQ(m.m23, 0.f);
    EXPECT_EQ(m.m30, 0.f);
    EXPECT_EQ(m.m31, 0.f);
    EXPECT_EQ(m.m32, 0.f);
    EXPECT_EQ(m.m33, 1.f);
}

SPECTRE_TEST(Matrix4, lookAt)
{
    //non normalized up
    Vec3 up(1, 1, 0);
    Point3 pos(1, 0, -2);
    Point3 target(0, 0, 1);
    Matrix4 m;
    errors_count[WARNING_INDEX] = 0;
    m.set_lookAt_inverse(pos, target, up);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;

    //normalized up
    up.normalize();
    m.set_lookAt_inverse(pos, target, up);
    EXPECT_EQ(errors_count[WARNING_INDEX], 0);
    EXPECT_NEAR(m.m00, 0.688247144f, 1e-5f);
    EXPECT_NEAR(m.m01, 0.65292853f, 1e-5f);
    EXPECT_NEAR(m.m02, -0.31622776f, 1e-5f);
    EXPECT_NEAR(m.m03, 1.f, 1e-5f);
    EXPECT_NEAR(m.m10, -0.688247f, 1e-5f);
    EXPECT_NEAR(m.m11, 0.725476f, 1e-5f);
    EXPECT_NEAR(m.m12, 0.f, 1e-5f);
    EXPECT_NEAR(m.m13, 0.f, 1e-5f);
    EXPECT_NEAR(m.m20, 0.22941573f, 1e-5f);
    EXPECT_NEAR(m.m21, 0.21764286f, 1e-5f);
    EXPECT_NEAR(m.m22, 0.948683261f, 1e-5f);
    EXPECT_NEAR(m.m23, -2.f, 1e-5f);
    EXPECT_NEAR(m.m30, 0.f, 1e-5f);
    EXPECT_NEAR(m.m31, 0.f, 1e-5f);
    EXPECT_NEAR(m.m32, 0.f, 1e-5f);
    EXPECT_NEAR(m.m33, 1.f, 1e-5f);
}

SPECTRE_TEST(Matrix4, transpose)
{
    float vals[] = {27.9484, -88.37513, -25.05486, 0.93192, 19.53558, 55.46225,
                    -92.99693, 13.30983, -39.91206, -63.35516, -80.28301,
                    96.89149, -97.99183,
                    69.73036, 34.27019, 58.81281};
    Matrix4 m(vals);
    Matrix4 out;
    m.transpose(&out);
    EXPECT_EQ(vals[0], out.m00);
    EXPECT_EQ(vals[1], out.m10);
    EXPECT_EQ(vals[2], out.m20);
    EXPECT_EQ(vals[3], out.m30);
    EXPECT_EQ(vals[4], out.m01);
    EXPECT_EQ(vals[5], out.m11);
    EXPECT_EQ(vals[6], out.m21);
    EXPECT_EQ(vals[7], out.m31);
    EXPECT_EQ(vals[8], out.m02);
    EXPECT_EQ(vals[9], out.m12);
    EXPECT_EQ(vals[10], out.m22);
    EXPECT_EQ(vals[11], out.m32);
    EXPECT_EQ(vals[12], out.m03);
    EXPECT_EQ(vals[13], out.m13);
    EXPECT_EQ(vals[14], out.m23);
    EXPECT_EQ(vals[15], out.m33);
}

SPECTRE_TEST(Matrix4, inverse)
{
    //invertible
    float vals[] = {44.48, -69.73, 62.26, -89.47, -20.59, 45.01, -77.12, 21.26,
                    3.27,
                    42.29, -62.23, -49.23, 6.83, -80.83, 18.96, -84.16};
    Matrix4 m(vals);
    Matrix4 out;
    bool res = m.inverse(&out);
    EXPECT_TRUE(res);
    EXPECT_NEAR(out.m00, 0.05696867986878306f, 1e-5f);
    EXPECT_NEAR(out.m01, 0.06042118741944838f, 1e-5f);
    EXPECT_NEAR(out.m02, -0.026891372703873692f, 1e-5f);
    EXPECT_NEAR(out.m03, -0.02956953311205848f, 1e-5f);
    EXPECT_NEAR(out.m10, -0.016213241351212312f, 1e-5f);
    EXPECT_NEAR(out.m11, -0.03287692440970072f, 1e-5f);
    EXPECT_NEAR(out.m12, 0.02312255927369855f, 1e-5f);
    EXPECT_NEAR(out.m13, -0.004594680398068575f, 1e-5f);
    EXPECT_NEAR(out.m20, -0.020370360928440107f, 1e-5f);
    EXPECT_NEAR(out.m21, -0.040761643380056015f, 1e-5f);
    EXPECT_NEAR(out.m22, 0.014874902160732165f, 1e-5f);
    EXPECT_NEAR(out.m23, 0.0026574715235824666f, 1e-5f);
    EXPECT_NEAR(out.m30, 0.015605873796566723f, 1e-5f);
    EXPECT_NEAR(out.m31, 0.027296551231286575f, 1e-5f);
    EXPECT_NEAR(out.m32, -0.021038931695497014f, 1e-5f);
    EXPECT_NEAR(out.m33, -0.009270273788407236f, 1e-5f);

    //non invertible
    //not the best solution, since I would like to try a dirty 0
    //(0.00000000000001 as determinant, for example)
    Matrix4 zero;
    zero.set_zero();
    res = zero.inverse(&out);
    EXPECT_FALSE(res);
}

SPECTRE_TEST(Matrix4, get_translation)
{
    Vec3 scale(53.94708, -56.04181, 38.21224);
    Vec3 translation(-5.28423, 22.63478, 22.10424);
    Vec3 rotation(-0.07627, -31.31443, -88.95238);
    Matrix4 ms;
    ms.set_scale(scale);
    Matrix4 mt;
    mt.set_translation(translation);
    Matrix4 mrx;
    mrx.set_rotate_x(rotation.x);
    Matrix4 mry;
    mry.set_rotate_y(rotation.y);
    Matrix4 mrz;
    mrz.set_rotate_z(rotation.z);
    Matrix4 combined;
    combined.set_identity();

    combined *= mt;
    combined *= mrz;
    combined *= mry;
    combined *= mrx;
    combined *= ms;

    Vec3 extracted = combined.get_translation();
    EXPECT_NEAR(extracted.x, translation.x, 1e-5f);
    EXPECT_NEAR(extracted.y, translation.y, 1e-5f);
    EXPECT_NEAR(extracted.z, translation.z, 1e-5f);
}

SPECTRE_TEST(Matrix4, get_scale)
{
    Vec3 scale(37.99025, 69.85438, 5.79172);
    Vec3 translation(-17.90241, 37.90712, 74.85354);
    Vec3 rotation(-20.80442, 27.33369, -31.58807);
    Matrix4 ms;
    ms.set_scale(scale);
    Matrix4 mt;
    mt.set_translation(translation);
    Matrix4 mrx;
    mrx.set_rotate_x(rotation.x);
    Matrix4 mry;
    mry.set_rotate_y(rotation.y);
    Matrix4 mrz;
    mrz.set_rotate_z(rotation.z);
    Matrix4 combined;
    combined.set_identity();

    combined *= mt;
    combined *= mrz;
    combined *= mry;
    combined *= mrx;
    combined *= ms;

    Vec3 extracted = combined.get_scale();
    EXPECT_NEAR(extracted.x, scale.x, 1e-5f);
    EXPECT_NEAR(extracted.y, scale.y, 1e-5f);
    EXPECT_NEAR(extracted.z, scale.z, 1e-5f);
}

SPECTRE_TEST(Matrix4, sum_noinline)
{
    float val1[] = {-98.96f, 98.99f, 72.96f, 98.37f, -61.17f, 6.f, -13.05f,
                    18.62f,
                    43.24f, -19.56f, 39.17f, -19.17f, -49.98f, -36.64f, 48.f,
                    45.27f};
    float val2[] = {59.09f, -8.73f, -19.45f, 88.6f, 85.6f, -67.18f, 31.89f,
                    -71.7f,
                    40.15f, 38.28f, 48.01f, -73.72f, 37.04f, 34.6f, -46.98f,
                    -44.3f};
    Matrix4 m1(val1);
    Matrix4 m2(val2);
    Matrix4 out = m1+m2;
    EXPECT_NEAR(out.m00, -39.87f, 1e-5f);
    EXPECT_NEAR(out.m01, 90.26f, 1e-5f);
    EXPECT_NEAR(out.m02, 53.51f, 1e-5f);
    EXPECT_NEAR(out.m03, 186.97f, 1e-5f);
    EXPECT_NEAR(out.m10, 24.43f, 1e-5f);
    EXPECT_NEAR(out.m11, -61.18f, 1e-5f);
    EXPECT_NEAR(out.m12, 18.84f, 1e-5f);
    EXPECT_NEAR(out.m13, -53.08f, 1e-5f);
    EXPECT_NEAR(out.m20, 83.39f, 1e-5f);
    EXPECT_NEAR(out.m21, 18.72f, 1e-5f);
    EXPECT_NEAR(out.m22, 87.18f, 1e-5f);
    EXPECT_NEAR(out.m23, -92.89f, 1e-5f);
    EXPECT_NEAR(out.m30, -12.94f, 1e-5f);
    EXPECT_NEAR(out.m31, -2.04f, 1e-5f);
    EXPECT_NEAR(out.m32, 1.02f, 1e-5f);
    EXPECT_NEAR(out.m33, .97000122f, 1e-5f);
}

SPECTRE_TEST(Matrix4, sum_this)
{
    float val1[] = {-98.96f, 98.99f, 72.96f, 98.37f, -61.17f, 6.f, -13.05f,
                    18.62f,
                    43.24f, -19.56f, 39.17f, -19.17f, -49.98f, -36.64f, 48.f,
                    45.27f};
    float val2[] = {59.09f, -8.73f, -19.45f, 88.6f, 85.6f, -67.18f, 31.89f,
                    -71.7f,
                    40.15f, 38.28f, 48.01f, -73.72f, 37.04f, 34.6f, -46.98f,
                    -44.3f};
    Matrix4 m1(val1);
    Matrix4 m2(val2);
    m1 += m2;
    EXPECT_NEAR(m1.m00, -39.87f, 1e-5f);
    EXPECT_NEAR(m1.m01, 90.26f, 1e-5f);
    EXPECT_NEAR(m1.m02, 53.51f, 1e-5f);
    EXPECT_NEAR(m1.m03, 186.97f, 1e-5f);
    EXPECT_NEAR(m1.m10, 24.43f, 1e-5f);
    EXPECT_NEAR(m1.m11, -61.18f, 1e-5f);
    EXPECT_NEAR(m1.m12, 18.84f, 1e-5f);
    EXPECT_NEAR(m1.m13, -53.08f, 1e-5f);
    EXPECT_NEAR(m1.m20, 83.39f, 1e-5f);
    EXPECT_NEAR(m1.m21, 18.72f, 1e-5f);
    EXPECT_NEAR(m1.m22, 87.18f, 1e-5f);
    EXPECT_NEAR(m1.m23, -92.89f, 1e-5f);
    EXPECT_NEAR(m1.m30, -12.94f, 1e-5f);
    EXPECT_NEAR(m1.m31, -2.04f, 1e-5f);
    EXPECT_NEAR(m1.m32, 1.02f, 1e-5f);
    EXPECT_NEAR(m1.m33, 0.97000122f, 1e-5f);
}

SPECTRE_TEST(Matrix4, sum_inline)
{
    float val1[] = {-98.96f, 98.99f, 72.96f, 98.37f, -61.17f, 6.f, -13.05f,
                    18.62f,
                    43.24f, -19.56f, 39.17f, -19.17f, -49.98f, -36.64f, 48.f,
                    45.27f};
    float val2[] = {59.09f, -8.73f, -19.45f, 88.6f, 85.6f, -67.18f, 31.89f,
                    -71.7f,
                    40.15f, 38.28f, 48.01f, -73.72f, 37.04f, 34.6f, -46.98f,
                    -44.3f};
    Matrix4 m1(val1);
    Matrix4 m2(val2);
    Matrix4 out;
    sum(&m1, &m2, &out);
    EXPECT_NEAR(out.m00, -39.87f, 1e-5f);
    EXPECT_NEAR(out.m01, 90.26f, 1e-5f);
    EXPECT_NEAR(out.m02, 53.51f, 1e-5f);
    EXPECT_NEAR(out.m03, 186.97f, 1e-5f);
    EXPECT_NEAR(out.m10, 24.43f, 1e-5f);
    EXPECT_NEAR(out.m11, -61.18f, 1e-5f);
    EXPECT_NEAR(out.m12, 18.84f, 1e-5f);
    EXPECT_NEAR(out.m13, -53.08f, 1e-5f);
    EXPECT_NEAR(out.m20, 83.39f, 1e-5f);
    EXPECT_NEAR(out.m21, 18.72f, 1e-5f);
    EXPECT_NEAR(out.m22, 87.18f, 1e-5f);
    EXPECT_NEAR(out.m23, -92.89f, 1e-5f);
    EXPECT_NEAR(out.m30, -12.94f, 1e-5f);
    EXPECT_NEAR(out.m31, -2.04f, 1e-5f);
    EXPECT_NEAR(out.m32, 1.02f, 1e-5f);
    EXPECT_NEAR(out.m33, .97000122f, 1e-5f);
}

SPECTRE_TEST(Matrix4, sub_noinline)
{
    float val1[] = {-20.64f, -25.69f, -17.56f, -97.15f, 88.28f, 28.07f, 65.32f,
                    46.34f,
                    1.19f, -66.15f, 92.73f, -3.68f, -20.59f, 62.21f, 73.89f,
                    -29.04f};
    float val2[] = {61.53f, 75.87f, 44.25f, -57.29f, -81.46f, 97.1f, -62.07f,
                    -27.39f,
                    34.94f, 61.01f, 5.92f, -71.72f, 90.79f, 93.32f, -63.03f,
                    45.79f};
    Matrix4 m1(val1);
    Matrix4 m2(val2);
    Matrix4 out = m1-m2;
    EXPECT_NEAR(out.m00, -82.17f, 1e-5f);
    EXPECT_NEAR(out.m01, -101.56f, 1e-5f);
    EXPECT_NEAR(out.m02, -61.81f, 1e-5f);
    EXPECT_NEAR(out.m03, -39.86f, 1e-5f);
    EXPECT_NEAR(out.m10, 169.73999f, 1e-5f); //fuck floats
    EXPECT_NEAR(out.m11, -69.03f, 1e-5f);
    EXPECT_NEAR(out.m12, 127.39f, 1e-5f);
    EXPECT_NEAR(out.m13, 73.73f, 1e-5f);
    EXPECT_NEAR(out.m20, -33.75f, 1e-5f);
    EXPECT_NEAR(out.m21, -127.16f, 1e-5f);
    EXPECT_NEAR(out.m22, 86.81f, 1e-5f);
    EXPECT_NEAR(out.m23, 68.04f, 1e-5f);
    EXPECT_NEAR(out.m30, -111.38f, 1e-5f);
    EXPECT_NEAR(out.m31, -31.11f, 1e-5f);
    EXPECT_NEAR(out.m32, 136.92f, 1e-5f);
    EXPECT_NEAR(out.m33, -74.83f, 1e-5f);
}

SPECTRE_TEST(Matrix4, sub_this)
{
    float val1[] = {-20.64f, -25.69f, -17.56f, -97.15f, 88.28f, 28.07f, 65.32f,
                    46.34f,
                    1.19f, -66.15f, 92.73f, -3.68f, -20.59f, 62.21f, 73.89f,
                    -29.04f};
    float val2[] = {61.53f, 75.87f, 44.25f, -57.29f, -81.46f, 97.1f, -62.07f,
                    -27.39f,
                    34.94f, 61.01f, 5.92f, -71.72f, 90.79f, 93.32f, -63.03f,
                    45.79f};
    Matrix4 m1(val1);
    Matrix4 m2(val2);
    m1 -= m2;
    EXPECT_NEAR(m1.m00, -82.17f, 1e-5f);
    EXPECT_NEAR(m1.m01, -101.56f, 1e-5f);
    EXPECT_NEAR(m1.m02, -61.81f, 1e-5f);
    EXPECT_NEAR(m1.m03, -39.86f, 1e-5f);
    EXPECT_NEAR(m1.m10, 169.73999f, 1e-5f);
    EXPECT_NEAR(m1.m11, -69.03f, 1e-5f);
    EXPECT_NEAR(m1.m12, 127.39f, 1e-5f);
    EXPECT_NEAR(m1.m13, 73.73f, 1e-5f);
    EXPECT_NEAR(m1.m20, -33.75f, 1e-5f);
    EXPECT_NEAR(m1.m21, -127.16f, 1e-5f);
    EXPECT_NEAR(m1.m22, 86.81f, 1e-5f);
    EXPECT_NEAR(m1.m23, 68.04f, 1e-5f);
    EXPECT_NEAR(m1.m30, -111.38f, 1e-5f);
    EXPECT_NEAR(m1.m31, -31.11f, 1e-5f);
    EXPECT_NEAR(m1.m32, 136.92f, 1e-5f);
    EXPECT_NEAR(m1.m33, -74.83f, 1e-5f);
}

SPECTRE_TEST(Matrix4, sub_inline)
{
    float val1[] = {-20.64f, -25.69f, -17.56f, -97.15f, 88.28f, 28.07f, 65.32f,
                    46.34f,
                    1.19f, -66.15f, 92.73f, -3.68f, -20.59f, 62.21f, 73.89f,
                    -29.04f};
    float val2[] = {61.53f, 75.87f, 44.25f, -57.29f, -81.46f, 97.1f, -62.07f,
                    -27.39f,
                    34.94f, 61.01f, 5.92f, -71.72f, 90.79f, 93.32f, -63.03f,
                    45.79f};
    Matrix4 m1(val1);
    Matrix4 m2(val2);
    Matrix4 out;
    sub(&m1, &m2, &out);
    EXPECT_NEAR(out.m00, -82.17f, 1e-5f);
    EXPECT_NEAR(out.m01, -101.56f, 1e-5f);
    EXPECT_NEAR(out.m02, -61.81f, 1e-5f);
    EXPECT_NEAR(out.m03, -39.86f, 1e-5f);
    EXPECT_NEAR(out.m10, 169.73999f, 1e-5f);
    EXPECT_NEAR(out.m11, -69.03f, 1e-5f);
    EXPECT_NEAR(out.m12, 127.39f, 1e-5f);
    EXPECT_NEAR(out.m13, 73.73f, 1e-5f);
    EXPECT_NEAR(out.m20, -33.75f, 1e-5f);
    EXPECT_NEAR(out.m21, -127.16f, 1e-5f);
    EXPECT_NEAR(out.m22, 86.81f, 1e-5f);
    EXPECT_NEAR(out.m23, 68.04f, 1e-5f);
    EXPECT_NEAR(out.m30, -111.38f, 1e-5f);
    EXPECT_NEAR(out.m31, -31.11f, 1e-5f);
    EXPECT_NEAR(out.m32, 136.92f, 1e-5f);
    EXPECT_NEAR(out.m33, -74.83f, 1e-5f);
}

SPECTRE_TEST(Matrix4, mul_noinline)
{
    float val1[] = {46.3f, 6.5f, -84.39f, 6.06f, 91.72f, 78.04f, -64.94f,
                    32.07f,
                    -59.33f, -78.26f, 54.08f, -73.42f, -27.12f, 4.49f, 69.9f,
                    91.19f};
    float val2[] = {-52.91f, 12.02f, -58.9f, 29.93f, -16.45f, 78.46f, 19.49f,
                    27.82f,
                    63.5f, 74.75f, 51.43f, 8.44f, 15.54f, 25.59f, 73.89f,
                    -9.28f};
    Matrix4 m1(val1);
    Matrix4 m2(val2);
    Matrix4 out = m1*m2;
    EXPECT_NEAR(out.m00, -7821.25048f, 1e-5f);
    EXPECT_NEAR(out.m01, -5086.56104f, 1e-5f);
    EXPECT_NEAR(out.m02, -6492.78906f, 1e-5f);
    EXPECT_NEAR(out.m03, 798.100586f, 1e-5f);
    EXPECT_NEAR(out.m10, -9761.98535f, 1e-5f);
    EXPECT_NEAR(out.m11, 3191.89941f, 1e-5f);
    EXPECT_NEAR(out.m12, -4851.52051f, 1e-5f);
    EXPECT_NEAR(out.m13, 4070.54907f, 1e-5f);
    EXPECT_NEAR(out.m20, 6719.66064f, 1e-5f);
    EXPECT_NEAR(out.m21, -4689.76367f, 1e-5f);
    EXPECT_NEAR(out.m22, -674.419434f, 1e-5f);
    EXPECT_NEAR(out.m23, -2815.16724f, 1e-5f);
    EXPECT_NEAR(out.m30, 7216.80126f, 1e-5f);
    EXPECT_NEAR(out.m31, 7584.87988f, 1e-5f);
    EXPECT_NEAR(out.m32, 12017.8643f, 1e-5f);
    EXPECT_NEAR(out.m33, -943.077087f, 1e-5f);
}

SPECTRE_TEST(Matrix4, mul_this)
{
    float val1[] = {46.3f, 6.5f, -84.39f, 6.06f, 91.72f, 78.04f, -64.94f,
                    32.07f,
                    -59.33f, -78.26f, 54.08f, -73.42f, -27.12f, 4.49f, 69.9f,
                    91.19f};
    float val2[] = {-52.91f, 12.02f, -58.9f, 29.93f, -16.45f, 78.46f, 19.49f,
                    27.82f,
                    63.5f, 74.75f, 51.43f, 8.44f, 15.54f, 25.59f, 73.89f,
                    -9.28f};
    Matrix4 m1(val1);
    Matrix4 m2(val2);
    m1 *= m2;
    EXPECT_NEAR(m1.m00, -7821.25048f, 1e-5f);
    EXPECT_NEAR(m1.m01, -5086.56104f, 1e-5f);
    EXPECT_NEAR(m1.m02, -6492.78906f, 1e-5f);
    EXPECT_NEAR(m1.m03, 798.100586f, 1e-5f);
    EXPECT_NEAR(m1.m10, -9761.98535f, 1e-5f);
    EXPECT_NEAR(m1.m11, 3191.89941f, 1e-5f);
    EXPECT_NEAR(m1.m12, -4851.52051f, 1e-5f);
    EXPECT_NEAR(m1.m13, 4070.54907f, 1e-5f);
    EXPECT_NEAR(m1.m20, 6719.66064f, 1e-5f);
    EXPECT_NEAR(m1.m21, -4689.76367f, 1e-5f);
    EXPECT_NEAR(m1.m22, -674.419434f, 1e-5f);
    EXPECT_NEAR(m1.m23, -2815.16724f, 1e-5f);
    EXPECT_NEAR(m1.m30, 7216.80126f, 1e-5f);
    EXPECT_NEAR(m1.m31, 7584.87988f, 1e-5f);
    EXPECT_NEAR(m1.m32, 12017.8643f, 1e-5f);
    EXPECT_NEAR(m1.m33, -943.077087f, 1e-5f);
}

SPECTRE_TEST(Matrix4, mul_inline)
{
    float val1[] = {46.3f, 6.5f, -84.39f, 6.06f, 91.72f, 78.04f, -64.94f,
                    32.07f, -59.33f, -78.26f, 54.08f, -73.42f, -27.12f, 4.49f,
                    69.9f, 91.19f};
    float val2[] = {-52.91f, 12.02f, -58.9f, 29.93f, -16.45f, 78.46f, 19.49f,
                    27.82f, 63.5f, 74.75f, 51.43f, 8.44f, 15.54f, 25.59f,
                    73.89f, -9.28f};
    Matrix4 m1(val1);
    Matrix4 m2(val2);
    Matrix4 out;
    mul(&m1, &m2, &out);
    EXPECT_NEAR(out.m00, -7821.25048f, 1e-5f);
    EXPECT_NEAR(out.m01, -5086.56104f, 1e-5f);
    EXPECT_NEAR(out.m02, -6492.78906f, 1e-5f);
    EXPECT_NEAR(out.m03, 798.100586f, 1e-5f);
    EXPECT_NEAR(out.m10, -9761.98535f, 1e-5f);
    EXPECT_NEAR(out.m11, 3191.89941f, 1e-5f);
    EXPECT_NEAR(out.m12, -4851.52051f, 1e-5f);
    EXPECT_NEAR(out.m13, 4070.54907f, 1e-5f);
    EXPECT_NEAR(out.m20, 6719.66064f, 1e-5f);
    EXPECT_NEAR(out.m21, -4689.76367f, 1e-5f);
    EXPECT_NEAR(out.m22, -674.419434f, 1e-5f);
    EXPECT_NEAR(out.m23, -2815.16724f, 1e-5f);
    EXPECT_NEAR(out.m30, 7216.80126f, 1e-5f);
    EXPECT_NEAR(out.m31, 7584.87988f, 1e-5f);
    EXPECT_NEAR(out.m32, 12017.8643f, 1e-5f);
    EXPECT_NEAR(out.m33, -943.077087f, 1e-5f);
}

SPECTRE_TEST(Matrix4, equal)
{
    float val1[] = {59.09f, -8.73f, -19.45f, 88.6f, 85.6f, -67.18f, 31.89f,
                    -71.7f,
                    40.15f, 38.28f, 48.01f, -73.72f, 37.04f, 34.6f, -46.98f,
                    -44.3f};
    float val2[] = {-20.64f, -25.69f, -17.56f, -97.15f, 88.28f, 28.07f, 65.32f,
                    46.34f,
                    1.19f, -66.15f, 92.73f, -3.68f, -20.59f, 62.21f, 73.89f,
                    -29.04f};
    Matrix4 m1(val1);
    Matrix4 m2(val2);

    //asserting M1 == M1 and M1 != M2
    EXPECT_TRUE(m1 == m1);
    EXPECT_FALSE(m1 == m2);

    //asserting M1 * M1^-1 == identity
    Matrix4 inverse;
    m1.inverse(&inverse);
    m1 *= inverse;
    Matrix4 identity;
    identity.set_identity();
    EXPECT_TRUE(m1 == identity);
}

SPECTRE_TEST(Matrix4, not_equal)
{
    float val1[] = {59.09f, -8.73f, -19.45f, 88.6f, 85.6f, -67.18f, 31.89f,
                    -71.7f,
                    40.15f, 38.28f, 48.01f, -73.72f, 37.04f, 34.6f, -46.98f,
                    -44.3f};
    float val2[] = {-20.64f, -25.69f, -17.56f, -97.15f, 88.28f, 28.07f, 65.32f,
                    46.34f,
                    1.19f, -66.15f, 92.73f, -3.68f, -20.59f, 62.21f, 73.89f,
                    -29.04f};
    Matrix4 m1(val1);
    Matrix4 m2(val2);

    //asserting M1 == M1 and M1 != M2
    EXPECT_FALSE(m1 != m1);
    EXPECT_TRUE(m1 != m2);

    //asserting M1 * M1^-1 == identity
    Matrix4 inverse;
    m1.inverse(&inverse);
    m1 *= inverse;
    Matrix4 identity;
    identity.set_identity();
    EXPECT_FALSE(m1 != identity);
}

SPECTRE_TEST(Matrix4, transform_point3)
{
    //no w component
    Point3 p(1, 1, 1);
    Matrix4 m;
    m.set_scale(3);
    p = m*p;
    EXPECT_EQ(p.x, 3.f);
    EXPECT_EQ(p.y, 3.f);
    EXPECT_EQ(p.z, 3.f);

    //with w component, a bit cheated but otherwise I'll need camera tests
    p = Point3(0, 1, 1);
    m.set_translation(Vec3(0, -1, 2.5));
    m.m30 = 1.f;
    m.m32 = 1.f;
    p = m*p;
    EXPECT_EQ(p.x, 0.f);
    EXPECT_EQ(p.y, 0.f);
    EXPECT_EQ(p.z, 3.5f/2.f);
}

SPECTRE_TEST(Matrix4, transform_vec3)
{
    //scale
    Vec3 p(1, 1, 1);
    Matrix4 m;
    m.set_scale(3);
    p = m*p;
    EXPECT_EQ(p.x, 3.f);
    EXPECT_EQ(p.y, 3.f);
    EXPECT_EQ(p.z, 3.f);

    //translation should leave vector unaffected
    p = Vec3(0, 1, 1);
    m.set_translation(Vec3(0, -1, 2.5));
    m.m30 = 1.f;
    m.m32 = 1.f;
    p = m*p;
    EXPECT_EQ(p.x, 0.f);
    EXPECT_EQ(p.y, 1.f);
    EXPECT_EQ(p.z, 1.f);
}

SPECTRE_TEST(Matrix4, transform_ray)
{
    Point3 p = Point3(0, 0, 0);
    Vec3 v = Vec3(0, 1, 0);
    Ray r(p, v);
    Matrix4 m;
    m.set_translation(Vec3(0, -1, 2.5));

    p = m*p;
    v = m*v;
    r = m*r;
    //assert that transforming a ray is exactly like transforming origin and
    //direction separately
    EXPECT_TRUE(r.origin == p);
    EXPECT_TRUE(r.direction == v);
}

SPECTRE_TEST(Matrix4, transform_normal_inline)
{
    //unchanged
    Normal n(0, 0, 1);
    Matrix4 trans;
    Matrix4 inv_trans;
    trans.set_translation(Vec3(1, 1, 1));
    trans.inverse(&inv_trans);
    Normal transformed = transform_normal(n, &inv_trans);
    EXPECT_EQ(transformed.x, 0.f);
    EXPECT_EQ(transformed.y, 0.f);
    EXPECT_EQ(transformed.z, 1.f);

    //rotation 90 degree right
    Normal n2(0, 0, 1);
    trans.set_rotate_y(ONE_PI/2.f);
    trans.inverse(&inv_trans);
    transformed = transform_normal(n, &inv_trans);
    EXPECT_NEAR(transformed.x, 1, 1e-5f);
    EXPECT_NEAR(transformed.y, 0, 1e-5f);
    EXPECT_NEAR(transformed.z, 0, 1e-5f);
}

SPECTRE_TEST_END(Matrix4)
