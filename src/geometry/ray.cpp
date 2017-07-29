#include "ray.hpp"

Ray::Ray() : origin(), direction()
{
    Ray::ricochet = 0;
}

Ray::Ray(const Point3 o, const Vec3 d)
    :origin(o.x, o.y, o.z), direction(d.x, d.y, d.z)
{
    Ray::ricochet = 0;
}

Ray::Ray(const Point3 origin, const Vec3 direction, unsigned char bounces)
    :origin(origin), direction(direction)
{
    Ray::ricochet = 0;
}

Ray::Ray(float ox, float oy, float oz, float dx, float dy, float dz)
    :origin(ox,oy,oz), direction(dx,dy,dz)
{
    Ray::ricochet = 0;
}

Point3 Ray::apply(float t)const
{
    //return Ray::o + Ray::d * t;
    return Point3(origin.x+direction.x*t, origin.y+direction.y*t,
                  origin.z+direction.z*t);
}
