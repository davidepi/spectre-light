#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#include <io.h>
#define unlink _unlink
#else

#include <gtest/gtest.h>

#endif

extern "C" {
#include "utility/imageio/imageio.h"
}

#include "utility/utility.hpp"
#include <cstdio>
#include <climits>

static const uint8_t write_data[300] = {
        0xD7, 0xF7, 0x40, 0x17, 0xE9, 0x85, 0x75, 0xE0, 0x3F, 0xEE, 0x22, 0xAE,
        0xD6, 0xD9, 0x1B, 0x23, 0x83, 0xB1, 0x81, 0xC7, 0x78, 0x77, 0xFE, 0xDD,
        0xBF, 0xE1, 0x81, 0x8E, 0x0E, 0xB3, 0xD0, 0xB2, 0xA0, 0xA8, 0x36, 0x67,
        0x84, 0xE6, 0xD4, 0x8E, 0x5F, 0x89, 0x86, 0x0C, 0xEC, 0x5E, 0x3E, 0xAB,
        0x96, 0x2E, 0x42, 0x7A, 0x9B, 0x6C, 0xCD, 0x67, 0x5A, 0x8F, 0x31, 0x48,
        0xA5, 0xC6, 0xDD, 0xCC, 0xB4, 0x09, 0xF6, 0x26, 0xEE, 0xE4, 0x66, 0xC0,
        0xBC, 0xA8, 0xE1, 0x90, 0x47, 0x1D, 0x1B, 0x9A, 0xB5, 0xAF, 0xCC, 0xB4,
        0x3B, 0xA7, 0x03, 0x9B, 0x5B, 0x84, 0x27, 0x6C, 0x7A, 0x82, 0x69, 0xE5,
        0xD4, 0x88, 0xAA, 0x99, 0x7F, 0x2A, 0xD0, 0x2F, 0x06, 0x04, 0xAD, 0xA5,
        0xBA, 0x5F, 0xCC, 0xC8, 0x69, 0x9B, 0xEC, 0xBD, 0xC0, 0x8A, 0x06, 0xC4,
        0x62, 0x7D, 0xD9, 0x5F, 0x1F, 0x0F, 0x77, 0xD9, 0xAD, 0x99, 0xB4, 0x2B,
        0x92, 0x72, 0x1E, 0x3A, 0xBF, 0x6A, 0xB5, 0xE5, 0x3E, 0x93, 0x29, 0x0A,
        0x44, 0x33, 0x39, 0xCE, 0x7B, 0x61, 0x02, 0x6C, 0x8E, 0x5D, 0x24, 0x2D,
        0x95, 0xF8, 0xEA, 0xB9, 0xB9, 0xB3, 0xD2, 0xEA, 0x2F, 0x20, 0x2B, 0x6B,
        0xCF, 0xED, 0xD8, 0xE8, 0xC6, 0x78, 0x86, 0x69, 0xD6, 0x4D, 0x2B, 0x15,
        0xE2, 0x3D, 0x32, 0x8A, 0xB7, 0x1D, 0x63, 0x44, 0x01, 0x34, 0xCE, 0x62,
        0xE8, 0xF9, 0x61, 0xD7, 0x84, 0x97, 0x6D, 0x07, 0x48, 0xA9, 0x8C, 0x57,
        0x2C, 0xC2, 0x24, 0x99, 0x99, 0x4B, 0xCD, 0x37, 0x89, 0x8F, 0x89, 0x7B,
        0xFE, 0xC9, 0x5D, 0x6F, 0x17, 0xF3, 0xAB, 0xF4, 0xB5, 0xDB, 0xDD, 0x5E,
        0xC1, 0x7F, 0x13, 0x9F, 0x24, 0xCF, 0x76, 0x7A, 0x60, 0xE9, 0xB7, 0x2A,
        0x7A, 0x45, 0xB1, 0x53, 0xE7, 0x00, 0x43, 0xDB, 0xAA, 0x59, 0x4E, 0xD3,
        0x93, 0xE1, 0x7D, 0x93, 0x33, 0xE2, 0xC7, 0xD3, 0x1C, 0xC2, 0x8E, 0x3B,
        0x5B, 0xDB, 0x16, 0x3F, 0x64, 0x4B, 0x72, 0xEA, 0x05, 0x7E, 0xFC, 0x5B,
        0x69, 0xB7, 0x73, 0x6C, 0x3E, 0x24, 0xD0, 0xF7, 0x3D, 0x03, 0x6D, 0x43,
        0x0B, 0x10, 0xEB, 0xF6, 0xA4, 0x28, 0x43, 0xAE, 0x1C, 0x8C, 0xCA, 0x04
};

SPECTRE_TEST_INIT(ImageIO_tests)

SPECTRE_TEST(ImageIO, image_supported_func)
{
    bool res;
    res = img_supported("ppm");
    EXPECT_TRUE(res);
    res = img_supported("bmp");
    EXPECT_TRUE(res);
    res = img_supported("tga");
    EXPECT_TRUE(res);
#ifdef JPEG_FOUND
    res = img_supported("jpg");
    EXPECT_TRUE(res);
    res = img_supported("jpeg");
    EXPECT_TRUE(res);
#endif
#ifdef PNG_FOUND
    res = img_supported("png");
    EXPECT_TRUE(res);
#endif
#ifdef TIFF_FOUND
    res = img_supported("tif");
    EXPECT_TRUE(res);
    res = img_supported("tiff");
    EXPECT_TRUE(res);
#endif
    res = img_supported("dds");
    EXPECT_FALSE(res);
}

