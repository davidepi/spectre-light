#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else
#include <gtest/gtest.h>
#endif

#include "utility/console.hpp"
#include "utility/utility.hpp"
#include <climits>

SPECTRE_TEST_INIT(Consolet_tests)

//tests are named Consolet instead of Console to avoid triggering
//the Console::instance() define

SPECTRE_TEST(Consolet, constructor_motd)
{
    //just for coverage, changes here are pretty evident
    Console;
}

SPECTRE_TEST(Consolet, log)
{
    errors_count[LOG_INDEX] = 0;
    Console.log("test", NULL);
    EXPECT_EQ(errors_count[LOG_INDEX], 1);
    errors_count[LOG_INDEX] = 0;

    errors_count[LOG_INDEX] = 0;
    Console.log("test", "test verbose");
    EXPECT_EQ(errors_count[LOG_INDEX], 1);
    errors_count[LOG_INDEX] = 0;
}

SPECTRE_TEST(Consolet, notice)
{
    errors_count[NOTICE_INDEX] = 0;
    Console.notice("test");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
}

SPECTRE_TEST(Consolet, notice_vargs)
{
    errors_count[NOTICE_INDEX] = 0;
    Console.notice("test #%d %s", 1, "ok");
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
}

SPECTRE_TEST(Consolet, warning)
{
    errors_count[WARNING_INDEX] = 0;
    Console.warning("test");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
}

SPECTRE_TEST(Consolet, warning_vargs)
{
    errors_count[WARNING_INDEX] = 0;
    Console.warning("test #%d %s", 1, "ok");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
}

SPECTRE_TEST(Consolet, severe)
{
    errors_count[ERROR_INDEX] = 0;
    Console.severe("test");
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(Consolet, severe_vargs)
{
    errors_count[ERROR_INDEX] = 0;
    Console.severe("test #%d %s", 1, "ok");
    EXPECT_EQ(errors_count[ERROR_INDEX], 1);
    errors_count[ERROR_INDEX] = 0;
}

SPECTRE_TEST(Consolet, critical)
{
    errors_count[CRITICAL_INDEX] = 0;
    Console.critical("test");
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

SPECTRE_TEST(Consolet, critical_vargs)
{
    errors_count[CRITICAL_INDEX] = 0;
    Console.critical("test #%d %s", 1, "ok");
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
}

SPECTRE_TEST(Consolet, progress_bar)
{
    //just for coverage, changes here are pretty evident
    Console.progress_bar(0.5,300);
    printf("\n");
    EXPECT_TRUE(true);
}

SPECTRE_TEST(Consolet, progress_bar_done)
{
    //just for coverage, changes here are pretty evident
    Console.progress_bar_done();
    EXPECT_TRUE(true);
}

SPECTRE_TEST_END(Consolet_tests)
