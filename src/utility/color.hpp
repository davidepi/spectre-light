#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <cstring>
#include <cstdlib>

class Color
{
public:
    
    Color();
    Color(float r, float g, float b);
    Color(float rgb);
    Color(const char* hex);
    ~Color();
    
    ///Red component
    float r;
    
    ///Green component
    float g;
    
    ///Blue component
    float b;
    
    Color operator+(const Color& c)const;
    void operator+=(const Color& c);
    Color operator-(const Color& c)const;
    void operator-=(const Color& c);
    Color operator*(const Color& c)const;
    void operator*=(const Color& c);
    Color operator/(const Color& c)const;
    void operator/=(const Color& c);
};

#endif
