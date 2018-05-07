//author: Davide Pizzolotto
//license: GNU GPLv3

#include "color.hpp"

Color::Color()
{
    Color::r = 0.f;
    Color::g = 0.f;
    Color::b = 0.f;
}

Color::Color(float r, float g, float b)
{
    Color::r = r;
    Color::g = g;
    Color::b = b;
}

Color::Color(float rgb)
{
    Color::r = rgb;
    Color::g = rgb;
    Color::b = rgb;
}

bool Color::is_black() const
{
    return Color::r == 0 && Color::g == 0 && Color::b == 0;
}

//------ Operators -------------------------------------------------------------

Color Color::operator+(const Color& c) const
{
    return Color(Color::r+c.r, Color::g+c.g, Color::b+c.b);
}

void Color::operator+=(const Color& c)
{
    Color::r += c.r;
    Color::g += c.g;
    Color::b += c.b;
}

Color Color::operator-(const Color& c) const
{
    return Color(Color::r-c.r, Color::g-c.g, Color::b-c.b);
}

void Color::operator-=(const Color& c)
{
    Color::r -= c.r;
    Color::g -= c.g;
    Color::b -= c.b;
}

Color Color::operator*(const Color& c) const
{
    return Color(Color::r*c.r, Color::g*c.g, Color::b*c.b);
}

void Color::operator*=(const Color& c)
{
    Color::r *= c.r;
    Color::g *= c.g;
    Color::b *= c.b;
}

Color Color::operator/(const Color& c) const
{
    return Color(Color::r/c.r, Color::g/c.g, Color::b/c.b);
}

void Color::operator/=(const Color& c)
{
    Color::r /= c.r;
    Color::g /= c.g;
    Color::b /= c.b;
}

Color Color::operator+(float c) const
{
    return Color(Color::r+c, Color::g+c, Color::b+c);
}

void Color::operator+=(float c)
{
    Color::r += c;
    Color::g += c;
    Color::b += c;
}

Color Color::operator-(float c) const
{
    return Color(Color::r-c, Color::g-c, Color::b-c);
}

void Color::operator-=(float c)
{
    Color::r -= c;
    Color::g -= c;
    Color::b -= c;
}

Color Color::operator*(float c) const
{
    return Color(Color::r*c, Color::g*c, Color::b*c);
}

void Color::operator*=(float c)
{
    Color::r *= c;
    Color::g *= c;
    Color::b *= c;
}

Color Color::operator/(float c) const
{
    return Color(Color::r/c, Color::g/c, Color::b/c);
}

void Color::operator/=(float c)
{
    Color::r /= c;
    Color::g /= c;
    Color::b /= c;
}

//------------------------------------------------------------------------------

ColorXYZ::ColorXYZ()
{
    ColorXYZ::r = 0.0f;
    ColorXYZ::g = 0.0f;
    ColorXYZ::b = 0.0f;
}

ColorXYZ::ColorXYZ(float xyz)
{
    ColorXYZ::r = xyz;
    ColorXYZ::g = xyz;
    ColorXYZ::b = xyz;
}

ColorXYZ::ColorXYZ(float x, float y, float z)
{
    ColorXYZ::r = x;
    ColorXYZ::g = y;
    ColorXYZ::b = z;
}

ColorRGB ColorXYZ::to_sRGB() const
{
    constexpr const double EXP = 1.0/2.4; //periodic :(
    float x = ColorXYZ::r;
    float y = ColorXYZ::g;
    float z = ColorXYZ::b;

    float r = x*3.2404542f+y*-1.5371385f+z*-0.4985314f;
    float g = x*-0.9692660f+y*1.8760108f+z*0.0415560f;
    float b = x*0.0556434f+y*-0.2040259f+z*1.0572252f;

    if(r>0.0031308f)
        r = 1.055f*powf(r, EXP)-0.055f;
    else
        r *= 12.92f;
    if(g>0.0031308f)
        g = 1.055f*powf(g, EXP)-0.055f;
    else
        g *= 12.92f;
    if(b>0.0031308f)
        b = 1.055f*powf(b, EXP)-0.055f;
    else
        b *= 12.92f;

    return ColorRGB((float)r, (float)g, (float)b);
}

ColorRGB ColorXYZ::to_AdobeRGB() const
{
    constexpr const double EXP = 1/2.19921875;
    float x = ColorXYZ::r;
    float y = ColorXYZ::g;
    float z = ColorXYZ::b;

    float r = x*2.04159f+y*-0.56501f+z*-0.34473f;
    float g = x*-0.96924f+y*1.87597f+z*0.03342f;
    float b = x*0.01344f+y*-0.11836f+z*1.34926f;

    return ColorRGB((float)pow(r, EXP),
                    (float)pow(g, EXP),
                    (float)pow(b, EXP));
}

ColorRGB::ColorRGB()
{
    ColorRGB::r = 0.0f;
    ColorRGB::g = 0.0f;
    ColorRGB::b = 0.0f;
}

ColorRGB::ColorRGB(float r, float g, float b)
{
    ColorRGB::r = r;
    ColorRGB::g = g;
    ColorRGB::b = b;
}

ColorRGB::ColorRGB(float rgb)
{
    ColorRGB::r = rgb;
    ColorRGB::g = rgb;
    ColorRGB::b = rgb;
}

ColorRGB::ColorRGB(unsigned char r, unsigned char g, unsigned char b)
{
    constexpr const float INV = 1.f/255.f;
    ColorRGB::r = r*INV;
    ColorRGB::g = g*INV;
    ColorRGB::b = b*INV;
}

ColorXYZ ColorRGB::to_XYZ() const
{
    constexpr const float INV = 1.f/12.92f;
    float r;
    float g;
    float b;

    if(ColorRGB::r>0.04045f)
        r = pow((ColorRGB::r+0.055f)/1.055f, 2.4f);
    else
        r = ColorRGB::r*INV;
    if(ColorRGB::g>0.04045f)
        g = powf((ColorRGB::g+0.055f)/1.055f, 2.4f);
    else
        g = ColorRGB::g*INV;
    if(ColorRGB::b>0.04045f)
        b = powf((ColorRGB::b+0.055f)/1.055f, 2.4f);
    else
        b = ColorRGB::b*INV;

    float x = (float)(r*0.4124564f+g*0.3575761f+b*0.1804375f);
    float y = (float)(r*0.2126729f+g*0.7151522f+b*0.0721750f);
    float z = (float)(r*0.0193339f+g*0.1191920f+b*0.9503041f);

    return ColorXYZ(x, y, z);
}
