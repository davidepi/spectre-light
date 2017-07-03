//Created,   3 May 2017
//Last Edit  3 Jul 2017

#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "vec3.hpp"
#include "point3.hpp"
#include "console.hpp"
#include "perspective_camera.hpp"
#include "orthographic_camera.hpp"
#include "box_filter.hpp"
#include "tent_filter.hpp"
#include "gaussian_filter.hpp"
#include "mitchell_filter.hpp"
#include "lanczos_filter.hpp"
#include <thread>
#include <stack>

struct Renderer_task;
class Renderer
{
public:
    Renderer(int width, int height, int spp, const char* outputfile);
    ~Renderer();
    void setPerspective(Point3 position, Point3 target, Vec3 up, float fov);
    void setOrthographic(Point3 position, Point3 target, Vec3 up);
    void setBoxFilter();
    void setTentFilter();
    void setGaussianFilter(float falloff);
    void setMitchellFilter(float b, float c);
    void setLanczosSincFilter(float tau);

    int render();

private:
    bool done;
    Camera* c;
    Filter* f;
    ImageOutput film;
    int numthreads;
    int w;
    int h;
    int spp;
    std::stack<Renderer_task> jobs;
    std::mutex jobs_mtx;
};

struct Renderer_task
{
    int startx;
    int endx;
    int starty;
    int endy;
};


#endif
