#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else
#include <gtest/gtest.h>
#endif

#include "utility/spectrum.hpp"
#include <climits>
#include <cmath>

SPECTRE_TEST_INIT(Spectrum_tests)

SPECTRE_TEST(Spectrum, constructor_blackbody)
{
    //black
    Spectrum sp(0);
    EXPECT_TRUE(sp.is_black());
    EXPECT_TRUE(sp.to_xyz().to_sRGB().is_black());

    //800K, mostly red
    Spectrum red(800);
    ColorRGB redrgb = red.to_xyz().to_sRGB();
    EXPECT_GT(redrgb.r, redrgb.g);
    EXPECT_GT(redrgb.r, redrgb.b);

    //6500K white
    Spectrum white(6500);
    ColorRGB whitergb = white.to_xyz().to_sRGB();
    EXPECT_GT(whitergb.r, 0.9f);
    EXPECT_GT(whitergb.g, 0.9f);
    EXPECT_GT(whitergb.b, 0.9f);

    //20000K blue

    Spectrum blue(20000);
    ColorRGB bluergb = blue.to_xyz().to_sRGB();
    EXPECT_GT(bluergb.b, bluergb.g);
    EXPECT_GT(bluergb.b, bluergb.r);
}

SPECTRE_TEST(Spectrum, constructor_init_list)
{
    //Wrong number of args
    try
    {
        Spectrum sp({1.f, 1.f, 1.f});
        FAIL();
    }
    catch(const char* msg)
    {}
#ifdef SPECTRAL
#else
    Spectrum sp({0.99302530302633674f,
                 1.0170691330352013f,
                 1.0143947530476214f,
                 1.0070517895374196f,
                 0.80112726913173504f,
                 0.077593476678434567f,
                 0.003229957831351733f,
                 -0.004352238640709956f,
                 0.0026944590704797754f,
                 0.28205531033673215f,
                 0.8570353689334701f,
                 0.99378492125784268f,
                 0.98449588288224388f,
                 0.8937980881442511f,
                 0.94958431903872431f,
                 0.9395992587226637f});
    ColorRGB res = sp.to_xyz().to_sRGB();
    EXPECT_GE(res.r, .9f);
    EXPECT_LE(res.g, 0.f);
    EXPECT_GE(res.b, .9f);
#endif
}

SPECTRE_TEST(Spectrum, constructor_single_value)
{
    Spectrum sp(1.f);
    ColorRGB res = sp.to_xyz().to_sRGB();
    EXPECT_GE(res.r, .95f);
    EXPECT_GE(res.g, .95f);
    EXPECT_GE(res.b, .95f);
}

SPECTRE_TEST(Spectrum, rgb_to_spectrum)
{
    ColorRGB rgb(1.f, 1.f, 1.f);
    Spectrum sp(rgb, false);
    ColorRGB res = sp.to_xyz().to_sRGB();
    EXPECT_GE(res.r, .95f);
    EXPECT_GE(res.g, .95f);
    EXPECT_GE(res.b, .95f);
}

SPECTRE_TEST(Spectrum, to_xyz)
{
    ColorRGB rgb(1.f, 0.f, 1.f);
    Spectrum sp(rgb, false);
    ColorXYZ res = sp.to_xyz();
    EXPECT_NEAR(res.r, 0.592893898f, 1e-5f);
    EXPECT_NEAR(res.g, 0.284847915f, 1e-5f);
    EXPECT_NEAR(res.b, 0.969637989f, 1e-5f);
}

SPECTRE_TEST(Spectrum, luminance)
{
    ColorRGB rgb(1.f, 0.f, 1.f);
    Spectrum sp(rgb, false);
    EXPECT_NEAR(sp.luminance(), 0.284847915f, 1e-5f);
}

SPECTRE_TEST(Spectrum, is_black)
{
    Spectrum sp(0);
    EXPECT_TRUE(sp.is_black());
}

