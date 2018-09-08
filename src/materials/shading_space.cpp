//author: Davide Pizzolotto
//license: GNU GPLv3

#include "shading_space.hpp"

ShadingSpace::ShadingSpace(const HitPoint* hp)
        :s(hp->dpdu), n(hp->normal_h)
{
    t = cross(Vec3(n), s).normalize();
}

Vec3 ShadingSpace::to_world(const Vec3& shading) const
{
    return Vec3(s.x*shading.x+t.x*shading.y+n.x*shading.z,
                s.y*shading.x+t.y*shading.y+n.y*shading.z,
                s.z*shading.x+t.z*shading.y+n.z*shading.z).normalize();
}

Vec3 ShadingSpace::to_shading(const Vec3& world) const
{
    return Vec3(dot(world, s), dot(world, t), dot(world, n)).normalize();
}
