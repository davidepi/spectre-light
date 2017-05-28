#include "perspective_camera.hpp"

PerspectiveCamera::PerspectiveCamera(const Point3* p,const Point3* t,
                                     const Vec3* u, int w, int h, const char* o,
                                     const float b[4], float fov)
: Camera(p,t,u,w,h,o)
{
    float f = 1000.0f; //far plane
    float n = 0.1f; //near plane
    float values[16] = {1.f/tanf(fov/2), 0,  0,  0,  //already inverted camera
                        0, 1.f/tanf(fov/2),  0,  0,  //screen to camera
                        0, 0, f/(f-n), (-f*n)/(f-n),
                        0, 0,  1,  0};
    
    Matrix4 camera2screen(values);
    Matrix4 screen2camera;
    camera2screen.inverse(&screen2camera);
    
    //Raster space to screen space values, see Orthographic camera
    values[0] = (b[1]-b[0])/w;
    values[1] = 0;
    values[2] = 0;
    values[3] = b[0];
    values[4] = 0;
    values[5] = (b[2]-b[3])/h;
    values[6] = 0;
    values[7] = b[3];
    values[8] = 0;
    values[9] = 0;
    values[10] = 1.f;
    values[11] = 0;
    values[12] = 0;
    values[13] = 0;
    values[14] = 0;
    values[15] = 1.f;
    
    Matrix4 raster2screen(values);
    raster2world *= screen2camera;
    raster2world *= raster2screen;
}

PerspectiveCamera::~PerspectiveCamera()
{
    
}

void PerspectiveCamera::createRay(Sample *s, Ray *r)const
{
    r->origin = Point3(s->posx,s->posy,0);
    r->direction = Vec3(0,0,1);
    *r = raster2world*(*r);
}
