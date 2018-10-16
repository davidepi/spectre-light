#include "date.hpp"
#include "utility/console.hpp"
#include <ctime>
#include <cctype>
#include <cstdlib>
#include <regex>
#include <iostream>

const uint8_t MDAYS[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date()
{
    time_t now = time(NULL);
    struct tm utc_time;
#ifdef _WIN32
    //Inverted parameters, _s instead of _r. Seriously windows?
    gmtime_s(&utc_time, &now);
#else
    gmtime_r(&now, &utc_time);
#endif
    year = (int16_t)(utc_time.tm_year+1900);
    month = (uint8_t)utc_time.tm_mon;
    day = (uint8_t)utc_time.tm_mday;
    hour = (uint8_t)utc_time.tm_hour;
    min = (uint8_t)utc_time.tm_min;
    sec = (uint8_t)utc_time.tm_sec;
}

static inline void sanitize(int16_t* year, uint8_t* month, uint8_t* day,
                            uint8_t* hours, uint8_t* minutes, uint8_t* seconds)
{
    if(*seconds>59)
        *seconds = 59;
    if(*minutes>59)
        *minutes = 59;
    if(*hours>23)
        *hours = 23;
    *month = *month-1;
    if(*day == 0)
        *day=*day+1;
    if(*month>11)
        *month = 11;
    if(*day>MDAYS[*month])
        *day = MDAYS[*month];
    //leap year
    if(*month == 1 && *day == 29 && *year%4 != 0)
        *day = *day-1;
    if(*year<-4712)
        *year = -4712;
}

Date::Date(const char* string)
{
    const char* regexp = "\\s*(-?[0-9]+)[-/]([0-9][0-9]?)[-/]([0-9][0-9]?)\\s+"\
                         "([0-9][0-9]):([0-9][0-9]):([0-9][0-9])\\s*";
    std::regex regex_engine(regexp, std::regex::ECMAScript);
    std::match_results<const char*> matched;
    std::regex_match(string, matched, regex_engine);
    if(matched.size() == 7)
    {
        year = strtol(matched[1].str().c_str(), NULL, 10);
        month = strtol(matched[2].str().c_str(), NULL, 10)-1;
        day = strtol(matched[3].str().c_str(), NULL, 10);
        hour = strtol(matched[4].str().c_str(), NULL, 10);
        min = strtol(matched[5].str().c_str(), NULL, 10);
        sec = strtol(matched[6].str().c_str(), NULL, 10);
    }
    else
    {
        Console.notice(MESSAGE_WRONG_DATA_FORMAT);
        *this = Date();
    }
}

Date::Date(int16_t year, uint8_t month, uint8_t day, uint8_t hours,
           uint8_t minutes, uint8_t seconds)
{
    //clamp everything out of range
    sanitize(&year, &month, &day, &hours, &minutes, &seconds);
    Date::year = year;
    Date::month = month;
    Date::day = day;
    Date::hour = hours;
    Date::min = minutes;
    Date::sec = seconds;
}

time_t Date::unix_timestamp() const
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
#ifdef _WIN32
        retval = _mkgmtime(&utc);
#else
        retval = timegm(&utc);
#endif
    }
    else
        retval = 0;
    return retval;
}

double Date::get_julian_date() const
{
    constexpr const double INV24 = 1.f/24.f;
    constexpr const double INV60 = 1.f/60.f;
    const double DEC_DAY = day+hour*INV24+min*INV24*INV60+sec*INV24*INV60*INV60;
    uint8_t month1 = (uint8_t)(month+1);
    int16_t year1;
    if(month1<=2)
    {
        year1 = (int16_t)(year-1);
        month1 += 12;
    }
    else
        year1 = year;
    double jd = (int)(365.25*(year1+4716))+(int)(30.6001*(month1+1))+DEC_DAY;
    jd -= 1524.5;
    if(jd>2299160)
    {
        //conversion coefficient from gregorian calendar (account leap years)
        const int Y100 = year1/100;
        jd += (2-Y100+(Y100 >> 2));
    }
    if(jd<0)
        jd = 0; //for a corner case like Jan 1, 00:00:00 -4712
    return jd;
}

double Date::get_delta_t() const
{
    //source: http://www.eclipsewise.com/help/deltatpoly2014.html
    double retval;
    if(year>=2015) //expected to be the most common one
    {
        const float T = year-2015;
        retval = 67.62+0.3645*T+0.0039755*T*T;
    }
    else if(year<-500)
    {
        const float U = (year-1820)/100;
        retval = -20+32*U*U;
    }
    else if(year<500)
    {
        const float U = year/100;
        retval =
                10583.6-1014.41*U+33.78311*U*U-5.952053*U*U*U-0.1798452*U*U*U*U+
                0.022174192*U*U*U*U*U+0.0090316521*U*U*U*U*U*U;
    }
    else if(year<1600)
    {
        const float U = (year-1000)/100;
        retval = 1574.2-556.01*U+71.23472*U*U+0.319781*U*U*U-0.8503463*U*U*U*U-
                 0.005050998*U*U*U*U*U+0.0083572073*U*U*U*U*U*U;
    }
    else if(year<1700)
    {
        const float T = year-1600;
        retval = 120-0.9808*T-0.01532*T*T+T*T*T/7129;
    }
    else if(year<1800)
    {
        const float T = year-1700;
        retval = 8.83+0.1603*T-0.0059285*T*T+0.00013336*T*T*T-T*T*T*T/1174000;
    }
    else if(year<1860)
    {
        const float T = year-1800;
        retval = 13.72-0.332447*T+0.0068612*T*T+0.0041116*T*T*T-
                 0.00037436*T*T*T*T+0.0000121272*T*T*T*T*T-
                 0.0000001699*T*T*T*T*T*T+0.000000000875*T*T*T*T*T*T*T;
    }
    else if(year<1900)
    {
        const float T = year-1860;
        retval = 7.62+0.5737*T-0.251754*T*T+0.01680668*T*T*T-
                 0.0004473624*T*T*T*T+T*T*T*T*T/233174;
    }
    else if(year<1920)
    {
        const float T = year-1900;
        retval =
                -2.79+1.494119*T-0.0598939*T*T+0.0061966*T*T*T-0.000197*T*T*T*T;
    }
    else if(year<1941)
    {
        const float T = year-1920;
        retval = 21.20+0.84493*T-0.076100*T*T+0.0020936*T*T*T;
    }
    else if(year<1961)
    {
        const float T = year-1950;
        retval = 29.07+0.407*T-T*T/233+T*T*T/2547;
    }
    else if(year<1986)
    {
        const float T = year-1975;
        retval = 45.45+1.067*T-T*T/260-T*T*T/718;
    }
    else if(year<2005)
    {
        const float T = year-2000;
        retval =
                63.86+0.3345*T-0.060374*T*T+0.0017275*T*T*T+0.000651814*T*T*T*T+
                0.00002373599*T*T*T*T*T;
    }
    else //year < 2015
    {
        const float T = year-2000;
        retval = 64.69+0.2930*T;
    }
    return retval;
}
