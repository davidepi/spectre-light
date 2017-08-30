#include "spectrum.hpp"

//lookup tables for spectrum to XYZ
//taken from http://www.brucelindbloom.com/index.html?Eqn_Spect_to_XYZ.html
#if HQ_SPECTRUM==0
const float X[SPECTRUM_SAMPLES] =
{
    0.704719194064694f,
    8.05919368162368f,
    26.0397303584315f,
    26.3344474095872f,
    9.09217349249588f,
    0.468913675410046f,
    6.14434813643801f,
    29.2570087297861f,
    59.45f,
    90.6445191071685f,
    103.784866140455f,
    84.6507668018606f,
    44.2958425675426f,
    16.1994298557152f,
    4.63907953796373f,
    1.04114730065218f
};

const float Y[SPECTRUM_SAMPLES] =
{
    0.0195016632319789f,
    0.239892653121705f,
    1.71963304882257f,
    5.43351734723257f,
    13.2161643551524f,
    30.9100239096826f,
    68.950326803714f,
    96.1129005792559f,
    99.5f,
    86.0643147694386f,
    61.6534085244091f,
    37.7458551420146f,
    17.3069266562178f,
    5.99251195390313f,
    1.6862166377033f,
    0.37597729297547f
};

const float Z[SPECTRUM_SAMPLES] =
{
    3.34138395279395f,
    38.7186742138432f,
    130.621831055477f,
    151.16045260001f,
    77.2844348592836f,
    26.0294938186801f,
    7.59910194772867f,
    2.0451696873783f,
    0.39f,
    0.163225523487228f,
    0.0781659696030543f,
    0.0188233923280388f,
    0.00197793447499632f,
    0.f,
    0.f,
    0.f
};

constexpr const float INVY_SUM = 1.f/526.927171336876f;

#else

const float X[SPECTRUM_SAMPLES] =
{
    0.704719194064694f,
    2.45612825752715f,
    8.05919368162368f,
    16.3991923955296f,
    26.0397303584315f,
    29.3129037088222f,
    26.3344474095872f,
    17.8405649537739f,
    9.09217349249588f,
    2.94265977310254f,
    0.468913675410046f,
    0.898296138990984f,
    6.14434813643801f,
    16.8954464697615f,
    29.2570087297861f,
    44.3477175902877f,
    59.45f,
    74.4860262967351f,
    90.6445191071685f,
    95.9706456420296f,
    103.784866140455f,
    99.5521507183938f,
    84.6507668018606f,
    61.5120323038324f,
    44.2958425675426f,
    27.1334189988948f,
    16.1994298557152f,
    9.00732538761708f,
    4.63907953796373f,
    1.98461278785078f,
    1.04114730065218f
};

const float Y[SPECTRUM_SAMPLES]
{
    0.0195016632319789f,
    0.068304187350215f,
    0.239892653121705f,
    0.670062105629249f,
    1.71963304882257f,
    3.31317769463189f,
    5.43351734723257f,
    8.30842853959023f,
    13.2161643551524f,
    19.1231517026176f,
    30.9100239096826f,
    48.5852642916629f,
    68.950326803714f,
    87.9992438485462f,
    96.1129005792559f,
    101.796692192635f,
    99.5f,
    93.0464467058022f,
    86.0643147694386f,
    70.7880529582153f,
    61.6534085244091f,
    49.9448751359985f,
    37.7458551420146f,
    25.3746708600803f,
    17.3069266562178f,
    10.2408318620167f,
    5.99251195390313f,
    3.29787657212525f,
    1.6862166377033f,
    0.71778286291872f,
    0.37597729297547f
};

const float Z[SPECTRUM_SAMPLES]
{
    3.34138395279395f,
    11.7076764102765f,
    38.7186742138432f,
    80.0377632379214f,
    130.621831055477f,
    154.508298011424f,
    151.16045260001f,
    117.58919460011f,
    77.2844348592836f,
    42.7637136286111f,
    26.0294938186801f,
    15.2806934611155f,
    7.59910194772867f,
    4.30400013997066f,
    2.0451696873783f,
    0.895241836639712f,
    0.39f,
    0.205249514792211f,
    0.163225523487228f,
    0.102862428340868f,
    0.0781659696030543f,
    0.0337599553603171f,
    0.0188233923280388f,
    0.00478767278965021f,
    0.00197793447499632f,
    0.f,
    0.f,
    0.f,
    0.f,
    0.f,
    0.f
};

