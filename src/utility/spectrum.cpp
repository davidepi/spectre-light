//author: Davide Pizzolotto
//license: GNU GPLv3

#include "spectrum.hpp"
//lookup tables for spectrum to XYZ
//taken from http://www.brucelindbloom.com/index.html?Eqn_Spect_to_XYZ.html
//EDIT: later changed with values from pbrt, however the results are similar
const float X[SPECTRUM_SAMPLES] =
{
    0.048547909657160444f,
    0.24864331478873888f,
    0.33913105790813763f,
    0.23759311571717262f,
    0.068513086394717301f,
    0.0074335845497747266f,
    0.08596576422452927f,
    0.30151855826377871f,
    0.58514208267132439f,
    0.88403650492429731f,
    1.0476295638084412f,
    0.91729557037353515f,
    0.55824810008207959f,
    0.24846323480208715f,
    0.082662385882188882f,
    0.023565863414357107f
};

const float Y[SPECTRUM_SAMPLES] =
{
    0.0013634899475922187f,
    0.010440415943351884f,
    0.033597446996718648f,
    0.077808559965342278f,
    0.16970793592433134f,
    0.38263264827430249f,
    0.73335171341896055f,
    0.95049857179323827f,
    0.98971243401368458f,
    0.88304891208807623f,
    0.67035055945316946f,
    0.43439004709323248f,
    0.22639957609275976f,
    0.093565923050045963f,
    0.030277141408684354f,
    0.0085307513410225518f
};

const float Z[SPECTRUM_SAMPLES] =
{
    0.23185277074575425f,
    1.2145957302053769f,
    1.7617404375473658f,
    1.4557389440139135f,
    0.66370667571822806f,
    0.24021451229850452f,
    0.075098564475774759f,
    0.020824563254912696f,
    0.0045391401535986612f,
    0.0017035374639090151f,
    0.00090068979518643274f,
    0.00025727244249234595f,
    3.9191220954914268E-05f,
    1.964333174934533E-06f,
    0.f,
    0.f
};

const float INVY_SUM = 0.17546832144055843f;

const Spectrum SPECTRUM_ONE(
{
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f
});

const Spectrum SPECTRUM_BLACK(0);

#ifdef SPECTRAL

const Spectrum SPECTRUM_WHITE(
{
    1.0619347266616228f,
    1.0623373513955183f,
    1.0624330274817486f,
    1.0624850787200137f,
    1.0622213950288308f,
    1.0613081599651542f,
    1.0613058645182336f,
    1.0618168659745209f,
    1.0624642293010491f,
    1.0624838864140043f,
    1.0624682453762331f,
    1.0625355983287506f,
    1.0624016329348598f,
    1.0622653248789862f,
    1.060266533148627f,
    1.0600420908765831f
});

const Spectrum SPECTRUM_WHITEL(
{
    1.1560446394211681f,
    1.1564162465744781f,
    1.1567872929485827f,
    1.1565328954114107f,
    1.1565926830659454f,
    1.1565499678850697f,
    1.1472133116300325f,
    1.1314209727068025f,
    1.096408860125702f,
    1.0338718350511178f,
    0.96528604465789958f,
    0.92067216838305188f,
    0.90011672087937411f,
    0.88940075523174911f,
    0.88083842252481404f,
    0.87810499922653207f
});

const Spectrum SPECTRUM_CYAN(
{
    1.0240953312699979f,
    1.0245612457188975f,
    1.0463755555238345f,
    1.0327846651059092f,
    1.0478428969483209f,
    1.0535090536305822f,
    1.0534870576691449f,
    1.0530663848751949f,
    1.0549102750144981f,
    0.94299173220279198f,
    0.3100097408600444f,
    0.0033711342032203243f,
    -0.0048549813110745684f,
    0.0018582205785167482f,
    0.0039837672915054804f,
    0.010507259067086385f
});

const Spectrum SPECTRUM_CYANL(
{
    1.1352399582424499f,
    1.1358531764433719f,
    1.1362707169771014f,
    1.1359364376354608f,
    1.1361867189829913f,
    1.135817770159788f,
    1.1359519356976406f,
    1.135423392708292f,
    1.1224513886352236f,
    0.87073337556349084f,
    0.3803441995397272f,
    0.051216852241201545f,
    -0.011762638745943615f,
    -0.01060685685959013f,
    -0.006931473364874461f,
    -0.0077818774183695668f
});

const Spectrum SPECTRUM_MAGENTA(
{
    0.99302530302633674f,
    1.0170691330352013f,
    1.0143947530476214f,
    1.0070517895374196f,
    0.80112726913173504f,
    0.077593476678434567f,
    0.003229957831351733f,
    -0.004352238640709956f,
    0.0026944590704797754f,
    0.28205531033673215f,
    0.8570353689334701f,
    0.99378492125784268f,
    0.98449588288224388f,
    0.8937980881442511f,
    0.94958431903872431f,
    0.9395992587226637f
});