SPECTRE_TEST(Spectrum, is_valid)
{
    //ok
    EXPECT_TRUE(SPECTRUM_WHITE.is_valid());
    //no ok
    Spectrum sp0nan = SPECTRUM_ONE;
    sp0nan.w[0] = NAN;
    Spectrum sp1nan = SPECTRUM_ONE;
    sp1nan.w[1] = NAN;
    Spectrum sp2nan = SPECTRUM_ONE;
    sp2nan.w[2] = NAN;
    Spectrum sp0inf = SPECTRUM_ONE;
    sp0inf.w[1] = INFINITY;
    Spectrum sp1inf = SPECTRUM_ONE;
    sp1inf.w[1] = INFINITY;
    Spectrum sp2inf = SPECTRUM_ONE;
    sp2inf.w[2] = INFINITY;
    EXPECT_FALSE(sp0nan.is_valid());
    EXPECT_FALSE(sp1nan.is_valid());
    EXPECT_FALSE(sp2nan.is_valid());
    EXPECT_FALSE(sp0inf.is_valid());
    EXPECT_FALSE(sp1inf.is_valid());
    EXPECT_FALSE(sp2inf.is_valid());
}

SPECTRE_TEST(Spectrum, sum_spectrum)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    Spectrum invalid = sp;
    invalid.w[0] = NAN;

    //valid
    Spectrum sp_res = sp+sp;
    EXPECT_EQ(sp_res.w[0], sp.w[0]+sp.w[0]);
    EXPECT_EQ(sp_res.w[1], sp.w[1]+sp.w[1]);
    EXPECT_EQ(sp_res.w[2], sp.w[2]+sp.w[2]);

    //invalid
    ASSERT_ANY_THROW(sp_res = sp+invalid);
    ASSERT_ANY_THROW(sp_res = invalid+sp);
}

SPECTRE_TEST(Spectrum, sum_this_spectrum)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    Spectrum invalid = sp;
    invalid.w[0] = NAN;

    //valid
    Spectrum sp_res = sp;
    sp_res += sp;
    EXPECT_EQ(sp_res.w[0], sp.w[0]+sp.w[0]);
    EXPECT_EQ(sp_res.w[1], sp.w[1]+sp.w[1]);
    EXPECT_EQ(sp_res.w[2], sp.w[2]+sp.w[2]);

    //invalid
    sp_res = sp;
    ASSERT_ANY_THROW(sp_res += invalid);
    ASSERT_ANY_THROW(invalid += sp);
}

SPECTRE_TEST(Spectrum, sub_spectrum)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    Spectrum invalid = sp;
    invalid.w[0] = NAN;

    //valid
    Spectrum sp_res = sp-sp;
    EXPECT_EQ(sp_res.w[0], sp.w[0]-sp.w[0]);
    EXPECT_EQ(sp_res.w[1], sp.w[1]-sp.w[1]);
    EXPECT_EQ(sp_res.w[2], sp.w[2]-sp.w[2]);

    //invalid
    ASSERT_ANY_THROW(sp_res = sp-invalid);
    ASSERT_ANY_THROW(sp_res = invalid-sp);
}

SPECTRE_TEST(Spectrum, sub_this_spectrum)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    Spectrum invalid = sp;
    invalid.w[0] = NAN;

    //valid
    Spectrum sp_res = sp;
    sp_res -= sp;
    EXPECT_EQ(sp_res.w[0], sp.w[0]-sp.w[0]);
    EXPECT_EQ(sp_res.w[1], sp.w[1]-sp.w[1]);
    EXPECT_EQ(sp_res.w[2], sp.w[2]-sp.w[2]);

    //invalid
    sp_res = sp;
    ASSERT_ANY_THROW(sp_res -= invalid);
    ASSERT_ANY_THROW(invalid -= sp);
}