constexpr const float INVY_SUM = 1.f/1050.2020328567f

#endif

Spectrum::Spectrum()
{
    //do nothing. Too expensive to initialize if I need to assign it later
}

Spectrum::Spectrum(SpectrumType st)
{
    switch(st)
    {
        case WHITE:memset(w, 0.0f, sizeof(float)*SPECTRUM_SAMPLES);break;
        case BLACK:memset(w, 1.0f, sizeof(float)*SPECTRUM_SAMPLES);break;
            //TODO: at least CMY
        default:memset(w, 0.0f, sizeof(float)*SPECTRUM_SAMPLES);break;
    }
}

ColorXYZ Spectrum::toXYZ()const
{
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
#if HQ_SPECTRUM!=0
    x+=Spectrum::w[16]*X[16];
    x+=Spectrum::w[17]*X[17];
    x+=Spectrum::w[18]*X[18];
    x+=Spectrum::w[19]*X[19];
    x+=Spectrum::w[20]*X[20];
    x+=Spectrum::w[21]*X[21];
    x+=Spectrum::w[22]*X[22];
    x+=Spectrum::w[23]*X[23];
    x+=Spectrum::w[24]*X[24];
    x+=Spectrum::w[25]*X[25];
    x+=Spectrum::w[26]*X[26];
    x+=Spectrum::w[27]*X[27];
    x+=Spectrum::w[28]*X[28];
    x+=Spectrum::w[29]*X[29];
    x+=Spectrum::w[30]*X[30];
    y+=Spectrum::w[16]*Y[16];
    y+=Spectrum::w[17]*Y[17];
    y+=Spectrum::w[18]*Y[18];
    y+=Spectrum::w[19]*Y[19];
    y+=Spectrum::w[20]*Y[20];
    y+=Spectrum::w[21]*Y[21];
    y+=Spectrum::w[22]*Y[22];
    y+=Spectrum::w[23]*Y[23];
    y+=Spectrum::w[24]*Y[24];
    y+=Spectrum::w[25]*Y[25];
    y+=Spectrum::w[26]*Y[26];
    y+=Spectrum::w[27]*Y[27];
    y+=Spectrum::w[28]*Y[28];
    y+=Spectrum::w[29]*Y[29];
    y+=Spectrum::w[30]*Y[30];
    z+=Spectrum::w[16]*Z[16];
    z+=Spectrum::w[17]*Z[17];
    z+=Spectrum::w[18]*Z[18];
    z+=Spectrum::w[19]*Z[19];
    z+=Spectrum::w[20]*Z[20];
    z+=Spectrum::w[21]*Z[21];
    z+=Spectrum::w[22]*Z[22];
    z+=Spectrum::w[23]*Z[23];
    z+=Spectrum::w[24]*Z[24];
    z+=Spectrum::w[25]*Z[25];
    z+=Spectrum::w[26]*Z[26];
    z+=Spectrum::w[27]*Z[27];
    z+=Spectrum::w[28]*Z[28];
    z+=Spectrum::w[29]*Z[29];
    z+=Spectrum::w[30]*Z[30];
#endif
    x*=INVY_SUM;
    y*=INVY_SUM;
    z*=INVY_SUM;
    
    return ColorXYZ(x,y,z);
}

float Spectrum::yVal()const
{
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
#if HQ_SPECTRUM!=0
    y+=Spectrum::w[16]*Y[16];
    y+=Spectrum::w[17]*Y[17];
    y+=Spectrum::w[18]*Y[18];
    y+=Spectrum::w[19]*Y[19];
    y+=Spectrum::w[20]*Y[20];
    y+=Spectrum::w[21]*Y[21];
    y+=Spectrum::w[22]*Y[22];
    y+=Spectrum::w[23]*Y[23];
    y+=Spectrum::w[24]*Y[24];
    y+=Spectrum::w[25]*Y[25];
    y+=Spectrum::w[26]*Y[26];
    y+=Spectrum::w[27]*Y[27];
    y+=Spectrum::w[28]*Y[28];
    y+=Spectrum::w[29]*Y[29];
    y+=Spectrum::w[30]*Y[30];
#endif
    
    return y*INVY_SUM;
}

