#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "primitives/sphere.hpp"
#include "textures/texture_library.hpp"
#include "materials/material_library.hpp"
#include "materials/single_brdf.hpp"
#include "materials/lambertian.hpp"

SPECTRE_TEST_INIT(MaterialLibrary_tests)

SPECTRE_TEST(MaterialLibrary, add)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Bsdf* mat = new SingleBRDF(new Lambertian(), texlib.get_dflt_texture());
    mtllib.add_inherit("New", mat);
    const Bsdf* got = mtllib.get("New");
    EXPECT_PTR_EQ((const Bsdf*)mat, got);

    //add different with same name
    Bsdf* mat3 = new SingleBRDF(new Lambertian(), texlib.get_dflt_texture());
    mtllib.add_inherit("New", mat3);
    const Bsdf* got3 = mtllib.get("New");
    EXPECT_PTR_NE(got3, mat3);
    delete mat3;
}

SPECTRE_TEST(MaterialLibrary, remove)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Bsdf* mat = new SingleBRDF(new Lambertian(), texlib.get_dflt_texture());
    mtllib.add_inherit("Removeme", mat);
    const Bsdf* got = mtllib.get("Removeme");
    ASSERT_PTR_EQ(mat, got);

    mtllib.erase("Removeme");
    got = mtllib.get("Removeme");
    EXPECT_PTR_NULL(got);

    //this should do nothing, material already removed
    got = mat;
    mtllib.erase("Removeme");
    got = mtllib.get("Removeme");
    EXPECT_PTR_NULL(got);
    mtllib.clear();
}

SPECTRE_TEST(MaterialLibrary, contains)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Bsdf* mat = new SingleBRDF(new Lambertian(), texlib.get_dflt_texture());
    mtllib.add_inherit("Contained", mat);
    bool res = mtllib.contains("Contained");
    EXPECT_TRUE(res);
    mtllib.erase("Contained");
    res = mtllib.contains("Contained");
    EXPECT_FALSE(res);
}

SPECTRE_TEST(MaterialLibrary, clear)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Bsdf* mat = new SingleBRDF(new Lambertian(), texlib.get_dflt_texture());
    mtllib.add_inherit("Removeme", mat);
    Bsdf* mat2 = new SingleBRDF(new Lambertian(), texlib.get_dflt_texture());
    mtllib.add_inherit("Removeme2", mat2);
    Bsdf* mat3 = new SingleBRDF(new Lambertian(), texlib.get_dflt_texture());
    mtllib.add_inherit("Removeme3", mat3);

    const Bsdf* got;
    got = mtllib.get("Removeme");
    EXPECT_PTR_NOTNULL(got);
    got = mtllib.get("Removeme2");
    EXPECT_PTR_NOTNULL(got);
    got = mtllib.get("Removeme3");
    EXPECT_PTR_NOTNULL(got);

    mtllib.clear();

    got = mtllib.get("Removeme");
    EXPECT_PTR_NULL(got);
    got = mtllib.get("Removeme2");
    EXPECT_PTR_NULL(got);
    got = mtllib.get("Removeme3");
    EXPECT_PTR_NULL(got);
}

SPECTRE_TEST(MaterialLibrary, get_default)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    Sphere s;
    MaskBoolean mask;
    const Bsdf* mat0 = mtllib.get_default();
    Ray r(Point3(0, -10, 0), Vec3(0, 1, 0));
    float distance = FLT_MAX;
    HitPoint hp;
    ShadingSpace matrix;
    Normal normal;
    Vec3 wo(1, -1, 0);
    Vec3 wi(-1, -1, 0);
    ASSERT_TRUE(s.intersect(&r, &distance, &hp, &mask));
    mat0->gen_shading_matrix(&hp, &matrix, &normal);
    Spectrum res = mat0->value(&wo, &hp, &wi, &matrix, true);
    ColorRGB col = res.to_xyz().to_sRGB();
    EXPECT_NEAR(col.r, .65f, 1e-1f);
    EXPECT_NEAR(col.g, .65f, 1e-1f);
    EXPECT_NEAR(col.b, .65f, 1e-1f);
}

SPECTRE_TEST(MaterialLibrary, size_fun)
{
    TextureLibrary texlib;
    MaterialLibrary mtllib(texlib.get_dflt_texture());
    ASSERT_EQ(mtllib.size(), 0);
    Bsdf* mat = new SingleBRDF(new Lambertian(), texlib.get_dflt_texture());
    mtllib.add_inherit("Removeme", mat);
    EXPECT_EQ(mtllib.size(), (size_t)1);
    mtllib.clear();
    EXPECT_EQ(mtllib.size(), (size_t)0);
}

SPECTRE_TEST_END(MaterialLibrary)
