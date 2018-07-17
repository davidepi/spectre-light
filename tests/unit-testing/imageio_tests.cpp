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

SPECTRE_TEST(ImageIO, ppm_save_func)
{
    char file_stat[64];

    uint8_t image_sample[17*10*3];
    for(int i = 0; i<17*10*3; i += 3)
        image_sample[i] = i/3;
    bool res = img_save("test.ppm", "ppm", 16, 10, image_sample);
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
    res = img_save("/root/nonexistent/test.ppm", "ppm", 16, 10, image_sample);
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
    float data[4*3+1];
    //non existent
    res = img_read32("nonexistent.ppm", "ppm", 2, 2, data, NULL);
    EXPECT_FALSE(res);
    //first letter of the magic number is wrong
    res = img_read32(TEST_ASSETS "images/wrong_magic1.ppm", "ppm", 2, 2, data,
                     NULL);
    EXPECT_FALSE(res);
    //second letter of the magic number is wrong
    res = img_read32(TEST_ASSETS "images/wrong_magic2.ppm", "ppm", 2, 2, data,
                     NULL);
    EXPECT_FALSE(res);
    //read image with normal depth (ASCII)
    res = img_read32(TEST_ASSETS "images/multiple_spaces.ppm", "ppm", 2, 2,
                     data, NULL);
    EXPECT_NEAR(data[0], 1.f, 1e-5f);
    EXPECT_NEAR(data[1], 0.f, 1e-5f);
    EXPECT_NEAR(data[2], 0.f, 1e-5f);
    EXPECT_NEAR(data[3], 0.f, 1e-5f);
    EXPECT_NEAR(data[4], 1.f, 1e-5f);
    EXPECT_NEAR(data[5], 0.f, 1e-5f);
    EXPECT_NEAR(data[6], 0.f, 1e-5f);
    EXPECT_NEAR(data[7], 0.f, 1e-5f);
    EXPECT_NEAR(data[8], 1.f, 1e-5f);
    EXPECT_NEAR(data[9], 0.f, 1e-5f);
    EXPECT_NEAR(data[10], 0.f, 1e-5f);
    EXPECT_NEAR(data[11], 0.f, 1e-5f);
    EXPECT_TRUE(res);
    memset(data, 0, 12);
    //read image with high depth (ASCII)
    res = img_read32(TEST_ASSETS "images/p3_high_depth.ppm", "ppm", 2, 2, data,
                     NULL);
    EXPECT_NEAR(data[0], 1.f, 1e-5f);
    EXPECT_NEAR(data[1], 1.f, 1e-5f);
    EXPECT_NEAR(data[2], 1.f, 1e-5f);
    EXPECT_NEAR(data[3], 0.f, 1e-5f);
    EXPECT_NEAR(data[4], 0.f, 1e-5f);
    EXPECT_NEAR(data[5], 0.f, 1e-5f);
    EXPECT_NEAR(data[6], 0.f, 1e-5f);
    EXPECT_NEAR(data[7], 0.f, 1e-5f);
    EXPECT_NEAR(data[8], 0.f, 1e-5f);
    EXPECT_NEAR(data[9], 1.f, 1e-5f);
    EXPECT_NEAR(data[10], 1.f, 1e-5f);
    EXPECT_NEAR(data[11], 1.f, 1e-5f);
    EXPECT_TRUE(res);
    memset(data, 0, 12);
    //read image with normal depth (binary) no stack_overflow
    res = img_read32(TEST_ASSETS "images/binary.ppm", "ppm", 2, 2, data, NULL);
    EXPECT_NEAR(data[0], 1.f, 1e-5f);
    EXPECT_NEAR(data[1], 0.f, 1e-5f);
    EXPECT_NEAR(data[2], 0.f, 1e-5f);
    EXPECT_NEAR(data[3], 0.f, 1e-5f);
    EXPECT_NEAR(data[4], 1.f, 1e-5f);
    EXPECT_NEAR(data[5], 0.f, 1e-5f);
    EXPECT_NEAR(data[6], 0.f, 1e-5f);
    EXPECT_NEAR(data[7], 0.f, 1e-5f);
    EXPECT_NEAR(data[8], 1.f, 1e-5f);
    EXPECT_NEAR(data[9], 0.f, 1e-5f);
    EXPECT_NEAR(data[10], 0.f, 1e-5f);
    EXPECT_NEAR(data[11], 0.f, 1e-5f);
    EXPECT_TRUE(res);
    memset(data, 0, 12);
    //read image that claims to be 2x2 but contains a lot more
    //bytes
    data[4*3] = (float)0x2B; //random val, check that this is unchanged
    res = img_read32(TEST_ASSETS "images/binary_stackoverflow.ppm", "ppm", 2, 2,
                     data, NULL);
    EXPECT_NEAR(data[0], 1.f, 1e-5f);
    EXPECT_NEAR(data[1], 1.f, 1e-5f);
    EXPECT_NEAR(data[2], 1.f, 1e-5f);
    EXPECT_NEAR(data[3], 0.f, 1e-5f);
    EXPECT_NEAR(data[4], 0.f, 1e-5f);
    EXPECT_NEAR(data[5], 0.f, 1e-5f);
    EXPECT_NEAR(data[6], 0.f, 1e-5f);
    EXPECT_NEAR(data[7], 0.f, 1e-5f);
    EXPECT_NEAR(data[8], 0.f, 1e-5f);
    EXPECT_NEAR(data[9], 1.f, 1e-5f);
    EXPECT_NEAR(data[10], 1.f, 1e-5f);
    EXPECT_NEAR(data[11], 1.f, 1e-5f);
    EXPECT_NEAR(data[12], (float)0x2B, 1e-5f); //assert no stack overflow
    EXPECT_TRUE(res);
    memset(data, 0, 12);
    //read image with high depth (binary) no stack_overflow
    res = img_read32(TEST_ASSETS "images/p6_high_depth.ppm", "ppm", 2, 2, data,
                     NULL);
    EXPECT_NEAR(data[0], 1.f, 1e-5f);
    EXPECT_NEAR(data[1], 1.f, 1e-5f);
    EXPECT_NEAR(data[2], 1.f, 1e-5f);
    EXPECT_NEAR(data[3], 0.f, 1e-5f);
    EXPECT_NEAR(data[4], 0.f, 1e-5f);
    EXPECT_NEAR(data[5], 0.f, 1e-5f);
    EXPECT_NEAR(data[6], 0.f, 1e-5f);
    EXPECT_NEAR(data[7], 0.f, 1e-5f);
    EXPECT_NEAR(data[8], 0.f, 1e-5f);
    EXPECT_NEAR(data[9], 1.f, 1e-5f);
    EXPECT_NEAR(data[10], 1.f, 1e-5f);
    EXPECT_NEAR(data[11], 1.f, 1e-5f);
    EXPECT_TRUE(res);
    memset(data, 0, 12);
    //read image with high depth (binary), stack_overflow
    res = img_read32(TEST_ASSETS "images/p6_high_depth_stack_overflow.ppm",
                     "ppm", 2, 2, data, NULL);
    EXPECT_NEAR(data[0], 1.f, 1e-5f);
    EXPECT_NEAR(data[1], 1.f, 1e-5f);
    EXPECT_NEAR(data[2], 1.f, 1e-5f);
    EXPECT_NEAR(data[3], 0.f, 1e-5f);
    EXPECT_NEAR(data[4], 0.f, 1e-5f);
    EXPECT_NEAR(data[5], 0.f, 1e-5f);
    EXPECT_NEAR(data[6], 0.f, 1e-5f);
    EXPECT_NEAR(data[7], 0.f, 1e-5f);
    EXPECT_NEAR(data[8], 0.f, 1e-5f);
    EXPECT_NEAR(data[9], 1.f, 1e-5f);
    EXPECT_NEAR(data[10], 1.f, 1e-5f);
    EXPECT_NEAR(data[11], 1.f, 1e-5f);
    EXPECT_NEAR(data[12], (float)0x2B, 1e-5f); //assert no stack overflow
    EXPECT_TRUE(res);
    memset(data, 0, 12);
}