SPECTRE_TEST(ImageIO, ppm_valid_func)
{
    bool res;
    res = img_valid("nonexistent.ppm", "ppm");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/wrong_magic1.ppm", "ppm");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/binary.ppm", "ppm");
    EXPECT_TRUE(res);
    res = img_valid(TEST_ASSETS "images/multiple_spaces.ppm", "ppm");
    EXPECT_TRUE(res);
}

SPECTRE_TEST(ImageIO, ppm_dimensions_func)
{
    int width;
    int height;
    int res;
    //non existent
    res = img_dimensions("nonexistent.ppm", "ppm", &width, &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    //first letter of the magic number is wrong
    res = img_dimensions(TEST_ASSETS "images/wrong_magic1.ppm", "ppm",
                         &width, &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    //second letter of the magic number is wrong
    res = img_dimensions(TEST_ASSETS "images/wrong_magic2.ppm", "ppm",
                         &width, &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    //multiple spaces in the image
    res = img_dimensions(TEST_ASSETS "images/multiple_spaces.ppm", "ppm",
                         &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    EXPECT_TRUE(res);
    width = 0;
    height = 0;
    //binary image
    res = img_dimensions(TEST_ASSETS "images/binary.ppm", "ppm",
                         &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    EXPECT_TRUE(res);
    width = 0;
    height = 0;
}

SPECTRE_TEST(ImageIO, ppm_read_func)
{
    int res;
    //+1 is used later to check stack overflows
    uint8_t data[4*3+1];
    //non existent
    res = img_read8("nonexistent.ppm", "ppm", data, NULL);
    EXPECT_FALSE(res);
    //first letter of the magic number is wrong
    res = img_read8(TEST_ASSETS "images/wrong_magic1.ppm", "ppm", data, NULL);
    EXPECT_FALSE(res);
    //second letter of the magic number is wrong
    res = img_read8(TEST_ASSETS "images/wrong_magic2.ppm", "ppm", data, NULL);
    EXPECT_FALSE(res);
    //read image with normal depth (ASCII)
    res = img_read8(TEST_ASSETS "images/multiple_spaces.ppm", "ppm", data,
                    NULL);
    EXPECT_EQ(data[0], (uint8_t)255);
    EXPECT_EQ(data[1], (uint8_t)0);
    EXPECT_EQ(data[2], (uint8_t)0);
    EXPECT_EQ(data[3], (uint8_t)0);
    EXPECT_EQ(data[4], (uint8_t)255);
    EXPECT_EQ(data[5], (uint8_t)0);
    EXPECT_EQ(data[6], (uint8_t)0);
    EXPECT_EQ(data[7], (uint8_t)0);
    EXPECT_EQ(data[8], (uint8_t)255);
    EXPECT_EQ(data[9], (uint8_t)0);
    EXPECT_EQ(data[10], (uint8_t)0);
    EXPECT_EQ(data[11], (uint8_t)0);
    EXPECT_TRUE(res);
    memset(data, 0, 12);
    //read image with high depth (ASCII)
    res = img_read8(TEST_ASSETS "images/p3_high_depth.ppm", "ppm", data, NULL);
    EXPECT_EQ(data[0], (uint8_t)255);
    EXPECT_EQ(data[1], (uint8_t)255);
    EXPECT_EQ(data[2], (uint8_t)255);
    EXPECT_EQ(data[3], (uint8_t)0);
    EXPECT_EQ(data[4], (uint8_t)0);
    EXPECT_EQ(data[5], (uint8_t)0);
    EXPECT_EQ(data[6], (uint8_t)0);
    EXPECT_EQ(data[7], (uint8_t)0);
    EXPECT_EQ(data[8], (uint8_t)0);
    EXPECT_EQ(data[9], (uint8_t)255);
    EXPECT_EQ(data[10], (uint8_t)255);
    EXPECT_EQ(data[11], (uint8_t)255);
    EXPECT_TRUE(res);
    memset(data, 0, 12);
    //read image with normal depth (binary) no stack_overflow
    res = img_read8(TEST_ASSETS "images/binary.ppm", "ppm", data, NULL);
    EXPECT_EQ(data[0], (uint8_t)255);
    EXPECT_EQ(data[1], (uint8_t)0);
    EXPECT_EQ(data[2], (uint8_t)0);
    EXPECT_EQ(data[3], (uint8_t)0);
    EXPECT_EQ(data[4], (uint8_t)255);
    EXPECT_EQ(data[5], (uint8_t)0);
    EXPECT_EQ(data[6], (uint8_t)0);
    EXPECT_EQ(data[7], (uint8_t)0);
    EXPECT_EQ(data[8], (uint8_t)255);
    EXPECT_EQ(data[9], (uint8_t)0);
    EXPECT_EQ(data[10], (uint8_t)0);
    EXPECT_EQ(data[11], (uint8_t)0);
    EXPECT_TRUE(res);
    memset(data, 0, 12);
    //read image that claims to be 2x2 but contains a lot more
    //bytes
    data[4*3] = 0x2B; //random val, check that this is unchanged
    res = img_read8(TEST_ASSETS "images/binary_stackoverflow.ppm", "ppm", data,
                    NULL);
    EXPECT_EQ(data[0], (uint8_t)255);
    EXPECT_EQ(data[1], (uint8_t)255);
    EXPECT_EQ(data[2], (uint8_t)255);
    EXPECT_EQ(data[3], (uint8_t)0);
    EXPECT_EQ(data[4], (uint8_t)0);
    EXPECT_EQ(data[5], (uint8_t)0);
    EXPECT_EQ(data[6], (uint8_t)0);
    EXPECT_EQ(data[7], (uint8_t)0);
    EXPECT_EQ(data[8], (uint8_t)0);
    EXPECT_EQ(data[9], (uint8_t)255);
    EXPECT_EQ(data[10], (uint8_t)255);
    EXPECT_EQ(data[11], (uint8_t)255);
    EXPECT_EQ(data[12], (uint8_t)0x2B); //assert no stack overflow
    EXPECT_TRUE(res);
    memset(data, 0, 12);
    //read image with high depth (binary) no stack_overflow
    res = img_read8(TEST_ASSETS "images/p6_high_depth.ppm", "ppm", data, NULL);
    EXPECT_EQ(data[0], (uint8_t)255);
    EXPECT_EQ(data[1], (uint8_t)255);
    EXPECT_EQ(data[2], (uint8_t)255);
    EXPECT_EQ(data[3], (uint8_t)0);
    EXPECT_EQ(data[4], (uint8_t)0);
    EXPECT_EQ(data[5], (uint8_t)0);
    EXPECT_EQ(data[6], (uint8_t)0);
    EXPECT_EQ(data[7], (uint8_t)0);
    EXPECT_EQ(data[8], (uint8_t)0);
    EXPECT_EQ(data[9], (uint8_t)255);
    EXPECT_EQ(data[10], (uint8_t)255);
    EXPECT_EQ(data[11], (uint8_t)255);
    EXPECT_TRUE(res);
    memset(data, 0, 12);
    //read image with high depth (binary), stack_overflow
    res = img_read8(TEST_ASSETS "images/p6_high_depth_stack_overflow.ppm",
                    "ppm", data, NULL);
    EXPECT_EQ(data[0], (uint8_t)255);
    EXPECT_EQ(data[1], (uint8_t)255);
    EXPECT_EQ(data[2], (uint8_t)255);
    EXPECT_EQ(data[3], (uint8_t)0);
    EXPECT_EQ(data[4], (uint8_t)0);
    EXPECT_EQ(data[5], (uint8_t)0);
    EXPECT_EQ(data[6], (uint8_t)0);
    EXPECT_EQ(data[7], (uint8_t)0);
    EXPECT_EQ(data[8], (uint8_t)0);
    EXPECT_EQ(data[9], (uint8_t)255);
    EXPECT_EQ(data[10], (uint8_t)255);
    EXPECT_EQ(data[11], (uint8_t)255);
    EXPECT_EQ(data[12], (uint8_t)0x2B); //assert no stack overflow
    EXPECT_TRUE(res);
    memset(data, 0, 12);
}

SPECTRE_TEST(ImageIO, ppm_write_func)
{
    uint8_t read_data[300];
    bool res;
    res = img_write("test.ppm", "ppm", 10, 10, write_data);
    ASSERT_TRUE(res);
    res = img_read8("test.ppm", "ppm", read_data, NULL);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.ppm"), 0);
    for(int i = 0; i<300; i++)
        EXPECT_EQ(read_data[i], write_data[i]);

    //non existent folder
    res = img_write("/root/nonexistent/test.ppm", "ppm", 10, 10, write_data);
    EXPECT_FALSE(res);
}

SPECTRE_TEST(ImageIO, bmp_valid_func)
{
    bool res;
    res = img_valid("nonexistent.ppm", "bmp");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/wrong_magic1.bmp", "bmp");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/wrong_magic2.bmp", "bmp");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/os2.bmp", "bmp");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/correct.bmp", "bmp");
    EXPECT_TRUE(res);
    res = img_valid(TEST_ASSETS "images/flipped.bmp", "bmp");
    EXPECT_TRUE(res);
    res = img_valid(TEST_ASSETS "images/32bit.bmp", "bmp");
    EXPECT_TRUE(res);
}

SPECTRE_TEST(ImageIO, bmp_dimensions_func)
{
    int width;
    int height;
    bool res;
    //non existent
    res = img_dimensions("nonexistent.bmp", "bmp", &width, &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    //first letter of the magic number is wrong
    res = img_dimensions(TEST_ASSETS "images/wrong_magic1.bmp", "bmp", &width,
                         &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    //second letter of the magic number is wrong
    res = img_dimensions(TEST_ASSETS "images/wrong_magic2.bmp", "bmp", &width,
                         &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    //os2
    res = img_dimensions(TEST_ASSETS "images/os2.bmp", "bmp", &width, &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    //normal image
    res = img_dimensions(TEST_ASSETS "images/correct.bmp", "bmp", &width,
                         &height);
    EXPECT_TRUE(res);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
    //flipped (negative) rows
    res = img_dimensions(TEST_ASSETS "images/flipped.bmp", "bmp", &width,
                         &height);
    EXPECT_TRUE(res);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
    //32bit
    res = img_dimensions(TEST_ASSETS "images/32bit.bmp", "bmp", &width,
                         &height);
    EXPECT_TRUE(res);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
}

SPECTRE_TEST(ImageIO, bmp_read_func)
{
    int res;
    uint8_t values[4*3];
    uint8_t alpha[4];
    //non existent
    res = img_read8("nonexistent.bmp", "bmp", values, NULL);
    EXPECT_EQ(res, 0);
    //first letter of the magic number is wrong
    res = img_read8(TEST_ASSETS "images/wrong_magic1.bmp", "bmp", values,
                    NULL);
    EXPECT_EQ(res, 0);
    //second letter of the magic number is wrong
    res = img_read8(TEST_ASSETS "images/wrong_magic2.bmp", "bmp", values,
                    NULL);
    EXPECT_EQ(res, 0);
    //os2
    res = img_read8(TEST_ASSETS "images/os2.bmp", "bmp", values, NULL);
    EXPECT_EQ(res, 0);
    //normal image
    res = img_read8(TEST_ASSETS "images/correct.bmp", "bmp", values, NULL);
    EXPECT_EQ(values[0], (uint8_t)255);
    EXPECT_EQ(values[1], (uint8_t)0);
    EXPECT_EQ(values[2], (uint8_t)0);
    EXPECT_EQ(values[3], (uint8_t)0);
    EXPECT_EQ(values[4], (uint8_t)255);
    EXPECT_EQ(values[5], (uint8_t)0);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)0);
    EXPECT_EQ(values[8], (uint8_t)255);
    EXPECT_EQ(values[9], (uint8_t)0);
    EXPECT_EQ(values[10], (uint8_t)0);
    EXPECT_EQ(values[11], (uint8_t)0);
    EXPECT_EQ(res, 1);
    //flipped (negative) rows
    res = img_read8(TEST_ASSETS "images/flipped.bmp", "bmp", values, NULL);
    EXPECT_EQ(values[0], (uint8_t)255);
    EXPECT_EQ(values[1], (uint8_t)0);
    EXPECT_EQ(values[2], (uint8_t)0);
    EXPECT_EQ(values[3], (uint8_t)0);
    EXPECT_EQ(values[4], (uint8_t)255);
    EXPECT_EQ(values[5], (uint8_t)0);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)0);
    EXPECT_EQ(values[8], (uint8_t)255);
    EXPECT_EQ(values[9], (uint8_t)0);
    EXPECT_EQ(values[10], (uint8_t)0);
    EXPECT_EQ(values[11], (uint8_t)0);
    EXPECT_EQ(res, 1);
    //32bit - NULL alpha array
    res = img_read8(TEST_ASSETS "images/32bit.bmp", "bmp", values, NULL);
    EXPECT_EQ(values[0], (uint8_t)255);
    EXPECT_EQ(values[1], (uint8_t)0);
    EXPECT_EQ(values[2], (uint8_t)0);
    EXPECT_EQ(values[3], (uint8_t)0);
    EXPECT_EQ(values[4], (uint8_t)255);
    EXPECT_EQ(values[5], (uint8_t)0);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)0);
    EXPECT_EQ(values[8], (uint8_t)255);
    EXPECT_EQ(values[9], (uint8_t)0);
    EXPECT_EQ(values[10], (uint8_t)0);
    EXPECT_EQ(values[11], (uint8_t)0);
    EXPECT_EQ(res, 1);
    //32bit - alpha array
    res = img_read8(TEST_ASSETS "images/32bit.bmp", "bmp", values, alpha);
    EXPECT_EQ(values[0], (uint8_t)255);
    EXPECT_EQ(values[1], (uint8_t)0);
    EXPECT_EQ(values[2], (uint8_t)0);
    EXPECT_EQ(values[3], (uint8_t)0);
    EXPECT_EQ(values[4], (uint8_t)255);
    EXPECT_EQ(values[5], (uint8_t)0);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)0);
    EXPECT_EQ(values[8], (uint8_t)255);
    EXPECT_EQ(values[9], (uint8_t)0);
    EXPECT_EQ(values[10], (uint8_t)0);
    EXPECT_EQ(values[11], (uint8_t)0);
    EXPECT_EQ(alpha[0], 255);
    EXPECT_EQ(alpha[1], 128);
    EXPECT_EQ(alpha[2], 66);
    EXPECT_EQ(alpha[3], 33);
    EXPECT_EQ(res, 2);
}

