
#include <gtest/gtest.h>


#include "geometry/matrix4.hpp"
#include "utility/utility.hpp"
#include <climits>
#include <cmath>
#define EPSILON 1E-5f

TEST(Matrix4,float_constructor)
{
    float vals[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    Matrix4 m(vals);
    EXPECT_EQ(m.m00,vals[0]);
    EXPECT_EQ(m.m01,vals[1]);
    EXPECT_EQ(m.m02,vals[2]);
    EXPECT_EQ(m.m03,vals[3]);
    EXPECT_EQ(m.m10,vals[4]);
    EXPECT_EQ(m.m11,vals[5]);
    EXPECT_EQ(m.m12,vals[6]);
    EXPECT_EQ(m.m13,vals[7]);
    EXPECT_EQ(m.m20,vals[8]);
    EXPECT_EQ(m.m21,vals[9]);
    EXPECT_EQ(m.m22,vals[10]);
    EXPECT_EQ(m.m23,vals[11]);
    EXPECT_EQ(m.m30,vals[12]);
    EXPECT_EQ(m.m31,vals[13]);
    EXPECT_EQ(m.m32,vals[14]);
    EXPECT_EQ(m.m33,vals[15]);

    errors_count[WARNING_INDEX] = 0;
    float* nullval = NULL;
    Matrix4 m2(nullval);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
}

TEST(Matrix4,toString)
{
    float vals[16] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
    Matrix4 m(vals);
    char* output = m.toString();
    EXPECT_EQ(strcmp(output,
                          "Matrix4[0.000000, 1.000000, 0.000000, 1.000000]\n"\
                          "       [0.000000, 1.000000, 0.000000, 1.000000]\n"\
                          "       [0.000000, 1.000000, 0.000000, 1.000000]\n"\
                          "       [0.000000, 1.000000, 0.000000, 1.000000]\n")
                   ,0);
}

TEST(Matrix4,toArray)
{
    float vals[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    Matrix4 m(vals);
    float res[16];
    m.toArray(res);
    EXPECT_EQ(vals[0],res[0]);
    EXPECT_EQ(vals[1],res[1]);
    EXPECT_EQ(vals[2],res[2]);
    EXPECT_EQ(vals[3],res[3]);
    EXPECT_EQ(vals[4],res[4]);
    EXPECT_EQ(vals[5],res[5]);
    EXPECT_EQ(vals[6],res[6]);
    EXPECT_EQ(vals[7],res[7]);
    EXPECT_EQ(vals[8],res[8]);
    EXPECT_EQ(vals[9],res[9]);
    EXPECT_EQ(vals[10],res[10]);
    EXPECT_EQ(vals[11],res[11]);
    EXPECT_EQ(vals[12],res[12]);
    EXPECT_EQ(vals[13],res[13]);
    EXPECT_EQ(vals[14],res[14]);
    EXPECT_EQ(vals[15],res[15]);
}

TEST(Matrix4,set_zero)
{
    Matrix4 m;
    m.set_zero();
    EXPECT_EQ(m.m00,0);
    EXPECT_EQ(m.m01,0);
    EXPECT_EQ(m.m02,0);
    EXPECT_EQ(m.m03,0);
    EXPECT_EQ(m.m10,0);
    EXPECT_EQ(m.m11,0);
    EXPECT_EQ(m.m12,0);
    EXPECT_EQ(m.m13,0);
    EXPECT_EQ(m.m20,0);
    EXPECT_EQ(m.m21,0);
    EXPECT_EQ(m.m22,0);
    EXPECT_EQ(m.m23,0);
    EXPECT_EQ(m.m30,0);
    EXPECT_EQ(m.m31,0);
    EXPECT_EQ(m.m32,0);
    EXPECT_EQ(m.m33,0);
}

TEST(Matrix4,set_identity)
{
    Matrix4 m;
    m.set_identity();
    EXPECT_EQ(m.m00,1);
    EXPECT_EQ(m.m01,0);
    EXPECT_EQ(m.m02,0);
    EXPECT_EQ(m.m03,0);
    EXPECT_EQ(m.m10,0);
    EXPECT_EQ(m.m11,1);
    EXPECT_EQ(m.m12,0);
    EXPECT_EQ(m.m13,0);
    EXPECT_EQ(m.m20,0);
    EXPECT_EQ(m.m21,0);
    EXPECT_EQ(m.m22,1);
    EXPECT_EQ(m.m23,0);
    EXPECT_EQ(m.m30,0);
    EXPECT_EQ(m.m31,0);
    EXPECT_EQ(m.m32,0);
    EXPECT_EQ(m.m33,1);
}

TEST(Matrix4,set_translation)
{
    Matrix4 m;
    Vec3 trans(-87.39175f,8.35182f,-93.43325f);
    m.set_translation(trans);
    EXPECT_EQ(m.m00,1);
    EXPECT_EQ(m.m01,0);
    EXPECT_EQ(m.m02,0);
    EXPECT_EQ(m.m03,trans.x);
    EXPECT_EQ(m.m10,0);
    EXPECT_EQ(m.m11,1);
    EXPECT_EQ(m.m12,0);
    EXPECT_EQ(m.m13,trans.y);
    EXPECT_EQ(m.m20,0);
    EXPECT_EQ(m.m21,0);
    EXPECT_EQ(m.m22,1);
    EXPECT_EQ(m.m23,trans.z);
    EXPECT_EQ(m.m30,0);
    EXPECT_EQ(m.m31,0);
    EXPECT_EQ(m.m32,0);
    EXPECT_EQ(m.m33,1);
}

TEST(Matrix4,set_scale_uniform)
{
    Matrix4 m;
    float magnitude = 73.35321f;
    m.set_scale(magnitude);
    EXPECT_EQ(m.m00,magnitude);
    EXPECT_EQ(m.m01,0);
    EXPECT_EQ(m.m02,0);
    EXPECT_EQ(m.m03,0);
    EXPECT_EQ(m.m10,0);
    EXPECT_EQ(m.m11,magnitude);
    EXPECT_EQ(m.m12,0);
    EXPECT_EQ(m.m13,0);
    EXPECT_EQ(m.m20,0);
    EXPECT_EQ(m.m21,0);
    EXPECT_EQ(m.m22,magnitude);
    EXPECT_EQ(m.m23,0);
    EXPECT_EQ(m.m30,0);
    EXPECT_EQ(m.m31,0);
    EXPECT_EQ(m.m32,0);
    EXPECT_EQ(m.m33,1);
}

TEST(Matrix4,set_scale_non_uniform)
{
    Matrix4 m;
    Vec3 magnitude(41.24096,-93.12313,31.83295);
    m.set_scale(magnitude);
    EXPECT_EQ(m.m00,magnitude.x);
    EXPECT_EQ(m.m01,0);
    EXPECT_EQ(m.m02,0);
    EXPECT_EQ(m.m03,0);
    EXPECT_EQ(m.m10,0);
    EXPECT_EQ(m.m11,magnitude.y);
    EXPECT_EQ(m.m12,0);
    EXPECT_EQ(m.m13,0);
    EXPECT_EQ(m.m20,0);
    EXPECT_EQ(m.m21,0);
    EXPECT_EQ(m.m22,magnitude.z);
    EXPECT_EQ(m.m23,0);
    EXPECT_EQ(m.m30,0);
    EXPECT_EQ(m.m31,0);
    EXPECT_EQ(m.m32,0);
    EXPECT_EQ(m.m33,1);
}

TEST(Matrix4,set_rotate_x)
{
    Matrix4 m;
    float val = 3.f/4.f*ONE_PI;
    m.set_rotate_x(val);
    EXPECT_EQ(m.m00,1);
    EXPECT_EQ(m.m01,0);
    EXPECT_EQ(m.m02,0);
    EXPECT_EQ(m.m03,0);
    EXPECT_EQ(m.m10,0);
    EXPECT_FLOAT_EQ(m.m11,-1.f/sqrtf(2));
    EXPECT_FLOAT_EQ(m.m12,-1.f/sqrtf(2));
    EXPECT_EQ(m.m13,0);
    EXPECT_EQ(m.m20,0);
    EXPECT_FLOAT_EQ(m.m21,1.f/sqrtf(2));
    EXPECT_FLOAT_EQ(m.m22,-1.f/sqrtf(2));
    EXPECT_EQ(m.m23,0);
    EXPECT_EQ(m.m30,0);
    EXPECT_EQ(m.m31,0);
    EXPECT_EQ(m.m32,0);
    EXPECT_EQ(m.m33,1);
}

TEST(Matrix4,set_rotate_y)
{
    Matrix4 m;
    float val = 3.f/4.f*ONE_PI;
    m.set_rotate_y(val);
    EXPECT_FLOAT_EQ(m.m00,-1.f/sqrtf(2));
    EXPECT_EQ(m.m01,0);
    EXPECT_FLOAT_EQ(m.m02,1.f/sqrtf(2));
    EXPECT_EQ(m.m03,0);
    EXPECT_EQ(m.m10,0);
    EXPECT_EQ(m.m11,1);
    EXPECT_EQ(m.m12,0);
    EXPECT_EQ(m.m13,0);
    EXPECT_FLOAT_EQ(m.m20,-1.f/sqrtf(2));
    EXPECT_EQ(m.m21,0);
    EXPECT_FLOAT_EQ(m.m22,-1.f/sqrtf(2));
    EXPECT_EQ(m.m23,0);
    EXPECT_EQ(m.m30,0);
    EXPECT_EQ(m.m31,0);
    EXPECT_EQ(m.m32,0);
    EXPECT_EQ(m.m33,1);
}

TEST(Matrix4,set_rotate_z)
{
    Matrix4 m;
    float val = 3.f/4.f*ONE_PI;
    m.set_rotate_z(val);
    EXPECT_FLOAT_EQ(m.m00,-1.f/sqrtf(2));
    EXPECT_FLOAT_EQ(m.m01,-1.f/sqrtf(2));
    EXPECT_EQ(m.m02,0);
    EXPECT_EQ(m.m03,0);
    EXPECT_FLOAT_EQ(m.m10,1.f/sqrtf(2));
    EXPECT_FLOAT_EQ(m.m11,-1.f/sqrtf(2));
    EXPECT_EQ(m.m12,0);
    EXPECT_EQ(m.m13,0);
    EXPECT_EQ(m.m20,0);
    EXPECT_EQ(m.m21,0);
    EXPECT_EQ(m.m22,1);
    EXPECT_EQ(m.m23,0);
    EXPECT_EQ(m.m30,0);
    EXPECT_EQ(m.m31,0);
    EXPECT_EQ(m.m32,0);
    EXPECT_EQ(m.m33,1);
}

