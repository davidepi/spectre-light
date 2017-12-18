
#include <gtest/gtest.h>


#include "geometry/vec3.hpp"
#include "geometry/vec2.hpp"
#include "utility/utility.hpp"
#include <climits>
#define EPSILON 1E-5f

TEST(Normal,Empty)
{

}

TEST(Normal,empty_constructor)
{
    Normal v;
    EXPECT_EQ(v.x,0.0f);
    EXPECT_EQ(v.y,0.0f);
    EXPECT_EQ(v.z,0.0f);
}

TEST(Normal,given_constructor)
{
    Normal v(1.0, 0.0, -1.0);
    EXPECT_EQ(v.x, 1.0f);
    EXPECT_EQ(v.y, 0.0f);
    EXPECT_EQ(v.z, -1.0f);
}

TEST(Normal,same_value_constructor)
{
    float f = 12.5;
    Normal v(f);
    EXPECT_EQ(v.x,f);
    EXPECT_EQ(v.y,f);
    EXPECT_EQ(v.z,f);
}

TEST(Normal,vec2_constructor)
{
    Vec2 v2(1.0f,-1.0f);
    float f = 17.11;
    Normal v3(v2,f);
    EXPECT_EQ(v3.x,v2.x);
    EXPECT_EQ(v3.y,v2.y);
    EXPECT_EQ(v3.z,f);
}

TEST(Normal,array_constructor)
{
    float array[] = {1.2f,1.5f,1.8f};
    Normal v(array);
    EXPECT_EQ(v.x, array[0]);
    EXPECT_EQ(v.y, array[1]);
    EXPECT_EQ(v.z, array[2]);
}

TEST(Normal,array_constructor_null_pointer)
{
    float* array = NULL;
    Normal v(array);
    EXPECT_EQ(v.x, 0.0f);
    EXPECT_EQ(v.y, 0.0f);
    EXPECT_EQ(v.z, 0.0f);
}

TEST(Normal,vec3_constructor)
{
    Vec3 v3(1.0,2.0,3.0);
    Normal n(v3);

    EXPECT_EQ(n.x,v3.x);
    EXPECT_EQ(n.y,v3.y);
    EXPECT_EQ(n.z,v3.z);
}

TEST(Normal,clone)
{
    Normal v(-83.27705,79.29129,-51.32018);
    Normal v2 = v;

    EXPECT_EQ(v.x, v2.x);
    EXPECT_EQ(v.y, v2.y);
    EXPECT_EQ(v.z, v2.z);
}

TEST(Normal,dot)
{
    Normal v(1,2,3);
    Normal v2(4,-5,6);
    EXPECT_EQ(v.dot(v2),12);

    Normal v3(6,-1,3);
    Vec3 v4(4,18,-2);
    EXPECT_EQ(v3.dot(v4),0);

    Normal n1(6,-1,3);
    EXPECT_EQ(v2.dot(n1), 47);
}

TEST(Normal,length)
{
    Normal v(-15,-2,39);
    float length = v.length();
    EXPECT_FLOAT_EQ(length,41.833f);

    Normal v1(-32,-53,23);
    EXPECT_EQ(v1.lengthSquared(),4362);

    EXPECT_FLOAT_EQ(v1.length()*v1.length(),v1.lengthSquared());

    Normal v2;
    EXPECT_EQ(v2.length(), 0);
}

TEST(Normal,normalize)
{
    Normal v1(3,1,2);
    EXPECT_FLOAT_EQ(v1.length(),3.7416575f);
    EXPECT_FALSE(v1.is_normalized());

    Normal v2 = normalize(v1);

    v1.normalize();
    EXPECT_EQ(v1.x,v2.x);
    EXPECT_EQ(v1.y,v2.y);
    EXPECT_EQ(v1.z,v2.z);
    EXPECT_TRUE(v1.is_normalized());
    EXPECT_TRUE(v2.is_normalized());

    errors_count[CRITICAL_INDEX] = 0;
    Normal vzero;
    vzero.normalize();
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Normal,toArray)
{
    Normal v(0,10,-1);
    float f[3];
    v.toArray(f);

    EXPECT_EQ(v.x, f[0]);
    EXPECT_EQ(v.y, f[1]);
    EXPECT_EQ(v.z, f[2]);
}

