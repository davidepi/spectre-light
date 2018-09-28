//Created,  19 May 2017
//Last Edit  2 Apr 2018

/**
 *  \file filter_box.hpp
 *  \brief     FilterBox class definition
 *  \details   The easiest, fastest and worst filter possible
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      2 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __FILTER_BOX_HPP__
#define __FILTER_BOX_HPP__

#include "samplers/filter.hpp"

/**
 *  \class FilterBox filter_box.hpp "samplers/filter_box.hpp"
 *  \brief Implement the simplest filter
 *
 *  The box filter is the most simple filter, where every sampled valued has the
 *  same contribution towards the final average. For this reason it is the
 *  fastest and easiest to implement, however, it does not grant the best
 *  results
 */
class FilterBox : public Filter
{
public:

    ///Default constructor
    FilterBox();

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
    float weight(float offset_x, float offset_y) const override;

    /**
     * \brief Returns the first parameter of the filter
     *
     *  This function should be used only while debugging and has no
     *  practical purpose in a release environment
     *
     *  \return -1 since the filter has no parameter
     */
    float get_param0() const override;

    /**
     * \brief Returns the second parameter of the filter
     *
     *  This function should be used only while debugging and has no
     *  practical purpose in a release environment
     *
     *  \return -1 since the filter has no parameter
     */
    float get_param1() const override;
};

#endif
