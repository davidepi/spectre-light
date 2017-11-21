#include "renderer.hpp"

//st = sampler type
static void executor(Camera* c,ImageOutput* io,std::mutex* lock,int spp, int st,
              std::stack<Renderer_task>* jobs, Scene* s, LightIntegrator* t);


static void progressBar(std::stack<Renderer_task>* jobs, unsigned long ts,
                        bool& alive);

#define SPECTRE_USE_RANDOM_SAMPLER 0
#define SPECTRE_USE_STRATIFIED_SAMPLER 1

Renderer::Renderer(int w, int h, int spp, const char* o,int th) : film(w,h,o)
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

    if(th<1)
        Renderer::numthreads = (int)std::thread::hardware_concurrency();
    else
        Renderer::numthreads = th;
    numthreads = numthreads > 0 ? numthreads : 1;

    //print number of rendering threads
    char threads[256];
    sprintf(threads,MESSAGE_NUMTHREADS,numthreads);
    Console.log(threads,threads);

    Renderer::spp = spp;
    Renderer::c = NULL;
    Renderer::f = NULL;
    Renderer::t = NULL;
    Renderer::sampler_t = -1;
    Renderer::workers=new std::thread[numthreads];//dflt ctor won't start thread
}

Renderer::~Renderer()
{
    delete c;
    delete f;
    delete t;
    delete[] Renderer::workers;
}

void Renderer::setPerspective(Point3 pos, Point3 target, Vec3 up, float fov)
{
    delete c;
    c = new PerspectiveCamera(&pos,&target,&up,w,h,fov);
}

void Renderer::setOrthographic(Point3 pos, Point3 target, Vec3 up)
{
    delete c;
    c = new OrthographicCamera(&pos,&target,&up,w,h);
}

void Renderer::setPanorama(Point3 pos, Point3 target, Vec3 up)
{
    delete c;
    c = new Camera360(&pos,&target,&up,w,h);
}

void Renderer::setRandomSampler()
{
    Renderer::sampler_t = SPECTRE_USE_RANDOM_SAMPLER;
}

void Renderer::setStratifiedSampler()
{
    int old_spp = Renderer::spp;
    //spp must be a perfect square
    Renderer::spp = (int)sqrtf(old_spp);
    Renderer::spp*=Renderer::spp;
    if(Renderer::spp!=old_spp)
    {
        char errmsg[256];
        snprintf(errmsg,256,MESSAGE_CHANGED_SPP,Renderer::spp);
        Console.notice(errmsg);
    }
    Renderer::sampler_t = SPECTRE_USE_STRATIFIED_SAMPLER;
}

void Renderer::setBoxFilter()
{

    delete f;
    f = new BoxFilter(BOX_FILTER_EXTENT,BOX_FILTER_EXTENT);
    film.setFilter(f);
}

void Renderer::setTentFilter()
{
    delete f;
    f = new TentFilter(TENT_FILTER_EXTENT,TENT_FILTER_EXTENT);
    film.setFilter(f);
}

void Renderer::setGaussianFilter(float sigma)
{
    delete f;
    f = new GaussianFilter(GAUSSIAN_FILTER_EXTENT,GAUSSIAN_FILTER_EXTENT,sigma);
    film.setFilter(f);
}

void Renderer::setMitchellFilter(float b, float c)
{
    delete f;
    f = new MitchellFilter(MITCHELL_FILTER_EXTENT,MITCHELL_FILTER_EXTENT,b,c);
    film.setFilter(f);
}

void Renderer::setLanczosSincFilter(float tau)
{
    delete f;
    f = new LanczosFilter(LANCZOS_FILTER_EXTENT,LANCZOS_FILTER_EXTENT,tau);
    film.setFilter(f);
}

void Renderer::setRayTracer()
{
    delete t;
    t = new RayTracer();
}

void Renderer::setPathTracer()
{
    delete t;
    t = new PathTracer();
}

