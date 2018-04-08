
#include <gtest/gtest.h>


#include "utility/console.hpp"
#include "utility/utility.hpp"
#include <climits>

//tests are named Consolet instead of Console to avoid triggering
//the Console::getInstance() define

TEST(Consolet,constructor_motd)
{
    //just for coverage, changes here are pretty evident
    Console;
}

TEST(Consolet,log)
{
    errors_count[LOG_INDEX] = 0;
    Console.log("test",NULL);
    EXPECT_EQ(errors_count[LOG_INDEX], 1);
    errors_count[LOG_INDEX] = 0;

    errors_count[LOG_INDEX] = 0;
    Console.log("test","test verbose");
    EXPECT_EQ(errors_count[LOG_INDEX], 1);
    errors_count[LOG_INDEX] = 0;
}

TEST(Consolet,notice)
{
    errors_count[NOTICE_INDEX] = 0;
    Console.notice("test");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
}

TEST(Consolet,notice_vargs)
{
    errors_count[NOTICE_INDEX] = 0;
    Console.notice("test #%d %s",1,"ok");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
}

TEST(Consolet,warning)
{
    errors_count[WARNING_INDEX] = 0;
    Console.warning("test");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
}

TEST(Consolet,warning_vargs)
{
    errors_count[WARNING_INDEX] = 0;
    Console.warning("test #%d %s",1,"ok");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
}

TEST(Consolet,severe)
{
    errors_count[ERROR_INDEX] = 0;
    Console.severe("test");
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
}

TEST(Consolet,severe_vargs)
{
    errors_count[ERROR_INDEX] = 0;
    Console.severe("test #%d %s",1,"ok");
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
}

TEST(Consolet,critical)
{
    errors_count[CRITICAL_INDEX] = 0;
    Console.critical("test");
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Consolet,critical_vargs)
{
    errors_count[CRITICAL_INDEX] = 0;
    Console.critical("test #%d %s",1,"ok");
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

TEST(Consolet,progress_bar)
{
    //just for coverage, changes here are pretty evident
    Console.progress_bar(0.5,300);
}

TEST(Consolet,progress_bar_done)
{
    //just for coverage, changes here are pretty evident
    Console.progress_bar_done();
}

