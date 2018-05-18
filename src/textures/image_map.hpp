//Created,   7 May 2018
//Last Edit 17 May 2018

/**
 *  \file image_map.hpp
 *  \brief     A square image
 *  \details   A square, power of 2, image used inside TextureImage as a MIPMap
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      17 May 2018
 *  \copyright GNU GPLv3
 */


#ifndef __IMAGE_MAP_HPP__
#define __IMAGE_MAP_HPP__

#include "utility/file.hpp"
#include "utility/imageIO.hpp"
#include "samplers/filter_box.hpp"
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

    //this class is mostly hidden behind the scenes, and an error should be
    //detected as soon as possible during testing
#ifndef TESTS
private:
#endif
    
    ///actual constructor, the others will initialize path and call this one
    void init();
    
    ///Path of the image on disk
    const File path;

    ///width or height
    unsigned short size;
    
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