SPECTRE_TEST(ImageIO, bmp_write_func)
{
    uint8_t read_data[300];
    bool res;
    res = img_write("test.bmp", "bmp", 10, 10, write_data);
    ASSERT_TRUE(res);
    res = img_read8("test.bmp", "bmp", read_data, NULL);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.bmp"), 0);
    for(int i = 0; i<300; i++)
        EXPECT_EQ(read_data[i], write_data[i]);

    //non existent folder
    res = img_write("/root/nonexistent/test.bmp", "bmp", 10, 10, write_data);
    EXPECT_FALSE(res);
}

SPECTRE_TEST(ImageIO, tga_valid_func)
{
    bool res;
    res = img_valid("nonexistent.tga", "tga");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/bmpastga.tga", "tga");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/16bit.tga", "tga");
    EXPECT_TRUE(res);
    res = img_valid(TEST_ASSETS "images/24bit.tga", "tga");
    EXPECT_TRUE(res);
    res = img_valid(TEST_ASSETS "images/32bit.tga", "tga");
    EXPECT_TRUE(res);
    res = img_valid(TEST_ASSETS "images/16bitRLE.tga", "tga");
    EXPECT_TRUE(res);
    res = img_valid(TEST_ASSETS "images/24bitRLE.tga", "tga");
    EXPECT_TRUE(res);
    res = img_valid(TEST_ASSETS "images/32bitRLE.tga", "tga");
    EXPECT_TRUE(res);
}

