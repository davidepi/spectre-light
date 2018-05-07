//Created,  23 May 2017
//Last Edit  5 Sep 2017

/**
 *  \file color.hpp
 *  \brief Colours representations using tristimulus values
 *  \details Contains a class to approximate the representation of the visible
 *  spectrum
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date 5 Sep 2017
 *  \copyright GNU GPLv3
 */


#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <cstring>
#include <cstdlib>
#include <cmath> //pow
#include "utility.hpp"

/**
 *  \class Color color.hpp "utility/color.hpp"
 *  \brief The representation of a visible colour
 *
 *  Color class contains an approximation of the visible spectrum. Instead of
 *  storing several samples of the spectral wave, this class stores a
 *  value composed of either Red Green and Blue component or X Y Z from the CIE
 *  standard. For better control, this class can be specialized under
 *  ColorXYZ and ColorRGB
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
     *  \param[in] r The value of the red or x component
     *  \param[in] g The value of the green or y component
     *  \param[in] b The value of the blue or z component
     */
    Color(float r, float g, float b);

    /** \brief Default Constructor, given a single component value
     *
     *  Create a color with the given value repeated for every component.
     *
     *  \param[in] rgb The value of the red, green and blue or x,y,z components
     */
    Color(float rgb);

    /** \brief Return true if the color is black
     *  \return true if every component is zero
     */
    bool is_black() const;

    ///Red or x component
    float r;

    ///Green or y component
    float g;

    ///Blue or z component
    float b;

    //------ Operators ---------------------------------------------------------

    ///The addition operation between two colours
    Color operator+(const Color& c) const;

    ///The addition operation between two colours
    void operator+=(const Color& c);

    ///The subtraction operation between two colours
    Color operator-(const Color& c) const;

    ///The subtraction operation between two colours
    void operator-=(const Color& c);

    ///The multiplication operation between two colours
    Color operator*(const Color& c) const;

    ///The multiplication operation between two colours
    void operator*=(const Color& c);

    ///The division operation between two colours
    Color operator/(const Color& c) const;

    ///The division operation between two colours
    void operator/=(const Color& c);

    ///The addition operation between a value and a colour
    Color operator+(float c) const;

    ///The addition operation between a value and a colour
    void operator+=(float c);

    ///The subtraction operation between a value and a colour
    Color operator-(float c) const;

    ///The subtraction operation between a value and a colour
    void operator-=(float c);

    ///The multiplication operation between a value and a colour
    Color operator*(float c) const;

    ///The multiplication operation between a value and a colour
    void operator*=(float c);

    ///The division operation between a value and a colour
    Color operator/(float c) const;

    ///The division operation between a value and a colour
    void operator/=(float c);

    //--------------------------------------------------------------------------
};

class ColorXYZ;

/** \brief Representeation of an RGB colour
 *
 *  Represents a Color using the three values R, G and B, in the range (0.0,1.0)
 */
class ColorRGB : public Color
{
public:

    /** \brief Default Constructor
     *
     *  Create a color with a value of 0.0 for each component, representing
     *  the black color
     */
    ColorRGB();

    /** \brief Default Constructor, given components values as floats
     *
     *  Create a color with the given value for each component. Values should be
     *  in the interval [0.0,1.0]
     *
     *  \param[in] r The value of the red component
     *  \param[in] g The value of the green component
     *  \param[in] b The value of the blue component
     *  \sa ColorRGB(unsigned char, unsigned char, unsigned char)
     */
    ColorRGB(float r, float g, float b);

    /** \brief Default Constructor, given a single component value
     *
     *  Create a color with the given value repeated for every component.
     *
     *  \param[in] rgb The value of the red, green and blue
     */
    ColorRGB(float rgb);

    /** \brief Default Constructor, given components values as unsigned chars
     *
     *  Create a color with the given value for each component. Values should be
     *  in the interval [0,255]
     *
     *  \param[in] r The value of the red component
     *  \param[in] g The value of the green component
     *  \param[in] b The value of the blue component
     *  \sa ColorRGB(float,float,float)
     */
    ColorRGB(unsigned char r, unsigned char g, unsigned char b);

    /** \brief Convert this RGB to the XYZ representation
     *
     *  Convert the color representation from RGB (sRGB color space assumed)
     *  to CIE 1931 XYZ. The Standard illuminant (D65) is also assumed to be the
     *  white colour
     */
    ColorXYZ to_XYZ() const;
};

/** \brief Representation of an XYZ colour
 *
 *  Represents a color using the CIE 1931 XYZ with values in range (0.0,100.0)
 */
class ColorXYZ : public Color
{
public:

    /** \brief Default Constructor
    *
    *  Create a color with a value of 0.0 for each component, representing
    *  the black color
    */
    ColorXYZ();

    /** \brief Default Constructor, given a single component value
     *
     *  Create a color with the given value repeated for every component.
     *
     *  \param[in] xyz The value of x, y, z components
     */
    ColorXYZ(float xyz);

    /** \brief Default Constructor, given X Y and Z values
     *
     *  Create a color with the given value for XYZ, using D65 standard
     *  illuminant
     *
     *  \param[in] x The value of the X component
     *  \param[in] y The value of the Y component
     *  \param[in] z The value of the Z component
     */
    ColorXYZ(float x, float y, float z);

    /** \brief Convert this XYZ to the sRGB representation
     *
     *  Convert the color representation from CIE 1931 XYZ to sRGB, assuming
     *  a D65 Illuminant as white
     */
    ColorRGB to_sRGB() const;

    /** \brief Convert this XYZ to the Adobe RGB representation
     *
     *  Convert the color representation from CIE 1931 XYZ to Adobe RGB, 
     *  assuming a D65 Illuminant as white
     */
    ColorRGB to_AdobeRGB() const;
};

#endif
