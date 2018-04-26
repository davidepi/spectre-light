#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#else

#include <gtest/gtest.h>

#endif

SPECTRE_TEST_INIT(MaterialLibrary_tests)

#include "materials/material_library.hpp"

SPECTRE_TEST(MaterialLibrary, add)
{
    Bsdf* mat = new Bsdf;
    MtlLib.add_inherit("New", mat);
    const Bsdf* got = MtlLib.get("New");
    EXPECT_EQ(mat, got);

    //add different with same name
    Bsdf* mat3 = new Bsdf;
    MtlLib.add_inherit("New", mat3);
    const Bsdf* got3 = MtlLib.get("New");
    EXPECT_NE(got3, mat3);
    delete mat3;
}

SPECTRE_TEST(MaterialLibrary, remove)
{
    Bsdf* mat = new Bsdf;
    MtlLib.add_inherit("Removeme", mat);
    const Bsdf* got = MtlLib.get("Removeme");
    EXPECT_EQ(mat, got);

    MtlLib.erase("Removeme");
    got = MtlLib.get("Removeme");
    EXPECT_EQ(got, nullptr);

    //this should do nothing, material already removed
    got = mat;
    MtlLib.erase("Removeme");
    got = MtlLib.get("Removeme");
    EXPECT_EQ(got, nullptr);

    got = MtlLib.get("Default");
    EXPECT_NE(got, nullptr);
    MtlLib.erase("Default");
    EXPECT_NE(got, nullptr);
}

SPECTRE_TEST(MaterialLibrary, contains)
{
    Bsdf* mat = new Bsdf;
    MtlLib.add_inherit("Contained", mat);
    bool res = MtlLib.contains("Contained");
    EXPECT_TRUE(res);
    MtlLib.erase("Contained");
    res = MtlLib.contains("Contained");
    EXPECT_FALSE(res);
}

SPECTRE_TEST(MaterialLibrary, clear)
{
    Bsdf* mat = new Bsdf();
    MtlLib.add_inherit("Removeme", mat);
    Bsdf* mat2 = new Bsdf();
    MtlLib.add_inherit("Removeme2", mat2);
    Bsdf* mat3 = new Bsdf();
    MtlLib.add_inherit("Removeme3", mat3);

    const Bsdf* got;
    got = MtlLib.get("Removeme");
    EXPECT_NE(got, nullptr);
    got = MtlLib.get("Removeme2");
    EXPECT_NE(got, nullptr);
    got = MtlLib.get("Removeme3");
    EXPECT_NE(got, nullptr);
    got = MtlLib.get("Default");
    EXPECT_NE(got, nullptr);

    MtlLib.clear();

    got = MtlLib.get("Removeme");
    EXPECT_EQ(got, nullptr);
    got = MtlLib.get("Removeme2");
    EXPECT_EQ(got, nullptr);
    got = MtlLib.get("Removeme3");
    EXPECT_EQ(got, nullptr);
    got = MtlLib.get("Default");
    EXPECT_NE(got, nullptr);
}

SPECTRE_TEST(MaterialLibrary, get_default)
{
    const Bsdf* mat0 = MtlLib.get_default();
    const Bsdf* mat1 = MtlLib.get("Default");
    EXPECT_EQ(mat0, mat1); //assert that they point to the same value
}

SPECTRE_TEST_END(MaterialLibrary)
