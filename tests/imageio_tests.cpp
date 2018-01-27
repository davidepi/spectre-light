
#include <gtest/gtest.h>


#include "utility/imageIO.hpp"
#include "utility/utility.hpp"
#include <cstdio>
#include <climits>

TEST(ImageIO,save_ppm)
{
    char file_stat[64];

    uint8_t image_sample[16*10*3];
    for(int i=0;i<16*10*3;i+=3)
        image_sample[i] = i/3;
    bool res = save_ppm("test.ppm",16,10,image_sample);
    ASSERT_TRUE(res);

    //check if saved image is actually a .ppm
    FILE* fp = popen("file -b --mime test.ppm","r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_EQ(strcmp(file_stat,
                          "image/x-portable-pixmap; charset=binary\n"),0);
    unlink("test.ppm");

    //non existent folder
    res = save_ppm("/root/nonexistent/test.ppm",16,10,image_sample);
    EXPECT_FALSE(res);
}

TEST(ImageIO,dimensions_ppm)
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
    dimensions_ppm(TEST_ASSETS "wrong_magic1.ppm", &width, &height);
    EXPECT_EQ(width, IMAGE_WRONG_MAGIC);
    EXPECT_EQ(height, IMAGE_WRONG_MAGIC);
    width = 0;
    height = 0;
    //second letter of the magic number is wrong
    dimensions_ppm(TEST_ASSETS "wrong_magic2.ppm", &width, &height);
    EXPECT_EQ(width, IMAGE_WRONG_MAGIC);
    EXPECT_EQ(height, IMAGE_WRONG_MAGIC);
    width = 0;
    height = 0;
    //multiple spaces in the image
    dimensions_ppm(TEST_ASSETS "multiple_spaces.ppm", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
    //binary image
    dimensions_ppm(TEST_ASSETS "binary.ppm", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
}

TEST(ImageIO,read_ppm)
{
    int res;
    //+1 is used later to check stack overflows
    float data[4*3+1];
    //non existent
    res = read_ppm("nonexistent.ppm", data);
    EXPECT_EQ(res, IMAGE_NOT_READABLE);
    //first letter of the magic number is wrong
    res = read_ppm(TEST_ASSETS "wrong_magic1.ppm", data);
    EXPECT_EQ(res, IMAGE_WRONG_MAGIC);
    //second letter of the magic number is wrong
    res = read_ppm(TEST_ASSETS "wrong_magic2.ppm", data);
    EXPECT_EQ(res, IMAGE_WRONG_MAGIC);
    //read image with normal depth (ASCII)
    res = read_ppm(TEST_ASSETS "multiple_spaces.ppm", data);
    EXPECT_FLOAT_EQ(data[0], 1.f);
    EXPECT_FLOAT_EQ(data[1], 1.f);
    EXPECT_FLOAT_EQ(data[2], 1.f);
    EXPECT_FLOAT_EQ(data[3], 0.f);
    EXPECT_FLOAT_EQ(data[4], 0.f);
    EXPECT_FLOAT_EQ(data[5], 0.f);
    EXPECT_FLOAT_EQ(data[6], 0.f);
    EXPECT_FLOAT_EQ(data[7], 0.f);
    EXPECT_FLOAT_EQ(data[8], 0.f);
    EXPECT_FLOAT_EQ(data[9], 1.f);
    EXPECT_FLOAT_EQ(data[10], 1.f);
    EXPECT_FLOAT_EQ(data[11], 1.f);
    EXPECT_EQ(res,IMAGE_OK);
    bzero(data,12);
    //read image with high depth (ASCII)
    res = read_ppm(TEST_ASSETS "p3_high_depth.ppm", data);
    EXPECT_FLOAT_EQ(data[0], 1.f);
    EXPECT_FLOAT_EQ(data[1], 1.f);
    EXPECT_FLOAT_EQ(data[2], 1.f);
    EXPECT_FLOAT_EQ(data[3], 0.f);
    EXPECT_FLOAT_EQ(data[4], 0.f);
    EXPECT_FLOAT_EQ(data[5], 0.f);
    EXPECT_FLOAT_EQ(data[6], 0.f);
    EXPECT_FLOAT_EQ(data[7], 0.f);
    EXPECT_FLOAT_EQ(data[8], 0.f);
    EXPECT_FLOAT_EQ(data[9], 1.f);
    EXPECT_FLOAT_EQ(data[10], 1.f);
    EXPECT_FLOAT_EQ(data[11], 1.f);
    EXPECT_EQ(res,IMAGE_OK);
    bzero(data,12);
    //read image with normal depth (binary) no stack_overflow
    res = read_ppm(TEST_ASSETS "binary.ppm", data);
    EXPECT_FLOAT_EQ(data[0], 1.f);
    EXPECT_FLOAT_EQ(data[1], 1.f);
    EXPECT_FLOAT_EQ(data[2], 1.f);
    EXPECT_FLOAT_EQ(data[3], 0.f);
    EXPECT_FLOAT_EQ(data[4], 0.f);
    EXPECT_FLOAT_EQ(data[5], 0.f);
    EXPECT_FLOAT_EQ(data[6], 0.f);
    EXPECT_FLOAT_EQ(data[7], 0.f);
    EXPECT_FLOAT_EQ(data[8], 0.f);
    EXPECT_FLOAT_EQ(data[9], 1.f);
    EXPECT_FLOAT_EQ(data[10], 1.f);
    EXPECT_FLOAT_EQ(data[11], 1.f);
    EXPECT_EQ(res,IMAGE_OK);
    bzero(data,12);
    //read image that claims to be 2x2 but contains a lot more
    //bytes
    data[4*3] = (float)0x2B; //random val, check that this is unchanged
    res = read_ppm(TEST_ASSETS "binary_stackoverflow.ppm", data);
    EXPECT_FLOAT_EQ(data[0], 1.f);
    EXPECT_FLOAT_EQ(data[1], 1.f);
    EXPECT_FLOAT_EQ(data[2], 1.f);
    EXPECT_FLOAT_EQ(data[3], 0.f);
    EXPECT_FLOAT_EQ(data[4], 0.f);
    EXPECT_FLOAT_EQ(data[5], 0.f);
    EXPECT_FLOAT_EQ(data[6], 0.f);
    EXPECT_FLOAT_EQ(data[7], 0.f);
    EXPECT_FLOAT_EQ(data[8], 0.f);
    EXPECT_FLOAT_EQ(data[9], 1.f);
    EXPECT_FLOAT_EQ(data[10], 1.f);
    EXPECT_FLOAT_EQ(data[11], 1.f);
    EXPECT_FLOAT_EQ(data[12], (float)0x2B); //assert no stack overflow
    EXPECT_EQ(res,IMAGE_OK);
    bzero(data,12);
    //read image with high depth (binary) no stack_overflow
    res = read_ppm(TEST_ASSETS "p6_high_depth.ppm", data);
    EXPECT_FLOAT_EQ(data[0], 1.f);
    EXPECT_FLOAT_EQ(data[1], 1.f);
    EXPECT_FLOAT_EQ(data[2], 1.f);
    EXPECT_FLOAT_EQ(data[3], 0.f);
    EXPECT_FLOAT_EQ(data[4], 0.f);
    EXPECT_FLOAT_EQ(data[5], 0.f);
    EXPECT_FLOAT_EQ(data[6], 0.f);
    EXPECT_FLOAT_EQ(data[7], 0.f);
    EXPECT_FLOAT_EQ(data[8], 0.f);
    EXPECT_FLOAT_EQ(data[9], 1.f);
    EXPECT_FLOAT_EQ(data[10], 1.f);
    EXPECT_FLOAT_EQ(data[11], 1.f);
    EXPECT_EQ(res,IMAGE_OK);
    bzero(data,12);
    //read image with high depth (binary), stack_overflow
    res = read_ppm(TEST_ASSETS "p6_high_depth_stack_overflow.ppm", data);
    EXPECT_FLOAT_EQ(data[0], 1.f);
    EXPECT_FLOAT_EQ(data[1], 1.f);
    EXPECT_FLOAT_EQ(data[2], 1.f);
    EXPECT_FLOAT_EQ(data[3], 0.f);
    EXPECT_FLOAT_EQ(data[4], 0.f);
    EXPECT_FLOAT_EQ(data[5], 0.f);
    EXPECT_FLOAT_EQ(data[6], 0.f);
    EXPECT_FLOAT_EQ(data[7], 0.f);
    EXPECT_FLOAT_EQ(data[8], 0.f);
    EXPECT_FLOAT_EQ(data[9], 1.f);
    EXPECT_FLOAT_EQ(data[10], 1.f);
    EXPECT_FLOAT_EQ(data[11], 1.f);
    EXPECT_FLOAT_EQ(data[12], (float)0x2B); //assert no stack overflow
    EXPECT_EQ(res,IMAGE_OK);
    bzero(data,12);
}

TEST(ImageIO,save_bmp)
{
    char file_stat[64];

    uint8_t image_sample[18*15*3];
    for(int i=0;i<18*15*3;i+=3)
        image_sample[i] = i/3;
    bool res = save_bmp("test.bmp",18,15,image_sample);
    ASSERT_TRUE(res);

    //check if saved image is actually a .ppm
    FILE* fp = popen("file -b --mime test.bmp","r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_EQ(strcmp(file_stat,
                          "image/x-ms-bmp; charset=binary\n"),0);
    unlink("test.bmp");

    //non existent folder
    res = save_bmp("/root/nonexistent/test.bmp",16,10,image_sample);
    EXPECT_FALSE(res);
}

