#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "parsers/parser_config.hpp"
#include "textures/texture_library.hpp"
#include "textures/texture_uniform.hpp"
#include "textures/texture_image.hpp"
#include "utility/spectrum.hpp"
#include "utility/file.hpp"

SPECTRE_TEST_INIT(TextureLibrary_tests)

SPECTRE_TEST(TextureLibrary, add_texture)
{
    TextureLibrary texlib;
    Vec2 shift(0.f);
    Vec2 scale(1.f);
    Spectrum res;
    HitPoint h;

    File src(TEST_ASSETS "images/black.bmp");
    const ImageMap* map = resolve_map(&src, &texlib, UNFILTERED);
    TextureImage* tex = new TextureImage(map, shift, scale);
    texlib.inherit_texture("New", tex);
    const Texture* got = texlib.get_texture("New");
    ASSERT_PTR_EQ(got, tex);
    res = got->map(&h);
    EXPECT_TRUE(res.is_black());

    //add different with same name, should be refused
    File src2(TEST_ASSETS "images/correct.bmp");
    const ImageMap* map2 = resolve_map(&src2, &texlib, UNFILTERED);
    TextureImage* tex2 = new TextureImage(map2, shift, scale);
    texlib.inherit_texture("New", tex2);
    const Texture* got2 = texlib.get_texture("New");
    res = got2->map(&h);
    EXPECT_TRUE(res.is_black());
    EXPECT_FALSE(tex2->map(&h).is_black());
    delete tex2;
}

SPECTRE_TEST(TextureLibrary, add_map)
{
    TextureLibrary texlib;
    const ImageMap* got;
    errors_count[CRITICAL_INDEX] = 0;
    pixBGRA data[4] = {0x0000FFFF, 0x00FF00FF, 0xFF0000FF, 0x000000FF};
    ImageMap* map0 = new ImageMapUnfiltered(data, 2);
    ImageMap* map1 = new ImageMapUnfiltered(data, 2);
    //assert no construction error of imagemaps
    ASSERT_EQ(errors_count[CRITICAL_INDEX], 0);

    //insert and retrieve first map
    texlib.inherit_map("test map", map0);
    got = texlib.get_map("test map");
    EXPECT_PTR_EQ(got, map0);
    got = texlib.get_map("test map2");
    EXPECT_PTR_NULL(got);

    //try with already inserted name
    texlib.inherit_map("test map", map1);
    got = texlib.get_map("test map");
    EXPECT_PTR_NE(got, map1);
    EXPECT_PTR_EQ(got, map0);
    texlib.inherit_map("test map1", map1);
    got = texlib.get_map("test map1");
    EXPECT_PTR_EQ(got, map1);
}

SPECTRE_TEST(TextureLibrary, remove_texture)
{
    TextureLibrary texlib;
    Vec2 shift(0.f);
    Vec2 scale(1.f);
    File src(TEST_ASSETS "images/black.bmp");
    const ImageMap* map = resolve_map(&src, &texlib, UNFILTERED);
    TextureImage* tex = new TextureImage(map, shift, scale);
    texlib.inherit_texture("Removeme", tex);
    const Texture* got = texlib.get_texture("Removeme");
    ASSERT_PTR_EQ(got, tex);

    texlib.erase_texture("Removeme");
    got = texlib.get_texture("Removeme");
    EXPECT_PTR_NULL(got);

    //this should do nothing, texture already removed
    got = tex;//just assign random address to got, avoid using previous null
    texlib.erase_texture("Removeme");
    got = texlib.get_texture("Removeme");
    EXPECT_PTR_NULL(got);
}

SPECTRE_TEST(TextureLibrary, remove_map)
{
    TextureLibrary texlib;
    pixBGRA data[4] = {0x0000FFFF, 0x00FF00FF, 0xFF0000FF, 0x000000FF};
    ImageMap* map0 = new ImageMapUnfiltered(data, 2);
    texlib.inherit_map("Removeme", map0);
    const ImageMap* got = texlib.get_map("Removeme");
    ASSERT_PTR_EQ(got, map0);

    texlib.erase_map("Removeme");
    got = texlib.get_map("Removeme");
    EXPECT_PTR_NULL(got);

    texlib.erase_map("Removeme");
    got = texlib.get_map("Removeme");
    EXPECT_PTR_NULL(got);
}

