
#include <gtest/gtest.h>


#include "utility/utility.hpp"
#include <climits>

TEST(Utility,format_seconds)
{
    char out[16];

    //more than 100d
    format_seconds(8640000,out);
    EXPECT_EQ(strcmp(out,MESSAGE_MORE_THAN_100_DAYS),0);

    //less than 1s
    format_seconds(0,out);
    EXPECT_EQ(strcmp(out,MESSAGE_LESS_THAN_1_SECOND),0);

    //max length for days, hours, mins and s
    format_seconds(8639999,out);
    EXPECT_EQ(strcmp(out,"99d 23h 59m 59s "),0);

    //only some seconds
    format_seconds(41,out);
    EXPECT_EQ(strcmp(out,"41s "),0);

    //five minutes
    format_seconds(300, out);
    EXPECT_EQ(strcmp(out,"5m "),0);
}

TEST(Utility,swap)
{
    float f1_original = 0.5f;
    float f2_original = -0.5f;
    float f1 = f1_original;
    float f2 = f2_original;
    swap(&f1,&f2);
    EXPECT_EQ(f1, f2_original);
    EXPECT_EQ(f2, f1_original);
}

TEST(Utility,radians)
{
    EXPECT_FLOAT_EQ(radians(0), 0);
    EXPECT_FLOAT_EQ(radians(90), ONE_PI/2.f);
    EXPECT_FLOAT_EQ(radians(180),ONE_PI);
    EXPECT_FLOAT_EQ(radians(270),ONE_PI*3.f/2.f);
    EXPECT_FLOAT_EQ(radians(360),TWO_PI);
    EXPECT_FLOAT_EQ(radians(450),TWO_PI+ONE_PI/2.f);
}

TEST(Utility,degrees)
{
    EXPECT_FLOAT_EQ(degrees(0),0.f);
    EXPECT_FLOAT_EQ(degrees(ONE_PI/2.f),90.f);
    EXPECT_FLOAT_EQ(degrees(ONE_PI),180.f);
    EXPECT_FLOAT_EQ(degrees(ONE_PI*3.f/2.f),270.f);
    EXPECT_FLOAT_EQ(degrees(TWO_PI), 360.f);
    EXPECT_FLOAT_EQ(degrees(TWO_PI+ONE_PI/2.f),450.f);
}

TEST(Utility,min_float)
{
    float a = 0.5f;
    float b = 1.5f;
    EXPECT_EQ(min(a,b), a);
    EXPECT_EQ(min(b,a), a);
}

TEST(Utility,max_float)
{
    float a = 0.5f;
    float b = 1.5f;
    EXPECT_EQ(max(a,b), b);
    EXPECT_EQ(max(b,a), b);
}

TEST(Utility,min_int)
{
    int a = 1;
    int b = 2;
    EXPECT_EQ(min(a,b), a);
    EXPECT_EQ(min(b,a), a);
}

TEST(Utility,max_int)
{
    int a = 1;
    int b = 2;
    EXPECT_EQ(max(a,b), b);
    EXPECT_EQ(max(b,a), b);
}

TEST(Utility,clamp)
{
    float a;
    float res;

    //in range
    a = 0.75f;
    res = clamp(a,0.5f,2.f);
    EXPECT_EQ(res, a);

    //lower
    a = -.5f;
    res = clamp(a,0.5f,2.f);
    EXPECT_EQ(res, 0.5f);

    //higher
    a = 3.5f;
    res = clamp(a,0.5f,2.f);
    EXPECT_EQ(res, 2.f);
}

TEST(Utility,lerp)
{
    float a = 0.25f;
    float res = lerp(a,0.f,1.f);
    EXPECT_EQ(res, a);

    res = lerp(a, -1.f,2.f);
    EXPECT_EQ(res, -0.25f);
}

TEST(Utility,inverse_lerp)
{
    float a = 0.25f;
    float res = inverse_lerp(0.25, 0.f, 1.f);
    EXPECT_EQ(res, a);

    res = inverse_lerp(-0.25,-1.f,2.f);
    EXPECT_EQ(res, a);
}

TEST(Utility,flt_equal)
{
    float a = 0.1;
    float b = 0.1+FLT_EPSILON;
    EXPECT_NE(a, b);
    EXPECT_TRUE(flt_equal(a,b));

    b+=1E-4f;
    EXPECT_NE(a, b);
    EXPECT_FALSE(flt_equal(a,b));
}

TEST(Utility,sign)
{
    float a = -.5f;
    float b = .5f;
    float zero = 0.f;

    EXPECT_EQ(sign(a),-1);
    EXPECT_EQ(sign(b),1);
    EXPECT_EQ(sign(zero),1);
}

TEST(Utility,equation1)
{
    EXPECT_EQ(equation1(2.f, 1.f), -0.5f);

    errors_count[ERROR_INDEX] = 0;
    equation1(0, 1.f);
    EXPECT_EQ(errors_count[ERROR_INDEX],1);
    errors_count[ERROR_INDEX] = 0;
}

TEST(Utility,equation2)
{
    float sol1;
    float sol2;
    bool res;

    //2 sol
    res = equation2(1.f, -1.f, -2.f, &sol1, &sol2);
    if(sol1>sol2)
        swap(&sol1,&sol2);
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
    res = equation2(1.00000012f,-2.62480998f,1.72240686f,&sol1,&sol2);
    EXPECT_FLOAT_EQ(sol1,1.31240487f);
    EXPECT_FLOAT_EQ(sol2,1.31240487f);
    EXPECT_TRUE(res);

}

