//Created,   7 May 2018
//Last Edit  9 Aug 2018

/**
 *  \file image_map.hpp
 *  \brief     Helper classes used to handle Images used as textures
 *  \details   ImageMap class, a square, power of 2, image used inside
 *             TextureImage as a MIPMap.
 *             Several other classes are provided to cope with varying filtering methods
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      9 Aug 2018
 *  \copyright GNU GPLv3
 */


#ifndef __IMAGE_MAP_HPP__
#define __IMAGE_MAP_HPP__

#include "utility/file.hpp"
#include "utility/imageio/imageio.h"
#include "samplers/filter_box.hpp"
#include "samplers/filter_lanczos.hpp"
#include "utility/utility.hpp" //swap
#include <cstdlib> //malloc/free
#include <cmath> //sqrtf
#include <array> //EWA weights allocation
#include "utility/array2D.hpp"

//forward declaration to be used in TexelMap
class ImageMap;

/**
 * \brief Struct holding a single Texel of the map in BGRA order
 *
 *  Since the architecture is little endian, the first element will map to the
 *  least significant digit of the uint32_t. The uint32_t is enforced to be
 *  as BGRA, so the actual order of this struct is a, r, g, b.
 *  On the other hand, if the architecture is big endian, the uint32_t is
 *  still forced to be BGRA, so the first element of this struct will be the
 *  Blue component, mapping to the most significant byte.
 */
struct Texel
{
#ifndef IS_BIG_ENDIAN
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;
#else
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
#endif
};

/**
 * \brief Union between an uint32_t texel and the Texel struct
 *
 *  This union is used to have both access to single components in an endiannes
 *  indipendent way (by using the bgra_texel member) or to get the uint32_t
 *  representing the entire value (by using the bgra_value member)
 */
union TexelUnion
{
    Texel bgra_texel;
    uint32_t bgra_value;
};

///Max eccentricity value for EWA filtering ellipse. Bounds EWA to constant time
#define EWA_MAX_ECCENTRICITY 30.f

///Defines the number of entries in the EWA_WEIGHTS lookup table
#define EWA_WEIGHTS_SIZE 128

///Value used in the EWA_WEIGHTS precomputation
//TODO: removed because macOS does not support constexpr expf(). Harcoded table
//#define EWA_ALPHA 2.f

/**
 *  \brief ImageMap
 *  Class representing an allocated image used for texture storage.
 *  Being specialized in texture storage, the ImageMap imposes two
 *  constraints: the width and height are expected to be equal and a power of
 *  two.
 *
 *  This class is different from ImageFilm: this one is specialized in texture
 *  reading and texture storage on memory, while ImageFilm class is used for the
 *  final image buffer and the multithreaded addition and filtering of samples
 *  aswell as image saving onto disk.
 *
 *  This class is thread-safe.
 */
class ImageMap
{

public:

    /**
     *  \brief Constructs an ImageMap with 8-bit per component
     *
     *  Constructor used to allocate an ImageMap where each value is a 32 bit
     *  represented color, with each channel in range [0-255] and BGRA order.
     *  The width and height of the image must be equals and power of two.
     *  MIPmaps necessary for the ImageMap to work are allocated inside this
     *  constructor, so the final ImageMap size will be 33% bigger than the
     *  original image
     *
     *  \param[in] values An array holding every value that will be used by the
     *  ImageMap.
     *  \param[in] side The width and height of the input image.
     */
    ImageMap(const pixBGRA* values, uint16_t side);

    ///No copy allowed
    ImageMap(const ImageMap& old) = delete;

    ///Default destructor
    virtual ~ImageMap();

    /**
     *  \brief Performs filtering over the texture
     *
     *  The filter function is a function pointer that will be used to setup
     *  a filtering function for this ImageMap. At every call of this function
     *  the filtered value will be retrieved from the texture
     *
     *  \param[in] u u value of the texture mapping
     *  \param[in] v v value of the texture mapping
     *  \param[in] dudx differential for the u value, when the ray is shifted
     *  on the x axis
     *  \param[in] dvdx differential for the u value, when the ray is shifted
     *  on the y axis
     *  \param[in] dudy differential for the v value, when the ray is shifted
     *  on the x axis
     *  \param[in] dvdy differential for the v value, when the ray is shifted
     *  on the y axis
     *  \return The filtered pixel value
     */
    virtual TexelUnion filter(float u, float v, float dudx, float dvdx,
                              float dudy, float dvdy) const = 0;

    /**
     *  \brief Returns the side of the ImageMap
     *
     *  The returned value refers to the top level of the pyramid
     *
     *  \return An int specifying the side of the texture
     */
    uint16_t get_side() const;

protected:

    /**
     *  \brief Performs bilinear interpolation between texels
     *
     *  Given the fact that u and v parameters are continuous, while a texture
     *  image is discrete, this method performs a linear interpolation in the 2D
     *  space between the 4 nearest pixels to the (u,v) mapped point. Note that
     *  if the point happens to be on the border, the underlying texture is
     *  wrapped
     *
     *  \param[in] u u mapping parameter, in range [0-1]
     *  \param[in] v v mapping parameter, in range [0-1]
     *  \param[in] level The chosen MIPmap level. This value should be
     *  delegated to the filtering algorithm
     *  \return The filtered texel color
     */
    TexelUnion bilinear(float u, float v, uint8_t level) const;

