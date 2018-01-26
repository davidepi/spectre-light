
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

TEST(ImageIO,size_ppm)
{
    int width;
    int height;
    size_ppm("nonexistent.ppm", &width, &height);
    EXPECT_EQ(width, IMAGE_NOT_READABLE);
    EXPECT_EQ(height, IMAGE_NOT_READABLE);
    width = 0;
    height = 0;
    size_ppm(TEST_ASSETS "wrong_magic1.ppm", &width, &height);
    EXPECT_EQ(width, IMAGE_WRONG_MAGIC);
    EXPECT_EQ(height, IMAGE_WRONG_MAGIC);
    width = 0;
    height = 0;
    size_ppm(TEST_ASSETS "wrong_magic2.ppm", &width, &height);
    EXPECT_EQ(width, IMAGE_WRONG_MAGIC);
    EXPECT_EQ(height, IMAGE_WRONG_MAGIC);
    width = 0;
    height = 0;
    size_ppm(TEST_ASSETS "multiple_spaces.ppm", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
    size_ppm(TEST_ASSETS "binary.ppm", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
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

