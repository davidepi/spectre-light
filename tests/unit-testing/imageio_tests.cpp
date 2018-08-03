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

#define ALPHA(x) (x & 0x000000FF)
#define RED(x) (x & 0x0000FF00) >> 8
#define GREEN(x) (x & 0x00FF0000) >> 16
#define BLUE(x )(x & 0xFF000000) >> 24

//just a random image in BGRA format
static const uint32_t write_data[100] = {
    0xD7F740FF, 0x17E985FF, 0x75E03FFF, 0xEE22AEFF,
    0xD6D91BFF, 0x2383B1FF, 0x81C778FF, 0x77FEDDFF,
    0xBFE181FF, 0x8E0EB3FF, 0xD0B2A0FF, 0xA83667FF,
    0x84E6D4FF, 0x8E5F89FF, 0x860CECFF, 0x5E3EABFF,
    0x962E42FF, 0x7A9B6CFF, 0xCD675AFF, 0x8F3148FF,
    0xA5C6DDFF, 0xCCB409FF, 0xF626EEFF, 0xE466C0FF,
    0xBCA8E1FF, 0x90471DFF, 0x1B9AB5FF, 0xAFCCB4FF,
    0x3BA703FF, 0x9B5B84FF, 0x276C7AFF, 0x8269E5FF,
    0xD488AAFF, 0x997F2AFF, 0xD02F06FF, 0x04ADA5FF,
    0xBA5FCCFF, 0xC8699BFF, 0xECBDC0FF, 0x8A06C4FF,
    0x627DD9FF, 0x5F1F0FFF, 0x77D9ADFF, 0x99B42BFF,
    0x92721EFF, 0x3ABF6AFF, 0xB5E53EFF, 0x93290AFF,
    0x443339FF, 0xCE7B61FF, 0x026C8EFF, 0x5D242DFF,
    0x95F8EAFF, 0xB9B9B3FF, 0xD2EA2FFF, 0x202B6BFF,
    0xCFEDD8FF, 0xE8C678FF, 0x8669D6FF, 0x4D2B15FF,
    0xE23D32FF, 0x8AB71DFF, 0x634401FF, 0x34CE62FF,
    0xE8F961FF, 0xD78497FF, 0x6D0748FF, 0xA98C57FF,
    0x2CC224FF, 0x99994BFF, 0xCD3789FF, 0x8F897BFF,
    0xFEC95DFF, 0x6F17F3FF, 0xABF4B5FF, 0xDBDD5EFF,
    0xC17F13FF, 0x9F24CFFF, 0x767A60FF, 0xE9B72AFF,
    0x7A45B1FF, 0x53E700FF, 0x43DBAAFF, 0x594ED3FF,
    0x93E17DFF, 0x9333E2FF, 0xC7D31CFF, 0xC28E3BFF,
    0x5BDB16FF, 0x3F644BFF, 0x72EA05FF, 0x7EFC5BFF,
    0x69B773FF, 0x6C3E24FF, 0xD0F73DFF, 0x036D43FF,
    0x0B10EBFF, 0xF6A428FF, 0x43AE1CFF, 0x8CCA04FF
};

SPECTRE_TEST_INIT(ImageIO_tests)

