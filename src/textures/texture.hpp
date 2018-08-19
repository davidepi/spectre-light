//Created,  14 Mar 2018
//Last Edit 14 Mar 2018

/**
 *  \file texture.hpp
 *  \brief     Texture abstract class definition
 *  \details   The superclass from which every texture inherits
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      14 Mar 2018
 *  \copyright GNU GPLv3
 */


#ifndef __TEXTURE_HPP_
#define __TEXTURE_HPP_

#include "primitives/hit_point.hpp"
#include "utility/spectrum.hpp"

/**
 *  \class Texture texture.hpp textures/texture.hpp
 *  \brief Texture superclass
 *
 *  Texture class is used to load an image that encloses high frequency details
 *  of a model and retrieve them. This class is the base class exposing only the
 *  evaluate function that every type of texture should provide
 */
class Texture
{
public:

    ///Default constructor
    Texture() = default;

    ///Default destructor
    virtual ~Texture() = default;

    /** \brief Maps an (u,v) coordinate to a texture value
     *
     *  Given the coordinates \p u and \p v of a point, this method finds the
     *  Spectrum value associated with these coordinates.
     *
     *  \param[in] hp The data of the hit point
     *  \return The Spectrum value of the mesh with this texture applied at the
     *  coordinates (u,v)
     */
    virtual Spectrum map(const HitPoint* hp) const = 0;
};

#endif
