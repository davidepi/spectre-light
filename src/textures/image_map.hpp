//Created,   7 May 2018
//Last Edit 13 Jul 2018

/**
 *  \file image_map.hpp
 *  \brief     Helper classes used to handle Images used as textures
 *  \details   ImageMap class, a square, power of 2, image used inside
 *             TextureImage as a MIPMap.
 *             Several other classes are provided to cope with varying texel
 *             size and filtering methods
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      13 Jul 2018
 *  \copyright GNU GPLv3
 */


#ifndef __IMAGE_MAP_HPP__
#define __IMAGE_MAP_HPP__

#include "utility/file.hpp"
#include "utility/imageio/imageio.h"
#include "samplers/filter_box.hpp"
#include "samplers/filter_lanczos.hpp"
#include "utility/spectrum.hpp"
#include "utility/utility.hpp" //swap
#include <cstdlib> //malloc/free
#include <cmath> //sqrtf
#include <array> //EWA weights allocation

//forward declaration to be used in TexelMap
class ImageMap;

enum TextureFilter_t
{
    UNFILTERED,
    TRILINEAR,
    EWA
};

///Pixel component of a texture, 24-bit version
struct Texel
{
    ///Red component in range [0-255]
    uint8_t r;

    ///Green component in range [0-255]
    uint8_t g;

    ///Blue component in range [0-255]
    uint8_t b;
};

///Pixel component of a texture, high dpi version
struct Texel32
{
    ///Red component in range [0-1]
    float r;

    ///Green component in range [0-1]
    float g;

    ///Blue component in range [0-1]
    float b;
};

///Max eccentricity value for EWA filtering ellipse. Bounds EWA to constant time
#define EWA_MAX_ECCENTRICITY 30.f

///Defines the number of entries in the EWA_WEIGHTS lookup table
#define EWA_WEIGHTS_SIZE 128

///Value used in the EWA_WEIGHTS precomputation
//TODO: removed because macOS does not support constexpr expf(). Harcoded table
//#define EWA_ALPHA 2.f

/**
 *  \brief Struct used to hold a single mipmap level
 *  The TexelMap struct is used to allocate a single MIPmap level and access its
 *  texels.
 */
struct TexelMap
{
public:

    ///Default destructor
    virtual ~TexelMap();

    /**
     *  \brief Returns a specific texel of the MIPmap in the form of a Texel32
     *  \param[in] lvl1 The index of the texel
     *  \param[out] out The Texel32 struct that will hold the texel
     */
    virtual void get_texel(int lvl1, Texel32* out) const = 0;

    /**
     *  \brief Returns a specific texel of the MIPmap in the form of ColorRGB
     *  \param[in] lvl1 The index of the texel
     *  \param[out] out A ColorRGB class representing the found texel
     */
    virtual void get_color(int lvl1, ColorRGB* out) const = 0;

    /**
     *  \brief Converts a specific texel of the MIPmap in the form of ColorRGB
     *  This is used because the retrieved Texel32 will not always be in range
     *  [0-1]
     *
     *  \note This is used primarly because Texel32 returned by TexelMapLow and
     *  TexelMapHigh uses different ranges ([0-255] or [0-1])
     *
     *  \param[in] in The index of the texel
     *  \param[out] out The ColorRGB class that will hold the texel
     */
    virtual void get_color(Texel32& in, ColorRGB* out) const = 0;

    /**
     *  \brief Sets the color of a specific texel, given the input ColorRGB
     *  \param[in] lvl1 The texel that will be changed
     *  \param[in] val ColorRGB class holding the new value for the texel
     */
    virtual void set_color(int lvl1, const ColorRGB& val) = 0;
};

/**
 *  \brief Struct used to hold a single MIPmap level.
 *  This struct contains a MIPmap level composed of uint8_t values per single
 *  pixel, for a total of width*height*3 values. No alpha channel is supported.
 *  The image must have equal width and height
 *  Values are in range [0-255]
 */
struct TexelMapLow : TexelMap
{
public:

    /**
     *  \brief Constructs the TexelMap given the array of values
     *  \param[in] values An array of size side*side*3 with each pixel composing
     *  the MIPmap ordered by row from top to bottom, in range [0-255]
     *  \param[in] side The value of width or height of the map. Recall that
     *  these two values must be the same
     */
    TexelMapLow(const uint8_t* values, uint16_t side);

    //no copy allowed
    TexelMapLow(const TexelMapLow&) = delete;

    ///Default destructor
    ~TexelMapLow() override;

    /**
     *  \brief Returns a specific texel of the MIPmap in the form of a Texel32
     *  \param[in] lvl1 The index of the texel
     *  \param[out] out The Texel32 struct that will hold the texel
     *
     *  /note Returned values will be in range [0-255] instead of the usual
     *  [0-1] used in Texel32, one should use get_color(Texel32,ColorRGB) to
     *  convert between the two
     */
    void get_texel(int lvl1, Texel32* out) const override;

    /**
     *  \brief Converts a specific texel of the MIPmap in the form of ColorRGB
     *  This is used because the retrieved Texel32 will not always be in range
     *  [0-1]
     *
     *  \note This is used primarly because Texel32 returned by TexelMapLow and
     *  TexelMapHigh uses different ranges ([0-255] or [0-1])
     *
     *  \param[in] in The index of the texel
     *  \param[out] out The ColorRGB class that will hold the texel
     */
    void get_color(Texel32& in, ColorRGB* out) const override;