SPECTRE_TEST(ImageIO, packed_structures)
{
    //Assert that the actual image headers are packed
    //If this doesn't hold the images ARE NOT read correctly
    ASSERT_EQ(sizeof(struct bmp_header), 14);
    ASSERT_EQ(sizeof(struct bmp_dib_v3), 40);
    ASSERT_EQ(sizeof(struct tga_header), 18);
}

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
    uint32_t data[2*2+1];
    //non existent
    res = img_read8("nonexistent.ppm", "ppm", data);
    EXPECT_FALSE(res);
    //first letter of the magic number is wrong
    res = img_read8(TEST_ASSETS "images/wrong_magic1.ppm", "ppm", data);
    EXPECT_FALSE(res);
    //second letter of the magic number is wrong
    res = img_read8(TEST_ASSETS "images/wrong_magic2.ppm", "ppm", data);
    EXPECT_FALSE(res);
    //read image with normal depth (ASCII)
    res = img_read8(TEST_ASSETS "images/multiple_spaces.ppm", "ppm", data);
    EXPECT_EQ(RED(data[0]), (uint8_t)255);
    EXPECT_EQ(GREEN(data[0]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[0]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[0]), (uint8_t)255);
    EXPECT_EQ(RED(data[1]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[1]), (uint8_t)255);
    EXPECT_EQ(BLUE(data[1]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[1]), (uint8_t)255);
    EXPECT_EQ(RED(data[2]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[2]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[2]), (uint8_t)255);
    EXPECT_EQ(ALPHA(data[2]), (uint8_t)255);
    EXPECT_EQ(RED(data[3]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[3]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[3]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[3]), (uint8_t)255);
    EXPECT_TRUE(res);
    //read image with high depth (ASCII)
     memset(data, 0, sizeof(data));
    res = img_read8(TEST_ASSETS "images/p3_high_depth.ppm", "ppm", data);
    EXPECT_EQ(RED(data[0]), (uint8_t)255);
    EXPECT_EQ(GREEN(data[0]), (uint8_t)255);
    EXPECT_EQ(BLUE(data[0]), (uint8_t)255);
    EXPECT_EQ(ALPHA(data[0]), (uint8_t)255);
    EXPECT_EQ(RED(data[1]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[1]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[1]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[1]), (uint8_t)255);
    EXPECT_EQ(RED(data[2]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[2]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[2]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[2]), (uint8_t)255);
    EXPECT_EQ(RED(data[3]), (uint8_t)255);
    EXPECT_EQ(GREEN(data[3]), (uint8_t)255);
    EXPECT_EQ(BLUE(data[3]), (uint8_t)255);
    EXPECT_EQ(ALPHA(data[3]), (uint8_t)255);
    EXPECT_TRUE(res);
    //read image with normal depth (binary) no stack_overflow
    res = img_read8(TEST_ASSETS "images/binary.ppm", "ppm", data);
    EXPECT_EQ(RED(data[0]), (uint8_t)255);
    EXPECT_EQ(GREEN(data[0]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[0]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[0]), (uint8_t)255);
    EXPECT_EQ(RED(data[1]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[1]), (uint8_t)255);
    EXPECT_EQ(BLUE(data[1]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[1]), (uint8_t)255);
    EXPECT_EQ(RED(data[2]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[2]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[2]), (uint8_t)255);
    EXPECT_EQ(ALPHA(data[2]), (uint8_t)255);
    EXPECT_EQ(RED(data[3]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[3]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[3]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[3]), (uint8_t)255);
    EXPECT_TRUE(res);
    memset(data, 0, sizeof(data));
    //read image that claims to be 2x2 but contains a lot more
    //bytes
    data[4] = 0x2B2B2B2B;
    res = img_read8(TEST_ASSETS "images/binary_stackoverflow.ppm", "ppm", data);
    EXPECT_EQ(RED(data[0]), (uint8_t)255);
    EXPECT_EQ(GREEN(data[0]), (uint8_t)255);
    EXPECT_EQ(BLUE(data[0]), (uint8_t)255);
    EXPECT_EQ(ALPHA(data[0]), (uint8_t)255);
    EXPECT_EQ(RED(data[1]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[1]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[1]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[1]), (uint8_t)255);
    EXPECT_EQ(RED(data[2]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[2]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[2]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[2]), (uint8_t)255);
    EXPECT_EQ(RED(data[3]), (uint8_t)255);
    EXPECT_EQ(GREEN(data[3]), (uint8_t)255);
    EXPECT_EQ(BLUE(data[3]), (uint8_t)255);
    EXPECT_EQ(ALPHA(data[3]), (uint8_t)255);
    EXPECT_EQ(data[4], 0x2B2B2B2B);
    EXPECT_TRUE(res);
    //read image with high depth (binary) no stack_overflow
    res = img_read8(TEST_ASSETS "images/p6_high_depth.ppm", "ppm", data);
    EXPECT_EQ(RED(data[0]), (uint8_t)255);
    EXPECT_EQ(GREEN(data[0]), (uint8_t)255);
    EXPECT_EQ(BLUE(data[0]), (uint8_t)255);
    EXPECT_EQ(ALPHA(data[0]), (uint8_t)255);
    EXPECT_EQ(RED(data[1]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[1]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[1]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[1]), (uint8_t)255);
    EXPECT_EQ(RED(data[2]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[2]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[2]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[2]), (uint8_t)255);
    EXPECT_EQ(RED(data[3]), (uint8_t)255);
    EXPECT_EQ(GREEN(data[3]), (uint8_t)255);
    EXPECT_EQ(BLUE(data[3]), (uint8_t)255);
    EXPECT_EQ(ALPHA(data[3]), (uint8_t)255);
    EXPECT_TRUE(res);
    //read image with high depth (binary), stack_overflow
    data[4] = 0x2B2B2B2B;
    res = img_read8(TEST_ASSETS "images/p6_high_depth_stack_overflow.ppm",
                    "ppm", data);
    EXPECT_EQ(RED(data[0]), (uint8_t)255);
    EXPECT_EQ(GREEN(data[0]), (uint8_t)255);
    EXPECT_EQ(BLUE(data[0]), (uint8_t)255);
    EXPECT_EQ(ALPHA(data[0]), (uint8_t)255);
    EXPECT_EQ(RED(data[1]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[1]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[1]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[1]), (uint8_t)255);
    EXPECT_EQ(RED(data[2]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[2]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[2]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[2]), (uint8_t)255);
    EXPECT_EQ(RED(data[3]), (uint8_t)255);
    EXPECT_EQ(GREEN(data[3]), (uint8_t)255);
    EXPECT_EQ(BLUE(data[3]), (uint8_t)255);
    EXPECT_EQ(ALPHA(data[3]), (uint8_t)255);
    EXPECT_EQ(data[4], 0x2B2B2B2B);
    EXPECT_TRUE(res);
}

