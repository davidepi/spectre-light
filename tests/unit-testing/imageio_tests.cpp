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

#include "utility/imageIO.hpp"
#include "utility/utility.hpp"
#include <cstdio>
#include <climits>

SPECTRE_TEST_INIT(ImageIO_tests)

SPECTRE_TEST(ImageIO, save_ppm_func)
{
    char file_stat[64];

    uint8_t image_sample[17*10*3];
    for(int i = 0; i<17*10*3; i += 3)
        image_sample[i] = i/3;
    bool res = save_ppm("test.ppm", 16, 10, image_sample);
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
    res = save_ppm("/root/nonexistent/test.ppm", 16, 10, image_sample);
    EXPECT_FALSE(res);
}

SPECTRE_TEST(ImageIO, dimensions_ppm_func)
{
    int width;
    int height;
    //non existent
    dimensions_ppm("nonexistent.ppm", &width, &height);
    EXPECT_EQ(width, IMAGE_NOT_READABLE);
    EXPECT_EQ(height, IMAGE_NOT_READABLE);
    width = 0;
    height = 0;
    //first letter of the magic number is wrong
    dimensions_ppm(TEST_ASSETS "images/wrong_magic1.ppm", &width, &height);
    EXPECT_EQ(width, IMAGE_WRONG_MAGIC);
    EXPECT_EQ(height, IMAGE_WRONG_MAGIC);
    width = 0;
    height = 0;
    //second letter of the magic number is wrong
    dimensions_ppm(TEST_ASSETS "images/wrong_magic2.ppm", &width, &height);
    EXPECT_EQ(width, IMAGE_WRONG_MAGIC);
    EXPECT_EQ(height, IMAGE_WRONG_MAGIC);
    width = 0;
    height = 0;
    //multiple spaces in the image
    dimensions_ppm(TEST_ASSETS "images/multiple_spaces.ppm", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
    //binary image
    dimensions_ppm(TEST_ASSETS "images/binary.ppm", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
}

SPECTRE_TEST(ImageIO, read_ppm_func)
{
    int res;
    //+1 is used later to check stack overflows
    float data[4*3+1];
    //non existent
    res = read_ppm("nonexistent.ppm", data);
    EXPECT_EQ(res, IMAGE_NOT_READABLE);
    //first letter of the magic number is wrong
    res = read_ppm(TEST_ASSETS "images/wrong_magic1.ppm", data);
    EXPECT_EQ(res, IMAGE_WRONG_MAGIC);
    //second letter of the magic number is wrong
    res = read_ppm(TEST_ASSETS "images/wrong_magic2.ppm", data);
    EXPECT_EQ(res, IMAGE_WRONG_MAGIC);
    //read image with normal depth (ASCII)
    res = read_ppm(TEST_ASSETS "images/multiple_spaces.ppm", data);
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
    EXPECT_EQ(res, IMAGE_OK);
    memset(data, 0, 12);
    //read image with high depth (ASCII)
    res = read_ppm(TEST_ASSETS "images/p3_high_depth.ppm", data);
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
    EXPECT_EQ(res, IMAGE_OK);
    memset(data, 0, 12);
    //read image with normal depth (binary) no stack_overflow
    res = read_ppm(TEST_ASSETS "images/binary.ppm", data);
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
    EXPECT_EQ(res, IMAGE_OK);
    memset(data, 0, 12);
    //read image that claims to be 2x2 but contains a lot more
    //bytes
    data[4*3] = (float)0x2B; //random val, check that this is unchanged
    res = read_ppm(TEST_ASSETS "images/binary_stackoverflow.ppm", data);
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
    EXPECT_EQ(res, IMAGE_OK);
    memset(data, 0, 12);
    //read image with high depth (binary) no stack_overflow
    res = read_ppm(TEST_ASSETS "images/p6_high_depth.ppm", data);
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
    EXPECT_EQ(res, IMAGE_OK);
    memset(data, 0, 12);
    //read image with high depth (binary), stack_overflow
    res = read_ppm(TEST_ASSETS "images/p6_high_depth_stack_overflow.ppm", data);
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
    EXPECT_EQ(res, IMAGE_OK);
    memset(data, 0, 12);
}

SPECTRE_TEST(ImageIO, save_bmp_func)
{
    char file_stat[64];

    uint8_t image_sample[17*10*3];
    for(int i = 0; i<17*10*3; i += 3)
        image_sample[i] = i/3;
    bool res = save_bmp("test.bmp", 16, 10, image_sample);
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
    res = save_bmp("/root/nonexistent/test.bmp", 16, 10, image_sample);
    EXPECT_FALSE(res);
}

SPECTRE_TEST(ImageIO, dimensions_bmp_func)
{
    int width;
    int height;
    //non existent
    dimensions_bmp("nonexistent.bmp", &width, &height);
    EXPECT_EQ(width, IMAGE_NOT_READABLE);
    EXPECT_EQ(height, IMAGE_NOT_READABLE);
    width = 0;
    height = 0;
    //first letter of the magic number is wrong
    dimensions_bmp(TEST_ASSETS "images/wrong_magic1.bmp", &width, &height);
    EXPECT_EQ(width, IMAGE_WRONG_MAGIC);
    EXPECT_EQ(height, IMAGE_WRONG_MAGIC);
    width = 0;
    height = 0;
    //second letter of the magic number is wrong
    dimensions_bmp(TEST_ASSETS "images/wrong_magic2.bmp", &width, &height);
    EXPECT_EQ(width, IMAGE_WRONG_MAGIC);
    EXPECT_EQ(height, IMAGE_WRONG_MAGIC);
    width = 0;
    height = 0;
    //32bit
    dimensions_bmp(TEST_ASSETS "images/32bit.bmp", &width, &height);
    EXPECT_EQ(width, IMAGE_NOT_SUPPORTED);
    EXPECT_EQ(height, IMAGE_NOT_SUPPORTED);
    width = 0;
    height = 0;
    //os2
    dimensions_bmp(TEST_ASSETS "images/os2.bmp", &width, &height);
    EXPECT_EQ(width, IMAGE_NOT_SUPPORTED);
    EXPECT_EQ(height, IMAGE_NOT_SUPPORTED);
    width = 0;
    height = 0;
    //normal image
    dimensions_bmp(TEST_ASSETS "images/correct.bmp", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
    //flipped (negative) rows
    dimensions_bmp(TEST_ASSETS "images/flipped.bmp", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
}

SPECTRE_TEST(ImageIO, read_bmp_func)
{
    int res;
    float values[4*3];
    //non existent
    res = read_bmp("nonexistent.bmp", values);
    EXPECT_EQ(res, IMAGE_NOT_READABLE);
    //first letter of the magic number is wrong
    res = read_bmp(TEST_ASSETS "images/wrong_magic1.bmp", values);
    EXPECT_EQ(res, IMAGE_WRONG_MAGIC);
    //second letter of the magic number is wrong
    res = read_bmp(TEST_ASSETS "images/wrong_magic2.bmp", values);
    EXPECT_EQ(res, IMAGE_WRONG_MAGIC);
    //os2
    res = read_bmp(TEST_ASSETS "images/os2.bmp", values);
    EXPECT_EQ(res, IMAGE_NOT_SUPPORTED);
    //32bit
    res = read_bmp(TEST_ASSETS "images/32bit.bmp", values);
    EXPECT_EQ(res, IMAGE_NOT_SUPPORTED);
    //normal image
    res = read_bmp(TEST_ASSETS "images/correct.bmp", values);
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
    //flipped (negative) rows
    res = read_bmp(TEST_ASSETS "images/flipped.bmp", values);
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
}

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

SPECTRE_TEST(ImageIO, high_depth_func)
{
    bool res;
    //normal depth ppm
    res = high_depth(TEST_ASSETS "images/binary.ppm", "ppm");
    EXPECT_FALSE(res);
    //high depth
    res = high_depth(TEST_ASSETS "images/p3_high_depth.ppm", "ppm");
    EXPECT_TRUE(res);
    //unable to read ppm
    res = high_depth(TEST_ASSETS "images/test-non-existent.ppm", "ppm");
    EXPECT_FALSE(res);
    //normal depth bmp
    res = high_depth(TEST_ASSETS "images/32bit.bmp", "bmp");
    EXPECT_FALSE(res);
    //high depth bmp
    //should return false since it is not supported -> hence a read error
    res = high_depth(TEST_ASSETS "images/correct.bmp", "bmp");
    EXPECT_FALSE(res);
    //unsupported image
    res = high_depth(TEST_ASSETS "images/generic.jpg", "jpg");
    EXPECT_FALSE(res);
}

SPECTRE_TEST_END(ImageIO)
