#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "utility/array2D.hpp"

static const int expected_order[256] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x40, 0x41, 0x42,
        0x43, 0x44, 0x45, 0x46, 0x47, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,
        0x0E, 0x0F, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x10,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x50, 0x51, 0x52, 0x53,
        0x54, 0x55, 0x56, 0x57, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
        0x1F, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x20, 0x21,
        0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x60, 0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
        0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x30, 0x31, 0x32,
        0x33, 0x34, 0x35, 0x36, 0x37, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75,
        0x76, 0x77, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x78,
        0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83,
        0x84, 0x85, 0x86, 0x87, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6,
        0xC7, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0xC8, 0xC9,
        0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0x90, 0x91, 0x92, 0x93, 0x94,
        0x95, 0x96, 0x97, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7,
        0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xD8, 0xD9, 0xDA,
        0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5,
        0xA6, 0xA7, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xA8,
        0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xE8, 0xE9, 0xEA, 0xEB,
        0xEC, 0xED, 0xEE, 0xEF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6,
        0xB7, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xB8, 0xB9,
        0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC,
        0xFD, 0xFE, 0xFF
};

SPECTRE_TEST_INIT(Array2D_tests)

SPECTRE_TEST(Array2D, corner_cases_ctor)
{
    //less than 1 block.
    const int SIDESMALL = 2;
    Array2D<int> imagesmall(SIDESMALL);
    EXPECT_EQ(imagesmall.blocks_no_side, 1U);

    //not power of 2
    const int SIDEBIG = 17;
    Array2D<int> imagebig(SIDEBIG);
    EXPECT_EQ(imagebig.blocks_no_side, 4U); //means that has been rounded to 32
}

SPECTRE_TEST(Array2D, ctor_with_init)
{
    const int SIDE = 16;
    int values[SIDE*SIDE];
    for(int i = 0; i<SIDE*SIDE; i++)
        values[i] = i;
    Array2D<int> image(values, SIDE);
    for(int y = 0; y<SIDE; y++)
        for(int x = 0; x<SIDE; x++)
            EXPECT_EQ(image.get(x, y), values[y*SIDE+x]);

    //less than 1 block
    const int SIDESMALL = 2;
    int values2[SIDESMALL*SIDESMALL];
    for(int i = 0; i<SIDESMALL*SIDESMALL; i++)
        values2[i] = i;
    Array2D<int> image2(values2, SIDESMALL);
    for(int y = 0; y<SIDESMALL; y++)
        for(int x = 0; x<SIDESMALL; x++)
            EXPECT_EQ(image2.get(x, y), values2[y*SIDESMALL+x]);

    //not power of 2
    const int SIDEBIG = 17;
    int valuesbig[SIDEBIG*SIDEBIG];
    for(int i = 0; i<SIDEBIG*SIDEBIG; i++)
        valuesbig[i] = i;
    Array2D<int> imagebig(valuesbig, SIDEBIG);
    ASSERT_EQ(imagebig.blocks_no_side, 4U);
    for(int y = 0; y<SIDEBIG; y++)
        for(int x = 0; x<SIDEBIG; x++)
            EXPECT_EQ(imagebig.get(x, y), valuesbig[y*SIDEBIG+x]);
}

SPECTRE_TEST(Array2D, getter)
{
    const int SIDE = 16;
    Array2D<int> image(SIDE);
    memset(image.data, 0, sizeof(int)*SIDE*SIDE);
    //set ordered arrays number (7 is close to 8, etc)
    for(int i = 0; i<SIDE*SIDE; i++)
        image.data[i] = i;
    //assert that the structure of the array is the same as the expected one
    for(int y = 0; y<SIDE; y++)
        for(int x = 0; x<SIDE; x++)
            EXPECT_EQ(image.get(x, y), expected_order[y*SIDE+x]);
}

SPECTRE_TEST(Array2D, setter)
{
    const int SIDE = 16;
    Array2D<int> image(SIDE);
    memset(image.data, 0, sizeof(int)*SIDE*SIDE);
    //set ordered arrays number (7 is close to 8, etc)
    for(int y = 0; y<SIDE; y++)
        for(int x = 0; x<SIDE; x++)
            image.set(x, y, expected_order[y*SIDE+x]);
    for(int i = 0; i<SIDE*SIDE; i++)
        EXPECT_EQ(image.data[i], i);
}

SPECTRE_TEST(Array2D, copy_ctor)
{
    const int SIDE = 16;
    Array2D<int> image(SIDE);
    memset(image.data, 0, sizeof(int)*SIDE*SIDE);
    for(int y = 0; y<SIDE; y++)
        for(int x = 0; x<SIDE; x++)
            image.set(x, y, expected_order[y*SIDE+x]);

    Array2D<int> image_copied(image);
    for(int y = 0; y<SIDE; y++)
        for(int x = 0; x<SIDE; x++)
            EXPECT_EQ(image_copied.get(x, y), image.get(x, y));

    //assert the two objects are not the same
    image_copied.set(0, 0, 255);
    EXPECT_NE(image_copied.get(0, 0), image.get(0, 0));
}

SPECTRE_TEST(Array2D, copy_assignment)
{
    const int SIDE = 16;
    Array2D<int> image(SIDE);
    memset(image.data, 0, sizeof(int)*SIDE*SIDE);
    for(int y = 0; y<SIDE; y++)
        for(int x = 0; x<SIDE; x++)
            image.set(x, y, expected_order[y*SIDE+x]);

    Array2D<int> image_copied = image;
    for(int y = 0; y<SIDE; y++)
        for(int x = 0; x<SIDE; x++)
            EXPECT_EQ(image_copied.get(x, y), image.get(x, y));

    //assert the two objects are not the same
    image_copied.set(0, 0, 255);
    EXPECT_NE(image_copied.get(0, 0), image.get(0, 0));
}

SPECTRE_TEST(Array2D, zero_out)
{
    const int SIDE = 64;
    Array2D<int> image(SIDE);
    image.zero_out();
    for(int i = 0; i<SIDE*SIDE; i++)
        EXPECT_EQ(image.data[i], 0);
}

SPECTRE_TEST_END(Array2D_tests)