Spectrum Spectrum::operator+(const Spectrum& s)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] + s.w[0];
    retval.w[1] = Spectrum::w[1] + s.w[1];
    retval.w[2] = Spectrum::w[2] + s.w[2];
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
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] + s.w[16];
    retval.w[17] = Spectrum::w[17] + s.w[17];
    retval.w[18] = Spectrum::w[18] + s.w[18];
    retval.w[19] = Spectrum::w[19] + s.w[19];
    retval.w[20] = Spectrum::w[20] + s.w[20];
    retval.w[21] = Spectrum::w[21] + s.w[21];
    retval.w[22] = Spectrum::w[22] + s.w[22];
    retval.w[23] = Spectrum::w[23] + s.w[23];
    retval.w[24] = Spectrum::w[24] + s.w[24];
    retval.w[25] = Spectrum::w[25] + s.w[25];
    retval.w[26] = Spectrum::w[26] + s.w[26];
    retval.w[27] = Spectrum::w[27] + s.w[27];
    retval.w[28] = Spectrum::w[28] + s.w[28];
    retval.w[29] = Spectrum::w[29] + s.w[29];
    retval.w[30] = Spectrum::w[30] + s.w[30];
#endif
    return retval;
}

void Spectrum::operator+=(const Spectrum& s)
{
    Spectrum::w[0] += s.w[0];
    Spectrum::w[1] += s.w[1];
    Spectrum::w[2] += s.w[2];
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
#if HQ_SPECTRUM!=0
    Spectrum::w[16] += s.w[16];
    Spectrum::w[17] += s.w[17];
    Spectrum::w[18] += s.w[18];
    Spectrum::w[19] += s.w[19];
    Spectrum::w[20] += s.w[20];
    Spectrum::w[21] += s.w[21];
    Spectrum::w[22] += s.w[22];
    Spectrum::w[23] += s.w[23];
    Spectrum::w[24] += s.w[24];
    Spectrum::w[25] += s.w[25];
    Spectrum::w[26] += s.w[26];
    Spectrum::w[27] += s.w[27];
    Spectrum::w[28] += s.w[28];
    Spectrum::w[29] += s.w[29];
    Spectrum::w[30] += s.w[30];
#endif
}

Spectrum Spectrum::operator-(const Spectrum& s)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] - s.w[0];
    retval.w[1] = Spectrum::w[1] - s.w[1];
    retval.w[2] = Spectrum::w[2] - s.w[2];
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
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] - s.w[16];
    retval.w[17] = Spectrum::w[17] - s.w[17];
    retval.w[18] = Spectrum::w[18] - s.w[18];
    retval.w[19] = Spectrum::w[19] - s.w[19];
    retval.w[20] = Spectrum::w[20] - s.w[20];
    retval.w[21] = Spectrum::w[21] - s.w[21];
    retval.w[22] = Spectrum::w[22] - s.w[22];
    retval.w[23] = Spectrum::w[23] - s.w[23];
    retval.w[24] = Spectrum::w[24] - s.w[24];
    retval.w[25] = Spectrum::w[25] - s.w[25];
    retval.w[26] = Spectrum::w[26] - s.w[26];
    retval.w[27] = Spectrum::w[27] - s.w[27];
    retval.w[28] = Spectrum::w[28] - s.w[28];
    retval.w[29] = Spectrum::w[29] - s.w[29];
    retval.w[30] = Spectrum::w[30] - s.w[30];
#endif
    return retval;

}

