#include "orthographic_camera.hpp"

OrthographicCamera::OrthographicCamera(const Point3* p,const Point3* t,
                                       const Vec3* u, int w, int h,
                                       const char* o, const float b[4])
: Camera(p,t,u,w,h,o)
{
    float f = 1.0f; //far plane
    float n = 0.1f; //near plane
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
    
    values[0] = (b[1]-b[0])/w;
    values[3] = b[0];
    values[5] = (b[2]-b[3])/h;
    values[7] = b[3];
    values[10] = 1.f;
    values[11] = 0.f;
    
    Matrix4 raster2screen(values);
    raster2world *= screen2camera;
    raster2world *= raster2screen;
}

OrthographicCamera::~OrthographicCamera()
{
    
}

void OrthographicCamera::createRay(Sample *s, Ray *r)const
{
    r->origin = Point3(s->posx,s->posy,0);
    r->direction = Vec3(0,0,1);
    *r = raster2world*(*r);
}