SPECTRE_TEST(TextureLibrary, contains_texture)
{
    TextureLibrary texlib;
    Vec2 shift(0.f);
    Vec2 scale(1.f);
    File src(TEST_ASSETS "images/black.bmp");
    const ImageMap* map = resolve_map(&src, &texlib, UNFILTERED);
    TextureImage* tex = new TextureImage(map, shift, scale);
    texlib.inherit_texture("Contained", tex);
    bool res = texlib.contains_texture("Contained");
    EXPECT_TRUE(res);
    texlib.erase_texture("Contained");
    res = texlib.contains_texture("Contained");
    EXPECT_FALSE(res);
}

SPECTRE_TEST(TextureLibrary, contains_map)
{
    TextureLibrary texlib;
    pixBGRA data[4] = {0x0000FFFF, 0x00FF00FF, 0xFF0000FF, 0x000000FF};
    ImageMap* map0 = new ImageMapUnfiltered(data, 2);
    texlib.inherit_map("ContainedM", map0);
    bool res = texlib.contains_map("ContainedM");
    EXPECT_TRUE(res);
    texlib.erase_map("ContainedM");
    res = texlib.contains_map("ContainedM");
    EXPECT_FALSE(res);
}

SPECTRE_TEST(TextureLibrary, clear)
{
    TextureLibrary texlib;
    Vec2 shift(0.f);
    Vec2 scale(1.f);
    File src(TEST_ASSETS "images/black.bmp");
    const ImageMap* map = resolve_map(&src, &texlib, UNFILTERED);
    TextureImage* tex = new TextureImage(map, shift, scale);
    texlib.inherit_texture("Removeme", tex);
    TextureImage* tex2 = new TextureImage(map, shift, scale);
    texlib.inherit_texture("Removeme2", tex2);
    TextureImage* tex3 = new TextureImage(map, shift, scale);
    texlib.inherit_texture("Removeme3", tex3);
    pixBGRA data[4] = {0x0000FFFF, 0x00FF00FF, 0xFF0000FF, 0x000000FF};
    ImageMap* map0 = new ImageMapUnfiltered(data, 2);
    texlib.inherit_map("Removeme4", map0);
    ImageMap* map1 = new ImageMapUnfiltered(data, 2);
    texlib.inherit_map("Removeme5", map1);

    const Texture* got;
    const ImageMap* gotm;
    got = texlib.get_texture("Removeme");
    EXPECT_PTR_NOTNULL(got);
    got = texlib.get_texture("Removeme2");
    EXPECT_PTR_NOTNULL(got);
    got = texlib.get_texture("Removeme3");
    EXPECT_PTR_NOTNULL(got);
    gotm = texlib.get_map("Removeme4");
    EXPECT_PTR_NOTNULL(gotm);
    gotm = texlib.get_map("Removeme5");
    EXPECT_PTR_NOTNULL(gotm);

    texlib.clear();

    got = texlib.get_texture("Removeme");
    EXPECT_PTR_NULL(got);
    got = texlib.get_texture("Removeme2");
    EXPECT_PTR_NULL(got);
    got = texlib.get_texture("Removeme3");
    EXPECT_PTR_NULL(got);
    gotm = texlib.get_map("Removeme4");
    EXPECT_PTR_NULL(gotm);
    gotm = texlib.get_map("Removeme5");
    EXPECT_PTR_NULL(gotm);
}

SPECTRE_TEST(TextureLibrary, get_default_map)
{
    TextureLibrary texlib;
    const ImageMap* map0 = texlib.get_dflt_map();
    uint32_t tex = map0->filter(0, 0, 0, 0, 0, 0).bgra_value;
    EXPECT_EQ(tex, 0xFFFFFFFF);
}

