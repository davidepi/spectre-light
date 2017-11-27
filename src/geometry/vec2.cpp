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
#ifdef _LOW_LEVEL_CHECKS_
    Console.severe(std::isnan(xy), MESSAGE_NAN("Vec2"));
    Console.severe(std::isinf(xy), MESSAGE_INFINITY("Vec2"));
#endif
    Vec2::x = xy;
    Vec2::y = xy;
}

Vec2::Vec2(float x, float y)
{
#ifdef _LOW_LEVEL_CHECKS_
    Console.severe(std::isnan(x) || std::isnan(y), MESSAGE_NAN("Vec2"));
    Console.severe(std::isinf(x) || std::isinf(y), MESSAGE_INFINITY("Vec2"));
#endif
    Vec2::x = x;
    Vec2::y = y;
}

Vec2::Vec2(const float* xy)
{
#ifdef _LOW_LEVEL_CHECKS_
    if(xy != NULL)
    {
        Console.severe(std::isnan(xy[0]) || std::isnan(xy[1]),
                       MESSAGE_NAN("Vec2"));
        Console.severe(std::isinf(xy[0]) || std::isinf(xy[1]),
                       MESSAGE_INFINITY("Vec2"));
#endif
        Vec2::x = xy[0];
        Vec2::y = xy[1];
#ifdef _LOW_LEVEL_CHECKS_
    }
    else
    {
        Console.warning(MESSAGE_NULLPOINTER("Vec2"));
        Vec2::x = 0;
        Vec2::y = 0;
    }
#endif
}

float Vec2::length()const
{
    return std::sqrt((Vec2::x * Vec2::x) + (Vec2::y * Vec2::y));
}

float Vec2::lengthSquared()const
{
    return (Vec2::x * Vec2::x) + (Vec2::y * Vec2::y);
}

void Vec2::normalize()
{
    float length = Vec2::length();
#ifdef _LOW_LEVEL_CHECKS_
    if(length==0)
    {
        Console.critical(MESSAGE_NORMALIZE_ZERO);
        return;
    }
#endif
    float inverse = 1 / length;
    Vec2::x *= inverse;
    Vec2::y *= inverse;
}

bool Vec2::isNormalized() const
{
    float len = Vec2::length();
    return len>1-FLT_EPSILON && len<1+FLT_EPSILON;
}

float* Vec2::toArray()const
{
    float* res = new float[2];
    res[0] = Vec2::x;
    res[1] = Vec2::y;
    return res;
}

char* Vec2::toString()const
{
    char val1[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val2[CHAR_ARRAY_SIZE_PER_FLOAT];
    snprintf(val1,sizeof(val1),"%f",(double)Vec2::x);
    snprintf(val2,sizeof(val2),"%f",(double)Vec2::y);
    
    //aperta tonda + chiusa tonda + virgola + '/0' + scritta "vec2" + spazio
    int res_len = (int)(9 + strlen(val1) + strlen(val2));
    char* res = new char[res_len];
    snprintf(res,sizeof(res)*res_len,"vec2(%s, %s)",val1,val2);
    
    return res;
}

void Vec2::clamp(const Vec2& min, const Vec2& max)
{
    if (Vec2::x < min.x) Vec2::x = min.x;
    else if (Vec2::x > max.x) Vec2::x = max.x;
    
    if (Vec2::y < min.y) Vec2::y = min.y;
    else if (Vec2::y > max.y) Vec2::y = max.y;
}

void Vec2::saturate()
{
    if (Vec2::x < .0f) Vec2::x = .0f;
    else if (Vec2::x > 1.0f) Vec2::x = 1.0f;
    if (Vec2::y < .0f) Vec2::y = .0f;
    else if (Vec2::y > 1.0f) Vec2::y = 1.0f;
}

float Vec2::distanceTo(const Vec2& target)const
{
    float x = target.x - Vec2::x;
    float y = target.y - Vec2::y;
    
    return std::sqrt((x * x) + (y * y));
}

float Vec2::dot(const Vec2& target)const
{
    return ((Vec2::x * target.x) + (Vec2::y * target.y));
}

void Vec2::max(const Vec2& vector2)
{
    float x, y;
    if (Vec2::x > vector2.x)
        x = Vec2::x;
    else
        x = vector2.x;
    if (Vec2::y > vector2.y)
        y = Vec2::y;
    else
        y = vector2.y;
    
    Vec2::x = x;
    Vec2::y = y;
}

void Vec2::min(const Vec2& vector2)
{
    float x, y;
    if (Vec2::x < vector2.x)
        x = Vec2::x;
    else
        x = vector2.x;
    if (Vec2::y < vector2.y)
        y = Vec2::y;
    else
        y = vector2.y;
    
    Vec2::x = x;
    Vec2::y = y;
}

void Vec2::reflect(const Vec2& centre)
{
#ifdef _LOW_LEVEL_CHECKS_
    Console.warning(!centre.isNormalized(), MESSAGE_REFLECT_NONORMALIZED);
#endif
    float dot = Vec2::dot(centre);
    Vec2::x -= ((2 * dot) * centre.x);
    Vec2::y -= ((2 * dot) * centre.y);
}

//------ Operators -------------------------------------------------------------

Vec2 Vec2::operator+(const Vec2& v)const
{
    return Vec2(Vec2::x + v.x, Vec2::y + v.y);
}

Vec2 Vec2::operator+(float f)const
{
    return Vec2(Vec2::x + f, Vec2::y + f);
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

Vec2 Vec2::operator-(const Vec2& v)const
{
    return Vec2(Vec2::x - v.x, Vec2::y - v.y);
}

Vec2 Vec2::operator-(float f)const
{
    return Vec2(Vec2::x - f, Vec2::y - f);
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

Vec2 Vec2::operator*(const Vec2& v)const
{
    return Vec2(Vec2::x * v.x, Vec2::y * v.y);
}

Vec2 Vec2::operator*(float f)const
{
    return Vec2(Vec2::x * f, Vec2::y * f);
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

Vec2 Vec2::operator/(const Vec2& v)const
{
#ifdef _LOW_LEVEL_CHECKS_
    if(v.x==0 || v.y==0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return Vec2();
    }
#endif
    return Vec2(Vec2::x / v.x, Vec2::y / v.y);
}

Vec2 Vec2::operator/(float f)const
{
#ifdef _LOW_LEVEL_CHECKS_
    if(f==0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return Vec2();
    }
#endif
    return Vec2(Vec2::x / f, Vec2::y / f);
}

void Vec2::operator/=(const Vec2& v)
{
#ifdef _LOW_LEVEL_CHECKS_
    if(v.x==0 || v.y==0)
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
#ifdef _LOW_LEVEL_CHECKS_
    if(f==0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return;
    }
#endif
    Vec2::x /= f;
    Vec2::y /= f;
}

Vec2 Vec2::operator!()const
{
    return Vec2(-Vec2::x,-Vec2::y);
}

Vec2 Vec2::operator-()const
{
    return Vec2(-Vec2::x,-Vec2::y);
}

bool Vec2::operator==(const Vec2& v)const
{
    return std::fabs(Vec2::x-v.x) <= FLT_EPSILON &&
    std::fabs(Vec2::y-v.y) <= FLT_EPSILON;
}

bool Vec2::operator!=(const Vec2& v)const
{
    return std::fabs(Vec2::x-v.x) > FLT_EPSILON ||
    std::fabs(Vec2::y-v.y) > FLT_EPSILON;
}

//------------------------------------------------------------------------------
