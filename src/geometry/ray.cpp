#include "ray.hpp"

Ray::Ray() : origin(), direction(), minext(0.0f), maxext(INFINITY),
             ricochet(DEFAULT_BOUNCES)
{ }

Ray::Ray(const Point3 o, const Vec3 d)
    :origin(o.x, o.y, o.z), direction(d.x, d.y, d.z),
     minext(0.0f), maxext(INFINITY), ricochet(DEFAULT_BOUNCES)
{ }

Ray::Ray(const Point3 origin, const Vec3 direction, unsigned char bounces)
    :origin(origin), direction(direction), minext(0.0f), maxext(INFINITY),
     ricochet(bounces)
{ }

Ray::Ray(float ox, float oy, float oz, float dx, float dy, float dz)
    :origin(ox,oy,oz), direction(dx,dy,dz), minext(0.0f), maxext(INFINITY),
     ricochet(DEFAULT_BOUNCES)
{ }

Point3 Ray::apply(float t)const
{
    //return Ray::o + Ray::d * t;
    return Point3(origin.x+direction.x*t, origin.y+direction.y*t,
                  origin.z+direction.z*t);
}
