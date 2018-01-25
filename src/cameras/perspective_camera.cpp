//author: Davide Pizzolotto
//license: GNU GPLv3

#include "perspective_camera.hpp"

PerspectiveCamera::PerspectiveCamera(const Point3* pos, const Point3* target,
                                     const Vec3* up, int width, int heigth,
                                     float fov)
: Camera(pos,target,up,width,heigth)
{
    float f = 1000.0f; //far plane
    float n = 0.01f; //near plane
    float inv_aspect_ratio = 1.f/tanf(fov/2.f);
    float values[16] = {inv_aspect_ratio, 0,  0,  0,
                        0, inv_aspect_ratio,  0,  0,
                        0, 0, f/(f-n), (-f*n)/(f-n),
                        0, 0,  1,  0};

    Matrix4 camera2screen(values);
    Matrix4 screen2camera;
    camera2screen.inverse(&screen2camera);

    float aspect_ratio = (float)width/(float)heigth;
    float bounds[4]; //screen-space bounds
    if(aspect_ratio > 1) //horizontal image
    {
        bounds[0] = -aspect_ratio; //minx
        bounds[1] = aspect_ratio;  //maxx
        bounds[2] = -1.f;//miny
        bounds[3] = 1.f; //maxy
    }
    else
    {
        bounds[0] = -1.f; //minx
        bounds[1] = 1.f;  //maxx
        bounds[2] = -1.f/aspect_ratio;//miny
        bounds[3] = 1.f/aspect_ratio; //maxy
    }
    //Raster space to screen space values, see Orthographic camera
    values[0] = (bounds[1]-bounds[0])/width;
    values[1] = 0;
    values[2] = 0;
    values[3] = bounds[0];
    values[4] = 0;
    values[5] = (bounds[2]-bounds[3])/heigth;
    values[6] = 0;
    values[7] = bounds[3];
    values[8] = 0;
    values[9] = 0;
    values[10] = 1.f;
    values[11] = 0;
    values[12] = 0;
    values[13] = 0;
    values[14] = 0;
    values[15] = 1.f;

    Matrix4 raster2screen(values);
    raster2camera.set_identity();
    raster2camera*= screen2camera;
    raster2camera *= raster2screen;
}

void PerspectiveCamera::create_ray(Sample* sample, Ray* ray)const
{
    ray->origin = camera2world * Point3(0,0,0);
    Point3 dir = raster2camera * Point3(sample->posx,sample->posy,0);
    ray->direction = camera2world * normalize(Vec3(dir.x,dir.y,dir.z));
}