const Spectrum SPECTRUM_MAGENTAL(
{
    1.0765584064227334f,
    1.0770490751029975f,
    1.0731253134738323f,
    1.0796647470180021f,
    1.0024747756009726f,
    0.4395828981593643f,
    0.02042973274257508f,
    -0.0015031343728669692f,
    -6.099749699375323e-06f,
    0.072151645981868115f,
    0.48078616824947817f,
    0.97313406556425108f,
    1.0781818622728534f,
    1.0327505540054573f,
    1.0495214724241742f,
    1.0257450908661028f
});

const Spectrum SPECTRUM_YELLOW(
{
    -0.0059362362867909409f,
    -0.0040293484704144403f,
    0.034632747920561285f,
    0.19407661745186114f,
    0.45561541868250915f,
    0.78117265145981962f,
    1.0163873556505527f,
    1.0511958466847318f,
    1.0513470268321483f,
    1.0515277720869929f,
    1.0512298920801075f,
    1.0515211534901903f,
    1.0514264026060656f,
    1.0513103386739624f,
    1.0507004197273715f,
    1.0485826837788901f
});

const Spectrum SPECTRUM_YELLOWL(
{
    0.0001468672999305493f,
    -0.00013161147654402951f,
    -0.00016768424395723818f,
    0.089519214436320216f,
    0.74821476916582985f,
    1.0340727288469598f,
    1.0365778653585402f,
    1.0367058054560021f,
    1.0365194490895373f,
    1.03661227107821f,
    1.0361321399468379f,
    1.0144985871415191f,
    0.8293751396865352f,
    0.6705682032005652f,
    0.60059597683336108f,
    0.58277723714307716f
});

const Spectrum SPECTRUM_RED(
{
    0.11487922506830811f,
    0.060141120462551691f,
    0.0040665397109191335f,
    0.010459427718803191f,
    0.0035470993579631675f,
    -0.0052706076654779289f,
    -0.0062588252221244959f,
    -0.0086496045197971341f,
    0.00097200190739861079f,
    0.14679380036909495f,
    0.85847180162874637f,
    0.99821493324988597f,
    0.99605297040670981f,
    1.0018494025816944f,
    0.99593834054491903f,
    0.9811979963396622f
});

const Spectrum SPECTRUM_REDL(
{
    0.057139392791085111f,
    0.043034047329456572f,
    0.021260689526515806f,
    0.001077172714861781f,
    0.00057985241220036873f,
    -0.00022486144117236386f,
    -0.00012009820021618776f,
    -0.0001991308173681336f,
    0.012756076079520295f,
    0.1832461591194777f,
    0.51948819108311795f,
    0.82120171360154059f,
    0.96263010562297358f,
    0.99410699787589729f,
    0.99018057306059759f,
    0.98278552726948454f
});

const Spectrum SPECTRUM_GREEN(
{
    -0.010865527381003439f,
    -0.010329458431599345f,
    -0.0083431520558099291f,
    0.083794233190453149f,
    0.57500780803880425f,
    0.95115677422179923f,
    0.99948898769838934f,
    0.99968078182605802f,
    0.9988159758735875f,
    0.88618140828021486f,
    0.35690377193776984f,
    0.01325598457467465f,
    -0.0050991929756587905f,
    -0.0083927995026960873f,
    -0.0084413650357697944f,
    -0.0047501377518373699f
});

const Spectrum SPECTRUM_GREENL(
{
    0.0064830780912117957f,
    0.00019032331867488899f,
    -0.0081060480798639516f,
    0.048161890183585902f,
    0.66729637282872345f,
    1.0307844454225901f,
    1.0311600157417389f,
    1.0265626896736526f,
    1.0363099387922192f,
    1.0120735391513225f,
    0.32668720729539291f,
    0.0033846154767388065f,
    0.0081701266623202973f,
    0.0088889810224966476f,
    0.00036631914529600032f,
    0.00099462806143045101f
});

const Spectrum SPECTRUM_BLUE(
{
    0.99498216185557875f,
    0.99569451590852531f,
    0.99983310193704411f,
    0.9648523926660395f,
    0.67060127526424484f,
    0.29157891777810102f,
    0.044614561825850822f,
    -6.7793271695393519e-06f,
    0.00050597357489660954f,
    0.0023497993510693772f,
    0.00067442519549839989f,
    0.016621955742817246f,
    0.040211692914411255f,
    0.049604490414015802f,
    0.043574051087547458f,
    0.027483432250758107f
});

const Spectrum SPECTRUM_BLUEL(
{
    1.054236254920313f,
    1.0576206026996142f,
    1.058143833550661f,
    1.0568818098511983f,
    1.0207912014756255f,
    0.2974275399820579f,
    -0.0014770394250804989f,
    -0.0013982161133251694f,
    -0.00059190711447091779f,
    -0.0010090527379278194f,
    -0.0015479588813372375f,
    0.0051106864601078716f,
    0.047054873524993275f,
    0.12827536395203271f,
    0.15246421103968871f,
    0.16615733676564479f
});
#else