SPECTRE_TEST(ImageIO, tga_dimensions_func)
{
    int width;
    int height;
    bool res;
    res = img_dimensions("nonexistent.tga", "tga", &width, &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    res = img_dimensions(TEST_ASSETS "images/bmpastga.tga", "tga", &width,
                         &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    //16bit
    res = img_dimensions(TEST_ASSETS "images/16bit.tga", "tga", &width,
                         &height);
    EXPECT_TRUE(res);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
    //24 bit
    res = img_dimensions(TEST_ASSETS "images/24bit.tga", "tga", &width,
                         &height);
    EXPECT_TRUE(res);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
    //32bit
    res = img_dimensions(TEST_ASSETS "images/32bit.tga", "tga", &width,
                         &height);
    EXPECT_TRUE(res);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
    //16bit
    res = img_dimensions(TEST_ASSETS "images/16bitRLE.tga", "tga", &width,
                         &height);
    EXPECT_TRUE(res);
    EXPECT_EQ(width, 10);
    EXPECT_EQ(height, 10);
    width = 0;
    height = 0;
    //24 bit
    res = img_dimensions(TEST_ASSETS "images/24bitRLE.tga", "tga", &width,
                         &height);
    EXPECT_TRUE(res);
    EXPECT_EQ(width, 10);
    EXPECT_EQ(height, 10);
    width = 0;
    height = 0;
    //32bit
    res = img_dimensions(TEST_ASSETS "images/32bitRLE.tga", "tga", &width,
                         &height);
    EXPECT_TRUE(res);
    EXPECT_EQ(width, 10);
    EXPECT_EQ(height, 10);
    width = 0;
    height = 0;
}

SPECTRE_TEST(ImageIO, tga_read_func)
{
    int res;
    uint8_t values[12];
    uint8_t alpha[4];
    res = -1;
    res = img_read8("nonexistent.tga", "tga", values, NULL);
    EXPECT_EQ(res, 0);
    res = -1;
    res = img_read8("bmpastga.tga", "tga", values, NULL);
    EXPECT_EQ(res, 0);
    //normal image
    res = -1;
    res = img_read8(TEST_ASSETS "images/24bit.tga", "tga", values, NULL);
    EXPECT_EQ(values[0], (uint8_t)255);
    EXPECT_EQ(values[1], (uint8_t)0);
    EXPECT_EQ(values[2], (uint8_t)0);
    EXPECT_EQ(values[3], (uint8_t)0);
    EXPECT_EQ(values[4], (uint8_t)255);
    EXPECT_EQ(values[5], (uint8_t)0);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)0);
    EXPECT_EQ(values[8], (uint8_t)255);
    EXPECT_EQ(values[9], (uint8_t)0);
    EXPECT_EQ(values[10], (uint8_t)0);
    EXPECT_EQ(values[11], (uint8_t)0);
    EXPECT_EQ(res, 1);
    //32 bit no alpha array
    res = -1;
    res = img_read8(TEST_ASSETS "images/32bit.tga", "tga", values, NULL);
    EXPECT_EQ(values[0], (uint8_t)255);
    EXPECT_EQ(values[1], (uint8_t)0);
    EXPECT_EQ(values[2], (uint8_t)0);
    EXPECT_EQ(values[3], (uint8_t)0);
    EXPECT_EQ(values[4], (uint8_t)255);
    EXPECT_EQ(values[5], (uint8_t)0);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)0);
    EXPECT_EQ(values[8], (uint8_t)255);
    EXPECT_EQ(values[9], (uint8_t)0);
    EXPECT_EQ(values[10], (uint8_t)0);
    EXPECT_EQ(values[11], (uint8_t)0);
    EXPECT_EQ(res, 1);
    //32 bit alpha array
    res = -1;
    res = img_read8(TEST_ASSETS "images/32bit.tga", "tga", values, alpha);
    EXPECT_EQ(values[0], (uint8_t)255);
    EXPECT_EQ(values[1], (uint8_t)0);
    EXPECT_EQ(values[2], (uint8_t)0);
    EXPECT_EQ(values[3], (uint8_t)0);
    EXPECT_EQ(values[4], (uint8_t)255);
    EXPECT_EQ(values[5], (uint8_t)0);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)0);
    EXPECT_EQ(values[8], (uint8_t)255);
    EXPECT_EQ(values[9], (uint8_t)0);
    EXPECT_EQ(values[10], (uint8_t)0);
    EXPECT_EQ(values[11], (uint8_t)0);
    EXPECT_EQ(alpha[0], (uint8_t)255);
    EXPECT_EQ(alpha[1], (uint8_t)128);
    EXPECT_EQ(alpha[2], (uint8_t)66);
    EXPECT_EQ(alpha[3], (uint8_t)33);
    EXPECT_EQ(res, 2);
    //16 bit
    res = -1;
    res = img_read8(TEST_ASSETS "images/16bit.tga", "tga", values, NULL);
    //shifts are used to account for precision lost with the 16 bits values
    EXPECT_EQ(values[0], (uint8_t)255 >> 3 << 3);
    EXPECT_EQ(values[1], (uint8_t)0);
    EXPECT_EQ(values[2], (uint8_t)0);
    EXPECT_EQ(values[3], (uint8_t)0);
    EXPECT_EQ(values[4], (uint8_t)255 >> 3 << 3);
    EXPECT_EQ(values[5], (uint8_t)0);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)0);
    EXPECT_EQ(values[8], (uint8_t)255 >> 3 << 3);
    EXPECT_EQ(values[9], (uint8_t)0);
    EXPECT_EQ(values[10], (uint8_t)0);
    EXPECT_EQ(values[11], (uint8_t)0);
    EXPECT_EQ(res, 1);
    uint8_t rleval[100*3];
    uint8_t rleval_expected[300] = {
            0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00,
            0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
            0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00,
            0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00,
            0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
            0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00,
            0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00,
            0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
            0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00,
            0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00,
            0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
            0x00, 0x00, 0xFF, 0x00, 0x00, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F,
            0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E,
            0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0xFF, 0x00, 0x00, 0xFF,
            0x00, 0x00, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F,
            0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E,
            0x9F, 0x5B, 0x7E, 0x9F, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x5B,
            0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x4F, 0x00, 0x62,
            0x4F, 0x00, 0x62, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E,
            0x9F, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x5B, 0x7E, 0x9F, 0x5B,
            0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x4F, 0x00, 0x62, 0x4F, 0x00, 0x62,
            0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0xFF, 0x00,
            0x00, 0xFF, 0x00, 0x00, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B,
            0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F,
            0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0xFF, 0x00, 0x00, 0xFF, 0x00,
            0x00, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B,
            0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F, 0x5B, 0x7E, 0x9F,
            0x5B, 0x7E, 0x9F
    };
    uint8_t rlealp[100*1];
    uint8_t rlealp_expected[100] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
            0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
            0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
            0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
            0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
            0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
            0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    res = -1;
    res = img_read8(TEST_ASSETS "images/24bitRLE.tga", "tga", rleval, NULL);
    ASSERT_EQ(res, 1);
    for(int i = 0; i<300; i++)
        EXPECT_EQ(rleval[i], rleval_expected[i]);
    memset(rleval, 0, sizeof(rleval));
    res = -1;
    res = img_read8(TEST_ASSETS "images/16bitRLE.tga", "tga", rleval, NULL);
    ASSERT_EQ(res, 1);
    for(int i = 0; i<300; i++)
        //shifts are used to account for precision lost with the 16 bits values
        EXPECT_EQ(rleval[i], rleval_expected[i] >> 3 << 3);
    memset(rleval, 0, sizeof(rleval));
    res = -1;
    res = img_read8(TEST_ASSETS "images/32bitRLE.tga", "tga", rleval, NULL);
    ASSERT_EQ(res, 1);
    for(int i = 0; i<300; i++)
        EXPECT_EQ(rleval[i], rleval_expected[i]);
    memset(rleval, 0, sizeof(rleval));
    memset(rlealp, 0, sizeof(rlealp));
    res = -1;
    res = img_read8(TEST_ASSETS "images/32bitRLE.tga", "tga", rleval, rlealp);
    ASSERT_EQ(res, 2);
    for(int i = 0; i<300; i++)
        EXPECT_EQ(rleval[i], rleval_expected[i]);
    for(int i = 0; i<100; i++)
        EXPECT_EQ(rlealp[i], rlealp_expected[i]);
}

