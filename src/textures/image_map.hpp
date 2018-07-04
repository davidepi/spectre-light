//Created,   7 May 2018
//Last Edit 22 Jun 2018

/**
 *  \file image_map.hpp
 *  \brief     A square image
 *  \details   A square, power of 2, image used inside TextureImage as a MIPMap
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      22 Jun 2018
 *  \copyright GNU GPLv3
 */


#ifndef __IMAGE_MAP_HPP__
#define __IMAGE_MAP_HPP__

#include "utility/file.hpp"
#include "utility/imageIO.hpp"
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

struct TexelMap
{
public:
    virtual ~TexelMap();
    
    virtual void get_texel(int lvl1, Texel32* out) const = 0;

    virtual void get_color(Texel32& in, ColorRGB* out) const = 0;

    virtual void get_color(int lvl1, ColorRGB* out) const = 0;

    virtual void set_color(int lvl1, const ColorRGB& val) const = 0;
};

struct TexelMapLow : TexelMap
{
public:
    
    TexelMapLow(const uint8_t* values, uint16_t side);
    
    ~TexelMapLow();
    
    virtual void get_texel(int lvl1, Texel32* out) const;
    
    virtual void get_color(Texel32& in, ColorRGB* out) const;
    
    virtual void get_color(int lvl1, ColorRGB* out) const;
    
    virtual void set_color(int lvl1, const ColorRGB& val) const;
private:
    Texel* values;
};

struct TexelMapHigh : TexelMap
{
public:
    
    TexelMapHigh(const float* values, uint16_t side);
    ~TexelMapHigh();
    
    void get_texel(int lvl1, Texel32* out) const override;

    void get_color(Texel32& in, ColorRGB* out) const override;

    void get_color(int lvl1, ColorRGB* out) const override;

    void set_color(int lvl1, const ColorRGB& val) const override;
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

    ImageMap(const uint8_t* values, uint16_t side);

    ImageMap(const float* values, uint16_t side);

    ///No copy allowed
    ImageMap(const ImageMap& old) = delete;

    ///Default destructor
    ~ImageMap();

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
    ColorRGB bilinear(float u, float v, uint8_t level) const;

    ///width or height
    uint16_t* side;

    ///number of MIPmaps
    uint8_t maps_no;

    TexelMap** MIPmap;
};

class ImageMapUnfiltered : public ImageMap
{
public:
    using ImageMap::ImageMap;

    ColorRGB filter(float u, float v, float dudx, float dvdx,
                    float dudy, float dvdy) const override;
};

class ImageMapTrilinear : public ImageMap
{
public:
    using ImageMap::ImageMap;

    ColorRGB filter(float u, float v, float dudx, float dvdx,
                    float dudy, float dvdy) const override;
};

class ImageMapEWA : public ImageMap
{
public:
    using ImageMap::ImageMap;

    ColorRGB filter(float u, float v, float dudx, float dvdx,
                    float dudy, float dvdy) const override;

private:

    /**
     *  \brief Table storing precomputed gaussian values
     *  This table stores the precomputed values of e^-radius*radius*alpha,
     *  which are used in the EWA filtering method. The value of alpha is 2.0
     */
    static const float EWA_WEIGHTS[EWA_WEIGHTS_SIZE];

    ColorRGB ewa(float u, float v, float dudx, float dvdx, float dudy,
                 float dvdy, uint8_t level) const;
};

#endif
