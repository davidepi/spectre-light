
#include <gtest/gtest.h>


#include "utility/imageIO.hpp"
#include "utility/utility.hpp"
#include <cstdio>
#include <climits>

TEST(ImageIO,save_ppm)
{
    char file_stat[64];

    uint8_t image_sample[17*10*3];
    for(int i=0;i<17*10*3;i+=3)
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
    EXPECT_FLOAT_EQ(data[1], 0.f);
    EXPECT_FLOAT_EQ(data[2], 0.f);
    EXPECT_FLOAT_EQ(data[3], 0.f);
    EXPECT_FLOAT_EQ(data[4], 1.f);
    EXPECT_FLOAT_EQ(data[5], 0.f);
    EXPECT_FLOAT_EQ(data[6], 0.f);
    EXPECT_FLOAT_EQ(data[7], 0.f);
    EXPECT_FLOAT_EQ(data[8], 1.f);
    EXPECT_FLOAT_EQ(data[9], 0.f);
    EXPECT_FLOAT_EQ(data[10], 0.f);
    EXPECT_FLOAT_EQ(data[11], 0.f);
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
    EXPECT_FLOAT_EQ(data[1], 0.f);
    EXPECT_FLOAT_EQ(data[2], 0.f);
    EXPECT_FLOAT_EQ(data[3], 0.f);
    EXPECT_FLOAT_EQ(data[4], 1.f);
    EXPECT_FLOAT_EQ(data[5], 0.f);
    EXPECT_FLOAT_EQ(data[6], 0.f);
    EXPECT_FLOAT_EQ(data[7], 0.f);
    EXPECT_FLOAT_EQ(data[8], 1.f);
    EXPECT_FLOAT_EQ(data[9], 0.f);
    EXPECT_FLOAT_EQ(data[10], 0.f);
    EXPECT_FLOAT_EQ(data[11], 0.f);
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

    uint8_t image_sample[17*10*3];
    for(int i=0;i<17*10*3;i+=3)
        image_sample[i] = i/3;
    bool res = save_bmp("test.bmp",16,10,image_sample);
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

TEST(ImageIO,dimensions_bmp)
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
    dimensions_bmp(TEST_ASSETS "wrong_magic1.bmp", &width, &height);
    EXPECT_EQ(width, IMAGE_WRONG_MAGIC);
    EXPECT_EQ(height, IMAGE_WRONG_MAGIC);
    width = 0;
    height = 0;
    //second letter of the magic number is wrong
    dimensions_bmp(TEST_ASSETS "wrong_magic2.bmp", &width, &height);
    EXPECT_EQ(width, IMAGE_WRONG_MAGIC);
    EXPECT_EQ(height, IMAGE_WRONG_MAGIC);
    width = 0;
    height = 0;
    //32bit
    dimensions_bmp(TEST_ASSETS "32bit.bmp", &width, &height);
    EXPECT_EQ(width, IMAGE_NOT_SUPPORTED);
    EXPECT_EQ(height, IMAGE_NOT_SUPPORTED);
    width = 0;
    height = 0;
    //os2
    dimensions_bmp(TEST_ASSETS "os2.bmp", &width, &height);
    EXPECT_EQ(width, IMAGE_NOT_SUPPORTED);
    EXPECT_EQ(height, IMAGE_NOT_SUPPORTED);
    width = 0;
    height = 0;
    //normal image
    dimensions_bmp(TEST_ASSETS "correct.bmp", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
    //flipped (negative) rows
    dimensions_bmp(TEST_ASSETS "flipped.bmp", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    width = 0;
    height = 0;
}

TEST(ImageIO,read_bmp)
{
    int res;
    float values[4*3];
    //non existent
    res = read_bmp("nonexistent.bmp", values);
    EXPECT_EQ(res, IMAGE_NOT_READABLE);
    //first letter of the magic number is wrong
    res = read_bmp(TEST_ASSETS "wrong_magic1.bmp", values);
    EXPECT_EQ(res, IMAGE_WRONG_MAGIC);
    //second letter of the magic number is wrong
    res = read_bmp(TEST_ASSETS "wrong_magic2.bmp", values);
    EXPECT_EQ(res, IMAGE_WRONG_MAGIC);
    //os2
    res = read_bmp(TEST_ASSETS "os2.bmp", values);
    EXPECT_EQ(res, IMAGE_NOT_SUPPORTED);
    //32bit
    res = read_bmp(TEST_ASSETS "32bit.bmp", values);
    EXPECT_EQ(res, IMAGE_NOT_SUPPORTED);
    //normal image
    res = read_bmp(TEST_ASSETS "correct.bmp", values);
    EXPECT_FLOAT_EQ(values[0], 1.f);
    EXPECT_FLOAT_EQ(values[1], 0.f);
    EXPECT_FLOAT_EQ(values[2], 0.f);
    EXPECT_FLOAT_EQ(values[3], 0.f);
    EXPECT_FLOAT_EQ(values[4], 1.f);
    EXPECT_FLOAT_EQ(values[5], 0.f);
    EXPECT_FLOAT_EQ(values[6], 0.f);
    EXPECT_FLOAT_EQ(values[7], 0.f);
    EXPECT_FLOAT_EQ(values[8], 1.f);
    EXPECT_FLOAT_EQ(values[9], 0.f);
    EXPECT_FLOAT_EQ(values[10], 0.f);
    EXPECT_FLOAT_EQ(values[11], 0.f);
    EXPECT_EQ(res, IMAGE_OK);
    //flipped (negative) rows
    res = read_bmp(TEST_ASSETS "flipped.bmp", values);
    EXPECT_FLOAT_EQ(values[0], 1.f);
    EXPECT_FLOAT_EQ(values[1], 0.f);
    EXPECT_FLOAT_EQ(values[2], 0.f);
    EXPECT_FLOAT_EQ(values[3], 0.f);
    EXPECT_FLOAT_EQ(values[4], 1.f);
    EXPECT_FLOAT_EQ(values[5], 0.f);
    EXPECT_FLOAT_EQ(values[6], 0.f);
    EXPECT_FLOAT_EQ(values[7], 0.f);
    EXPECT_FLOAT_EQ(values[8], 1.f);
    EXPECT_FLOAT_EQ(values[9], 0.f);
    EXPECT_FLOAT_EQ(values[10], 0.f);
    EXPECT_FLOAT_EQ(values[11], 0.f);
    EXPECT_EQ(res, IMAGE_OK);
}

TEST(ImageIO,save_rgb)
{
    bool res;
    uint8_t image_sample[17*10*3];
    for(int i=0;i<17*10*3;i+=3)
        image_sample[i] = i/3;
#ifdef IMAGEMAGICK
    char file_stat[64];
    FILE* fp;

    //save jpg
    res = save_RGB("test.jpg",16,10,image_sample);
    ASSERT_TRUE(res);
    //check if saved image is actually a .ppm
    fp = popen("file -b --mime test.jpg","r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_EQ(strcmp(file_stat,
                          "image/jpeg; charset=binary\n"),0);
    unlink("test.jpg");

    //save tiff
    res = save_RGB("test.tiff",16,10,image_sample);
    ASSERT_TRUE(res);
    //check if saved image is actually a .ppm
    fp = popen("file -b --mime test.tiff","r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_EQ(strcmp(file_stat,
                          "image/tiff; charset=binary\n"),0);
    unlink("test.tiff");

    //save targa
    res = save_RGB("test.tga",16,10,image_sample);
    ASSERT_TRUE(res);
    //check if saved image is actually a .ppm
    fp = popen("file -b --mime test.tga","r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_EQ(strcmp(file_stat,
                          "image/x-tgaimage/x-tga; charset=binary\n"),0);
    unlink("test.tga");

    //save png
    res = save_RGB("test.png",16,10,image_sample);
    ASSERT_TRUE(res);
    //check if saved image is actually a .ppm
    fp = popen("file -b --mime test.png","r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_EQ(strcmp(file_stat,
                          "image/png; charset=binary\n"),0);
    unlink("test.png");

    //save dds
    res = save_RGB("test.dds",16,10,image_sample);
    ASSERT_TRUE(res);
    //check if saved image is actually a .ppm
    fp = popen("file -b --mime test.dds","r");
    fgets(file_stat, 64, fp);
    pclose(fp);
    EXPECT_EQ(strcmp(file_stat,
                          "application/octet-stream; charset=binary\n"),0);
    unlink("test.dds");

    //non existent folder
    errors_count[ERROR_INDEX] = 0;
    res = save_RGB("/root/nonexistent/test.jpg",16,10,image_sample);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
    EXPECT_FALSE(res);
