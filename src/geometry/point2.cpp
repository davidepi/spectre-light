//author: Davide Pizzolotto
//license: GNU GPLv3

#include "point2.hpp"
Point2::Point2()
{
    Point2::x = 0.0f;
    Point2::y = 0.0f;
}

Point2::Point2(float xyz)
{
#ifdef DEBUG
    if(std::isnan(xyz))
        Console.severe(MESSAGE_NAN("Point2"));
#endif
    Point2::x = xyz;
    Point2::y = xyz;
}

Point2::Point2(float x, float y)
{
#ifdef DEBUG
    if(std::isnan(x) || std::isnan(y))
        Console.severe(MESSAGE_NAN("Point2"));
#endif
    Point2::x = x;
    Point2::y = y;
}

float Point2::distanceTo(const Point2& p)const
{
    float x = p.x - Point2::x;
    float y = p.y - Point2::y;

    return std::sqrt((x * x) + (y * y));
}

void Point2::max(const Point2& p)
{
    if(p.x > Point2::x)
        Point2::x = p.x;
    if(p.y > Point2::y)
        Point2::y = p.y;
}

void Point2::min(const Point2& p)
{
    if(p.x < Point2::x)
        Point2::x = p.x;
    if(p.y < Point2::y)
        Point2::y = p.y;
}

//------ Operators -------------------------------------------------------------

Point2 Point2::operator+ (const Vec2& v) const
{
    return Point2(Point2::x + v.x, Point2::y + v.y);
}

void Point2::operator+=(const Vec2&  v)
{
    Point2::x += v.x;
    Point2::y += v.y;
}

Vec2 Point2::operator-(const Point2& p)const
{
    return Vec2(Point2::x - p.x, Point2::y - p.y);
}

Point2 Point2::operator-(const Vec2&  v)const
{
    return Point2(Point2::x - v.x, Point2::y - v.y);
}

void Point2::operator-=(const Vec2&  v)
{
    Point2::x -= v.x;
    Point2::y -= v.y;
}

bool Point2::operator==(const Point2& p)const
{
#ifdef DEBUG
    if(p.x == INFINITY || p.y == INFINITY ||
       Point2::x == INFINITY || Point2::y == INFINITY)
        Console.severe(MESSAGE_COMPARE_INF);
#endif
    return std::fabs(Point2::x-p.x) <= FLT_EPSILON &&
           std::fabs(Point2::y-p.y) <= FLT_EPSILON;
}

bool Point2::operator!=(const Point2& p)const
{
#ifdef DEBUG
    if(p.x == INFINITY || p.y == INFINITY ||
       Point2::x == INFINITY || Point2::y == INFINITY)
        Console.severe(MESSAGE_COMPARE_INF);
#endif
    return std::fabs(Point2::x-p.x) > FLT_EPSILON ||
           std::fabs(Point2::y-p.y) > FLT_EPSILON;
}

float& Point2::operator[](int val)
{
    return *(&(Point2::x)+val);
}

float Point2::operator[](int val)const
{
    return *(&(Point2::x)+val);
}

//------------------------------------------------------------------------------
