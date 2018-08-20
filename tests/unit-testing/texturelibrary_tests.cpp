#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "textures/texture_library.hpp"
#include "textures/texture_uniform.hpp"
#include "utility/spectrum.hpp"

SPECTRE_TEST_INIT(TextureLibrary_tests)

SPECTRE_TEST(TextureLibrary, add_texture)
{
    const Spectrum color1 = SPECTRUM_WHITE;
    const Spectrum color2(4500);
    Spectrum res;
    HitPoint h;

    Texture* tex = new TextureUniform(color1);
    TexLib.inherit_texture("New", tex);
    const Texture* got = TexLib.get_texture("New");
    ASSERT_EQ(got, tex);
    res = got->map(&h);
    EXPECT_EQ(color1.w[0], res.w[0]);
    EXPECT_EQ(color1.w[1], res.w[1]);
    EXPECT_EQ(color1.w[2], res.w[2]);

    //add different with same name, should be refused
    Texture* tex2 = new TextureUniform(color2);
    TexLib.inherit_texture("New", tex2);
    const Texture* got2 = TexLib.get_texture("New");
    res = got2->map(&h);
    EXPECT_EQ(color1.w[0], res.w[0]);
    EXPECT_EQ(color1.w[1], res.w[1]);
    EXPECT_EQ(color1.w[2], res.w[2]);
    EXPECT_NE(color2.w[0], res.w[0]);
    EXPECT_NE(color2.w[1], res.w[1]);
    EXPECT_NE(color2.w[2], res.w[2]);
    delete tex2;
}

SPECTRE_TEST(TextureLibrary, add_texture_anonymous)
{
    const Spectrum color1 = SPECTRUM_WHITE;
    Texture* tex = new TextureUniform(color1);
    TexLib.inherit_texture(tex);
    //no way to check this ¯\_(ツ)_/¯
    //no problem since it is useless, anonymous textures are
    //deallocated at program termination (when this singleton
    //dies)
}

SPECTRE_TEST(TextureLibrary, add_map)
{
    const ImageMap* got;
    errors_count[CRITICAL_INDEX] = 0;
    pixBGRA data[4] = {0x0000FFFF, 0x00FF00FF, 0xFF0000FF, 0x000000FF};
    ImageMap* map0 = new ImageMapUnfiltered(data, 2);
    ImageMap* map1 = new ImageMapUnfiltered(data, 2);
    //assert no construction error of imagemaps
    ASSERT_EQ(errors_count[CRITICAL_INDEX], 0);

    //insert and retrieve first map
    TexLib.inherit_map("test map", map0);
    got = TexLib.get_map("test map");
    EXPECT_PTR_EQ(got, map0);
    got = TexLib.get_map("test map2");
    EXPECT_PTR_NULL(got);

    //try with already inserted name
    TexLib.inherit_map("test map", map1);
    got = TexLib.get_map("test map");
    EXPECT_PTR_NE(got, map1);
    EXPECT_PTR_EQ(got, map0);
    TexLib.inherit_map("test map1", map1);
    got = TexLib.get_map("test map1");
    EXPECT_PTR_EQ(got, map1);
}

SPECTRE_TEST(TextureLibrary, remove_texture)
{
    Texture* tex = new TextureUniform(SPECTRUM_WHITE);
    TexLib.inherit_texture("Removeme", tex);
    const Texture* got = TexLib.get_texture("Removeme");
    ASSERT_PTR_EQ(got, tex);

    TexLib.erase_texture("Removeme");
    got = TexLib.get_texture("Removeme");
    EXPECT_PTR_NULL(got);

    //this should do nothing, texture already removed
    got = tex;//just assign random address to got, avoid using previous null
    TexLib.erase_texture("Removeme");
    got = TexLib.get_texture("Removeme");
    EXPECT_PTR_NULL(got);

    got = TexLib.get_texture("Default");
    EXPECT_PTR_NOTNULL(got);
    TexLib.erase_texture("Default");
    EXPECT_PTR_NOTNULL(got);
}