SPECTRE_TEST(ImageIO, bmp_save_func)
{
    char file_stat[64];

    uint8_t image_sample[17*10*3];
    for(int i = 0; i<17*10*3; i += 3)
        image_sample[i] = i/3;
    bool res = img_save("test.bmp", "bmp", 16, 10, image_sample);
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
    res = img_save("/root/nonexistent/test.bmp", "bmp", 16, 10, image_sample);
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
    float values[4*3];
    uint8_t alpha[4];
    //non existent
    res = img_read32("nonexistent.bmp", "bmp", 2, 2, values, NULL);
    EXPECT_FALSE(res);
    //first letter of the magic number is wrong
    res = img_read32(TEST_ASSETS "images/wrong_magic1.bmp", "bmp", 2, 2, values,
                     NULL);
    EXPECT_FALSE(res);
    //second letter of the magic number is wrong
    res = img_read32(TEST_ASSETS "images/wrong_magic2.bmp", "bmp", 2, 2, values,
                     NULL);
    EXPECT_FALSE(res);
    //os2
    res = img_read32(TEST_ASSETS "images/os2.bmp", "bmp", 2, 2, values, NULL);
    EXPECT_FALSE(res);
    //normal image
    res = img_read32(TEST_ASSETS "images/correct.bmp", "bmp", 2, 2, values,
                     NULL);
    EXPECT_NEAR(values[0], 1.f, 1e-5f);
    EXPECT_NEAR(values[1], 0.f, 1e-5f);
    EXPECT_NEAR(values[2], 0.f, 1e-5f);
    EXPECT_NEAR(values[3], 0.f, 1e-5f);
    EXPECT_NEAR(values[4], 1.f, 1e-5f);
    EXPECT_NEAR(values[5], 0.f, 1e-5f);
    EXPECT_NEAR(values[6], 0.f, 1e-5f);
    EXPECT_NEAR(values[7], 0.f, 1e-5f);
    EXPECT_NEAR(values[8], 1.f, 1e-5f);
    EXPECT_NEAR(values[9], 0.f, 1e-5f);
    EXPECT_NEAR(values[10], 0.f, 1e-5f);
    EXPECT_NEAR(values[11], 0.f, 1e-5f);
    EXPECT_TRUE(res);
    //flipped (negative) rows
    res = img_read32(TEST_ASSETS "images/flipped.bmp", "bmp", 2, 2, values,
                     NULL);
    EXPECT_NEAR(values[0], 1.f, 1e-5f);
    EXPECT_NEAR(values[1], 0.f, 1e-5f);
    EXPECT_NEAR(values[2], 0.f, 1e-5f);
    EXPECT_NEAR(values[3], 0.f, 1e-5f);
    EXPECT_NEAR(values[4], 1.f, 1e-5f);
    EXPECT_NEAR(values[5], 0.f, 1e-5f);
    EXPECT_NEAR(values[6], 0.f, 1e-5f);
    EXPECT_NEAR(values[7], 0.f, 1e-5f);
    EXPECT_NEAR(values[8], 1.f, 1e-5f);
    EXPECT_NEAR(values[9], 0.f, 1e-5f);
    EXPECT_NEAR(values[10], 0.f, 1e-5f);
    EXPECT_NEAR(values[11], 0.f, 1e-5f);
    EXPECT_TRUE(res);
    //32bit - NULL alpha array
    res = img_read32(TEST_ASSETS "images/32bit.bmp", "bmp", 2, 2, values, NULL);
    EXPECT_NEAR(values[0], 1.f, 1e-5f);
    EXPECT_NEAR(values[1], 0.f, 1e-5f);
    EXPECT_NEAR(values[2], 0.f, 1e-5f);
    EXPECT_NEAR(values[3], 0.f, 1e-5f);
    EXPECT_NEAR(values[4], 1.f, 1e-5f);
    EXPECT_NEAR(values[5], 0.f, 1e-5f);
    EXPECT_NEAR(values[6], 0.f, 1e-5f);
    EXPECT_NEAR(values[7], 0.f, 1e-5f);
    EXPECT_NEAR(values[8], 1.f, 1e-5f);
    EXPECT_NEAR(values[9], 0.f, 1e-5f);
    EXPECT_NEAR(values[10], 0.f, 1e-5f);
    EXPECT_NEAR(values[11], 0.f, 1e-5f);
    EXPECT_TRUE(res);
    //32bit - alpha array
    res = img_read32(TEST_ASSETS "images/32bit.bmp", "bmp", 2, 2, values,
                     alpha);
    EXPECT_NEAR(values[0], 1.f, 1e-5f);
    EXPECT_NEAR(values[1], 0.f, 1e-5f);
    EXPECT_NEAR(values[2], 0.f, 1e-5f);
    EXPECT_NEAR(values[3], 0.f, 1e-5f);
    EXPECT_NEAR(values[4], 1.f, 1e-5f);
    EXPECT_NEAR(values[5], 0.f, 1e-5f);
    EXPECT_NEAR(values[6], 0.f, 1e-5f);
    EXPECT_NEAR(values[7], 0.f, 1e-5f);
    EXPECT_NEAR(values[8], 1.f, 1e-5f);
    EXPECT_NEAR(values[9], 0.f, 1e-5f);
    EXPECT_NEAR(values[10], 0.f, 1e-5f);
    EXPECT_NEAR(values[11], 0.f, 1e-5f);
    EXPECT_EQ(alpha[0], 255);
    EXPECT_EQ(alpha[1], 128);
    EXPECT_EQ(alpha[2], 66);
    EXPECT_EQ(alpha[3], 33);
    EXPECT_TRUE(res);
}
/*
SPECTRE_TEST(ImageIO, save_rgb_func)
{
    bool res;
    uint8_t image_sample[17*10*3];
    for(int i = 0; i<17*10*3; i += 3)
        image_sample[i] = i/3;
#ifdef IMAGEMAGICK
    char file_stat[64];
    FILE* fp;

    //save jpg
    res = save_RGB("test.jpg",  "jpg", 16, 10, image_sample);
    ASSERT_TRUE(res);
    //check if saved image is actually a .ppm
    fp = popen("file -b --mime test.jpg", "r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_STREQ(file_stat, "image/jpeg; charset=binary\n");
    EXPECT_EQ(unlink("test.jpg"), 0);

    //save tiff
    res = save_RGB("test.tiff", "tiff", 16, 10, image_sample);
    ASSERT_TRUE(res);
    //check if saved image is actually a .ppm
    fp = popen("file -b --mime test.tiff", "r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_STREQ(file_stat, "image/tiff; charset=binary\n");
    EXPECT_EQ(unlink("test.tiff"), 0);

    //save targa
    res = save_RGB("test.tga", "tga", 16, 10, image_sample);
    ASSERT_TRUE(res);
    //check if saved image is actually a .ppm
    fp = popen("file -b --mime test.tga", "r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_STREQ(file_stat, "image/x-tgaimage/x-tga; charset=binary\n");
    EXPECT_EQ(unlink("test.tga"), 0);

    //save png
    res = save_RGB("test.png", "png", 16, 10, image_sample);
    ASSERT_TRUE(res);
    //check if saved image is actually a .ppm
    fp = popen("file -b --mime test.png", "r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_STREQ(file_stat, "image/png; charset=binary\n");
    EXPECT_EQ(unlink("test.png"), 0);

    //save dds
    res = save_RGB("test.dds", "dds", 16, 10, image_sample);
    ASSERT_TRUE(res);
    //check if saved image is actually a .ppm
    fp = popen("file -b --mime test.dds", "r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_STREQ(file_stat, "application/octet-stream; charset=binary\n");
    EXPECT_EQ(unlink("test.dds"), 0);
    
    //bmp
    res = save_RGB("test.bmp","bmp",16,10,image_sample);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.bmp"), 0);
    //ppm
    res = save_RGB("test.ppm","ppm",16,10,image_sample);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.ppm"), 0);

    //non existent folder
    errors_count[ERROR_INDEX] = 0;
    res = save_RGB("/root/nonexistent/test.jpg", "jpg", 16, 10, image_sample);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
    EXPECT_FALSE(res);
#else
    res = save_RGB("test.jpg", "jpg", 16, 10, image_sample);
    EXPECT_FALSE(res);
    //ensures calls are forwarded to save_ppm and save_bmp
    res = save_RGB("test.bmp", "bmp", 16, 10, image_sample);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.bmp"), 0);
    res = save_RGB("test.ppm", "ppm", 16, 10, image_sample);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.ppm"), 0);
#endif
}

SPECTRE_TEST(ImageIO, dimensions_rgb_func)
{
    int width;
    int height;
    bool res;
#ifdef IMAGEMAGICK

    //non existent
    res = dimensions_RGB("nonexistent.bmp", "bmp", &width, &height);
    EXPECT_EQ(width, IMAGE_NOT_READABLE);
    EXPECT_EQ(height, IMAGE_NOT_READABLE);
    EXPECT_EQ(res, false);
    width = 0;
    height = 0;
    //jpg
    res = dimensions_RGB(TEST_ASSETS "images/generic.jpg", "jpg",
                         &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 3);
    EXPECT_EQ(res, false);
    width = 0;
    height = 0;
    //png
    res = dimensions_RGB(TEST_ASSETS "images/generic.png", "png",
                         &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 3);
    EXPECT_EQ(res, false);
    width = 0;
    height = 0;
    //tiff
    res = dimensions_RGB(TEST_ASSETS "images/generic.tiff", "tiff",
                         &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 3);
    EXPECT_EQ(res, false);
    width = 0;
    height = 0;
    //targa
    res = dimensions_RGB(TEST_ASSETS "images/generic.tga", "tga",
                         &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 3);
    EXPECT_EQ(res, false);
    width = 0;
    height = 0;
    //alpha channel
    res = dimensions_RGB(TEST_ASSETS "images/generic_alpha.tiff", "tiff",
                         &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    EXPECT_EQ(res, true);
    width = 0;
    height = 0;
    //bmp
    res = dimensions_RGB(TEST_ASSETS "images/correct.bmp", "bmp",
                         &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    EXPECT_TRUE(res);
    width = 0;
    height = 0;
    //ppm
    res = dimensions_RGB(TEST_ASSETS "images/binary.ppm", "ppm",
                         &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    EXPECT_TRUE(res);
    width = 0;
    height = 0;
#else
    res = dimensions_RGB("test.jpg", "jpg", &width, &height);
    EXPECT_EQ(width, IMAGE_NOT_SUPPORTED);
    EXPECT_EQ(height, IMAGE_NOT_SUPPORTED);
    EXPECT_FALSE(res);
    //correctly forwared calls to dimensions_ppm and dimensions_bmp
    width = 0;
    height = 0;
    res = dimensions_RGB(TEST_ASSETS "images/correct.bmp", "bmp",
                         &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
    res = dimensions_RGB(TEST_ASSETS "images/binary.ppm", "ppm",
                         &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    EXPECT_FALSE(res);
    width = 0;
    height = 0;
#endif
}

SPECTRE_TEST(ImageIO, read_rgb_func)
{
    int res;
    float values[2*3*3];
    uint8_t alpha[2*3];
#ifdef IMAGEMAGICK
    //non existent
    res = read_RGB("nonexistent.bmp", "bmp", values, alpha);
    EXPECT_EQ(res, IMAGE_NOT_READABLE);
    //too many channels
    errors_count[ERROR_INDEX] = 0;
    res = read_RGB(TEST_ASSETS "images/singlechannel.tiff", "tiff",
                   values, alpha);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
    EXPECT_EQ(res, IMAGE_NOT_SUPPORTED);
    
    //jpg
    res = read_RGB(TEST_ASSETS "images/generic.jpg", "jpg",
                   values, alpha);
    EXPECT_NEAR(values[0], 1.f, .1f);
    EXPECT_NEAR(values[1], 0.f, .1f);
    EXPECT_NEAR(values[2], 0.f, .1f);
    EXPECT_NEAR(values[3], 1.f, .1f);
    EXPECT_NEAR(values[4], 1.f, .1f);
    EXPECT_NEAR(values[5], 0.f, .1f);
    EXPECT_NEAR(values[6], 0.f, .1f);
    EXPECT_NEAR(values[7], 1.f, .1f);
    EXPECT_NEAR(values[8], 0.f, .1f);
    EXPECT_NEAR(values[9], 0.f, .1f);
    EXPECT_NEAR(values[10], 0.f, .1f);
    EXPECT_NEAR(values[11], 1.f, .1f);
    EXPECT_NEAR(values[12], 1.f, .1f);
    EXPECT_NEAR(values[13], 1.f, .1f);
    EXPECT_NEAR(values[14], 1.f, .1f);
    EXPECT_NEAR(values[15], 0.f, .1f);
    EXPECT_NEAR(values[16], 0.f, .1f);
    EXPECT_NEAR(values[17], 0.f, .1f);
    EXPECT_EQ(res, IMAGE_OK);
    //png
    res = read_RGB(TEST_ASSETS "images/generic.png", "png",
                   values, alpha);
    EXPECT_NEAR(values[0], 1.f, .1f);
    EXPECT_NEAR(values[1], 0.f, .1f);
    EXPECT_NEAR(values[2], 0.f, .1f);
    EXPECT_NEAR(values[3], 1.f, .1f);
    EXPECT_NEAR(values[4], 1.f, .1f);
    EXPECT_NEAR(values[5], 0.f, .1f);
    EXPECT_NEAR(values[6], 0.f, .1f);
    EXPECT_NEAR(values[7], 1.f, .1f);
    EXPECT_NEAR(values[8], 0.f, .1f);
    EXPECT_NEAR(values[9], 0.f, .1f);
    EXPECT_NEAR(values[10], 0.f, .1f);
    EXPECT_NEAR(values[11], 1.f, .1f);
    EXPECT_NEAR(values[12], 1.f, .1f);
    EXPECT_NEAR(values[13], 1.f, .1f);
    EXPECT_NEAR(values[14], 1.f, .1f);
    EXPECT_NEAR(values[15], 0.f, .1f);
    EXPECT_NEAR(values[16], 0.f, .1f);
    EXPECT_NEAR(values[17], 0.f, .1f);
    EXPECT_EQ(res, IMAGE_OK);
    //tiff
    res = read_RGB(TEST_ASSETS "images/generic.tiff", "tiff",
                   values, alpha);
    EXPECT_NEAR(values[0], 1.f, .1f);
    EXPECT_NEAR(values[1], 0.f, .1f);
    EXPECT_NEAR(values[2], 0.f, .1f);
    EXPECT_NEAR(values[3], 1.f, .1f);
    EXPECT_NEAR(values[4], 1.f, .1f);
    EXPECT_NEAR(values[5], 0.f, .1f);
    EXPECT_NEAR(values[6], 0.f, .1f);
    EXPECT_NEAR(values[7], 1.f, .1f);
    EXPECT_NEAR(values[8], 0.f, .1f);
    EXPECT_NEAR(values[9], 0.f, .1f);
    EXPECT_NEAR(values[10], 0.f, .1f);
    EXPECT_NEAR(values[11], 1.f, .1f);
    EXPECT_NEAR(values[12], 1.f, .1f);
    EXPECT_NEAR(values[13], 1.f, .1f);
    EXPECT_NEAR(values[14], 1.f, .1f);
    EXPECT_NEAR(values[15], 0.f, .1f);
    EXPECT_NEAR(values[16], 0.f, .1f);
    EXPECT_NEAR(values[17], 0.f, .1f);
    EXPECT_EQ(res, IMAGE_OK);
    //targa
    res = read_RGB(TEST_ASSETS "images/generic.tga", "tga",
                   values, alpha);
    EXPECT_NEAR(values[0], 1.f, .1f);
    EXPECT_NEAR(values[1], 0.f, .1f);
    EXPECT_NEAR(values[2], 0.f, .1f);
    EXPECT_NEAR(values[3], 1.f, .1f);
    EXPECT_NEAR(values[4], 1.f, .1f);
    EXPECT_NEAR(values[5], 0.f, .1f);
    EXPECT_NEAR(values[6], 0.f, .1f);
    EXPECT_NEAR(values[7], 1.f, .1f);
    EXPECT_NEAR(values[8], 0.f, .1f);
    EXPECT_NEAR(values[9], 0.f, .1f);
    EXPECT_NEAR(values[10], 0.f, .1f);
    EXPECT_NEAR(values[11], 1.f, .1f);
    EXPECT_NEAR(values[12], 1.f, .1f);
    EXPECT_NEAR(values[13], 1.f, .1f);
    EXPECT_NEAR(values[14], 1.f, .1f);
    EXPECT_NEAR(values[15], 0.f, .1f);
    EXPECT_NEAR(values[16], 0.f, .1f);
    EXPECT_NEAR(values[17], 0.f, .1f);
    EXPECT_EQ(res, IMAGE_OK);
    //tiff with alpha
    res = read_RGB(TEST_ASSETS "images/generic_alpha.tiff", "tiff",
                   values, alpha);
    EXPECT_NEAR(values[0], 1.f, .1f);
    EXPECT_NEAR(values[1], 0.f, .1f);
    EXPECT_NEAR(values[2], 0.f, .1f);
    EXPECT_NEAR(values[3], 0.f, .1f);
    EXPECT_NEAR(values[4], 1.f, .1f);
    EXPECT_NEAR(values[5], 0.f, .1f);
    EXPECT_NEAR(values[6], 0.f, .14f); //suspicious, hope it is the compression
    EXPECT_NEAR(values[7], 0.f, .1f);
    EXPECT_NEAR(values[8], 1.f, .1f);
    EXPECT_NEAR(values[9], 1.f, .1f);
    EXPECT_NEAR(values[10], 1.f, .1f);
    EXPECT_NEAR(values[11], 1.f, .1f);
    EXPECT_EQ(alpha[0], 255);
    EXPECT_EQ(alpha[1], 0);
    EXPECT_EQ(alpha[2], 0);
    EXPECT_EQ(alpha[3], 255);
    EXPECT_EQ(res, IMAGE_OK);
    //ppm
    res = read_RGB(TEST_ASSETS "images/binary.ppm", "ppm", values, NULL);
    EXPECT_NEAR(values[0], 1.f, 1e-5f);
    EXPECT_NEAR(values[1], 0.f, 1e-5f);
    EXPECT_NEAR(values[2], 0.f, 1e-5f);
    EXPECT_NEAR(values[3], 0.f, 1e-5f);
    EXPECT_NEAR(values[4], 1.f, 1e-5f);
    EXPECT_NEAR(values[5], 0.f, 1e-5f);
    EXPECT_NEAR(values[6], 0.f, 1e-5f);
    EXPECT_NEAR(values[7], 0.f, 1e-5f);
    EXPECT_NEAR(values[8], 1.f, 1e-5f);
    EXPECT_NEAR(values[9], 0.f, 1e-5f);
    EXPECT_NEAR(values[10], 0.f, 1e-5f);
    EXPECT_NEAR(values[11], 0.f, 1e-5f);
    EXPECT_EQ(res, IMAGE_OK);
    //bmp
    res = read_RGB(TEST_ASSETS "images/correct.bmp", "bmp", values, NULL);
    EXPECT_NEAR(values[0], 1.f, 1e-5f);
    EXPECT_NEAR(values[1], 0.f, 1e-5f);
    EXPECT_NEAR(values[2], 0.f, 1e-5f);
    EXPECT_NEAR(values[3], 0.f, 1e-5f);
    EXPECT_NEAR(values[4], 1.f, 1e-5f);
    EXPECT_NEAR(values[5], 0.f, 1e-5f);
    EXPECT_NEAR(values[6], 0.f, 1e-5f);
    EXPECT_NEAR(values[7], 0.f, 1e-5f);
    EXPECT_NEAR(values[8], 1.f, 1e-5f);
    EXPECT_NEAR(values[9], 0.f, 1e-5f);
    EXPECT_NEAR(values[10], 0.f, 1e-5f);
    EXPECT_NEAR(values[11], 0.f, 1e-5f);
    EXPECT_EQ(res, IMAGE_OK);
#else
    res = read_RGB(TEST_ASSETS "generic.jpg", "jpg", values, alpha);
    EXPECT_EQ(res, IMAGE_NOT_SUPPORTED);
    //forwarded calls
    res = read_RGB(TEST_ASSETS "images/binary.ppm", "ppm", values, NULL);
    EXPECT_NEAR(values[0], 1.f, 1e-5f);
    EXPECT_NEAR(values[1], 0.f, 1e-5f);
    EXPECT_NEAR(values[2], 0.f, 1e-5f);
    EXPECT_NEAR(values[3], 0.f, 1e-5f);
    EXPECT_NEAR(values[4], 1.f, 1e-5f);
    EXPECT_NEAR(values[5], 0.f, 1e-5f);
    EXPECT_NEAR(values[6], 0.f, 1e-5f);
    EXPECT_NEAR(values[7], 0.f, 1e-5f);
    EXPECT_NEAR(values[8], 1.f, 1e-5f);
    EXPECT_NEAR(values[9], 0.f, 1e-5f);
    EXPECT_NEAR(values[10], 0.f, 1e-5f);
    EXPECT_NEAR(values[11], 0.f, 1e-5f);
    EXPECT_EQ(res, IMAGE_OK);
    res = read_RGB(TEST_ASSETS "images/correct.bmp", "bmp", values, NULL);
    EXPECT_NEAR(values[0], 1.f, 1e-5f);
    EXPECT_NEAR(values[1], 0.f, 1e-5f);
    EXPECT_NEAR(values[2], 0.f, 1e-5f);
    EXPECT_NEAR(values[3], 0.f, 1e-5f);
    EXPECT_NEAR(values[4], 1.f, 1e-5f);
    EXPECT_NEAR(values[5], 0.f, 1e-5f);
    EXPECT_NEAR(values[6], 0.f, 1e-5f);
    EXPECT_NEAR(values[7], 0.f, 1e-5f);
    EXPECT_NEAR(values[8], 1.f, 1e-5f);
    EXPECT_NEAR(values[9], 0.f, 1e-5f);
    EXPECT_NEAR(values[10], 0.f, 1e-5f);
    EXPECT_NEAR(values[11], 0.f, 1e-5f);
    EXPECT_EQ(res, IMAGE_OK);
#endif
}

SPECTRE_TEST(ImageIO, image_supported_func)
{
    int res;
    //null pointer
    res = image_supported(NULL);
    EXPECT_FALSE(res);
    //empty extension
    res = image_supported("");
    EXPECT_FALSE(res);
    //ppm
    res = image_supported("ppm");
    EXPECT_TRUE(res);
    //not ppm but letter p
    res = image_supported("png");
#ifdef IMAGEMAGICK
    EXPECT_TRUE(res);
#else
    EXPECT_FALSE(res);
#endif
    //bmp
    res = image_supported("bmp");
    EXPECT_TRUE(res);
    //jpg
    res = image_supported("jpg");
#ifdef IMAGEMAGICK
    EXPECT_TRUE(res);
#else
    EXPECT_FALSE(res);
#endif
    //totally random extension
    res = image_supported("ok");
    EXPECT_FALSE(res);
}
*/
SPECTRE_TEST_END(ImageIO_tests)
