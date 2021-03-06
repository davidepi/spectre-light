//author: Davide Pizzolotto
//license: GNU GPLv3

#include "renderer.hpp"

//st = sampler type
static void executor(Camera* camera, ImageFilm* film, std::mutex* lock, int spp,
                     int sampler_type, std::stack<Renderer_task>* jobs,
                     Scene* scene, LightIntegrator* mc_solver);


static void progressBar(std::stack<Renderer_task>* jobs, unsigned long ts,
                        bool& alive);

Renderer::Renderer(int width, int height, int spp, const char* out,
                   int thread_number):film(width, height, out)
{
    if(width%SPLIT_SIZE)
    {
        Console.severe(MESSAGE_WIDTH_MULTIPLE, SPLIT_SIZE);
        //set w and h as 0 so no image will be rendered
        Renderer::width = 0;
        Renderer::height = 0;
    }
    else
    {
        Renderer::width = width;
        Renderer::height = height;
    }

    if(thread_number<1)
        Renderer::numthreads = (int)std::thread::hardware_concurrency();
    else
        Renderer::numthreads = thread_number;
    numthreads = numthreads>0?numthreads:1;

    //print number of rendering threads
    char threads[256];
    sprintf(threads, MESSAGE_NUMTHREADS, numthreads);
    Console.log(threads, threads);

    Renderer::spp = spp;
    Renderer::camera = NULL;
    Renderer::filter = NULL;
    Renderer::mc_solver = NULL;
    Renderer::sampler_t = -1;
    Renderer::workers = new std::thread[numthreads];//dflt ctor won't start thread
}

Renderer::~Renderer()
{
    delete camera;
    delete filter;
    delete mc_solver;
    delete[] Renderer::workers;
}

void Renderer::inherit_camera(Camera* camera)
{
    Renderer::camera = camera;
}

void Renderer::set_sampler(int sampler)
{
    Renderer::sampler_t = sampler;
}

void Renderer::inherit_filter(Filter* filter)
{
    Renderer::filter = filter;
    Renderer::film.set_filter(filter);
}

void Renderer::inherit_integrator(LightIntegrator* integrator)
{
    Renderer::mc_solver = integrator;
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
    if(Renderer::camera == NULL)
        Console.critical(MESSAGE_MISSING_CAMERA);
    if(Renderer::filter == NULL)
        Console.critical(MESSAGE_MISSING_FILTER);
    if(Renderer::mc_solver == NULL)
        Console.critical(MESSAGE_MISSING_INTEGRATOR);
    if(Renderer::sampler_t == -1)
        Console.critical(MESSAGE_MISSING_SAMPLER);

    //add part of the image as renderer_tasks
    Renderer_task task;
    for(int y = 0; y<height; y += SPLIT_SIZE)
    {
        task.starty = y;
        task.endy = y+SPLIT_SIZE<height?y+SPLIT_SIZE:height;
        for(int x = 0; x<width; x += SPLIT_SIZE)
        {
            task.startx = x;
            task.endx = x+SPLIT_SIZE;
            jobs.push(task);
        }
    }
    steady_clock::time_point a = steady_clock::now();
    RendererProgressBar progress_bar(&jobs);
    //create threads
    for(int i = 0; i<Renderer::numthreads; i++)
    {
        Renderer::workers[i] = std::thread(executor, camera, &film, &jobs_mtx,
                                           spp,
                                           sampler_t, &jobs, s,
                                           Renderer::mc_solver);
    }

    //wait for them to finish
    for(int i = 0; i<Renderer::numthreads; i++)
    {
        Renderer::workers[i].join();
    }
    progress_bar.kill();
    steady_clock::time_point b = steady_clock::now();

    //all these things to print the elapsed time!
    //sizeof because MSVC cannot resolve strlen a compile time
    char endmsg[sizeof(MESSAGE_RENDERTIME)/sizeof(char)+MAX_TIME_FORMAT_LENGTH];
    char elapsed_formatted[MAX_TIME_FORMAT_LENGTH];
    format_seconds((int)duration_cast<seconds>(b-a).count(), elapsed_formatted);
    sprintf(endmsg, MESSAGE_RENDERTIME, elapsed_formatted);
    Console.log(endmsg, NULL);

    Console.log(MESSAGE_IMAGEO, NULL);
    //save the image
    Renderer::film.save_image();
    Console.log(MESSAGE_BYE, NULL);

    return 0;
}

