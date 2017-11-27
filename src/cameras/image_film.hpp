//Created,  25 May 2017
//Last Edit 27 Nov 2017

/**
 *  \file image_output.hpp
 *  \brief     Buffer storing and saving an image, will be used by Camera
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      27 Nov 2017
 *  \copyright GNU GPLv3
 */


#ifndef __IMAGE_FILM_HPP__
#define __IMAGE_FILM_HPP__

#define EXTENSION_NOT_SUPPORTED -1
#define EXTENSION_PPM 0
#define EXTENSION_BMP 1

#include "samplers/filter.hpp"
#include "samplers/sampler.hpp"
#include "utility/color.hpp"
#include "utility/console.hpp"
#include "utility/utility.hpp"
#include "utility/imageIO.hpp"
#include <cstring>
#include <cmath>
#include <mutex>
#include <stack>
#include <cstdio>
#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

///Used to store the weigthed average for every pixel
struct Pixel
{
    
    ///The CIE X value, from 0.0 to 1.0
    float cie_x;
    
    ///The CIE Y value, from 0.0 to 1.0
    float cie_y;
    
    ///The CIE Z value, from 0.0 to 1.0
    float cie_z;
    
    /**
     *  The weight of the various samples added. The final value of r,g and b
     *  have to be divided by this number
     */
    float samples;
};

///Like the Pixel struct, but with the added x and y position on the image plane
struct TodoPixel
{
	///The CIE X value, from 0.0 to 1.0
	float cie_x;

	///The CIE Y value, from 0.0 to 1.0
	float cie_y;

	///The CIE Z vale, from 0.0 to 1.0
	float cie_z;

	///The weight of the various samples added
	float samples;

	///The x position of the pixel on the image plane
	int x;

	///The y position of the pixel on the image plane
	int y;
};

///Stores the rendered area and where to put the pixel samples
struct ExecutorData
{
	///The starting x point of the sub-image
	int startx;

	///The ending x point of the sub-image
	int endx;

	///The starting y point of the sub-image
	int starty;

	///The ending y point of the sub-image
	int endy;

	///If the pixel is in a critical area it will be put here
	std::stack<TodoPixel> deferred;
};

/**
 * \class ImageFilm image_film.hpp "cameras/image_film.hpp"
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
class ImageFilm
{
public:
    
    /** \brief Default Constructor
     *
     *  Cosntruct an empty image with the given width, height and filename
     *  If the filename has no extension, the image will be saved as .bmp
     *
     *  \param[in] width The width of the image
     *  \param[in] height The height of the image
     *  \param[in] filename The name of the output image
     */
    ImageFilm(int width, int height, const char* filename);
    
    ///Default destructor
    ~ImageFilm();
    
    /** \brief Add a sample to this image
     *
     *  After rendering the image for every Sample there will be a resulting 
     *  Color.
     *  However, Sample and Color are part of a continuous function, whereas the
     *  pixel are discrete. This method maps these continuous values to the
     *  discrete values of the pixels, updating every affected pixel in a
     *  weighted way. The weight is defined by the filter.
     *
     *  If the pixel to be updated is in a critical area, outside of the
	 *	ExecutorData bounds, the pixel is put in the ExecutorData stack for
	 *	deferred processing
	 *
     *  \warning By default filter is unset, remember to set it with
     *  ImageOutput::setFilter
     *
     *  \param[in] sample The sampled point
     *  \param[in] c The color value of the sampled point
	 *	\param[in,out] ex A struct containing the rendered sub-image coordinates
	 *	and where to put the pixel values that cannot be updated. For these 
	 *	values a mutex will be used.
	 *	\sa deferredAddPixel(const ExecutorData* ex);
	 *	\sa forceAddPixel(const ExecutorData* ex);
     */
    void addPixel(const Sample* sample, ColorXYZ c, ExecutorData* ex);


	/** \brief Attempts the addition of pixels in critical areas
	 *	
	 *	When using the addPixel method, every pixel that could be influenced by
	 *	samples of other rendering thread is put on the ExecutorData struct.
	 *	This method tries the addition of these values in a thread safe way.
	 * 	If the mutex is already locked nothing is done, otherwise the
	 *	ExecutorData stack is emptied
	 *
	 *	\param[in] ex The struct containing all the pixel values that will be
	 *	updated
	 *	\sa addPixel(const Sample* sample, const Color* c, ExecutorData* ex);
	 *	\sa forceAddPixel(ExecutorData* ex);
	 */
	void deferredAddPixel(ExecutorData* ex);

	/** \brief Force the addition of pixels in critical areas
	 *	
	 *	When using the addPixel method, every pixel that could be influenced by
	 *	samples of other rendering thread is put on the ExecutorData struct.
	 *	This method force the addition of these values in a thread safe way.
	 *
	 *	\param[in] ex The struct containing all the pixel values that will be
	 *	updated
	 *	\sa addPixel(const Sample* sample, const Color* c, ExecutorData* ex);
	 *	\sa deferredAddPixel(const ExecutorData* ex);
	 */
	void forceAddPixel(ExecutorData* ex);
    
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
    
    //extesion of the file, using the defines at the beginning of this .hpp
    char extension;
    
    //mutex for concurrent write
    std::mutex mtx;
};

#endif
