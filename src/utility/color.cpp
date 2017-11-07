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

Color::Color(const char* hex)
{
    if(hex[0]!='#' || (strlen(hex)!=4&&strlen(hex)!=7))
    {
        Color::r = 0.f;
        Color::g = 0.f;
        Color::b = 0.f;
    }
    else
    {
        unsigned char hexred;
        unsigned char hexgreen;
        unsigned char hexblue;
        char tmp[3];
        tmp[2] = '\0';
        if(strlen(hex)==4)
        {   tmp[0] = hex[1];
            tmp[1] = hex[1];
            hexred = (unsigned char)strtol(tmp, NULL, 16);
            tmp[0] = hex[2];
            tmp[1] = hex[2];
            hexgreen = (unsigned char)strtol(tmp, NULL, 16);
            tmp[0] = hex[3];
            tmp[1] = hex[3];
            hexblue = (unsigned char)strtol(tmp, NULL, 16);
        }
        else
        {
            tmp[0] = hex[1];
            tmp[1] = hex[2];
            hexred = (unsigned char)strtol(tmp, NULL, 16);
            tmp[0] = hex[3];
            tmp[1] = hex[4];
            hexgreen = (unsigned char)strtol(tmp, NULL, 16);
            tmp[0] = hex[5];
            tmp[1] = hex[6];
            hexblue = (unsigned char)strtol(tmp, NULL, 16);
        }
        Color::r = hexred / 255.f;
        Color::g = hexgreen / 255.f;
        Color::b = hexblue / 255.f;
    }
}

bool Color::isBlack()const
{
    return Color::r==0 && Color::g==0 && Color::b==0;
}

//------ Operators -------------------------------------------------------------

Color Color::operator+(const Color& c)const
{
    return Color(Color::r+c.r,Color::g+c.g,Color::b+c.b);
}

void Color::operator+=(const Color& c)
{
    Color::r+=c.r;
    Color::g+=c.g;
    Color::b+=c.b;
}

Color Color::operator-(const Color& c)const
{
    return Color(Color::r-c.r,Color::g-c.g,Color::b-c.b);
}

void Color::operator-=(const Color& c)
{
    Color::r-=c.r;
    Color::g-=c.g;
    Color::b-=c.b;
}

Color Color::operator*(const Color& c)const
{
    return Color(Color::r*c.r,Color::g*c.g,Color::b*c.b);
}

void Color::operator*=(const Color& c)
{
    Color::r*=c.r;
    Color::g*=c.g;
    Color::b*=c.b;
}

Color Color::operator/(const Color& c)const
{
    return Color(Color::r/c.r,Color::g/c.g,Color::b/c.b);
}

void Color::operator/=(const Color& c)
{
    Color::r/=c.r;
    Color::g/=c.g;
    Color::b/=c.b;
}

Color Color::operator+(float c)const
{
    return Color(Color::r+c,Color::g+c,Color::b+c);
}

void Color::operator+=(float c)
{
    Color::r+=c;
    Color::g+=c;
    Color::b+=c;
}

Color Color::operator-(float c)const
{
    return Color(Color::r-c,Color::g-c,Color::b-c);
}

void Color::operator-=(float c)
{
    Color::r-=c;
    Color::g-=c;
    Color::b-=c;
}

Color Color::operator*(float c)const
{
    return Color(Color::r*c,Color::g*c,Color::b*c);
}

void Color::operator*=(float c)
{
    Color::r*=c;
    Color::g*=c;
    Color::b*=c;
}

Color Color::operator/(float c)const
{
    return Color(Color::r/c,Color::g/c,Color::b/c);
}

void Color::operator/=(float c)
{
    Color::r/=c;
    Color::g/=c;
    Color::b/=c;
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

ColorRGB ColorXYZ::toStandardRGB()const
{
    constexpr const double EXP = 1.0/2.4; //periodic :(
    double x = ColorXYZ::r;
    double y = ColorXYZ::g;
    double z = ColorXYZ::b;
    
    double r = x *  3.2404542 + y * -1.5371385 + z * -0.4985314;
    double g = x * -0.9692660 + y *  1.8760108 + z *  0.0415560;
    double b = x *  0.0556434 + y * -0.2040259 + z *  1.0572252;
    
    if(r > 0.0031308)
        r = 1.055*pow(r,EXP)-0.055;
    else
        r *= 12.92;
    if(g > 0.0031308)
        g = 1.055*pow(g,EXP)-0.055;
    else
        g *= 12.92;
    if(b > 0.0031308)
        b = 1.055*pow(b,EXP)-0.055;
    else
        b *= 12.92;
    
    return ColorRGB((float)r,(float)g,(float)b);
}

ColorRGB ColorXYZ::toAdobeRGB()const
{
    constexpr const double EXP = 1/2.19921875;
    double x = ColorXYZ::r;
    double y = ColorXYZ::g;
    double z = ColorXYZ::b;
    
    double r = x *  2.04159 + y * -0.56501 + z * -0.34473;
    double g = x * -0.96924 + y *  1.87597 + z *  0.03342;
    double b = x *  0.01344 + y * -0.11836 + z *  1.34926;
    
    return ColorRGB((float)pow(r,EXP),
                    (float)pow(g,EXP),
                    (float)pow(b,EXP));
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

ColorRGB::ColorRGB(const char* hex) : Color(hex)
{

}

ColorRGB::ColorRGB(unsigned char r, unsigned char g, unsigned char b)
{
    constexpr const float INV = 1.f/255.f;
    ColorRGB::r = r*INV;
    ColorRGB::g = g*INV;
    ColorRGB::b = b*INV;
}

ColorXYZ ColorRGB::toXYZ()const
{
    constexpr const double INV = 1.0/12.92;
    double r;
    double g;
    double b;
    
    if(ColorRGB::r > 0.04045)
        r = pow((ColorRGB::r+0.055)/1.055,2.4);
    else
        r = ColorRGB::r * INV;
    if(ColorRGB::g > 0.04045)
        g = pow((ColorRGB::g+0.055)/1.055,2.4);
    else
        g = ColorRGB::g * INV;
    if(ColorRGB::b > 0.04045)
        b = pow((ColorRGB::b+0.055)/1.055,2.4);
    else
        b = ColorRGB::b * INV;
    
    float x = (float)(r * 0.4124564 + g * 0.3575761 + b * 0.1804375);
    float y = (float)(r * 0.2126729 + g * 0.7151522 + b * 0.0721750);
    float z = (float)(r * 0.0193339 + g * 0.1191920 + b * 0.9503041);
    
    return ColorXYZ(x,y,z);
}