void executor(Camera* camera, ImageFilm* film, std::mutex* lock, int spp,
              int sampler_type, std::stack<Renderer_task>* jobs, Scene* scene,
              LightIntegrator* mc_solver)
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
    snprintf(seedstr, 128, "Seed is %d", debug_seed);
    Console.log(seedstr, NULL);
    for(int i = 0; i<WELL_R; i++)
        //debug seed is easier to replicate, but really predictable
        WELLseed[i] = debug_seed;
#endif
#endif

    bool done = false;
    Renderer_task todo;
    Sampler* sam;
    Sample* samples = new Sample[spp];
    Ray r;
    Ray rx;
    Ray ry;
    ExecutorData ex;
    Spectrum radiance;
    HitPoint h;
    OcclusionTester ot(scene);
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

        for(int i = 0; i<WELL_R; i++) //alterate the seed
            WELLseed[i]++; //Predictable, but it is only a seed

        switch(sampler_type)
        {
            case SPECTRE_SAMPLER_RANDOM:
                sam = new SamplerRandom(todo.startx, todo.endx, todo.starty,
                                        todo.endy, spp, WELLseed);
                break;
            case SPECTRE_SAMPLER_STRATIFIED:
            default:
                sam = new SamplerStratified(todo.startx, todo.endx, todo.starty,
                                            todo.endy, spp, WELLseed,
                                            JITTERED_SAMPLER);
                break;
        }
        ex.startx = todo.startx;
        ex.starty = todo.starty;
        ex.endx = todo.endx;
        ex.endy = todo.endy;
        while(sam->get_samples(samples))
        {
            for(int i = 0; i<spp; i++)
            {
                camera->create_ray(&(samples[i]), &r, &rx, &ry);
                if(scene->k.intersect(&r, &h))
                {
                    calculate_differentials(&h, &rx, &ry);
                    radiance = mc_solver->radiance(scene, &h, &r, sam, &ot);
                }
                else
                    radiance = SPECTRUM_BLACK;

                ColorXYZ cx = radiance.to_xyz();
                film->add_pixel(&(samples[i]), cx, &ex);
            }
        }
        film->add_pixel_deferred(&ex);
        delete sam;
    }
    delete[] samples;
    film->add_pixel_forced(&ex);
}

RendererProgressBar::RendererProgressBar(std::stack<Renderer_task>* jobs)
{
    RendererProgressBar::jobs = jobs;
    RendererProgressBar::alive = true;
    RendererProgressBar::listener = std::thread(progressBar, jobs, jobs->size(),
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
    Console.progress_bar_done();
}

void progressBar(std::stack<Renderer_task>* jobs, unsigned long jobs_no,
                 bool& alive)
{
    unsigned long remaining;
    float done;
    time_t start_time = time(NULL); //Precision not required for an eta
    time_t current_time;
    time_t eta;
    while(alive)
    {
        remaining = jobs->size(); //I don't care about dirty reads, it's an
        current_time = time(NULL); //eta, I cannot block n threads for an eta
        done = (float)(jobs_no-remaining)/(float)jobs_no;
        eta = (time_t)((float)(current_time-start_time)/(jobs_no-remaining)*
                       remaining);
        //avoid garbage values... it is useless, but it runs once per second...
        if(eta>0)
            Console.progress_bar(done, (float)eta);
        std::this_thread::sleep_for
                (std::chrono::seconds(PROGRESS_BAR_UPDATE_SECONDS));
    }
}