void Spectrum::operator-=(const Spectrum& s)
{
    Spectrum::w[0] -= s.w[0];
    Spectrum::w[1] -= s.w[1];
    Spectrum::w[2] -= s.w[2];
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
#if HQ_SPECTRUM!=0
    Spectrum::w[16] -= s.w[16];
    Spectrum::w[17] -= s.w[17];
    Spectrum::w[18] -= s.w[18];
    Spectrum::w[19] -= s.w[19];
    Spectrum::w[20] -= s.w[20];
    Spectrum::w[21] -= s.w[21];
    Spectrum::w[22] -= s.w[22];
    Spectrum::w[23] -= s.w[23];
    Spectrum::w[24] -= s.w[24];
    Spectrum::w[25] -= s.w[25];
    Spectrum::w[26] -= s.w[26];
    Spectrum::w[27] -= s.w[27];
    Spectrum::w[28] -= s.w[28];
    Spectrum::w[29] -= s.w[29];
    Spectrum::w[30] -= s.w[30];
#endif
}

Spectrum Spectrum::operator*(const Spectrum& s)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] * s.w[0];
    retval.w[1] = Spectrum::w[1] * s.w[1];
    retval.w[2] = Spectrum::w[2] * s.w[2];
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
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] * s.w[16];
    retval.w[17] = Spectrum::w[17] * s.w[17];
    retval.w[18] = Spectrum::w[18] * s.w[18];
    retval.w[19] = Spectrum::w[19] * s.w[19];
    retval.w[20] = Spectrum::w[20] * s.w[20];
    retval.w[21] = Spectrum::w[21] * s.w[21];
    retval.w[22] = Spectrum::w[22] * s.w[22];
    retval.w[23] = Spectrum::w[23] * s.w[23];
    retval.w[24] = Spectrum::w[24] * s.w[24];
    retval.w[25] = Spectrum::w[25] * s.w[25];
    retval.w[26] = Spectrum::w[26] * s.w[26];
    retval.w[27] = Spectrum::w[27] * s.w[27];
    retval.w[28] = Spectrum::w[28] * s.w[28];
    retval.w[29] = Spectrum::w[29] * s.w[29];
    retval.w[30] = Spectrum::w[30] * s.w[30];
#endif
    return retval;

}

void Spectrum::operator*=(const Spectrum& s)
{
    Spectrum::w[0] *= s.w[0];
    Spectrum::w[1] *= s.w[1];
    Spectrum::w[2] *= s.w[2];
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
#if HQ_SPECTRUM!=0
    Spectrum::w[16] *= s.w[16];
    Spectrum::w[17] *= s.w[17];
    Spectrum::w[18] *= s.w[18];
    Spectrum::w[19] *= s.w[19];
    Spectrum::w[20] *= s.w[20];
    Spectrum::w[21] *= s.w[21];
    Spectrum::w[22] *= s.w[22];
    Spectrum::w[23] *= s.w[23];
    Spectrum::w[24] *= s.w[24];
    Spectrum::w[25] *= s.w[25];
    Spectrum::w[26] *= s.w[26];
    Spectrum::w[27] *= s.w[27];
    Spectrum::w[28] *= s.w[28];
    Spectrum::w[29] *= s.w[29];
    Spectrum::w[30] *= s.w[30];
#endif
}

Spectrum Spectrum::operator/(const Spectrum& s)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] / s.w[0];
    retval.w[1] = Spectrum::w[1] / s.w[1];
    retval.w[2] = Spectrum::w[2] / s.w[2];
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
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] / s.w[16];
    retval.w[17] = Spectrum::w[17] / s.w[17];
    retval.w[18] = Spectrum::w[18] / s.w[18];
    retval.w[19] = Spectrum::w[19] / s.w[19];
    retval.w[20] = Spectrum::w[20] / s.w[20];
    retval.w[21] = Spectrum::w[21] / s.w[21];
    retval.w[22] = Spectrum::w[22] / s.w[22];
    retval.w[23] = Spectrum::w[23] / s.w[23];
    retval.w[24] = Spectrum::w[24] / s.w[24];
    retval.w[25] = Spectrum::w[25] / s.w[25];
    retval.w[26] = Spectrum::w[26] / s.w[26];
    retval.w[27] = Spectrum::w[27] / s.w[27];
    retval.w[28] = Spectrum::w[28] / s.w[28];
    retval.w[29] = Spectrum::w[29] / s.w[29];
    retval.w[30] = Spectrum::w[30] / s.w[30];
#endif
    return retval;
}