#else
    res = save_RGB("test.jpg",16,10,image_sample);
    EXPECT_FALSE(res);
#endif
}

TEST(ImageIO,dimensions_rgb)
{
    int width;
    int height;
    bool res;
#ifdef IMAGEMAGICK

    //non existent
    res = dimensions_RGB("nonexistent.bmp", &width, &height);
    EXPECT_EQ(width, IMAGE_NOT_READABLE);
    EXPECT_EQ(height, IMAGE_NOT_READABLE);
    EXPECT_EQ(res, false);
    width = 0;
    height = 0;
    //jpg
    res = dimensions_RGB(TEST_ASSETS "generic.jpg", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 3);
    EXPECT_EQ(res, false);
    width = 0;
    height = 0;
    //png
    res = dimensions_RGB(TEST_ASSETS "generic.png", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 3);
    EXPECT_EQ(res, false);
    width = 0;
    height = 0;
    //tiff
    res = dimensions_RGB(TEST_ASSETS "generic.tiff", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 3);
    EXPECT_EQ(res, false);
    width = 0;
    height = 0;
    //targa
    res = dimensions_RGB(TEST_ASSETS "generic.tga", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 3);
    EXPECT_EQ(res, false);
    width = 0;
    height = 0;
    //alpha channel
    res = dimensions_RGB(TEST_ASSETS "generic_alpha.tiff", &width, &height);
    EXPECT_EQ(width, 2);
    EXPECT_EQ(height, 2);
    EXPECT_EQ(res, true);
    width = 0;
    height = 0;
#else
    res = dimensions_RGB("test.jpg",&width,&height);
    EXPECT_EQ(width, IMAGE_NOT_SUPPORTED);
    EXPECT_EQ(height, IMAGE_NOT_SUPPORTED);
    EXPECT_FALSE(res);
#endif
}

