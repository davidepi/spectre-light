
#include <gtest/gtest.h>


#include "geometry/vec2.hpp"
#include "utility/utility.hpp"
#include <climits>
#include <math.h>
#define EPSILON 1E-5f

TEST(Vec2,Empty)
{

}

TEST(Vec2,empty_constructor)
{
    Vec2 v;
    EXPECT_EQ(v.x,0.0f);
    EXPECT_EQ(v.y,0.0f);
}

TEST(Vec2,given_constructor)
{
    Vec2 v(1.0, 0.0);
    EXPECT_EQ(v.x, 1.0f);
    EXPECT_EQ(v.y, 0.0f);

    errors_count[ERROR_INDEX] = 0;
    Vec2 nanx(NAN,1.f);
    Vec2 nany(1.f,NAN);
    Vec2 infx(INFINITY,1.f);
    Vec2 infy(1.f,INFINITY);
    EXPECT_EQ(errors_count[ERROR_INDEX], 4);
    errors_count[ERROR_INDEX] = 0;
}

TEST(Vec2,same_value_constructor)
{
    Vec2 v(1.0);
    EXPECT_EQ(v.x, 1.0f);
    EXPECT_EQ(v.y, v.x);

    errors_count[ERROR_INDEX] = 0;
    Vec2 nan(NAN);
    Vec2 inf(INFINITY);
    EXPECT_EQ(errors_count[ERROR_INDEX], 2);
    errors_count[ERROR_INDEX] = 0;
}

TEST(Vec2,array_constructor)
{
    float array[] = {1.2f,1.5f};
    Vec2 v(array);
    EXPECT_EQ(v.x, array[0]);
    EXPECT_EQ(v.y, array[1]);

    //NaN checks
    errors_count[ERROR_INDEX] = 0;
    float array1[] = {NAN,1.5f};
    float array2[] = {1.5f,NAN};
    float array3[] = {INFINITY,1.5f};
    float array4[] = {1.5f,INFINITY};
    Vec2 v1(array1);
    Vec2 v2(array2);
    Vec2 v3(array3);
    Vec2 v4(array4);
    EXPECT_EQ(errors_count[ERROR_INDEX], 4);
    errors_count[ERROR_INDEX] = 0;

    //null pointer
    float* arr = NULL;
    errors_count[WARNING_INDEX] = 0;
    v = Vec2(arr);
    EXPECT_EQ(v.x, 0.0f);
    EXPECT_EQ(v.y, 0.0f);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
}

TEST(Vec2,clone)
{
    Vec2 v(-83.27705,79.29129);
    Vec2 v2 = v;

    EXPECT_EQ(v.x, v2.x);
    EXPECT_EQ(v.y, v2.y);
}

TEST(Vec2,dot)
{
    Vec2 v(1,2);
    Vec2 v2(4,-5);
    EXPECT_EQ(v.dot(v2),-6);

    Vec2 v3(6,-1);
    Vec2 v4(4,18);
    EXPECT_EQ(v3.dot(v4),6);

    Vec2 v5(6,-1);
    Vec2 v6(4,24);
    EXPECT_EQ(v5.dot(v6),0);
}

TEST(Vec2,length)
{
    Vec2 v(-15,-2);
    float length = v.length();
    EXPECT_FLOAT_EQ(length,15.1327459504f);

    Vec2 v1(-32,-53);
    EXPECT_EQ(v1.lengthSquared(),3833);

    EXPECT_EQ((int)(v1.length()*v1.length()),v1.lengthSquared());

    Vec2 v2;
    EXPECT_EQ(v2.length(), 0);
}

TEST(Vec2,normalize)
{
    Vec2 v1(3,1);
    EXPECT_EQ(v1.length(),3.1622776602f);
    EXPECT_FALSE(v1.isNormalized());

    Vec2 v2 = normalize(v1);

    v1.normalize();
    EXPECT_EQ(v1.x,v2.x);
    EXPECT_EQ(v1.y,v2.y);
    EXPECT_TRUE(v1.isNormalized());
    EXPECT_TRUE(v2.isNormalized());

    errors_count[CRITICAL_INDEX] = 0;
    Vec2 vzero;
    vzero.normalize();
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Vec2,toArray)
{
    Vec2 v(0,10);
    float f[3];
    v.toArray(f);

    EXPECT_EQ(v.x, f[0]);
    EXPECT_EQ(v.y, f[1]);
}

