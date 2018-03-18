
#include <gtest/gtest.h>


#include "utility/spectrum.hpp"
#include "textures/texture.hpp"
#include "textures/uniform.hpp"

TEST(Textures,UniformTexture_map)
{
    UniformTexture tex(SPECTRUM_WHITE);
    Spectrum res;
    res = tex.map(0,0);
    EXPECT_EQ(res.w[0],SPECTRUM_WHITE.w[0]);
    EXPECT_EQ(res.w[1],SPECTRUM_WHITE.w[1]);
    EXPECT_EQ(res.w[2],SPECTRUM_WHITE.w[2]);

    res = tex.map(-1,-1);
    EXPECT_EQ(res.w[0],SPECTRUM_WHITE.w[0]);
    EXPECT_EQ(res.w[1],SPECTRUM_WHITE.w[1]);
    EXPECT_EQ(res.w[2],SPECTRUM_WHITE.w[2]);

    res = tex.map(1,1);
    EXPECT_EQ(res.w[0],SPECTRUM_WHITE.w[0]);
    EXPECT_EQ(res.w[1],SPECTRUM_WHITE.w[1]);
    EXPECT_EQ(res.w[2],SPECTRUM_WHITE.w[2]);
}