TEST(Normal,toString)
{
    Normal v(0,1,0);
    char* str = v.toString();
    EXPECT_EQ(strcmp(str,"Normal(0.000000, 1.000000, 0.000000)"),0);
    free(str);
}

TEST(Normal,sum_vector)
{
    Normal v1(1,2,3);
    Normal v2(4,5.5,-3);

    Normal res = v1 + v2;
    EXPECT_GE(res.x,5-EPSILON);
    EXPECT_LE(res.x,5+EPSILON);
    EXPECT_GE(res.y,7.5-EPSILON);
    EXPECT_LE(res.y,7.5+EPSILON);
    EXPECT_GE(res.z,0-EPSILON);
    EXPECT_LE(res.z,0+EPSILON);
}

TEST(Normal,sum_float)
{
    Normal v1(1,2,-3);
    float f= -0.75;

    Normal res = v1 + f;
    EXPECT_GE(res.x,0.25-EPSILON);
    EXPECT_LE(res.x,0.25+EPSILON);
    EXPECT_GE(res.y,1.25-EPSILON);
    EXPECT_LE(res.y,1.25+EPSILON);
    EXPECT_GE(res.z,-3.75-EPSILON);
    EXPECT_LE(res.z,-3.75+EPSILON);
}

TEST(Normal,sum_vector_this)
{
    Normal v1(1,2,3);
    Normal v2(4,5.5,-3);

    v1 += v2;
    EXPECT_GE(v1.x,5-EPSILON);
    EXPECT_LE(v1.x,5+EPSILON);
    EXPECT_GE(v1.y,7.5-EPSILON);
    EXPECT_LE(v1.y,7.5+EPSILON);
    EXPECT_GE(v1.z,0-EPSILON);
    EXPECT_LE(v1.z,0+EPSILON);
}

TEST(Normal,sum_float_this)
{
    Normal v1(3.3,1.2,-1.5);
    float f = 0.5;
    v1 += f;
    EXPECT_GE(v1.x,3.8-EPSILON);
    EXPECT_LE(v1.x,3.8+EPSILON);
    EXPECT_GE(v1.y,1.7-EPSILON);
    EXPECT_LE(v1.y,1.7+EPSILON);
    EXPECT_GE(v1.z,-1-EPSILON);
    EXPECT_LE(v1.z,-1+EPSILON);
}

TEST(Normal,sub_vector)
{
    Normal v1(7,6.5,-5);
    Normal v2(7,5.3,-4);

    Normal res = v1 - v2;
    EXPECT_GE(res.x,0-EPSILON);
    EXPECT_LE(res.x,0+EPSILON);
    EXPECT_GE(res.y,1.2-EPSILON);
    EXPECT_LE(res.y,1.2+EPSILON);
    EXPECT_GE(res.z,-1-EPSILON);
    EXPECT_LE(res.z,-1+EPSILON);
}

TEST(Normal,sub_float)
{
    Normal v1(3.3,1.2,-1.5);
    float f = 0.5;
    Normal res = v1 - f;
    EXPECT_GE(res.x,2.8-EPSILON);
    EXPECT_LE(res.x,2.8+EPSILON);
    EXPECT_GE(res.y,0.7-EPSILON);
    EXPECT_LE(res.y,0.7+EPSILON);
    EXPECT_GE(res.z,-2.0-EPSILON);
    EXPECT_LE(res.z,-2.0+EPSILON);
}