TEST(Vec2,toString)
{
    Vec2 v(0,1);
    char* str = v.toString();
    EXPECT_EQ(strcmp(str,"vec2(0.000000, 1.000000)"),0);
    free(str);
}

TEST(Vec2,sum_vector)
{
    Vec2 v1(1.f,2.f);
    Vec2 v2(4.f,5.5f);

    Vec2 res = v1 + v2;
    EXPECT_FLOAT_EQ(res.x, 5.f);
    EXPECT_FLOAT_EQ(res.y, 7.5f);
}

TEST(Vec2,sum_float)
{
    Vec2 v1(1.f,2.65f);
    float f= -0.75;

    Vec2 res = v1 + f;
    EXPECT_FLOAT_EQ(res.x, 0.25f);
    EXPECT_FLOAT_EQ(res.y, 1.9f);
}

TEST(Vec2,sum_vector_this)
{
    Vec2 v1(1.f,2.f);
    Vec2 v2(4.f,5.5f);

    v1 += v2;
    EXPECT_FLOAT_EQ(v1.x, 5.f);
    EXPECT_FLOAT_EQ(v1.y, 7.5f);
}

TEST(Vec2,sum_float_this)
{
    Vec2 v1(3.3,1.2);
    float f = 0.5;
    v1 += f;
    EXPECT_FLOAT_EQ(v1.x, 3.8f);
    EXPECT_FLOAT_EQ(v1.y, 1.7f);
}

TEST(Vec2,sub_vector)
{
    Vec2 v1(7.f,6.5f);
    Vec2 v2(7.f,5.3f);

    Vec2 res = v1 - v2;
    EXPECT_FLOAT_EQ(res.x, 0.f);
    EXPECT_FLOAT_EQ(res.y, 1.2f);
}

TEST(Vec2,sub_float)
{
    Vec2 v1(3.3f,1.2f);
    float f = 0.5;
    Vec2 res = v1 - f;
    EXPECT_FLOAT_EQ(res.x, 2.8f);
    EXPECT_FLOAT_EQ(res.y, 0.7f);
}

TEST(Vec2,sub_vector_this)
{
    Vec2 v1(5,3);
    Vec2 v2(7,3.3);

    v1 -= v2;
    EXPECT_FLOAT_EQ(v1.x, -2.f);
    EXPECT_FLOAT_EQ(v1.y, -.3f);
}

TEST(Vec2,sub_float_this)
{
    Vec2 v1(3.3,1.2);
    float f = 0.5;
    v1 -= f;
    EXPECT_FLOAT_EQ(v1.x, 2.8f);
    EXPECT_FLOAT_EQ(v1.y, .7f);
}

TEST(Vec2,mul_vector)
{
    Vec2 v1(1.2,5.6);
    Vec2 v2(1.4,45);

    Vec2 res = v1 * v2;
    EXPECT_FLOAT_EQ(res.x, 1.68f);
    EXPECT_FLOAT_EQ(res.y, 252);
}

TEST(Vec2,mul_float)
{
    Vec2 v1(3.3f,1.2f);
    float f = 7.33f;
    Vec2 res = v1 * f;
    EXPECT_FLOAT_EQ(res.x, 24.189f);
    EXPECT_FLOAT_EQ(res.y, 8.796f);
}

TEST(Vec2,mul_vector_this)
{
    Vec2 v1(1,0.5);
    Vec2 v2(2,3);

    v1 *= v2;
    EXPECT_FLOAT_EQ(v1.x, 2.f);
    EXPECT_FLOAT_EQ(v1.y, 1.5f);
}

TEST(Vec2,mul_float_this)
{
    Vec2 v1(3.3,1.2);
    float f = -53.477;
    v1 *= f;
    EXPECT_FLOAT_EQ(v1.x, -176.4741f);
    EXPECT_FLOAT_EQ(v1.y, -64.1724f);
}

