//Created,  19 May 2017
//Last Edit 31 May 2017

/**
 *  \file stratified_sampler.hpp
 *  \brief     Stratified sampling implementation
 *  \details   Divide the region in equal subregions and sample each one
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      31 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __STRATIFIED_SAMPLER_HPP__
#define __STRATIFIED_SAMPLER_HPP__

#include <cmath>
#include "samplers/sampler.hpp"

/**
 * \class StratifiedSampler stratified_sampler.hpp
 * \brief Sampler based on subregion sampling
 *
 *  In order to avoid uneven distribution of samples, but still preserve
 *  unbiased behaviour, the strafied sampler firstly subdivides the region
 *  in \a n identical subregions, where \a n is the number of samples required.
 *  Then for each subregion, one random sample is picked. This decreases
 *  considerably the probability of oversampling some part of the region
 *  and undersampling others.
 */
class StratifiedSampler : public Sampler
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
     * \param[in] random if the samples for each subregion are picked at random
     * or in the centre
     */
    StratifiedSampler(int startx, int endx, int starty, int endy, int spp,
                              const unsigned int* seed, bool random);

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
    bool get_samples(Sample* res);

private:

    //the next pixel (x-coordinate)
    int nextx;

    //the next pixel (y-coordinate)
    int nexty;

    //number of x subregion per pixel
    int strata_x;

    //number of y subregion per pixel
    int strata_y;

    //true if the sample is no centered in the subregion
    bool isRandomized;
};

#endif
