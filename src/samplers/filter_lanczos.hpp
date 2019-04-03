//Created,  19 May 2017
//Last Edit  2 Apr 2018

/**
 *  \file filter_lanczos.hpp
 *  \brief     FilterLanczos class definition
 *  \details   A filter based on the sinc function
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      2 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __FILTER_LANCZOS_HPP__
#define __FILTER_LANCZOS_HPP__

#include "samplers/filter.hpp"

/**
 *  \class FilterLanczos filter_lanczos.hpp "samplers/filter_lanczos.hpp"
 *  \brief Implement a filter based on the sinc function
 *
 *  This filter is based on the sinc function. Since the behaviour of the sinc
 *  function is infinite, it is multiplied by another function to clamp it to
 *  zero. The parameter tau of the constructor is used for this behaviour.
 *  For this reason, the sample contribution has a value of 1.0 on the center
 *  of the filter, and 0.0 on the edges
 */
class FilterLanczos : public Filter
{
public:

    /** \brief Default constructor
     *
     *  \param[in] tau The number of cycles of the sinc function before clamping
     *  it to zero
     */
    FilterLanczos(float tau);

    /** \brief Compute the weight of a given sample in the final average
     *
     *  This method is an implementation of the pure virtual function of the
     *  weight class which returns the weight of the considered pixel.
     *  The sample in the exact centre of the filter has a value of 1.0, and
     *  every other sample is calculated following a normalized sinc function,
     *  multiplied by another function that clamps it after a given amount of
     *  cycles
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
     *  \return The value of the tau parameter
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

private:

    //number of cycles of the sinc function before clamping it
    float tau;
};

#endif
