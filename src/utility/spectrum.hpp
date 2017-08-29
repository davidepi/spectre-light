//Created,  29 Aug 2017
//Last Edit 29 Aug 2017

#ifndef __SPECTRUM_HPP__
#define __SPECTRUM_HPP__

#include "utility/color.hpp"

enum SpectrumType {BLACK, WHITE, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW};

class Spectrum
{
public:
    
    Spectrum();
    Spectrum(SpectrumType);
    
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
    float nm400;
    float nm420;
    float nm440;
    float nm460;
    float nm480;
    float nm500;
    float nm520;
    float nm540;
    float nm560;
    float nm580;
    float nm600;
    float nm620;
    float nm640;
    float nm660;
    float nm680;
    float nm700;
};

#endif
