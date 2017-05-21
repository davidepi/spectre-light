//Created,  19 May 2017
//Last Edit 21 May 2017

/**
 *  \file lanczos_filter.hpp
 *  \brief     LanczosFilter class definition
 *  \details   A filter based on the sinc function
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      21 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __LANCZOS_FILTER_HPP__
#define __LANCZOS_FILTER_HPP__

#include <cmath>
#include "filter.hpp"
#include "utility.hpp" //M_PI

/**
 *  \class LanczosFilter lanczos_filter.hpp "samplers/lanczos_filter.hpp"
 *  \brief Implement a filter based on the sinc function
 *
 *  This filter is based on the sinc function. Since the behaviour of the sinc
 *  function is infinite, it is multiplied by another function to clamp it to
 *  zero. The parameter tau of the constructor is used for this behaviour.
 *  For this reason, the sample contribution has a value of 1.0 on the center
 *  of the filter, and 0.0 on the edges
 */
class LanczosFilter : public Filter
{
public:
    
    /** \brief Default constructor
     *
     *  \param x_range The x extent of the filter
     *  \param y_range The y extent of the filter
     *  \param tau The number of cycles of the sinc function before clamping it
     *        to zero
     */
    LanczosFilter(float x_range, float y_range, float tau);
    
    ///Default destructor
    ~LanczosFilter();
    
    /** \brief Compute the weight of a given sample in the final average
     *
     *  This method is an implementation of the pure virtual function of the
     *  weight class which returns the weight of the considered pixel.
     *  The sample in the exact centre of the filter has a value of 1.0, and
     *  every other sample is calculated following a normalized sinc function,
     *  multiplied by another function that clamps it after a given amount of
     *  cycles
     *
     * \param offset_x The \a x distance of the sample from the centre.
     * \param offset_y The \a y distance of the sample from the centre.
     * \return The weight of the sample in the final average for the pixel.
     */
    float weight(float offset_x, float offset_y);
    
private:
    
    //precomputed inverse of the filter width
    float inverse_width;
    
    //precomputed inverse of the filter height
    float inverse_height;
    
    //number of cycles of the sinc function before clamping it
    float tau;
};

#endif