SPECTRE_TEST(TextureLibrary, remove_map)
{
    pixBGRA data[4] = {0x0000FFFF, 0x00FF00FF, 0xFF0000FF, 0x000000FF};
    ImageMap* map0 = new ImageMapUnfiltered(data, 2);
    TexLib.inherit_map("Removeme", map0);
    const ImageMap* got = TexLib.get_map("Removeme");
    ASSERT_PTR_EQ(got, map0);

    TexLib.erase_map("Removeme");
    got = TexLib.get_map("Removeme");
    EXPECT_PTR_NULL(got);

    got = map0;
    TexLib.erase_map("Removeme");
    got = TexLib.get_map("Removeme");
    EXPECT_PTR_NULL(got);
}

SPECTRE_TEST(TextureLibrary, contains_texture)
{
    Texture* tex = new TextureUniform(SPECTRUM_WHITE);
    TexLib.inherit_texture("Contained", tex);
    bool res = TexLib.contains_texture("Contained");
    EXPECT_TRUE(res);
    TexLib.erase_texture("Contained");
    res = TexLib.contains_texture("Contained");
    EXPECT_FALSE(res);
}

SPECTRE_TEST(TextureLibrary, contains_map)
{
    pixBGRA data[4] = {0x0000FFFF, 0x00FF00FF, 0xFF0000FF, 0x000000FF};
    ImageMap* map0 = new ImageMapUnfiltered(data, 2);
    TexLib.inherit_map("ContainedM", map0);
    bool res = TexLib.contains_map("ContainedM");
    EXPECT_TRUE(res);
    TexLib.erase_map("ContainedM");
    res = TexLib.contains_map("ContainedM");
    EXPECT_FALSE(res);
}

SPECTRE_TEST(TextureLibrary, clear)
{
    Texture* tex = new TextureUniform(SPECTRUM_WHITE);
    TexLib.inherit_texture("Removeme", tex);
    Texture* tex2 = new TextureUniform(SPECTRUM_WHITE);
    TexLib.inherit_texture("Removeme2", tex2);
    Texture* tex3 = new TextureUniform(SPECTRUM_WHITE);
    TexLib.inherit_texture("Removeme3", tex3);
    pixBGRA data[4] = {0x0000FFFF, 0x00FF00FF, 0xFF0000FF, 0x000000FF};
    ImageMap* map0 = new ImageMapUnfiltered(data, 2);
    TexLib.inherit_map("Removeme4", map0);
    ImageMap* map1 = new ImageMapUnfiltered(data, 2);
    TexLib.inherit_map("Removeme5", map1);

    const Texture* got;
    const ImageMap* gotm;
    got = TexLib.get_texture("Removeme");
    EXPECT_PTR_NOTNULL(got);
    got = TexLib.get_texture("Removeme2");
    EXPECT_PTR_NOTNULL(got);
    got = TexLib.get_texture("Removeme3");
    EXPECT_PTR_NOTNULL(got);
    gotm = TexLib.get_map("Removeme4");
    EXPECT_PTR_NOTNULL(gotm);
    gotm = TexLib.get_map("Removeme5");
    EXPECT_PTR_NOTNULL(gotm);
    got = TexLib.get_texture("Default");
    EXPECT_PTR_NOTNULL(got);

    TexLib.clear();

    got = TexLib.get_texture("Removeme");
    EXPECT_PTR_NULL(got);
    got = TexLib.get_texture("Removeme2");
    EXPECT_PTR_NULL(got);
    got = TexLib.get_texture("Removeme3");
    EXPECT_PTR_NULL(got);
    gotm = TexLib.get_map("Removeme4");
    EXPECT_PTR_NULL(gotm);
    gotm = TexLib.get_map("Removeme5");
    EXPECT_PTR_NULL(gotm);
    got = TexLib.get_texture("Default");
    EXPECT_PTR_NOTNULL(got);
}

SPECTRE_TEST(TextureLibrary, get_default)
{
    const Texture* tex0 = TexLib.get_dflt_diffuse();
    const Texture* tex1 = TexLib.get_texture("Default");
    EXPECT_PTR_EQ(tex0, tex1); //assert that they point to the same value
}

SPECTRE_TEST_END(TextureLibrary)
