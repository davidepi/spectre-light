#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#else

#include <gtest/gtest.h>

#endif

SPECTRE_TEST_INIT(TextureLibrary_tests)

#include "textures/texture_library.hpp"
#include "textures/uniform.hpp"
#include "utility/spectrum.hpp"

SPECTRE_TEST(TextureLibrary, add)
{
    const Spectrum color1 = SPECTRUM_WHITE;
    const Spectrum color2(4500);
    Spectrum res;

    Texture* tex = new UniformTexture(color1);
    TexLib.add_inherit("New", tex);
    const Texture* got = TexLib.get("New");
    ASSERT_EQ(got, tex);
    res = got->map(Point2());
    EXPECT_EQ(color1.w[0], res.w[0]);
    EXPECT_EQ(color1.w[1], res.w[1]);
    EXPECT_EQ(color1.w[2], res.w[2]);

    //add different with same name, should be refused
    Texture* tex2 = new UniformTexture(color2);
    TexLib.add_inherit("New", tex2);
    const Texture* got2 = TexLib.get("New");
    res = got2->map(Point2());
    EXPECT_EQ(color1.w[0], res.w[0]);
    EXPECT_EQ(color1.w[1], res.w[1]);
    EXPECT_EQ(color1.w[2], res.w[2]);
    EXPECT_NE(color2.w[0], res.w[0]);
    EXPECT_NE(color2.w[1], res.w[1]);
    EXPECT_NE(color2.w[2], res.w[2]);
    delete tex2;
}

SPECTRE_TEST(TextureLibrary, remove)
{
    Texture* tex = new UniformTexture(SPECTRUM_WHITE);
    TexLib.add_inherit("Removeme", tex);
    const Texture* got = TexLib.get("Removeme");
    ASSERT_EQ(got, tex);

    TexLib.erase("Removeme");
    got = TexLib.get("Removeme");
    EXPECT_EQ(got, nullptr);

    //this should do nothing, texture already removed
    got = tex;
    TexLib.erase("Removeme");
    got = TexLib.get("Removeme");
    EXPECT_EQ(got, nullptr);

    got = TexLib.get("Default");
    EXPECT_NE(got, nullptr);
    TexLib.erase("Default");
    EXPECT_NE(got, nullptr);
}

SPECTRE_TEST(TextureLibrary, contains)
{
    Texture* tex = new UniformTexture(SPECTRUM_WHITE);
    TexLib.add_inherit("Contained", tex);
    bool res = TexLib.contains("Contained");
    EXPECT_TRUE(res);
    TexLib.erase("Contained");
    res = TexLib.contains("Contained");
    EXPECT_FALSE(res);
}

SPECTRE_TEST(TextureLibrary, clear)
{
    Texture* tex = new UniformTexture(SPECTRUM_WHITE);
    TexLib.add_inherit("Removeme", tex);
    Texture* tex2 = new UniformTexture(SPECTRUM_WHITE);
    TexLib.add_inherit("Removeme2", tex2);
    Texture* tex3 = new UniformTexture(SPECTRUM_WHITE);
    TexLib.add_inherit("Removeme3", tex3);

    const Texture* got;
    got = TexLib.get("Removeme");
    EXPECT_NE(got, nullptr);
    got = TexLib.get("Removeme2");
    EXPECT_NE(got, nullptr);
    got = TexLib.get("Removeme3");
    EXPECT_NE(got, nullptr);
    got = TexLib.get("Default");
    EXPECT_NE(got, nullptr);

    TexLib.clear();

    got = TexLib.get("Removeme");
    EXPECT_EQ(got, nullptr);
    got = TexLib.get("Removeme2");
    EXPECT_EQ(got, nullptr);
    got = TexLib.get("Removeme3");
    EXPECT_EQ(got, nullptr);
    got = TexLib.get("Default");
    EXPECT_NE(got, nullptr);
}

SPECTRE_TEST(TextureLibrary, get_default)
{
    const Texture* tex0 = TexLib.get_default();
    const Texture* tex1 = TexLib.get("Default");
    EXPECT_EQ(tex0, tex1); //assert that they point to the same value
}

SPECTRE_TEST_END(TextureLibrary)
