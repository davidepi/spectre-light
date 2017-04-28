#include "matrix4.hpp"
#define CHAR_ARRAY_SIZE_PER_FLOAT 10

Matrix4::Matrix4()
{
    Matrix4::m[0][0] = .0f;
    Matrix4::m[0][1] = .0f;
    Matrix4::m[0][2] = .0f;
    Matrix4::m[0][3] = .0f;
    Matrix4::m[1][0] = .0f;
    Matrix4::m[1][1] = .0f;
    Matrix4::m[1][2] = .0f;
    Matrix4::m[1][3] = .0f;
    Matrix4::m[2][0] = .0f;
    Matrix4::m[2][1] = .0f;
    Matrix4::m[2][2] = .0f;
    Matrix4::m[2][3] = .0f;
    Matrix4::m[3][0] = .0f;
    Matrix4::m[3][1] = .0f;
    Matrix4::m[3][2] = .0f;
    Matrix4::m[3][3] = .0f;
}

Matrix4::Matrix4(int identity)
{
    (void)identity;
    Matrix4::m[0][0] = 1.0f;
    Matrix4::m[0][1] = .0f;
    Matrix4::m[0][2] = .0f;
    Matrix4::m[0][3] = .0f;
    Matrix4::m[1][0] = .0f;
    Matrix4::m[1][1] = 1.0f;
    Matrix4::m[1][2] = .0f;
    Matrix4::m[1][3] = .0f;
    Matrix4::m[2][0] = .0f;
    Matrix4::m[2][1] = .0f;
    Matrix4::m[2][2] = 1.0f;
    Matrix4::m[2][3] = .0f;
    Matrix4::m[3][0] = .0f;
    Matrix4::m[3][1] = .0f;
    Matrix4::m[3][2] = .0f;
    Matrix4::m[3][3] = 1.0f;
}

Matrix4::Matrix4(const float* v)
{
    Matrix4::m[0][0] = v[0];
    Matrix4::m[0][1] = v[1];
    Matrix4::m[0][2] = v[2];
    Matrix4::m[0][3] = v[3];
    Matrix4::m[1][0] = v[4];
    Matrix4::m[1][1] = v[5];
    Matrix4::m[1][2] = v[6];
    Matrix4::m[1][3] = v[7];
    Matrix4::m[2][0] = v[8];
    Matrix4::m[2][1] = v[9];
    Matrix4::m[2][2] = v[10];
    Matrix4::m[2][3] = v[11];
    Matrix4::m[3][0] = v[12];
    Matrix4::m[3][1] = v[13];
    Matrix4::m[3][2] = v[14];
    Matrix4::m[3][3] = v[15];
}

Matrix4::~Matrix4()
{
    
};