void Spectrum::operator/=(const Spectrum& s)
{
    Spectrum::w[0] /= s.w[0];
    Spectrum::w[1] /= s.w[1];
    Spectrum::w[2] /= s.w[2];
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
#if HQ_SPECTRUM!=0
    Spectrum::w[16] /= s.w[16];
    Spectrum::w[17] /= s.w[17];
    Spectrum::w[18] /= s.w[18];
    Spectrum::w[19] /= s.w[19];
    Spectrum::w[20] /= s.w[20];
    Spectrum::w[21] /= s.w[21];
    Spectrum::w[22] /= s.w[22];
    Spectrum::w[23] /= s.w[23];
    Spectrum::w[24] /= s.w[24];
    Spectrum::w[25] /= s.w[25];
    Spectrum::w[26] /= s.w[26];
    Spectrum::w[27] /= s.w[27];
    Spectrum::w[28] /= s.w[28];
    Spectrum::w[29] /= s.w[29];
    Spectrum::w[30] /= s.w[30];
#endif
}

Spectrum Spectrum::operator+(float v)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] + v;
    retval.w[1] = Spectrum::w[1] + v;
    retval.w[2] = Spectrum::w[2] + v;
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
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] + v;
    retval.w[17] = Spectrum::w[17] + v;
    retval.w[18] = Spectrum::w[18] + v;
    retval.w[19] = Spectrum::w[19] + v;
    retval.w[20] = Spectrum::w[20] + v;
    retval.w[21] = Spectrum::w[21] + v;
    retval.w[22] = Spectrum::w[22] + v;
    retval.w[23] = Spectrum::w[23] + v;
    retval.w[24] = Spectrum::w[24] + v;
    retval.w[25] = Spectrum::w[25] + v;
    retval.w[26] = Spectrum::w[26] + v;
    retval.w[27] = Spectrum::w[27] + v;
    retval.w[28] = Spectrum::w[28] + v;
    retval.w[29] = Spectrum::w[29] + v;
    retval.w[30] = Spectrum::w[30] + v;
#endif
    return retval;
}

void Spectrum::operator+=(float v)
{
    Spectrum::w[0] += v;
    Spectrum::w[1] += v;
    Spectrum::w[2] += v;
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
#if HQ_SPECTRUM!=0
    Spectrum::w[16] += v;
    Spectrum::w[17] += v;
    Spectrum::w[18] += v;
    Spectrum::w[19] += v;
    Spectrum::w[20] += v;
    Spectrum::w[21] += v;
    Spectrum::w[22] += v;
    Spectrum::w[23] += v;
    Spectrum::w[24] += v;
    Spectrum::w[25] += v;
    Spectrum::w[26] += v;
    Spectrum::w[27] += v;
    Spectrum::w[28] += v;
    Spectrum::w[29] += v;
    Spectrum::w[30] += v;
#endif
}

Spectrum Spectrum::operator-(float v)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] - v;
    retval.w[1] = Spectrum::w[1] - v;
    retval.w[2] = Spectrum::w[2] - v;
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
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] - v;
    retval.w[17] = Spectrum::w[17] - v;
    retval.w[18] = Spectrum::w[18] - v;
    retval.w[19] = Spectrum::w[19] - v;
    retval.w[20] = Spectrum::w[20] - v;
    retval.w[21] = Spectrum::w[21] - v;
    retval.w[22] = Spectrum::w[22] - v;
    retval.w[23] = Spectrum::w[23] - v;
    retval.w[24] = Spectrum::w[24] - v;
    retval.w[25] = Spectrum::w[25] - v;
    retval.w[26] = Spectrum::w[26] - v;
    retval.w[27] = Spectrum::w[27] - v;
    retval.w[28] = Spectrum::w[28] - v;
    retval.w[29] = Spectrum::w[29] - v;
    retval.w[30] = Spectrum::w[30] - v;
#endif
    return retval;
}

