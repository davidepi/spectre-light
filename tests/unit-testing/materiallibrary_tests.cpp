#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "materials/material_library.hpp"
#include "primitives/sphere.hpp"

SPECTRE_TEST_INIT(MaterialLibrary_tests)

SPECTRE_TEST(MaterialLibrary, add)
{
    Bsdf* mat = new SingleBRDF(new Lambertian());
    MtlLib.add_inherit("New", mat);
    const Bsdf* got = MtlLib.get("New");
    EXPECT_PTR_EQ((const Bsdf*)mat, got);

    //add different with same name
    Bsdf* mat3 = new SingleBRDF(new Lambertian());
    MtlLib.add_inherit("New", mat3);
    const Bsdf* got3 = MtlLib.get("New");
    EXPECT_PTR_NE(got3, mat3);
    delete mat3;
    MtlLib.clear();
}

SPECTRE_TEST(MaterialLibrary, remove)
{
    Bsdf* mat = new SingleBRDF(new Lambertian());
    MtlLib.add_inherit("Removeme", mat);
    const Bsdf* got = MtlLib.get("Removeme");
    ASSERT_PTR_EQ(mat, got);

    MtlLib.erase("Removeme");
    got = MtlLib.get("Removeme");
    EXPECT_PTR_NULL(got);

    //this should do nothing, material already removed
    got = mat;
    MtlLib.erase("Removeme");
    got = MtlLib.get("Removeme");
    EXPECT_PTR_NULL(got);
    MtlLib.clear();
}

SPECTRE_TEST(MaterialLibrary, contains)
{
    Bsdf* mat = new SingleBRDF(new Lambertian());
    MtlLib.add_inherit("Contained", mat);
    bool res = MtlLib.contains("Contained");
    EXPECT_TRUE(res);
    MtlLib.erase("Contained");
    res = MtlLib.contains("Contained");
    EXPECT_FALSE(res);
    MtlLib.clear();
}

SPECTRE_TEST(MaterialLibrary, clear)
{
    Bsdf* mat = new SingleBRDF(new Lambertian());
    MtlLib.add_inherit("Removeme", mat);
    Bsdf* mat2 = new SingleBRDF(new Lambertian());
    MtlLib.add_inherit("Removeme2", mat2);
    Bsdf* mat3 = new SingleBRDF(new Lambertian());
    MtlLib.add_inherit("Removeme3", mat3);

    const Bsdf* got;
    got = MtlLib.get("Removeme");
    EXPECT_PTR_NOTNULL(got);
    got = MtlLib.get("Removeme2");
    EXPECT_PTR_NOTNULL(got);
    got = MtlLib.get("Removeme3");
    EXPECT_PTR_NOTNULL(got);

    MtlLib.clear();

    got = MtlLib.get("Removeme");
    EXPECT_PTR_NULL(got);
    got = MtlLib.get("Removeme2");
    EXPECT_PTR_NULL(got);
    got = MtlLib.get("Removeme3");
    EXPECT_PTR_NULL(got);
}

SPECTRE_TEST(MaterialLibrary, get_default)
{
    Sphere s;
    MaskBoolean mask;
    const Bsdf* mat0 = MtlLib.get_default();
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
    ASSERT_EQ(MtlLib.size(), 0);
    Bsdf* mat = new SingleBRDF(new Lambertian());
    MtlLib.add_inherit("Removeme", mat);
    EXPECT_EQ(MtlLib.size(), 1);
    MtlLib.clear();
}

SPECTRE_TEST_END(MaterialLibrary)
