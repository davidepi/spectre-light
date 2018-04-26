//author: Davide Pizzolotto
//license: GNU GPLv3

#include "vec3.hpp"

#define CHAR_ARRAY_SIZE_PER_FLOAT 10

Vec3::Vec3()
{
    Vec3::x = 0;
    Vec3::y = 0;
    Vec3::z = 0;
}

Vec3::Vec3(float xyz)
{
#ifdef DEBUG
    if(std::isnan(xyz))
        Console.severe(MESSAGE_NAN("Vec3"));
    if(std::isinf(xyz))
        Console.severe(MESSAGE_INFINITY("Vec3"));
#endif
    Vec3::x = xyz;
    Vec3::y = xyz;
    Vec3::z = xyz;
}

Vec3::Vec3(float x, float y, float z)
{
#ifdef DEBUG
    if(std::isnan(x) || std::isnan(y) || std::isnan(z))
        Console.severe(MESSAGE_NAN("Vec3"));
    if(std::isinf(x) || std::isinf(y) || std::isinf(z))
        Console.severe(MESSAGE_INFINITY("Vec3"));
#endif
    Vec3::x = x;
    Vec3::y = y;
    Vec3::z = z;
}

Vec3::Vec3(Vec2 xy, float z)
{
#ifdef DEBUG
    if(std::isnan(xy.x) || std::isnan(xy.y) || std::isnan(z))
        Console.severe(MESSAGE_NAN("Vec3"));
    if(std::isinf(xy.x) || std::isinf(xy.y) || std::isinf(z))
        Console.severe(MESSAGE_INFINITY("Vec3"));
#endif
    Vec3::x = xy.x;
    Vec3::y = xy.y;
    Vec3::z = z;
}

Vec3::Vec3(const float* xyz)
{
#ifdef DEBUG
    if(xyz != NULL)
    {
        if(std::isnan(xyz[0]) || std::isnan(xyz[1]) || std::isnan(xyz[2]))
            Console.severe(MESSAGE_NAN("Vec3"));
        if(std::isinf(xyz[0]) || std::isinf(xyz[1]) || std::isinf(xyz[2]))
            Console.severe(MESSAGE_INFINITY("Vec3"));
#endif
        Vec3::x = xyz[0];
        Vec3::y = xyz[1];
        Vec3::z = xyz[2];
#ifdef DEBUG
    }
    else
    {
        Console.warning(MESSAGE_NULLPOINTER("Vec3"));
        Vec3::x = 0;
        Vec3::y = 0;
        Vec3::z = 0;
    }
#endif
}

Vec3::Vec3(Normal n)
{
#ifdef DEBUG
    if(std::isnan(n.x) || std::isnan(n.y) || std::isnan(n.z))
        Console.severe(MESSAGE_NAN("Vec3"));
    if(std::isinf(n.x) || std::isinf(n.y) || std::isinf(n.z))
        Console.severe(MESSAGE_INFINITY("Vec3"));
#endif
    Vec3::x = n.x;
    Vec3::y = n.y;
    Vec3::z = n.z;
}

float Vec3::dot(const Vec3& target) const
{
    return (Vec3::x*target.x+Vec3::y*target.y+Vec3::z*target.z);
}

float Vec3::dot(const Normal& target) const
{
    return (Vec3::x*target.x+Vec3::y*target.y+Vec3::z*target.z);
}

float Vec3::length() const
{
    return sqrtf(Vec3::x*Vec3::x+Vec3::y*Vec3::y+Vec3::z*Vec3::z);
}

float Vec3::lengthSquared() const
{
    return Vec3::x*Vec3::x+Vec3::y*Vec3::y+Vec3::z*Vec3::z;
}

float Vec3::distanceTo(const Vec3& target) const
{
    float x = target.x-Vec3::x;
    float y = target.y-Vec3::y;
    float z = target.z-Vec3::z;

    return sqrtf((x*x)+(y*y)+(z*z));
}

void Vec3::cross(const Vec3& target, Vec3* output) const
{
    output->x = Vec3::y*target.z-Vec3::z*target.y;
    output->y = Vec3::z*target.x-Vec3::x*target.z;
    output->z = Vec3::x*target.y-Vec3::y*target.x;
}

