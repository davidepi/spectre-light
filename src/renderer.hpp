//Created,   3 Jul 2017
//Last Edit  1 Apr 2018

/**
 *  \file renderer.hpp
 *  \brief     Wrapper of cameras, filters, and rendering threads
 *  \details   Given a camera, a filter and a scene performs the rendering
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      1 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "geometry/vec3.hpp"
#include "geometry/point3.hpp"
#include "utility/console.hpp"
#include "cameras/image_film.hpp"
#include "utility/scene.hpp"
#include "cameras/camera.hpp"
#include "samplers/sampler.hpp"
#include "samplers/random_sampler.hpp"
#include "samplers/stratified_sampler.hpp"
#include "integrators/light_integrator.hpp"
#include "settings.h"
#include <thread> //std::thread
#include <stack> //std::stack
#include <chrono> //std::this_thread::sleep_for, platform independent
#include <ctime> //time for srand

/**  \brief Struct containing the coordinates of a sub-image to be rendered
 *
 *  If an image has coordinate (0,0) to (1920,1080), a possible sub-image could
 *  be (32,32) to (64,64). This class stores this sub-image as startx, endx,
 *  starty and endy values
 */
struct Renderer_task
{
    ///The starting x point of the sub-image
    int startx;

    ///The ending x point of the sub-image
    int endx;

    ///The starting y point of the sub-image
    int starty;

    ///The ending y point of the sub-image
    int endy;
};

///Class used to check the progress in the rendering
class RendererProgressBar
{
public:

    /** \brief Default constructor
     *
     * \param[in] jobs The job queue
     */
    RendererProgressBar(std::stack<Renderer_task>* jobs);

    ///Default destructor
    ~RendererProgressBar();

    ///Terminate the listener
    void kill();

private:

    //jobs queue
    std::stack<Renderer_task>* jobs;

    //listener thread
    std::thread listener;

    //used to terminate the thread
    bool alive;
};

/**
 *  \class Renderer renderer.hpp "renderer.hpp"
 *  \brief Wrapper for Cameras and Filters, used to start the rendering threads
 *
 *  The Renderer class is pretty self-explicative, because it it used to render
 *  things. The usual routine consist of creating this class by giving the
 *  desired image size output, setting up the camera and the filter, and then
 *  passing the scene in the render method. This class will handle the threads
 *  creation and the actual rendering, and in the end an image will be saved on
 *  disk, at the path given in the constructor. The actual rendering is
 *  performed by subdividing the original image in sub-images of
 *  SPLIT_SIZE * SPLIT_SIZE pixels, to maximize the cache hit.
 */
class Renderer
{
public:

    /** \brief Default constructor
     *
     *  \param[in] width The width of the output image, in pixels. This value
     *  must be a multiple of SPLIT_SIZE
     *  \param[in] height The height of the output image, in pixels
     *  \param[in] spp The number of samples per pixel. Recall that the higher
     *  the samples number, the lower the noise. The price for this is longer
     *  rendering times.
     *  \param[in] threads If you wish to override the number of rendering
     *  threads, anything below 1 to autodetect
     *  \param[in] output The desired path for the output image
     */
    Renderer(int width,int height,int spp,const char* output,int threads=0);

    ///Default destructor
    ~Renderer();

    /** \brief Set a Camera for this renderer
     *
     *  Inherit the pointer of a Camera passed as input and used it as the
     *  default camera for rendering the scene. As the name implies, the
     *  ownership of the pointer is transfered to the Renderer that will take
     *  care of the Camera deallocation
     *
     *  \param[in] camera A Camera that will be inherited by the renderer
     */
    void inherit_camera(Camera* camera);
    
    /** \brief Set a Sampler for this renderer
     *
     *  This method differs from the others like Renderer::inherit_camera or
     *  Renderer::inherit_filter because multiple sampler are allocated and
     *  deallocated by the renderer while rendering a scene. Thus this method
     *  expects an integer corresponding to the type of sampler that will be
     *  allocated internally by the renderer. The various samplers are defined
     *  in the samplers/sampler.hpp file
     *
     *  \param[in] sampler An integer defining the type of sampler that will be
     *  used by the renderer
     */
    void set_sampler(int sampler);
    
    /** \brief Set a Filter for this renderer
     *
     *  Inherit the pointer of a Filter passed as input and used it as the
     *  filter for filtering the various sampled points. As the name implies,
     *  the ownership of the pointer is transfered to the Renderer that will
     *  take care of the Filter deallocation
     *
     *  \param[in] filter A Filter that will be inherited by the renderer
     */
    void inherit_filter(Filter* filter);
    
    /** \brief Set a LightIntegrator for this renderer
     *
     *  Inherit the pointer of a LightIntegrator passed as input and used it as
     *  the surface integrator to solve the rendering equation. As the name
     *  implies, the ownership of the pointer is transfered to the Renderer that
     *  will take care of the LightIntegrator deallocation
     *
     *  \param[in] integrator A LightIntegrator that will be inherited by the
     *  renderer
     */
    void inherit_integrator(LightIntegrator* integrator);
    
    /** \brief Render the scene
     *
     *  This method, given an input scene, sets up the rendering threads and
     *  perform the rendering. A camera and a filter are needed. The output
     *  image will be saved in the path given in the constructor
     *
     * \param[in] scene The scene that will be rendered
     * \return 0 if everything was ok, 1 otherwise
     */
    int render(Scene* scene);

private:

    //Camera for the renderer
    Camera* camera;

    //Filter for the renderer
    Filter* filter;

    //Actual image
    ImageFilm film;

    //Number of rendering threads
    int numthreads;

    //width of the image
    int width;

    //height of the image
    int height;

    //samples per pixel
    int spp;

    //Sub-image that needs to be computed
    std::stack<Renderer_task> jobs;

    //mutex for the jobs stack
    std::mutex jobs_mtx;

    //working threads
    std::thread* workers;

    //integrator
    LightIntegrator* mc_solver;

    //sampler
    int sampler_t;
};

#endif
