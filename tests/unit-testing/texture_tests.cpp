#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#else

#include <gtest/gtest.h>

#endif

SPECTRE_TEST_INIT(Texture_tests)

#include "utility/spectrum.hpp"
#include "textures/texture.hpp"
#include "textures/texture_uniform.hpp"

SPECTRE_TEST(Texture, UniformTexture_map)
{
    TextureUniform tex(SPECTRUM_WHITE);
    Spectrum res;
    res = tex.map(Point2());
    EXPECT_EQ(res.w[0], SPECTRUM_WHITE.w[0]);
    EXPECT_EQ(res.w[1], SPECTRUM_WHITE.w[1]);
    EXPECT_EQ(res.w[2], SPECTRUM_WHITE.w[2]);

    res = tex.map(Point2(-1, -1));
    EXPECT_EQ(res.w[0], SPECTRUM_WHITE.w[0]);
    EXPECT_EQ(res.w[1], SPECTRUM_WHITE.w[1]);
    EXPECT_EQ(res.w[2], SPECTRUM_WHITE.w[2]);

    res = tex.map(Point2(1, 1));
    EXPECT_EQ(res.w[0], SPECTRUM_WHITE.w[0]);
    EXPECT_EQ(res.w[1], SPECTRUM_WHITE.w[1]);
    EXPECT_EQ(res.w[2], SPECTRUM_WHITE.w[2]);
}

SPECTRE_TEST_END(Texture)
