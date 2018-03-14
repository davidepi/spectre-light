//Created,  14 Mar 2018
//Last Edit 14 Mar 2018

/**
 *  \file texture.hpp
 *  \brief     Texture returning a single value
 *  \details   A texture mapping evey u,v coordinate to the same Spectrum value
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      14 Mar 2018
 *  \copyright GNU GPLv3
 */


#ifndef __UNIFORM_TEXTURE_HPP_
#define __UNIFORM_TEXTURE_HPP_

#include "textures/texture.hpp"
#include "utility/spectrum.hpp"

/**
 *  \class UniformTexture uniform.hpp textures/uniform.hpp
 *  \brief A Texture class returning always the same value
 *
 *  UniformTexture that maps every (u,v) coordinate to the same Spectrum value
 *  passed at construction time. Although this seems an unnecessary wrapping, it
 *  it used to set a sort of default implementation of the texture class.
 */
class UniformTexture : public Texture
{
public:
    
    /*  \brief Default constructor
     *
     *  \param[in] value The spectrum value that will be returned by the map()
     *  function
     */
    UniformTexture(const Spectrum& value);
    
    ///Default destructor
    ~UniformTexture() = default;
    
    /** \brief Maps an (u,v) coordinate to a texture value
     *
     *  Given the coordinates \p u and \p v of a point, this method finds the
     *  Spectrum value associated with these coordinates by looking at the
     *  underlying image
     *
     *  \param[in] u The x value of the mapped point in image space
     *  \param[in] v The y value of the mapped point in image space
     */
    Spectrum map(float u,float v)const;

private:
    const Spectrum value;
};

#endif

