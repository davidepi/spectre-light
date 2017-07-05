#include "renderer.hpp"

void executor(Camera* c, ImageOutput* io, std::mutex* lock, int spp,
              std::stack<Renderer_task>* jobs, Scene* s);

Renderer::Renderer(int w, int h, int spp, const char* o) : film(w,h,o)
{
    Renderer::w = w;
    Renderer::h = h;
    Renderer::spp = spp;
    Renderer::numthreads = (int)std::thread::hardware_concurrency();
    numthreads = numthreads > 0 ? numthreads : 1;
    Renderer::c = NULL;
    Renderer::f = NULL;
}

Renderer::~Renderer()
{
    if(Renderer::c != NULL)
        delete c;
    if(Renderer::f != NULL)
        delete f;
}

void Renderer::setPerspective(Point3 pos, Point3 target, Vec3 up, float fov)
{
    if(Renderer::c != NULL)
        delete c;
    c = new PerspectiveCamera(&pos,&target,&up,w,h,fov);
}

void Renderer::setOrthographic(Point3 pos, Point3 target, Vec3 up)
{
    if(Renderer::c != NULL)
        delete c;
    c = new OrthographicCamera(&pos,&target,&up,w,h);
}

void Renderer::setBoxFilter()
{

    if(Renderer::f != NULL)
        delete f;
    f = new BoxFilter(BOX_FILTER_EXTENT,BOX_FILTER_EXTENT);
}

void Renderer::setTentFilter()
{
    if(Renderer::f != NULL)
        delete f;
    f = new TentFilter(TENT_FILTER_EXTENT,TENT_FILTER_EXTENT);
}

void Renderer::setGaussianFilter(float sigma)
{
    if(Renderer::f != NULL)
        delete f;
    f = new GaussianFilter(GAUSSIAN_FILTER_EXTENT,GAUSSIAN_FILTER_EXTENT,sigma);
}

void Renderer::setMitchellFilter(float b, float c)
{
    if(Renderer::f != NULL)
        delete f;
    f = new MitchellFilter(MITCHELL_FILTER_EXTENT,MITCHELL_FILTER_EXTENT,b,c);
}

void Renderer::setLanczosSincFilter(float tau)
{
    if(Renderer::f != NULL)
        delete f;
    f = new LanczosFilter(LANCZOS_FILTER_EXTENT,LANCZOS_FILTER_EXTENT,tau);
}

int Renderer::render(Scene* s)
{
    if(Renderer::c == NULL)
    {
        Console.severe(MESSAGE_MISSING_CAMERA);
        return 1;
    }
    if(Renderer::f == NULL)
    {
        Console.severe(MESSAGE_MISSING_FILTER);
    }
}

void executor(Camera* c, ImageOutput* io, std::mutex* lock, int spp,
              std::stack<Renderer_task>* jobs, Scene* s)
{
    bool done = false;
    Renderer_task todo;
    Sample sample;
    Ray r;
    Color radiance;
    Asset* h;
    while(!done)
    {
        lock->lock();
        if(jobs->size() == 0)
        {
            lock->unlock();
            done = true;
            continue;
        }
        else
        {
            todo = jobs->top();
            jobs->pop();
            lock->unlock();
        }
        unsigned int* seed = (unsigned int*) &todo; //TODO: maybe change this
        StratifiedSampler sam(todo.startx,todo.endx,todo.starty,todo.endy,spp,
                              seed, true);
        while(sam.getSamples(&sample))
        {
            c->createRay(&sample,&r);
            //TODO: compute actual radiance instead of these lines
            if(s->k.intersect(&r,h))
            {
                radiance.r = 1;
                radiance.g = 1;
                radiance.b = 1;
            }
            else
            {
                radiance.r = 0;
                radiance.g = 0;
                radiance.b = 0;
            }
            //end
            io->addPixel(&sample,&radiance);
        }
    }
}