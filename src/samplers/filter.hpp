//Created,  19 May 2017
//Last Edit  2 Apr 2018

/**
 *  \file filter.hpp
 *  \brief     Filter abstract class definition
 *  \details   The superclass for every filter
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      2 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __FILTER_HPP__
#define __FILTER_HPP__

/**
 *  \class Filter filter.hpp "samplers/filter.hpp"
 *  \brief An abstract class used as a template for every filter
 *
 *  The filter class provides a method for reconstructing of a correct value,
 *  given a finite amount of samples. The only method exposed by this class is
 *  the Filter::weight one which return the weight of the sample in the final
 *  average
 */
class Filter
{
public:

    Filter() = default;

    ///Default destructor
    virtual ~Filter() = default;

    /** \brief Compute the weight of a given sample in the final average
     *
     * Given a sample, measured as an offset from the centre of the pixel,
     * measure its weight in the final average, in the range [0.0,1.0]
     *
     * \param[in] offset_x The \a x distance of the sample from the centre
     * \param[in] offset_y The \a y distance of the sample from the centre
     * \return The weight of the sample in the final average for the pixel
     */
    virtual float weight(float offset_x, float offset_y)const = 0;
};

#endif
