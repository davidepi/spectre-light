#include "color.hpp"

Color::Color()
{
    Color::r = 0.f;
    Color::g = 0.f;
    Color::b = 0.f;
}

Color::Color(float r, float g, float b)
{
    Color::r = r;
    Color::g = g;
    Color::b = b;
}

Color::Color(float rgb)
{
    Color::r = rgb;
    Color::g = rgb;
    Color::b = rgb;
}

Color::Color(const char* hex)
{
    if(hex[0]!='#' || (strlen(hex)!=4&&strlen(hex)!=7))
    {
        Color::r = 0.f;
        Color::g = 0.f;
        Color::b = 0.f;
    }
    else
    {
        unsigned char hexred = 0x0;
        unsigned char hexgreen = 0x0;
        unsigned char hexblue = 0x0;
        char tmp[3];
        tmp[2] = '\0';
        if(strlen(hex)==4)
        {   tmp[0] = hex[1];
            tmp[1] = hex[1];
            hexred = (unsigned char)strtol(tmp, NULL, 16);
            tmp[0] = hex[2];
            tmp[1] = hex[2];
            hexgreen = (unsigned char)strtol(tmp, NULL, 16);
            tmp[0] = hex[3];
            tmp[1] = hex[3];
            hexblue = (unsigned char)strtol(tmp, NULL, 16);
        }
        else
        {
            tmp[0] = hex[1];
            tmp[1] = hex[2];
            hexred = (unsigned char)strtol(tmp, NULL, 16);
            tmp[0] = hex[3];
            tmp[1] = hex[4];
            hexgreen = (unsigned char)strtol(tmp, NULL, 16);
            tmp[0] = hex[5];
            tmp[1] = hex[6];
            hexblue = (unsigned char)strtol(tmp, NULL, 16);
        }
        Color::r = hexred / 255.f;
        Color::g = hexgreen / 255.f;
        Color::b = hexblue / 255.f;
    }
}

Color::~Color()
{
    
}
