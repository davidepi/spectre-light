//Created,  12 Aug 2018
//Last Edit 25 Aug 2018

/**
 *  \file texture_normal.hpp
 *  \brief     Normalmap implementation
 *  \details   Bump mapping performed using a tangent space normal map
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      25 Aug 2018
 *  \copyright GNU GPLv3
 */


#ifndef __TEXTURENORMAL_HPP__
#define __TEXTURENORMAL_HPP__

#include "textures/texture_image.hpp"

/**
 *  \brief Provides an implementation of the normal maps
 *
 *  The TextureNormal class is used to perform bump mapping by using a normal
 *  map instead of the common height map. A normal map is used to encode the
 *  shading normal in tangent space with each component (x,y,z) encoded by the
 *  channel (R,G,B) respectively, from range [0-255] to [-1,+1].
 *  This class overrides the method bump() used to compute the ShadingMatrix
 *  and the shading Normal
 */
class TextureNormal : public Bump
{
public:

    /**
     *  \brief Default constructor
     *  \param[in] image A pointer (not inherited) to the TextureImage that
     *  holds the normal map
     */
    TextureNormal(const Texture* image);

    /**
     *  \brief  Calculate the shading matrix for this material
     *
     * \param[in] hp The HitPoint that will be used for the shading matrix
     * computation
     * \param[out] matrix The shading matrix that will be generated
     * \param[out] normal The shading normal
     */
    void bump(const HitPoint* hp, ShadingSpace* matrix,
              Normal* normal) const override;

private:

    /** Underlying normal map */
    const Texture* image;
};

#endif
