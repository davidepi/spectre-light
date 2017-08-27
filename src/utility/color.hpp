//Created,  23 May 2017
//Last Edit 15 Jun 2017
/**
 *  \file color.hpp
 *  \brief Spectrum and colours representations
 *  \details Contains a class to approximate the representation of the visible
 *  spectrum
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date 15 June 2017
 *  \copyright GNU GPLv3
 */


#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <cstring>
#include <cstdlib>

/**
 *  \class Color color.hpp "utility/color.hpp"
 *  \brief The representation of a visibile colour
 *
 *  Color class contains an approximation of the visible spectrum. Instead of
 *  storing several samples of the spectral wave, this class stores the weighted
 *  sum of red, green and blue values. These correspond to the following
 *  wavelengths: Red 700.47nm, Green 546.09nm, Blue 455.79nm
 *
 *  This sacrifices precision, however, the supplied input will most likely be
 *  in RGB form.
 */
class Color
{
public:

    /** \brief Default Constructor
     *
     *  Create a color with a value of 0.0 for each component, representing
     *  the black color
     */
    Color();

    /** \brief Default Constructor, given components values
     *
     *  Create a color with the given value for each component
     *
     *  \param r The value of the red component
     *  \param g The value of the green component
     *  \param b The value of the blue component
     */
    Color(float r, float g, float b);

    /** \brief Default Constructor, given a single component value
     *
     *  Create a color with the given value repeated for every component.
     *  This will create a greyscale colour.
     *
     *  \param rgb The value of the red, green and blue components
     */
    Color(float rgb);

    /** \brief Default Constructor, given hex value
     *
     *  Create a color with the given components values, encoded as hex string
     *  in the form #RRGGBB or #RGB which will be translated to #RRGGBB aswell
     *
     *  \param hex The value of the red, green and blue components encoded as an
     *  hex string
     */
    Color(const char* hex);

    ///Default destructor
    ~Color();

    /** \brief Return true if the color is black
     *  \return true if every component is zero
     */
    bool isBlack()const;
    
    ///Red component
    float r;
    
    ///Green component
    float g;
    
    ///Blue component
    float b;

    // <><><><> Operators <><><><><><><><><><><><><><><><><><><><><><><><><><><>

    ///The addition operation between two colours
    Color operator+(const Color& c)const;
    ///The addition operation between two colours
    void operator+=(const Color& c);
    ///The subtraction operation between two colours
    Color operator-(const Color& c)const;
    ///The subtraction operation between two colours
    void operator-=(const Color& c);
    ///The multiplication operation between two colours
    Color operator*(const Color& c)const;
    ///The multiplication operation between two colours
    void operator*=(const Color& c);
    ///The division operation between two colours
    Color operator/(const Color& c)const;
    ///The division operation between two colours
    void operator/=(const Color& c);
    ///The addition operation between a value and a colour
    Color operator+(float c)const;
    ///The addition operation between a value and a colour
    void operator+=(float c);
    ///The subtraction operation between a value and a colour
    Color operator-(float c)const;
    ///The subtraction operation between a value and a colour
    void operator-=(float c);
    ///The multiplication operation between a value and a colour
    Color operator*(float c)const;
    ///The multiplication operation between a value and a colour
    void operator*=(float c);
    ///The division operation between a value and a colour
    Color operator/(float c)const;
    ///The division operation between a value and a colour
    void operator/=(float c);

    // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
};

#endif