SPECTRE_TEST(Spectrum, mul_spectrum)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    Spectrum invalid = sp;
    invalid.w[0] = NAN;

    //valid
    Spectrum sp_res = sp*sp;
    EXPECT_EQ(sp_res.w[0], sp.w[0]*sp.w[0]);
    EXPECT_EQ(sp_res.w[1], sp.w[1]*sp.w[1]);
    EXPECT_EQ(sp_res.w[2], sp.w[2]*sp.w[2]);

    //invalid
    ASSERT_ANY_THROW(sp_res = sp*invalid);
    ASSERT_ANY_THROW(sp_res = invalid*sp);
}

SPECTRE_TEST(Spectrum, mul_this_spectrum)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    Spectrum invalid = sp;
    invalid.w[0] = NAN;

    //valid
    Spectrum sp_res = sp;
    sp_res *= sp;
    EXPECT_EQ(sp_res.w[0], sp.w[0]*sp.w[0]);
    EXPECT_EQ(sp_res.w[1], sp.w[1]*sp.w[1]);
    EXPECT_EQ(sp_res.w[2], sp.w[2]*sp.w[2]);

    //invalid
    sp_res = sp;
    ASSERT_ANY_THROW(sp_res *= invalid);
    ASSERT_ANY_THROW(invalid *= sp);
}

SPECTRE_TEST(Spectrum, div_spectrum)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    Spectrum invalid = sp;
    invalid.w[0] = NAN;

    //valid
    Spectrum sp_res = sp/sp;
    EXPECT_EQ(sp_res.w[0], sp.w[0]/sp.w[0]);
    EXPECT_EQ(sp_res.w[1], sp.w[1]/sp.w[1]);
    EXPECT_EQ(sp_res.w[2], sp.w[2]/sp.w[2]);

    //invalid
    ASSERT_ANY_THROW(sp_res = sp/invalid);
    ASSERT_ANY_THROW(sp_res = invalid/sp);
}

SPECTRE_TEST(Spectrum, div_this_spectrum)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    Spectrum invalid = sp;
    invalid.w[0] = NAN;

    //valid
    Spectrum sp_res = sp;
    sp_res /= sp;
    EXPECT_EQ(sp_res.w[0], sp.w[0]/sp.w[0]);
    EXPECT_EQ(sp_res.w[1], sp.w[1]/sp.w[1]);
    EXPECT_EQ(sp_res.w[2], sp.w[2]/sp.w[2]);

    //invalid
    sp_res = sp;
    ASSERT_ANY_THROW(sp_res /= invalid);
    ASSERT_ANY_THROW(invalid /= sp);
}

SPECTRE_TEST(Spectrum, sum_float)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    float invalid_float = NAN;

    //valid
    Spectrum sp_res = sp+0.1f;
    EXPECT_EQ(sp_res.w[0], sp.w[0]+0.1f);
    EXPECT_EQ(sp_res.w[1], sp.w[1]+0.1f);
    EXPECT_EQ(sp_res.w[2], sp.w[2]+0.1f);

    //invalid
    ASSERT_ANY_THROW(sp_res = sp+invalid_float);
    sp.w[0] = NAN;
    ASSERT_ANY_THROW(sp_res = sp+0.1f);
}

SPECTRE_TEST(Spectrum, sum_this_float)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    float invalid_float = NAN;

    //valid
    Spectrum sp_res = sp;
    sp_res += 0.1f;
    EXPECT_EQ(sp_res.w[0], sp.w[0]+0.1f);
    EXPECT_EQ(sp_res.w[1], sp.w[1]+0.1f);
    EXPECT_EQ(sp_res.w[2], sp.w[2]+0.1f);

    //invalid
    sp_res = sp;
    ASSERT_ANY_THROW(sp_res += invalid_float);
    sp.w[0] = NAN;
    ASSERT_ANY_THROW(sp += 0.1f);
}