Vec3 Vec3::cross(const Vec3& target) const
{
    return Vec3(Vec3::y*target.z-Vec3::z*target.y,
                Vec3::z*target.x-Vec3::x*target.z,
                Vec3::x*target.y-Vec3::y*target.x);
}

void Vec3::normalize()
{
    float len;
    float len2;
    len2 = Vec3::x*Vec3::x+Vec3::y*Vec3::y+Vec3::z*Vec3::z;
    if(len2>1.f-1E-5f && len2<1.f+1E-5f)
        return;
    else
        len = sqrtf(len2);
#ifdef DEBUG
    if(len == 0)
    {
        Console.critical(MESSAGE_NORMALIZE_ZERO);
        return;
    }
#endif
    len = 1/len;
    Vec3::x *= len;
    Vec3::y *= len;
    Vec3::z *= len;
}

bool Vec3::is_normalized() const
{
    //sqrt(1) = 1 so I don't need the expense of a Vec3::length()
    float len = Vec3::x*Vec3::x+Vec3::y*Vec3::y+Vec3::z*Vec3::z;
    return len>1.f-1E-5f && len<1.f+1E-5f;
}

void Vec3::toArray(float* res) const
{
    res[0] = Vec3::x;
    res[1] = Vec3::y;
    res[2] = Vec3::z;
}

