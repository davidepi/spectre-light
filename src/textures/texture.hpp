//Created,  14 Mar 2018
//Last Edit  5 Dec 2018

/**
 *  \file texture.hpp
 *  \brief     Texture abstract class definition
 *  \details   The superclass from which every texture inherits
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      5 Dec 2018
 *  \copyright GNU GPLv3
 */


#ifndef __TEXTURE_HPP_
#define __TEXTURE_HPP_

#include "primitives/hit_point.hpp"
#include "utility/spectrum.hpp"
#include "image_map.hpp"

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
    virtual Spectrum map(const HitPoint* hp) const
    { return {map_color(hp), false}; };

    /** \brief Maps an (u,v) coordinate to a texture value
     *
     *  Given the coordinates \p u and \p v of a point, this method finds the
     *  ColorRGB value associated with these coordinates.
     *
     *  \param[in] hp The data of the hit point
     *  \return The RGB value of the mesh with this texture applied at the
     *  coordinates (u,v)
     */
    virtual ColorRGB map_color(const HitPoint* hp) const
    {
        Texel value = map_value(hp).bgra_texel;
        return {value.r, value.g, value.b};
    };

    /** \brief Maps an (u,v) coordinate to a texture value
     *
     *  Given the coordinates \p u and \p v of a point, this method finds the
     *  Texel associated with the point.
     *
     *  \param[in] hp The data of the hit point
     *  \return The texel of the mesh with this texture applied at the
     *  coordinates (u,v)
     */
    virtual TexelUnion map_value(const HitPoint* hp) const = 0;

    /**
     *  \brief Returns the shift component
     *
     *  Returns the shift component applied to this ImageMap, where the returned
     *  vector's x component correspond to the texture U shifting value, and the
     *  vector's y component to the shifted V.
     *
     *  \return The shift component applied to the underlying ImageMap
     */
    virtual Vec2 get_shift() const
    { return {}; };

    /**
     *  \brief Returns the scale component
     *
     *  Returns the scale component applied to this ImageMap, where the returned
     *  vector's x component correspond to the texture U scaling value, and the
     *  vector's y component to the scaling V.
     *
     *  \return The scale component applied to the underlying ImageMap
     */
    virtual Vec2 get_scale() const
    { return {1.f, 1.f}; };

    /**
     *  \brief Returns the side of the Texture
     *
     *  \return An unsigned int specifying the side of the texture
     */
    virtual uint16_t get_side() const = 0;
};

#endif