void Spectrum::operator-=(float v)
{
    Spectrum::w[0] -= v;
    Spectrum::w[1] -= v;
    Spectrum::w[2] -= v;
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
#if HQ_SPECTRUM!=0
    Spectrum::w[16] -= v;
    Spectrum::w[17] -= v;
    Spectrum::w[18] -= v;
    Spectrum::w[19] -= v;
    Spectrum::w[20] -= v;
    Spectrum::w[21] -= v;
    Spectrum::w[22] -= v;
    Spectrum::w[23] -= v;
    Spectrum::w[24] -= v;
    Spectrum::w[25] -= v;
    Spectrum::w[26] -= v;
    Spectrum::w[27] -= v;
    Spectrum::w[28] -= v;
    Spectrum::w[29] -= v;
    Spectrum::w[30] -= v;
#endif
}

Spectrum Spectrum::operator*(float v)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] * v;
    retval.w[1] = Spectrum::w[1] * v;
    retval.w[2] = Spectrum::w[2] * v;
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
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] * v;
    retval.w[17] = Spectrum::w[17] * v;
    retval.w[18] = Spectrum::w[18] * v;
    retval.w[19] = Spectrum::w[19] * v;
    retval.w[20] = Spectrum::w[20] * v;
    retval.w[21] = Spectrum::w[21] * v;
    retval.w[22] = Spectrum::w[22] * v;
    retval.w[23] = Spectrum::w[23] * v;
    retval.w[24] = Spectrum::w[24] * v;
    retval.w[25] = Spectrum::w[25] * v;
    retval.w[26] = Spectrum::w[26] * v;
    retval.w[27] = Spectrum::w[27] * v;
    retval.w[28] = Spectrum::w[28] * v;
    retval.w[29] = Spectrum::w[29] * v;
    retval.w[30] = Spectrum::w[30] * v;
#endif
    return retval;
}

void Spectrum::operator*=(float v)
{
    Spectrum::w[0] *= v;
    Spectrum::w[1] *= v;
    Spectrum::w[2] *= v;
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
#if HQ_SPECTRUM!=0
    Spectrum::w[16] *= v;
    Spectrum::w[17] *= v;
    Spectrum::w[18] *= v;
    Spectrum::w[19] *= v;
    Spectrum::w[20] *= v;
    Spectrum::w[21] *= v;
    Spectrum::w[22] *= v;
    Spectrum::w[23] *= v;
    Spectrum::w[24] *= v;
    Spectrum::w[25] *= v;
    Spectrum::w[26] *= v;
    Spectrum::w[27] *= v;
    Spectrum::w[28] *= v;
    Spectrum::w[29] *= v;
    Spectrum::w[30] *= v;
#endif
}

Spectrum Spectrum::operator/(float v)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] / v;
    retval.w[1] = Spectrum::w[1] / v;
    retval.w[2] = Spectrum::w[2] / v;
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
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] / v;
    retval.w[17] = Spectrum::w[17] / v;
    retval.w[18] = Spectrum::w[18] / v;
    retval.w[19] = Spectrum::w[19] / v;
    retval.w[20] = Spectrum::w[20] / v;
    retval.w[21] = Spectrum::w[21] / v;
    retval.w[22] = Spectrum::w[22] / v;
    retval.w[23] = Spectrum::w[23] / v;
    retval.w[24] = Spectrum::w[24] / v;
    retval.w[25] = Spectrum::w[25] / v;
    retval.w[26] = Spectrum::w[26] / v;
    retval.w[27] = Spectrum::w[27] / v;
    retval.w[28] = Spectrum::w[28] / v;
    retval.w[29] = Spectrum::w[29] / v;
    retval.w[30] = Spectrum::w[30] / v;
#endif
    return retval;
}

void Spectrum::operator/=(float v)
{
    Spectrum::w[0] /= v;
    Spectrum::w[1] /= v;
    Spectrum::w[2] /= v;
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
#if HQ_SPECTRUM!=0
    Spectrum::w[16] /= v;
    Spectrum::w[17] /= v;
    Spectrum::w[18] /= v;
    Spectrum::w[19] /= v;
    Spectrum::w[20] /= v;
    Spectrum::w[21] /= v;
    Spectrum::w[22] /= v;
    Spectrum::w[23] /= v;
    Spectrum::w[24] /= v;
    Spectrum::w[25] /= v;
    Spectrum::w[26] /= v;
    Spectrum::w[27] /= v;
    Spectrum::w[28] /= v;
    Spectrum::w[29] /= v;
    Spectrum::w[30] /= v;
#endif
}