TEST(Vec2,div_vector)
{
    Vec2 v1(7.f,8.4f);
    Vec2 v2(-6.f,-0.4f);
    Vec2 res = v1 / v2;
    EXPECT_FLOAT_EQ(res.x, -1.1666666667f);
    EXPECT_FLOAT_EQ(res.y, -21.f);

    //div by zero
    errors_count[CRITICAL_INDEX] = 0;
    Vec2 vzerox(0,1);
    Vec2 vzeroy(1,0);
    v1/vzerox;
    v1/vzeroy;
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 2);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Vec2,div_float)
{
    Vec2 v1(3.3,1.2);
    float f = 7.33;
    Vec2 res = v1 / f;
    EXPECT_FLOAT_EQ(res.x, 0.4502046385f);
    EXPECT_FLOAT_EQ(res.y, 0.1637107776f);

    errors_count[CRITICAL_INDEX] = 0;
    float zero = 0.f;
    v1/zero;
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Vec2,div_vector_this)
{
    Vec2 v1(1,0.7);
    Vec2 v2(2,3);
    v1 /= v2;
    EXPECT_FLOAT_EQ(v1.x, 0.5f);
    EXPECT_FLOAT_EQ(v1.y, 0.2333333333f);

    Vec2 vzerox(0,1);
    Vec2 vzeroy(1,0);
    errors_count[CRITICAL_INDEX] = 0;
    v2 = v1;
    v2/=vzerox;
    v2 = v1;
    v2/=vzeroy;
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 2);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Vec2,div_float_this)
{
    Vec2 v1(3.3,1.2);
    float f = -53.477;
    v1 /= f;
    EXPECT_FLOAT_EQ(v1.x, -0.061708772f);
    EXPECT_FLOAT_EQ(v1.y, -0.02243955345f);

    errors_count[CRITICAL_INDEX] = 0;
    float zero = 0.f;
    v1/=zero;
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Vec2,not_vector)
{
    Vec2 v1(3,4.55556);
    Vec2 res = !v1;
    EXPECT_EQ(res.x, -v1.x);
    EXPECT_EQ(res.y, -v1.y);
}

TEST(Vec2,minus_vector)
{
    Vec2 v1(6,8.5);
    Vec2 res = -v1;
    EXPECT_EQ(res.x, -v1.x);
    EXPECT_EQ(res.y, -v1.y);
}

TEST(Vec2,equal_vector)
{
    //[X VALUE] [Y VALUE] [Z VALUE]
    //[F] [F]
    Vec2 v1(1.4,2.5);
    Vec2 v2(4.9,-5.8);
    bool res = v1==v2;
    EXPECT_EQ(res, false);

    //[T] [F]
    v1 = Vec2(4.9,2.5);
    v2 = Vec2(4.9,-5.8);
    res = v1==v2;
    EXPECT_EQ(res, false);

    //[F] [T]
    v1 = Vec2(1.2,-5.8);
    v2 = Vec2(4.9,-5.8);
    res = v1==v2;
    EXPECT_EQ(res, false);

    //[T] [T]
    v1 = Vec2(4.9,2.5);
    v2 = Vec2(4.9,2.5);
    res = v1==v2;
    EXPECT_EQ(res, true);
}

TEST(Vec2,not_equal_vector)
{
    //[X VALUE] [Y VALUE] [Z VALUE]
    //[F] [F]
    Vec2 v1(1.4,2.5);
    Vec2 v2(4.9,-5.8);
    bool res = v1!=v2;
    EXPECT_EQ(res, true);

    //[T] [F]
    v1 = Vec2(4.9,2.5);
    v2 = Vec2(4.9,-5.8);
    res = v1!=v2;
    EXPECT_EQ(res, true);

    //[F] [T]
    v1 = Vec2(1.2,-5.8);
    v2 = Vec2(4.9,-5.8);
    res = v1!=v2;
    EXPECT_EQ(res, true);

    //[T] [T]
    v1 = Vec2(5.8,6.7);
    v2 = Vec2(5.8,6.7);
    res = v1!=v2;
    EXPECT_EQ(res, false);
}