TEST(Normal,sub_vector_this)
{
    Normal v1(5,3,1);
    Normal v2(7,3.3,4);

    v1 -= v2;
    EXPECT_GE(v1.x,-2-EPSILON);
    EXPECT_LE(v1.x,-2+EPSILON);
    EXPECT_GE(v1.y,-0.3-EPSILON);
    EXPECT_LE(v1.y,-0.3+EPSILON);
    EXPECT_GE(v1.z,-3-EPSILON);
    EXPECT_LE(v1.z,-3+EPSILON);
}

TEST(Normal,sub_float_this)
{
    Normal v1(3.3,1.2,-1.5);
    float f = 0.5;
    v1 -= f;
    EXPECT_GE(v1.x,2.8-EPSILON);
    EXPECT_LE(v1.x,2.8+EPSILON);
    EXPECT_GE(v1.y,0.7-EPSILON);
    EXPECT_LE(v1.y,0.7+EPSILON);
    EXPECT_GE(v1.z,-2.0-EPSILON);
    EXPECT_LE(v1.z,-2.0+EPSILON);
}

TEST(Normal,mul_vector)
{
    Normal v1(1.2,5.6,87.3);
    Normal v2(1.4,45,-.004);

    Normal res = v1 * v2;
    EXPECT_GE(res.x,1.68-EPSILON);
    EXPECT_LE(res.x,1.68+EPSILON);
    EXPECT_GE(res.y,252-EPSILON);
    EXPECT_LE(res.y,252+EPSILON);
    EXPECT_GE(res.z,-0.3492-EPSILON);
    EXPECT_LE(res.z,-0.3492+EPSILON);
}

TEST(Normal,mul_float)
{
    Normal v1(3.3,1.2,-1.5);
    float f = 7.33;
    Normal res = v1 * f;
    EXPECT_GE(res.x,24.189-EPSILON);
    EXPECT_LE(res.x,24.189+EPSILON);
    EXPECT_GE(res.y,8.796-EPSILON);
    EXPECT_LE(res.y,8.796+EPSILON);
    EXPECT_GE(res.z,-10.995-EPSILON);
    EXPECT_LE(res.z,-10.995+EPSILON);
}

TEST(Normal,mul_vector_this)
{
    Normal v1(1,0,3);
    Normal v2(2,3,7);

    v1 *= v2;
    EXPECT_GE(v1.x,2-EPSILON);
    EXPECT_LE(v1.x,2+EPSILON);
    EXPECT_GE(v1.y,0-EPSILON);
    EXPECT_LE(v1.y,0+EPSILON);
    EXPECT_GE(v1.z,21-EPSILON);
    EXPECT_LE(v1.z,21+EPSILON);
}

TEST(Normal,mul_float_this)
{
    Normal v1(3.3,1.2,-1.5);
    float f = -53.477;
    v1 *= f;
    EXPECT_GE(v1.x,-176.4741-EPSILON);
    EXPECT_LE(v1.x,-176.4741+EPSILON);
    EXPECT_GE(v1.y,-64.1724-EPSILON);
    EXPECT_LE(v1.y,-64.1724+EPSILON);
    EXPECT_GE(v1.z,80.2155-EPSILON);
    EXPECT_LE(v1.z,80.2155+EPSILON);
}