SPECTRE_TEST(ImageIO, tga_save_func)
{
    uint8_t read_data[300];
    bool res;
    res = img_write("test.tga", "tga", 10, 10, write_data);
    ASSERT_TRUE(res);
    res = img_read8("test.tga", "tga", read_data, NULL);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.tga"), 0);
    for(int i = 0; i<300; i++)
        EXPECT_EQ(read_data[i], write_data[i]);

    //non existent folder
    res = img_write("/root/nonexistent/test.tga", "tga", 10, 10, write_data);
    EXPECT_FALSE(res);
}

#ifdef JPEG_FOUND

SPECTRE_TEST(ImageIO, jpg_valid_func)
{
    bool res;
    res = img_valid("nonexistent.jpg", "jpg");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/bmpasjpg.jpg", "jpg");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/generic.jpg", "jpg");
    EXPECT_TRUE(res);
    res = img_valid(TEST_ASSETS "images/generic.jpeg", "jpeg");
    EXPECT_TRUE(res);
}

SPECTRE_TEST(ImageIO, jpg_dimensions_func)
{
    bool res;
    int width;
    int height;
    width = 0;
    height = 0;
    res = img_dimensions("nonexistent.jpg", "jpg", &width, &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    res = img_dimensions(TEST_ASSETS "images/bmpasjpg.jpg", "jpg", &width,
                         &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    res = img_dimensions(TEST_ASSETS "images/generic.jpg", "jpg", &width,
                         &height);
    EXPECT_TRUE(res);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 3);
    width = 0;
    height = 0;
    res = img_dimensions(TEST_ASSETS "images/generic.jpeg", "jpeg", &width,
                         &height);
    EXPECT_TRUE(res);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 3);
}

