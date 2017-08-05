//Created,  31 Jul 2017
//Last Edit 31 Jul 2017

/**
 *  \file random_sampler.hpp
 *  \brief     Random sampling implementation
 *  \details   Naive sampling of a 2D region
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      31 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __RANDOM_SAMPLER_HPP__
#define __RANDOM_SAMPLER_HPP__

#include "samplers/sampler.hpp"
#include <cmath>

/**
 * \class RandomSampler random_sampler.hpp
 * \brief Sampler based on naive uniform sampling
 *
 *  This class generates random samples in a region. It is a naive
 *  implementation that uses just a random offset, so it yields terrible
 *  results. Other classes such as the StratifiedSampler can give better
 *  samples in the same amount of time, however, this class is kept here just
 *  for comparison
 */
class RandomSampler : public Sampler
{
public:

    /** Default constructor
     *
     * Initialize the sampler to operate in a region defined by a starting pixel
     * with (x,y) coordinates and an ending pixel
     *
     * \param[in] startx The x coordinate of the starting pixel
     * \param[in] endx The x coordinate of the ending pixel
     * \param[in] starty The \a y coordinate of the starting pixel
     * \param[in] endy The \a y coordinate of the ending pixel
     * \param[in] spp The number of samples per pixel
     * \param[in] seed The seed of the prng (128 bytes array)
     */
    RandomSampler(int startx, int endx, int starty, int endy, int spp,
                      const unsigned int* seed);

    /** Return the samples
     *
     *  Return a set of samples for the current pixel. The current pixel is
     *  auto-updated, and not required as input
     *
     *  If the whole area has been sampled, the function returns false
     *
     *  \param[in,out] res The resulting array of samples
     *  \return false if the whole area has been sampled, true otherwise
     */
    bool getSamples(Sample* res);

private:

    //the next pixel (x-coordinate)
    int nextx;

    //the next pixel (y-coordinate)
    int nexty;
};

#endif