TEST(Normal,div_vector)
{
    Normal v1(7,8.4,7);
    Normal v2(-6,-0.4,2);

    Normal res = v1 / v2;
    EXPECT_GE(res.x,(7.0/-6.0)-EPSILON);
    EXPECT_LE(res.x,(7.0/-6.0)+EPSILON);
    EXPECT_GE(res.y,(8.4/-0.4)-EPSILON);
    EXPECT_LE(res.y,(8.4/-0.4)+EPSILON);
    EXPECT_GE(res.z,(7.0/2.0)-EPSILON);
    EXPECT_LE(res.z,(7.0/2.0)+EPSILON);

    Normal vzerox(0,1,1);
    Normal vzeroy(1,0,1);
    Normal vzeroz(1,1,0);

    v1/vzerox;
    v1/vzeroy;
    v1/vzeroz;

    EXPECT_EQ(errors_count[CRITICAL_INDEX], 3);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Normal,div_float)
{
    Normal v1(3.3,1.2,-1.5);
    float f = 7.33;
    Normal res = v1 / f;
    EXPECT_GE(res.x,3.3/7.33-EPSILON);
    EXPECT_LE(res.x,3.3/7.33+EPSILON);
    EXPECT_GE(res.y,1.2/7.33-EPSILON);
    EXPECT_LE(res.y,1.2/7.33+EPSILON);
    EXPECT_GE(res.z,-1.5/7.33-EPSILON);
    EXPECT_LE(res.z,-1.5/7.33+EPSILON);

    float zero = 0.f;
    v1/zero;
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Normal,div_vector_this)
{
    Normal v1(1,0,3);
    Normal v2(2,3,7);

    v1 /= v2;
    EXPECT_GE(v1.x,1.0/2.0-EPSILON);
    EXPECT_LE(v1.x,1.0/2.0+EPSILON);
    EXPECT_GE(v1.y,0.0/3.0-EPSILON);
    EXPECT_LE(v1.y,0.0/3.0+EPSILON);
    EXPECT_GE(v1.z,3.0/7.0-EPSILON);
    EXPECT_LE(v1.z,3.0/7.0+EPSILON);

    Normal vzerox(0,1,1);
    Normal vzeroy(1,0,1);
    Normal vzeroz(1,1,0);

    v2 = v1;
    v2/=vzerox;
    v2 = v1;
    v2/=vzeroy;
    v2 = v1;
    v2/=vzeroz;

    EXPECT_EQ(errors_count[CRITICAL_INDEX], 3);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Normal,div_float_this)
{
    Normal v1(3.3,1.2,-1.5);
    float f = -53.477;
    v1 /= f;
    EXPECT_GE(v1.x,3.3/-53.477-EPSILON);
    EXPECT_LE(v1.x,3.3/-53.477+EPSILON);
    EXPECT_GE(v1.y,1.2/-53.477-EPSILON);
    EXPECT_LE(v1.y,1.2/-53.477+EPSILON);
    EXPECT_GE(v1.z,-1.5/-53.477-EPSILON);
    EXPECT_LE(v1.z,-1.5/-53.477+EPSILON);

    float zero = 0.f;
    v1/=zero;
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Normal,not_vector)
{
    Normal v1(3,4.55556,-18);
    Normal res = !v1;

    EXPECT_GE(res.x,-3-EPSILON);
    EXPECT_LE(res.x,-3+EPSILON);
    EXPECT_GE(res.y,-4.55556-EPSILON);
    EXPECT_LE(res.y,-4.55556+EPSILON);
    EXPECT_GE(res.z,18-EPSILON);
    EXPECT_LE(res.z,18+EPSILON);
}

TEST(Normal,minus_vector)
{
    Normal v1(6,8.5,-3.76);
    Normal res = -v1;

    EXPECT_GE(res.x,-6-EPSILON);
    EXPECT_LE(res.x,-6+EPSILON);
    EXPECT_GE(res.y,-8.5-EPSILON);
    EXPECT_LE(res.y,-8.5+EPSILON);
    EXPECT_GE(res.z,3.76-EPSILON);
    EXPECT_LE(res.z,3.76+EPSILON);
}