SPECTRE_TEST(ImageIO, jpg_read_func)
{
    bool res;
    uint8_t values[6*3];
    res = img_read8("nonexistent.jpg", "jpg", values, NULL);
    EXPECT_FALSE(res);
    res = img_read8(TEST_ASSETS "images/bmpasjpg.jpg", "jpg", values, NULL);
    EXPECT_FALSE(res);
    res = img_read8(TEST_ASSETS "images/generic.jpg", "jpg", values, NULL);
    EXPECT_TRUE(res);
    //Strange values (not 0 or 255) are given to jpg compression. These has been
    //checked previously with floating point values and an epsilon of 1e-2
    EXPECT_EQ(values[0], (uint8_t)255);
    EXPECT_EQ(values[1], (uint8_t)2);
    EXPECT_EQ(values[2], (uint8_t)2);
    EXPECT_EQ(values[3], (uint8_t)255);
    EXPECT_EQ(values[4], (uint8_t)250);
    EXPECT_EQ(values[5], (uint8_t)6);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)255);
    EXPECT_EQ(values[8], (uint8_t)0);
    EXPECT_EQ(values[9], (uint8_t)14);
    EXPECT_EQ(values[10], (uint8_t)4);
    EXPECT_EQ(values[11], (uint8_t)255);
    EXPECT_EQ(values[12], (uint8_t)255);
    EXPECT_EQ(values[13], (uint8_t)255);
    EXPECT_EQ(values[14], (uint8_t)250);
    EXPECT_EQ(values[15], (uint8_t)7);
    EXPECT_EQ(values[16], (uint8_t)0);
    EXPECT_EQ(values[17], (uint8_t)0);

    res = img_read8(TEST_ASSETS "images/generic.jpeg", "jpeg", values, NULL);
    EXPECT_TRUE(res);
    EXPECT_EQ(values[0], (uint8_t)255);
    EXPECT_EQ(values[1], (uint8_t)2);
    EXPECT_EQ(values[2], (uint8_t)2);
    EXPECT_EQ(values[3], (uint8_t)255);
    EXPECT_EQ(values[4], (uint8_t)250);
    EXPECT_EQ(values[5], (uint8_t)6);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)255);
    EXPECT_EQ(values[8], (uint8_t)0);
    EXPECT_EQ(values[9], (uint8_t)14);
    EXPECT_EQ(values[10], (uint8_t)4);
    EXPECT_EQ(values[11], (uint8_t)255);
    EXPECT_EQ(values[12], (uint8_t)255);
    EXPECT_EQ(values[13], (uint8_t)255);
    EXPECT_EQ(values[14], (uint8_t)250);
    EXPECT_EQ(values[15], (uint8_t)7);
    EXPECT_EQ(values[16], (uint8_t)0);
    EXPECT_EQ(values[17], (uint8_t)0);
}