SPECTRE_TEST(ImageIO, ppm_write_func)
{
    uint32_t read_data[100];
    bool res;
    res = img_write("test.ppm", "ppm", 10, 10, write_data);
    ASSERT_TRUE(res);
    res = img_read8("test.ppm", "ppm", read_data);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.ppm"), 0);
    for(int i = 0; i<100; i++)
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
    uint32_t data[4];
    //non existent
    res = img_read8("nonexistent.bmp", "bmp", data);
    EXPECT_EQ(res, 0);
    //first letter of the magic number is wrong
    res = img_read8(TEST_ASSETS "images/wrong_magic1.bmp", "bmp", data);
    EXPECT_EQ(res, 0);
    //second letter of the magic number is wrong
    res = img_read8(TEST_ASSETS "images/wrong_magic2.bmp", "bmp", data);
    EXPECT_EQ(res, 0);
    //os2
    res = img_read8(TEST_ASSETS "images/os2.bmp", "bmp", data);
    EXPECT_EQ(res, 0);
    //normal image
    res = img_read8(TEST_ASSETS "images/correct.bmp", "bmp", data);
    EXPECT_EQ(RED(data[0]), (uint8_t)255);
    EXPECT_EQ(GREEN(data[0]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[0]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[0]), (uint8_t)255);
    EXPECT_EQ(RED(data[1]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[1]), (uint8_t)255);
    EXPECT_EQ(BLUE(data[1]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[1]), (uint8_t)255);
    EXPECT_EQ(RED(data[2]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[2]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[2]), (uint8_t)255);
    EXPECT_EQ(ALPHA(data[2]), (uint8_t)255);
    EXPECT_EQ(RED(data[3]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[3]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[3]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[3]), (uint8_t)255);
    EXPECT_EQ(res, 1);
    //flipped (negative) rows
    res = img_read8(TEST_ASSETS "images/flipped.bmp", "bmp", data);
    EXPECT_EQ(RED(data[0]), (uint8_t)255);
    EXPECT_EQ(GREEN(data[0]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[0]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[0]), (uint8_t)255);
    EXPECT_EQ(RED(data[1]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[1]), (uint8_t)255);
    EXPECT_EQ(BLUE(data[1]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[1]), (uint8_t)255);
    EXPECT_EQ(RED(data[2]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[2]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[2]), (uint8_t)255);
    EXPECT_EQ(ALPHA(data[2]), (uint8_t)255);
    EXPECT_EQ(RED(data[3]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[3]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[3]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[3]), (uint8_t)255);
    EXPECT_EQ(res, 1);
    //32bit
    res = img_read8(TEST_ASSETS "images/32bit.bmp", "bmp", data);
    EXPECT_EQ(RED(data[0]), (uint8_t)255);
    EXPECT_EQ(GREEN(data[0]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[0]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[0]), (uint8_t)255);
    EXPECT_EQ(RED(data[1]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[1]), (uint8_t)255);
    EXPECT_EQ(BLUE(data[1]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[1]), (uint8_t)128);
    EXPECT_EQ(RED(data[2]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[2]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[2]), (uint8_t)255);
    EXPECT_EQ(ALPHA(data[2]), (uint8_t)66);
    EXPECT_EQ(RED(data[3]), (uint8_t)0);
    EXPECT_EQ(GREEN(data[3]), (uint8_t)0);
    EXPECT_EQ(BLUE(data[3]), (uint8_t)0);
    EXPECT_EQ(ALPHA(data[3]), (uint8_t)33);
    EXPECT_EQ(res, 1);
}