int Renderer::render(Scene* s)
{
    //too verbose otherwise
    using namespace std::chrono;
    
    //used just for seed generation, WELLrng will be the actual prng
    srand((unsigned int)time(NULL));

    //build the kd-tree, or rebuild it, just to be sure
    s->k.buildTree();

    //checks if the settings are ok
    if (Renderer::c == NULL)
        Console.critical(MESSAGE_MISSING_CAMERA);
    if (Renderer::f == NULL)
        Console.critical(MESSAGE_MISSING_FILTER);
    if (Renderer::t == NULL)
        Console.critical(MESSAGE_MISSING_INTEGRATOR);
    if(Renderer::sampler_t == -1)
        Console.critical(MESSAGE_MISSING_SAMPLER);

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
    steady_clock::time_point a = steady_clock::now();
    RendererProgressBar rb(&jobs);
    //create threads
    for(int i=0;i<Renderer::numthreads;i++)
    {
        Renderer::workers[i] = std::thread(executor,c,&film,&jobs_mtx,spp,
                                           sampler_t,&jobs,s,Renderer::t);
    }

    //wait for them to finish
    for(int i=0;i<Renderer::numthreads;i++)
    {
        Renderer::workers[i].join();
    }
    rb.kill();
    steady_clock::time_point b = steady_clock::now();
    
    //all these things to print the elapsed time!
    //sizeof because MSVC cannot resolve strlen a compile time
    char endmsg[sizeof(MESSAGE_RENDERTIME)/sizeof(char)+MAX_TIME_FORMAT_LENGTH];
    char elapsed_formatted[16];
    formatSeconds((int)duration_cast<seconds>(b-a).count(),elapsed_formatted);
    sprintf(endmsg, MESSAGE_RENDERTIME,elapsed_formatted);
    Console.log(endmsg,NULL);
    
    Console.log(MESSAGE_IMAGEO,NULL);
    //save the image
    Renderer::film.saveImage();
    Console.log(MESSAGE_BYE,NULL);
	
    return 0;
}

void executor(Camera* c, ImageOutput* io, std::mutex* lock, int spp, int st,
              std::stack<Renderer_task>* jobs, Scene* s, LightIntegrator* t)
{
    //generate seed for WELLrng. Constant WELL_R is inside wellrng.h
    unsigned int WELLseed[WELL_R];
#ifndef DEBUG
    for(int i=0;i<WELL_R;i++)
        //assuming RAND_MAX=2^31, sum two randoms
        WELLseed[i] = ((unsigned int)rand()+(unsigned int)rand());
#else
#ifdef FORCED_SEED
    Console.log("Forced seed",NULL);
    for(int i=0;i<WELL_R;i++)
        //used defined seed
        WELLseed[i] = FORCED_SEED;
#else
    int debug_seed = (int)rand();
    char seedstr[128];
    snprintf(seedstr, 128, "Seed is %d",debug_seed);
    Console.log(seedstr,NULL);
    for(int i=0;i<WELL_R;i++)
        //debug seed is easier to replicate, but really predictable
        WELLseed[i] = debug_seed;
#endif
#endif
    
    bool done = false;
    Renderer_task todo;
    Sampler* sam;
    Sample* samples = new Sample[spp];
    Ray r;
	ExecutorData ex;
    Spectrum radiance;
    HitPoint h;
    OcclusionTester ot(s);
    while(!done)
    {
        lock->lock();
        //check if the job queue is empty
        if(jobs->empty())
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
        
	for(int i=0;i<WELL_R;i++) //alterate the seed
	    WELLseed[i]++; //Predictable, but it is only a seed

        switch(st)
        {
            case SPECTRE_USE_RANDOM_SAMPLER:
                sam = new RandomSampler(todo.startx, todo.endx, todo.starty,
                                        todo.endy, spp, WELLseed);
                break;
            case SPECTRE_USE_STRATIFIED_SAMPLER:
            default:
                sam = new StratifiedSampler(todo.startx, todo.endx, todo.starty,
                                      todo.endy, spp, WELLseed,
                                      JITTERED_SAMPLER);
                break;
        }
		ex.startx = todo.startx;
		ex.starty = todo.starty;
		ex.endx = todo.endx;
		ex.endy = todo.endy;
        while(sam->getSamples(samples))
        {
            for(int i=0;i<spp;i++)
            {
                c->createRay(&(samples[i]), &r);
                if (s->k.intersect(&r, &h))
                    radiance = t->radiance(s, &h, &r, sam, &ot);
                    
                else
                    radiance = SPECTRUM_BLACK;
                
                ColorXYZ cx = radiance.toXYZ();
                io->addPixel(&(samples[i]), cx, &ex);
            }
        }
		io->deferredAddPixel(&ex);
        delete sam;
    }
    delete[] samples;
	io->forceAddPixel(&ex);
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
    //if alive variable is set when the thread is not sleeping it will print
    //some garbage.
    
    //However this is fine, no point in setting a mutex every time just to
    //avoid a bad print
    Console.progressBarDone();
}

void progressBar(std::stack<Renderer_task>* jobs, unsigned long ts, bool& alive)
{
    unsigned long remaining;
    const unsigned long total_size = ts;
    float done;
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
}
