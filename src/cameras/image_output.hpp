//Created,  25 May 2017
//Last Edit 25 May 2017

/**
 *  \file image_output.hpp
 *  \brief     Buffer storing and saving an image, will be used by Camera
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      25 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __IMAGE_OUTPUT_HPP__
#define __IMAGE_OUTPUT_HPP__

#include "filter.hpp"
#include "box_filter.hpp"
#include "sampler.hpp"
#include "color.hpp"
#include "console.hpp"
#include <cstring>
#include <cmath>
#include <mutex>
#include <cstdio>

///Used to store the weigthed average for every pixel
struct Pixel
{
    
    ///The red value, from 0.0 to 1.0
    float r;
    
    ///The green value, from 0.0 to 1.0
    float g;
    
    ///The blue value, from 0.0 to 1.0
    float b;
    
    /**
     *  The weight of the various samples added. The final value of r,g and b
     *  have to be divided by this number
     */
    float samples;
};

/**
 * \class ImageOutput image_output.hpp "cameras/image_output.hpp"
 * \brief Class used to store an image and filter every sample
 *
 *  This class is simply a wrapper around an array of pixel, however, new 
 *  samples results can be added, and their value will be filtered and added to
 *  the correct pixels. For this reason, this class will be used by the Camera
 *  to store an instance of the final rendered image.
 *
 *  This class provides also a method for saving the image on the disk after
 *  the render
 */
class ImageOutput
{
public:
    
    /** \brief Default Constructor
     *
     *  Cosntruct an empty image with the given width, height and filename
     *  If the filename has no extension, the image will be saved as .bmp
     *
     *  \warning If ImageMagick is not installed on the system, the image can be
     *  saved only as a .bmp
     *
     *  \param[in] width The width of the image
     *  \param[in] height The height of the image
     *  \param[in] filename The name of the output image
     */
    ImageOutput(int width, int height, const char* filename);
    
    ///Default destructor
    ~ImageOutput();
    
    /** \brief Add a sample to this image
     *
     *  After rendering the image for every Sample there will be a resulting 
     *  Color.
     *  However, Sample and Color are part of a continuous function, whereas the
     *  pixel are discrete. This method maps these continuous values to the
     *  discrete values of the pixels, updating every affected pixel in a
     *  weighted way. The weight is defined by the filter.
     *
     *  This function is thread-safe
     *
     *  \warning By default filter is unset, remember to set it with
     *  ImageOutput::setFilter
     *
     *  \param[in] sample The sampled point
     *  \param[in] c The color value of the sampled point
     */
    void addPixel(Sample* sample, Color* c);
    
    /** \brief Set a Filter for this image
     *
     *  Set the Filter that will be used to filter the various samples and 
     *  weight their contribution to every pixel.
     *
     *  \param[in] f A pointer to the filter that will be used
     */
    void setFilter(Filter* f);
    
    /** \brief Store the image on the disk
     *
     *  After adding every sample, by calling this method the resulting image
     *  will be saved on disk, at the path given when constructing the object.
     *  If for a pixel there were no samples, the output value will be 0 0 0
     *
     *  \return true if the image has been stored, false otherwise
     */
    bool saveImage();
    
private:
    
    //width of the image
    const int width;
    
    //height of the image
    const int height;
    
    //filter
    Filter* f;
    
    //the buffer of the image
    Pixel* image;
    
    //filename of the image
    char* filename;
    
    //mutex for concurrent write
    std::mutex mtx;
};

#endif
