//Created,  11 Aug 2018
//Last Edit 12 Aug 2018

/**
 *  \file mask_boolean.hpp
 *  \brief     Boolean mask
 *  \details   Enables masking capabilities given a TextureImage
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      12 Aug 2018
 *  \copyright GNU GPLv3
 */


#ifndef __MASK_BOOLEAN_HPP__
#define __MASK_BOOLEAN_HPP__

#include "textures/texture_image.hpp"

//Check image_map.hpp for details on ARGB/BGRA between the two architectures
#ifndef IS_BIG_ENDIAN
/** Channel of the TextureImage. ARGB order in little endian machines */
enum ImageChannel
{
    ALPHA = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 3,
};
#else
/** Channel of the TextureImage. BGRA order in big endian machines */
enum ImageChannel
{
    BLUE = 0,
    GREEN = 1,
    RED = 2,
    ALPHA = 3
};
#endif

///Values under the threshold are considered false when applying masking
#define MASK_BINARY_THRESHOLD 128

/**
 *  \brief Mask based on a texture, performing boolean masking
 *
 *  This class is a TextureImage wrapper used to perform masking. The method
 *  is_masked is provided in order to know if a given point over the surface
 *  of an asset is masked or not. Additional members of this class are used
 *  to know which channel should be considered for the mask and if the mask
 *  should be inverted
 */
class MaskBoolean
{
public:

    /**
     *  \brief Default mask constructor.
     *
     *  This mask constructor constructs an empty Mask. With this
     *  constructor, the is_masked function will always return false
     */
    MaskBoolean();

    /**
     *  \brief Boolean mask constructor
     *
     *  Note that the TextureImage is NOT inherited by this class
     *
     *  \param[in] map Texture that will be used to decide masking
     *  \param[in] channel Channel of the texture used to get mask values
     *  \param[in] inverted True if the mask should be inverted
     */
    MaskBoolean(const TextureImage* map, ImageChannel channel, bool inverted);

    ///Default destructor
    ~MaskBoolean() = default;

    /**
     *  \brief Returns the value for this mask
     *
     *  This function finds the texture value of the underlying TextureImage
     *  (considering shift and scale) and returns true if the value is above
     *  the threshold, false otherwise. Only the channel passed in the
     *  constructor is considered. Mask inversion is taken into account in
     *  this method
     *
     *  \param[in] hp The data of the hit point
     *  \return true if the value is masked, false otherwise
     */
    bool is_masked(const HitPoint* hp) const;

private:

    /** Image used as mask */
    const TextureImage* map;

    /** Channel of the Image that wil be used */
    ImageChannel channel;

    /** True if this image has to be inverted */
    bool inverted;
};

#endif
