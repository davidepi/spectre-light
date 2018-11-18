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
#include "utility/console.hpp"
#include <regex>
#include <iostream>

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

SPECTRE_TEST(Date, string_given)
{
    //correct with -
    Date d2("1971-08-26 12:30:30");
    EXPECT_EQ((uint64_t)d2.unix_timestamp(), (uint64_t)52057830);
    //correct with /
    Date d3("  1996/09/09    09:09:09  ");
    EXPECT_EQ((uint64_t)d3.unix_timestamp(), (uint64_t)842260149);
    //correct with -, single digit
    Date d4("1971-8-26 12:30:30");
    EXPECT_EQ((uint64_t)d4.unix_timestamp(), (uint64_t)52057830);
    //correct with /, single digit
    Date d5("  1996/9/9    09:09:09  ");
    EXPECT_EQ((uint64_t)d5.unix_timestamp(), (uint64_t)842260149);
    Date d6("1996-9-9 9:09:09");
    EXPECT_EQ((uint64_t)d6.unix_timestamp(), (uint64_t)842260149);
    Date d7("1996-9-9 09:9:09");
    EXPECT_EQ((uint64_t)d7.unix_timestamp(), (uint64_t)842260149);
    Date d8("1996-9-9 09:09:9");
    EXPECT_EQ((uint64_t)d8.unix_timestamp(), (uint64_t)842260149);
    //wrong
    errors_count[NOTICE_INDEX] = 0;
    Date d1("ciao");
    time_t now = time(NULL);
    EXPECT_EQ((uint64_t)d1.unix_timestamp(), (uint64_t)now);
    EXPECT_EQ(errors_count[NOTICE_INDEX], 1);
    errors_count[NOTICE_INDEX] = 0;
}

