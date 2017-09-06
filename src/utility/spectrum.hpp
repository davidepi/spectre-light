//Created,  29 Aug 2017
//Last Edit  6 Sep 2017

/**
 *  \file spectrum.hpp
 *  \brief Colours representations using wavelength spectrum
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date 6 Sep 2017
 *  \copyright GNU GPLv3
 */


#ifndef __SPECTRUM_HPP__
#define __SPECTRUM_HPP__

#include "utility/color.hpp"
#include "settings.h"

#if HQ_SPECTRUM==0
#define SPECTRUM_SAMPLES 16
#else
#define SPECTRUM_SAMPLES 31
#endif

/**
 *  \class Spectrum spectrum.hpp "utility/spectrum.hpp"
 *  \brief The representation of a visibile colour
 *
 *  Spectrum class contains an approximation of the visible spectrum. It 
 *  represents a colour by sampling its EM spectrum. The samples span the range 
 *  400nm to 700nm (included) with an interval of either 20nm or 10nm if the
 *  macro HQ_SPECTRUM is set to 1
 */
class Spectrum
{
public:
    
    ///Default constructor, does nothing
    Spectrum();
    
    /** \brief Initialize the spectrum given the temperature
     *
     *  Consider this spectrum as an emission from a blackbody and initialize it
     *  based on the temperature of the object.
     *  The value 0 is used as an efficient way to indicate a black spectrum.
     *
     *  \param[in] temperature The temperature of the body, in Kelvin degrees
     */
    Spectrum(int temperature);
    
    /** \brief Initialize the spectrum with a constant value
     *
     *  \param[in] val The value of the spectrum
     */
    Spectrum(float val);
    
    /** \brief Initialize the spectrum with the given values
     *
     *  Initialize this class by filling it with the given values
     *
     *  \param[in] vals The values, sorted by nm, used for this spectrum
     */
    Spectrum(const float* vals);
    
    /** \brief Attempt to convert an sRGB colour to a spectrum
     *
     *  Although an exact answer is impossible, this constructor tries to
     *  create a spectrum given an RGB colour. Note that multiple spectra can
     *  have the same RGB colour, so this method being a one-to-many can lead
     *  to unexpected results
     *
     *  \param[in] c The RGB colour that will be converted
     *  \param[in] light true if the colour is a light source
     */
    Spectrum(ColorRGB c, bool light);
    
    /** \brief Convert this spectrum to its XYZ representation
     *
     *  \return The XYZ representation of this spectrum
     */
    ColorXYZ toXYZ()const;
    
    /** \brief Calculate the luminous intensity of this spectrum
     *
     *  Calculate only the Y value of the XYZ color represented by this 
     *  spectrum. This value is used to represent the luminance
     *
     *  \return The luminous intensity of this spectrum
     */
    float luminance()const;
    
    /** \brief Retun true if the spectrum is composed only by 0 values
     * 
     *  \return true if only 0 values compose this spectrum
     */
    bool isBlack()const;
    
    ///The addition operation between two spectra
    Spectrum operator+(const Spectrum& s)const;
    ///The addition operation between two spectra
    void operator+=(const Spectrum& s);
    ///The subtraction operation between two spectra
    Spectrum operator-(const Spectrum& s)const;
    ///The subtraction operation between two spectra
    void operator-=(const Spectrum& s);
    ///The multiplication operation between two spectra
    Spectrum operator*(const Spectrum& s)const;
    ///The multiplication operation between two spectra
    void operator*=(const Spectrum& s);
    ///The division operation between two spectra
    Spectrum operator/(const Spectrum& s)const;
    ///The division operation between two spectra
    void operator/=(const Spectrum& s);
    ///The addition operation between a value and a spectrum
    Spectrum operator+(float v)const;
    ///The addition operation between a value and a spectrum
    void operator+=(float v);
    ///The subtraction operation between a value and a spectrum
    Spectrum operator-(float v)const;
    ///The subtraction operation between a value and a spectrum
    void operator-=(float v);
    ///The multiplication operation between a value and a spectrum
    Spectrum operator*(float v)const;
    ///The multiplication operation between a value and a spectrum
    void operator*=(float v);
    ///The division operation between a value and a spectrum
    Spectrum operator/(float v)const;
    ///The division operation between a value and a spectrum
    void operator/=(float v);
    
    //private:
    
    //wavelength samples
    float w[SPECTRUM_SAMPLES];
};

///Spectrum of white surfaces
extern const Spectrum SPECTRUM_WHITE;
///Spectrum composed of 0 values
extern const Spectrum SPECTRUM_BLACK;

#endif