TEST(Normal,equal_vector)
{
    //[X VALUE] [Y VALUE] [Z VALUE]
    //[F] [F] [F]
    Normal v1(1.4,2.5,3.6);
    Normal v2(4.9,-5.8,6.7);
    bool res = v1==v2;
    EXPECT_EQ(res, false);

    //[T] [F] [F]
    v1 = Normal(4.9,2.5,3.6);
    v2 = Normal(4.9,-5.8,6.7);
    res = v1==v2;
    EXPECT_EQ(res, false);

    //[F] [T] [F]
    v1 = Normal(1.2,-5.8,3.6);
    v2 = Normal(4.9,-5.8,6.7);
    res = v1==v2;
    EXPECT_EQ(res, false);

    //[F] [F] [T]
    v1 = Normal(4.5,2.5,6.7);
    v2 = Normal(4.9,-5.8,6.7);
    res = v1==v2;
    EXPECT_EQ(res, false);

    //[T] [T] [F]
    v1 = Normal(4.9,-5.8,3.6);
    v2 = Normal(4.9,-5.8,6.7);
    res = v1==v2;
    EXPECT_EQ(res, false);

    //[T] [F] [T]
    v1 = Normal(4.9,2.5,3.6);
    v2 = Normal(4.9,-5.8,3.6);
    res = v1==v2;
    EXPECT_EQ(res, false);

    //[F] [T] [T]
    v1 = Normal(2.9,2.5,3.6);
    v2 = Normal(4.9,2.5,3.6);
    res = v1==v2;
    EXPECT_EQ(res, false);

    //[T] [T] [T]
    v1 = Normal(4.9,-5.8,6.7);
    v2 = Normal(4.9,-5.8,6.7);
    res = v1==v2;
    EXPECT_EQ(res, true);
}

TEST(Normal,not_equal_vector)
{
    //[X VALUE] [Y VALUE] [Z VALUE]
    //[F] [F] [F]
    Normal v1(1.4,2.5,3.6);
    Normal v2(4.9,-5.8,6.7);
    bool res = v1!=v2;
    EXPECT_EQ(res, true);

    //[T] [F] [F]
    v1 = Normal(4.9,2.5,3.6);
    v2 = Normal(4.9,-5.8,6.7);
    res = v1!=v2;
    EXPECT_EQ(res, true);

    //[F] [T] [F]
    v1 = Normal(1.2,-5.8,3.6);
    v2 = Normal(4.9,-5.8,6.7);
    res = v1!=v2;
    EXPECT_EQ(res, true);

    //[F] [F] [T]
    v1 = Normal(4.5,2.5,6.7);
    v2 = Normal(4.9,-5.8,6.7);
    res = v1!=v2;
    EXPECT_EQ(res, true);

    //[T] [T] [F]
    v1 = Normal(4.9,-5.8,3.6);
    v2 = Normal(4.9,-5.8,6.7);
    res = v1!=v2;
    EXPECT_EQ(res, true);

    //[T] [F] [T]
    v1 = Normal(4.9,2.5,3.6);
    v2 = Normal(4.9,-5.8,3.6);
    res = v1!=v2;
    EXPECT_EQ(res, true);

    //[F] [T] [T]
    v1 = Normal(2.9,2.5,3.6);
    v2 = Normal(4.9,2.5,3.6);
    res = v1!=v2;
    EXPECT_EQ(res, true);

    //[T] [T] [T]
    v1 = Normal(4.9,-5.8,6.7);
    v2 = Normal(4.9,-5.8,6.7);
    res = v1!=v2;
    EXPECT_EQ(res, false);
}

TEST(Normal,access)
{
    Normal v(-72.74395f,-6.04488f,-51.11608f);
    EXPECT_EQ(v.x, v[0]);
    EXPECT_EQ(v.y, v[1]);
    EXPECT_EQ(v.z, v[2]);
}

TEST(Normal,const_access)
{
    const Normal v2(-72.74395f,-6.04488f,-51.11608f);
    EXPECT_EQ(v2.x,v2[0]);
    EXPECT_EQ(v2.y,v2[1]);
    EXPECT_EQ(v2.z,v2[2]);
}

