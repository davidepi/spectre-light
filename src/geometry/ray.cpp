//author: Davide Pizzolotto
//license: GNU GPLv3

#include "ray.hpp"

Ray::Ray()
        :origin(), direction()
{
    Ray::ricochet = 0;
}

Ray::Ray(const Point3& o, const Vec3& d)
        :origin(o), direction(d)
{
    Ray::ricochet = 0;
}

Ray::Ray(float ox, float oy, float oz, float dx, float dy, float dz)
        :origin(ox, oy, oz), direction(dx, dy, dz)
{
    Ray::ricochet = 0;
}

Point3 Ray::apply(float t) const
{
    //return Ray::o + Ray::d * t;
    return Point3(origin.x+direction.x*t, origin.y+direction.y*t,
                  origin.z+direction.z*t);
}

Ray::Ray(Chunk* data)
{
    origin.x = data->pop_float();
    origin.y = data->pop_float();
    origin.z = data->pop_float();
    direction.x = data->pop_float();
    direction.y = data->pop_float();
    direction.z = data->pop_float();
}

void Ray::serialize(Chunk* data) const
{
    data->push_float(origin.x);
    data->push_float(origin.y);
    data->push_float(origin.z);
    data->push_float(direction.x);
    data->push_float(direction.y);
    data->push_float(direction.z);
}