const Spectrum SPECTRUM_WHITE = SPECTRUM_ONE;

#endif

Spectrum::Spectrum()
{

}

Spectrum::Spectrum(int t)
{
    if(t==0) //black
    {
#ifdef SPECTRAL
        memset(Spectrum::w,0,sizeof(float)*SPECTRUM_SAMPLES);
#else
        w[0] = 0.f;
        w[1] = 0.f;
        w[2] = 0.f;
#endif
    }
    else //apply planck's law
    {
#ifdef SPECTRAL
        float* values = Spectrum::w;
#else
        float values[16];
#endif
        //TODO: this must be changed if not vacuum
        constexpr const float c = 299792458;
        constexpr const float c2 = c*c;
        ///first radiation constant: 2hc^2
        constexpr float frc = 2.f*PLANCK_H*c2;
        //second radiation constant: hc/kb
        constexpr float src = PLANCK_H*c/BOLTZMANN_K;
        float current_wavelength = SPECTRUM_START*1E-9f;
        float maxval = FLT_MIN;
        for(int i=0;i<SPECTRUM_SAMPLES;i++)
        {
            values[i]=frc/powf(current_wavelength,5);
            values[i]*=1.f/(expf(src/(t*current_wavelength))+1.f);
            if(values[i]>maxval)
                maxval = values[i];
            current_wavelength+=SPECTRUM_INTERVAL*1E-9f;
        }
        for(int i=0;i<SPECTRUM_SAMPLES;i++)
            values[i]/=maxval;
#ifndef SPECTRAL
        //convert to XYZ, cannot use the Spectrum method beacuse without
        //the #define SPECTRAL it would have only 3 component
        float x = 0;
        float y = 0;
        float z = 0;
        for(int i=0;i<SPECTRUM_SAMPLES;i++)
        {
            x+=values[i]*X[i];
            y+=values[i]*Y[i];
            z+=values[i]*Z[i];
        }
        Spectrum::w[0] = x*INVY_SUM;
        Spectrum::w[1] = y*INVY_SUM;
        Spectrum::w[2] = z*INVY_SUM;
#endif
    }
}

Spectrum::Spectrum(const float* vals)
{
#ifdef SPECTRAL
    for(int i=0;i<SPECTRUM_SAMPLES;i++)
        Spectrum::w[i] = vals[i];
#else
    Spectrum::w[0] = vals[0];
    Spectrum::w[1] = vals[1];
    Spectrum::w[2] = vals[2];
#endif
}

Spectrum::Spectrum(const std::initializer_list<float> vals)
{
    if(vals.size()!=16)
        throw "Incorrect sized spectrum";
    int i=0;
#ifdef SPECTRAL
    for(float val:vals)
        Spectrum::w[i++] = val;
#else
    //not super precise... but whatever, this constructor is used where full
    //spectrum rendering is almost required so the result won't be precise
    //anyway (referring to Conductor reflection)
    for(float val:vals)
    {
        if(i<5)
            Spectrum::w[0] += val;
        else if(i<11)
            Spectrum::w[1] += val;
        else
            Spectrum::w[2] += val;
        i++;
    }
    Spectrum::w[0]/=5;
    Spectrum::w[1]/=6;
    Spectrum::w[2]/=5;
#endif
}

Spectrum::Spectrum(float val)
{
    Spectrum::w[0] = val;
    Spectrum::w[1] = val;
    Spectrum::w[2] = val;
#ifdef SPECTRAL
    Spectrum::w[3] = val;
    Spectrum::w[4] = val;
    Spectrum::w[5] = val;
    Spectrum::w[6] = val;
    Spectrum::w[7] = val;
    Spectrum::w[8] = val;
    Spectrum::w[9] = val;
    Spectrum::w[10] = val;
    Spectrum::w[11] = val;
    Spectrum::w[12] = val;
    Spectrum::w[13] = val;
    Spectrum::w[14] = val;
    Spectrum::w[15] = val;
#endif
}

Spectrum::Spectrum(ColorRGB c, bool l)
{
#ifdef SPECTRAL
    memset(Spectrum::w,0,sizeof(float)*SPECTRUM_SAMPLES);
    if(!l)
    {
        if(c.r<=c.g && c.r<=c.b)
        {
            *this += SPECTRUM_WHITE*c.r;
            if(c.g <= c.b)
            {
                *this += SPECTRUM_CYAN*(c.g-c.r);
                *this += SPECTRUM_BLUE*(c.b-c.g);
            }
            else
            {
                *this += SPECTRUM_CYAN*(c.b-c.r);
                *this += SPECTRUM_GREEN*(c.g-c.b);
            }
        }
        else if(c.g<=c.r && c.g<=c.b)
        {
            *this += SPECTRUM_WHITE*c.g;
            if(c.r <= c.b)
            {
                *this += SPECTRUM_MAGENTA*(c.r-c.g);
                *this += SPECTRUM_BLUE*(c.b-c.r);
            }
            else
            {
                *this += SPECTRUM_MAGENTA*(c.b-c.g);
                *this += SPECTRUM_RED*(c.r-c.b);
            }
        }
        else
        {
            *this += SPECTRUM_WHITE*c.b;
            if(c.r <= c.g)
            {
                *this += SPECTRUM_YELLOW*(c.r-c.b);
                *this += SPECTRUM_GREEN*(c.g-c.r);
            }
            else
            {
                *this += SPECTRUM_YELLOW*(c.g-c.b);
                *this += SPECTRUM_RED*(c.r-c.g);
            }
        }
        *this *= 0.94f;
    }
    else
    {
        if(c.r<=c.g && c.r<=c.b)
        {
            *this += SPECTRUM_WHITEL*c.r;
            if(c.g <= c.b)
            {
                *this += SPECTRUM_CYANL*(c.g-c.r);
                *this += SPECTRUM_BLUEL*(c.b-c.g);
            }
            else
            {
                *this += SPECTRUM_CYANL*(c.b-c.r);
                *this += SPECTRUM_GREENL*(c.g-c.b);
            }
        }
        else if(c.g<=c.r && c.g<=c.b)
        {
            *this += SPECTRUM_WHITEL*c.g;
            if(c.r <= c.b)
            {
                *this += SPECTRUM_MAGENTAL*(c.r-c.g);
                *this += SPECTRUM_BLUEL*(c.b-c.r);
            }
            else
            {
                *this += SPECTRUM_MAGENTAL*(c.b-c.g);
                *this += SPECTRUM_REDL*(c.r-c.b);
            }
        }
        else
        {
            *this += SPECTRUM_WHITEL*c.b;
            if(c.r <= c.g)
            {
                *this += SPECTRUM_YELLOWL*(c.r-c.b);
                *this += SPECTRUM_GREENL*(c.g-c.r);
            }
            else
            {
                *this += SPECTRUM_YELLOWL*(c.g-c.b);
                *this += SPECTRUM_REDL*(c.r-c.g);
            }
        }
        *this *= 0.86445f;
    }
    for(int i=0;i<SPECTRUM_SAMPLES;i++)
        w[i] = clamp(w[i],0.f,1.f);
#else
    (void)l; //to avoid unused parameters warnings
    ColorXYZ res = c.toXYZ();
    Spectrum::w[0] = res.r;
    Spectrum::w[1] = res.g;
    Spectrum::w[2] = res.b;
#endif
}

ColorXYZ Spectrum::toXYZ()const
{
#ifdef SPECTRAL
    float x = 0;
    float y = 0;
    float z = 0;
    x+=Spectrum::w[0]*X[0];
    x+=Spectrum::w[1]*X[1];
    x+=Spectrum::w[2]*X[2];
    x+=Spectrum::w[3]*X[3];
    x+=Spectrum::w[4]*X[4];
    x+=Spectrum::w[5]*X[5];
    x+=Spectrum::w[6]*X[6];
    x+=Spectrum::w[7]*X[7];
    x+=Spectrum::w[8]*X[8];
    x+=Spectrum::w[9]*X[9];
    x+=Spectrum::w[10]*X[10];
    x+=Spectrum::w[11]*X[11];
    x+=Spectrum::w[12]*X[12];
    x+=Spectrum::w[13]*X[13];
    x+=Spectrum::w[14]*X[14];
    x+=Spectrum::w[15]*X[15];
    
    y+=Spectrum::w[0]*Y[0];
    y+=Spectrum::w[1]*Y[1];
    y+=Spectrum::w[2]*Y[2];
    y+=Spectrum::w[3]*Y[3];
    y+=Spectrum::w[4]*Y[4];
    y+=Spectrum::w[5]*Y[5];
    y+=Spectrum::w[6]*Y[6];
    y+=Spectrum::w[7]*Y[7];
    y+=Spectrum::w[8]*Y[8];
    y+=Spectrum::w[9]*Y[9];
    y+=Spectrum::w[10]*Y[10];
    y+=Spectrum::w[11]*Y[11];
    y+=Spectrum::w[12]*Y[12];
    y+=Spectrum::w[13]*Y[13];
    y+=Spectrum::w[14]*Y[14];
    y+=Spectrum::w[15]*Y[15];
    
    z+=Spectrum::w[0]*Z[0];
    z+=Spectrum::w[1]*Z[1];
    z+=Spectrum::w[2]*Z[2];
    z+=Spectrum::w[3]*Z[3];
    z+=Spectrum::w[4]*Z[4];
    z+=Spectrum::w[5]*Z[5];
    z+=Spectrum::w[6]*Z[6];
    z+=Spectrum::w[7]*Z[7];
    z+=Spectrum::w[8]*Z[8];
    z+=Spectrum::w[9]*Z[9];
    z+=Spectrum::w[10]*Z[10];
    z+=Spectrum::w[11]*Z[11];
    z+=Spectrum::w[12]*Z[12];
    z+=Spectrum::w[13]*Z[13];
    z+=Spectrum::w[14]*Z[14];
    z+=Spectrum::w[15]*Z[15];
    x*=INVY_SUM;
    y*=INVY_SUM;
    z*=INVY_SUM;
    return ColorXYZ(x,y,z);
#else
    return ColorXYZ(w[0],w[1],w[2]);
#endif
}

float Spectrum::luminance()const
{
#ifdef SPECTRAL
    float y = 0;
    y+=Spectrum::w[0]*Y[0];
    y+=Spectrum::w[1]*Y[1];
    y+=Spectrum::w[2]*Y[2];
    y+=Spectrum::w[3]*Y[3];
    y+=Spectrum::w[4]*Y[4];
    y+=Spectrum::w[5]*Y[5];
    y+=Spectrum::w[6]*Y[6];
    y+=Spectrum::w[7]*Y[7];
    y+=Spectrum::w[8]*Y[8];
    y+=Spectrum::w[9]*Y[9];
    y+=Spectrum::w[10]*Y[10];
    y+=Spectrum::w[11]*Y[11];
    y+=Spectrum::w[12]*Y[12];
    y+=Spectrum::w[13]*Y[13];
    y+=Spectrum::w[14]*Y[14];
    y+=Spectrum::w[15]*Y[15];
    return y*INVY_SUM;
#else
    return Spectrum::w[1];
#endif
}

bool Spectrum::isBlack()const
{
#ifdef SPECTRAL
    for(int i=0;i<SPECTRUM_SAMPLES;i++)
        if(Spectrum::w[i]!=0)
            return false;
    return true;
#else
    return w[0]==0 && w[1]==0 && w[2]==0;
#endif
}

bool Spectrum::isValid()const
{
    bool retval = true;
    using std::isnan;
    using std::isinf;
#ifdef SPECTRAL
    if(isnan(w[ 0]) || isnan(w[ 1]) || isnan (w[ 2]) || isnan(w[ 3]) ||
       isnan(w[ 4]) || isnan(w[ 5]) || isnan (w[ 6]) || isnan(w[ 7]) ||
       isnan(w[ 8]) || isnan(w[ 9]) || isnan (w[10]) || isnan(w[11]) ||
       isnan(w[12]) || isnan(w[13]) || isnan (w[14]) || isnan(w[15]))
    {
        Console.severe(MESSAGE_SPECTRUM_NAN);
        retval = false;
    }
    if(isinf(w[ 0]) || isinf(w[ 1]) || isinf (w[ 2]) || isinf(w[ 3]) ||
       isinf(w[ 4]) || isinf(w[ 5]) || isinf (w[ 6]) || isinf(w[ 7]) ||
       isinf(w[ 8]) || isinf(w[ 9]) || isinf (w[10]) || isinf(w[11]) ||
       isinf(w[12]) || isinf(w[13]) || isinf (w[14]) || isinf(w[15]))
    {
        Console.severe(MESSAGE_SPECTRUM_INF);
        retval = false;
    }

//    if(w[ 0]<0 || w[ 1]<0 || w[ 2]<0 || w[ 3]<0 ||
//       w[ 4]<0 || w[ 5]<0 || w[ 6]<0 || w[ 7]<0 ||
//       w[ 8]<0 || w[ 9]<0 || w[10]<0 || w[11]<0 ||
//       w[12]<0 || w[13]<0 || w[14]<0 || w[15]<0)
//    {
//        Console.severe(MESSAGE_SPECTRUM_NEG);
//        retval = false;
//    }
#else
    if(isnan(w[0]) || isnan(w[1]) || isnan (w[2]))
    {
        Console.severe(MESSAGE_SPECTRUM_NAN);
        retval = false;
    }
    if(isinf(w[0]) || isinf(w[1]) || isinf (w[2]))
    {
        Console.severe(MESSAGE_SPECTRUM_INF);
        retval = false;
    }
//    if(w[0]<0 || w[1]<0 || w[2]<0)
//    {
//        Console.severe(MESSAGE_SPECTRUM_NEG);
//        retval = false;
//    }
#endif
    return retval;
}

Spectrum Spectrum::operator+(const Spectrum& s)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] + s.w[0];
    retval.w[1] = Spectrum::w[1] + s.w[1];
    retval.w[2] = Spectrum::w[2] + s.w[2];
#ifdef SPECTRAL
    retval.w[3] = Spectrum::w[3] + s.w[3];
    retval.w[4] = Spectrum::w[4] + s.w[4];
    retval.w[5] = Spectrum::w[5] + s.w[5];
    retval.w[6] = Spectrum::w[6] + s.w[6];
    retval.w[7] = Spectrum::w[7] + s.w[7];
    retval.w[8] = Spectrum::w[8] + s.w[8];
    retval.w[9] = Spectrum::w[9] + s.w[9];
    retval.w[10] = Spectrum::w[10] + s.w[10];
    retval.w[11] = Spectrum::w[11] + s.w[11];
    retval.w[12] = Spectrum::w[12] + s.w[12];
    retval.w[13] = Spectrum::w[13] + s.w[13];
    retval.w[14] = Spectrum::w[14] + s.w[14];
    retval.w[15] = Spectrum::w[15] + s.w[15];
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
    return retval;
}

void Spectrum::operator+=(const Spectrum& s)
{
    Spectrum::w[0] += s.w[0];
    Spectrum::w[1] += s.w[1];
    Spectrum::w[2] += s.w[2];
#ifdef SPECTRAL
    Spectrum::w[3] += s.w[3];
    Spectrum::w[4] += s.w[4];
    Spectrum::w[5] += s.w[5];
    Spectrum::w[6] += s.w[6];
    Spectrum::w[7] += s.w[7];
    Spectrum::w[8] += s.w[8];
    Spectrum::w[9] += s.w[9];
    Spectrum::w[10] += s.w[10];
    Spectrum::w[11] += s.w[11];
    Spectrum::w[12] += s.w[12];
    Spectrum::w[13] += s.w[13];
    Spectrum::w[14] += s.w[14];
    Spectrum::w[15] += s.w[15];
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
}

Spectrum Spectrum::operator-(const Spectrum& s)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] - s.w[0];
    retval.w[1] = Spectrum::w[1] - s.w[1];
    retval.w[2] = Spectrum::w[2] - s.w[2];
#ifdef SPECTRAL
    retval.w[3] = Spectrum::w[3] - s.w[3];
    retval.w[4] = Spectrum::w[4] - s.w[4];
    retval.w[5] = Spectrum::w[5] - s.w[5];
    retval.w[6] = Spectrum::w[6] - s.w[6];
    retval.w[7] = Spectrum::w[7] - s.w[7];
    retval.w[8] = Spectrum::w[8] - s.w[8];
    retval.w[9] = Spectrum::w[9] - s.w[9];
    retval.w[10] = Spectrum::w[10] - s.w[10];
    retval.w[11] = Spectrum::w[11] - s.w[11];
    retval.w[12] = Spectrum::w[12] - s.w[12];
    retval.w[13] = Spectrum::w[13] - s.w[13];
    retval.w[14] = Spectrum::w[14] - s.w[14];
    retval.w[15] = Spectrum::w[15] - s.w[15];
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
    return retval;

}

void Spectrum::operator-=(const Spectrum& s)
{
    Spectrum::w[0] -= s.w[0];
    Spectrum::w[1] -= s.w[1];
    Spectrum::w[2] -= s.w[2];
#ifdef SPECTRAL
    Spectrum::w[3] -= s.w[3];
    Spectrum::w[4] -= s.w[4];
    Spectrum::w[5] -= s.w[5];
    Spectrum::w[6] -= s.w[6];
    Spectrum::w[7] -= s.w[7];
    Spectrum::w[8] -= s.w[8];
    Spectrum::w[9] -= s.w[9];
    Spectrum::w[10] -= s.w[10];
    Spectrum::w[11] -= s.w[11];
    Spectrum::w[12] -= s.w[12];
    Spectrum::w[13] -= s.w[13];
    Spectrum::w[14] -= s.w[14];
    Spectrum::w[15] -= s.w[15];
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
}

Spectrum Spectrum::operator*(const Spectrum& s)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] * s.w[0];
    retval.w[1] = Spectrum::w[1] * s.w[1];
    retval.w[2] = Spectrum::w[2] * s.w[2];
#ifdef SPECTRAL
    retval.w[3] = Spectrum::w[3] * s.w[3];
    retval.w[4] = Spectrum::w[4] * s.w[4];
    retval.w[5] = Spectrum::w[5] * s.w[5];
    retval.w[6] = Spectrum::w[6] * s.w[6];
    retval.w[7] = Spectrum::w[7] * s.w[7];
    retval.w[8] = Spectrum::w[8] * s.w[8];
    retval.w[9] = Spectrum::w[9] * s.w[9];
    retval.w[10] = Spectrum::w[10] * s.w[10];
    retval.w[11] = Spectrum::w[11] * s.w[11];
    retval.w[12] = Spectrum::w[12] * s.w[12];
    retval.w[13] = Spectrum::w[13] * s.w[13];
    retval.w[14] = Spectrum::w[14] * s.w[14];
    retval.w[15] = Spectrum::w[15] * s.w[15];
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
    return retval;

}

void Spectrum::operator*=(const Spectrum& s)
{
    Spectrum::w[0] *= s.w[0];
    Spectrum::w[1] *= s.w[1];
    Spectrum::w[2] *= s.w[2];
#ifdef SPECTRAL
    Spectrum::w[3] *= s.w[3];
    Spectrum::w[4] *= s.w[4];
    Spectrum::w[5] *= s.w[5];
    Spectrum::w[6] *= s.w[6];
    Spectrum::w[7] *= s.w[7];
    Spectrum::w[8] *= s.w[8];
    Spectrum::w[9] *= s.w[9];
    Spectrum::w[10] *= s.w[10];
    Spectrum::w[11] *= s.w[11];
    Spectrum::w[12] *= s.w[12];
    Spectrum::w[13] *= s.w[13];
    Spectrum::w[14] *= s.w[14];
    Spectrum::w[15] *= s.w[15];
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
}

Spectrum Spectrum::operator/(const Spectrum& s)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] / s.w[0];
    retval.w[1] = Spectrum::w[1] / s.w[1];
    retval.w[2] = Spectrum::w[2] / s.w[2];
#ifdef SPECTRAL
    retval.w[3] = Spectrum::w[3] / s.w[3];
    retval.w[4] = Spectrum::w[4] / s.w[4];
    retval.w[5] = Spectrum::w[5] / s.w[5];
    retval.w[6] = Spectrum::w[6] / s.w[6];
    retval.w[7] = Spectrum::w[7] / s.w[7];
    retval.w[8] = Spectrum::w[8] / s.w[8];
    retval.w[9] = Spectrum::w[9] / s.w[9];
    retval.w[10] = Spectrum::w[10] / s.w[10];
    retval.w[11] = Spectrum::w[11] / s.w[11];
    retval.w[12] = Spectrum::w[12] / s.w[12];
    retval.w[13] = Spectrum::w[13] / s.w[13];
    retval.w[14] = Spectrum::w[14] / s.w[14];
    retval.w[15] = Spectrum::w[15] / s.w[15];
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
    return retval;
}

void Spectrum::operator/=(const Spectrum& s)
{
    Spectrum::w[0] /= s.w[0];
    Spectrum::w[1] /= s.w[1];
    Spectrum::w[2] /= s.w[2];
#ifdef SPECTRAL
    Spectrum::w[3] /= s.w[3];
    Spectrum::w[4] /= s.w[4];
    Spectrum::w[5] /= s.w[5];
    Spectrum::w[6] /= s.w[6];
    Spectrum::w[7] /= s.w[7];
    Spectrum::w[8] /= s.w[8];
    Spectrum::w[9] /= s.w[9];
    Spectrum::w[10] /= s.w[10];
    Spectrum::w[11] /= s.w[11];
    Spectrum::w[12] /= s.w[12];
    Spectrum::w[13] /= s.w[13];
    Spectrum::w[14] /= s.w[14];
    Spectrum::w[15] /= s.w[15];
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
}

Spectrum Spectrum::operator+(float v)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] + v;
    retval.w[1] = Spectrum::w[1] + v;
    retval.w[2] = Spectrum::w[2] + v;
#ifdef SPECTRAL
    retval.w[3] = Spectrum::w[3] + v;
    retval.w[4] = Spectrum::w[4] + v;
    retval.w[5] = Spectrum::w[5] + v;
    retval.w[6] = Spectrum::w[6] + v;
    retval.w[7] = Spectrum::w[7] + v;
    retval.w[8] = Spectrum::w[8] + v;
    retval.w[9] = Spectrum::w[9] + v;
    retval.w[10] = Spectrum::w[10] + v;
    retval.w[11] = Spectrum::w[11] + v;
    retval.w[12] = Spectrum::w[12] + v;
    retval.w[13] = Spectrum::w[13] + v;
    retval.w[14] = Spectrum::w[14] + v;
    retval.w[15] = Spectrum::w[15] + v;
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
    return retval;
}

void Spectrum::operator+=(float v)
{
    Spectrum::w[0] += v;
    Spectrum::w[1] += v;
    Spectrum::w[2] += v;
#ifdef SPECTRAL
    Spectrum::w[3] += v;
    Spectrum::w[4] += v;
    Spectrum::w[5] += v;
    Spectrum::w[6] += v;
    Spectrum::w[7] += v;
    Spectrum::w[8] += v;
    Spectrum::w[9] += v;
    Spectrum::w[10] += v;
    Spectrum::w[11] += v;
    Spectrum::w[12] += v;
    Spectrum::w[13] += v;
    Spectrum::w[14] += v;
    Spectrum::w[15] += v;
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
}

Spectrum Spectrum::operator-(float v)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] - v;
    retval.w[1] = Spectrum::w[1] - v;
    retval.w[2] = Spectrum::w[2] - v;
#ifdef SPECTRAL
    retval.w[3] = Spectrum::w[3] - v;
    retval.w[4] = Spectrum::w[4] - v;
    retval.w[5] = Spectrum::w[5] - v;
    retval.w[6] = Spectrum::w[6] - v;
    retval.w[7] = Spectrum::w[7] - v;
    retval.w[8] = Spectrum::w[8] - v;
    retval.w[9] = Spectrum::w[9] - v;
    retval.w[10] = Spectrum::w[10] - v;
    retval.w[11] = Spectrum::w[11] - v;
    retval.w[12] = Spectrum::w[12] - v;
    retval.w[13] = Spectrum::w[13] - v;
    retval.w[14] = Spectrum::w[14] - v;
    retval.w[15] = Spectrum::w[15] - v;
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
    return retval;
}

void Spectrum::operator-=(float v)
{
    Spectrum::w[0] -= v;
    Spectrum::w[1] -= v;
    Spectrum::w[2] -= v;
#ifdef SPECTRAL
    Spectrum::w[3] -= v;
    Spectrum::w[4] -= v;
    Spectrum::w[5] -= v;
    Spectrum::w[6] -= v;
    Spectrum::w[7] -= v;
    Spectrum::w[8] -= v;
    Spectrum::w[9] -= v;
    Spectrum::w[10] -= v;
    Spectrum::w[11] -= v;
    Spectrum::w[12] -= v;
    Spectrum::w[13] -= v;
    Spectrum::w[14] -= v;
    Spectrum::w[15] -= v;
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
}

Spectrum Spectrum::operator*(float v)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] * v;
    retval.w[1] = Spectrum::w[1] * v;
    retval.w[2] = Spectrum::w[2] * v;
#ifdef SPECTRAL
    retval.w[3] = Spectrum::w[3] * v;
    retval.w[4] = Spectrum::w[4] * v;
    retval.w[5] = Spectrum::w[5] * v;
    retval.w[6] = Spectrum::w[6] * v;
    retval.w[7] = Spectrum::w[7] * v;
    retval.w[8] = Spectrum::w[8] * v;
    retval.w[9] = Spectrum::w[9] * v;
    retval.w[10] = Spectrum::w[10] * v;
    retval.w[11] = Spectrum::w[11] * v;
    retval.w[12] = Spectrum::w[12] * v;
    retval.w[13] = Spectrum::w[13] * v;
    retval.w[14] = Spectrum::w[14] * v;
    retval.w[15] = Spectrum::w[15] * v;
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
    return retval;
}

void Spectrum::operator*=(float v)
{
    Spectrum::w[0] *= v;
    Spectrum::w[1] *= v;
    Spectrum::w[2] *= v;
#ifdef SPECTRAL
    Spectrum::w[3] *= v;
    Spectrum::w[4] *= v;
    Spectrum::w[5] *= v;
    Spectrum::w[6] *= v;
    Spectrum::w[7] *= v;
    Spectrum::w[8] *= v;
    Spectrum::w[9] *= v;
    Spectrum::w[10] *= v;
    Spectrum::w[11] *= v;
    Spectrum::w[12] *= v;
    Spectrum::w[13] *= v;
    Spectrum::w[14] *= v;
    Spectrum::w[15] *= v;
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
}

Spectrum Spectrum::operator/(float v)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] / v;
    retval.w[1] = Spectrum::w[1] / v;
    retval.w[2] = Spectrum::w[2] / v;
#ifdef SPECTRAL
    retval.w[3] = Spectrum::w[3] / v;
    retval.w[4] = Spectrum::w[4] / v;
    retval.w[5] = Spectrum::w[5] / v;
    retval.w[6] = Spectrum::w[6] / v;
    retval.w[7] = Spectrum::w[7] / v;
    retval.w[8] = Spectrum::w[8] / v;
    retval.w[9] = Spectrum::w[9] / v;
    retval.w[10] = Spectrum::w[10] / v;
    retval.w[11] = Spectrum::w[11] / v;
    retval.w[12] = Spectrum::w[12] / v;
    retval.w[13] = Spectrum::w[13] / v;
    retval.w[14] = Spectrum::w[14] / v;
    retval.w[15] = Spectrum::w[15] / v;
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
    return retval;
}

void Spectrum::operator/=(float v)
{
    Spectrum::w[0] /= v;
    Spectrum::w[1] /= v;
    Spectrum::w[2] /= v;
#ifdef SPECTRAL
    Spectrum::w[3] /= v;
    Spectrum::w[4] /= v;
    Spectrum::w[5] /= v;
    Spectrum::w[6] /= v;
    Spectrum::w[7] /= v;
    Spectrum::w[8] /= v;
    Spectrum::w[9] /= v;
    Spectrum::w[10] /= v;
    Spectrum::w[11] /= v;
    Spectrum::w[12] /= v;
    Spectrum::w[13] /= v;
    Spectrum::w[14] /= v;
    Spectrum::w[15] /= v;
#endif
#ifdef DEBUG
    if(!this->isValid())
        throw "Spectrum operator produced NaN values";
#endif
}
