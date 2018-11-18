//Created,  14 Mar 2018
//Last Edit 14 Mar 2018

/**
 *  \file texture_uniform.hpp
 *  \brief     Texture returning a single value
 *  \details   A texture mapping evey u,v coordinate to the same Spectrum value
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      14 Mar 2018
 *  \copyright GNU GPLv3
 */


#ifndef __UNIFORM_HPP_
#define __UNIFORM_HPP_

#include "textures/texture.hpp"
#include "primitives/hit_point.hpp"
#include "utility/spectrum.hpp"

/**
 *  \class TextureUniform uniform.hpp textures/texture_uniform.hpp
 *  \brief A Texture class returning always the same value
 *
 *  TextureUniform that maps every (u,v) coordinate to the same Spectrum value
 *  passed at construction time. Although this seems an unnecessary wrapping, it
 *  it used to set a sort of default implementation of the texture class.
 */
class TextureUniform : public Texture
{
public:

    /*  \brief Default constructor
     *
     *  \param[in] value The spectrum value that will be returned by the map()
     *  function
     */
    TextureUniform(const Spectrum& value);

    /** \brief Maps an (u,v) coordinate to a texture value
     *
     *  Given the coordinates \p u and \p v of a point, this method finds the
     *  Spectrum value associated with these coordinates by looking at the
     *  underlying image
     *
     *  \param[in] hp The data of the hit point
     */
    Spectrum map(const HitPoint* hp) const override;

    TexelUnion map_value(const HitPoint* hp) const override;

    /**
     *  \brief Returns the side of the Texture
     *
     *  Since this texture is procedurally generated and mostly implrtant is is
     *  uniform, it can be viewed as a 1x1 TextureImage with the constant color.
     *  Thus, this function returns 1.
     *
     *  \return 1
     */
    uint16_t get_side() const override;

    /**
     *  \brief Returns an array representation of this Texture
     *
     *  Copy the values of this texture inside the array passed as parameter.
     *  The array is expected to be of length 1, for this particular type of
     *  Texture. Alternatively, an array should be allocated of size side*side
     *  with side equals to the value returned by the function get_side()
     *
     *  \param[in] array The array where the value will be copied
     */
    void to_array(TexelUnion* array) const override;

private:
    const Spectrum value;
};

#endif