TEST(Vec2,clamp)
{
    Vec2 sample(4.9,-5.8);
    Vec2 v1 = sample;
    Vec2 min(-10,-10);
    Vec2 max(10,10);

    //in range x
    v1.clamp(min,max);
    EXPECT_EQ(v1.x, sample.x);
    //min x
    v1 = sample;
    min.x = 5;
    v1.clamp(min,max);
    EXPECT_EQ(v1.x, min.x);
    min.x = -10;
    //max x
    v1 = sample;
    max.x = 3;
    v1.clamp(min,max);
    EXPECT_EQ(v1.x, max.x);
    max.x = 10;

    //in range y
    v1.clamp(min,max);
    EXPECT_EQ(v1.y, sample.y);
    //min y
    v1 = sample;
    min.y = 5;
    v1.clamp(min,max);
    EXPECT_EQ(v1.y, min.y);
    min.y = -10;
    //max y
    v1 = sample;
    max.y = -6;
    v1.clamp(min,max);
    EXPECT_EQ(v1.y, max.y);
    max.y = 10;
}

TEST(Vec2,saturate)
{
    Vec2 sample(0.9,0.5);
    Vec2 v1 = sample;

    //in range x
    v1.saturate();
    EXPECT_EQ(v1.x, sample.x);
    //min x
    v1 = sample;
    v1.x = -0.1;
    v1.saturate();
    EXPECT_EQ(v1.x, 0.f);
    //max x
    v1 = sample;
    v1.x = 1.5;
    v1.saturate();
    EXPECT_EQ(v1.x, 1.f);

    //in range y
    v1.saturate();
    EXPECT_EQ(v1.y, sample.y);
    //min y
    v1 = sample;
    v1.y = -0.1;
    v1.saturate();
    EXPECT_EQ(v1.y, 0.f);
    //max y
    v1 = sample;
    v1.y = 1.5;
    v1.saturate();
    EXPECT_EQ(v1.y, 1.f);
}

TEST(Vec2,distanceTo)
{
    Vec2 a(1.5f,-2.f);
    Vec2 b(3.7f,2.5f);
    float dist = a.distanceTo(b);
    EXPECT_EQ(5.0089919145f, dist);
}

TEST(Vec2,max)
{
    Vec2 sample(0.5,1.5);
    Vec2 value;
    Vec2 compare;

    //x is max
    value = sample;
    compare = Vec2(0.2f,0.f);
    value.max(compare);
    EXPECT_EQ(value.x, sample.x);
    //x is not max
    value = sample;
    compare = Vec2(1.0,0.f);
    value.max(compare);
    EXPECT_EQ(value.x, compare.x);

    //y is max
    value = sample;
    compare = Vec2(0.f,1.f);
    value.max(compare);
    EXPECT_EQ(value.y,sample.y);
    //y is not max
    value = sample;
    compare = Vec2(0.f,10.f);
    value.max(compare);
    EXPECT_EQ(value.y, compare.y);
}

TEST(Vec2,min)
{
    Vec2 sample(0.5,1.5);
    Vec2 value;
    Vec2 compare;

    //x is max
    value = sample;
    compare = Vec2(0.2f,0.f);
    value.min(compare);
    EXPECT_EQ(value.x, compare.x);
    //x is not max
    value = sample;
    compare = Vec2(1.0,0.f);
    value.min(compare);
    EXPECT_EQ(value.x, sample.x);

    //y is max
    value = sample;
    compare = Vec2(0.f,1.f);
    value.min(compare);
    EXPECT_EQ(value.y,compare.y);
    //y is not max
    value = sample;
    compare = Vec2(0.f,10.f);
    value.min(compare);
    EXPECT_EQ(value.y, sample.y);
}

// ------

TEST(Vec2,inline_dot)
{
    Vec2 v(1,2);
    Vec2 v2(4,-5);
    EXPECT_EQ(dot(v,v2),-6);
}

