//Created,   3 Oct 2018
//Last Edit  3 Oct 2018

/**
 *  \file date.hpp
 *  \brief     class representing a given instant of time
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      3 Oct 2018
 *  \copyright GNU GPLv3
 */


#ifndef __DATE_HPP__
#define __DATE_HPP__

#include <cstdint>
#include <cstdlib>

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

private:
    int16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
};

#endif
