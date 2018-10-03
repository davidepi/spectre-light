#include "date.hpp"
#include <ctime>

const uint8_t MDAYS[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date()
{
    time_t now = time(NULL);
    //TODO: check this thing on windows. should be gmtime_s
    struct tm utc_time;
    gmtime_r(&now, &utc_time);
    year = (int16_t)(utc_time.tm_year+1900);
    month = (uint8_t)utc_time.tm_mon;
    day = (uint8_t)utc_time.tm_mday;
    hour = (uint8_t)utc_time.tm_hour;
    min = (uint8_t)utc_time.tm_min;
    sec = (uint8_t)utc_time.tm_sec;
}

Date::Date(int16_t year, uint8_t month, uint8_t day, uint8_t hours,
           uint8_t minutes, uint8_t seconds)
{
    //clamp everything out of range
    if(seconds>59)
        seconds = 59;
    if(minutes>59)
        minutes = 59;
    if(hours>23)
        hours = 23;
    month--;
    if(day == 0)
        day++;
    if(month>11)
        month = 11;
    if(day>MDAYS[month])
        day = MDAYS[month];
    //leap year
    if(month==1 && day==29 && year%4!=0)
        day--;
    if(year<-4712)
        year = -4712;
    Date::year = year;
    Date::month = month;
    Date::day = day;
    Date::hour = hours;
    Date::min = minutes;
    Date::sec = seconds;
}

time_t Date::unix_timestamp()
{
    time_t retval;
    if(year>=1970)
    {
        struct tm utc;
        utc.tm_year = year-1900;
        utc.tm_mon = month;
        utc.tm_mday = day;
        utc.tm_hour = hour;
        utc.tm_min = min;
        utc.tm_sec = sec;
        retval = timegm(&utc);
    }
    else
        retval = 0;
    return retval;
}
