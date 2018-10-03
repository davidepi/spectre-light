#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else
#include <gtest/gtest.h>
#endif

#include <ctime>
#include "utility/date.hpp"

SPECTRE_TEST_INIT(Date_tests)

SPECTRE_TEST(Date, unix_timestamp)
{
    //now
    Date d1;
    time_t now = time(NULL);
    EXPECT_EQ((uint64_t)d1.unix_timestamp(), (uint64_t)now);

    //given date
    Date d2(2018, 10, 3, 15, 5, 40);
    EXPECT_EQ((uint64_t)d2.unix_timestamp(), (uint64_t)1538579140);

    //prior to 1970
    Date d3(1936, 9, 6, 12, 30, 15);
    EXPECT_EQ((uint64_t)d3.unix_timestamp(), (uint64_t)0);
}

SPECTRE_TEST(Date, constructor_given)
{
    //correct
    Date d1(2000,1,1,0,0,0);
    EXPECT_EQ((uint64_t)d1.unix_timestamp(), (uint64_t)946684800);

    //wrong year
    Date d2(-10000,1,1,0,0,0);
    EXPECT_EQ((uint64_t)d2.unix_timestamp(), (uint64_t)0);

    //wrong month
    Date d3(2000,13,1,0,0,0);
    EXPECT_EQ((uint64_t)d3.unix_timestamp(), (uint64_t)975628800);

    //wrong day of the month (Feb, 30), but leap year
    Date d4(2020,2,30,0,0,0);
    EXPECT_EQ((uint64_t)d4.unix_timestamp(), (uint64_t)1582934400);

    //wrong day of the month (Feb, 30) but not leap year
    Date d5(2019, 2, 30, 0, 0, 0);
    EXPECT_EQ((uint64_t)d5.unix_timestamp(), (uint64_t)1551312000);

    //leap year
    Date d6(2020, 2, 29, 0 ,0,0);
    EXPECT_EQ((uint64_t)d6.unix_timestamp(), (uint64_t)1582934400);

    //non leap year, wrong day
    Date d7(2019, 2, 29, 0, 0, 0);
    EXPECT_EQ((uint64_t)d7.unix_timestamp(), (uint64_t)1551312000);

    //zero day
    Date d8(2000,1,0,0,0,0);
    EXPECT_EQ((uint64_t)d8.unix_timestamp(), (uint64_t)946684800);

    //out of range hours
    Date d9(2000, 1, 1, 24, 59, 59);
    EXPECT_EQ((uint64_t)d9.unix_timestamp(), (uint64_t)946771199);

    //out of range minutes
    Date d10(2000, 1, 1, 23, 60, 59);
    EXPECT_EQ((uint64_t)d10.unix_timestamp(), (uint64_t)946771199);

    //out of range seconds
    Date d11(2000, 1, 1, 23, 59, 60);
    EXPECT_EQ((uint64_t)d11.unix_timestamp(), (uint64_t)946771199);

}

SPECTRE_TEST_END(Date_tests)
