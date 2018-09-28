//author: Davide Pizzolotto
//license: GNU GPLv3

#include "camera.hpp"

Camera::Camera(const Point3& pos, const Point3& target, const Vec3& up,
               int, int)
{
    camera2world.set_lookAt_inverse(pos, target, up);
}

void Camera::create_ray(const Sample* sample, Ray* ray) const
{
    create_single_ray(sample, &(ray->origin), &(ray->direction));
}

void Camera::create_ray(const Sample* sample, Ray* ray, Ray* rx, Ray* ry) const
{
    create_single_ray(sample, &(ray->origin), &(ray->direction));

    //generate x offset
    Sample offsetx = *sample;
    offsetx.posx++;
    create_single_ray(&offsetx, &(rx->origin), &(rx->direction));

    //generate y offset
    Sample offsety = *sample;
    offsety.posy++;
    create_single_ray(&offsety, &(ry->origin), &(ry->direction));
}

void Camera::get_camera2world(Matrix4* cam2world) const
{
    *cam2world = camera2world;
}
