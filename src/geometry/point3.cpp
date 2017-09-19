#include "point3.hpp"
Point3::Point3()
{
    Point3::x = 0.0f;
    Point3::y = 0.0f;
    Point3::z = 0.0f;
}

Point3::Point3(float xyz)
{
#ifdef _LOW_LEVEL_CHECKS_
    Console.severe(std::isnan(xyz), MESSAGE_NAN("Point3"));
#endif
    Point3::x = xyz;
    Point3::y = xyz;
    Point3::z = xyz;
}

Point3::Point3(float x, float y, float z)
{
#ifdef _LOW_LEVEL_CHECKS_
    Console.severe(std::isnan(x) || std::isnan(y) || std::isnan(z),
                   MESSAGE_NAN("Point3"));
#endif
    Point3::x = x;
    Point3::y = y;
    Point3::z = z;
}

float Point3::distanceTo(const Point3& p)const
{
    float x = p.x - Point3::x;
    float y = p.y - Point3::y;
    float z = p.z - Point3::z;
    
    return std::sqrt((x * x) + (y * y) + (z*z));
}

void Point3::max(const Point3& p)
{
    if(p.x > Point3::x)
        Point3::x = p.x;
    if(p.y > Point3::y)
        Point3::y = p.y;
    if(p.z > Point3::z)
        Point3::z = p.z;
}

void Point3::min(const Point3& p)
{
    if(p.x < Point3::x)
        Point3::x = p.x;
    if(p.y < Point3::y)
        Point3::y = p.y;
    if(p.z < Point3::z)
        Point3::z = p.z;
}

//♥ ♥ ♥ Operators ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥

Point3 Point3::operator+ (const Vec3& v) const
{
    return Point3(Point3::x + v.x, Point3::y + v.y, Point3::z + v.z);
}

//Point3 Point3::operator+ (const Point3& p) const
//{
//    return Point3(Point3::x + p.x, Point3::y + p.y, Point3::z + p.z);
//}

void Point3::operator+=(const Vec3&  v)
{
    Point3::x += v.x;
    Point3::y += v.y;
    Point3::z += v.z;
}

Vec3 Point3::operator-(const Point3& p)const
{
    return Vec3(Point3::x - p.x, Point3::y - p.y, Point3::z - p.z);
}

Point3 Point3::operator-(const Vec3&  v)const
{
    return Point3(Point3::x - v.x, Point3::y - v.y, Point3::z - v.z);
}

void Point3::operator-=(const Vec3&  v)
{
    Point3::x -= v.x;
    Point3::y -= v.y;
    Point3::z -= v.z;
}

//Point3 Point3::operator* (const float f)const
//{
//    return Point3(Point3::x * f, Point3::y * f, Point3::z * f);
//}

bool Point3::operator== (const Point3& p)const
{
    return std::fabs(Point3::x-p.x) <= FLT_EPSILON &&
           std::fabs(Point3::y-p.y) <= FLT_EPSILON &&
           std::fabs(Point3::z-p.z) <= FLT_EPSILON;
}

bool Point3::operator!= (const Point3& p)const
{
    return std::fabs(Point3::x-p.x) > FLT_EPSILON ||
           std::fabs(Point3::y-p.y) > FLT_EPSILON ||
           std::fabs(Point3::z-p.z) > FLT_EPSILON;
}

float Point3::operator[] (int val)const
{
    return *(&(Point3::x)+val);
}

//♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥
