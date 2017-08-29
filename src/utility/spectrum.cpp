#include "spectrum.hpp"

//hardcoded almost everywhere, but with a define it is more clear
#define SPECTRUM_SIZE 15

Spectrum::Spectrum()
{
    //do nothing. Too expensive to initialize if I need to assign it later
}

Spectrum::Spectrum(SpectrumType st)
{
    switch(st)
    {
        case WHITE:memset((float*)&nm400, 0.0f, sizeof(float)*15);break;
        case BLACK:memset((float*)&nm400, 1.0f, sizeof(float)*15);break;
            //TODO: at least CMY
        default:memset((float*)&nm400, 1.0f, sizeof(float)*15);break;
    }
}

Spectrum Spectrum::operator+(const Spectrum& s)const
{
    Spectrum retval;
    retval.nm400 = Spectrum::nm400 + s.nm400;
    retval.nm420 = Spectrum::nm420 + s.nm420;
    retval.nm440 = Spectrum::nm440 + s.nm440;
    retval.nm460 = Spectrum::nm460 + s.nm460;
    retval.nm480 = Spectrum::nm480 + s.nm480;
    retval.nm500 = Spectrum::nm500 + s.nm500;
    retval.nm520 = Spectrum::nm520 + s.nm520;
    retval.nm540 = Spectrum::nm540 + s.nm540;
    retval.nm560 = Spectrum::nm560 + s.nm560;
    retval.nm580 = Spectrum::nm580 + s.nm580;
    retval.nm600 = Spectrum::nm600 + s.nm600;
    retval.nm620 = Spectrum::nm620 + s.nm620;
    retval.nm640 = Spectrum::nm640 + s.nm640;
    retval.nm660 = Spectrum::nm660 + s.nm660;
    retval.nm680 = Spectrum::nm680 + s.nm680;
    retval.nm700 = Spectrum::nm700 + s.nm700;
    return retval;
}

void Spectrum::operator+=(const Spectrum& s)
{
    Spectrum::nm400 += s.nm400;
    Spectrum::nm420 += s.nm420;
    Spectrum::nm440 += s.nm440;
    Spectrum::nm460 += s.nm460;
    Spectrum::nm480 += s.nm480;
    Spectrum::nm500 += s.nm500;
    Spectrum::nm520 += s.nm520;
    Spectrum::nm540 += s.nm540;
    Spectrum::nm560 += s.nm560;
    Spectrum::nm580 += s.nm580;
    Spectrum::nm600 += s.nm600;
    Spectrum::nm620 += s.nm620;
    Spectrum::nm640 += s.nm640;
    Spectrum::nm660 += s.nm660;
    Spectrum::nm680 += s.nm680;
    Spectrum::nm700 += s.nm700;
}

Spectrum Spectrum::operator-(const Spectrum& s)const
{
    Spectrum retval;
    retval.nm400 = Spectrum::nm400 - s.nm400;
    retval.nm420 = Spectrum::nm420 - s.nm420;
    retval.nm440 = Spectrum::nm440 - s.nm440;
    retval.nm460 = Spectrum::nm460 - s.nm460;
    retval.nm480 = Spectrum::nm480 - s.nm480;
    retval.nm500 = Spectrum::nm500 - s.nm500;
    retval.nm520 = Spectrum::nm520 - s.nm520;
    retval.nm540 = Spectrum::nm540 - s.nm540;
    retval.nm560 = Spectrum::nm560 - s.nm560;
    retval.nm580 = Spectrum::nm580 - s.nm580;
    retval.nm600 = Spectrum::nm600 - s.nm600;
    retval.nm620 = Spectrum::nm620 - s.nm620;
    retval.nm640 = Spectrum::nm640 - s.nm640;
    retval.nm660 = Spectrum::nm660 - s.nm660;
    retval.nm680 = Spectrum::nm680 - s.nm680;
    retval.nm700 = Spectrum::nm700 - s.nm700;
    return retval;
}

void Spectrum::operator-=(const Spectrum& s)
{
    Spectrum::nm400 -= s.nm400;
    Spectrum::nm420 -= s.nm420;
    Spectrum::nm440 -= s.nm440;
    Spectrum::nm460 -= s.nm460;
    Spectrum::nm480 -= s.nm480;
    Spectrum::nm500 -= s.nm500;
    Spectrum::nm520 -= s.nm520;
    Spectrum::nm540 -= s.nm540;
    Spectrum::nm560 -= s.nm560;
    Spectrum::nm580 -= s.nm580;
    Spectrum::nm600 -= s.nm600;
    Spectrum::nm620 -= s.nm620;
    Spectrum::nm640 -= s.nm640;
    Spectrum::nm660 -= s.nm660;
    Spectrum::nm680 -= s.nm680;
    Spectrum::nm700 -= s.nm700;
}

Spectrum Spectrum::operator*(const Spectrum& s)const
{
    Spectrum retval;
    retval.nm400 = Spectrum::nm400 * s.nm400;
    retval.nm420 = Spectrum::nm420 * s.nm420;
    retval.nm440 = Spectrum::nm440 * s.nm440;
    retval.nm460 = Spectrum::nm460 * s.nm460;
    retval.nm480 = Spectrum::nm480 * s.nm480;
    retval.nm500 = Spectrum::nm500 * s.nm500;
    retval.nm520 = Spectrum::nm520 * s.nm520;
    retval.nm540 = Spectrum::nm540 * s.nm540;
    retval.nm560 = Spectrum::nm560 * s.nm560;
    retval.nm580 = Spectrum::nm580 * s.nm580;
    retval.nm600 = Spectrum::nm600 * s.nm600;
    retval.nm620 = Spectrum::nm620 * s.nm620;
    retval.nm640 = Spectrum::nm640 * s.nm640;
    retval.nm660 = Spectrum::nm660 * s.nm660;
    retval.nm680 = Spectrum::nm680 * s.nm680;
    retval.nm700 = Spectrum::nm700 * s.nm700;
    return retval;
}

void Spectrum::operator*=(const Spectrum& s)
{
    Spectrum::nm400 *= s.nm400;
    Spectrum::nm420 *= s.nm420;
    Spectrum::nm440 *= s.nm440;
    Spectrum::nm460 *= s.nm460;
    Spectrum::nm480 *= s.nm480;
    Spectrum::nm500 *= s.nm500;
    Spectrum::nm520 *= s.nm520;
    Spectrum::nm540 *= s.nm540;
    Spectrum::nm560 *= s.nm560;
    Spectrum::nm580 *= s.nm580;
    Spectrum::nm600 *= s.nm600;
    Spectrum::nm620 *= s.nm620;
    Spectrum::nm640 *= s.nm640;
    Spectrum::nm660 *= s.nm660;
    Spectrum::nm680 *= s.nm680;
    Spectrum::nm700 *= s.nm700;
}

Spectrum Spectrum::operator/(const Spectrum& s)const
{
    Spectrum retval;
    retval.nm400 = Spectrum::nm400 / s.nm400;
    retval.nm420 = Spectrum::nm420 / s.nm420;
    retval.nm440 = Spectrum::nm440 / s.nm440;
    retval.nm460 = Spectrum::nm460 / s.nm460;
    retval.nm480 = Spectrum::nm480 / s.nm480;
    retval.nm500 = Spectrum::nm500 / s.nm500;
    retval.nm520 = Spectrum::nm520 / s.nm520;
    retval.nm540 = Spectrum::nm540 / s.nm540;
    retval.nm560 = Spectrum::nm560 / s.nm560;
    retval.nm580 = Spectrum::nm580 / s.nm580;
    retval.nm600 = Spectrum::nm600 / s.nm600;
    retval.nm620 = Spectrum::nm620 / s.nm620;
    retval.nm640 = Spectrum::nm640 / s.nm640;
    retval.nm660 = Spectrum::nm660 / s.nm660;
    retval.nm680 = Spectrum::nm680 / s.nm680;
    retval.nm700 = Spectrum::nm700 / s.nm700;
    return retval;
}

void Spectrum::operator/=(const Spectrum& s)
{
    Spectrum::nm400 /= s.nm400;
    Spectrum::nm420 /= s.nm420;
    Spectrum::nm440 /= s.nm440;
    Spectrum::nm460 /= s.nm460;
    Spectrum::nm480 /= s.nm480;
    Spectrum::nm500 /= s.nm500;
    Spectrum::nm520 /= s.nm520;
    Spectrum::nm540 /= s.nm540;
    Spectrum::nm560 /= s.nm560;
    Spectrum::nm580 /= s.nm580;
    Spectrum::nm600 /= s.nm600;
    Spectrum::nm620 /= s.nm620;
    Spectrum::nm640 /= s.nm640;
    Spectrum::nm660 /= s.nm660;
    Spectrum::nm680 /= s.nm680;
    Spectrum::nm700 /= s.nm700;
}

Spectrum Spectrum::operator+(float v)const
{
    Spectrum retval;
    retval.nm400 = Spectrum::nm400 + v;
    retval.nm420 = Spectrum::nm420 + v;
    retval.nm440 = Spectrum::nm440 + v;
    retval.nm460 = Spectrum::nm460 + v;
    retval.nm480 = Spectrum::nm480 + v;
    retval.nm500 = Spectrum::nm500 + v;
    retval.nm520 = Spectrum::nm520 + v;
    retval.nm540 = Spectrum::nm540 + v;
    retval.nm560 = Spectrum::nm560 + v;
    retval.nm580 = Spectrum::nm580 + v;
    retval.nm600 = Spectrum::nm600 + v;
    retval.nm620 = Spectrum::nm620 + v;
    retval.nm640 = Spectrum::nm640 + v;
    retval.nm660 = Spectrum::nm660 + v;
    retval.nm680 = Spectrum::nm680 + v;
    retval.nm700 = Spectrum::nm700 + v;
    return retval;
}

void Spectrum::operator+=(float v)
{
    Spectrum::nm400 += v;
    Spectrum::nm420 += v;
    Spectrum::nm440 += v;
    Spectrum::nm460 += v;
    Spectrum::nm480 += v;
    Spectrum::nm500 += v;
    Spectrum::nm520 += v;
    Spectrum::nm540 += v;
    Spectrum::nm560 += v;
    Spectrum::nm580 += v;
    Spectrum::nm600 += v;
    Spectrum::nm620 += v;
    Spectrum::nm640 += v;
    Spectrum::nm660 += v;
    Spectrum::nm680 += v;
    Spectrum::nm700 += v;
}

Spectrum Spectrum::operator-(float v)const
{
    Spectrum retval;
    retval.nm400 = Spectrum::nm400 - v;
    retval.nm420 = Spectrum::nm420 - v;
    retval.nm440 = Spectrum::nm440 - v;
    retval.nm460 = Spectrum::nm460 - v;
    retval.nm480 = Spectrum::nm480 - v;
    retval.nm500 = Spectrum::nm500 - v;
    retval.nm520 = Spectrum::nm520 - v;
    retval.nm540 = Spectrum::nm540 - v;
    retval.nm560 = Spectrum::nm560 - v;
    retval.nm580 = Spectrum::nm580 - v;
    retval.nm600 = Spectrum::nm600 - v;
    retval.nm620 = Spectrum::nm620 - v;
    retval.nm640 = Spectrum::nm640 - v;
    retval.nm660 = Spectrum::nm660 - v;
    retval.nm680 = Spectrum::nm680 - v;
    retval.nm700 = Spectrum::nm700 - v;
    return retval;
}

void Spectrum::operator-=(float v)
{
    Spectrum::nm400 -= v;
    Spectrum::nm420 -= v;
    Spectrum::nm440 -= v;
    Spectrum::nm460 -= v;
    Spectrum::nm480 -= v;
    Spectrum::nm500 -= v;
    Spectrum::nm520 -= v;
    Spectrum::nm540 -= v;
    Spectrum::nm560 -= v;
    Spectrum::nm580 -= v;
    Spectrum::nm600 -= v;
    Spectrum::nm620 -= v;
    Spectrum::nm640 -= v;
    Spectrum::nm660 -= v;
    Spectrum::nm680 -= v;
    Spectrum::nm700 -= v;
}

Spectrum Spectrum::operator*(float v)const
{
    Spectrum retval;
    retval.nm400 = Spectrum::nm400 * v;
    retval.nm420 = Spectrum::nm420 * v;
    retval.nm440 = Spectrum::nm440 * v;
    retval.nm460 = Spectrum::nm460 * v;
    retval.nm480 = Spectrum::nm480 * v;
    retval.nm500 = Spectrum::nm500 * v;
    retval.nm520 = Spectrum::nm520 * v;
    retval.nm540 = Spectrum::nm540 * v;
    retval.nm560 = Spectrum::nm560 * v;
    retval.nm580 = Spectrum::nm580 * v;
    retval.nm600 = Spectrum::nm600 * v;
    retval.nm620 = Spectrum::nm620 * v;
    retval.nm640 = Spectrum::nm640 * v;
    retval.nm660 = Spectrum::nm660 * v;
    retval.nm680 = Spectrum::nm680 * v;
    retval.nm700 = Spectrum::nm700 * v;
    return retval;
}

void Spectrum::operator*=(float v)
{
    Spectrum::nm400 *= v;
    Spectrum::nm420 *= v;
    Spectrum::nm440 *= v;
    Spectrum::nm460 *= v;
    Spectrum::nm480 *= v;
    Spectrum::nm500 *= v;
    Spectrum::nm520 *= v;
    Spectrum::nm540 *= v;
    Spectrum::nm560 *= v;
    Spectrum::nm580 *= v;
    Spectrum::nm600 *= v;
    Spectrum::nm620 *= v;
    Spectrum::nm640 *= v;
    Spectrum::nm660 *= v;
    Spectrum::nm680 *= v;
    Spectrum::nm700 *= v;
}

Spectrum Spectrum::operator/(float v)const
{
    Spectrum retval;
    retval.nm400 = Spectrum::nm400 / v;
    retval.nm420 = Spectrum::nm420 / v;
    retval.nm440 = Spectrum::nm440 / v;
    retval.nm460 = Spectrum::nm460 / v;
    retval.nm480 = Spectrum::nm480 / v;
    retval.nm500 = Spectrum::nm500 / v;
    retval.nm520 = Spectrum::nm520 / v;
    retval.nm540 = Spectrum::nm540 / v;
    retval.nm560 = Spectrum::nm560 / v;
    retval.nm580 = Spectrum::nm580 / v;
    retval.nm600 = Spectrum::nm600 / v;
    retval.nm620 = Spectrum::nm620 / v;
    retval.nm640 = Spectrum::nm640 / v;
    retval.nm660 = Spectrum::nm660 / v;
    retval.nm680 = Spectrum::nm680 / v;
    retval.nm700 = Spectrum::nm700 / v;
    return retval;
}

void Spectrum::operator/=(float v)
{
    Spectrum::nm400 /= v;
    Spectrum::nm420 /= v;
    Spectrum::nm440 /= v;
    Spectrum::nm460 /= v;
    Spectrum::nm480 /= v;
    Spectrum::nm500 /= v;
    Spectrum::nm520 /= v;
    Spectrum::nm540 /= v;
    Spectrum::nm560 /= v;
    Spectrum::nm580 /= v;
    Spectrum::nm600 /= v;
    Spectrum::nm620 /= v;
    Spectrum::nm640 /= v;
    Spectrum::nm660 /= v;
    Spectrum::nm680 /= v;
    Spectrum::nm700 /= v;
}
