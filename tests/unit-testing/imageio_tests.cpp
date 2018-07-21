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

SPECTRE_TEST(ImageIO, ppm_write_func)
{
    char file_stat[64];

    uint8_t image_sample[17*10*3];
    for(int i = 0; i<17*10*3; i += 3)
        image_sample[i] = i/3;
    bool res = img_write("test.ppm", "ppm", 16, 10, image_sample);
    ASSERT_TRUE(res);
#ifndef _WIN32
    //check if saved image is actually a .ppm
    FILE* fp = popen("file -b --mime test.ppm", "r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_STREQ(file_stat, "image/x-portable-pixmap; charset=binary\n");
#endif
    EXPECT_EQ(unlink("test.ppm"), 0);

    //non existent folder
    res = img_write("/root/nonexistent/test.ppm", "ppm", 16, 10, image_sample);
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

SPECTRE_TEST(ImageIO, bmp_write_func)
{
    char file_stat[64];

    uint8_t image_sample[17*10*3];
    for(int i = 0; i<17*10*3; i += 3)
        image_sample[i] = i/3;
    bool res = img_write("test.bmp", "bmp", 16, 10, image_sample);
    ASSERT_TRUE(res);
#ifndef _WIN32
    //check if saved image is actually a .bmp
    FILE* fp = popen("file -b --mime test.bmp", "r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_STREQ(file_stat,
                 "image/x-ms-bmp; charset=binary\n");
#endif
    EXPECT_EQ(unlink("test.bmp"), 0);

    //non existent folder
    res = img_write("/root/nonexistent/test.bmp", "bmp", 16, 10, image_sample);
    EXPECT_FALSE(res);
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
    width = 2;
    height = 2;
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

#ifdef JPEG_FOUND

SPECTRE_TEST(ImageIO, jpg_write_func)
{
    char file_stat[64];

    uint8_t image_sample[17*10*3];
    for(int i = 0; i<17*10*3; i += 3)
        image_sample[i] = i/3;
    bool res = img_write("test.jpg", "jpg", 16, 10, image_sample);
    ASSERT_TRUE(res);
#ifndef _WIN32
    //check if saved image is actually a .ppm
    FILE* fp = popen("file -b --mime test.jpg", "r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_STREQ(file_stat, "image/jpeg; charset=binary\n");
#endif
    EXPECT_EQ(unlink("test.jpg"), 0);

    //non existent folder
    res = img_write("/root/nonexistent/test.jpg", "jpg", 16, 10, image_sample);
    EXPECT_FALSE(res);
    res = img_write("/root/nonexistent/test.jpeg", "jpeg", 16, 10,
                    image_sample);
    EXPECT_FALSE(res);
}

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
    uint8_t alpha[4];
    res = img_read8("nonexistent.jpg", "jpg", values, alpha);
    EXPECT_FALSE(res);
    res = img_read8(TEST_ASSETS "images/bmpasjpg.jpg", "jpg", values, alpha);
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

#endif
#ifdef PNG_FOUND

SPECTRE_TEST(ImageIO, png_write_func)
{
    char file_stat[64];

    uint8_t image_sample[17*10*3];
    for(int i = 0; i<17*10*3; i += 3)
        image_sample[i] = i/3;
    bool res = img_write("test.png", "png", 16, 10,
                         image_sample);
    ASSERT_TRUE(res);
#ifndef _WIN32
    //check if saved image is actually a .ppm
    FILE* fp = popen("file -b --mime test.png", "r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_STREQ(file_stat, "image/png; charset=binary\n");
#endif
    EXPECT_EQ(unlink("test.png"), 0);

    //non existent folder
    res = img_write("/root/nonexistent/test.png", "png", 16, 10, image_sample);
    EXPECT_FALSE(res);
}

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
    uint8_t alpha[4];
    res = img_read8("nonexistent.png", "png", values, alpha);
    EXPECT_EQ(res, 0);
    res = img_read8(TEST_ASSETS "images/bmpaspng.png", "png", values, alpha);
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

#endif

SPECTRE_TEST_END(ImageIO_tests)
