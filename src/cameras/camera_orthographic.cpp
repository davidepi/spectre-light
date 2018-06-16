//author: Davide Pizzolotto
//license: GNU GPLv3

#include "camera_orthographic.hpp"

CameraOrthographic::CameraOrthographic(const Point3* pos, const Point3* target,
                                       const Vec3* up, int width, int height)
        :Camera(pos, target, up, width, height)
{
    raster2world = camera2world;

    float aspect_ratio = (float)width/(float)height;
    float bounds[4]; //screen-space bounds
    if(aspect_ratio>1) //horizontal image
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
    float f = 1.0f; //far plane
    float n = 0.0f; //near plane
    float values[16] = {1, 0, 0, 0,  //already inverted camera
                        0, 1, 0, 0,  //screen to camera
                        0, 0, f-n, n,
                        0, 0, 0, 1};

    Matrix4 screen2camera(values);

    //Screen to Raster S = scale, T = translate
    //S(xres,yres,1) * S(1/(b[1]-b[0]),1/(b[2]-b[3]),1) * T(-b[0],-b[3],0)

    //[xres/(b[1]-b[0]) 0               0          -b[0]*xres/(b[1]-b[0])]
    //[0           yres/(b[2]-b[3])     0          -b[3]*yres/(b[2]-b[3])]
    //[0                0               1                    0          ]
    //[0                0               0                    1          ]

    //Raster to Screen
    //[(b[1]-b[0])/xres     0           0                   b[0]         ]
    //[      0       (b[2]-b[3])/yres   0                   b[3]         ]
    //[      0              0           1                     0          ]
    //[      0              0           0                     1          ]

    values[0] = (bounds[1]-bounds[0])/width;
    values[3] = bounds[0];
    values[5] = (bounds[2]-bounds[3])/height;
    values[7] = bounds[3];
    values[10] = 1.f;
    values[11] = 0.f;

    Matrix4 raster2screen(values);
    raster2world *= screen2camera;
    raster2world *= raster2screen;
    Matrix4 raster2camera;
    raster2camera.set_identity();
    raster2camera *= screen2camera;
    raster2camera *= raster2screen;
    dx = raster2camera*Vec3(1, 0, 0);
    dy = raster2camera*Vec3(0, 1, 0);
}

void CameraOrthographic::create_ray(const Sample* spl, Ray* ray, Ray* rx,
                                    Ray* ry) const
{
    ray->origin = raster2world*Point3(spl->posx, spl->posy, 0);
    //TODO: check this, probably raster 2 world is not correct
    rx->origin = raster2world*Point3(spl->posx+dx.x, spl->posy+dx.y, dx.z);
    ry->origin = raster2world*Point3(spl->posx+dy.x, spl->posy+dy.y, dy.z);
    ray->direction = camera2world*Vec3(0, 0, 1);
    rx->direction = ray->direction;
    ry->direction = ray->direction;
}

void CameraOrthographic::create_single_ray(const Sample* sample, Point3* origin,
                                           Vec3* direction) const
{
    *origin = raster2world*Point3(sample->posx, sample->posy, 0);
    *direction = camera2world*Vec3(0, 0, 1);
}