char* Matrix4::toString()const
{
    char val1[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val2[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val3[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val4[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val5[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val6[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val7[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val8[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val9[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val10[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val11[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val12[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val13[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val14[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val15[CHAR_ARRAY_SIZE_PER_FLOAT];
    char val16[CHAR_ARRAY_SIZE_PER_FLOAT];
    snprintf(val1,sizeof(val1),"%f",Matrix4::m[0][0]);
    snprintf(val2,sizeof(val2),"%f",Matrix4::m[0][1]);
    snprintf(val3,sizeof(val3),"%f",Matrix4::m[0][2]);
    snprintf(val4,sizeof(val4),"%f",Matrix4::m[0][3]);
    snprintf(val5,sizeof(val5),"%f",Matrix4::m[1][0]);
    snprintf(val6,sizeof(val6),"%f",Matrix4::m[1][1]);
    snprintf(val7,sizeof(val7),"%f",Matrix4::m[1][2]);
    snprintf(val8,sizeof(val8),"%f",Matrix4::m[1][3]);
    snprintf(val9,sizeof(val9),"%f",Matrix4::m[2][0]);
    snprintf(val10,sizeof(val10),"%f",Matrix4::m[2][1]);
    snprintf(val11,sizeof(val11),"%f",Matrix4::m[2][2]);
    snprintf(val12,sizeof(val12),"%f",Matrix4::m[2][3]);
    snprintf(val13,sizeof(val13),"%f",Matrix4::m[3][0]);
    snprintf(val14,sizeof(val14),"%f",Matrix4::m[3][1]);
    snprintf(val15,sizeof(val15),"%f",Matrix4::m[3][2]);
    snprintf(val16,sizeof(val16),"%f",Matrix4::m[3][3]);
    
    int res_len = (int)(16*4 +strlen(val1 ) + strlen(val2 ) + strlen(val3 ) +
                              strlen(val4 ) + strlen(val5 ) + strlen(val6 ) +
                              strlen(val7 ) + strlen(val8 ) + strlen(val9 ) +
                              strlen(val10) + strlen(val11) + strlen(val12) +
                              strlen(val13) + strlen(val14) + strlen(val15) +
                              strlen(val16));  //Matrix4 [ .. , .. , .. , ..]
    char* res = new char[res_len];
    snprintf(res,sizeof(res)*res_len,"Matrix4[%s, %s, %s, %s]\n"
                                     "       [%s, %s, %s, %s]\n"
                                     "       [%s, %s, %s, %s]\n"
                                     "       [%s, %s, %s, %s]\n",
                                             val1, val2, val3, val4,
                                             val5, val6, val7, val8,
                                             val9, val10,val11,val12,
                                             val13,val14,val15,val16);
    return res;
}

float* Matrix4::toArray()const
{
    float* res = new float[16];
    res[0] = Matrix4::m[0][0];
    res[1] = Matrix4::m[0][1];
    res[2] = Matrix4::m[0][2];
    res[3] = Matrix4::m[0][3];
    res[4] = Matrix4::m[1][0];
    res[5] = Matrix4::m[1][1];
    res[6] = Matrix4::m[1][2];
    res[7] = Matrix4::m[1][3];
    res[8] = Matrix4::m[2][0];
    res[9] = Matrix4::m[2][1];
    res[10] = Matrix4::m[2][2];
    res[11] = Matrix4::m[2][3];
    res[12] = Matrix4::m[3][0];
    res[13] = Matrix4::m[3][1];
    res[14] = Matrix4::m[3][2];
    res[15] = Matrix4::m[3][3];
    return res;
}

void Matrix4::transpose(Matrix4* output)const
{
    output->m[0][0] = Matrix4::m[0][0];
    output->m[0][1] = Matrix4::m[1][0];
    output->m[0][2] = Matrix4::m[2][0];
    output->m[0][3] = Matrix4::m[3][0];
    output->m[1][0] = Matrix4::m[0][1];
    output->m[1][1] = Matrix4::m[1][1];
    output->m[1][2] = Matrix4::m[2][1];
    output->m[1][3] = Matrix4::m[3][1];
    output->m[2][0] = Matrix4::m[0][2];
    output->m[2][1] = Matrix4::m[1][2];
    output->m[2][2] = Matrix4::m[2][2];
    output->m[2][3] = Matrix4::m[3][2];
    output->m[3][0] = Matrix4::m[0][3];
    output->m[3][1] = Matrix4::m[1][3];
    output->m[3][2] = Matrix4::m[2][3];
    output->m[3][3] = Matrix4::m[3][3];
}

bool Matrix4::inverse(Matrix4 *output)const
{
    float inv[16], det;
    
    inv[0] =    Matrix4::m[1][1] * Matrix4::m[2][2] * Matrix4::m[3][3] -
                Matrix4::m[1][1] * Matrix4::m[2][3] * Matrix4::m[3][2] -
                Matrix4::m[2][1] * Matrix4::m[1][2] * Matrix4::m[3][3] +
                Matrix4::m[2][1] * Matrix4::m[1][3] * Matrix4::m[3][2] +
                Matrix4::m[3][1] * Matrix4::m[1][2] * Matrix4::m[2][3] -
                Matrix4::m[3][1] * Matrix4::m[1][3] * Matrix4::m[2][2];
    
    inv[4] =  - Matrix4::m[1][0] * Matrix4::m[2][2] * Matrix4::m[3][3] +
                Matrix4::m[1][0] * Matrix4::m[2][3] * Matrix4::m[3][2] +
                Matrix4::m[2][0] * Matrix4::m[1][2] * Matrix4::m[3][3] -
                Matrix4::m[2][0] * Matrix4::m[1][3] * Matrix4::m[3][2] -
                Matrix4::m[3][0] * Matrix4::m[1][2] * Matrix4::m[2][3] +
                Matrix4::m[3][0] * Matrix4::m[1][3] * Matrix4::m[2][2];
    
    inv[8] =    Matrix4::m[1][0] * Matrix4::m[2][1] * Matrix4::m[3][3] -
                Matrix4::m[1][0] * Matrix4::m[2][3] * Matrix4::m[3][1] -
                Matrix4::m[2][0] * Matrix4::m[1][1] * Matrix4::m[3][3] +
                Matrix4::m[2][0] * Matrix4::m[1][3] * Matrix4::m[3][1] +
                Matrix4::m[3][0] * Matrix4::m[1][1] * Matrix4::m[2][3] -
                Matrix4::m[3][0] * Matrix4::m[1][3] * Matrix4::m[2][1];
    
    inv[12] = - Matrix4::m[1][0] * Matrix4::m[2][1] * Matrix4::m[3][2] +
                Matrix4::m[1][0] * Matrix4::m[2][2] * Matrix4::m[3][1] +
                Matrix4::m[2][0] * Matrix4::m[1][1] * Matrix4::m[3][2] -
                Matrix4::m[2][0] * Matrix4::m[1][2] * Matrix4::m[3][1] -
                Matrix4::m[3][0] * Matrix4::m[1][1] * Matrix4::m[2][2] +
                Matrix4::m[3][0] * Matrix4::m[1][2] * Matrix4::m[2][1];
    
    inv[1] =  - Matrix4::m[0][1] * Matrix4::m[2][2] * Matrix4::m[3][3] +
                Matrix4::m[0][1] * Matrix4::m[2][3] * Matrix4::m[3][2] +
                Matrix4::m[2][1] * Matrix4::m[0][2] * Matrix4::m[3][3] -
                Matrix4::m[2][1] * Matrix4::m[0][3] * Matrix4::m[3][2] -
                Matrix4::m[3][1] * Matrix4::m[0][2] * Matrix4::m[2][3] +
                Matrix4::m[3][1] * Matrix4::m[0][3] * Matrix4::m[2][2];
    
    inv[5] =    Matrix4::m[0][0] * Matrix4::m[2][2] * Matrix4::m[3][3] -
                Matrix4::m[0][0] * Matrix4::m[2][3] * Matrix4::m[3][2] -
                Matrix4::m[2][0] * Matrix4::m[0][2] * Matrix4::m[3][3] +
                Matrix4::m[2][0] * Matrix4::m[0][3] * Matrix4::m[3][2] +
                Matrix4::m[3][0] * Matrix4::m[0][2] * Matrix4::m[2][3] -
                Matrix4::m[3][0] * Matrix4::m[0][3] * Matrix4::m[2][2];
    
    inv[9] =  - Matrix4::m[0][0] * Matrix4::m[2][1] * Matrix4::m[3][3] +
                Matrix4::m[0][0] * Matrix4::m[2][3] * Matrix4::m[3][1] +
                Matrix4::m[2][0] * Matrix4::m[0][1] * Matrix4::m[3][3] -
                Matrix4::m[2][0] * Matrix4::m[0][3] * Matrix4::m[3][1] -
                Matrix4::m[3][0] * Matrix4::m[0][1] * Matrix4::m[2][3] +
                Matrix4::m[3][0] * Matrix4::m[0][3] * Matrix4::m[2][1];
    
    inv[13] =   Matrix4::m[0][0] * Matrix4::m[2][1] * Matrix4::m[3][2] -
                Matrix4::m[0][0] * Matrix4::m[2][2] * Matrix4::m[3][1] -
                Matrix4::m[2][0] * Matrix4::m[0][1] * Matrix4::m[3][2] +
                Matrix4::m[2][0] * Matrix4::m[0][2] * Matrix4::m[3][1] +
                Matrix4::m[3][0] * Matrix4::m[0][1] * Matrix4::m[2][2] -
                Matrix4::m[3][0] * Matrix4::m[0][2] * Matrix4::m[2][1];
    
    inv[2] =    Matrix4::m[0][1] * Matrix4::m[1][2] * Matrix4::m[3][3] -
                Matrix4::m[0][1] * Matrix4::m[1][3] * Matrix4::m[3][2] -
                Matrix4::m[1][1] * Matrix4::m[0][2] * Matrix4::m[3][3] +
                Matrix4::m[1][1] * Matrix4::m[0][3] * Matrix4::m[3][2] +
                Matrix4::m[3][1] * Matrix4::m[0][2] * Matrix4::m[1][3] -
                Matrix4::m[3][1] * Matrix4::m[0][3] * Matrix4::m[1][2];
    
    inv[6] =  - Matrix4::m[0][0] * Matrix4::m[1][2] * Matrix4::m[3][3] +
                Matrix4::m[0][0] * Matrix4::m[1][3] * Matrix4::m[3][2] +
                Matrix4::m[1][0] * Matrix4::m[0][2] * Matrix4::m[3][3] -
                Matrix4::m[1][0] * Matrix4::m[0][3] * Matrix4::m[3][2] -
                Matrix4::m[3][0] * Matrix4::m[0][2] * Matrix4::m[1][3] +
                Matrix4::m[3][0] * Matrix4::m[0][3] * Matrix4::m[1][2];
    
    inv[10] =   Matrix4::m[0][0] * Matrix4::m[1][1] * Matrix4::m[3][3] -
                Matrix4::m[0][0] * Matrix4::m[1][3] * Matrix4::m[3][1] -
                Matrix4::m[1][0] * Matrix4::m[0][1] * Matrix4::m[3][3] +
                Matrix4::m[1][0] * Matrix4::m[0][3] * Matrix4::m[3][1] +
                Matrix4::m[3][0] * Matrix4::m[0][1] * Matrix4::m[1][3] -
                Matrix4::m[3][0] * Matrix4::m[0][3] * Matrix4::m[1][1];
    
    inv[14] = - Matrix4::m[0][0] * Matrix4::m[1][1] * Matrix4::m[3][2] +
                Matrix4::m[0][0] * Matrix4::m[1][2] * Matrix4::m[3][1] +
                Matrix4::m[1][0] * Matrix4::m[0][1] * Matrix4::m[3][2] -
                Matrix4::m[1][0] * Matrix4::m[0][2] * Matrix4::m[3][1] -
                Matrix4::m[3][0] * Matrix4::m[0][1] * Matrix4::m[1][2] +
                Matrix4::m[3][0] * Matrix4::m[0][2] * Matrix4::m[1][1];
    
    inv[3] =  - Matrix4::m[0][1] * Matrix4::m[1][2] * Matrix4::m[2][3] +
                Matrix4::m[0][1] * Matrix4::m[1][3] * Matrix4::m[2][2] +
                Matrix4::m[1][1] * Matrix4::m[0][2] * Matrix4::m[2][3] -
                Matrix4::m[1][1] * Matrix4::m[0][3] * Matrix4::m[2][2] -
                Matrix4::m[2][1] * Matrix4::m[0][2] * Matrix4::m[1][3] +
                Matrix4::m[2][1] * Matrix4::m[0][3] * Matrix4::m[1][2];
    
    inv[7] =    Matrix4::m[0][0] * Matrix4::m[1][2] * Matrix4::m[2][3] -
                Matrix4::m[0][0] * Matrix4::m[1][3] * Matrix4::m[2][2] -
                Matrix4::m[1][0] * Matrix4::m[0][2] * Matrix4::m[2][3] +
                Matrix4::m[1][0] * Matrix4::m[0][3] * Matrix4::m[2][2] +
                Matrix4::m[2][0] * Matrix4::m[0][2] * Matrix4::m[1][3] -
                Matrix4::m[2][0] * Matrix4::m[0][3] * Matrix4::m[1][2];
    
    inv[11] = - Matrix4::m[0][0] * Matrix4::m[1][1] * Matrix4::m[2][3] +
                Matrix4::m[0][0] * Matrix4::m[1][3] * Matrix4::m[2][1] +
                Matrix4::m[1][0] * Matrix4::m[0][1] * Matrix4::m[2][3] -
                Matrix4::m[1][0] * Matrix4::m[0][3] * Matrix4::m[2][1] -
                Matrix4::m[2][0] * Matrix4::m[0][1] * Matrix4::m[1][3] +
                Matrix4::m[2][0] * Matrix4::m[0][3] * Matrix4::m[1][1];
    
    inv[15] =   Matrix4::m[0][0] * Matrix4::m[1][1] * Matrix4::m[2][2] -
                Matrix4::m[0][0] * Matrix4::m[1][2] * Matrix4::m[2][1] -
                Matrix4::m[1][0] * Matrix4::m[0][1] * Matrix4::m[2][2] +
                Matrix4::m[1][0] * Matrix4::m[0][2] * Matrix4::m[2][1] +
                Matrix4::m[2][0] * Matrix4::m[0][1] * Matrix4::m[1][2] -
                Matrix4::m[2][0] * Matrix4::m[0][2] * Matrix4::m[1][1];
    
    det = Matrix4::m[0][0] * inv[0] + Matrix4::m[0][1] * inv[4]
        + Matrix4::m[0][2] * inv[8] + Matrix4::m[0][3] * inv[12];
    
    if (det == 0)
        return false;
    
    det = 1.0 / det;
    
    output->m[0][0] = inv[0]  * det;
    output->m[0][1] = inv[1]  * det;
    output->m[0][2] = inv[2]  * det;
    output->m[0][3] = inv[3]  * det;
    output->m[1][0] = inv[4]  * det;
    output->m[1][1] = inv[5]  * det;
    output->m[1][2] = inv[6]  * det;
    output->m[1][3] = inv[7]  * det;
    output->m[2][0] = inv[8]  * det;
    output->m[2][1] = inv[9]  * det;
    output->m[2][2] = inv[10] * det;
    output->m[2][3] = inv[11] * det;
    output->m[3][0] = inv[12] * det;
    output->m[3][1] = inv[13] * det;
    output->m[3][2] = inv[14] * det;
    output->m[3][3] = inv[15] * det;
    
    return true;
}

//♥ ♥ ♥ Operators ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥

Matrix4 Matrix4::operator+(const Matrix4& mat)const
{
    float* val = new float[16];
    val[0] = Matrix4::m[0][0] + mat.m[0][0];
    val[1] = Matrix4::m[0][1] + mat.m[0][1];
    val[2] = Matrix4::m[0][2] + mat.m[0][2];
    val[3] = Matrix4::m[0][3] + mat.m[0][3];
    val[4] = Matrix4::m[1][0] + mat.m[1][0];
    val[5] = Matrix4::m[1][1] + mat.m[1][1];
    val[6] = Matrix4::m[1][2] + mat.m[1][2];
    val[7] = Matrix4::m[1][3] + mat.m[1][3];
    val[8] = Matrix4::m[2][0] + mat.m[2][0];
    val[9] = Matrix4::m[2][1] + mat.m[2][1];
    val[10] = Matrix4::m[2][2] + mat.m[2][2];
    val[11] = Matrix4::m[2][3] + mat.m[2][3];
    val[12] = Matrix4::m[3][0] + mat.m[3][0];
    val[13] = Matrix4::m[3][1] + mat.m[3][1];
    val[14] = Matrix4::m[3][2] + mat.m[3][2];
    val[15] = Matrix4::m[3][3] + mat.m[3][3];
    
    Matrix4 res = Matrix4(val);
    delete[] val;
    return res;
}

Matrix4 Matrix4::operator-(const Matrix4& mat)const
{    float* val = new float[16];
    val[0] = Matrix4::m[0][0] - mat.m[0][0];
    val[1] = Matrix4::m[0][1] - mat.m[0][1];
    val[2] = Matrix4::m[0][2] - mat.m[0][2];
    val[3] = Matrix4::m[0][3] - mat.m[0][3];
    val[4] = Matrix4::m[1][0] - mat.m[1][0];
    val[5] = Matrix4::m[1][1] - mat.m[1][1];
    val[6] = Matrix4::m[1][2] - mat.m[1][2];
    val[7] = Matrix4::m[1][3] - mat.m[1][3];
    val[8] = Matrix4::m[2][0] - mat.m[2][0];
    val[9] = Matrix4::m[2][1] - mat.m[2][1];
    val[10] = Matrix4::m[2][2] - mat.m[2][2];
    val[11] = Matrix4::m[2][3] - mat.m[2][3];
    val[12] = Matrix4::m[3][0] - mat.m[3][0];
    val[13] = Matrix4::m[3][1] - mat.m[3][1];
    val[14] = Matrix4::m[3][2] - mat.m[3][2];
    val[15] = Matrix4::m[3][3] - mat.m[3][3];
    
    Matrix4 res = Matrix4(val);
    delete[] val;
    return res;
}

void Matrix4::operator+=(const Matrix4& mat)
{
    Matrix4::m[0][0] += mat.m[0][0];
    Matrix4::m[0][1] += mat.m[0][1];
    Matrix4::m[0][2] += mat.m[0][2];
    Matrix4::m[0][3] += mat.m[0][3];
    Matrix4::m[1][0] += mat.m[1][0];
    Matrix4::m[1][1] += mat.m[1][1];
    Matrix4::m[1][2] += mat.m[1][2];
    Matrix4::m[1][3] += mat.m[1][3];
    Matrix4::m[2][0] += mat.m[2][0];
    Matrix4::m[2][1] += mat.m[2][1];
    Matrix4::m[2][2] += mat.m[2][2];
    Matrix4::m[2][3] += mat.m[2][3];
    Matrix4::m[3][0] += mat.m[3][0];
    Matrix4::m[3][1] += mat.m[3][1];
    Matrix4::m[3][2] += mat.m[3][2];
    Matrix4::m[3][3] += mat.m[3][3];
}

void Matrix4::operator-=(const Matrix4& mat)
{
    Matrix4::m[0][0] -= mat.m[0][0];
    Matrix4::m[0][1] -= mat.m[0][1];
    Matrix4::m[0][2] -= mat.m[0][2];
    Matrix4::m[0][3] -= mat.m[0][3];
    Matrix4::m[1][0] -= mat.m[1][0];
    Matrix4::m[1][1] -= mat.m[1][1];
    Matrix4::m[1][2] -= mat.m[1][2];
    Matrix4::m[1][3] -= mat.m[1][3];
    Matrix4::m[2][0] -= mat.m[2][0];
    Matrix4::m[2][1] -= mat.m[2][1];
    Matrix4::m[2][2] -= mat.m[2][2];
    Matrix4::m[2][3] -= mat.m[2][3];
    Matrix4::m[3][0] -= mat.m[3][0];
    Matrix4::m[3][1] -= mat.m[3][1];
    Matrix4::m[3][2] -= mat.m[3][2];
    Matrix4::m[3][3] -= mat.m[3][3];
}

Matrix4 Matrix4::operator*(const Matrix4& mat)const
{
    float val[16];
    val[0] = (Matrix4::m[0][0] * mat.m[0][0]) +
             (Matrix4::m[0][1] * mat.m[1][0]) +
             (Matrix4::m[0][2] * mat.m[2][0]) +
             (Matrix4::m[0][3] * mat.m[3][0]);
    
    val[1] = (Matrix4::m[0][0] * mat.m[0][1]) +
             (Matrix4::m[0][1] * mat.m[1][1]) +
             (Matrix4::m[0][2] * mat.m[2][1]) +
             (Matrix4::m[0][3] * mat.m[3][1]);
    
    val[2] = (Matrix4::m[0][0] * mat.m[0][2]) +
             (Matrix4::m[0][1] * mat.m[1][2]) +
             (Matrix4::m[0][2] * mat.m[2][2]) +
             (Matrix4::m[0][3] * mat.m[3][2]);
    
    val[3] = (Matrix4::m[0][0] * mat.m[0][3]) +
             (Matrix4::m[0][1] * mat.m[1][3]) +
             (Matrix4::m[0][2] * mat.m[2][3]) +
             (Matrix4::m[0][3] * mat.m[3][3]);
    
    val[4] = (Matrix4::m[1][0] * mat.m[0][0]) +
             (Matrix4::m[1][1] * mat.m[1][0]) +
             (Matrix4::m[1][2] * mat.m[2][0]) +
             (Matrix4::m[1][3] * mat.m[3][0]);
    
    val[5] = (Matrix4::m[1][0] * mat.m[0][1]) +
             (Matrix4::m[1][1] * mat.m[1][1]) +
             (Matrix4::m[1][2] * mat.m[2][1]) +
             (Matrix4::m[1][3] * mat.m[3][1]);
    
    val[6] = (Matrix4::m[1][0] * mat.m[0][2]) +
             (Matrix4::m[1][1] * mat.m[1][2]) +
             (Matrix4::m[1][2] * mat.m[2][2]) +
             (Matrix4::m[1][3] * mat.m[3][2]);
    
    val[7] = (Matrix4::m[1][0] * mat.m[0][3]) +
             (Matrix4::m[1][1] * mat.m[1][3]) +
             (Matrix4::m[1][2] * mat.m[2][3]) +
             (Matrix4::m[1][3] * mat.m[3][3]);
    
    val[8] = (Matrix4::m[2][0] * mat.m[0][0]) +
             (Matrix4::m[2][1] * mat.m[1][0]) +
             (Matrix4::m[2][2] * mat.m[2][0]) +
             (Matrix4::m[2][3] * mat.m[3][0]);
    
    val[9] = (Matrix4::m[2][0] * mat.m[0][1]) +
             (Matrix4::m[2][1] * mat.m[1][1]) +
             (Matrix4::m[2][2] * mat.m[2][1]) +
             (Matrix4::m[2][3] * mat.m[3][1]);
    
    val[10] = (Matrix4::m[2][0] * mat.m[0][2]) +
              (Matrix4::m[2][1] * mat.m[1][2]) +
              (Matrix4::m[2][2] * mat.m[2][2]) +
              (Matrix4::m[2][3] * mat.m[3][2]);
    
    val[11] = (Matrix4::m[2][0] * mat.m[0][3]) +
              (Matrix4::m[2][1] * mat.m[1][3]) +
              (Matrix4::m[2][2] * mat.m[2][3]) +
              (Matrix4::m[2][3] * mat.m[3][3]);
    
    val[12] = (Matrix4::m[3][0] * mat.m[0][0]) +
              (Matrix4::m[3][1] * mat.m[1][0]) +
              (Matrix4::m[3][2] * mat.m[2][0]) +
              (Matrix4::m[3][3] * mat.m[3][0]);
    
    val[13] = (Matrix4::m[3][0] * mat.m[0][1]) +
              (Matrix4::m[3][1] * mat.m[1][1]) +
              (Matrix4::m[3][2] * mat.m[2][1]) +
              (Matrix4::m[3][3] * mat.m[3][1]);
    
    val[14] = (Matrix4::m[3][0] * mat.m[0][2]) +
              (Matrix4::m[3][1] * mat.m[1][2]) +
              (Matrix4::m[3][2] * mat.m[2][2]) +
              (Matrix4::m[3][3] * mat.m[3][2]);
    
    val[15] = (Matrix4::m[3][0] * mat.m[0][3]) +
              (Matrix4::m[3][1] * mat.m[1][3]) +
              (Matrix4::m[3][2] * mat.m[2][3]) +
              (Matrix4::m[3][3] * mat.m[3][3]);
    
    Matrix4 res = Matrix4(val);
    return res;
}

void Matrix4::operator*=(const Matrix4& mat)
{
    float val[16];
    val[0] = (Matrix4::m[0][0] * mat.m[0][0]) +
             (Matrix4::m[0][1] * mat.m[1][0]) +
             (Matrix4::m[0][2] * mat.m[2][0]) +
             (Matrix4::m[0][3] * mat.m[3][0]);
    
    val[1] = (Matrix4::m[0][0] * mat.m[0][1]) +
             (Matrix4::m[0][1] * mat.m[1][1]) +
             (Matrix4::m[0][2] * mat.m[2][1]) +
             (Matrix4::m[0][3] * mat.m[3][1]);
    
    val[2] = (Matrix4::m[0][0] * mat.m[0][2]) +
             (Matrix4::m[0][1] * mat.m[1][2]) +
             (Matrix4::m[0][2] * mat.m[2][2]) +
             (Matrix4::m[0][3] * mat.m[3][2]);
    
    val[3] = (Matrix4::m[0][0] * mat.m[0][3]) +
             (Matrix4::m[0][1] * mat.m[1][3]) +
             (Matrix4::m[0][2] * mat.m[2][3]) +
             (Matrix4::m[0][3] * mat.m[3][3]);
    
    val[4] = (Matrix4::m[1][0] * mat.m[0][0]) +
             (Matrix4::m[1][1] * mat.m[1][0]) +
             (Matrix4::m[1][2] * mat.m[2][0]) +
             (Matrix4::m[1][3] * mat.m[3][0]);
    
    val[5] = (Matrix4::m[1][0] * mat.m[0][1]) +
             (Matrix4::m[1][1] * mat.m[1][1]) +
             (Matrix4::m[1][2] * mat.m[2][1]) +
             (Matrix4::m[1][3] * mat.m[3][1]);
    
    val[6] = (Matrix4::m[1][0] * mat.m[0][2]) +
             (Matrix4::m[1][1] * mat.m[1][2]) +
             (Matrix4::m[1][2] * mat.m[2][2]) +
             (Matrix4::m[1][3] * mat.m[3][2]);
    
    val[7] = (Matrix4::m[1][0] * mat.m[0][3]) +
             (Matrix4::m[1][1] * mat.m[1][3]) +
             (Matrix4::m[1][2] * mat.m[2][3]) +
             (Matrix4::m[1][3] * mat.m[3][3]);
    
    val[8] = (Matrix4::m[2][0] * mat.m[0][0]) +
             (Matrix4::m[2][1] * mat.m[1][0]) +
             (Matrix4::m[2][2] * mat.m[2][0]) +
             (Matrix4::m[2][3] * mat.m[3][0]);
    
    val[9] = (Matrix4::m[2][0] * mat.m[0][1]) +
             (Matrix4::m[2][1] * mat.m[1][1]) +
             (Matrix4::m[2][2] * mat.m[2][1]) +
             (Matrix4::m[2][3] * mat.m[3][1]);
    
    val[10] = (Matrix4::m[2][0] * mat.m[0][2]) +
              (Matrix4::m[2][1] * mat.m[1][2]) +
              (Matrix4::m[2][2] * mat.m[2][2]) +
              (Matrix4::m[2][3] * mat.m[3][2]);
    
    val[11] = (Matrix4::m[2][0] * mat.m[0][3]) +
              (Matrix4::m[2][1] * mat.m[1][3]) +
              (Matrix4::m[2][2] * mat.m[2][3]) +
              (Matrix4::m[2][3] * mat.m[3][3]);
    
    val[12] = (Matrix4::m[3][0] * mat.m[0][0]) +
              (Matrix4::m[3][1] * mat.m[1][0]) +
              (Matrix4::m[3][2] * mat.m[2][0]) +
              (Matrix4::m[3][3] * mat.m[3][0]);
    
    val[13] = (Matrix4::m[3][0] * mat.m[0][1]) +
              (Matrix4::m[3][1] * mat.m[1][1]) +
              (Matrix4::m[3][2] * mat.m[2][1]) +
              (Matrix4::m[3][3] * mat.m[3][1]);
    
    val[14] = (Matrix4::m[3][0] * mat.m[0][2]) +
              (Matrix4::m[3][1] * mat.m[1][2]) +
              (Matrix4::m[3][2] * mat.m[2][2]) +
              (Matrix4::m[3][3] * mat.m[3][2]);
    
    val[15] = (Matrix4::m[3][0] * mat.m[0][3]) +
              (Matrix4::m[3][1] * mat.m[1][3]) +
              (Matrix4::m[3][2] * mat.m[2][3]) +
              (Matrix4::m[3][3] * mat.m[3][3]);
    
    Matrix4::m[0][0] = val[0];
    Matrix4::m[0][1] = val[1];
    Matrix4::m[0][2] = val[2];
    Matrix4::m[0][3] = val[3];
    Matrix4::m[1][0] = val[4];
    Matrix4::m[1][1] = val[5];
    Matrix4::m[1][2] = val[6];
    Matrix4::m[1][3] = val[7];
    Matrix4::m[2][0] = val[8];
    Matrix4::m[2][1] = val[9];
    Matrix4::m[2][2] = val[10];
    Matrix4::m[2][3] = val[11];
    Matrix4::m[3][0] = val[12];
    Matrix4::m[3][1] = val[13];
    Matrix4::m[3][2] = val[14];
    Matrix4::m[3][3] = val[15];
}

Matrix4 Matrix4::operator/(const Matrix4& mat)const
{
    float val[16];
    val[0] = (Matrix4::m[0][0] / mat.m[0][0]) +
             (Matrix4::m[0][1] / mat.m[1][0]) +
             (Matrix4::m[0][2] / mat.m[2][0]) +
             (Matrix4::m[0][3] / mat.m[3][0]);
    
    val[1] = (Matrix4::m[0][0] / mat.m[0][1]) +
             (Matrix4::m[0][1] / mat.m[1][1]) +
             (Matrix4::m[0][2] / mat.m[2][1]) +
             (Matrix4::m[0][3] / mat.m[3][1]);
    
    val[2] = (Matrix4::m[0][0] / mat.m[0][2]) +
             (Matrix4::m[0][1] / mat.m[1][2]) +
             (Matrix4::m[0][2] / mat.m[2][2]) +
             (Matrix4::m[0][3] / mat.m[3][2]);
    
    val[3] = (Matrix4::m[0][0] / mat.m[0][3]) +
             (Matrix4::m[0][1] / mat.m[1][3]) +
             (Matrix4::m[0][2] / mat.m[2][3]) +
             (Matrix4::m[0][3] / mat.m[3][3]);
    
    val[4] = (Matrix4::m[1][0] / mat.m[0][0]) +
             (Matrix4::m[1][1] / mat.m[1][0]) +
             (Matrix4::m[1][2] / mat.m[2][0]) +
             (Matrix4::m[1][3] / mat.m[3][0]);
    
    val[5] = (Matrix4::m[1][0] / mat.m[0][1]) +
             (Matrix4::m[1][1] / mat.m[1][1]) +
             (Matrix4::m[1][2] / mat.m[2][1]) +
             (Matrix4::m[1][3] / mat.m[3][1]);
    
    val[6] = (Matrix4::m[1][0] / mat.m[0][2]) +
             (Matrix4::m[1][1] / mat.m[1][2]) +
             (Matrix4::m[1][2] / mat.m[2][2]) +
             (Matrix4::m[1][3] / mat.m[3][2]);
    
    val[7] = (Matrix4::m[1][0] / mat.m[0][3]) +
             (Matrix4::m[1][1] / mat.m[1][3]) +
             (Matrix4::m[1][2] / mat.m[2][3]) +
             (Matrix4::m[1][3] / mat.m[3][3]);
    
    val[8] = (Matrix4::m[2][0] / mat.m[0][0]) +
             (Matrix4::m[2][1] / mat.m[1][0]) +
             (Matrix4::m[2][2] / mat.m[2][0]) +
             (Matrix4::m[2][3] / mat.m[3][0]);
    
    val[9] = (Matrix4::m[2][0] / mat.m[0][1]) +
             (Matrix4::m[2][1] / mat.m[1][1]) +
             (Matrix4::m[2][2] / mat.m[2][1]) +
             (Matrix4::m[2][3] / mat.m[3][1]);
    
    val[10] = (Matrix4::m[2][0] / mat.m[0][2]) +
              (Matrix4::m[2][1] / mat.m[1][2]) +
              (Matrix4::m[2][2] / mat.m[2][2]) +
              (Matrix4::m[2][3] / mat.m[3][2]);
    
    val[11] = (Matrix4::m[2][0] / mat.m[0][3]) +
              (Matrix4::m[2][1] / mat.m[1][3]) +
              (Matrix4::m[2][2] / mat.m[2][3]) +
              (Matrix4::m[2][3] / mat.m[3][3]);
    
    val[12] = (Matrix4::m[3][0] / mat.m[0][0]) +
              (Matrix4::m[3][1] / mat.m[1][0]) +
              (Matrix4::m[3][2] / mat.m[2][0]) +
              (Matrix4::m[3][3] / mat.m[3][0]);
    
    val[13] = (Matrix4::m[3][0] / mat.m[0][1]) +
              (Matrix4::m[3][1] / mat.m[1][1]) +
              (Matrix4::m[3][2] / mat.m[2][1]) +
              (Matrix4::m[3][3] / mat.m[3][1]);
    
    val[14] = (Matrix4::m[3][0] / mat.m[0][2]) +
              (Matrix4::m[3][1] / mat.m[1][2]) +
              (Matrix4::m[3][2] / mat.m[2][2]) +
              (Matrix4::m[3][3] / mat.m[3][2]);
    
    val[15] = (Matrix4::m[3][0] / mat.m[0][3]) +
              (Matrix4::m[3][1] / mat.m[1][3]) +
              (Matrix4::m[3][2] / mat.m[2][3]) +
              (Matrix4::m[3][3] / mat.m[3][3]);
    
    Matrix4 res = Matrix4(val);
    return res;
}

void Matrix4::operator/=(const Matrix4& mat)
{
    float val[16];
    val[0] = (Matrix4::m[0][0] / mat.m[0][0]) +
             (Matrix4::m[0][1] / mat.m[1][0]) +
             (Matrix4::m[0][2] / mat.m[2][0]) +
             (Matrix4::m[0][3] / mat.m[3][0]);
    
    val[1] = (Matrix4::m[0][0] / mat.m[0][1]) +
             (Matrix4::m[0][1] / mat.m[1][1]) +
             (Matrix4::m[0][2] / mat.m[2][1]) +
             (Matrix4::m[0][3] / mat.m[3][1]);
    
    val[2] = (Matrix4::m[0][0] / mat.m[0][2]) +
             (Matrix4::m[0][1] / mat.m[1][2]) +
             (Matrix4::m[0][2] / mat.m[2][2]) +
             (Matrix4::m[0][3] / mat.m[3][2]);
    
    val[3] = (Matrix4::m[0][0] / mat.m[0][3]) +
             (Matrix4::m[0][1] / mat.m[1][3]) +
             (Matrix4::m[0][2] / mat.m[2][3]) +
             (Matrix4::m[0][3] / mat.m[3][3]);
    
    val[4] = (Matrix4::m[1][0] / mat.m[0][0]) +
             (Matrix4::m[1][1] / mat.m[1][0]) +
             (Matrix4::m[1][2] / mat.m[2][0]) +
             (Matrix4::m[1][3] / mat.m[3][0]);
    
    val[5] = (Matrix4::m[1][0] / mat.m[0][1]) +
             (Matrix4::m[1][1] / mat.m[1][1]) +
             (Matrix4::m[1][2] / mat.m[2][1]) +
             (Matrix4::m[1][3] / mat.m[3][1]);
    
    val[6] = (Matrix4::m[1][0] / mat.m[0][2]) +
             (Matrix4::m[1][1] / mat.m[1][2]) +
             (Matrix4::m[1][2] / mat.m[2][2]) +
             (Matrix4::m[1][3] / mat.m[3][2]);
    
    val[7] = (Matrix4::m[1][0] / mat.m[0][3]) +
             (Matrix4::m[1][1] / mat.m[1][3]) +
             (Matrix4::m[1][2] / mat.m[2][3]) +
             (Matrix4::m[1][3] / mat.m[3][3]);
    
    val[8] = (Matrix4::m[2][0] / mat.m[0][0]) +
             (Matrix4::m[2][1] / mat.m[1][0]) +
             (Matrix4::m[2][2] / mat.m[2][0]) +
             (Matrix4::m[2][3] / mat.m[3][0]);
    
    val[9] = (Matrix4::m[2][0] / mat.m[0][1]) +
             (Matrix4::m[2][1] / mat.m[1][1]) +
             (Matrix4::m[2][2] / mat.m[2][1]) +
             (Matrix4::m[2][3] / mat.m[3][1]);
    
    val[10] = (Matrix4::m[2][0] / mat.m[0][2]) +
              (Matrix4::m[2][1] / mat.m[1][2]) +
              (Matrix4::m[2][2] / mat.m[2][2]) +
              (Matrix4::m[2][3] / mat.m[3][2]);
    
    val[11] = (Matrix4::m[2][0] / mat.m[0][3]) +
              (Matrix4::m[2][1] / mat.m[1][3]) +
              (Matrix4::m[2][2] / mat.m[2][3]) +
              (Matrix4::m[2][3] / mat.m[3][3]);
    
    val[12] = (Matrix4::m[3][0] / mat.m[0][0]) +
              (Matrix4::m[3][1] / mat.m[1][0]) +
              (Matrix4::m[3][2] / mat.m[2][0]) +
              (Matrix4::m[3][3] / mat.m[3][0]);
    
    val[13] = (Matrix4::m[3][0] / mat.m[0][1]) +
              (Matrix4::m[3][1] / mat.m[1][1]) +
              (Matrix4::m[3][2] / mat.m[2][1]) +
              (Matrix4::m[3][3] / mat.m[3][1]);
    
    val[14] = (Matrix4::m[3][0] / mat.m[0][2]) +
              (Matrix4::m[3][1] / mat.m[1][2]) +
              (Matrix4::m[3][2] / mat.m[2][2]) +
              (Matrix4::m[3][3] / mat.m[3][2]);
    
    val[15] = (Matrix4::m[3][0] / mat.m[0][3]) +
              (Matrix4::m[3][1] / mat.m[1][3]) +
              (Matrix4::m[3][2] / mat.m[2][3]) +
              (Matrix4::m[3][3] / mat.m[3][3]);
    
    Matrix4::m[0][0] = val[0];
    Matrix4::m[0][1] = val[1];
    Matrix4::m[0][2] = val[2];
    Matrix4::m[0][3] = val[3];
    Matrix4::m[1][0] = val[4];
    Matrix4::m[1][1] = val[5];
    Matrix4::m[1][2] = val[6];
    Matrix4::m[1][3] = val[7];
    Matrix4::m[2][0] = val[8];
    Matrix4::m[2][1] = val[9];
    Matrix4::m[2][2] = val[10];
    Matrix4::m[2][3] = val[11];
    Matrix4::m[3][0] = val[12];
    Matrix4::m[3][1] = val[13];
    Matrix4::m[3][2] = val[14];
    Matrix4::m[3][3] = val[15];
}

bool Matrix4::operator==(const Matrix4& mat)const
{
    return Matrix4::m[0][0] == mat.m[0][0] &&
           Matrix4::m[0][1] == mat.m[0][1] &&
           Matrix4::m[0][2] == mat.m[0][2] &&
           Matrix4::m[0][3] == mat.m[0][3] &&
           Matrix4::m[1][0] == mat.m[1][0] &&
           Matrix4::m[1][1] == mat.m[1][1] &&
           Matrix4::m[1][2] == mat.m[1][2] &&
           Matrix4::m[1][3] == mat.m[1][3] &&
           Matrix4::m[2][0] == mat.m[2][0] &&
           Matrix4::m[2][1] == mat.m[2][1] &&
           Matrix4::m[2][2] == mat.m[2][2] &&
           Matrix4::m[2][3] == mat.m[2][3] &&
           Matrix4::m[3][0] == mat.m[3][0] &&
           Matrix4::m[3][1] == mat.m[3][1] &&
           Matrix4::m[3][2] == mat.m[3][2] &&
           Matrix4::m[3][3] == mat.m[3][3];
}

bool Matrix4::operator!=(const Matrix4& mat)const
{
    return !(Matrix4::m[0][0] == mat.m[0][0] &&
             Matrix4::m[0][1] == mat.m[0][1] &&
             Matrix4::m[0][2] == mat.m[0][2] &&
             Matrix4::m[0][3] == mat.m[0][3] &&
             Matrix4::m[1][0] == mat.m[1][0] &&
             Matrix4::m[1][1] == mat.m[1][1] &&
             Matrix4::m[1][2] == mat.m[1][2] &&
             Matrix4::m[1][3] == mat.m[1][3] &&
             Matrix4::m[2][0] == mat.m[2][0] &&
             Matrix4::m[2][1] == mat.m[2][1] &&
             Matrix4::m[2][2] == mat.m[2][2] &&
             Matrix4::m[2][3] == mat.m[2][3] &&
             Matrix4::m[3][0] == mat.m[3][0] &&
             Matrix4::m[3][1] == mat.m[3][1] &&
             Matrix4::m[3][2] == mat.m[3][2] &&
             Matrix4::m[3][3] == mat.m[3][3] );
}

void sum (const Matrix4* input1, const Matrix4* input2, Matrix4* output)
{
  output->m[0][0] = input1->m[0][0] + input2->m[0][0];
  output->m[0][1] = input1->m[0][1] + input2->m[0][1];
  output->m[0][2] = input1->m[0][2] + input2->m[0][2];
  output->m[0][3] = input1->m[0][3] + input2->m[0][3];
  output->m[1][0] = input1->m[1][0] + input2->m[1][0];
  output->m[1][1] = input1->m[1][1] + input2->m[1][1];
  output->m[1][2] = input1->m[1][2] + input2->m[1][2];
  output->m[1][3] = input1->m[1][3] + input2->m[1][3];
  output->m[2][0] = input1->m[2][0] + input2->m[2][0];
  output->m[2][1] = input1->m[2][1] + input2->m[2][1];
  output->m[2][2] = input1->m[2][2] + input2->m[2][2];
  output->m[2][3] = input1->m[2][3] + input2->m[2][3];
  output->m[3][0] = input1->m[3][0] + input2->m[3][0];
  output->m[3][1] = input1->m[3][1] + input2->m[3][1];
  output->m[3][2] = input1->m[3][2] + input2->m[3][2];
  output->m[3][3] = input1->m[3][3] + input2->m[3][3];
}

void sub (const Matrix4* input1, const Matrix4* input2, Matrix4* output)
{
  output->m[0][0] = input1->m[0][0] - input2->m[0][0];
  output->m[0][1] = input1->m[0][1] - input2->m[0][1];
  output->m[0][2] = input1->m[0][2] - input2->m[0][2];
  output->m[0][3] = input1->m[0][3] - input2->m[0][3];
  output->m[1][0] = input1->m[1][0] - input2->m[1][0];
  output->m[1][1] = input1->m[1][1] - input2->m[1][1];
  output->m[1][2] = input1->m[1][2] - input2->m[1][2];
  output->m[1][3] = input1->m[1][3] - input2->m[1][3];
  output->m[2][0] = input1->m[2][0] - input2->m[2][0];
  output->m[2][1] = input1->m[2][1] - input2->m[2][1];
  output->m[2][2] = input1->m[2][2] - input2->m[2][2];
  output->m[2][3] = input1->m[2][3] - input2->m[2][3];
  output->m[3][0] = input1->m[3][0] - input2->m[3][0];
  output->m[3][1] = input1->m[3][1] - input2->m[3][1];
  output->m[3][2] = input1->m[3][2] - input2->m[3][2];
  output->m[3][3] = input1->m[3][3] - input2->m[3][3];
}

void mull (const Matrix4* input1, const Matrix4* input2, Matrix4* output)
{
  output->m[0][0] = (input1->m[0][0] * input2->m[0][0]) +
                    (input1->m[0][1] * input2->m[1][0]) +
                    (input1->m[0][2] * input2->m[2][0]) +
                    (input1->m[0][3] * input2->m[3][0]);
    
  output->m[0][1] = (input1->m[0][0] * input2->m[0][1]) +
                    (input1->m[0][1] * input2->m[1][1]) +
                    (input1->m[0][2] * input2->m[2][1]) +
                    (input1->m[0][3] * input2->m[3][1]);
    
  output->m[0][2] = (input1->m[0][0] * input2->m[0][2]) +
                    (input1->m[0][1] * input2->m[1][2]) +
                    (input1->m[0][2] * input2->m[2][2]) +
                    (input1->m[0][3] * input2->m[3][2]);
    
  output->m[0][3] = (input1->m[0][0] * input2->m[0][3]) +
                    (input1->m[0][1] * input2->m[1][3]) +
                    (input1->m[0][2] * input2->m[2][3]) +
                    (input1->m[0][3] * input2->m[3][3]);
    
  output->m[1][0] = (input1->m[1][0] * input2->m[0][0]) +
                    (input1->m[1][1] * input2->m[1][0]) +
                    (input1->m[1][2] * input2->m[2][0]) +
                    (input1->m[1][3] * input2->m[3][0]);
    
  output->m[1][1] = (input1->m[1][0] * input2->m[0][1]) +
                    (input1->m[1][1] * input2->m[1][1]) +
                    (input1->m[1][2] * input2->m[2][1]) +
                    (input1->m[1][3] * input2->m[3][1]);
    
  output->m[1][2] = (input1->m[1][0] * input2->m[0][2]) +
                    (input1->m[1][1] * input2->m[1][2]) +
                    (input1->m[1][2] * input2->m[2][2]) +
                    (input1->m[1][3] * input2->m[3][2]);
    
  output->m[1][3] = (input1->m[1][0] * input2->m[0][3]) +
                    (input1->m[1][1] * input2->m[1][3]) +
                    (input1->m[1][2] * input2->m[2][3]) +
                    (input1->m[1][3] * input2->m[3][3]);
    
  output->m[2][0] = (input1->m[2][0] * input2->m[0][0]) +
                    (input1->m[2][1] * input2->m[1][0]) +
                    (input1->m[2][2] * input2->m[2][0]) +
                    (input1->m[2][3] * input2->m[3][0]);
    
  output->m[2][1] = (input1->m[2][0] * input2->m[0][1]) +
                    (input1->m[2][1] * input2->m[1][1]) +
                    (input1->m[2][2] * input2->m[2][1]) +
                    (input1->m[2][3] * input2->m[3][1]);
    
  output->m[2][2] = (input1->m[2][0] * input2->m[0][2]) +
                    (input1->m[2][1] * input2->m[1][2]) +
                    (input1->m[2][2] * input2->m[2][2]) +
                    (input1->m[2][3] * input2->m[3][2]);
    
  output->m[2][3] = (input1->m[2][0] * input2->m[0][3]) +
                    (input1->m[2][1] * input2->m[1][3]) +
                    (input1->m[2][2] * input2->m[2][3]) +
                    (input1->m[2][3] * input2->m[3][3]);
    
  output->m[3][0] = (input1->m[3][0] * input2->m[0][0]) +
                    (input1->m[3][1] * input2->m[1][0]) +
                    (input1->m[3][2] * input2->m[2][0]) +
                    (input1->m[3][3] * input2->m[3][0]);
    
  output->m[3][1] = (input1->m[3][0] * input2->m[0][1]) +
                    (input1->m[3][1] * input2->m[1][1]) +
                    (input1->m[3][2] * input2->m[2][1]) +
                    (input1->m[3][3] * input2->m[3][1]);
    
  output->m[3][2] = (input1->m[3][0] * input2->m[0][2]) +
                    (input1->m[3][1] * input2->m[1][2]) +
                    (input1->m[3][2] * input2->m[2][2]) +
                    (input1->m[3][3] * input2->m[3][2]);
    
  output->m[3][3] = (input1->m[3][0] * input2->m[0][3]) +
                    (input1->m[3][1] * input2->m[1][3]) +
                    (input1->m[3][2] * input2->m[2][3]) +
                    (input1->m[3][3] * input2->m[3][3]);
}

//♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥

void viewLeftHand(Vec3* target, Vec3* position, Vec3* up,
                  Matrix4* output)
{
// [ column1.x   column2.x   column3.x   0.0f ]
// [ column1.y   column2.y   column3.y   0.0f ]
// [ column1.z   column2.z   column3.z   0.0f ]
// [    -A          -B          -C       1.0f ]

    Vec3 column3 = (*target)-(*position);
    column3.normalize();

    Vec3 column1 = cross(*up,column3);
    column1.normalize();

    Vec3 column2 = cross(column3,column1);

    float a = column1.dot(*position);
    float b = column2.dot(*position);
    float c = column3.dot(*position);

    output->m[0][0] = column1.x;
    output->m[0][1] = column2.x;
    output->m[0][2] = column3.x;
    output->m[0][3] = .0f;
    output->m[1][0] = column1.y;
    output->m[1][1] = column2.y;
    output->m[1][2] = column3.y;
    output->m[1][3] = .0f;
    output->m[2][0] = column1.z;
    output->m[2][1] = column2.z;
    output->m[2][2] = column3.z;
    output->m[2][3] = .0f;
    output->m[3][0] = -a;
    output->m[3][1] = -b;
    output->m[3][2] = -c;
    output->m[3][3] = 1.f;

    return;
}

void viewRightHand(Vec3* target, Vec3* position, Vec3* up, Matrix4* output)
{
// [ column1.x   column2.x   column3.x   0.0f ]
// [ column1.y   column2.y   column3.y   0.0f ]
// [ column1.z   column2.z   column3.z   0.0f ]
// [     A           B           C       1.0f ]

    Vec3 column3 = (*position)-(*target);
    column3.normalize();
    
    Vec3 column1;
    column1 = cross(*up,column3);
    column1.normalize();
    
    Vec3 column2 = cross(column3,column1);

    float a = column1.dot(*position);
    float b = column2.dot(*position);
    float c = column3.dot(*position);

    output->m[0][0] = column1.x;
    output->m[0][1] = column2.x;
    output->m[0][2] = column3.x;
    output->m[0][3] = .0f;
    output->m[1][0] = column1.y;
    output->m[1][1] = column2.y;
    output->m[1][2] = column3.y;
    output->m[1][3] = .0f;
    output->m[2][0] = column1.z;
    output->m[2][1] = column2.z;
    output->m[2][2] = column3.z;
    output->m[2][3] = .0f;
    output->m[3][0] = a;
    output->m[3][1] = b;
    output->m[3][2] = c;
    output->m[3][3] = 1.f;

    return;
}

void PerspectiveLeftHand(float fov, float ar, float n, float f, Matrix4* output)
{
//  [   A   0   0   0   ]
//  [   0   B   0   0   ]
//  [   0   0   C   D   ]
//  [   0   0   E   0   ]

    float b = 1.f / (float)(tan(fov * .5f));
    float a = b/ar;

    float tmp = f - n;

    float c = -(f + n) / tmp;
    float d = 1.f;
    float e = (2 * f * n) / tmp;

    output->m[0][0] = a;
    output->m[0][1] = .0f;
    output->m[0][2] = .0f;
    output->m[0][3] = .0f;
    output->m[1][0] = .0f;
    output->m[1][1] = b;
    output->m[1][2] = .0f;
    output->m[1][3] = .0f;
    output->m[2][0] = .0f;
    output->m[2][1] = .0f;
    output->m[2][2] = c;
    output->m[2][3] = d;
    output->m[3][0] = .0f;
    output->m[3][1] = .0f;
    output->m[3][2] = e;
    output->m[3][3] = .0f;

    return;
}

void PerspectiveRightHand(float fX, float fY, float n, float f, Matrix4* out)
{
//  [   A   0   0   0   ]
//  [   0   B   0   0   ]
//  [   0   0   C   D   ]
//  [   0   0   E   0   ]

    float a = atan(fX/2);
    float b = atan(fY/2);
    float tmp = f - n;
    float c = -((f+n)/tmp);
    float d = -((2*n*f)/tmp);
    float e = -1;
    

    out->m[0][0] = a;
    out->m[0][1] = .0f;
    out->m[0][2] = .0f;
    out->m[0][3] = .0f;
    out->m[1][0] = .0f;
    out->m[1][1] = b;
    out->m[1][2] = .0f;
    out->m[1][3] = .0f;
    out->m[2][0] = .0f;
    out->m[2][1] = .0f;
    out->m[2][2] = c;
    out->m[2][3] = d;
    out->m[3][0] = .0f;
    out->m[3][1] = .0f;
    out->m[3][2] = e;
    out->m[3][3] = .0f;

    return;
}

void OrthographicRightHand(float w, float h, float n, float f, Matrix4* out)
{
    //  [   A   0   0   0   ]
    //  [   0   B   0   0   ]
    //  [   0   0   C   D   ]
    //  [   0   0   0   E   ]
    
    float a = 1/w;
    float b = 1/h;
    float tmp = f - n;
    float c = -(2/tmp);
    float d = -((f+n)/tmp);
    float e = 1;
    
    
    out->m[0][0] = a;
    out->m[0][1] = .0f;
    out->m[0][2] = .0f;
    out->m[0][3] = .0f;
    out->m[1][0] = .0f;
    out->m[1][1] = b;
    out->m[1][2] = .0f;
    out->m[1][3] = .0f;
    out->m[2][0] = .0f;
    out->m[2][1] = .0f;
    out->m[2][2] = c;
    out->m[2][3] = d;
    out->m[3][0] = .0f;
    out->m[3][1] = .0f;
    out->m[3][2] = .0f;
    out->m[3][3] = e;
    
    return;

}

void Translation(Vec3 *source, Matrix4* output)
{
    output->m[0][0] = 1.0f;
    output->m[0][1] = .0f;
    output->m[0][2] = .0f;
    output->m[0][3] = source->x;
    output->m[1][0] = .0f;
    output->m[1][1] = 1.f;
    output->m[1][2] = .0f;
    output->m[1][3] = source->y;
    output->m[2][0] = .0f;
    output->m[2][1] = .0f;
    output->m[2][2] = 1.0f;
    output->m[2][3] = source->z;
    output->m[3][0] = .0f;
    output->m[3][1] = .0f;
    output->m[3][2] = .0f;
    output->m[3][3] = 1.0f;

    return;
}

void Scale(Vec3 *source, Matrix4* output)
{
    output->m[0][0] = source->x;
    output->m[0][1] = .0f;
    output->m[0][2] = .0f;
    output->m[0][3] = .0f;
    output->m[1][0] = .0f;
    output->m[1][1] = source->y;
    output->m[1][2] = .0f;
    output->m[1][3] = .0f;
    output->m[2][0] = .0f;
    output->m[2][1] = .0f;
    output->m[2][2] = source->z;
    output->m[2][3] = .0f;
    output->m[3][0] = .0f;
    output->m[3][1] = .0f;
    output->m[3][2] = .0f;
    output->m[3][3] = 1.0f;
    
    return;
}

void YawPitchRollRotation(float yaw, float pitch, float roll, Matrix4* output)
{
    float quaternion[4];

    float halfroll = roll*.5f;
    float halfyaw = yaw*.5f;
    float halfpitch = pitch*.5f;

    float sinyaw = sin(halfyaw);
    float cosyaw = cos(halfyaw);
    float sinpitch = sin(halfpitch);
    float cospitch = cos(halfpitch);
    float sinroll = sin(halfroll);
    float cosroll = cos(halfroll);

    quaternion[0] = (cosyaw*sinpitch*cosroll)+(sinyaw*cospitch*sinroll),
    quaternion[1] = (sinyaw*cospitch*cosroll)-(cosyaw*sinpitch*sinroll),
    quaternion[2] = (cosyaw*cospitch*sinroll)-(sinyaw*sinpitch*cosroll),
    quaternion[3] = (cosyaw*cospitch*cosroll)+(sinyaw*sinpitch*sinroll);

    float xx = quaternion[0] * quaternion[0];
    float yy = quaternion[1] * quaternion[1];
    float zz = quaternion[2] * quaternion[2];
    float xy = quaternion[0] * quaternion[1];
    float zw = quaternion[2] * quaternion[3];
    float zx = quaternion[2] * quaternion[0];
    float yw = quaternion[1] * quaternion[3];
    float yz = quaternion[1] * quaternion[2];
    float xw = quaternion[0] * quaternion[3];

    output->m[0][0] = 1.f - (2.f * (yy + zz));
    output->m[0][1] = 2.f * (xy + zw);
    output->m[0][2] = 2.f * (zx - yw);
    output->m[0][3] = .0f;
    output->m[1][0] = 2.f * (xy - zw);
    output->m[1][1] = 1.f - (2.f * (zz + xx));
    output->m[1][2] = 0.f * (yz + xw);
    output->m[1][3] = 0.f;
    output->m[2][0]= 2.f * (zx + yw);
    output->m[2][1] = 2.f * (yz - xw);
    output->m[2][2] = 1.f - (2.f * (yy + xx));
    output->m[2][3] = .0f;
    output->m[3][0] = .0f;
    output->m[3][1] = .0f;
    output->m[3][2] = .0f;
    output->m[3][3] = 1.0f;

    return;
}
