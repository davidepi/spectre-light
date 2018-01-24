
#include <gtest/gtest.h>


#include "materials/material_library.hpp"

TEST(MaterialLibrary,add)
{
    Bsdf* mat = new Bsdf;
    MtlLib.add_inherit("New", mat);
    const Bsdf* got = MtlLib.get("New");
    EXPECT_EQ(mat, got);

    //add different with same name
    Bsdf* mat3 = new Bsdf;
    MtlLib.add_inherit("New",mat3);
    const Bsdf* got3 = MtlLib.get("New");
    EXPECT_NE(got3, mat3);
    delete mat3;
}

TEST(MaterialLibrary,edit)
{
    Bsdf* mat = new Bsdf;
    MtlLib.add_inherit("Editme",mat);

    //found
    Bsdf* got = MtlLib.edit("Editme");
    EXPECT_EQ(got, mat);

    //not found
    Bsdf* got2 = MtlLib.edit("Not found");
    EXPECT_EQ(got2, nullptr);
}

TEST(MaterialLibrary,remove)
{
    Bsdf* mat = new Bsdf;
    MtlLib.add_inherit("Removeme",mat);
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
}

TEST(MaterialLibrary,contains)
{
    Bsdf* mat = new Bsdf;
    MtlLib.add_inherit("Contained", mat);
    bool res = MtlLib.contains("Contained");
    EXPECT_TRUE(res);
    MtlLib.erase("Contained");
    res = MtlLib.contains("Contained");
    EXPECT_FALSE(res);
}

