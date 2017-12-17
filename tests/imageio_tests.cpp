
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
    FILE* fp = popen("file test.ppm","r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_EQ(strcmp(file_stat,
                          "test.ppm: Netpbm image data, size = 16 x 10, "\
                          "rawbits, pixmap\n"),0);
    unlink("test.ppm");

    //non existent folder
    res = save_ppm("/root/nonexistent/test.ppm",16,10,image_sample);
    EXPECT_FALSE(res);
}

TEST(ImageIO,save_bmp)
{
    char file_stat[64];

    uint8_t image_sample[18*15*3];
    for(int i=0;i<18*15*3;i+=3)
        image_sample[i] = i/3;
    bool res = save_ppm("test.bmp",18,15,image_sample);
    ASSERT_TRUE(res);

    //check if saved image is actually a .ppm
    FILE* fp = popen("file test.bmp","r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_EQ(strcmp(file_stat,
                          "test.bmp: Netpbm image data, size = 18 x 15, "\
                          "rawbits, pixmap\n"),0);
    unlink("test.bmp");

    //non existent folder
    res = save_ppm("/root/nonexistent/test.bmp",16,10,image_sample);
    EXPECT_FALSE(res);
}