TEST(Normal,clamp)
{
    Normal sample(4.9,-5.8,3.6);;
    Normal v1 = sample;
    Vec3 min(-10,-10,-10);
    Vec3 max(10,10,10);

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

    //in range z
    v1.clamp(min,max);
    EXPECT_EQ(v1.z, sample.z);
    //min z
    v1 = sample;
    min.z = 5;
    v1.clamp(min,max);
    EXPECT_EQ(v1.z, min.z);
    min.z = -10;
    //max z
    v1 = sample;
    max.z = 3;
    v1.clamp(min,max);
    EXPECT_EQ(v1.z, max.z);
    max.z = 10;
}

TEST(Normal,saturate)
{
    Normal sample(0.9,0.5,0.3);;
    Normal v1 = sample;

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

    //in range z
    v1.saturate();
    EXPECT_EQ(v1.z, sample.z);
    //min z
    v1 = sample;
    v1.z = -0.1;
    v1.saturate();
    EXPECT_EQ(v1.z, 0.f);
    //max z
    v1 = sample;
    v1.z = 1.5;
    v1.saturate();
    EXPECT_EQ(v1.z, 1.f);
}

TEST(Normal,distanceTo)
{
    Normal a(1.5f,-2.f,1.7f);
    Normal b(3.7f,2.5f,-4.6f);
    float dist = a.distanceTo(b);
    EXPECT_EQ(8.0486023631f, dist);
}

TEST(Normal,max)
{
    Normal sample(0.5,1.5,-3.5);
    Normal value;
    Normal compare;

    //x is max
    value = sample;
    compare = Normal(0.2f,0.f,0.f);
    value.max(compare);
    EXPECT_EQ(value.x, sample.x);
    //x is not max
    value = sample;
    compare = Normal(1.0,0.f,0.f);
    value.max(compare);
    EXPECT_EQ(value.x, compare.x);

    //y is max
    value = sample;
    compare = Normal(0.f,1.f,0.f);
    value.max(compare);
    EXPECT_EQ(value.y,sample.y);
    //y is not max
    value = sample;
    compare = Normal(0.f,10.f,0.f);
    value.max(compare);
    EXPECT_EQ(value.y, compare.y);

    //z is max
    value = sample;
    compare = Normal(0.f,0.f,-5.f);
    value.max(compare);
    EXPECT_EQ(value.z,sample.z);
    //z is not max
    value = sample;
    compare = Normal(0.f,0.f,0.f);
    value.max(compare);
    EXPECT_EQ(value.z, compare.z);
}

TEST(Normal,min)
{
    Normal sample(0.5,1.5,-3.5);
    Normal value;
    Normal compare;

    //x is max
    value = sample;
    compare = Normal(0.2f,0.f,0.f);
    value.min(compare);
    EXPECT_EQ(value.x, compare.x);
    //x is not max
    value = sample;
    compare = Normal(1.0,0.f,0.f);
    value.min(compare);
    EXPECT_EQ(value.x, sample.x);

    //y is max
    value = sample;
    compare = Normal(0.f,1.f,0.f);
    value.min(compare);
    EXPECT_EQ(value.y,compare.y);
    //y is not max
    value = sample;
    compare = Normal(0.f,10.f,0.f);
    value.min(compare);
    EXPECT_EQ(value.y, sample.y);

    //z is max
    value = sample;
    compare = Normal(0.f,0.f,-5.f);
    value.min(compare);
    EXPECT_EQ(value.z,compare.z);
    //z is not max
    value = sample;
    compare = Normal(0.f,0.f,0.f);
    value.min(compare);
    EXPECT_EQ(value.z, sample.z);
}