    /**
     *  \brief Returns a specific texel of the MIPmap in the form of ColorRGB
     *  \param[in] lvl1 The index of the texel
     *  \param[out] out A ColorRGB class representing the found texel
     */
    void get_color(int lvl1, ColorRGB* out) const override;

    /**
     *  \brief Sets the color of a specific texel, given the input ColorRGB
     *  \param[in] lvl1 The texel that will be changed
     *  \param[in] val ColorRGB class holding the new value for the texel
     */
    void set_color(int lvl1, const ColorRGB& val) override;

private:

    Texel* values;
};

/**
 *  \brief Struct used to hold a single MIPmap level.
 *  This struct contains a MIPmap level composed of float values per single
 *  pixel, for a total of width*height*3 values. No alpha channel is supported.
 *  The image must have equal width and height
 *  Values are in range [0-1]
 */
struct TexelMapHigh : TexelMap
{
public:

    /**
     *  \brief Constructs the TexelMap given the array of values
     *  \param[in] values An array of size side*side*3 with each pixel composing
     *  the MIPmap ordered by row from top to bottom in range [0.0-1.0]
     *  \param[in] side The value of width or height of the map. Recall that
     *  these two values must be the same
     */
    TexelMapHigh(const float* values, uint16_t side);

    //no copy allowed
    TexelMapHigh(const TexelMapHigh&) = delete;

    ///Default destructor
    ~TexelMapHigh() override;

    /**
     *  \brief Returns a specific texel of the MIPmap in the form of a Texel32
     *  \param[in] lvl1 The index of the texel
     *  \param[out] out The Texel32 struct that will hold the texel
     */
    void get_texel(int lvl1, Texel32* out) const override;

    /**
     *  \brief Converts a specific texel of the MIPmap in the form of ColorRGB
     *  This is used because the retrieved Texel32 will not always be in range
     *  [0-1]
     *
     *  \note This is used primarly because Texel32 returned by TexelMapLow and
     *  TexelMapHigh uses different ranges ([0-255] or [0-1])
     *
     *  \param[in] in The index of the texel
     *  \param[out] out The ColorRGB class that will hold the texel
     */
    void get_color(Texel32& in, ColorRGB* out) const override;

    /**
     *  \brief Returns a specific texel of the MIPmap in the form of ColorRGB
     *  \param[in] lvl1 The index of the texel
     *  \param[out] out A ColorRGB class representing the found texel
     */
    void get_color(int lvl1, ColorRGB* out) const override;

    /**
     *  \brief Sets the color of a specific texel, given the input ColorRGB
     *  \param[in] lvl1 The texel that will be changed
     *  \param[in] val ColorRGB class holding the new value for the texel
     */
    void set_color(int lvl1, const ColorRGB& val) override;

private:

    Texel32* values;
};

/**
 *  \brief ImageMap
 *  Class representing an allocated image used for texture storage.
 *  Being specialized in texture storage, the ImageMap imposes two
 *  constraints: the width and height are expected to be equal and a power of
 *  two.
 *  This class comes in two different flavours: high depth and 24-bit depth and
 *  this is done to save space on memory. For this reason if the high depth
 *  constructor is used but every value could be represented by a 24-bit depth
 *  image this one will be used. High depth images are represented using 32 bit
 *  floating point values, so the limit of the image is the precision ensured by
 *  the float data type.
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
     *  Constructor used to allocate an ImageMap where each value is an 8 bit
     *  unsigned integer, in range [0-255]. The width and height of the image
     *  must be equals and power of two. MIPmaps necessary for the ImageMap to
     *  work are allocated inside this constructor, so the final ImageMap size
     *  will be 33% bigger than the original image
     *
     *  \param[in] values An array holding every value that will be used by the
     *  ImageMap.
     *  \param[in] side The width and height of the input image.
     */
    ImageMap(const uint8_t* values, uint16_t side);

    /**
     *  \brief Constructs an ImageMap with 32-bit per component
     *
     *  Constructor used to allocate an ImageMap where each value is a 32-bit
     *  floating point, in range [0.0-1.0]. The width and height of the image
     *  must be equals and power of two. MIPmaps necessary for the ImageMap to
     *  work are allocated inside this constructor, so the final ImageMap size
     *  will be 33% bigger than the original image
     *
     *  \param[in] values An array holding every value that will be used by the
     *  ImageMap.
     *  \param[in] side The width and height of the input image.
     */
    ImageMap(const float* values, uint16_t side);

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
    virtual ColorRGB filter(float u, float v, float dudx, float dvdx,
                            float dudy, float dvdy) const = 0;

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
    ColorRGB bilinear(float u, float v, uint8_t level) const;

    ///width or height of every MIPmap level
    uint16_t* side;

    ///number of MIPmaps
    uint8_t maps_no;

    ///Array holding every MIPmap level
    TexelMap** MIPmap;
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
    ColorRGB filter(float u, float v, float dudx, float dvdx,
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
    ColorRGB filter(float u, float v, float dudx, float dvdx,
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
    ColorRGB filter(float u, float v, float dudx, float dvdx,
                    float dudy, float dvdy) const override;

private:

    /**
     *  \brief Table storing precomputed gaussian values
     *  This table stores the precomputed values of e^-radius*radius*alpha,
     *  which are used in the EWA filtering method. The value of alpha is 2.0
     */
    static const float EWA_WEIGHTS[EWA_WEIGHTS_SIZE];

    //Performs the actual ewa filtering
    ColorRGB ewa(float u, float v, float dudx, float dvdx, float dudy,
                 float dvdy, uint8_t level) const;
};

#endif
