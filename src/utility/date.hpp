//Created,   3 Oct 2018
//Last Edit 11 Oct 2018

/**
 *  \file date.hpp
 *  \brief     Class representing a given instant of time
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      11 Oct 2018
 *  \copyright GNU GPLv3
 */


#ifndef __DATE_HPP__
#define __DATE_HPP__

#include <cstdint>
#include <cstdlib>
#include <ctime>

/**
 *  \brief Class representing an instant of time
 *
 *  The date class represents an instant of time by using a date on the
 *  calendar and a given time. This class is extremely simple and does not
 *  take into account leap seconds. The class can be used to calculate the
 *  Julian calendar date required to derive the sun position.
 *
 *  Everything in this class is assumed UTC
 */
class Date
{
public:

    /**
     *  \brief Construct a Date object representing the given date and time
     *
     *  Values not in range will be clamped, leap seconds are not supported
     *
     *  \param[in] year The year for the current date, in range [-4712, 32767]
     *  \param[in] month The month for the current date, 1-based, in range
     *  [1, 12]
     *  \param[in] day The day of the month for the current date in range from 1
     *  to the maximum days of the given month
     *  \param[in] hours The hours for the given time, in range [0-23]
     *  \param[in] minutes The minutes for the given time, in range [0-59]
     *  \param[in] seconds The seconds for the given time, in range [0-59]
     */
    Date(int16_t year, uint8_t month, uint8_t day, uint8_t hours,
         uint8_t minutes, uint8_t seconds);

    /**
     *  \brief Construct a Date object given a yyyy/MM/dd HH:mm:ss string
     *
     *  Given a string in the format yyyy/MM/dd HH:mm:ss or yyyy-mm-dd HH:mm:ss
     *  the Date object is constructed.
     *  If the string is not parsable, the date will be set as Jan 1, 2000 at
     *  00:00:00.
     *  Exceptionally, months and days only, can be written with a single digit.
     *
     *  \param[in] string A string formatted as yyyy/MM/dd HH:mm:ss or
     *  yyyy-MM-dd HH:mm:ss
     */
    Date(const char* string);

    /**
     *  \brief Construct a Date object representing the current time
     *
     *  Construct this class with the current day and hour as parameters
     */
    Date();

    /**
     *  \brief Returns the current date as unix timestamp
     *
     *  Convert the date represented by this class into an unix timestamp,
     *  the number of seconds passed since Jan 1, 1970. If the current date
     *  is prior to Jan 1, 1970 this function returns 0
     *
     *  \return The unix timestamp for this date, 0 if prior to Jan 1, 1970
     */
    time_t unix_timestamp() const;

    /**
     *  \brief Calculate the Julian date for the current date
     *
     *  Calculate the number of days since Jan 1, -4712 at noon. A fraction
     *  is added to the number to take into account hours, minutes and seconds
     *
     *  \return The julian date (JD) for the current date
     */
    double get_julian_date() const;

    /**
     *  \brief Returns the difference between UT1 and TT for the given date
     *
     *  This class uses UTC time (TT) for measurement. TT time is corrected
     *  to account for earth variation by adding a term ΔT to the atomic time
     *  UT1. This function is used to retrieve this value.
     *  Note that the value is calculated and not measured, thus it is not
     *  precise. Note also that historical values (before 1955) are deducted
     *  and thus even less precise.
     *
     *  \return The difference between UT1 and TT for the given date
     */
    double get_delta_t()const;

private:
    /** year [-4712, +32768] */
    int16_t year;
    /** month [0, 11] */
    uint8_t month;
    /** day [0, 31] */
    uint8_t day;
    /** hour [0, 24] */
    uint8_t hour;
    /** minutes [0, 59] */
    uint8_t min;
    /** seconds [0, 59] */
    uint8_t sec;
};

#endif
