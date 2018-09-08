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

//just a random image in BGRA format
static const uint32_t write_data[100] = {
        0xD7F740FF, 0x17E985FF, 0x75E03FFF, 0xEE22AEFF, 0xD6D91BFF, 0x2383B1FF,
        0x81C778FF, 0x77FEDDFF, 0xBFE181FF, 0x8E0EB3FF, 0xD0B2A0FF, 0xA83667FF,
        0x84E6D4FF, 0x8E5F89FF, 0x860CECFF, 0x5E3EABFF, 0x962E42FF, 0x7A9B6CFF,
        0xCD675AFF, 0x8F3148FF, 0xA5C6DDFF, 0xCCB409FF, 0xF626EEFF, 0xE466C0FF,
        0xBCA8E1FF, 0x90471DFF, 0x1B9AB5FF, 0xAFCCB4FF, 0x3BA703FF, 0x9B5B84FF,
        0x276C7AFF, 0x8269E5FF, 0xD488AAFF, 0x997F2AFF, 0xD02F06FF, 0x04ADA5FF,
        0xBA5FCCFF, 0xC8699BFF, 0xECBDC0FF, 0x8A06C4FF, 0x627DD9FF, 0x5F1F0FFF,
        0x77D9ADFF, 0x99B42BFF, 0x92721EFF, 0x3ABF6AFF, 0xB5E53EFF, 0x93290AFF,
        0x443339FF, 0xCE7B61FF, 0x026C8EFF, 0x5D242DFF, 0x95F8EAFF, 0xB9B9B3FF,
        0xD2EA2FFF, 0x202B6BFF, 0xCFEDD8FF, 0xE8C678FF, 0x8669D6FF, 0x4D2B15FF,
        0xE23D32FF, 0x8AB71DFF, 0x634401FF, 0x34CE62FF, 0xE8F961FF, 0xD78497FF,
        0x6D0748FF, 0xA98C57FF, 0x2CC224FF, 0x99994BFF, 0xCD3789FF, 0x8F897BFF,
        0xFEC95DFF, 0x6F17F3FF, 0xABF4B5FF, 0xDBDD5EFF, 0xC17F13FF, 0x9F24CFFF,
        0x767A60FF, 0xE9B72AFF, 0x7A45B1FF, 0x53E700FF, 0x43DBAAFF, 0x594ED3FF,
        0x93E17DFF, 0x9333E2FF, 0xC7D31CFF, 0xC28E3BFF, 0x5BDB16FF, 0x3F644BFF,
        0x72EA05FF, 0x7EFC5BFF, 0x69B773FF, 0x6C3E24FF, 0xD0F73DFF, 0x036D43FF,
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
    EXPECT_EQ(BGRA_RED(data[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[0]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 255U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 255U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[2]), 255U);
    EXPECT_EQ(BGRA_RED(data[3]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 255U);
    EXPECT_TRUE(res);
    //read image with high depth (ASCII)
    memset(data, 0, sizeof(data));
    res = img_read8(TEST_ASSETS "images/p3_high_depth.ppm", "ppm", data);
    EXPECT_EQ(BGRA_RED(data[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[0]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 255U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 255U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[2]), 255U);
    EXPECT_EQ(BGRA_RED(data[3]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 255U);
    EXPECT_TRUE(res);
    //read image with normal depth (binary) no stack_overflow
    res = img_read8(TEST_ASSETS "images/binary.ppm", "ppm", data);
    EXPECT_EQ(BGRA_RED(data[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[0]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 255U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 255U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[2]), 255U);
    EXPECT_EQ(BGRA_RED(data[3]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 255U);
    EXPECT_TRUE(res);
    memset(data, 0, sizeof(data));
    //read image that claims to be 2x2 but contains a lot more
    //bytes
    data[4] = 0x2B2B2B2B;
    res = img_read8(TEST_ASSETS "images/binary_stackoverflow.ppm", "ppm", data);
    EXPECT_EQ(BGRA_RED(data[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[0]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 255U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 255U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[2]), 255U);
    EXPECT_EQ(BGRA_RED(data[3]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 255U);
    EXPECT_EQ(data[4], 0x2B2B2B2BU);
    EXPECT_TRUE(res);
    //read image with high depth (binary) no stack_overflow
    res = img_read8(TEST_ASSETS "images/p6_high_depth.ppm", "ppm", data);
    EXPECT_EQ(BGRA_RED(data[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[0]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 255U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 255U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[2]), 255U);
    EXPECT_EQ(BGRA_RED(data[3]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 255U);
    EXPECT_TRUE(res);
    //read image with high depth (binary), stack_overflow
    data[4] = 0x2B2B2B2B;
    res = img_read8(TEST_ASSETS "images/p6_high_depth_stack_overflow.ppm",
                    "ppm", data);
    EXPECT_EQ(BGRA_RED(data[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[0]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 255U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 255U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[2]), 255U);
    EXPECT_EQ(BGRA_RED(data[3]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 255U);
    EXPECT_EQ(data[4], 0x2B2B2B2BU);
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
    EXPECT_EQ(BGRA_RED(data[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[0]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 255U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 255U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[2]), 255U);
    EXPECT_EQ(BGRA_RED(data[3]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 255U);
    EXPECT_EQ(res, 1);
    //flipped (negative) rows
    res = img_read8(TEST_ASSETS "images/flipped.bmp", "bmp", data);
    EXPECT_EQ(BGRA_RED(data[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[0]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 255U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 255U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[2]), 255U);
    EXPECT_EQ(BGRA_RED(data[3]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 255U);
    EXPECT_EQ(res, 1);
    //32bit
    res = img_read8(TEST_ASSETS "images/32bit.bmp", "bmp", data);
    EXPECT_EQ(BGRA_RED(data[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[0]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 255U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 128U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[2]), 66U);
    EXPECT_EQ(BGRA_RED(data[3]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 33U);
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
    uint32_t data[12];
    res = -1;
    res = img_read8("nonexistent.tga", "tga", data);
    EXPECT_EQ(res, 0);
    res = -1;
    res = img_read8("bmpastga.tga", "tga", data);
    EXPECT_EQ(res, 0);
    //normal image
    res = -1;
    res = img_read8(TEST_ASSETS "images/24bit.tga", "tga", data);
    EXPECT_EQ(BGRA_RED(data[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[0]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 255U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 255U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[2]), 255U);
    EXPECT_EQ(BGRA_RED(data[3]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 255U);
    EXPECT_EQ(res, 1);
    //32 bit BGRA_ALPHA array
    res = -1;
    res = img_read8(TEST_ASSETS "images/32bit.tga", "tga", data);
    EXPECT_EQ(BGRA_RED(data[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[0]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 255U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 128U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[2]), 66U);
    EXPECT_EQ(BGRA_RED(data[3]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 33U);
    EXPECT_EQ(res, 1);
    //16 bit
    res = -1;
    res = img_read8(TEST_ASSETS "images/16bit.tga", "tga", data);
    //shifts are used to account for precision loss with the 16 bits values
    EXPECT_EQ(BGRA_RED(data[0]), (255U >> 3 << 3));
    EXPECT_EQ(BGRA_GREEN(data[0]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 255U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), (255U >> 3 << 3));
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 255U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), (255U >> 3 << 3));
    EXPECT_EQ(BGRA_ALPHA(data[2]), 255U);
    EXPECT_EQ(BGRA_RED(data[3]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 255U);
    EXPECT_EQ(res, 1);
    //RLE image data
    uint32_t rleval[100];
    uint32_t rleval_expected[100] = {
            0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00,
            0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00,
            0x0000FF00, 0x0000FF00, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF,
            0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FF00, 0x0000FF00,
            0x0000FF00, 0x0000FF00, 0x0000FFFF, 0x0000FFFF, 0x0000FF00,
            0x0000FF00, 0x0000FFFF, 0x0000FFFF, 0x0000FF00, 0x0000FF00,
            0x0000FF00, 0x0000FF00, 0x0000FFFF, 0x0000FFFF, 0x0000FF00,
            0x0000FF00, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FF00,
            0x0000FF00, 0x0000FF00, 0x9F7E5BFF, 0x9F7E5BFF, 0x9F7E5B00,
            0x9F7E5B00, 0x9F7E5BFF, 0x9F7E5BFF, 0x9F7E5BFF, 0x9F7E5B00,
            0x0000FF00, 0x0000FF00, 0x9F7E5BFF, 0x9F7E5BFF, 0x9F7E5B00,
            0x9F7E5BFF, 0x9F7E5BFF, 0x9F7E5BFF, 0x9F7E5B00, 0x9F7E5B00,
            0x0000FF00, 0x0000FF00, 0x9F7E5BFF, 0x9F7E5BFF, 0x9F7E5BFF,
            0x62004FFF, 0x62004FFF, 0x9F7E5B00, 0x9F7E5B00, 0x9F7E5B00,
            0x0000FF00, 0x0000FF00, 0x9F7E5BFF, 0x9F7E5BFF, 0x9F7E5B00,
            0x62004FFF, 0x62004FFF, 0x9F7E5BFF, 0x9F7E5B00, 0x9F7E5B00,
            0x0000FF00, 0x0000FF00, 0x9F7E5BFF, 0x9F7E5BFF, 0x9F7E5B00,
            0x9F7E5B00, 0x9F7E5BFF, 0x9F7E5BFF, 0x9F7E5BFF, 0x9F7E5B00,
            0x0000FF00, 0x0000FF00, 0x9F7E5B00, 0x9F7E5B00, 0x9F7E5B00,
            0x9F7E5B00, 0x9F7E5B00, 0x9F7E5B00, 0x9F7E5B00, 0x9F7E5B00
    };
    res = -1;
    res = img_read8(TEST_ASSETS "images/24bitRLE.tga", "tga", rleval);
    ASSERT_EQ(res, 1);
    for(int i = 0; i<100; i++)
    {
        EXPECT_EQ(BGRA_RED(rleval[i]), BGRA_RED(rleval_expected[i]));
        EXPECT_EQ(BGRA_GREEN(rleval[i]), BGRA_GREEN(rleval_expected[i]));
        EXPECT_EQ(BGRA_BLUE(rleval[i]), BGRA_BLUE(rleval[i]));
        //the expected value is for the 32 bit, with BGRA_ALPHA support
        //the 24 bit is without BGRA_ALPHA so its value should always be 0xFF
        EXPECT_EQ(BGRA_ALPHA(rleval[i]), 0x000000FFU);
    }
    memset(rleval, 0, sizeof(rleval));
    res = -1;
    res = img_read8(TEST_ASSETS "images/16bitRLE.tga", "tga", rleval);
    ASSERT_EQ(res, 1);
    for(int i = 0; i<100; i++)
    {
        //shifts are used to account for precision lost with the 16 bits values
        EXPECT_EQ(BGRA_RED(rleval[i]), BGRA_RED(rleval_expected[i]) >> 3 << 3);
        EXPECT_EQ(BGRA_GREEN(rleval[i]),
                  BGRA_GREEN(rleval_expected[i]) >> 3 << 3);
        EXPECT_EQ(BGRA_BLUE(rleval[i]), BGRA_BLUE(rleval[i]) >> 3 << 3);
        //the expected value is for the 32 bit, with BGRA_ALPHA support
        //the 24 bit is without BGRA_ALPHA so its value should always be 0xFF
        EXPECT_EQ(BGRA_ALPHA(rleval[i]), 0x000000FFU);
    }
    memset(rleval, 0, sizeof(rleval));
    res = -1;
    res = -1;
    res = img_read8(TEST_ASSETS "images/32bitRLE.tga", "tga", rleval);
    ASSERT_EQ(res, 1);
    for(int i = 0; i<100; i++)
        EXPECT_EQ(rleval[i], rleval_expected[i]);
}

SPECTRE_TEST(ImageIO, tga_save_func)
{
    uint32_t read_data[100];
    bool res;
    res = img_write("test.tga", "tga", 10, 10, write_data);
    ASSERT_TRUE(res);
    res = img_read8("test.tga", "tga", read_data);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.tga"), 0);
    for(int i = 0; i<100; i++)
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
    uint32_t values[6];
    res = img_read8("nonexistent.jpg", "jpg", values);
    EXPECT_FALSE(res);
    res = img_read8(TEST_ASSETS "images/bmpasjpg.jpg", "jpg", values);
    EXPECT_FALSE(res);
    res = img_read8(TEST_ASSETS "images/generic.jpg", "jpg", values);
    EXPECT_TRUE(res);
    //Strange values (not 0 or 255) are given to jpg compression. These has been
    //checked previously with floating point values and an epsilon of 1e-2
    EXPECT_EQ(BGRA_RED(values[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(values[0]), 2U);
    EXPECT_EQ(BGRA_BLUE(values[0]), 2U);
    EXPECT_EQ(BGRA_ALPHA(values[0]), 255U);
    EXPECT_EQ(BGRA_RED(values[1]), 255U);
    EXPECT_EQ(BGRA_GREEN(values[1]), 250U);
    EXPECT_EQ(BGRA_BLUE(values[1]), 6U);
    EXPECT_EQ(BGRA_ALPHA(values[1]), 255U);
    EXPECT_EQ(BGRA_RED(values[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(values[2]), 255U);
    EXPECT_EQ(BGRA_BLUE(values[2]), 0U);
    EXPECT_EQ(BGRA_ALPHA(values[2]), 255U);
    EXPECT_EQ(BGRA_RED(values[3]), 14U);
    EXPECT_EQ(BGRA_GREEN(values[3]), 4U);
    EXPECT_EQ(BGRA_BLUE(values[3]), 255U);
    EXPECT_EQ(BGRA_ALPHA(values[3]), 255U);
    EXPECT_EQ(BGRA_RED(values[4]), 255U);
    EXPECT_EQ(BGRA_GREEN(values[4]), 255U);
    EXPECT_EQ(BGRA_BLUE(values[4]), 250U);
    EXPECT_EQ(BGRA_ALPHA(values[4]), 255U);
    EXPECT_EQ(BGRA_RED(values[5]), 7U);
    EXPECT_EQ(BGRA_GREEN(values[5]), 0U);
    EXPECT_EQ(BGRA_BLUE(values[5]), 0U);
    EXPECT_EQ(BGRA_ALPHA(values[5]), 255U);

    res = img_read8(TEST_ASSETS "images/generic.jpeg", "jpeg", values);
    EXPECT_TRUE(res);
    EXPECT_EQ(BGRA_RED(values[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(values[0]), 2U);
    EXPECT_EQ(BGRA_BLUE(values[0]), 2U);
    EXPECT_EQ(BGRA_ALPHA(values[0]), 255U);
    EXPECT_EQ(BGRA_RED(values[1]), 255U);
    EXPECT_EQ(BGRA_GREEN(values[1]), 250U);
    EXPECT_EQ(BGRA_BLUE(values[1]), 6U);
    EXPECT_EQ(BGRA_ALPHA(values[1]), 255U);
    EXPECT_EQ(BGRA_RED(values[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(values[2]), 255U);
    EXPECT_EQ(BGRA_BLUE(values[2]), 0U);
    EXPECT_EQ(BGRA_ALPHA(values[2]), 255U);
    EXPECT_EQ(BGRA_RED(values[3]), 14U);
    EXPECT_EQ(BGRA_GREEN(values[3]), 4U);
    EXPECT_EQ(BGRA_BLUE(values[3]), 255U);
    EXPECT_EQ(BGRA_ALPHA(values[3]), 255U);
    EXPECT_EQ(BGRA_RED(values[4]), 255U);
    EXPECT_EQ(BGRA_GREEN(values[4]), 255U);
    EXPECT_EQ(BGRA_BLUE(values[4]), 250U);
    EXPECT_EQ(BGRA_ALPHA(values[4]), 255U);
    EXPECT_EQ(BGRA_RED(values[5]), 7U);
    EXPECT_EQ(BGRA_GREEN(values[5]), 0U);
    EXPECT_EQ(BGRA_BLUE(values[5]), 0U);
    EXPECT_EQ(BGRA_ALPHA(values[5]), 255U);
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
     */
#ifdef __APPLE__
    uint32_t check_data[100] = {
            0xABEF62FF, 0x82E468FF, 0x79C27AFF, 0x75625FFF, 0xD38DB1FF,
            0x88848AFF, 0x5EC28EFF, 0x9EFFBEFF, 0xCCC7B2FF, 0x9C2F6DFF,
            0xBCC77FFF, 0x5D5F35FF, 0xF1CFD9FF, 0xA45693FF, 0x903D88FF,
            0x6B527EFF, 0x1D493CFF, 0x699C70FF, 0x7F7460FF, 0x832D55FF,
            0xCEC4D1FF, 0xB07198FF, 0xCC599CFF, 0xDD69BCFF, 0xE49CE8FF,
            0x473263FF, 0x8F919CFF, 0xCBC6B7FF, 0x8A6A5FFF, 0xA25F7CFF,
            0x335C93FF, 0x9A80B0FF, 0xDF89A7FF, 0xAB5E65FF, 0x48352DFF,
            0x869B92FF, 0x838D87FF, 0x9C817DFF, 0xF3BBC0FF, 0x853A60FF,
            0x478FBFFF, 0x00232DFF, 0xCFCF9FFF, 0x9FA645FF, 0x5D8115FF,
            0x81B266FF, 0xA2BB99FF, 0x3F2A28FF, 0x662B39FF, 0xB66C88FF,
            0x61627CFF, 0x213425FF, 0xD9FFB9FF, 0xABE168FF, 0xABD95EFF,
            0x465805FF, 0xF5ECCBFF, 0xC8B2ADFF, 0xA98A87FF, 0x4F2917FF,
            0xA63D4CFF, 0xAF8277FF, 0x284419FF, 0x7EB478FF, 0xCCDCA6FF,
            0xC39976FF, 0x642412FF, 0xA2816EFF, 0x878F67FF, 0x8E9852FF,
            0xC25553FF, 0xB58474FF, 0xA3B8A2FF, 0x406A63FF, 0xD7D6DFFF,
            0xEEAEB3FF, 0xB0644EFF, 0x8E713EFF, 0x708C40FF, 0x8EB553FF,
            0x767E41FF, 0x8AA66BFF, 0x9DCEA0FF, 0x55836DFF, 0xAEBCBBFF,
            0x85706FFF, 0xC0A083FF, 0x968E48FF, 0x99B54AFF, 0x54800BFF,
            0x50D83AFF, 0x84EB78FF, 0x78B96AFF, 0x26560EFF, 0xA8D198FF,
            0x405B4BFF, 0x485252FF, 0x8F9866FF, 0x84A11CFF, 0x8EC217FF
    };
#elif __linux__
    uint32_t check_data[100] = {
            0xB9D294FF, 0xB4C495FF, 0xABA899FF, 0x6A5E6AFF, 0xA294B6FF,
            0x7F7E98FF, 0x99AE9FFF, 0xE5ECD7FF, 0xE8BAC0FF, 0x884054FF,
            0xABC191FF, 0x565C3DFF, 0xE9D4D3FF, 0x86687BFF, 0x68526EFF,
            0x605B70FF, 0x35433FFF, 0x898C83FF, 0x916772FF, 0x753749FF,
            0xC0D0BFFF, 0x8D8481FF, 0xA66A88FF, 0xC17DA0FF, 0xD6B2C2FF,
            0x4C3E49FF, 0x908EA1FF, 0xC4BBD0FF, 0x816174FF, 0x916576FF,
            0x5D676EFF, 0x958D98FF, 0xBF8FA9FF, 0x925E70FF, 0x4C362BFF,
            0xA19A8BFF, 0x91888BFF, 0x8E7D8AFF, 0xD8BBCBFF, 0x694556FF,
            0x8990A4FF, 0x17202AFF, 0xBAC5BBFF, 0x839374FF, 0x5B6E3DFF,
            0x9BA872FF, 0xC1BC8BFF, 0x473314FF, 0x523233FF, 0x9B7484FF,
            0x736374FF, 0x2D2C2EFF, 0xDBF4DAFF, 0xA5CA98FF, 0xA8C784FF,
            0x46540DFF, 0xFFF2B9FF, 0xDABD91FF, 0xAB907BFF, 0x412A1BFF,
            0x7F4B3FFF, 0xA98476FF, 0x403925FF, 0xA0A883FF, 0xD5DF9DFF,
            0xACA468FF, 0x562711FF, 0xAD816AFF, 0x9B915BFF, 0x8E9950FF,
            0x8C6D3AFF, 0xA58F66FF, 0xB8B5A0FF, 0x656C51FF, 0xE2EBB3FF,
            0xCEC691FF, 0x966557FF, 0x91684FFF, 0x7E8C3AFF, 0x8FBA49FF,
            0x608F29FF, 0x83AD5FFF, 0xA6C8AAFF, 0x627F6FFF, 0xAEC9A2FF,
            0x778055FF, 0xBDA280FF, 0x988853FF, 0x8DB64DFF, 0x418704FF,
            0x74C949FF, 0x98E282FF, 0x75AB88FF, 0x1B4337FF, 0xA4C8AAFF,
            0x4F6138FF, 0x6C5C32FF, 0x9F9C58FF, 0x689F2AFF, 0x69BD2FFF
    };
#else
#error "Unmatched platform: check manually the output jpg and update results"
#endif
    uint32_t read_data[100];
    bool res;
    res = img_write("test.jpg", "jpg", 10, 10, write_data);
    ASSERT_TRUE(res);
    res = img_read8("test.jpg", "jpg", read_data);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.jpg"), 0);
    for(int i = 0; i<100; i++)
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
    uint32_t values[6];
    res = img_read8("nonexistent.png", "png", values);
    EXPECT_EQ(res, 0);
    res = img_read8(TEST_ASSETS "images/bmpaspng.png", "png", values);
    EXPECT_EQ(res, 0);
    res = img_read8(TEST_ASSETS "images/generic.png", "png", values);
    EXPECT_EQ(res, 1);
    //The input image was converted from the jpg one, so strange values are
    //inherited
    EXPECT_EQ(BGRA_RED(values[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(values[0]), 2U);
    EXPECT_EQ(BGRA_BLUE(values[0]), 2U);
    EXPECT_EQ(BGRA_ALPHA(values[0]), 255U);
    EXPECT_EQ(BGRA_RED(values[1]), 255U);
    EXPECT_EQ(BGRA_GREEN(values[1]), 250U);
    EXPECT_EQ(BGRA_BLUE(values[1]), 6U);
    EXPECT_EQ(BGRA_ALPHA(values[1]), 255U);
    EXPECT_EQ(BGRA_RED(values[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(values[2]), 255U);
    EXPECT_EQ(BGRA_BLUE(values[2]), 0U);
    EXPECT_EQ(BGRA_ALPHA(values[2]), 255U);
    EXPECT_EQ(BGRA_RED(values[3]), 14U);
    EXPECT_EQ(BGRA_GREEN(values[3]), 4U);
    EXPECT_EQ(BGRA_BLUE(values[3]), 255U);
    EXPECT_EQ(BGRA_ALPHA(values[3]), 255U);
    EXPECT_EQ(BGRA_RED(values[4]), 255U);
    EXPECT_EQ(BGRA_GREEN(values[4]), 255U);
    EXPECT_EQ(BGRA_BLUE(values[4]), 250U);
    EXPECT_EQ(BGRA_ALPHA(values[4]), 255U);
    EXPECT_EQ(BGRA_RED(values[5]), 7U);
    EXPECT_EQ(BGRA_GREEN(values[5]), 0U);
    EXPECT_EQ(BGRA_BLUE(values[5]), 0U);
    EXPECT_EQ(BGRA_ALPHA(values[5]), 255U);
}

SPECTRE_TEST(ImageIO, png_write_func)
{
    uint32_t read_data[100];
    bool res;
    res = img_write("test.png", "png", 10, 10, write_data);
    ASSERT_TRUE(res);
    res = img_read8("test.png", "png", read_data);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.png"), 0);
    for(int i = 0; i<100; i++)
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
    uint32_t data[4];
    res = img_read8("nonexistent.tiff", "tiff", data);
    EXPECT_EQ(res, 0);
    res = img_read8(TEST_ASSETS "images/bmpastif.tif", "tif", data);
    EXPECT_EQ(res, 0);
    res = img_read8(TEST_ASSETS "images/generic.tif", "tif", data);
    ASSERT_EQ(res, 1);
    EXPECT_EQ(BGRA_RED(data[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[0]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 255U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 255U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[2]), 255U);
    EXPECT_EQ(BGRA_RED(data[3]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 255U);
    res = img_read8(TEST_ASSETS "images/generic_alpha.tiff", "tiff", data);
    ASSERT_EQ(res, 1);
    EXPECT_EQ(BGRA_RED(data[0]), 255U);
    EXPECT_EQ(BGRA_GREEN(data[0]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[0]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[0]), 127U);
    EXPECT_EQ(BGRA_RED(data[1]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[1]), 255U);
    EXPECT_EQ(BGRA_BLUE(data[1]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[1]), 255U);
    EXPECT_EQ(BGRA_RED(data[2]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[2]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[2]), 255U);
    EXPECT_EQ(BGRA_ALPHA(data[2]), 0U);
    EXPECT_EQ(BGRA_RED(data[3]), 0U);
    EXPECT_EQ(BGRA_GREEN(data[3]), 0U);
    EXPECT_EQ(BGRA_BLUE(data[3]), 0U);
    EXPECT_EQ(BGRA_ALPHA(data[3]), 54U);
}

SPECTRE_TEST(ImageIO, tiff_write_func)
{
    uint32_t read_data[100];
    bool res;
    res = img_write("test.tif", "tif", 10, 10, write_data);
    ASSERT_TRUE(res);
    res = img_read8("test.tif", "tif", read_data);
    ASSERT_TRUE(res);
    EXPECT_EQ(unlink("test.tif"), 0);
    for(int i = 0; i<100; i++)
        EXPECT_EQ(read_data[i], write_data[i]);

    //non existent folder
    res = img_write("/root/nonexistent/test.tif", "tif", 10, 10, write_data);
    EXPECT_FALSE(res);
}

#endif

SPECTRE_TEST(ImageIO, BGRAtoRGB_conversion)
{
    uint32_t bgra_data[16] = {
            0xC8E323FF, 0x7CC32AFF, 0x407784FF, 0xC2303EFF, 0x9E601DFF,
            0x384DC8FF, 0xEC693EFF, 0x299D4AFF, 0xEDB0ABFF, 0x1AD062FF,
            0x0881E5FF, 0xC02831FF, 0xC7C89AFF, 0x23AF23FF, 0x1C46DCFF,
            0x19B086FF

    };
    uint8_t rgb_expected[16*3] = {
            0x23, 0xE3, 0xC8, 0x2A, 0xC3, 0x7C, 0x84, 0x77, 0x40, 0x3E, 0x30,
            0xC2, 0x1D, 0x60, 0x9E, 0xC8, 0x4D, 0x38, 0x3E, 0x69, 0xEC, 0x4A,
            0x9D, 0x29, 0xAB, 0xB0, 0xED, 0x62, 0xD0, 0x1A, 0xE5, 0x81, 0x08,
            0x31, 0x28, 0xC0, 0x9A, 0xC8, 0xC7, 0x23, 0xAF, 0x23, 0xDC, 0x46,
            0x1C, 0x86, 0xB0, 0x19
    };
    uint8_t rgb_got[16*3];
    BGRAtoRGB(rgb_got, bgra_data, 16);
    for(int i = 0; i<16*3; i++)
        EXPECT_EQ(rgb_got[i], rgb_expected[i]);
}

SPECTRE_TEST(ImageIO, RGBtoBGRA_conversion)
{
    uint8_t rgb_data[16*3] = {
            0x80, 0xC6, 0x14, 0xF0, 0xEA, 0x39, 0xD5, 0x8A, 0x19, 0x24, 0x0D,
            0x58, 0xCD, 0xC1, 0xEF, 0x8D, 0x77, 0x48, 0xF1, 0x7C, 0xD5, 0x6C,
            0x6C, 0x5B, 0x98, 0x6D, 0x11, 0xE9, 0x00, 0xA1, 0x84, 0x35, 0x52,
            0x25, 0xA3, 0x2F, 0x66, 0x3E, 0xEA, 0x32, 0x88, 0x11, 0xD0, 0x46,
            0xEB, 0xC9, 0x47, 0xF4
    };
    uint32_t bgra_expected[16] = {
            0x14C680FF, 0x39EAF0FF, 0x198AD5FF, 0x580D24FF, 0xEFC1CDFF,
            0x48778DFF, 0xD57CF1FF, 0x5B6C6CFF, 0x116D98FF, 0xA100E9FF,
            0x523584FF, 0x2FA325FF, 0xEA3E66FF, 0x118832FF, 0xEB46D0FF,
            0xF447C9FF
    };
    uint32_t bgra_got[16];
    RGBtoBGRA(bgra_got, rgb_data, 16*3);
    for(int i = 0; i<16; i++)
        EXPECT_EQ(bgra_got[i], bgra_expected[i]);
}

SPECTRE_TEST_END(ImageIO_tests)