SPECTRE_TEST(Spectrum, sub_float)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    float invalid_float = NAN;

    //valid
    Spectrum sp_res = sp-0.1f;
    EXPECT_EQ(sp_res.w[0], sp.w[0]-0.1f);
    EXPECT_EQ(sp_res.w[1], sp.w[1]-0.1f);
    EXPECT_EQ(sp_res.w[2], sp.w[2]-0.1f);

    //invalid
    ASSERT_ANY_THROW(sp_res = sp-invalid_float);
    sp.w[0] = NAN;
    ASSERT_ANY_THROW(sp_res = sp-0.1f);
}

SPECTRE_TEST(Spectrum, sub_this_float)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    float invalid_float = NAN;

    //valid
    Spectrum sp_res = sp;
    sp_res -= 0.1f;
    EXPECT_EQ(sp_res.w[0], sp.w[0]-0.1f);
    EXPECT_EQ(sp_res.w[1], sp.w[1]-0.1f);
    EXPECT_EQ(sp_res.w[2], sp.w[2]-0.1f);

    //invalid
    sp_res = sp;
    ASSERT_ANY_THROW(sp_res -= invalid_float);
    sp.w[0] = NAN;
    ASSERT_ANY_THROW(sp -= 0.1f);
}

SPECTRE_TEST(Spectrum, mul_float)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    float invalid_float = NAN;

    //valid
    Spectrum sp_res = sp*0.1f;
    EXPECT_EQ(sp_res.w[0], sp.w[0]*0.1f);
    EXPECT_EQ(sp_res.w[1], sp.w[1]*0.1f);
    EXPECT_EQ(sp_res.w[2], sp.w[2]*0.1f);

    //invalid
    ASSERT_ANY_THROW(sp_res = sp*invalid_float);
    sp.w[0] = NAN;
    ASSERT_ANY_THROW(sp_res = sp*0.1f);
}

SPECTRE_TEST(Spectrum, mul_this_float)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    float invalid_float = NAN;

    //valid
    Spectrum sp_res = sp;
    sp_res *= 0.1f;
    EXPECT_EQ(sp_res.w[0], sp.w[0]*0.1f);
    EXPECT_EQ(sp_res.w[1], sp.w[1]*0.1f);
    EXPECT_EQ(sp_res.w[2], sp.w[2]*0.1f);

    //invalid
    sp_res = sp;
    ASSERT_ANY_THROW(sp_res *= invalid_float);
    sp.w[0] = NAN;
    ASSERT_ANY_THROW(sp *= 0.1f);
}

SPECTRE_TEST(Spectrum, div_float)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    float invalid_float = NAN;

    //valid
    Spectrum sp_res = sp/0.1f;
    EXPECT_EQ(sp_res.w[0], sp.w[0]/0.1f);
    EXPECT_EQ(sp_res.w[1], sp.w[1]/0.1f);
    EXPECT_EQ(sp_res.w[2], sp.w[2]/0.1f);

    //invalid
    ASSERT_ANY_THROW(sp_res = sp/invalid_float);
    sp.w[0] = NAN;
    ASSERT_ANY_THROW(sp_res = sp/0.1f);
}

SPECTRE_TEST(Spectrum, div_this_float)
{
    ColorRGB input(0.5f, 0.5f, 0.5f);
    Spectrum sp(input, false);
    float invalid_float = NAN;

    //valid
    Spectrum sp_res = sp;
    sp_res /= 0.1f;
    EXPECT_EQ(sp_res.w[0], sp.w[0]/0.1f);
    EXPECT_EQ(sp_res.w[1], sp.w[1]/0.1f);
    EXPECT_EQ(sp_res.w[2], sp.w[2]/0.1f);

    //invalid
    sp_res = sp;
    ASSERT_ANY_THROW(sp_res /= invalid_float;);
    sp.w[0] = NAN;
    ASSERT_ANY_THROW(sp /= 0.1f);
}

SPECTRE_TEST_END(Spectrum_tests)
