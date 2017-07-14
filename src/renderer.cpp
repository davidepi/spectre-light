#include "renderer.hpp"

static void executor(Camera* c, ImageOutput* io, std::mutex* lock, int spp,
              std::stack<Renderer_task>* jobs, Scene* s);


static void progressBar(std::stack<Renderer_task>* jobs, unsigned long ts,
                        bool& alive);

Renderer::Renderer(int w, int h, int spp, const char* o) : film(w,h,o)
{
    if(w%SPLIT_SIZE)
    {
        char errmsg[256];
        snprintf(errmsg,256,MESSAGE_WIDTH_MULTIPLE,SPLIT_SIZE);
        Console.severe(errmsg);
        //set w and h as 0 so no image will be rendered
        Renderer::w = 0;
        Renderer::h = 0;
    }
    else
    {
        Renderer::w = w;
        Renderer::h = h;
    }
    Renderer::spp = spp;
    Renderer::numthreads = (int)std::thread::hardware_concurrency();

    //print number of rendering threads
    char threads[256];
    sprintf(threads,MESSAGE_NUMTHREADS,numthreads);
    Console.log(threads,threads);

    numthreads = numthreads > 0 ? numthreads : 1;
    Renderer::c = NULL;
    Renderer::f = NULL;
    Renderer::workers=new std::thread[numthreads];//dflt ctor won't start thread
}

Renderer::~Renderer()
{
    if(Renderer::c != NULL)
        delete c;
    if(Renderer::f != NULL)
        delete f;
    delete[] Renderer::workers;
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
    film.setFilter(f);
}

void Renderer::setTentFilter()
{
    if(Renderer::f != NULL)
        delete f;
    f = new TentFilter(TENT_FILTER_EXTENT,TENT_FILTER_EXTENT);
    film.setFilter(f);
}

void Renderer::setGaussianFilter(float sigma)
{
    if(Renderer::f != NULL)
        delete f;
    f = new GaussianFilter(GAUSSIAN_FILTER_EXTENT,GAUSSIAN_FILTER_EXTENT,sigma);
    film.setFilter(f);
}

void Renderer::setMitchellFilter(float b, float c)
{
    if(Renderer::f != NULL)
        delete f;
    f = new MitchellFilter(MITCHELL_FILTER_EXTENT,MITCHELL_FILTER_EXTENT,b,c);
    film.setFilter(f);
}

void Renderer::setLanczosSincFilter(float tau)
{
    if(Renderer::f != NULL)
        delete f;
    f = new LanczosFilter(LANCZOS_FILTER_EXTENT,LANCZOS_FILTER_EXTENT,tau);
    film.setFilter(f);
}

int Renderer::render(Scene* s)
{
    //used just for seed generation, WELLrng will be the actual prng
    srand(time(NULL));

    //build the kd-tree, or rebuild it, just to be sure
    s->k.buildTree();

    //checks if the camera and the filter are set
    if (Renderer::c == NULL)
    {
        Console.severe(MESSAGE_MISSING_CAMERA);
        return 1;
    }
    if (Renderer::f == NULL)
    {
        Console.severe(MESSAGE_MISSING_FILTER);
        return 1;
    }

    //add part of the image as renderer_tasks
    Renderer_task task;
    for(int y=0;y<h;y+=SPLIT_SIZE)
    {
        task.starty = y;
        task.endy = y+SPLIT_SIZE<h?y+SPLIT_SIZE:h;
        for(int x=0;x<w;x+=SPLIT_SIZE)
        {
            task.startx = x;
            task.endx = x+SPLIT_SIZE;
            jobs.push(task);
        }
    }
    RendererProgressBar rb(&jobs);
    //create threads
    for(int i=0;i<Renderer::numthreads;i++)
    {
        Renderer::workers[i] = std::thread(executor,c,&film,&jobs_mtx,spp,
                                           &jobs,s);
    }

    //wait for them to finish
    for(int i=0;i<Renderer::numthreads;i++)
    {
        Renderer::workers[i].join();
    }
    rb.kill();
    //save the image
    Renderer::film.saveImage();

    return 0;
}

void executor(Camera* c, ImageOutput* io, std::mutex* lock, int spp,
              std::stack<Renderer_task>* jobs, Scene* s)
{
    //generate seed for WELLrng. Constant WELL_R is inside wellrng.h
    unsigned int WELLseed[WELL_R];
    for(int i=0;i<WELL_R;i++)
    {
        //assuming RAND_MAX=2^31, sum two randoms and xor them with a third one
        WELLseed[i] = ((unsigned int)rand()+(unsigned int)rand()) ^ rand();
    }
    bool done = false;
    Renderer_task todo;
    Sample sample;
    Ray r;
    Color radiance;
    HitPoint h;
    while(!done)
    {
        lock->lock();
        //check if the job queue is empty
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
        StratifiedSampler sam(todo.startx,todo.endx,todo.starty,todo.endy,spp,
                              WELLseed, JITTERED_SAMPLER);
        while(sam.getSamples(&sample))
        {
            c->createRay(&sample,&r);
            //TODO: compute actual radiance instead of these lines
            if(s->k.intersect(&r,&h))
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

RendererProgressBar::RendererProgressBar(std::stack<Renderer_task> *jobs)
{
    RendererProgressBar::jobs = jobs;
    RendererProgressBar::alive = true;
    RendererProgressBar::listener=std::thread(progressBar,jobs,jobs->size(),
                                              std::ref(alive));
}

RendererProgressBar::~RendererProgressBar()
{
    RendererProgressBar::alive = false;
    RendererProgressBar::listener.join();
}

void RendererProgressBar::kill()
{
    RendererProgressBar::alive = false;
}

void progressBar(std::stack<Renderer_task>* jobs, unsigned long ts, bool& alive)
{

    unsigned long remaining;
    const unsigned long total_size = ts;
    float done = 0.f;
    time_t start_time = time(NULL); //Precision not required for an eta
    time_t current_time;
    time_t eta;
    while(alive)
    {
        remaining = jobs->size(); //I don't care about dirty reads, it's an
        current_time = time(NULL); //eta, I cannot block n threads for an eta
        done = (float)(total_size-remaining)/(float)total_size;
        eta = (time_t)((float)(current_time-start_time)/(total_size-remaining)*
                remaining);
        Console.progressBar(done,eta);
        std::this_thread::sleep_for
                (std::chrono::seconds(PROGRESS_BAR_UPDATE_SECONDS));
    }
    Console.progressBarDone();
}