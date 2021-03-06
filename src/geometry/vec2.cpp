//author: Davide Pizzolotto
//license: GNU GPLv3

#include "vec2.hpp"

#define CHAR_ARRAY_SIZE_PER_FLOAT 10

Vec2::Vec2()
{
    Vec2::x = 0;
    Vec2::y = 0;
}

Vec2::Vec2(float xy)
{
#ifdef DEBUG
    if(std::isnan(xy))
        Console.severe(MESSAGE_NAN("Vec2"));
    if(std::isinf(xy))
        Console.severe(MESSAGE_INFINITY("Vec2"));
#endif
    Vec2::x = xy;
    Vec2::y = xy;
}

Vec2::Vec2(float x, float y)
{
#ifdef DEBUG
    if(std::isnan(x) || std::isnan(y))
        Console.severe(MESSAGE_NAN("Vec2"));
    if(std::isinf(x) || std::isinf(y))
        Console.severe(MESSAGE_INFINITY("Vec2"));
#endif
    Vec2::x = x;
    Vec2::y = y;
}

Vec2::Vec2(const float* xy)
{
#ifdef DEBUG
    if(xy != NULL)
    {
        if(std::isnan(xy[0]) || std::isnan(xy[1]))
            Console.severe(MESSAGE_NAN("Vec2"));
        if(std::isinf(xy[0]) || std::isinf(xy[1]))
            Console.severe(MESSAGE_INFINITY("Vec2"));
#endif
        Vec2::x = xy[0];
        Vec2::y = xy[1];
#ifdef DEBUG
    }
    else
    {
        Console.warning(MESSAGE_NULLPOINTER("Vec2"));
        Vec2::x = 0;
        Vec2::y = 0;
    }
#endif
}

float Vec2::length() const
{
    return std::sqrt((Vec2::x*Vec2::x)+(Vec2::y*Vec2::y));
}

float Vec2::length2() const
{
    return (Vec2::x*Vec2::x)+(Vec2::y*Vec2::y);
}

void Vec2::normalize()
{
    float length = Vec2::length();
#ifdef DEBUG
    if(length == 0)
    {
        Console.critical(MESSAGE_NORMALIZE_ZERO);
        return;
    }
#endif
    float inverse = 1/length;
    Vec2::x *= inverse;
    Vec2::y *= inverse;
}

bool Vec2::is_normalized() const
{
    float len = Vec2::length();
    return len>1-FLT_EPSILON && len<1+FLT_EPSILON;
}

void Vec2::to_array(float* res) const
{
    res[0] = Vec2::x;
    res[1] = Vec2::y;
}

std::string Vec2::to_string() const
{
    std::ostringstream oss;
    oss << std::fixed;
    oss << "Vec2[" << x << ", " << y << "]";
    return oss.str();
}

void Vec2::clamp(const Vec2& min, const Vec2& max)
{
    if(Vec2::x<min.x) Vec2::x = min.x;
    else if(Vec2::x>max.x) Vec2::x = max.x;

    if(Vec2::y<min.y) Vec2::y = min.y;
    else if(Vec2::y>max.y) Vec2::y = max.y;
}

void Vec2::saturate()
{
    if(Vec2::x<.0f) Vec2::x = .0f;
    else if(Vec2::x>1.0f) Vec2::x = 1.0f;
    if(Vec2::y<.0f) Vec2::y = .0f;
    else if(Vec2::y>1.0f) Vec2::y = 1.0f;
}

float Vec2::distance(const Vec2& target) const
{
    float x = target.x-Vec2::x;
    float y = target.y-Vec2::y;

    return std::sqrt((x*x)+(y*y));
}

float Vec2::dot(const Vec2& target) const
{
    return ((Vec2::x*target.x)+(Vec2::y*target.y));
}

void Vec2::max(const Vec2& vector2)
{
    float x, y;
    if(Vec2::x>vector2.x)
        x = Vec2::x;
    else
        x = vector2.x;
    if(Vec2::y>vector2.y)
        y = Vec2::y;
    else
        y = vector2.y;

    Vec2::x = x;
    Vec2::y = y;
}

void Vec2::min(const Vec2& vector2)
{
    float x, y;
    if(Vec2::x<vector2.x)
        x = Vec2::x;
    else
        x = vector2.x;
    if(Vec2::y<vector2.y)
        y = Vec2::y;
    else
        y = vector2.y;

    Vec2::x = x;
    Vec2::y = y;
}

//------ Operators -------------------------------------------------------------

Vec2 Vec2::operator+(const Vec2& v) const
{
    return Vec2(Vec2::x+v.x, Vec2::y+v.y);
}

Vec2 Vec2::operator+(float f) const
{
    return Vec2(Vec2::x+f, Vec2::y+f);
}

void Vec2::operator+=(const Vec2& v)
{
    Vec2::x += v.x;
    Vec2::y += v.y;
}

void Vec2::operator+=(float f)
{
    Vec2::x += f;
    Vec2::y += f;
}

Vec2 Vec2::operator-(const Vec2& v) const
{
    return Vec2(Vec2::x-v.x, Vec2::y-v.y);
}

Vec2 Vec2::operator-(float f) const
{
    return Vec2(Vec2::x-f, Vec2::y-f);
}

void Vec2::operator-=(const Vec2& v)
{
    Vec2::x -= v.x;
    Vec2::y -= v.y;
}

void Vec2::operator-=(float f)
{
    Vec2::x -= f;
    Vec2::y -= f;
}

Vec2 Vec2::operator*(const Vec2& v) const
{
    return Vec2(Vec2::x*v.x, Vec2::y*v.y);
}

Vec2 Vec2::operator*(float f) const
{
    return Vec2(Vec2::x*f, Vec2::y*f);
}

void Vec2::operator*=(const Vec2& v)
{
    Vec2::x *= v.x;
    Vec2::y *= v.y;
}

void Vec2::operator*=(float f)
{
    Vec2::x *= f;
    Vec2::y *= f;
}

Vec2 Vec2::operator/(const Vec2& v) const
{
#ifdef DEBUG
    if(v.x == 0 || v.y == 0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return Vec2();
    }
#endif
    return Vec2(Vec2::x/v.x, Vec2::y/v.y);
}

Vec2 Vec2::operator/(float f) const
{
#ifdef DEBUG
    if(f == 0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return Vec2();
    }
#endif
    return Vec2(Vec2::x/f, Vec2::y/f);
}

void Vec2::operator/=(const Vec2& v)
{
#ifdef DEBUG
    if(v.x == 0 || v.y == 0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return;
    }
#endif
    Vec2::x /= v.x;
    Vec2::y /= v.y;
}

void Vec2::operator/=(float f)
{
#ifdef DEBUG
    if(f == 0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return;
    }
#endif
    Vec2::x /= f;
    Vec2::y /= f;
}

Vec2 Vec2::operator!() const
{
    return Vec2(-Vec2::x, -Vec2::y);
}

Vec2 Vec2::operator-() const
{
    return Vec2(-Vec2::x, -Vec2::y);
}

bool Vec2::operator==(const Vec2& v) const
{
    return std::fabs(Vec2::x-v.x)<=FLT_EPSILON &&
           std::fabs(Vec2::y-v.y)<=FLT_EPSILON;
}

bool Vec2::operator!=(const Vec2& v) const
{
    return std::fabs(Vec2::x-v.x)>FLT_EPSILON ||
           std::fabs(Vec2::y-v.y)>FLT_EPSILON;
}

//------------------------------------------------------------------------------
