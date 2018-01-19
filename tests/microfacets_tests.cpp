
#include <gtest/gtest.h>


#include "materials/microfacet_distributions.hpp"
#include "utility/utility.hpp"

#define EPSILON 1E-5f

TEST(MicrofacetDist,Blinn_D)
{
    const int SAMPLES = 160;
    Blinn blinn(48.f);
    Vec3 wo(0.f,0.f,0.f);
    float mean = 0;
    float stddev = 0;
    for(float f = -40.f;f<=40.f;f+=0.5f)
    {
        wo.z = cosf(radians(f));
        mean+=blinn.D(&wo);
    }
    mean/=SAMPLES;
    EXPECT_FLOAT_EQ(mean, 2.05130506f);

    for(float f = -40.f;f<=40.f;f+=0.5f)
    {
        wo.z = cosf(radians(f));
        float sample = blinn.D(&wo) - mean;
        stddev += sample*sample;
    }
    stddev=sqrtf(stddev/SAMPLES);
    EXPECT_FLOAT_EQ(stddev,2.71867514f);
}

TEST(MicrofacetDist,Blinn_G)
{
    Blinn blinn(48.f);
    Vec3 wo;
    Vec3 wi;
    float res;

    //cos = 0;
    wo = Vec3(1.f,0.f,0.f);
    wi = Vec3(1.f,0.f,0.f);
    res = blinn.G(&wo,&wi);
    EXPECT_EQ(res, 0.f);

    //cos >1
    wo = Vec3(0.f,0.f,1.2f);
    wi = Vec3(0.f,0.f,1.2f);
    res = blinn.G(&wo,&wi);
    EXPECT_EQ(res, 1.f);

    //c > 1.6f
    wo = Vec3(0.f,0.f,0.9f);
    wi = Vec3(0.f,0.f,0.9f);
    res = blinn.G(&wo,&wi);
    EXPECT_EQ(res, 1.f);

    //normal execution
    wo = Vec3(0.f,0.f,0.1f);
    wi = Vec3(0.f,0.f,0.1f);
    res = blinn.G(&wo,&wi);
    EXPECT_FLOAT_EQ(res, 0.693502366f);
}

TEST(MicrofacetDist,Beckmann_D)
{
    const int SAMPLES = 160;
    Beckmann beckmann(0.2f);
    Vec3 wo(0.f,0.f,0.f);
    float mean = 0;
    float stddev = 0;
    for(float f = -40.f;f<=40.f;f+=0.5f)
    {
        wo.z = cosf(radians(f));
        mean+=beckmann.D(&wo);
    }
    mean/=SAMPLES;
    EXPECT_FLOAT_EQ(mean, 1.44289351f);

    for(float f = -40.f;f<=40.f;f+=0.5f)
    {
        wo.z = cosf(radians(f));
        float sample = beckmann.D(&wo) - mean;
        stddev += sample*sample;
    }
    stddev=sqrtf(stddev/SAMPLES);
    EXPECT_FLOAT_EQ(stddev,2.46824217f);
}

TEST(MicrofacetDist,Beckmann_G)
{
    Beckmann beckmann(0.2f);
    Vec3 wo;
    Vec3 wi;
    float res;

    //cos = 0;
    wo = Vec3(1.f,0.f,0.f);
    wi = Vec3(1.f,0.f,0.f);
    res = beckmann.G(&wo,&wi);
    EXPECT_EQ(res, 0.f);

    //cos >1
    wo = Vec3(0.f,0.f,1.2f);
    wi = Vec3(0.f,0.f,1.2f);
    res = beckmann.G(&wo,&wi);
    EXPECT_EQ(res, 1.f);

    //c > 1.6f
    wo = Vec3(0.f,0.f,0.9f);
    wi = Vec3(0.f,0.f,0.9f);
    res = beckmann.G(&wo,&wi);
    EXPECT_EQ(res, 1.f);

    //normal execution
    wo = Vec3(0.f,0.f,0.1f);
    wi = Vec3(0.f,0.f,0.1f);
    res = beckmann.G(&wo,&wi);
    EXPECT_FLOAT_EQ(res, 0.693502366f);
}

TEST(MicrofacetDist,GGXiso_D)
{
    const int SAMPLES = 160;
    GGXiso ggx(0.2f);
    Vec3 wo(0.f,0.f,0.f);
    float mean = 0;
    float stddev = 0;
    for(float f = -40.f;f<=40.f;f+=0.5f)
    {
        wo.z = cosf(radians(f));
        mean+=ggx.D(&wo);
    }
    mean/=SAMPLES;
    EXPECT_FLOAT_EQ(mean, 1.83194709f);

    for(float f = -40.f;f<=40.f;f+=0.5f)
    {
        wo.z = cosf(radians(f));
        float sample = ggx.D(&wo) - mean;
        stddev += sample*sample;
    }
    stddev=sqrtf(stddev/SAMPLES);
    EXPECT_FLOAT_EQ(stddev,2.40666032f);
}

TEST(MicrofacetDist,GGXiso_G)
{
    GGXiso ggx(0.2f);
    Vec3 wo;
    Vec3 wi;
    float res;

    //cos = 0;
    wo = Vec3(1.f,0.f,0.f);
    wi = Vec3(1.f,0.f,0.f);
    res = ggx.G(&wo,&wi);
    EXPECT_EQ(res, 0.f);

    //normal execution
    wo = Vec3(0.f,0.f,0.3f);
    wi = Vec3(0.f,0.f,0.3f);
    res = ggx.G(&wo,&wi);
    EXPECT_FLOAT_EQ(res, 0.826182127f);
}

