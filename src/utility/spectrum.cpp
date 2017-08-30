#include "spectrum.hpp"

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
#if HQ_SPECTRUM!=0
    retval.w[15] = Spectrum::w[15] + s.w[15];
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
#if HQ_SPECTRUM!=0
    Spectrum::w[15] += s.w[15];
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
#if HQ_SPECTRUM!=0
    retval.w[15] = Spectrum::w[15] - s.w[15];
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
#if HQ_SPECTRUM!=0
    Spectrum::w[15] -= s.w[15];
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
#if HQ_SPECTRUM!=0
    retval.w[15] = Spectrum::w[15] * s.w[15];
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
#if HQ_SPECTRUM!=0
    Spectrum::w[15] *= s.w[15];
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
#if HQ_SPECTRUM!=0
    retval.w[15] = Spectrum::w[15] / s.w[15];
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
#if HQ_SPECTRUM!=0
    Spectrum::w[15] /= s.w[15];
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
#if HQ_SPECTRUM!=0
    retval.w[15] = Spectrum::w[15] + v;
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
#if HQ_SPECTRUM!=0
    Spectrum::w[15] += v;
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
#if HQ_SPECTRUM!=0
    retval.w[15] = Spectrum::w[15] - v;
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
#if HQ_SPECTRUM!=0
    Spectrum::w[15] -= v;
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
#if HQ_SPECTRUM!=0
    retval.w[15] = Spectrum::w[15] * v;
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
#if HQ_SPECTRUM!=0
    Spectrum::w[15] *= v;
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
#if HQ_SPECTRUM!=0
    retval.w[15] = Spectrum::w[15] / v;
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
#if HQ_SPECTRUM!=0
    Spectrum::w[15] /= v;
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
#endif
}