SPECTRE_TEST(Date, constructor_given)
{
    //correct
    Date d1(2000, 1, 1, 0, 0, 0);
    EXPECT_EQ((uint64_t)d1.unix_timestamp(), (uint64_t)946684800);

    //wrong year
    Date d2(-10000, 1, 1, 0, 0, 0);
    EXPECT_EQ((uint64_t)d2.unix_timestamp(), (uint64_t)0);

    //wrong month
    Date d3(2000, 13, 1, 0, 0, 0);
    EXPECT_EQ((uint64_t)d3.unix_timestamp(), (uint64_t)975628800);

    //wrong day of the month (Feb, 30), but leap year
    Date d4(2020, 2, 30, 0, 0, 0);
    EXPECT_EQ((uint64_t)d4.unix_timestamp(), (uint64_t)1582934400);

    //wrong day of the month (Feb, 30) but not leap year
    Date d5(2019, 2, 30, 0, 0, 0);
    EXPECT_EQ((uint64_t)d5.unix_timestamp(), (uint64_t)1551312000);

    //leap year
    Date d6(2020, 2, 29, 0, 0, 0);
    EXPECT_EQ((uint64_t)d6.unix_timestamp(), (uint64_t)1582934400);

    //non leap year, wrong day
    Date d7(2019, 2, 29, 0, 0, 0);
    EXPECT_EQ((uint64_t)d7.unix_timestamp(), (uint64_t)1551312000);

    //zero day
    Date d8(2000, 1, 0, 0, 0, 0);
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

SPECTRE_TEST(Date, get_julian_day)
{
    Date d1(2000, 1, 1, 12, 0, 0);
    EXPECT_NEAR(d1.get_julian_date(), 2451545.0, 1e-5f);
    Date d2(1999, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d2.get_julian_date(), 2451179.5, 1e-5f);
    Date d3(1987, 1, 27, 0, 0, 0);
    EXPECT_NEAR(d3.get_julian_date(), 2446822.5, 1e-5f);
    Date d4(1987, 6, 19, 12, 0, 0);
    EXPECT_NEAR(d4.get_julian_date(), 2446966.0, 1e-5f);
    Date d5(1988, 1, 27, 0, 0, 0);
    EXPECT_NEAR(d5.get_julian_date(), 2447187.5, 1e-5f);
    Date d6(1988, 6, 19, 12, 0, 0);
    EXPECT_NEAR(d6.get_julian_date(), 2447332.0, 1e-5f);
    Date d7(1900, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d7.get_julian_date(), 2415020.5, 1e-5f);
    Date d8(1600, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d8.get_julian_date(), 2305447.5, 1e-5f);
    Date d9(1600, 12, 31, 0, 0, 0);
    EXPECT_NEAR(d9.get_julian_date(), 2305812.5, 1e-5f);
    Date d10(837, 4, 10, 7, 12, 0);
    EXPECT_NEAR(d10.get_julian_date(), 2026871.8, 1e-5f);
    Date d11(-123, 12, 31, 0, 0, 0);
    EXPECT_NEAR(d11.get_julian_date(), 1676496.5, 1e-5f);
    Date d12(-122, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d12.get_julian_date(), 1676497.5, 1e-5f);
    Date d13(-1000, 7, 12, 12, 0, 0);
    EXPECT_NEAR(d13.get_julian_date(), 1356001.0, 1e-5f);
    Date d14(-1000, 2, 29, 0, 0, 0);
    EXPECT_NEAR(d14.get_julian_date(), 1355866.5, 1e-5f);
    Date d15(-1001, 8, 17, 21, 36, 0);
    EXPECT_NEAR(d15.get_julian_date(), 1355671.4, 1e-5f);
    Date d16(-4712, 1, 1, 12, 0, 0);
    EXPECT_NEAR(d16.get_julian_date(), 0.0, 1e-5f);
    Date d17(-4712, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d17.get_julian_date(), 0.0, 1e-5f);
}

SPECTRE_TEST(Date, get_delta_t)
{
    Date d1(-500, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d1.get_delta_t(), 17203.6, 1e-1);
    Date d2(-400, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d2.get_delta_t(), 15530.9, 1e-1);
    Date d3(-300, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d3.get_delta_t(), 14078.2, 1e-1);
    Date d4(-200, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d4.get_delta_t(), 12792.1, 1e-1);
    Date d5(-100, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d5.get_delta_t(), 11637.5, 1e-1);
    Date d6(0, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d6.get_delta_t(), 10583.6, 1e-1);
    Date d7(100, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d7.get_delta_t(), 9596.8, 1e-1);
    Date d8(200, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d8.get_delta_t(), 8640.7, 1e-1);
    Date d9(300, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d9.get_delta_t(), 7681.1, 1e-1);
    Date d10(400, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d10.get_delta_t(), 6699.2, 1e-1);
    Date d11(500, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d11.get_delta_t(), 5710.0, 1e-1);
    Date d12(600, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d12.get_delta_t(), 4739.2, 1e-1);
    Date d13(700, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d13.get_delta_t(), 3813.1, 1e-1);
    Date d14(800, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d14.get_delta_t(), 2955.6, 1e-1);
    Date d15(900, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d15.get_delta_t(), 2200.2, 1e-1);
    Date d16(1000, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d16.get_delta_t(), 1574.2, 1e-1);
    Date d17(1100, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d17.get_delta_t(), 1088.8, 1e-1);
    Date d18(1200, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d18.get_delta_t(), 736.4, 1e-1);
    Date d19(1300, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d19.get_delta_t(), 491.9, 1e-1);
    Date d20(1400, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d20.get_delta_t(), 321.7, 1e-1);
    Date d21(1500, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d21.get_delta_t(), 198.3, 1e-1);
    Date d22(1600, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d22.get_delta_t(), 120.0, 1e-1);
    Date d23(1700, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d23.get_delta_t(), 8.83, 1e-1);
    Date d24(1750, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d24.get_delta_t(), 13.3, 1e-1);
    Date d25(1800, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d25.get_delta_t(), 13.7, 1e-1);
    Date d26(1850, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d26.get_delta_t(), 7.1, 1e-1);
    Date d27(1900, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d27.get_delta_t(), -2.79, 1e-1);
    Date d28(1950, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d28.get_delta_t(), 29.0, 1e-1);
    Date d29(1955, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d29.get_delta_t(), 31.1, 1e-1);
    Date d30(1960, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d30.get_delta_t(), 33.2, 1e-1);
    Date d31(1965, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d31.get_delta_t(), 35.7, 1e-1);
    Date d32(1970, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d32.get_delta_t(), 40.2, 1e-1);
    Date d33(1975, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d33.get_delta_t(), 45.5, 1e-1);
    Date d34(1980, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d34.get_delta_t(), 50.5, 1e-1);
    Date d35(1985, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d35.get_delta_t(), 54.3, 1e-1);
    Date d36(1990, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d36.get_delta_t(), 56.9, 1e-1);
    Date d37(1995, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d37.get_delta_t(), 60.8, 1e-1);
    Date d38(2000, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d38.get_delta_t(), 63.8, 1e-1);
    Date d39(2005, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d39.get_delta_t(), 66.1, 1e-1);
    Date d40(2010, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d40.get_delta_t(), 67.6, 1e-1);
    Date d41(2014, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d41.get_delta_t(), 68.7, 1e-1);
    Date d42(2016, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d42.get_delta_t(), 67.9, 1e-1);
    Date d43(2018, 1, 1, 0, 0, 0);
    EXPECT_NEAR(d43.get_delta_t(), 68.7, 1e-1);
}

SPECTRE_TEST_END(Date_tests)