SPECTRE_TEST(TextureLibrary, get_default_texture)
{
    TextureLibrary texlib;
    HitPoint hp;
    ColorRGB res;
    const Texture* tex0 = texlib.get_dflt_texture();
    res = tex0->map(&hp).to_xyz().to_sRGB();
    EXPECT_NEAR(res.r, 1.f, 1e-1f);
    EXPECT_NEAR(res.g, 1.f, 1e-1f);
    EXPECT_NEAR(res.b, 1.f, 1e-1f);
}

SPECTRE_TEST(TextureLibrary, size)
{
    TextureLibrary texlib;
    ASSERT_EQ(texlib.size_map(), 0);
    ASSERT_EQ(texlib.size_texture(), 0);
    File src(TEST_ASSETS "images/black.bmp");
    const ImageMap* map = resolve_map(&src, &texlib, UNFILTERED);
    TextureImage* tex = new TextureImage(map, Vec2(0.f), Vec2(1.f));
    texlib.inherit_texture("Texture", tex);
    bool res = texlib.contains_texture("Texture");
    EXPECT_TRUE(res);
    res = texlib.contains_map(src.absolute_path());
    EXPECT_TRUE(res);
    EXPECT_EQ(texlib.size_texture(), 1);
    EXPECT_EQ(texlib.size_map(), 1);
}

SPECTRE_TEST(TextureLibrary, resolve_map)
{
    TextureLibrary texlib;
    Vec2 zero(0.f);
    //not readable
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    File src0("nonexistent.bmp");
    const ImageMap* map0 = resolve_map(&src0, &texlib, UNFILTERED);
    TextureImage tex0(map0, zero, zero);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    //width != height
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    File src1(TEST_ASSETS "images/2by3.bmp");
    const ImageMap* map1 = resolve_map(&src1, &texlib, UNFILTERED);
    TextureImage tex1(map1, zero, zero);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    //width == height but not power of 2
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    File src2(TEST_ASSETS "images/3by3.bmp");
    const ImageMap* map2 = resolve_map(&src2, &texlib, UNFILTERED);
    TextureImage tex2(map2, zero, zero);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    //correct execution
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    File src3(TEST_ASSETS "images/correct.bmp");
    const ImageMap* map3 = resolve_map(&src3, &texlib, UNFILTERED);
    TextureImage tex3(map3, zero, zero);
    EXPECT_EQ(errors_count[WARNING_INDEX], 0);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_EQ(typeid(*(tex3.imagemap)).hash_code(),
              typeid(ImageMapUnfiltered).hash_code());
    //correct execution, cached
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    File src4(TEST_ASSETS "images/correct.bmp");
    const ImageMap* map4 = resolve_map(&src4, &texlib, UNFILTERED);
    TextureImage tex4(map4, zero, zero);
    EXPECT_EQ(errors_count[WARNING_INDEX], 0);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_PTR_EQ(tex3.imagemap, tex4.imagemap);
    //trilinear
    texlib.clear(); //otherwise the texture wil be cached (thus unfiltered)
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    File src5(TEST_ASSETS "images/correct.bmp");
    const ImageMap* map5 = resolve_map(&src5, &texlib, TRILINEAR);
    TextureImage tex5(map5, zero, zero);
    EXPECT_EQ(errors_count[WARNING_INDEX], 0);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_EQ(typeid(*(tex5.imagemap)).hash_code(),
              typeid(ImageMapTrilinear).hash_code());
    //ewa
    texlib.clear(); //otherwise the texture wil be cached (thus unfiltered)
    errors_count[WARNING_INDEX] = 0;
    ASSERT_EQ(errors_count[WARNING_INDEX], 0);
    File src6(TEST_ASSETS "images/correct.bmp");
    const ImageMap* map6 = resolve_map(&src6, &texlib, EWA);
    TextureImage tex6(map6, zero, zero);
    EXPECT_EQ(errors_count[WARNING_INDEX], 0);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_EQ(typeid(*(tex6.imagemap)).hash_code(),
              typeid(ImageMapEWA).hash_code());
}

SPECTRE_TEST_END(TextureLibrary)
