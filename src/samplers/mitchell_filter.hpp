//Created,  20 May 2017
//Last Edit 21 May 2017

/**
 *  \file mitchell_filter.hpp
 *  \brief     MitchellFilter class definition
 *  \details   A filter that approximate a gaussian function, with less blur
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      21 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __MITCHELL_FILTER_HPP__
#define __MITCHELL_FILTER_HPP__

#include <cmath>
#include "filter.hpp"

/**
 *  \class MitchellFilter mitchell_filter.hpp "samplers/mitchell_filter.hpp"
 *  \brief Improvement over the gaussian filter
 *
 *  The Mitchell-Netravali filter is similar to the gaussian filter, but gives
 *  sharper edges, instead of the blurry ones typical of the gaussian filter.
 *  This is done by assuming negative values near the limit of the filter,
 *  yet mantaining a limit of 0.0. As in the gaussian filter the value in the
 *  center of the filter is 1.0.
 *
 *  This filter can approximate several other filters such as bicubic or
 *  Catmull-Rom, check the constructor for further information
 */
class MitchellFilter : public Filter
{
public:

    /** Default constructor
     *
     *  The Mitchell-Netravali filter is based on a parametrized expression
     *  that requires the term \p b and \p c to be set up.
     *  The authors suggest values like $B + 2C = 1$ or B = 1/3 and C = 1/3.
     *  However, several other filters can be simulated by carefully setting
     *  this two parameters. For example with B = 0 and C = 0.5 the filter is
     *  like a Catmull-Rom, and with B = 1 and C = 0 the filter is a B-spline.
     *
     *  \param x_range The x extent of the filter
     *  \param y_range The y extent of the filter
     *  \param b B value of the filter, check detailed description
     *  \param c C value of the filter, check detailed description
     */
    MitchellFilter(float x_range, float y_range, float b, float c);

    ///Default destructor
    ~MitchellFilter();

    /** \brief Compute the weight of a given sample in the final average
     *
     *  This method is an implementation of the pure virtual function of the
     *  weight class which returns the weight of the considered pixel.
     *  The sample in the exact centre of the filter has a value of 1.0, and
     *  every other sample is calculated with a parametric expression similar to
     *  to a gaussian curve, until the value of 0.0 on the limit.
     *
     *  \param offset_x The \a x distance of the sample from the centre.
     *  \param offset_y The \a y distance of the sample from the centre.
     *  \return The weight of the sample in the final average for the pixel.
     */
    float weight(float offset_x, float offset_y);

private:

    //inverse of the width of the filter
    float inv_width;

    //inverse of the height of the filter
    float inv_height;

    //b value of the filter. See constructor documentation
    float b;

    //c value of the filter. See constructor documentation
    float c;
};

#endif
