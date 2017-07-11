//Created,   3 Jul 2017
//Last Edit 11 Jul 2017

/**
 *  \file renderer.hpp
 *  \brief     Wrapper of cameras, filters, and rendering threads
 *  \details   Given a camera, a filter and a scene performs the rendering
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      11 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "geometry/vec3.hpp"
#include "geometry/point3.hpp"
#include "utility/console.hpp"
#include "cameras/perspective_camera.hpp"
#include "cameras/orthographic_camera.hpp"
#include "samplers/box_filter.hpp"
#include "samplers/tent_filter.hpp"
#include "samplers/gaussian_filter.hpp"
#include "samplers/mitchell_filter.hpp"
#include "samplers/lanczos_filter.hpp"
#include "utility/scene.hpp"
#include "samplers/stratified_sampler.hpp"
#include "settings.h"
#include <thread> //std::thread
#include <stack> //std::stack
#include <time.h> //time for srand

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
     *  \param[in] outputfile The desired path for the output image
     */
    Renderer(int width, int height, int spp, const char* outputfile);

    ///Default destructor
    ~Renderer();

    /** \brief Create a perspective camera for this renderer
     *
     *  More info in the perspective_camera.hpp file
     *
     *  \param[in] position The position of the camera
     *  \param[in] target The target of the camera
     *  \param[in] up A vector representing the up direction for the camera
     *  \param[in] fov The field of view, in radians
     */
    void setPerspective(Point3 position, Point3 target, Vec3 up, float fov);

    /** \brief Create an orthographic camera for this renderer
     *
     *  More info in the orthographic_camera.hpp file
     *
     *  \param[in] position The position of the camera
     *  \param[in] target The target of the camera
     *  \param[in] up A vector representing the up direction for the camera
     */
    void setOrthographic(Point3 position, Point3 target, Vec3 up);

    /** \brief Set a box filter for the computed radiance values
     *
     *  More info in the box_filter.hpp file. The used filter extents are
     *  defined in settings.h
     */
    void setBoxFilter();

    /** \brief Set a tent filter for the computed radiance values
     *
     *  More info in the tent_filter.hpp file. The used filter extents are
     *  defined in settings.h
     */
    void setTentFilter();

    /** \brief Set a gaussian filter for the computed radiance values
     *
     *  More info in the gaussian_filter.hpp file. The used filter extents are
     *  defined in settings.h
     *
     *  \param[in] falloff The falloff for the gaussian filter
     */
    void setGaussianFilter(float falloff);

    /** \brief Set a Mitchell-Netravali filter for the computed radiance values
     *
     *  More info in the mitchell_filter.hpp file. The used filter extents are
     *  defined in settings.h
     *
     *  \param[in] b The B parameter for the mitchell filter equations
     *  \param[in] c The C parameter for the mitchell filter equations
     */
    void setMitchellFilter(float b, float c);

    /** \brief Set a sinc filter for the computed radiance values
     *
     *  More info in the lanczos_filter.hpp file. The used filter extents are
     *  defined in settings.h
     *
     *  \param[in] tau The tau value for the sinc filter
     */
    void setLanczosSincFilter(float tau);

    /** \brief Render the scene
     *
     *  This method, given an input scene, sets up the rendering threads and
     *  perform the rendering. A camera and a filter are needed. The output
     *  image will be saved in the path given in the constructor
     *
     * \param[in] s The scene that will be rendered
     * \return 0 if everything was ok, 1 otherwise
     */
    int render(Scene* s);

private:

    //Camera for the renderer
    Camera* c;

    //Filter for the renderer
    Filter* f;

    //Actual image
    ImageOutput film;

    //Number of rendering threads
    int numthreads;

    //width of the image
    int w;

    //height of the image
    int h;

    //samples per pixel
    int spp;

    //Sub-image that needs to be computed
    std::stack<Renderer_task> jobs;

    //mutex for the jobs stack
    std::mutex jobs_mtx;

    //working threads
    std::thread* workers;
};

#endif