TEST(Normal,inline_normalize)
{
    errors_count[CRITICAL_INDEX] = 0;
    Normal v1(3,1,2);
    EXPECT_FLOAT_EQ(v1.length(),3.7416575f);
    EXPECT_FALSE(v1.is_normalized());

    Normal v2 = normalize(v1);

    v1.normalize();
    EXPECT_EQ(v1.x,v2.x);
    EXPECT_EQ(v1.y,v2.y);
    EXPECT_EQ(v1.z,v2.z);
    EXPECT_TRUE(v1.is_normalized());
    EXPECT_TRUE(v2.is_normalized());

    Normal vzero;
    normalize(vzero);
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Normal,inline_clamp)
{
    Normal sample(4.9,-5.8,3.6);;
    Normal v1 = sample;
    Vec3 min(-10,-10,-10);
    Vec3 max(10,10,10);
    Normal out;

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

    //in range z
    out = clamp(v1,min,max);
    EXPECT_EQ(out.z, sample.z);
    //min z
    v1 = sample;
    min.z = 5;
    out = clamp(v1,min,max);
    EXPECT_EQ(out.z, min.z);
    min.z = -10;
    //max z
    v1 = sample;
    max.z = 3;
    out = clamp(v1,min,max);
    EXPECT_EQ(out.z, max.z);
    max.z = 10;
}

TEST(Normal,inline_saturate)
{
    Normal sample(0.9,0.5,0.3);;
    Normal v1 = sample;
    Normal out;
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

    //in range z
    out = saturate(v1);;
    EXPECT_EQ(out.z, sample.z);
    //min z
    v1 = sample;
    v1.z = -0.1;
    out = saturate(v1);;
    EXPECT_EQ(out.z, 0.f);
    //max z
    v1 = sample;
    v1.z = 1.5;
    out = saturate(v1);;
    EXPECT_EQ(out.z, 1.f);
}

TEST(Normal,inline_distance)
{
    Normal a(1.5f,-2.f,1.7f);
    Normal b(3.7f,2.5f,-4.6f);
    float dist = distance(a,b);
    EXPECT_EQ(8.0486023631f, dist);
}

TEST(Normal,inline_max)
{
    Normal sample(0.5,1.5,-3.5);
    Normal value;
    Normal compare;
    Normal out;

    //x is max
    value = sample;
    compare = Normal(0.2f,0.f,0.f);
    out = max(value,compare);;
    EXPECT_EQ(out.x, sample.x);
    //x is not max
    value = sample;
    compare = Normal(1.0,0.f,0.f);
    out = max(value,compare);;
    EXPECT_EQ(out.x, compare.x);

    //y is max
    value = sample;
    compare = Normal(0.f,1.f,0.f);
    out = max(value,compare);;
    EXPECT_EQ(out.y,sample.y);
    //y is not max
    value = sample;
    compare = Normal(0.f,10.f,0.f);
    out = max(value,compare);;
    EXPECT_EQ(out.y, compare.y);

    //z is max
    value = sample;
    compare = Normal(0.f,0.f,-5.f);
    out = max(value,compare);;
    EXPECT_EQ(out.z,sample.z);
    //z is not max
    value = sample;
    compare = Normal(0.f,0.f,0.f);
    out = max(value,compare);;
    EXPECT_EQ(out.z, compare.z);
}

TEST(Normal,inline_min)
{
    Normal sample(0.5,1.5,-3.5);
    Normal value;
    Normal compare;
    Normal out;

    //x is max
    value = sample;
    compare = Normal(0.2f,0.f,0.f);
    out = min(value,compare);;
    EXPECT_EQ(out.x, compare.x);
    //x is not max
    value = sample;
    compare = Normal(1.0,0.f,0.f);
    out = min(value,compare);;
    EXPECT_EQ(out.x, sample.x);

    //y is max
    value = sample;
    compare = Normal(0.f,1.f,0.f);
    out = min(value,compare);;
    EXPECT_EQ(out.y,compare.y);
    //y is not max
    value = sample;
    compare = Normal(0.f,10.f,0.f);
    out = min(value,compare);;
    EXPECT_EQ(out.y, sample.y);

    //z is max
    value = sample;
    compare = Normal(0.f,0.f,-5.f);
    out = min(value,compare);;
    EXPECT_EQ(out.z,compare.z);
    //z is not max
    value = sample;
    compare = Normal(0.f,0.f,0.f);
    out = min(value,compare);;
    EXPECT_EQ(out.z, sample.z);
}

