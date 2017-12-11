
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

TEST(Matrix4,lookAt)
{
    //non normalized up
    Vec3 up(1,1,0);
    Point3 pos(1,0,-2);
    Point3 target(0,0,1);
    Matrix4 m;
    errors_count[WARNING_INDEX] = 0;
    m.set_lookAt_inverse(pos, target, up);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;

    //normalized up
    up.normalize();
    m.set_lookAt_inverse(pos, target, up);
    EXPECT_EQ(errors_count[WARNING_INDEX], 0);
    EXPECT_FLOAT_EQ(m.m00,0.688247f);
    EXPECT_FLOAT_EQ(m.m01,0.652929f);
    EXPECT_FLOAT_EQ(m.m02,-0.316228f);
    EXPECT_FLOAT_EQ(m.m03,1.f);
    EXPECT_FLOAT_EQ(m.m10,-0.688247f);
    EXPECT_FLOAT_EQ(m.m11,0.725476f);
    EXPECT_FLOAT_EQ(m.m12,0.f);
    EXPECT_FLOAT_EQ(m.m13,0.f);
    EXPECT_FLOAT_EQ(m.m20,0.229416f);
    EXPECT_FLOAT_EQ(m.m21,0.217643f);
    EXPECT_FLOAT_EQ(m.m22,0.948683f);
    EXPECT_FLOAT_EQ(m.m23,-2.f);
    EXPECT_FLOAT_EQ(m.m30,0.f);
    EXPECT_FLOAT_EQ(m.m31,0.f);
    EXPECT_FLOAT_EQ(m.m32,0.f);
    EXPECT_FLOAT_EQ(m.m33,1.f);
}

TEST(Matrix4,transpose)
{
    float vals[] = {27.9484,-88.37513,-25.05486,0.93192,19.53558,55.46225,
        -92.99693,13.30983,-39.91206,-63.35516,-80.28301,96.89149,-97.99183,
        69.73036,34.27019,58.81281};
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

TEST(Matrix4,inverse)
{
    //invertible
    float vals[] = {44.48,-69.73,62.26,-89.47,-20.59,45.01,-77.12,21.26,3.27,
                    42.29,-62.23,-49.23,6.83,-80.83,18.96,-84.16};
    Matrix4 m(vals);
    Matrix4 out;
    bool res = m.inverse(&out);
    EXPECT_TRUE(res);
    EXPECT_FLOAT_EQ(out.m00,0.05696867986878306f);
    EXPECT_FLOAT_EQ(out.m01,0.06042118741944838f);
    EXPECT_FLOAT_EQ(out.m02,-0.026891372703873692f);
    EXPECT_FLOAT_EQ(out.m03,-0.02956952311205848f);
    EXPECT_FLOAT_EQ(out.m10,-0.016213241351212312f);
    EXPECT_FLOAT_EQ(out.m11,-0.03287692440970072f);
    EXPECT_FLOAT_EQ(out.m12,0.02312255927369855f);
    EXPECT_FLOAT_EQ(out.m13,-0.004594680398068575f);
    EXPECT_FLOAT_EQ(out.m20,-0.020370360928440107f);
    EXPECT_FLOAT_EQ(out.m21,-0.040761643380056015f);
    EXPECT_FLOAT_EQ(out.m22,0.014874897160732165f);
    EXPECT_FLOAT_EQ(out.m23,0.0026574675235824666f);
    EXPECT_FLOAT_EQ(out.m30,0.015605873796566723f);
    EXPECT_FLOAT_EQ(out.m31,0.027296551231286575f);
    EXPECT_FLOAT_EQ(out.m32,-0.021038931695497014f);
    EXPECT_FLOAT_EQ(out.m33,-0.009270273788407236f);

    //non invertible
    //not the best solution, since I would like to try a dirty 0
    //(0.00000000000001 as determinant, for example)
    Matrix4 zero;
    zero.set_zero();
    res = zero.inverse(&out);
    EXPECT_FALSE(res);
}

TEST(Matrix4,get_translation)
{
    Vec3 scale(53.94708,-56.04181,38.21224);
    Vec3 translation(-5.28423,22.63478,22.10424);
    Vec3 rotation(-0.07627,-31.31443,-88.95238);
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

    combined*=mt;
    combined*=mrz;
    combined*=mry;
    combined*=mrx;
    combined*=ms;

    Vec3 extracted = combined.get_translation();
    EXPECT_FLOAT_EQ(extracted.x, translation.x);
    EXPECT_FLOAT_EQ(extracted.y, translation.y);
    EXPECT_FLOAT_EQ(extracted.z, translation.z);
}

TEST(Matrix4,get_scale)
{
    Vec3 scale(37.99025,69.85438,5.79172);
    Vec3 translation(-17.90241,37.90712,74.85354);
    Vec3 rotation(-20.80442,27.33369,-31.58807);
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

    combined*=mt;
    combined*=mrz;
    combined*=mry;
    combined*=mrx;
    combined*=ms;

    Vec3 extracted = combined.get_scale();
    EXPECT_FLOAT_EQ(extracted.x, scale.x);
    EXPECT_FLOAT_EQ(extracted.y, scale.y);
    EXPECT_FLOAT_EQ(extracted.z, scale.z);
}

