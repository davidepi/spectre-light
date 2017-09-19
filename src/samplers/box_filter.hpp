//Created,  19 May 2017
//Last Edit 20 May 2017

/**
 *  \file box_filter.hpp
 *  \brief     BoxFilter class definition
 *  \details   The easiest, fastest and worst filter possible
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      20 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __BOX_FILTER_HPP__
#define __BOX_FILTER_HPP__

#include "samplers/filter.hpp"

/**
 *  \class BoxFilter box_filter.hpp "samplers/box_filter.hpp"
 *  \brief Implement the simplest filter
 *
 *  The box filter is the most simple filter, where every sampled valued has the
 *  same contribution towards the final average. For this reason it is the
 *  fastest and easiest to implement, however, it does not grant the best
 *  results
 */
class BoxFilter : public Filter
{
public:

    /** Default constructor
     *
     * \param[in] x_range The x extent of the filter
     * \param[in] y_range The y extent of the filter
     */
    BoxFilter(float x_range, float y_range);

    /** \brief Compute the weight of a given sample in the final average
     *
     * This method is an implementation of the pure virtual function of the
     * weight class which is supposed to return the weight of the considered
     * pixel. However, since every pixel in a box filter is weighted in the same
     * way, this function simply returns 1.0
     *
     * \param[in] offset_x The \a x distance of the sample from the centre.
     * Unused
     * \param[in] offset_y The \a y distance of the sample from the centre.
     * Unused
     * \return The weight of the sample in the final average for the pixel.
     * Which is always 1.0 in a box filter, since every sample has the same
     * weight
     */
    float weight(float offset_x, float offset_y)const;
};

#endif
