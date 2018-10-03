#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "utility/date.hpp"

SPECTRE_TEST_INIT(Date_tests)

SPECTRE_TEST(Date, unix_timestamp)
{
    //now
    Date d1;
    time_t now = time(NULL);
    EXPECT_EQ(d1.unix_timestamp(), now);

    //given date
    Date d2(2018, 10, 3, 15, 5, 40);
    EXPECT_EQ(d2.unix_timestamp(), (time_t)1538579140);

    //prior to 1970
    Date d3(1936, 9, 6, 12, 30, 15);
    EXPECT_EQ(d3.unix_timestamp(), (time_t)0);
}

SPECTRE_TEST(Date, constructor_given)
{
    //correct
    Date d1(2000, 1, 1, 0, 0, 0);
    EXPECT_EQ(d1.unix_timestamp(), (time_t)946684800);

    //wrong year
    Date d2(-10000, 1, 1, 0, 0, 0);
    EXPECT_EQ(d2.unix_timestamp(), (time_t)0);

    //wrong month
    Date d3(2000, 13, 1, 0, 0, 0);
    EXPECT_EQ(d3.unix_timestamp(), (time_t)975628800);

    //wrong day of the month (Feb, 30), but leap year
    Date d4(2020, 2, 30, 0, 0, 0);
    EXPECT_EQ(d4.unix_timestamp(), (time_t)1582934400);

    //wrong day of the month (Feb, 30) but not leap year
    Date d5(2019, 2, 30, 0, 0, 0);
    EXPECT_EQ(d5.unix_timestamp(), (time_t)1551312000);

    //leap year
    Date d6(2020, 2, 29, 0, 0, 0);
    EXPECT_EQ(d6.unix_timestamp(), (time_t)1582934400);

    //non leap year, wrong day
    Date d7(2019, 2, 29, 0, 0, 0);
    EXPECT_EQ(d7.unix_timestamp(), (time_t)1551312000);

    //zero day
    Date d8(2000, 1, 0, 0, 0, 0);
    EXPECT_EQ(d8.unix_timestamp(), (time_t)946684800);

    //out of range hours
    Date d9(2000, 1, 1, 24, 59, 59);
    EXPECT_EQ(d9.unix_timestamp(), (time_t)946771199);

    //out of range minutes
    Date d10(2000, 1, 1, 23, 60, 59);
    EXPECT_EQ(d10.unix_timestamp(), (time_t)946771199);

    //out of range seconds
    Date d11(2000, 1, 1, 23, 59, 60);
    EXPECT_EQ(d11.unix_timestamp(), (time_t)946771199);

}

SPECTRE_TEST(Date, get_julian_day)
{
    Date d1(2000, 1, 1, 12, 0, 0);
    EXPECT_EQ(d1.get_julian_date(), 2451545.0);
    Date d2(1999, 1, 1, 0, 0, 0);
    EXPECT_EQ(d2.get_julian_date(), 2451179.5);
    Date d3(1987, 1, 27, 0, 0, 0);
    EXPECT_EQ(d3.get_julian_date(), 2446822.5);
    Date d4(1987, 6, 19, 12, 0, 0);
    EXPECT_EQ(d4.get_julian_date(), 2446966.0);
    Date d5(1988, 1, 27, 0, 0, 0);
    EXPECT_EQ(d5.get_julian_date(), 2447187.5);
    Date d6(1988, 6, 19, 12, 0, 0);
    EXPECT_EQ(d6.get_julian_date(), 2447332.0);
    Date d7(1900, 1, 1, 0, 0, 0);
    EXPECT_EQ(d7.get_julian_date(), 2415020.5);
    Date d8(1600, 1, 1, 0, 0, 0);
    EXPECT_EQ(d8.get_julian_date(), 2305447.5);
    Date d9(1600, 12, 31, 0, 0, 0);
    EXPECT_EQ(d9.get_julian_date(), 2305812.5);
    Date d10(837, 4, 10, 7, 12, 0);
    EXPECT_EQ(d10.get_julian_date(), 2026871.75);
    Date d11(-123, 12, 31, 0, 0, 0);
    EXPECT_EQ(d11.get_julian_date(), 1676496.5);
    Date d12(-122, 1, 1, 0, 0, 0);
    EXPECT_EQ(d12.get_julian_date(), 1676497.5);
    Date d13(-1000, 7, 12, 12, 0, 0);
    EXPECT_EQ(d13.get_julian_date(), 1356001.0);
    Date d14(-1000, 2, 29, 0, 0, 0);
    EXPECT_EQ(d14.get_julian_date(), 1355866.5);
    Date d15(-1001, 8, 17, 21, 36, 0);
    EXPECT_EQ(d15.get_julian_date(), 1355671.375);
    Date d16(-4712, 1, 1, 12, 0, 0);
    EXPECT_EQ(d16.get_julian_date(), 0.0);
    Date d17(-4712, 1, 1, 0, 0, 0);
    EXPECT_EQ(d17.get_julian_date(), 0.0);
}

SPECTRE_TEST_END(Date_tests)
