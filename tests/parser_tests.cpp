
#include <gtest/gtest.h>


#include "parsers/config_driver.hpp"
#include "renderer.hpp"

TEST(Parser,out)
{
    //set
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/out.txt");
    EXPECT_EQ(strcmp(driver0.output.c_str(),"filename.jpg"),0);
    delete r0;
    //default
    ConfigDriver driver1;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/resolution_ok.txt");
    EXPECT_EQ(strcmp(driver1.output.c_str(),"out.ppm"),0);
    delete r1;
}

TEST(Parser,resolution)
{
    //resolution ok
    ConfigDriver driver0;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver0.width, 1920);
    EXPECT_EQ(driver0.height, 1080);
    delete r0;
    //resolution default
    ConfigDriver driver1;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/out.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver1.width, 800);
    EXPECT_EQ(driver1.height, 600);
    delete r1;
    //not multiple of 32, but height even
    ConfigDriver driver2;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/resolution_even.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver2.width, 6016);
    EXPECT_EQ(driver2.height, 3008);
    delete r2;
    //not multiple of 32, but height odd
    ConfigDriver driver3;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/resolution_odd.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver3.width, 1952);
    EXPECT_EQ(driver3.height, 1098);
    delete r3;
}

TEST(Parser,sampler)
{
    //unset
    ConfigDriver driver0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt");
    EXPECT_EQ(driver0.sampler_type, SPECTRE_SAMPLER_STRATIFIED);
    delete r0;
    //stratified
    ConfigDriver driver1;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/sampler_stratified.txt");
    EXPECT_EQ(driver1.sampler_type, SPECTRE_SAMPLER_STRATIFIED);
    delete r1;
    //random
    ConfigDriver driver2;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/sampler_random.txt");
    EXPECT_EQ(driver2.sampler_type, SPECTRE_SAMPLER_RANDOM);
    delete r2;
}

TEST(Parser,spp)
{
    //unset
    ConfigDriver driver0;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r0 = driver0.parse(TEST_ASSETS "parser/resolution_ok.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver0.spp, 121);
    delete r0;
    //perfect_square
    ConfigDriver driver1;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r1 = driver1.parse(TEST_ASSETS "parser/spp_perfect_square.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver1.spp, 900);
    delete r1;
    //round up
    ConfigDriver driver2;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r2 = driver2.parse(TEST_ASSETS "parser/spp_change_ceil.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver2.spp, 36);
    delete r2;
    //round down
    ConfigDriver driver3;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r3 = driver3.parse(TEST_ASSETS "parser/spp_change_floor.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver3.spp, 36);
    delete r3;
    //random sampler, not rounding
    ConfigDriver driver4;
    errors_count[NOTICE_INDEX] = 0;
    Renderer* r4 = driver4.parse(TEST_ASSETS "parser/spp_random.txt");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 0);
    errors_count[NOTICE_INDEX] = 0;
    EXPECT_EQ(driver4.spp, 122);
    delete r4;
}

