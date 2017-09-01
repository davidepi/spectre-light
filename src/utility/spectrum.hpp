//Created,  29 Aug 2017
//Last Edit  1 Sep 2017

#ifndef __SPECTRUM_HPP__
#define __SPECTRUM_HPP__

#include "utility/color.hpp"
#include "settings.h"

#if HQ_SPECTRUM==0
#define SPECTRUM_SAMPLES 16
#else
#define SPECTRUM_SAMPLES 31
#endif

class Spectrum
{
public:
    
    Spectrum();
    Spectrum(int black);
    Spectrum(const float* vals);
    Spectrum(ColorRGB c, bool light);
    
    ColorXYZ toXYZ()const;
    float luminance()const;
    
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
    
private:
    
    float w[SPECTRUM_SAMPLES];
};

#endif