SPECTRE_TEST(ImageIO, jpg_write_func)
{
    uint8_t read_data[300];
    bool res;
    res = img_write("test.jpg", "jpg", 10, 10, write_data);
    ASSERT_TRUE(res);
    res = img_read8("test.jpg", "jpg", read_data, NULL);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.jpg"), 0);
    for(int i = 0; i<300; i++)
        EXPECT_EQ(read_data[i], write_data[i]);

    //non existent folder
    res = img_write("/root/nonexistent/test.jpeg", "jpeg", 10, 10, write_data);
    EXPECT_FALSE(res);
}

#endif
#ifdef PNG_FOUND

SPECTRE_TEST(ImageIO, png_valid_func)
{
    bool res;
    res = img_valid("nonexistent.png", "png");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/bmpaspng.png", "png");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/generic.png", "png");
    EXPECT_TRUE(res);
}

SPECTRE_TEST(ImageIO, png_dimensions_func)
{
    bool res;
    int width;
    int height;
    width = 0;
    height = 0;
    res = img_dimensions("nonexistent.png", "png", &width, &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    res = img_dimensions(TEST_ASSETS "images/bmpaspng.png", "png", &width,
                         &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    res = img_dimensions(TEST_ASSETS "images/generic.png", "png", &width,
                         &height);
    EXPECT_TRUE(res);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 3);
}

SPECTRE_TEST(ImageIO, png_read_func)
{
    bool res;
    uint8_t values[6*3];
    res = img_read8("nonexistent.png", "png", values, NULL);
    EXPECT_EQ(res, 0);
    res = img_read8(TEST_ASSETS "images/bmpaspng.png", "png", values, NULL);
    EXPECT_EQ(res, 0);
    res = img_read8(TEST_ASSETS "images/generic.png", "png", values, NULL);
    EXPECT_EQ(res, 1);
    //The input image was converted from the jpg one, so strange values are
    //inherited
    EXPECT_EQ(values[0], (uint8_t)255);
    EXPECT_EQ(values[1], (uint8_t)2);
    EXPECT_EQ(values[2], (uint8_t)2);
    EXPECT_EQ(values[3], (uint8_t)255);
    EXPECT_EQ(values[4], (uint8_t)250);
    EXPECT_EQ(values[5], (uint8_t)6);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)255);
    EXPECT_EQ(values[8], (uint8_t)0);
    EXPECT_EQ(values[9], (uint8_t)14);
    EXPECT_EQ(values[10], (uint8_t)4);
    EXPECT_EQ(values[11], (uint8_t)255);
    EXPECT_EQ(values[12], (uint8_t)255);
    EXPECT_EQ(values[13], (uint8_t)255);
    EXPECT_EQ(values[14], (uint8_t)250);
    EXPECT_EQ(values[15], (uint8_t)7);
    EXPECT_EQ(values[16], (uint8_t)0);
    EXPECT_EQ(values[17], (uint8_t)0);
}