char* Vec3::toString() const
{
    char val1[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val2[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val3[CHAR_ARRAY_SIZE_PER_FLOAT];
    snprintf(val1, sizeof(val1), "%f", (double)Vec3::x);
    snprintf(val2, sizeof(val2), "%f", (double)Vec3::y);
    snprintf(val3, sizeof(val3), "%f", (double)Vec3::z);

    //( + ) + 2 commas + '/0' + "vec3" + 2 space
    int res_len = (int)(11+strlen(val1)+strlen(val2)+strlen(val3));
    char* res = new char[res_len];
    snprintf(res, sizeof(res)*res_len, "vec3(%s, %s, %s)", val1, val2, val3);

    return res;
}

void Vec3::clamp(const Vec3& min, const Vec3& max)
{
    if(Vec3::x<min.x)
        Vec3::x = min.x;
    else if(Vec3::x>max.x)
        Vec3::x = max.x;

    if(Vec3::y<min.y)
        Vec3::y = min.y;
    else if(Vec3::y>max.y)
        Vec3::y = max.y;

    if(Vec3::z<min.z)
        Vec3::z = min.z;
    else if(Vec3::z>max.z)
        Vec3::z = max.z;
}

void Vec3::saturate()
{
    if(Vec3::x<0.0f) Vec3::x = 0.0f;
    else if(Vec3::x>1.0f)Vec3::x = 1.0f;

    if(Vec3::y<0.0f) Vec3::y = 0.0f;
    else if(Vec3::y>1.0f)Vec3::y = 1.0f;

    if(Vec3::z<0.0f) Vec3::z = 0.0f;
    else if(Vec3::z>1.0f)Vec3::z = 1.0f;
}

void Vec3::max(const Vec3& vector2)
{
    float x, y, z;
    if(Vec3::x>vector2.x)
        x = Vec3::x;
    else
        x = vector2.x;

    if(Vec3::y>vector2.y)
        y = Vec3::y;
    else
        y = vector2.y;

    if(Vec3::z>vector2.z)
        z = Vec3::z;
    else
        z = vector2.z;

    Vec3::x = x;
    Vec3::y = y;
    Vec3::z = z;
}

void Vec3::min(const Vec3& vector2)
{
    float x, y, z;
    if(Vec3::x<vector2.x)
        x = Vec3::x;
    else
        x = vector2.x;

    if(Vec3::y<vector2.y)
        y = Vec3::y;
    else
        y = vector2.y;

    if(Vec3::z<vector2.z)
        z = Vec3::z;
    else
        z = vector2.z;

    Vec3::x = x;
    Vec3::y = y;
    Vec3::z = z;
}

void Vec3::reflect(const Vec3& centre)
{
#ifdef DEBUG
    if(!centre.is_normalized())
        Console.warning(MESSAGE_REFLECT_NONORMALIZED);
#endif
    float dot = Vec3::dot(centre);
    Vec3::x -= ((2*dot)*centre.x);
    Vec3::y -= ((2*dot)*centre.y);
    Vec3::z -= ((2*dot)*centre.z);
}

void Vec3::reflect(const Normal& centre)
{
#ifdef DEBUG
    if(!centre.is_normalized())
        Console.warning(MESSAGE_REFLECT_NONORMALIZED);
#endif
    float dot = Vec3::dot(centre);
    Vec3::x -= ((2*dot)*centre.x);
    Vec3::y -= ((2*dot)*centre.y);
    Vec3::z -= ((2*dot)*centre.z);
}

bool Vec3::refract(const Vec3& interface, float eta)
{
#ifdef DEBUG
    if(!interface.is_normalized())
        Console.warning(MESSAGE_REFRACT_NONORMALIZED);
#endif
    const float cosi = Vec3::dot(interface); //cos incident
    const float sin2i = ::max(0.f, (1.f-cosi*cosi));
    const float sin2t = sin2i*eta*eta;
    if(sin2t>1.f) //bail out if tir
        return false;
    else
    {
        Vec3 retval;
        const float cos2t = 1.f-sin2t; //cos2t transmitted
        const float cost = sqrtf(cos2t);
        *this = -*this*eta;
        Vec3::operator+=(interface*(cosi*eta-cost));
        return true;
    }
}

bool Vec3::refract(const Normal& interface, float eta)
{
#ifdef DEBUG
    if(!interface.is_normalized())
        Console.warning(MESSAGE_REFRACT_NONORMALIZED);
#endif
    const float cosi = Vec3::dot(interface); //cos incident
    const float sin2i = ::max(0.f, (1.f-cosi*cosi));
    const float sin2t = sin2i*eta*eta;
    if(sin2t>1.f) //bail out if tir
        return false;
    else
    {
        Vec3 retval;
        const float cos2t = 1.f-sin2t; //cos2t transmitted
        const float cost = sqrtf(cos2t);
        *this = -*this*eta;
        Vec3::operator+=((Vec3)(interface*(cosi*eta-cost)));
        return true;
    }
}

//------ Operators -------------------------------------------------------------

Vec3 Vec3::operator+(const Vec3& v) const
{
    return Vec3(Vec3::x+v.x, Vec3::y+v.y, Vec3::z+v.z);
}

Vec3 Vec3::operator+(float f) const
{
    return Vec3(Vec3::x+f, Vec3::y+f, Vec3::z+f);
}

void Vec3::operator+=(const Vec3& v)
{
    Vec3::x += v.x;
    Vec3::y += v.y;
    Vec3::z += v.z;
}

void Vec3::operator+=(float f)
{
    Vec3::x += f;
    Vec3::y += f;
    Vec3::z += f;
}

Vec3 Vec3::operator-(const Vec3& v) const
{
    return Vec3(Vec3::x-v.x, Vec3::y-v.y, Vec3::z-v.z);
}

Vec3 Vec3::operator-(float f) const
{
    return Vec3(Vec3::x-f, Vec3::y-f, Vec3::z-f);
}

void Vec3::operator-=(const Vec3& v)
{
    Vec3::x -= v.x;
    Vec3::y -= v.y;
    Vec3::z -= v.z;
}

void Vec3::operator-=(float f)
{
    Vec3::x -= f;
    Vec3::y -= f;
    Vec3::z -= f;
}

Vec3 Vec3::operator*(const Vec3& v) const
{
    return Vec3(Vec3::x*v.x, Vec3::y*v.y, Vec3::z*v.z);
}

Vec3 Vec3::operator*(float f) const
{
    return Vec3(Vec3::x*f, Vec3::y*f, Vec3::z*f);
}

void Vec3::operator*=(const Vec3& v)
{
    Vec3::x *= v.x;
    Vec3::y *= v.y;
    Vec3::z *= v.z;
}

void Vec3::operator*=(float f)
{
    Vec3::x *= f;
    Vec3::y *= f;
    Vec3::z *= f;
}

Vec3 Vec3::operator/(const Vec3& v) const
{
#ifdef DEBUG
    if(v.x == 0 || v.y == 0 || v.z == 0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return Vec3();
    }
#endif
    return Vec3(Vec3::x/v.x, Vec3::y/v.y, Vec3::z/v.z);
}

Vec3 Vec3::operator/(float f) const
{
#ifdef DEBUG
    if(f == 0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return Vec3();
    }
#endif
    return Vec3(Vec3::x/f, Vec3::y/f, Vec3::z/f);
}

void Vec3::operator/=(const Vec3& v)
{
#ifdef DEBUG
    if(v.x == 0 || v.y == 0 || v.z == 0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return;
    }
#endif
    Vec3::x /= v.x;
    Vec3::y /= v.y;
    Vec3::z /= v.z;
}

void Vec3::operator/=(float f)
{
#ifdef DEBUG
    if(f == 0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return;
    }
#endif
    Vec3::x /= f;
    Vec3::y /= f;
    Vec3::z /= f;
}

Vec3 Vec3::operator!() const
{
    return Vec3(-Vec3::x, -Vec3::y, -Vec3::z);
}

Vec3 Vec3::operator-() const
{
    return Vec3(-Vec3::x, -Vec3::y, -Vec3::z);
}

bool Vec3::operator==(const Vec3& v) const
{
    return std::fabs(Vec3::x-v.x)<=FLT_EPSILON &&
           std::fabs(Vec3::y-v.y)<=FLT_EPSILON &&
           std::fabs(Vec3::z-v.z)<=FLT_EPSILON;
}

bool Vec3::operator!=(const Vec3& v) const
{
    return std::fabs(Vec3::x-v.x)>FLT_EPSILON ||
           std::fabs(Vec3::y-v.y)>FLT_EPSILON ||
           std::fabs(Vec3::z-v.z)>FLT_EPSILON;
}

float& Vec3::operator[](int component)
{
    return *(&(Vec3::x)+component);
}

float Vec3::operator[](int component) const
{
    return *(&(Vec3::x)+component);
}

//------------------------------------------------------------------------------

Normal::Normal()
{
    Normal::x = 0;
    Normal::y = 0;
    Normal::z = 0;
}

Normal::Normal(float xyz)
{
#ifdef DEBUG
    if(std::isnan(xyz))
        Console.severe(MESSAGE_NAN("Normal"));
    if(std::isinf(xyz))
        Console.severe(MESSAGE_INFINITY("Normal"));
#endif
    Normal::x = xyz;
    Normal::y = xyz;
    Normal::z = xyz;
}

Normal::Normal(float x, float y, float z)
{
#ifdef DEBUG
    if(std::isnan(x) || std::isnan(y) || std::isnan(z))
        Console.severe(MESSAGE_NAN("Normal"));
    if(std::isinf(x) || std::isinf(y) || std::isinf(z))
        Console.severe(MESSAGE_INFINITY("Normal"));
#endif
    Normal::x = x;
    Normal::y = y;
    Normal::z = z;
}

Normal::Normal(Vec2 xy, float z)
{
#ifdef DEBUG
    if(std::isnan(xy.x) || std::isnan(xy.y) || std::isnan(z))
        Console.severe(MESSAGE_NAN("Normal"));
    if(std::isinf(xy.x) || std::isinf(xy.y) || std::isinf(z))
        Console.severe(MESSAGE_INFINITY("Normal"));
#endif
    Normal::x = xy.x;
    Normal::y = xy.y;
    Normal::z = z;
}

Normal::Normal(const float* xyz)
{
#ifdef DEBUG
    if(xyz != NULL)
    {
        if(std::isnan(xyz[0]) || std::isnan(xyz[1]) || std::isnan(xyz[2]))
            Console.severe(MESSAGE_NAN("Normal"));
        if(std::isinf(xyz[0]) || std::isinf(xyz[1]) ||
           std::isinf(xyz[2]))
            Console.severe(MESSAGE_INFINITY("Normal"));
#endif
        Normal::x = xyz[0];
        Normal::y = xyz[1];
        Normal::z = xyz[2];
#ifdef DEBUG
    }
    else
    {
        Console.warning(MESSAGE_NULLPOINTER("Normal"));
        Normal::x = 0;
        Normal::y = 0;
        Normal::z = 0;
    }
#endif
}

Normal::Normal(const Vec3 v)
{
#ifdef DEBUG
    if(std::isnan(v.x) || std::isnan(v.y) || std::isnan(v.z))
        Console.severe(MESSAGE_NAN("Normal"));
    if(std::isinf(v.x) || std::isinf(v.y) || std::isinf(v.z))
        Console.severe(MESSAGE_INFINITY("Normal"));
#endif
    Normal::x = v.x;
    Normal::y = v.y;
    Normal::z = v.z;
}

float Normal::dot(const Normal& target) const
{
    return
            ((Normal::x*target.x)+(Normal::y*target.y)+(Normal::z*target.z));
}

float Normal::dot(const Vec3& target) const
{
    return
            ((Normal::x*target.x)+(Normal::y*target.y)+(Normal::z*target.z));
}

float Normal::length() const
{
    return std::sqrt(Normal::x*Normal::x+
                     Normal::y*Normal::y+
                     Normal::z*Normal::z);
}

float Normal::lengthSquared() const
{
    return Normal::x*Normal::x+Normal::y*Normal::y+Normal::z*Normal::z;
}

float Normal::distanceTo(const Normal& target) const
{
    float x = target.x-Normal::x;
    float y = target.y-Normal::y;
    float z = target.z-Normal::z;

    return sqrtf((x*x)+(y*y)+(z*z));
}

void Normal::normalize()
{
    float len;
    float len2;
    len2 = Normal::x*Normal::x+Normal::y*Normal::y+Normal::z*Normal::z;
    if(len2>1.f-1E-5f && len2<1.f+1E-5f)
        return;
    else
        len = sqrtf(len2);
#ifdef DEBUG
    if(len == 0)
    {
        Console.critical(MESSAGE_NORMALIZE_ZERO);
        return;
    }
#endif
    len = 1/len;
    Normal::x *= len;
    Normal::y *= len;
    Normal::z *= len;
}

bool Normal::is_normalized() const
{
    float len = x*x+y*y+z*z;
    return len>1.f-1E-5f && len<1.f+1E-5f;
}

void Normal::toArray(float* res) const
{
    res[0] = Normal::x;
    res[1] = Normal::y;
    res[2] = Normal::z;
}

char* Normal::toString() const
{
    char val1[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val2[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val3[CHAR_ARRAY_SIZE_PER_FLOAT];
    snprintf(val1, sizeof(val1), "%f", (double)Normal::x);
    snprintf(val2, sizeof(val2), "%f", (double)Normal::y);
    snprintf(val3, sizeof(val3), "%f", (double)Normal::z);

    //( + ) + 2 comma + '/0' + "Normal" + 2 space
    int res_len = (int)(13+strlen(val1)+strlen(val2)+strlen(val3));
    char* res = new char[res_len];
    snprintf(res, sizeof(res)*res_len, "Normal(%s, %s, %s)", val1, val2, val3);

    return res;
}

void Normal::clamp(const Vec3& min, const Vec3& max)
{
    if(Normal::x<min.x) Normal::x = min.x;
    else if(Normal::x>max.x)Normal::x = max.x;

    if(Normal::y<min.y) Normal::y = min.y;
    else if(Normal::y>max.y)Normal::y = max.y;

    if(Normal::z<min.z) Normal::z = min.z;
    else if(Normal::z>max.z)Normal::z = max.z;
}

void Normal::saturate()
{
    if(Normal::x<0.0f) Normal::x = 0.0f;
    else if(Normal::x>1.0f)Normal::x = 1.0f;

    if(Normal::y<0.0f) Normal::y = 0.0f;
    else if(Normal::y>1.0f)Normal::y = 1.0f;

    if(Normal::z<0.0f) Normal::z = 0.0f;
    else if(Normal::z>1.0f)Normal::z = 1.0f;
}

void Normal::max(const Normal& n)
{
    float x, y, z;
    if(Normal::x>n.x)
        x = Normal::x;
    else
        x = n.x;

    if(Normal::y>n.y)
        y = Normal::y;
    else
        y = n.y;

    if(Normal::z>n.z)
        z = Normal::z;
    else
        z = n.z;

    Normal::x = x;
    Normal::y = y;
    Normal::z = z;
}

void Normal::min(const Normal& n)
{
    float x, y, z;
    if(Normal::x<n.x)
        x = Normal::x;
    else
        x = n.x;

    if(Normal::y<n.y)
        y = Normal::y;
    else
        y = n.y;

    if(Normal::z<n.z)
        z = Normal::z;
    else
        z = n.z;

    Normal::x = x;
    Normal::y = y;
    Normal::z = z;
}

//------ Operators -------------------------------------------------------------

Normal Normal::operator+(const Normal& n) const
{
    return Normal(Normal::x+n.x, Normal::y+n.y, Normal::z+n.z);
}

Normal Normal::operator+(float f) const
{
    return Normal(Normal::x+f, Normal::y+f, Normal::z+f);
}

void Normal::operator+=(const Normal& n)
{
    Normal::x += n.x;
    Normal::y += n.y;
    Normal::z += n.z;
}

void Normal::operator+=(float f)
{
    Normal::x += f;
    Normal::y += f;
    Normal::z += f;
}

Normal Normal::operator-(const Normal& n) const
{
    return Normal(Normal::x-n.x, Normal::y-n.y, Normal::z-n.z);
}

Normal Normal::operator-(float f) const
{
    return Normal(Normal::x-f, Normal::y-f, Normal::z-f);
}

void Normal::operator-=(const Normal& n)
{
    Normal::x -= n.x;
    Normal::y -= n.y;
    Normal::z -= n.z;
}

void Normal::operator-=(float f)
{
    Normal::x -= f;
    Normal::y -= f;
    Normal::z -= f;
}

Normal Normal::operator*(const Normal& n) const
{
    return Normal(Normal::x*n.x, Normal::y*n.y, Normal::z*n.z);
}

Normal Normal::operator*(float f) const
{
    return Normal(Normal::x*f, Normal::y*f, Normal::z*f);
}

void Normal::operator*=(const Normal& n)
{
    Normal::x *= n.x;
    Normal::y *= n.y;
    Normal::z *= n.z;
}

void Normal::operator*=(float f)
{
    Normal::x *= f;
    Normal::y *= f;
    Normal::z *= f;
}

Normal Normal::operator/(const Normal& n) const
{
#ifdef DEBUG
    if(n.x == 0 || n.y == 0 || n.z == 0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return Normal();
    }
#endif
    return Normal(Normal::x/n.x, Normal::y/n.y, Normal::z/n.z);
}

Normal Normal::operator/(float f) const
{
#ifdef DEBUG
    if(f == 0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return Normal();
    }
#endif
    return Normal(Normal::x/f, Normal::y/f, Normal::z/f);
}

void Normal::operator/=(const Normal& n)
{
#ifdef DEBUG
    if(n.x == 0 || n.y == 0 || n.z == 0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return;
    }
#endif
    Normal::x /= n.x;
    Normal::y /= n.y;
    Normal::z /= n.z;
}

void Normal::operator/=(float f)
{
#ifdef DEBUG
    if(f == 0)
    {
        Console.critical(MESSAGE_DIVISIONBY0);
        return;
    }
#endif
    Normal::x /= f;
    Normal::y /= f;
    Normal::z /= f;
}

Normal Normal::operator!() const
{
    return Normal(-Normal::x, -Normal::y, -Normal::z);
}

Normal Normal::operator-() const
{
    return Normal(-Normal::x, -Normal::y, -Normal::z);
}

bool Normal::operator==(const Normal& n) const
{
    return Normal::x == n.x && Normal::y == n.y && Normal::z == n.z;
}

bool Normal::operator!=(const Normal& n) const
{
    return Normal::x != n.x || Normal::y != n.y || Normal::z != n.z;
}

float& Normal::operator[](int component)
{
    return *(&(Normal::x)+component);
}

float Normal::operator[](int component) const
{
    return *(&(Normal::x)+component);
}

//------------------------------------------------------------------------------
