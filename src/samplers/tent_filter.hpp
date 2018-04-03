//Created,  19 May 2017
//Last Edit  2 Apr 2018

/**
 *  \file tent_filter.hpp
 *  \brief     TentFilter class definition
 *  \details   A slightly better filter than the box one
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      2 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __TENT_FILTER_HPP__
#define __TENT_FILTER_HPP__

#include "samplers/filter.hpp"
#include "utility/utility.hpp"

///Value used by the parser to know the filter type is `tent`
#define SPECTRE_FILTER_TENT 1

/**
 *  \class TentFilter tent_filter.hpp "samplers/tent_filter.hpp"
 *  \brief Implement a filter with linear falloff
 *
 *  The tent filter is a slightly improvement over the box filter. The samples
 *  in the exact center have a weight of 1.0, and the samples at the extents
 *  have a weight of 0.0 towards the final average. In between them, every
 *  other sample is calculated as a linear falloff from the centre.
 */
class TentFilter : public Filter
{
public:

    ///Default constructor
    TentFilter();

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
    float weight(float offset_x, float offset_y)const;
};

#endif
