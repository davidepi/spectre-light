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

    /** Default constructor
     *
     * \param[in] range_x The number of pixel affected by this filter in the x
     *  axis
     * \param[in] range_y The number of pixel affected by this filter in the y
     *  axis
     */
    Filter(float range_x, float range_y):range_x(range_x), range_y(range_y)
    {};

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
    virtual float weight(float offset_x, float offset_y) const = 0;

    /**
     * \brief Returns the first parameter of the filter
     *
     *  This function should be used only while debugging and has no
     *  practical purpose in a release environment
     *
     *  \return The first parameter used to construct the filter. -1 if the
     *  filter has no parameter
     */
    virtual float get_param0() const = 0;

    /**
     * \brief Returns the second parameter of the filter
     *
     *  This function should be used only while debugging and has no
     *  practical purpose in a release environment
     *
     *  \return The second parameter used to construct the filter. -1 if the
     *  filter has no parameter
     */
    virtual float get_param1() const = 0;

    ///The number of pixel affected by this filter in the x axis
    const float range_x;
    ///The number of pixel affected by this filter in the y axis
    const float range_y;
};

#endif