SPECTRE_TEST(ImageIO, png_write_func)
{
    uint8_t read_data[300];
    bool res;
    res = img_write("test.png", "png", 10, 10, write_data);
    ASSERT_TRUE(res);
    res = img_read8("test.png", "png", read_data, NULL);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.png"), 0);
    for(int i = 0; i<300; i++)
        EXPECT_EQ(read_data[i], write_data[i]);

    //non existent folder
    res = img_write("/root/nonexistent/test.png", "png", 10, 10, write_data);
    EXPECT_FALSE(res);
}

#endif
#ifdef TIFF_FOUND

SPECTRE_TEST(ImageIO, tiff_valid_func)
{
    bool res;
    res = img_valid("nonexistent.tif", "tiff");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/bmpastif.tif", "tif");
    EXPECT_FALSE(res);
    res = img_valid(TEST_ASSETS "images/generic.tif", "tif");
    EXPECT_TRUE(res);
}

SPECTRE_TEST(ImageIO, tiff_dimensions_func)
{
    bool res;
    int width;
    int height;
    width = 0;
    height = 0;
    res = img_dimensions("nonexistent.tiff", "tiff", &width, &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    res = img_dimensions(TEST_ASSETS "images/bmpastif.tif", "tif", &width,
                         &height);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    res = img_dimensions(TEST_ASSETS "images/generic.tif", "tif",
                         &width, &height);
    EXPECT_TRUE(res);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
}

SPECTRE_TEST(ImageIO, tiff_read_func)
{
    char res;
    uint8_t values[4*3];
    uint8_t alpha[4];
    res = img_read8("nonexistent.tiff", "tiff", values, alpha);
    EXPECT_EQ(res, 0);
    res = img_read8(TEST_ASSETS "images/bmpastif.tif", "tif", values, alpha);
    EXPECT_EQ(res, 0);
    res = img_read8(TEST_ASSETS "images/generic.tif", "tif", values, NULL);
    EXPECT_EQ(res, 1);
    EXPECT_EQ(values[0], (uint8_t)255);
    EXPECT_EQ(values[1], (uint8_t)0);
    EXPECT_EQ(values[2], (uint8_t)0);
    EXPECT_EQ(values[3], (uint8_t)0);
    EXPECT_EQ(values[4], (uint8_t)255);
    EXPECT_EQ(values[5], (uint8_t)0);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)0);
    EXPECT_EQ(values[8], (uint8_t)255);
    EXPECT_EQ(values[9], (uint8_t)0);
    EXPECT_EQ(values[10], (uint8_t)0);
    EXPECT_EQ(values[11], (uint8_t)0);
    memset(values, 0, sizeof(values));
    res = img_read8(TEST_ASSETS "images/generic_alpha.tiff", "tiff", values,
                    alpha);
    EXPECT_EQ(res, 2);
    EXPECT_EQ(values[0], (uint8_t)255);
    EXPECT_EQ(values[1], (uint8_t)0);
    EXPECT_EQ(values[2], (uint8_t)0);
    EXPECT_EQ(values[3], (uint8_t)0);
    EXPECT_EQ(values[4], (uint8_t)255);
    EXPECT_EQ(values[5], (uint8_t)0);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)0);
    EXPECT_EQ(values[8], (uint8_t)255);
    EXPECT_EQ(values[9], (uint8_t)0);
    EXPECT_EQ(values[10], (uint8_t)0);
    EXPECT_EQ(values[11], (uint8_t)0);
    EXPECT_EQ(alpha[0], (uint8_t)127);
    EXPECT_EQ(alpha[1], (uint8_t)255);
    EXPECT_EQ(alpha[2], (uint8_t)0);
    EXPECT_EQ(alpha[3], (uint8_t)54);
}

SPECTRE_TEST(ImageIO, tiff_write_func)
{
    uint8_t read_data[300];
    bool res;
    res = img_write("test.tif", "tif", 10, 10, write_data);
    ASSERT_TRUE(res);
    res = img_read8("test.tif", "tif", read_data, NULL);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.tif"), 0);
    for(int i = 0; i<300; i++)
        EXPECT_EQ(read_data[i], write_data[i]);

    //non existent folder
    res = img_write("/root/nonexistent/test.tif", "tif", 10, 10, write_data);
    EXPECT_FALSE(res);
}

#endif

SPECTRE_TEST_END(ImageIO_tests)
