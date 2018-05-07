//Created,  19 May 2017
//Last Edit 13 Jul 2017

/**
 *  \file sampler.hpp
 *  \brief     Definition of Sampler superclass and Sample POD
 *  \details   Contains the superclass for every sampler and the minimum
 *             data structure expected to be returning
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      13 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __SAMPLER_HPP__
#define __SAMPLER_HPP__

#include "utility/wellrng.hpp"

/**
 *  \struct Sample sampler.hpp "samplers/sampler.hpp"
 *  \brief A simple struct containing a sample
 *
 *  The Sample structure contains the position of a sample in raster space
 *  where (0,0) is the top-left image corner and (image_size,image_size) is the
 *  bottom-right one.
 */
struct Sample
{
    ///The x position of the sample, from (0,0) to (max_pixel,max_pixel)
    float posx;

    ///The y position of the sample, from (0,0) to (max_pixel,max_pixel)
    float posy;
};

/**
 *  \class Sampler sampler.hpp "samplers/sampler.hpp"
 *  \brief Abstract class exposing samplers methods
 *
 *  This class is the template that needs to be followed while implementing a
 *  sampler. The constructor requires a seed for the rng, the starting and
 *  ending pixels (Since this could be a sub-sampler of the image) and the
 *  number of samples per pixel
 */
class Sampler
{
public:

    /** \brief Constructor
     *
     *  Construct a sampler instance responsible for generating samples in a
     *  portion of the image
     *
     *  \param[in] startx The \a x coordinate of the starting pixel of the image
     *  or sub-image. (0,0) is the top-left corner
     *  \param[in] endx The \a x coordinate of the ending pixel of the image, or
     *  sub-image.
     *  \param[in] starty The \a y coordinate of the starting pixel of the image
     *  \param[in] endy The \a y coordinate of the ending pixel of the image
     *  \param[in] spp The number of samples expected for each pixel
     *  \param[in] seed A 128 bytes array containing the seed of the rng
     */
    Sampler(int startx, int endx, int starty, int endy, int spp,
            const unsigned int* seed);

    ///Default destructor
    virtual ~Sampler() = default;

    /** \brief Return a set of samples
     *
     *  Return the set of samples that needs to be evaluated for the current
     *  pixel. The size of the array is the same as the number of spp passed to
     *  the constructor
     *
     *  \param[out] res An array containing the generated samples
     *  \return false if the whole area has been sampled, true otherwise
     */
    virtual bool get_samples(Sample* res) = 0;

    /** \brief Generate random numbers
     *
     *  Return \p size randomly generated numbers in the interval (0.0,1.0)
     *
     *  \param[out] container The array where the random numbers will be stored
     *  \param[in]  size The amount of numbers that will be generated
     */
    void get_random_numbers(float* container, int size);

protected:

    ///The random number generator
    WELLrng rng;

    ///The starting pixel (x-coordinate)
    int startx;

    ///The starting pixel (y-coordinate)
    int starty;

    ///The ending pixel (x-coordinate)
    int endx;

    ///The ending pixel (y-coordinate)
    int endy;

    ///The number of samples per pixel
    int spp;
};

#endif
