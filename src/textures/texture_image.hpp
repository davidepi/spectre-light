//Created,   8 May 2018
//Last Edit  7 Sep 2018

/**
 *  \file texture_image.hpp
 *  \brief     Wrapper for image map
 *  \details   Class holding an image map that can be shifted and scaled
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      7 Sep 2018
 *  \copyright GNU GPLv3
 */


#ifndef __TEXTURE_IMAGE_HPP__
#define __TEXTURE_IMAGE_HPP__

//This magnificent bastard must come first, otherwise C++ linking is used anyway
extern "C" {
#include "utility/imageio/imageio.h"
}

#include "textures/texture.hpp"
#include "textures/image_map.hpp"
#include "textures/texture_library.hpp"
#include "primitives/hit_point.hpp"
#include "textures/types_imgchannel.h"

/**
 *  \brief Wrapper containing an ImageMap shifted and scaled
 *  This class contains a refeerence to an ImageMap. This image is used as
 *  texture that will be applied over an object. This class in particular, is
 *  the bridge between the Texture interface and the ImageMap class containing
 *  the actual stored data, and provides additional information such as scaling
 *  and shifting, that may vary between assets with the same underlying ImageMap
 */
class TextureImage : public Texture
{
public:

    /**
     *  \brief Constructor
     *
     *  Given the underlying ImageMap and its shift and scale values, construct
     *  this class
     *
     *  \param[in] src The path to the underlying ImageMap
     *  \param[in] shift The value used to shift the UV values before performing
     *  texture mapping
     *  \param[in] scale The value used to scale the UV values before performing
     *  texture mapping
     *  \param[in] filter The type of filter that will be used to filter this
     *  texture
     */
    TextureImage(const File& src, Vec2& shift, Vec2& scale,
                 texturefilter_t filter);

    /**
     *  \brief Constructor
     *
     *  Given the underlying ImageMap and its shift and scale values, construct
     *  this class
     *
     *  \param[in] map A pointer to the underlying ImageMap
     *  \param[in] scale The value used to scale the UV values before performing
     *  texture mapping
     *  \param[in] shift The value used to shift the UV values before performing
     *  texture mapping
     *  \param[in] unfiltered True if the underlying ImageMap is unfiltered.
     *  If this is not known, use false. Passing false if the image is
     *  unfiltered causes only a small performance degradation, passing true
     *  if the image is NOT unfiltered leads to completely wrong results.
     */
    TextureImage(const ImageMap* map, Vec2& shift, Vec2& scale,
                 bool unfiltered = false);

    ///Default destructor
    ~TextureImage() override = default;

    /**
     *  \brief Returns the shift component
     *
     *  Returns the shift component applied to this ImageMap, where the returned
     *  vector's x component correspond to the texture U shifting value, and the
     *  vector's y component to the shifted V.
     *
     *  \return The shift component applied to the underlying ImageMap
     */
    Vec2 get_shift() const;

    /**
     *  \brief Returns the scale component
     *
     *  Returns the scale component applied to this ImageMap, where the returned
     *  vector's x component correspond to the texture U scaling value, and the
     *  vector's y component to the scaling V.
     *
     *  \return The scale component applied to the underlying ImageMap
     */
    Vec2 get_scale() const;

    /** \brief Maps an (u,v) coordinate to a texture value
     *
     *  Given the coordinates \p u and \p v of a point, this method finds the
     *  Spectrum value associated with these coordinates by looking at the
     *  underlying ImageMap. The value is returned as a spectrum NOT to be used
     *  for lights
     *
     *  \param[in] hp The data of the hit point
     *  \return The Spectrum value of the mesh with this texture applied at the
     *  coordinates (u,v)
     */
    Spectrum map(const HitPoint* hp) const override;

    /** \brief Maps an (u,v) coordinate to a texture value
     *
     *  Given the coordinates \p u and \p v of a point, this method finds the
     *  Spectrum value associated with these coordinates by looking at the
     *  underlying ImageMap. Exactly like the map method, but this returns a
     *  TexelUnion instead of a Spectrum.
     *
     *  \param[in] hp The data of the hit point
     *  \return The Spectrum value of the mesh with this texture applied at the
     *  coordinates (u,v)
     */
    TexelUnion map_value(const HitPoint* hp) const override;

    /**
     *  \brief Returns the side of the Texture
     *
     *  \return An int specifying the side of the texture
     */
    uint16_t get_side() const override;

    /**
     *  \brief Returns an array representation of this Texture
     *
     *  Copy the values of this texture inside the array passed as parameter.
     *  The array is expected to be at least side*side size, where side can be
     *  obtained by callidn the TextureImage::get_side() function
     *  The array will be ordererd top to bottom, left to right.
     *
     *  \param[in] array The array where the value will be copied
     */
    void to_array(TexelUnion* array) const override;

    //used to ensure ImageMap is allocated of the correct type
#ifndef TESTS
    protected:
#endif

    ///scale component
    Vec2 scale;

    ///shift component
    Vec2 shift;

    ///Filter used by the underlying imageMap
    bool unfiltered;

    ///The underlying ImageMap
    const ImageMap* imagemap;
};

#endif
