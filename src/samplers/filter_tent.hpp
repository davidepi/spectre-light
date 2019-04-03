//Created,  19 May 2017
//Last Edit  2 Apr 2018

/**
 *  \file filter_tent.hpp
 *  \brief     FilterTent class definition
 *  \details   A slightly better filter than the box one
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      2 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __FILTER_TENT_HPP__
#define __FILTER_TENT_HPP__

#include "samplers/filter.hpp"

/**
 *  \class FilterTent filter_tent.hpp "samplers/filter_tent.hpp"
 *  \brief Implement a filter with linear falloff
 *
 *  The tent filter is a slightly improvement over the box filter. The samples
 *  in the exact center have a weight of 1.0, and the samples at the extents
 *  have a weight of 0.0 towards the final average. In between them, every
 *  other sample is calculated as a linear falloff from the centre.
 */
class FilterTent : public Filter
{
public:

    ///Default constructor
    FilterTent();

    /** \brief Compute the weight of a given sample in the final average
     *
     * This method is an implementation of the pure virtual function of the
     * weight class which returns the weight of the considered pixel.
     * The sample in the exact centre of the filter has a value of 1.0, and
     * every other sample is calculated as a linear falloff from the centre
     * until the edge of the filter which posses a value of 0.0
     *
     * \param[in] offset_x The \a x distance of the sample from the centre.
     * \param[in] offset_y The \a y distance of the sample from the centre.
     * \return The weight of the sample in the final average for the pixel.
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
