#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else
#include <gtest/gtest.h>
#endif

#include "parsers/parser_obj.hpp"
#include "primitives/mesh.hpp"

SPECTRE_TEST_INIT(ParserObj_tests)

SPECTRE_TEST(ParserObj, input_error)
{
    ParserObj parser;
    errors_count[ERROR_INDEX] = 0;
    parser.start_parsing(TEST_ASSETS "parser_obj/nonexistent.obj");
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(ParserObj, close_unopened_input)
{
    ParserObj parser;
    parser.end_parsing();
    parser.start_parsing(TEST_ASSETS "parser_obj/pyramid.obj");
    parser.end_parsing();
    //test passes if everything does not crash
    EXPECT_TRUE(true);
}

SPECTRE_TEST(ParserObj, get_next_mesh_unopened)
{
    //unopened
    ParserObj parser;
    Mesh m(1);
    EXPECT_FALSE(parser.get_next_mesh(&m));
    parser.start_parsing(TEST_ASSETS "parser_obj/nonexistent.obj");
    EXPECT_FALSE(parser.get_next_mesh(&m));
    parser.end_parsing();
}

SPECTRE_TEST(ParserObj, get_next_mesh_retval)
{
    bool res;
    ParserObj parser;
    parser.start_parsing(TEST_ASSETS "parser_obj/pyramid.obj");
    Mesh m(6);
    res = parser.get_next_mesh(&m);
    EXPECT_TRUE(res);
    res = parser.get_next_mesh(&m);
    EXPECT_FALSE(res);
    parser.end_parsing();

    parser.start_parsing(TEST_ASSETS "parser_obj/multi.obj");
    Mesh m1(6);
    Mesh m2(2);
    res = parser.get_next_mesh(&m1);
    EXPECT_TRUE(res);
    res = parser.get_next_mesh(&m2);
    EXPECT_TRUE(res);
    res = parser.get_next_mesh(&m1);
    EXPECT_FALSE(res);
    parser.end_parsing();
}

SPECTRE_TEST(ParserObj, two_vertices_face)
{
    //this method checks a broken .obj file
    //and will result in an array overflow read.
    //Being a read this will contain just garbage values that won't be used
    //but both VS and Xcode will flag this as an error and break testing
#if !defined(__VS__) && !defined(__XCODE__)
    Mesh m(1);
    ParserObj parser;
    bool res;
    parser.start_parsing(TEST_ASSETS "parser_obj/2vertface.obj");
    errors_count[ERROR_INDEX] = 0;
    res = parser.get_next_mesh(&m);
    EXPECT_EQ(res, false);
    parser.end_parsing();
#endif
}

SPECTRE_TEST(ParserObj, out_of_index)
{
    Mesh m0(1);
    Mesh m1(1);
    Mesh m2(1);
    ParserObj parser;
    bool res;

    //vertices
    parser.start_parsing(TEST_ASSETS "parser_obj/outofindex_vert.obj");
    errors_count[ERROR_INDEX] = 0;
    res = parser.get_next_mesh(&m0);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    EXPECT_EQ(res, false);
    errors_count[ERROR_INDEX] = 0;
    parser.end_parsing();
    //normals
    parser.start_parsing(TEST_ASSETS "parser_obj/outofindex_norm.obj");
    errors_count[ERROR_INDEX] = 0;
    res = parser.get_next_mesh(&m1);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    EXPECT_EQ(res, false);
    errors_count[ERROR_INDEX] = 0;
    parser.end_parsing();
    //textures
    parser.start_parsing(TEST_ASSETS "parser_obj/outofindex_text.obj");
    errors_count[ERROR_INDEX] = 0;
    res = parser.get_next_mesh(&m2);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    EXPECT_EQ(res, false);
    errors_count[ERROR_INDEX] = 0;
    parser.end_parsing();
}

SPECTRE_TEST(ParserObj, get_next_obj_tris)
{
    bool res;
    ParserObj parser;
    parser.start_parsing(TEST_ASSETS "parser_obj/pyramid.obj");
    Mesh m(6);
    res = parser.get_next_mesh(&m);
    EXPECT_NEAR(m.surface(), 3.2360679775f, 1e-5f);
    EXPECT_TRUE(res);
    parser.end_parsing();
}

SPECTRE_TEST(ParserObj, triangulate)
{
    bool res;
    ParserObj parser;
    parser.start_parsing(TEST_ASSETS "parser_obj/ngon.obj");
    Mesh m(6);
    res = parser.get_next_mesh(&m);
    EXPECT_EQ(parser.get_face_no(), 14U);
    EXPECT_NEAR(m.surface(), 8.221780f, 1e-5f);
    EXPECT_TRUE(res);
    parser.end_parsing();
}

SPECTRE_TEST(ParserObj, negative_tris_index)
{
    bool res;
    ParserObj parser;
    parser.start_parsing(TEST_ASSETS "parser_obj/neg_vertices.obj");
    Mesh m(6);
    res = parser.get_next_mesh(&m);
    EXPECT_NEAR(m.surface(), 3.2360679775f, 1e-5f);
    EXPECT_TRUE(res);
    parser.end_parsing();
}

SPECTRE_TEST(ParserObj, multiple_meshes)
{
    bool res;
    ParserObj parser;
    parser.start_parsing(TEST_ASSETS "parser_obj/multi.obj");
    Mesh m0(1);
    Mesh m1(1);
    res = parser.get_next_mesh(&m0);
    ASSERT_TRUE(res);
    res = parser.get_next_mesh(&m1);
    ASSERT_TRUE(res);
    EXPECT_NEAR(m0.surface(), 24.f, 1e-5f);
    EXPECT_NEAR(m1.surface(), 24.f, 1e-5f);
    parser.end_parsing();
}

SPECTRE_TEST(ParserObj, textures)
{
    //can't test correctness for textures... so I'll put a multiobject in the
    //same file. If textures are parsed wrongly the second object will have
    //wrong vertices
    bool res;
    ParserObj parser;
    parser.start_parsing(TEST_ASSETS "parser_obj/textures.obj");
    Mesh m0(1);
    Mesh m1(1);
    res = parser.get_next_mesh(&m0);
    EXPECT_TRUE(res);
    res = parser.get_next_mesh(&m1);
    EXPECT_TRUE(res);
    EXPECT_NEAR(m1.surface(), 3.2360679775f, 1e-5f);
    parser.end_parsing();
}

SPECTRE_TEST(ParserObj, normal_reconstruction)
{
    bool res;
    ParserObj parser;
    parser.start_parsing(TEST_ASSETS "parser_obj/nonormal.obj");
    Mesh m(6);
    res = parser.get_next_mesh(&m);
    ASSERT_TRUE(res);
    float densities[6];
    Matrix4 mat;
    mat.set_identity();
    m.get_densities_array(&mat, densities);
    Point3 p;
    Normal n;
    m.sample_point(0.f, 0.f, densities, &p, &n);
    EXPECT_NEAR(n.x, 0.f, 1e-5f);
    EXPECT_NEAR(n.y, 0.f, 1e-5f);
    EXPECT_NEAR(n.z, -1.f, 1e-5f);
    parser.end_parsing();
}

SPECTRE_TEST(ParserObj, get_object_name)
{
    //object name with g
    bool res;
    ParserObj parser;
    parser.start_parsing(TEST_ASSETS "parser_obj/multi.obj");
    Mesh m(6);
    Mesh m1(6);
    res = parser.get_next_mesh(&m);
    EXPECT_STREQ(parser.get_mesh_name().c_str(), "Cube.001");
    EXPECT_TRUE(res);
    res = parser.get_next_mesh(&m1);
    EXPECT_STREQ(parser.get_mesh_name().c_str(), "Cube");
    EXPECT_TRUE(res);
    parser.end_parsing();

    parser.start_parsing(TEST_ASSETS "parser_obj/pyramid_o.obj");
    Mesh m2(6);
    res = parser.get_next_mesh(&m2);
    EXPECT_STREQ(parser.get_mesh_name().c_str(), "SquarePyr");
    EXPECT_TRUE(res);
    parser.end_parsing();
}

SPECTRE_TEST(ParserObj, get_face_number)
{
    //object name with g
    bool res;
    ParserObj parser;
    parser.start_parsing(TEST_ASSETS "parser_obj/pyramid.obj");
    Mesh m(6);
    res = parser.get_next_mesh(&m);
    EXPECT_EQ(parser.get_face_no(), 6U);
    EXPECT_TRUE(res);
    parser.end_parsing();
}

SPECTRE_TEST(ParserObj, get_material_no)
{
    //push some materials used in the file into the library
    Bsdf* mat0 = new SingleBRDF();
    Bsdf* mat1 = new SingleBRDF();
    Bsdf* mat2 = new SingleBRDF();
    mat0->inherit_bdf(new Lambertian());
    mat1->inherit_bdf(new Lambertian());
    mat2->inherit_bdf(new Lambertian());
    MtlLib.add_inherit("Red", mat0);
    MtlLib.add_inherit("Green", mat1);
    MtlLib.add_inherit("Blue", mat2);
    ParserObj parser;
    bool res;

    //with default material and unused, should be shrinked to have only 1 entry
    parser.start_parsing(TEST_ASSETS "parser_obj/multimat.obj");
    Mesh m(6);
    res = parser.get_next_mesh(&m);
    EXPECT_EQ(parser.get_material_no(), (unsigned char)3);
    EXPECT_TRUE(res);
    parser.end_parsing();

    //no default material
    parser.start_parsing(TEST_ASSETS "parser_obj/multimat_nodflt.obj");
    Mesh m1(6);
    res = parser.get_next_mesh(&m1);
    EXPECT_EQ(parser.get_material_no(), (unsigned char)3);
    EXPECT_TRUE(res);
    parser.end_parsing();

    MtlLib.clear();
}

SPECTRE_TEST(ParserObj, get_materials)
{
    //push some materials used in the file into the library
    Bsdf* mat0 = new SingleBRDF();
    Bsdf* mat1 = new SingleBRDF();
    Bsdf* mat2 = new SingleBRDF();
    mat0->inherit_bdf(new Lambertian());
    mat1->inherit_bdf(new Lambertian());
    mat2->inherit_bdf(new Lambertian());
    MtlLib.add_inherit("Red", mat0);
    MtlLib.add_inherit("Green", mat1);
    MtlLib.add_inherit("Blue", mat2);
    ParserObj parser;
    bool res;

    parser.start_parsing(TEST_ASSETS "parser_obj/multimat.obj");
    Mesh m(6);
    res = parser.get_next_mesh(&m);
    const Bsdf** mats = new const Bsdf* [parser.get_material_no()];
    parser.get_materials(mats);
    EXPECT_PTR_EQ(mats[0], MtlLib.get_default());
    EXPECT_PTR_EQ(mats[1], MtlLib.get("Red"));
    EXPECT_PTR_EQ(mats[2], MtlLib.get("Green"));
    EXPECT_TRUE(res);
    delete[] mats;
    parser.end_parsing();

    parser.start_parsing(TEST_ASSETS "parser_obj/multimat_nodflt.obj");
    Mesh m1(6);
    res = parser.get_next_mesh(&m1);
    const Bsdf** mats2 = new const Bsdf* [parser.get_material_no()];
    parser.get_materials(mats2);
    EXPECT_PTR_EQ(mats2[0], MtlLib.get("Blue"));
    EXPECT_PTR_EQ(mats2[1], MtlLib.get("Green"));
    EXPECT_PTR_EQ(mats2[2], MtlLib.get("Red"));
    EXPECT_TRUE(res);
    delete[] mats2;
    parser.end_parsing();

    MtlLib.clear();
}

SPECTRE_TEST(ParserObj, get_material_association)
{
    //push some materials used in the file into the library
    Bsdf* mat0 = new SingleBRDF();
    Bsdf* mat1 = new SingleBRDF();
    Bsdf* mat2 = new SingleBRDF();
    mat0->inherit_bdf(new Lambertian());
    mat1->inherit_bdf(new Lambertian());
    mat2->inherit_bdf(new Lambertian());
    MtlLib.add_inherit("Red", mat0);
    MtlLib.add_inherit("Green", mat1);
    MtlLib.add_inherit("Blue", mat2);
    ParserObj parser;
    bool res;

    //dflt
    parser.start_parsing(TEST_ASSETS "parser_obj/multimat.obj");
    Mesh m(6);
    res = parser.get_next_mesh(&m);
    unsigned char* assoc = new unsigned char[parser.get_face_no()];
    parser.get_material_association(assoc);
    parser.end_parsing();
    EXPECT_EQ(assoc[0], (unsigned char)0);
    EXPECT_EQ(assoc[1], (unsigned char)0);
    EXPECT_EQ(assoc[2], (unsigned char)0);
    EXPECT_EQ(assoc[3], (unsigned char)1);
    EXPECT_EQ(assoc[4], (unsigned char)0);
    EXPECT_EQ(assoc[5], (unsigned char)2);
    EXPECT_TRUE(res);

    //no dflt
    parser.start_parsing(TEST_ASSETS "parser_obj/multimat_nodflt.obj");
    Mesh m1(6);
    res = parser.get_next_mesh(&m1);


    unsigned char* assoc2 = new unsigned char[parser.get_face_no()];
    parser.get_material_association(assoc2);
    parser.end_parsing();
    EXPECT_EQ(assoc2[0], (unsigned char)0);
    EXPECT_EQ(assoc2[1], (unsigned char)0);
    EXPECT_EQ(assoc2[2], (unsigned char)1);
    EXPECT_EQ(assoc2[3], (unsigned char)2);
    EXPECT_EQ(assoc2[4], (unsigned char)0);
    EXPECT_EQ(assoc2[5], (unsigned char)1);
    EXPECT_TRUE(res);

    MtlLib.clear();
}

SPECTRE_TEST(ParserObj, no_name)
{
    Mesh m0(1);
    ParserObj parser;
    bool res;
    parser.start_parsing(TEST_ASSETS "parser_obj/noname.obj");
    res = parser.get_next_mesh(&m0);
    EXPECT_EQ(res, true);
    EXPECT_EQ(parser.get_material_no(), (unsigned char)1);
    EXPECT_STREQ(parser.get_mesh_name().c_str(), "Unnamed");
    EXPECT_EQ(parser.get_face_no(), 1U);
    parser.end_parsing();
}

SPECTRE_TEST_END(ParserObj_tests)
