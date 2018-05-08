//Created,   7 May 2018
//Last Edit  7 May 2018

/**
 *  \file image_map.hpp
 *  \brief     A square image
 *  \details   A square, power of 2, image used inside TextureImage as a MIPMap
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      7 May 2018
 *  \copyright GNU GPLv3
 */


#ifndef __IMAGE_MAP_HPP__
#define __IMAGE_MAP_HPP__

#include "textures/texture.hpp"
#include "samplers/filter_lanczos.hpp"

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

/**
 *  \brief ImageMap
 *  Class representing an allocated image used for texture storage.
 *  Being specialized in texture storage, the ImageMap imposes two
 *  constraints: the width and height are expected to be equal and a power of
 *  two.
 *  This class comes in two different flavours: high dpi and normal dpi and
 *  this is done to save space on memory. For this reason if the high dpi
 *  constructor is used but every value could be represented by a normal dpi
 *  image this one will be used.
 */
class ImageMap
{
public:
    
    ///Default constructor, allocates an empy image of size 0x0
    ImageMap();
    
    /** \brief Allocates an image with the given values
     *
     *  Allocates an image of size side*side and uses the given values to
     *  initialize it. The values must be in range [0-255].
     *
     *  \param[in] source The values used for the image, in range [0-255]
     *  \param[in] side The width and height of the image
     */
    ImageMap(const uint8_t* source, int side);
    
    /** \brief Allocates an image with the given values (high dpi version)
     *
     *  Allocates an image of size side*side and uses the given values to
     *  initialize it. The values must be in range [0.0-1.0] and aren't limited
     *  to 8-bit. Note that if this constructor detects that the values could
     *  fit in range [0-255] it will convert them automatically in order to save
     *  memory space
     *
     *  \param[in] source The values used for the image, in range [0.0-1.0]
     *  \param[in] side The width and height of the image
     */
    ImageMap(const float* source, int side);
    
    ///Copy constructor
    ImageMap(const ImageMap &old);
    
    /** \brief Copy constructor, with the possibility to resize the map
     *
     *  Copy the input ImageMap, and, if the halves parameter is true, halves
     *  its size. This kind of copy constructor is very useful to create the
     *  various MIP Maps
     *
     *  \param[in] old The ImageMap that will be copied
     *  \param[in] halves true if the copied ImageMap will be half the size of
     *  the old one
     */
    ImageMap(const ImageMap &old, bool halves);
    
    ///Default destructor
    ~ImageMap();
    
private:
    
    ///width or height
    unsigned short size;
    
    ///true if the image uses floats instead of uint8_ts
    bool high_depth;
    union
    {
        ///array of uint8_t
        Texel* values;
        
        ///array of float
        Texel32* values_high;
    };
};

#endif
