//Created,   7 May 2018
//Last Edit 19 Jun 2018

/**
 *  \file image_map.hpp
 *  \brief     A square image
 *  \details   A square, power of 2, image used inside TextureImage as a MIPMap
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      19 Jun 2018
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
     *  \brief Constructor given path, C-string version
     *
     *  Allocates an Image Map giving the input file as a C-string
     *
     *  \param[in] src A C-string representing the path to the image
     */
    ImageMap(const char* src);

    /**
     *  \brief Constructor given path, File version
     *
     * Allocates an ImageMap giving the input file as a File class
     *
     *  \param[in] src a File class representing the path to the image on disk
     */
    ImageMap(const File& src);

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
    ColorRGB (ImageMap::*filter)(float u, float v, float dudx, float dvdx,
                                 float dudy, float dvdy) const;

    /**
     *  \brief Sets the filtering method for this texture
     *  \param[in] type The type of filtering that will be used on this texture
     */
    void set_filter(TextureFilter_t type);

    /**
     *  \brief Table storing precomputed gaussian values
     *  This table stores the precomputed values of e^-radius*radius*alpha,
     *  which are used in the EWA filtering method. The value of alpha is
     *  defined in EWA_ALPHA
     *
     *  This is an std::array instead of a float[] so its initialization is
     *  performed at compile time with the functions found at the beginning
     *  of the textures/image_map.cpp file. For this reason it is possible to
     *  modify the values inside this array by just changing the EWA_ALPHA or
     *  EWA_WEIGHTS_SIZE parameters, instead of having to manually rewrite the
     *  entire lookup table every time
     */
    static const float EWA_WEIGHTS[EWA_WEIGHTS_SIZE];

    //this class is mostly hidden behind the scenes, and an error should be
    //detected as soon as possible during testing
#ifndef TESTS
    private:
#endif

    ///Do not perform any filtering
    ColorRGB unfiltered(float u, float v, float dudx, float dvdx, float dudy,
                        float dvdy) const;

    ///Performs linear interpolation with bilinear isotropic filter
    ColorRGB trilinear(float u, float v, float dudx, float dvdx, float dudy,
                       float dvdy) const;

    ///Performs linear interpolation with EWA filter
    ColorRGB linear_ewa(float u, float v, float dudx, float dvdx, float dudy,
                        float dvdy) const;

    ///actual constructor, the others will initialize path and call this one
    void init();

    ///Path of the image on disk
    const File path;

    ///width or height
    unsigned short* side;

    ///number of MIPmaps
    unsigned char maps_no;

    ///true if the image uses floats instead of uint8_ts
    bool high_depth;

    union
    {
        ///array of uint8_t
        Texel** values;

        ///array of float
        Texel32** values_high;
    };
};

#endif