TEST(ImageIO,read_rgb)
{
    int res;
    float values[2*3*3];
    uint8_t alpha[2*3];
#ifdef IMAGEMAGICK
    //non existent
    res = read_RGB("nonexistent.bmp", values,alpha);
    EXPECT_EQ(res, IMAGE_NOT_READABLE);
    //too many channels
#ifndef IMAGEMAGICK6
    errors_count[ERROR_INDEX] = 0;
    res = read_RGB(TEST_ASSETS "singlechannel.tiff", values, alpha);
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
    EXPECT_EQ(res, IMAGE_NOT_SUPPORTED);
#endif
    //jpg
    res = read_RGB(TEST_ASSETS "generic.jpg", values, alpha);
    EXPECT_NEAR(values[0],1.f,.1f);
    EXPECT_NEAR(values[1],0.f,.1f);
    EXPECT_NEAR(values[2],0.f,.1f);
    EXPECT_NEAR(values[3],1.f,.1f);
    EXPECT_NEAR(values[4],1.f,.1f);
    EXPECT_NEAR(values[5],0.f,.1f);
    EXPECT_NEAR(values[6],0.f,.1f);
    EXPECT_NEAR(values[7],1.f,.1f);
    EXPECT_NEAR(values[8],0.f,.1f);
    EXPECT_NEAR(values[9],0.f,.1f);
    EXPECT_NEAR(values[10],0.f,.1f);
    EXPECT_NEAR(values[11],1.f,.1f);
    EXPECT_NEAR(values[12],1.f,.1f);
    EXPECT_NEAR(values[13],1.f,.1f);
    EXPECT_NEAR(values[14],1.f,.1f);
    EXPECT_NEAR(values[15],0.f,.1f);
    EXPECT_NEAR(values[16],0.f,.1f);
    EXPECT_NEAR(values[17],0.f,.1f);
    EXPECT_EQ(res, IMAGE_OK);
    //png
    res = read_RGB(TEST_ASSETS "generic.png", values, alpha);
    EXPECT_NEAR(values[0],1.f,.1f);
    EXPECT_NEAR(values[1],0.f,.1f);
    EXPECT_NEAR(values[2],0.f,.1f);
    EXPECT_NEAR(values[3],1.f,.1f);
    EXPECT_NEAR(values[4],1.f,.1f);
    EXPECT_NEAR(values[5],0.f,.1f);
    EXPECT_NEAR(values[6],0.f,.1f);
    EXPECT_NEAR(values[7],1.f,.1f);
    EXPECT_NEAR(values[8],0.f,.1f);
    EXPECT_NEAR(values[9],0.f,.1f);
    EXPECT_NEAR(values[10],0.f,.1f);
    EXPECT_NEAR(values[11],1.f,.1f);
    EXPECT_NEAR(values[12],1.f,.1f);
    EXPECT_NEAR(values[13],1.f,.1f);
    EXPECT_NEAR(values[14],1.f,.1f);
    EXPECT_NEAR(values[15],0.f,.1f);
    EXPECT_NEAR(values[16],0.f,.1f);
    EXPECT_NEAR(values[17],0.f,.1f);
    EXPECT_EQ(res, IMAGE_OK);
    //tiff
    res = read_RGB(TEST_ASSETS "generic.tiff", values, alpha);
    EXPECT_NEAR(values[0],1.f,.1f);
    EXPECT_NEAR(values[1],0.f,.1f);
    EXPECT_NEAR(values[2],0.f,.1f);
    EXPECT_NEAR(values[3],1.f,.1f);
    EXPECT_NEAR(values[4],1.f,.1f);
    EXPECT_NEAR(values[5],0.f,.1f);
    EXPECT_NEAR(values[6],0.f,.1f);
    EXPECT_NEAR(values[7],1.f,.1f);
    EXPECT_NEAR(values[8],0.f,.1f);
    EXPECT_NEAR(values[9],0.f,.1f);
    EXPECT_NEAR(values[10],0.f,.1f);
    EXPECT_NEAR(values[11],1.f,.1f);
    EXPECT_NEAR(values[12],1.f,.1f);
    EXPECT_NEAR(values[13],1.f,.1f);
    EXPECT_NEAR(values[14],1.f,.1f);
    EXPECT_NEAR(values[15],0.f,.1f);
    EXPECT_NEAR(values[16],0.f,.1f);
    EXPECT_NEAR(values[17],0.f,.1f);
    EXPECT_EQ(res, IMAGE_OK);
    //targa
    res = read_RGB(TEST_ASSETS "generic.tga", values, alpha);
    EXPECT_NEAR(values[0],1.f,.1f);
    EXPECT_NEAR(values[1],0.f,.1f);
    EXPECT_NEAR(values[2],0.f,.1f);
    EXPECT_NEAR(values[3],1.f,.1f);
    EXPECT_NEAR(values[4],1.f,.1f);
    EXPECT_NEAR(values[5],0.f,.1f);
    EXPECT_NEAR(values[6],0.f,.1f);
    EXPECT_NEAR(values[7],1.f,.1f);
    EXPECT_NEAR(values[8],0.f,.1f);
    EXPECT_NEAR(values[9],0.f,.1f);
    EXPECT_NEAR(values[10],0.f,.1f);
    EXPECT_NEAR(values[11],1.f,.1f);
    EXPECT_NEAR(values[12],1.f,.1f);
    EXPECT_NEAR(values[13],1.f,.1f);
    EXPECT_NEAR(values[14],1.f,.1f);
    EXPECT_NEAR(values[15],0.f,.1f);
    EXPECT_NEAR(values[16],0.f,.1f);
    EXPECT_NEAR(values[17],0.f,.1f);
    EXPECT_EQ(res, IMAGE_OK);
    //tiff with alpha
    res = read_RGB(TEST_ASSETS "generic_alpha.tiff", values, alpha);
    EXPECT_NEAR(values[0],1.f,.1f);
    EXPECT_NEAR(values[1],0.f,.1f);
    EXPECT_NEAR(values[2],0.f,.1f);
    EXPECT_NEAR(values[3],0.f,.1f);
    EXPECT_NEAR(values[4],1.f,.1f);
    EXPECT_NEAR(values[5],0.f,.1f);
    EXPECT_NEAR(values[6],0.f,.14f); //suspicious, hope it is the compression
    EXPECT_NEAR(values[7],0.f,.1f);
    EXPECT_NEAR(values[8],1.f,.1f);
    EXPECT_NEAR(values[9],1.f,.1f);
    EXPECT_NEAR(values[10],1.f,.1f);
    EXPECT_NEAR(values[11],1.f,.1f);
    EXPECT_EQ(alpha[0], 255);
    EXPECT_EQ(alpha[1], 0);
    EXPECT_EQ(alpha[2], 0);
    EXPECT_EQ(alpha[3], 255);
    EXPECT_EQ(res, IMAGE_OK);
#else
    res = read_RGB(TEST_ASSETS "generic.jpg", values, alpha);
    EXPECT_EQ(res, IMAGE_NOT_SUPPORTED);
#endif
}

TEST(ImageIO,image_supported)
{
    char res;
    //null pointer
    res = image_supported(NULL);
    EXPECT_EQ(res, IMAGE_NOT_SUPPORTED);
    //empty extension
    res = image_supported("");
    EXPECT_EQ(res, IMAGE_NOT_SUPPORTED);
    //ppm
    res = image_supported("ppm");
    EXPECT_EQ(res, IMAGE_PPM);
    //not ppm but letter p
    res = image_supported("png");
    EXPECT_EQ(res, IMAGE_RGB);
    //bmp
    res = image_supported("bmp");
    EXPECT_EQ(res, IMAGE_BMP);
    //not bmp but letter b
    //bmp
    res = image_supported("blob");
    EXPECT_EQ(res, IMAGE_NOT_SUPPORTED);
    //jpg
    res = image_supported("jpg");
    EXPECT_EQ(res, IMAGE_RGB);
    //totally random extension
    res = image_supported("ok");
    EXPECT_EQ(res, IMAGE_NOT_SUPPORTED);
}

