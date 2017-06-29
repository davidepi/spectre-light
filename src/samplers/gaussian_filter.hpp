//Created,  19 May 2017
//Last Edit 20 May 2017

/**
 *  \file gaussian_filter.hpp
 *  \brief     GaussianFilter class definition
 *  \details   A filter that approximate a gaussian function
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      20 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __GAUSSIAN_FILTER_HPP__
#define __GAUSSIAN_FILTER_HPP__

#include <cmath>
#include "filter.hpp"
#include "utility.hpp"

/**
 *  \class GaussianFilter gaussian_filter.hpp "samplers/gaussian_filter.hpp"
 *  \brief Implement a filter with gaussian falloff
 *
 *  The gaussian filter is similar to the tent filter, but instead of falling
 *  off linearly, it tries to approximate a gaussian function. As in the
 *  tent filter the center has a value of 1.0 and the limit has a value of
 *  0.0
 */
class GaussianFilter : public Filter
{
public:

    /** \brief Default constructor
     *
     * \param[in] x_range The x extent of the filter
     * \param[in] y_range The y extent of the filter
     * \param[in] falloff The rate of the falloff. Smaller values gives slower
     * falloff
     */
    GaussianFilter(float x_range, float y_range, float falloff);

    /** \brief Compute the weight of a given sample in the final average
     *
     * This method is an implementation of the pure virtual function of the
     * weight class which returns the weight of the considered pixel.
     * The sample in the exact centre of the filter has a value of 1.0, and
     * every other sample is calculated as a gaussian falloff from the centre
     * until the edge of the filter which posses a value of 0.0. The speed
     * of this falloff is governed by the value passed in the constructor
     *
     * \param[in] offset_x The \a x distance of the sample from the centre.
     * \param[in] offset_y The \a y distance of the sample from the centre.
     * \return The weight of the sample in the final average for the pixel.
     */
    float weight(float offset_x, float offset_y)const;

private:

    //precomputed value based on the width
    float precomputed_exp_x;

    //precomputed value based on the height
    float precomputed_exp_y;

    //alpha of the gaussian
    float alpha;
};

#endif