    ///width or height of every MIPmap level
    uint16_t* side;

    ///number of MIPmaps
    uint8_t maps_no;

    ///Array holding every MIPmap level
    Array2D<TexelUnion>** MIPmap;
};

/**
 *  \brief ImageMap class that performs filtering by using a NN filter
 *
 *  The Nearest Neighbour filter maps the continuous (u,v) value to the nearest
 *  discrete texel found in the texture. Although this is source of aliasing, it
 *  is fast and behaves well in highly sampled images
 */
class ImageMapUnfiltered : public ImageMap
{

public:

    using ImageMap::ImageMap;

    /**
     *  \brief Performs filtering over the texture
     *
     *  The filter function is a function pointer that will be used to setup
     *  a filtering function for this ImageMap. At every call of this function
     *  the filtered value will be retrieved from the texture
     *
     *  \param[in] u u value of the texture mapping in range [0-1]
     *  \param[in] v v value of the texture mapping in range [0-1]
     *  \param[in] dudx differential for the u value, when the ray is shifted
     *  on the x axis
     *  \param[in] dvdx differential for the u value, when the ray is shifted
     *  on the y axis
     *  \param[in] dudy differential for the v value, when the ray is shifted
     *  on the x axis
     *  \param[in] dvdy differential for the v value, when the ray is shifted
     *  on the y axis
     *  \return The filtered pixel value
     */
    TexelUnion filter(float u, float v, float dudx, float dvdx,
                      float dudy, float dvdy) const override;
};

/**
 *  \brief ImageMap class that performs filtering by using a Trilinear filter
 *
 *  The Trilinear filter performs 2D linear interpolation between the 4
 *  nearest pixel to the mapped (u,v) point. Since the correct distance may fall
 *  between two MIPmap levels, the interpolation is done also between the
 *  retrieved values of these MIPmap levels. This grants a decent performance
 *  while eliminating most of the aliasing typical of the NN filtering.
 *  Note that trilinear filter blurs textures seen over oblique surfaces
 *
 */
class ImageMapTrilinear : public ImageMap
{

public:

    using ImageMap::ImageMap;

    /**
     *  \brief Performs filtering over the texture
     *
     *  The filter function is a function pointer that will be used to setup
     *  a filtering function for this ImageMap. At every call of this function
     *  the filtered value will be retrieved from the texture. If the uv maps
     *  on the border of the texture, the texture will be wrapped
     *
     *  \param[in] u u value of the texture mapping in range [0-1]
     *  \param[in] v v value of the texture mapping in range [0-1]
     *  \param[in] dudx differential for the u value, when the ray is shifted
     *  on the x axis
     *  \param[in] dvdx differential for the u value, when the ray is shifted
     *  on the y axis
     *  \param[in] dudy differential for the v value, when the ray is shifted
     *  on the x axis
     *  \param[in] dvdy differential for the v value, when the ray is shifted
     *  on the y axis
     *  \return The filtered pixel value
     */
    TexelUnion filter(float u, float v, float dudx, float dvdx,
                      float dudy, float dvdy) const override;
};

/**
 *  \brief ImageMap class that performs filtering by using an EWA filter
 *
 *  State of the art texture filtering. EWA filter is the slowest one but does
 *  not suffer blurring or aliasing. However, consider that if the number of
 *  samples is high, Trilinear or NN filtering will still converge to the
 *  correct value while granting less computational time
 */
class ImageMapEWA : public ImageMap
{

public:

    using ImageMap::ImageMap;

    /**
     *  \brief Performs filtering over the texture
     *
     *  The filter function is a function pointer that will be used to setup
     *  a filtering function for this ImageMap. At every call of this function
     *  the filtered value will be retrieved from the texture
     *
     *  \param[in] u u value of the texture mapping
     *  \param[in] v v value of the texture mapping
     *  \param[in] dudx differential for the u value, when the ray is shifted
     *  on the x axis
     *  \param[in] dvdx differential for the u value, when the ray is shifted
     *  on the y axis
     *  \param[in] dudy differential for the v value, when the ray is shifted
     *  on the x axis
     *  \param[in] dvdy differential for the v value, when the ray is shifted
     *  on the y axis
     *  \return The filtered pixel value
     */
    TexelUnion filter(float u, float v, float dudx, float dvdx,
                      float dudy, float dvdy) const override;

private:

    /**
     *  \brief Table storing precomputed gaussian values
     *  This table stores the precomputed values of e^-radius*radius*alpha,
     *  which are used in the EWA filtering method. The value of alpha is 2.0
     */
    static const float EWA_WEIGHTS[EWA_WEIGHTS_SIZE];

    //Performs the actual ewa filtering
    TexelUnion ewa(float u, float v, float dudx, float dvdx, float dudy,
                   float dvdy, uint8_t level) const;
};

#endif