TEST(Vec2,inline_normalize)
{
    Vec2 v1(3,0);
    EXPECT_FLOAT_EQ(v1.length(),3.f);
    EXPECT_FALSE(v1.isNormalized());

    Vec2 v2 = normalize(v1);

    v1.normalize();
    EXPECT_EQ(v1.x,v2.x);
    EXPECT_EQ(v1.y,v2.y);
    EXPECT_TRUE(v1.isNormalized());
    EXPECT_TRUE(v2.isNormalized());
    EXPECT_EQ(v2.x,1.f);
    EXPECT_EQ(v2.y,0.f);


    errors_count[CRITICAL_INDEX] = 0;
    Vec2 vzero;
    normalize(vzero);
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Vec2,inline_clamp)
{
    Vec2 sample(4.9,-5.8);
    Vec2 v1 = sample;
    Vec2 min(-10,-10);
    Vec2 max(10,10);
    Vec2 out;

    //in range x
    out = clamp(v1,min,max);
    EXPECT_EQ(out.x, sample.x);
    //min x
    v1 = sample;
    min.x = 5;
    out = clamp(v1,min,max);
    EXPECT_EQ(out.x, min.x);
    min.x = -10;
    //max x
    v1 = sample;
    max.x = 3;
    out = clamp(v1,min,max);
    EXPECT_EQ(out.x, max.x);
    max.x = 10;

    //in range y
    out = clamp(v1,min,max);
    EXPECT_EQ(out.y, sample.y);
    //min y
    v1 = sample;
    min.y = 5;
    out = clamp(v1,min,max);
    EXPECT_EQ(out.y, min.y);
    min.y = -10;
    //max y
    v1 = sample;
    max.y = -6;
    out = clamp(v1,min,max);
    EXPECT_EQ(out.y, max.y);
    max.y = 10;
}

TEST(Vec2,inline_saturate)
{
    Vec2 sample(0.9,0.5);
    Vec2 v1 = sample;
    Vec2 out;
    //in range x
    out = saturate(v1);;
    EXPECT_EQ(out.x, sample.x);
    //min x
    v1 = sample;
    v1.x = -0.1;
    out = saturate(v1);;
    EXPECT_EQ(out.x, 0.f);
    //max x
    v1 = sample;
    v1.x = 1.5;
    out = saturate(v1);;
    EXPECT_EQ(out.x, 1.f);

    //in range y
    out = saturate(v1);;
    EXPECT_EQ(out.y, sample.y);
    //min y
    v1 = sample;
    v1.y = -0.1;
    out = saturate(v1);;
    EXPECT_EQ(out.y, 0.f);
    //max y
    v1 = sample;
    v1.y = 1.5;
    out = saturate(v1);;
    EXPECT_EQ(out.y, 1.f);
}

TEST(Vec2,inline_distance)
{
    Vec2 a(1.5f,-2.f);
    Vec2 b(3.7f,2.5f);
    float dist = distance(a,b);
    EXPECT_EQ(5.0089919145f, dist);
}

TEST(Vec2,inline_max)
{
    Vec2 sample(0.5,1.5);
    Vec2 value;
    Vec2 compare;
    Vec2 out;

    //x is max
    value = sample;
    compare = Vec2(0.2f,0.f);
    out = max(value,compare);;
    EXPECT_EQ(out.x, sample.x);
    //x is not max
    value = sample;
    compare = Vec2(1.0,0.f);
    out = max(value,compare);;
    EXPECT_EQ(out.x, compare.x);

    //y is max
    value = sample;
    compare = Vec2(0.f,1.f);
    out = max(value,compare);;
    EXPECT_EQ(out.y,sample.y);
    //y is not max
    value = sample;
    compare = Vec2(0.f,10.f);
    out = max(value,compare);;
    EXPECT_EQ(out.y, compare.y);
}

TEST(Vec2,inline_min)
{
    Vec2 sample(0.5,1.5);
    Vec2 value;
    Vec2 compare;
    Vec2 out;

    //x is max
    value = sample;
    compare = Vec2(0.2f,0.f);
    out = min(value,compare);;
    EXPECT_EQ(out.x, compare.x);
    //x is not max
    value = sample;
    compare = Vec2(1.0,0.f);
    out = min(value,compare);;
    EXPECT_EQ(out.x, sample.x);

    //y is max
    value = sample;
    compare = Vec2(0.f,1.f);
    out = min(value,compare);;
    EXPECT_EQ(out.y,compare.y);
    //y is not max
    value = sample;
    compare = Vec2(0.f,10.f);
    out = min(value,compare);;
    EXPECT_EQ(out.y, sample.y);
}

