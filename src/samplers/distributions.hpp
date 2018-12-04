//Created,   2 Dec 2018
//Last Edit  2 Dec 2018

/**
 *  \file distributions.hpp
 *  \brief     Provides the definition of piecewise-constant functions
 *  \author    Davide Pizzolotto (taken from pbrt)
 *  \version   0.2
 *  \date      2 Dec 2018
 *  \copyright GNU GPLv3
 */

/*----------------------------------------------------------------------\
 | Note that this class is taken from pbrt. In some part of the code    |
 | (for example uniform sampling of a mesh) I wrote a similar version   |
 | of my own, but in the end I decided to take this one from pbrt which |
 | is actually better.                                                  |
 `---------------------------------------------------------------------*/

#ifndef DISTRIBUTIONS_HPP
#define DISTRIBUTIONS_HPP

#include <cstdlib>
#include "geometry/point2.hpp"

/**
 *  \brief Class representing a one dimensional distribution
 *
 *  The Distribution1D takes a piecewise-constant function an uses it to perform
 *  discrete or continuous sampling. The implementation of this class computes
 *  the cumulative density function of the distribution and its integral in
 *  order to simplify the sampling.
 */
class Distribution1D
{
public:

    /**
     * \brief Constructor
     * \param[in] data The discrete values of the piecewise function
     * \param[in] length The number of values passed to the constructor
     */
    Distribution1D(const float* data, size_t length);

    /**
     * \brief Destructor
     */
    ~Distribution1D();

    /**
     * \brief Deleted copy constructor.
     */
    Distribution1D(const Distribution1D&) = delete;

    /**
     * \brief Performs continuous sampling from the distribution
     * \param[in] u A random float in the interval [0-1] used to sample the
     * distribution
     * \param[in] pdf The pdf of the chosen sample
     * \return A continuous sample taken from the distribution
     */
    float sample_continuous(float u, float* pdf = NULL) const;

    /**
     * \brief Returns the (cached) integral value of this distribution
     * \return The integral value of the distribution
     */
    float get_integral_value() const;

    /**
     * \brief Returns the original value at the ith index
     * \param[in] index The index of the original sampled value
     * \return The value of the original piecewise distribution at given index
     */
    float get_piecewise_value(int index) const;

private:

    //values
    float* values;

    //cumulative density function
    float* cdf;

    //number of samples
    size_t num;

    float integral_value;
};

/**
 *  \brief Class representing a two dimensional distribution
 *
 *  The Distribution2D takes a piecewise-constant function an uses it to perform
 *  discrete or continuous sampling. The piecewise-constant function is expected
 *  to be in two dimension.
 */
class Distribution2D
{
public:

    /**
     * \brief Default constructor
     * \param[in] data The value of the piecewise function. Since this is a 1D
     * array, it is expected to contains value ordered left to right, top to
     * bottom
     * \param[in] len_x size of the first dimension
     * \param[in] len_y size of the second dimension
     */
    Distribution2D(const float* data, size_t len_x, size_t len_y);

    /**
     * \brief Default destructor
     */
    ~Distribution2D();

    /**
     * \brief Deleted copy constructor.
     */
    Distribution2D(const Distribution2D&) = delete;

    /**
     * \brief Perform continous sampling over the distribution
     * \param[in] u A random value in the interval [0-1] used to sample the
     * first dimension of the distribution
     * \param[in] v A random value in the interval [0,1] used to sample the
     * second dimension of the distribution
     * \param[out] pdf The pdf for the chosen samples.
     * \return A continuous sample in two dimensions.
     */
    Point2 sample_continuous(float u, float v, float* pdf = NULL) const;

    /**
     * \brief Retrieve the pdf given a sampled value
     * \param[in] value The value that has been previously sampled
     * \return The pdf for the given value
     */
    float pdf(const Point2* value) const;

private:

    //conditional probabilities, p[u|v]
    Distribution1D** conditional;

    //marginal sampling density p[v]
    Distribution1D* marginal;

    //Number of values of the marginal density
    size_t marginal_len;
};


#endif
