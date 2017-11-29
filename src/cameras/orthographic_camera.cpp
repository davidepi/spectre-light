//author: Davide Pizzolotto
//license: GNU GPLv3

#include "orthographic_camera.hpp"

OrthographicCamera::OrthographicCamera(const Point3* pos,const Point3* target,
                                       const Vec3* up, int width, int height)
: Camera(pos,target,up,width,height)
{
    raster2world = camera2world;
    
    float aspect_ratio = (float)width/(float)height;
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
    float f = 1.0f; //far plane
    float n = 0.0f; //near plane
    float values[16] = {1, 0,  0,  0,  //already inverted camera
                        0, 1,  0,  0,  //screen to camera
                        0, 0, f-n, n,
                        0, 0,  0,  1};
    
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
}

void OrthographicCamera::createRay(Sample* sample, Ray* ray)const
{
    ray->origin = raster2world * Point3(sample->posx,sample->posy,0);
    ray->direction = camera2world * Vec3(0,0,1);
    ray->direction.normalize();
}