SPECTRE_TEST(ImageIO, bmp_write_func)
{
    uint32_t read_data[300];
    bool res;
    res = img_write("test.bmp", "bmp", 10, 10, write_data);
    ASSERT_TRUE(res);
    res = img_read8("test.bmp", "bmp", read_data);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.bmp"), 0);
    for(int i = 0; i<100; i++)
        EXPECT_EQ(read_data[i], write_data[i]);

    //non existent folder
    res = img_write("/root/nonexistent/test.bmp", "bmp", 10, 10, write_data);
    EXPECT_FALSE(res);
}
/*
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
    EXPECT_EQ(values[0], (uint8_t)(255 >> 3 << 3));
    EXPECT_EQ(values[1], (uint8_t)0);
    EXPECT_EQ(values[2], (uint8_t)0);
    EXPECT_EQ(values[3], (uint8_t)0);
    EXPECT_EQ(values[4], (uint8_t)(255 >> 3 << 3));
    EXPECT_EQ(values[5], (uint8_t)0);
    EXPECT_EQ(values[6], (uint8_t)0);
    EXPECT_EQ(values[7], (uint8_t)0);
    EXPECT_EQ(values[8], (uint8_t)(255 >> 3 << 3));
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
        EXPECT_EQ(rleval[i], (uint8_t)(rleval_expected[i] >> 3 << 3));
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
    /*
     *  Colors are really different from the input one while applied on such a
     *  small image. However, this has been hand-checked on a 3840*2160 image
     *  and the results are correct. This test is left here just to be
     *  notified if something unexpectedly changes.
     *
     *  Moreover, these values are different between OSX/Linux. Visually and
     *  manually checked on both platforms
     *
#ifdef __APPLE__
    uint8_t check_data[300] = {
            0xBA, 0xFF, 0x71, 0x68, 0xCA, 0x4F, 0x83, 0xCC, 0x83, 0x7C, 0x6A,
            0x68, 0xEF, 0xA9, 0xCE, 0x6D, 0x6A, 0x71, 0x6A, 0xCE, 0x9A, 0x90,
            0xFA, 0xB0, 0xD3, 0xCD, 0xB7, 0x8E, 0x1D, 0x5D, 0xB9, 0xC5, 0x7D,
            0x61, 0x63, 0x3B, 0xDC, 0xBC, 0xC7, 0xA2, 0x54, 0x90, 0x7C, 0x28,
            0x75, 0x61, 0x47, 0x74, 0x32, 0x5E, 0x51, 0x6C, 0xA1, 0x73, 0x8E,
            0x83, 0x6D, 0x87, 0x32, 0x5B, 0xC5, 0xBA, 0xC8, 0xCF, 0x91, 0xB6,
            0xC4, 0x51, 0x94, 0xDF, 0x6A, 0xBB, 0xDE, 0x96, 0xE2, 0x62, 0x4C,
            0x7D, 0x74, 0x76, 0x82, 0xC5, 0xC2, 0xB1, 0x8A, 0x6C, 0x61, 0x9E,
            0x5C, 0x78, 0x36, 0x5F, 0x97, 0x8D, 0x73, 0xA2, 0xDB, 0x86, 0xA3,
            0xB1, 0x66, 0x6B, 0x67, 0x54, 0x4D, 0x6D, 0x81, 0x78, 0x80, 0x8B,
            0x85, 0x9D, 0x84, 0x7F, 0xF1, 0xBA, 0xBF, 0x73, 0x29, 0x4E, 0x48,
            0x8E, 0xBF, 0x17, 0x39, 0x43, 0xBB, 0xBD, 0x8B, 0xA3, 0xA9, 0x47,
            0x65, 0x89, 0x1F, 0x75, 0xA5, 0x5B, 0xB8, 0xD0, 0xB0, 0x56, 0x3E,
            0x3A, 0x62, 0x26, 0x32, 0xC2, 0x77, 0x95, 0x4D, 0x4D, 0x69, 0x2A,
            0x3C, 0x2E, 0xC3, 0xEF, 0xA2, 0x9F, 0xD6, 0x5E, 0xBC, 0xEA, 0x70,
            0x2B, 0x3E, 0x00, 0xEC, 0xE3, 0xC4, 0xD9, 0xC0, 0xBC, 0x97, 0x75,
            0x73, 0x4F, 0x28, 0x17, 0xB5, 0x4C, 0x5B, 0xB8, 0x8C, 0x81, 0x37,
            0x54, 0x28, 0x74, 0xAC, 0x6F, 0xDC, 0xEF, 0xB8, 0xBF, 0x97, 0x74,
            0x5B, 0x1C, 0x0B, 0xA9, 0x88, 0x77, 0x82, 0x8A, 0x63, 0x90, 0x9B,
            0x56, 0xBA, 0x4D, 0x48, 0xAD, 0x7C, 0x6B, 0xC0, 0xD6, 0xC1, 0x2C,
            0x57, 0x50, 0xD6, 0xD6, 0xDE, 0xF8, 0xBB, 0xC0, 0xBE, 0x71, 0x5D,
            0x77, 0x59, 0x27, 0x6B, 0x87, 0x3C, 0xA5, 0xCD, 0x6C, 0x62, 0x6B,
            0x2C, 0x93, 0xAF, 0x74, 0x8D, 0xBA, 0x8F, 0x43, 0x70, 0x5B, 0xB3,
            0xC3, 0xC3, 0x73, 0x5E, 0x5D, 0xD7, 0xB5, 0x99, 0xA3, 0x99, 0x52,
            0x98, 0xB3, 0x4A, 0x45, 0x70, 0x00, 0x5F, 0xE7, 0x49, 0x8B, 0xEF,
            0x7B, 0x75, 0xB4, 0x65, 0x30, 0x5F, 0x19, 0xBE, 0xE9, 0xB1, 0x37,
            0x54, 0x42, 0x20, 0x2A, 0x2B, 0xAF, 0xB5, 0x85, 0x79, 0x94, 0x11,
            0x90, 0xC4, 0x1A
    };
#elif __linux__
    uint8_t check_data[300] = {
            0xD0, 0xE9, 0xA8, 0x99, 0xA9, 0x7A, 0xB2, 0xAF, 0xA0, 0x76, 0x6A,
            0x76, 0xC8, 0xBA, 0xDE, 0x6B, 0x68, 0x83, 0x9C, 0xB3, 0xA3, 0xCF,
            0xD7, 0xC0, 0xEC, 0xBD, 0xC5, 0x77, 0x2E, 0x42, 0xAF, 0xC5, 0x94,
            0x5D, 0x64, 0x43, 0xD6, 0xC0, 0xC2, 0x86, 0x66, 0x7B, 0x55, 0x41,
            0x5D, 0x55, 0x50, 0x64, 0x45, 0x54, 0x4F, 0x8C, 0x8D, 0x87, 0xA0,
            0x76, 0x80, 0x7A, 0x3B, 0x4E, 0xB5, 0xC6, 0xB4, 0xAE, 0xA6, 0xA3,
            0xA2, 0x65, 0x84, 0xC1, 0x7E, 0xA1, 0xCC, 0xA7, 0xB8, 0x60, 0x53,
            0x5C, 0x77, 0x74, 0x85, 0xC4, 0xBC, 0xD1, 0x88, 0x69, 0x7B, 0x8F,
            0x64, 0x77, 0x51, 0x5C, 0x62, 0x84, 0x7C, 0x89, 0xC2, 0x92, 0xAC,
            0xA0, 0x6B, 0x7D, 0x6A, 0x54, 0x49, 0x81, 0x7A, 0x6A, 0x8D, 0x84,
            0x87, 0x95, 0x85, 0x92, 0xDD, 0xC1, 0xD0, 0x59, 0x37, 0x47, 0x78,
            0x7E, 0x94, 0x29, 0x31, 0x3C, 0xB0, 0xBC, 0xB2, 0x94, 0xA5, 0x85,
            0x6A, 0x7E, 0x4D, 0x8B, 0x98, 0x62, 0xCD, 0xC9, 0x99, 0x56, 0x43,
            0x25, 0x4F, 0x2F, 0x30, 0xAA, 0x84, 0x93, 0x58, 0x4A, 0x59, 0x35,
            0x35, 0x37, 0xCA, 0xE4, 0xC9, 0xA3, 0xC9, 0x98, 0xC0, 0xDF, 0x9C,
            0x2E, 0x3B, 0x00, 0xF4, 0xE3, 0xAB, 0xE0, 0xC3, 0x9B, 0x94, 0x7A,
            0x63, 0x44, 0x2D, 0x1F, 0x91, 0x5F, 0x54, 0xB3, 0x8F, 0x81, 0x4C,
            0x47, 0x33, 0x91, 0x9B, 0x76, 0xE3, 0xEE, 0xAC, 0xAC, 0xA4, 0x66,
            0x50, 0x22, 0x0B, 0xB3, 0x84, 0x70, 0x90, 0x87, 0x50, 0x91, 0x9B,
            0x52, 0x88, 0x6A, 0x38, 0x9D, 0x87, 0x5E, 0xD1, 0xCF, 0xB8, 0x46,
            0x4F, 0x34, 0xD7, 0xE0, 0xA9, 0xDB, 0xD1, 0x9C, 0xA9, 0x79, 0x6B,
            0x7B, 0x53, 0x39, 0x76, 0x83, 0x31, 0xA7, 0xCF, 0x5D, 0x4C, 0x7B,
            0x15, 0x8B, 0xB6, 0x67, 0x93, 0xB6, 0x98, 0x4E, 0x6A, 0x5B, 0xB0,
            0xCA, 0xA3, 0x63, 0x6C, 0x3F, 0xD1, 0xB8, 0x99, 0xA3, 0x96, 0x61,
            0x8E, 0xB7, 0x4D, 0x34, 0x7A, 0x00, 0x7F, 0xD4, 0x53, 0x9B, 0xE5,
            0x84, 0x76, 0xAC, 0x8A, 0x2E, 0x56, 0x4B, 0xC1, 0xE4, 0xC6, 0x42,
            0x52, 0x2B, 0x35, 0x28, 0x00, 0xB6, 0xB5, 0x72, 0x64, 0x9B, 0x26,
            0x77, 0xCA, 0x3C

    };
#else
#error "Unmatched platform: check manually the output jpg and update results"
#endif
    uint8_t read_data[300];
    bool res;
    res = img_write("test.jpg", "jpg", 10, 10, write_data);
    ASSERT_TRUE(res);
    res = img_read8("test.jpg", "jpg", read_data, NULL);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.jpg"), 0);
    for(int i = 0; i<300; i++)
        EXPECT_EQ(read_data[i], check_data[i]);

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
*/
SPECTRE_TEST_END(ImageIO_tests)
