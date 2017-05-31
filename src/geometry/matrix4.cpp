#include "matrix4.hpp"
#define CHAR_ARRAY_SIZE_PER_FLOAT 10

Matrix4::Matrix4()
{ }

Matrix4::Matrix4(const float* v)
{
#ifdef _LOW_LEVEL_CHECKS_
    if(v!=NULL)
    {
        //checking if the values are not NaN or Infinity is too expensive,
        //so cross your fingers :^)
#endif
        Matrix4::m00 = v[0];
        Matrix4::m01 = v[1];
        Matrix4::m02 = v[2];
        Matrix4::m03 = v[3];
        Matrix4::m10 = v[4];
        Matrix4::m11 = v[5];
        Matrix4::m12 = v[6];
        Matrix4::m13 = v[7];
        Matrix4::m20 = v[8];
        Matrix4::m21 = v[9];
        Matrix4::m22 = v[10];
        Matrix4::m23 = v[11];
        Matrix4::m30 = v[12];
        Matrix4::m31 = v[13];
        Matrix4::m32 = v[14];
        Matrix4::m33 = v[15];
#ifdef _LOW_LEVEL_CHECKS_
    }
    else
        Console.warning("Initializing a Matrix4 with a NULL pointer to array.\
                Matrix4 was left uninitialized");
#endif
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
    snprintf(val1,sizeof(val1),"%f",Matrix4::m00);
    snprintf(val2,sizeof(val2),"%f",Matrix4::m01);
    snprintf(val3,sizeof(val3),"%f",Matrix4::m02);
    snprintf(val4,sizeof(val4),"%f",Matrix4::m03);
    snprintf(val5,sizeof(val5),"%f",Matrix4::m10);
    snprintf(val6,sizeof(val6),"%f",Matrix4::m11);
    snprintf(val7,sizeof(val7),"%f",Matrix4::m12);
    snprintf(val8,sizeof(val8),"%f",Matrix4::m13);
    snprintf(val9,sizeof(val9),"%f",Matrix4::m20);
    snprintf(val10,sizeof(val10),"%f",Matrix4::m21);
    snprintf(val11,sizeof(val11),"%f",Matrix4::m22);
    snprintf(val12,sizeof(val12),"%f",Matrix4::m23);
    snprintf(val13,sizeof(val13),"%f",Matrix4::m30);
    snprintf(val14,sizeof(val14),"%f",Matrix4::m31);
    snprintf(val15,sizeof(val15),"%f",Matrix4::m32);
    snprintf(val16,sizeof(val16),"%f",Matrix4::m33);
    
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
    res[0] = Matrix4::m00;
    res[1] = Matrix4::m01;
    res[2] = Matrix4::m02;
    res[3] = Matrix4::m03;
    res[4] = Matrix4::m10;
    res[5] = Matrix4::m11;
    res[6] = Matrix4::m12;
    res[7] = Matrix4::m13;
    res[8] = Matrix4::m20;
    res[9] = Matrix4::m21;
    res[10] = Matrix4::m22;
    res[11] = Matrix4::m23;
    res[12] = Matrix4::m30;
    res[13] = Matrix4::m31;
    res[14] = Matrix4::m32;
    res[15] = Matrix4::m33;
    return res;
}

void Matrix4::setZero()
{
    Matrix4::m00 = 0.0f;
    Matrix4::m01 = 0.0f;
    Matrix4::m02 = 0.0f;
    Matrix4::m03 = 0.0f;
    Matrix4::m10 = 0.0f;
    Matrix4::m11 = 0.0f;
    Matrix4::m12 = 0.0f;
    Matrix4::m13 = 0.0f;
    Matrix4::m20 = 0.0f;
    Matrix4::m21 = 0.0f;
    Matrix4::m22 = 0.0f;
    Matrix4::m23 = 0.0f;
    Matrix4::m30 = 0.0f;
    Matrix4::m31 = 0.0f;
    Matrix4::m32 = 0.0f;
    Matrix4::m33 = 0.0f;
}

void Matrix4::setIdentity()
{
    Matrix4::m00 = 1.0f;
    Matrix4::m01 = 0.0f;
    Matrix4::m02 = 0.0f;
    Matrix4::m03 = 0.0f;
    Matrix4::m10 = 0.0f;
    Matrix4::m11 = 1.0f;
    Matrix4::m12 = 0.0f;
    Matrix4::m13 = 0.0f;
    Matrix4::m20 = 0.0f;
    Matrix4::m21 = 0.0f;
    Matrix4::m22 = 1.0f;
    Matrix4::m23 = 0.0f;
    Matrix4::m30 = 0.0f;
    Matrix4::m31 = 0.0f;
    Matrix4::m32 = 0.0f;
    Matrix4::m33 = 1.0f;
}

void Matrix4::setTranslation(Vec3 direction)
{
    Matrix4::m00 = 1.0f;
    Matrix4::m01 = 0.0f;
    Matrix4::m02 = 0.0f;
    Matrix4::m03 = direction.x;
    Matrix4::m10 = 0.0f;
    Matrix4::m11 = 1.0f;
    Matrix4::m12 = 0.0f;
    Matrix4::m13 = direction.y;
    Matrix4::m20 = 0.0f;
    Matrix4::m21 = 0.0f;
    Matrix4::m22 = 1.0f;
    Matrix4::m23 = direction.z;
    Matrix4::m30 = 0.0f;
    Matrix4::m31 = 0.0f;
    Matrix4::m32 = 0.0f;
    Matrix4::m33 = 1.0f;
}

void Matrix4::setScale(float value)
{
    Matrix4::m00 = value;
    Matrix4::m01 = 0.0f;
    Matrix4::m02 = 0.0f;
    Matrix4::m03 = 0.0f;
    Matrix4::m10 = 0.0f;
    Matrix4::m11 = value;
    Matrix4::m12 = 0.0f;
    Matrix4::m13 = 0.0f;
    Matrix4::m20 = 0.0f;
    Matrix4::m21 = 0.0f;
    Matrix4::m22 = value;
    Matrix4::m23 = 0.0f;
    Matrix4::m30 = 0.0f;
    Matrix4::m31 = 0.0f;
    Matrix4::m32 = 0.0f;
    Matrix4::m33 = 1.0f;
}

void Matrix4::setScale(Vec3 value)
{
    Matrix4::m00 = value.x;
    Matrix4::m01 = 0.0f;
    Matrix4::m02 = 0.0f;
    Matrix4::m03 = 0.0f;
    Matrix4::m10 = 0.0f;
    Matrix4::m11 = value.y;
    Matrix4::m12 = 0.0f;
    Matrix4::m13 = 0.0f;
    Matrix4::m20 = 0.0f;
    Matrix4::m21 = 0.0f;
    Matrix4::m22 = value.z;
    Matrix4::m23 = 0.0f;
    Matrix4::m30 = 0.0f;
    Matrix4::m31 = 0.0f;
    Matrix4::m32 = 0.0f;
    Matrix4::m33 = 1.0f;
}

void Matrix4::setRotateX(float value)
{
    float sint = sinf(value);
    float cost = cosf(value);
    Matrix4::m00 = 1.0f;
    Matrix4::m01 = 0.0f;
    Matrix4::m02 = 0.0f;
    Matrix4::m03 = 0.0f;
    Matrix4::m10 = 0.0f;
    Matrix4::m11 = cost;
    Matrix4::m12 = -sint;
    Matrix4::m13 = 0.0f;
    Matrix4::m20 = 0.0f;
    Matrix4::m21 = sint;
    Matrix4::m22 = cost;
    Matrix4::m23 = 0.0f;
    Matrix4::m30 = 0.0f;
    Matrix4::m31 = 0.0f;
    Matrix4::m32 = 0.0f;
    Matrix4::m33 = 1.0f;
}

void Matrix4::setRotateY(float value)
{
    float sint = sinf(value);
    float cost = cosf(value);
    Matrix4::m00 = cost;
    Matrix4::m01 = 0.0f;
    Matrix4::m02 = sint;
    Matrix4::m03 = 0.0f;
    Matrix4::m10 = 0.0f;
    Matrix4::m11 = 1.0f;
    Matrix4::m12 = 0.0f;
    Matrix4::m13 = 0.0f;
    Matrix4::m20 = -sint;
    Matrix4::m21 = 0.0f;
    Matrix4::m22 = cost;
    Matrix4::m23 = 0.0f;
    Matrix4::m30 = 0.0f;
    Matrix4::m31 = 0.0f;
    Matrix4::m32 = 0.0f;
    Matrix4::m33 = 1.0f;
}

void Matrix4::setRotateZ(float value)
{
    float sint = sinf(value);
    float cost = cosf(value);
    Matrix4::m00 = cost;
    Matrix4::m01 = -sint;
    Matrix4::m02 = 0.0f;
    Matrix4::m03 = 0.0f;
    Matrix4::m10 = sint;
    Matrix4::m11 = cost;
    Matrix4::m12 = 0.0f;
    Matrix4::m13 = 0.0f;
    Matrix4::m20 = 0.0f;
    Matrix4::m21 = 0.0f;
    Matrix4::m22 = 1.0f;
    Matrix4::m23 = 0.0f;
    Matrix4::m30 = 0.0f;
    Matrix4::m31 = 0.0f;
    Matrix4::m32 = 0.0f;
    Matrix4::m33 = 1.0f;
}

void Matrix4::setLookAtLH(const Point3 pos, const Point3 target, const Vec3 up)
{
    Vec3 newup = up;
#ifdef _LOW_LEVEL_CHECKS_
    if(!(up.isNormalized()))
    {
        Console.warning("Up camera vector is not normalized. Normalizing now");
        newup.normalize();
    }
#endif
    Vec3 dir = target - pos;
    dir.normalize();
    Vec3 left = cross(newup,dir);
    left.normalize();
    newup = cross(dir,left);
    
    Matrix4::m00 = left.x;
    Matrix4::m01 = newup.x;
    Matrix4::m02 = dir.x;
    Matrix4::m03 = pos.x;
    Matrix4::m10 = left.y;
    Matrix4::m11 = newup.y;
    Matrix4::m12 = dir.y;
    Matrix4::m13 = pos.y;
    Matrix4::m20 = left.z;
    Matrix4::m21 = newup.z;
    Matrix4::m22 = dir.z;
    Matrix4::m23 = pos.z;
    Matrix4::m30 = 0.0f;
    Matrix4::m31 = 0.0f;
    Matrix4::m32 = 0.0f;
    Matrix4::m33 = 1.0f;
    Matrix4::inverse(this); //hardcoding this matrix is a nightmare
}

void Matrix4::transpose(Matrix4* output)const
{
    output->m00 = Matrix4::m00;
    output->m01 = Matrix4::m10;
    output->m02 = Matrix4::m20;
    output->m03 = Matrix4::m30;
    output->m10 = Matrix4::m01;
    output->m11 = Matrix4::m11;
    output->m12 = Matrix4::m21;
    output->m13 = Matrix4::m31;
    output->m20 = Matrix4::m02;
    output->m21 = Matrix4::m12;
    output->m22 = Matrix4::m22;
    output->m23 = Matrix4::m32;
    output->m30 = Matrix4::m03;
    output->m31 = Matrix4::m13;
    output->m32 = Matrix4::m23;
    output->m33 = Matrix4::m33;
}

bool Matrix4::inverse(Matrix4 *output)const
{
    float inv[16], det;
    
    inv[0] =    Matrix4::m11 * Matrix4::m22 * Matrix4::m33 -
    Matrix4::m11 * Matrix4::m23 * Matrix4::m32 -
    Matrix4::m21 * Matrix4::m12 * Matrix4::m33 +
    Matrix4::m21 * Matrix4::m13 * Matrix4::m32 +
    Matrix4::m31 * Matrix4::m12 * Matrix4::m23 -
    Matrix4::m31 * Matrix4::m13 * Matrix4::m22;
    
    inv[4] =  - Matrix4::m10 * Matrix4::m22 * Matrix4::m33 +
    Matrix4::m10 * Matrix4::m23 * Matrix4::m32 +
    Matrix4::m20 * Matrix4::m12 * Matrix4::m33 -
    Matrix4::m20 * Matrix4::m13 * Matrix4::m32 -
    Matrix4::m30 * Matrix4::m12 * Matrix4::m23 +
    Matrix4::m30 * Matrix4::m13 * Matrix4::m22;
    
    inv[8] =    Matrix4::m10 * Matrix4::m21 * Matrix4::m33 -
    Matrix4::m10 * Matrix4::m23 * Matrix4::m31 -
    Matrix4::m20 * Matrix4::m11 * Matrix4::m33 +
    Matrix4::m20 * Matrix4::m13 * Matrix4::m31 +
    Matrix4::m30 * Matrix4::m11 * Matrix4::m23 -
    Matrix4::m30 * Matrix4::m13 * Matrix4::m21;
    
    inv[12] = - Matrix4::m10 * Matrix4::m21 * Matrix4::m32 +
    Matrix4::m10 * Matrix4::m22 * Matrix4::m31 +
    Matrix4::m20 * Matrix4::m11 * Matrix4::m32 -
    Matrix4::m20 * Matrix4::m12 * Matrix4::m31 -
    Matrix4::m30 * Matrix4::m11 * Matrix4::m22 +
    Matrix4::m30 * Matrix4::m12 * Matrix4::m21;
    
    inv[1] =  - Matrix4::m01 * Matrix4::m22 * Matrix4::m33 +
    Matrix4::m01 * Matrix4::m23 * Matrix4::m32 +
    Matrix4::m21 * Matrix4::m02 * Matrix4::m33 -
    Matrix4::m21 * Matrix4::m03 * Matrix4::m32 -
    Matrix4::m31 * Matrix4::m02 * Matrix4::m23 +
    Matrix4::m31 * Matrix4::m03 * Matrix4::m22;
    
    inv[5] =    Matrix4::m00 * Matrix4::m22 * Matrix4::m33 -
    Matrix4::m00 * Matrix4::m23 * Matrix4::m32 -
    Matrix4::m20 * Matrix4::m02 * Matrix4::m33 +
    Matrix4::m20 * Matrix4::m03 * Matrix4::m32 +
    Matrix4::m30 * Matrix4::m02 * Matrix4::m23 -
    Matrix4::m30 * Matrix4::m03 * Matrix4::m22;
    
    inv[9] =  - Matrix4::m00 * Matrix4::m21 * Matrix4::m33 +
    Matrix4::m00 * Matrix4::m23 * Matrix4::m31 +
    Matrix4::m20 * Matrix4::m01 * Matrix4::m33 -
    Matrix4::m20 * Matrix4::m03 * Matrix4::m31 -
    Matrix4::m30 * Matrix4::m01 * Matrix4::m23 +
    Matrix4::m30 * Matrix4::m03 * Matrix4::m21;
    
    inv[13] =   Matrix4::m00 * Matrix4::m21 * Matrix4::m32 -
    Matrix4::m00 * Matrix4::m22 * Matrix4::m31 -
    Matrix4::m20 * Matrix4::m01 * Matrix4::m32 +
    Matrix4::m20 * Matrix4::m02 * Matrix4::m31 +
    Matrix4::m30 * Matrix4::m01 * Matrix4::m22 -
    Matrix4::m30 * Matrix4::m02 * Matrix4::m21;
    
    inv[2] =    Matrix4::m01 * Matrix4::m12 * Matrix4::m33 -
    Matrix4::m01 * Matrix4::m13 * Matrix4::m32 -
    Matrix4::m11 * Matrix4::m02 * Matrix4::m33 +
    Matrix4::m11 * Matrix4::m03 * Matrix4::m32 +
    Matrix4::m31 * Matrix4::m02 * Matrix4::m13 -
    Matrix4::m31 * Matrix4::m03 * Matrix4::m12;
    
    inv[6] =  - Matrix4::m00 * Matrix4::m12 * Matrix4::m33 +
    Matrix4::m00 * Matrix4::m13 * Matrix4::m32 +
    Matrix4::m10 * Matrix4::m02 * Matrix4::m33 -
    Matrix4::m10 * Matrix4::m03 * Matrix4::m32 -
    Matrix4::m30 * Matrix4::m02 * Matrix4::m13 +
    Matrix4::m30 * Matrix4::m03 * Matrix4::m12;
    
    inv[10] =   Matrix4::m00 * Matrix4::m11 * Matrix4::m33 -
    Matrix4::m00 * Matrix4::m13 * Matrix4::m31 -
    Matrix4::m10 * Matrix4::m01 * Matrix4::m33 +
    Matrix4::m10 * Matrix4::m03 * Matrix4::m31 +
    Matrix4::m30 * Matrix4::m01 * Matrix4::m13 -
    Matrix4::m30 * Matrix4::m03 * Matrix4::m11;
    
    inv[14] = - Matrix4::m00 * Matrix4::m11 * Matrix4::m32 +
    Matrix4::m00 * Matrix4::m12 * Matrix4::m31 +
    Matrix4::m10 * Matrix4::m01 * Matrix4::m32 -
    Matrix4::m10 * Matrix4::m02 * Matrix4::m31 -
    Matrix4::m30 * Matrix4::m01 * Matrix4::m12 +
    Matrix4::m30 * Matrix4::m02 * Matrix4::m11;
    
    inv[3] =  - Matrix4::m01 * Matrix4::m12 * Matrix4::m23 +
    Matrix4::m01 * Matrix4::m13 * Matrix4::m22 +
    Matrix4::m11 * Matrix4::m02 * Matrix4::m23 -
    Matrix4::m11 * Matrix4::m03 * Matrix4::m22 -
    Matrix4::m21 * Matrix4::m02 * Matrix4::m13 +
    Matrix4::m21 * Matrix4::m03 * Matrix4::m12;
    
    inv[7] =    Matrix4::m00 * Matrix4::m12 * Matrix4::m23 -
    Matrix4::m00 * Matrix4::m13 * Matrix4::m22 -
    Matrix4::m10 * Matrix4::m02 * Matrix4::m23 +
    Matrix4::m10 * Matrix4::m03 * Matrix4::m22 +
    Matrix4::m20 * Matrix4::m02 * Matrix4::m13 -
    Matrix4::m20 * Matrix4::m03 * Matrix4::m12;
    
    inv[11] = - Matrix4::m00 * Matrix4::m11 * Matrix4::m23 +
    Matrix4::m00 * Matrix4::m13 * Matrix4::m21 +
    Matrix4::m10 * Matrix4::m01 * Matrix4::m23 -
    Matrix4::m10 * Matrix4::m03 * Matrix4::m21 -
    Matrix4::m20 * Matrix4::m01 * Matrix4::m13 +
    Matrix4::m20 * Matrix4::m03 * Matrix4::m11;
    
    inv[15] =   Matrix4::m00 * Matrix4::m11 * Matrix4::m22 -
    Matrix4::m00 * Matrix4::m12 * Matrix4::m21 -
    Matrix4::m10 * Matrix4::m01 * Matrix4::m22 +
    Matrix4::m10 * Matrix4::m02 * Matrix4::m21 +
    Matrix4::m20 * Matrix4::m01 * Matrix4::m12 -
    Matrix4::m20 * Matrix4::m02 * Matrix4::m11;
    
    det = Matrix4::m00 * inv[0] + Matrix4::m01 * inv[4]
    + Matrix4::m02 * inv[8] + Matrix4::m03 * inv[12];
    
    if (flt_equal(det,0.0f))
        return false;
    
    det = 1.0f / det;
    
    output->m00 = inv[0]  * det;
    output->m01 = inv[1]  * det;
    output->m02 = inv[2]  * det;
    output->m03 = inv[3]  * det;
    output->m10 = inv[4]  * det;
    output->m11 = inv[5]  * det;
    output->m12 = inv[6]  * det;
    output->m13 = inv[7]  * det;
    output->m20 = inv[8]  * det;
    output->m21 = inv[9]  * det;
    output->m22 = inv[10] * det;
    output->m23 = inv[11] * det;
    output->m30 = inv[12] * det;
    output->m31 = inv[13] * det;
    output->m32 = inv[14] * det;
    output->m33 = inv[15] * det;
    
    return true;
}

//♥ ♥ ♥ Operators ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥

Matrix4 Matrix4::operator+(const Matrix4& mat)const
{
    float val[16];
    val[0] = Matrix4::m00 + mat.m00;
    val[1] = Matrix4::m01 + mat.m01;
    val[2] = Matrix4::m02 + mat.m02;
    val[3] = Matrix4::m03 + mat.m03;
    val[4] = Matrix4::m10 + mat.m10;
    val[5] = Matrix4::m11 + mat.m11;
    val[6] = Matrix4::m12 + mat.m12;
    val[7] = Matrix4::m13 + mat.m13;
    val[8] = Matrix4::m20 + mat.m20;
    val[9] = Matrix4::m21 + mat.m21;
    val[10] = Matrix4::m22 + mat.m22;
    val[11] = Matrix4::m23 + mat.m23;
    val[12] = Matrix4::m30 + mat.m30;
    val[13] = Matrix4::m31 + mat.m31;
    val[14] = Matrix4::m32 + mat.m32;
    val[15] = Matrix4::m33 + mat.m33;
    
    return Matrix4(val);
}

Matrix4 Matrix4::operator-(const Matrix4& mat)const
{    float val[16];
    val[0] = Matrix4::m00 - mat.m00;
    val[1] = Matrix4::m01 - mat.m01;
    val[2] = Matrix4::m02 - mat.m02;
    val[3] = Matrix4::m03 - mat.m03;
    val[4] = Matrix4::m10 - mat.m10;
    val[5] = Matrix4::m11 - mat.m11;
    val[6] = Matrix4::m12 - mat.m12;
    val[7] = Matrix4::m13 - mat.m13;
    val[8] = Matrix4::m20 - mat.m20;
    val[9] = Matrix4::m21 - mat.m21;
    val[10] = Matrix4::m22 - mat.m22;
    val[11] = Matrix4::m23 - mat.m23;
    val[12] = Matrix4::m30 - mat.m30;
    val[13] = Matrix4::m31 - mat.m31;
    val[14] = Matrix4::m32 - mat.m32;
    val[15] = Matrix4::m33 - mat.m33;
    
    return Matrix4(val);
}

void Matrix4::operator+=(const Matrix4& mat)
{
    Matrix4::m00 += mat.m00;
    Matrix4::m01 += mat.m01;
    Matrix4::m02 += mat.m02;
    Matrix4::m03 += mat.m03;
    Matrix4::m10 += mat.m10;
    Matrix4::m11 += mat.m11;
    Matrix4::m12 += mat.m12;
    Matrix4::m13 += mat.m13;
    Matrix4::m20 += mat.m20;
    Matrix4::m21 += mat.m21;
    Matrix4::m22 += mat.m22;
    Matrix4::m23 += mat.m23;
    Matrix4::m30 += mat.m30;
    Matrix4::m31 += mat.m31;
    Matrix4::m32 += mat.m32;
    Matrix4::m33 += mat.m33;
}

void Matrix4::operator-=(const Matrix4& mat)
{
    Matrix4::m00 -= mat.m00;
    Matrix4::m01 -= mat.m01;
    Matrix4::m02 -= mat.m02;
    Matrix4::m03 -= mat.m03;
    Matrix4::m10 -= mat.m10;
    Matrix4::m11 -= mat.m11;
    Matrix4::m12 -= mat.m12;
    Matrix4::m13 -= mat.m13;
    Matrix4::m20 -= mat.m20;
    Matrix4::m21 -= mat.m21;
    Matrix4::m22 -= mat.m22;
    Matrix4::m23 -= mat.m23;
    Matrix4::m30 -= mat.m30;
    Matrix4::m31 -= mat.m31;
    Matrix4::m32 -= mat.m32;
    Matrix4::m33 -= mat.m33;
}

Matrix4 Matrix4::operator*(const Matrix4& mat)const
{
    float val[16];
    val[0] = (Matrix4::m00 * mat.m00) +
    (Matrix4::m01 * mat.m10) +
    (Matrix4::m02 * mat.m20) +
    (Matrix4::m03 * mat.m30);
    
    val[1] = (Matrix4::m00 * mat.m01) +
    (Matrix4::m01 * mat.m11) +
    (Matrix4::m02 * mat.m21) +
    (Matrix4::m03 * mat.m31);
    
    val[2] = (Matrix4::m00 * mat.m02) +
    (Matrix4::m01 * mat.m12) +
    (Matrix4::m02 * mat.m22) +
    (Matrix4::m03 * mat.m32);
    
    val[3] = (Matrix4::m00 * mat.m03) +
    (Matrix4::m01 * mat.m13) +
    (Matrix4::m02 * mat.m23) +
    (Matrix4::m03 * mat.m33);
    
    val[4] = (Matrix4::m10 * mat.m00) +
    (Matrix4::m11 * mat.m10) +
    (Matrix4::m12 * mat.m20) +
    (Matrix4::m13 * mat.m30);
    
    val[5] = (Matrix4::m10 * mat.m01) +
    (Matrix4::m11 * mat.m11) +
    (Matrix4::m12 * mat.m21) +
    (Matrix4::m13 * mat.m31);
    
    val[6] = (Matrix4::m10 * mat.m02) +
    (Matrix4::m11 * mat.m12) +
    (Matrix4::m12 * mat.m22) +
    (Matrix4::m13 * mat.m32);
    
    val[7] = (Matrix4::m10 * mat.m03) +
    (Matrix4::m11 * mat.m13) +
    (Matrix4::m12 * mat.m23) +
    (Matrix4::m13 * mat.m33);
    
    val[8] = (Matrix4::m20 * mat.m00) +
    (Matrix4::m21 * mat.m10) +
    (Matrix4::m22 * mat.m20) +
    (Matrix4::m23 * mat.m30);
    
    val[9] = (Matrix4::m20 * mat.m01) +
    (Matrix4::m21 * mat.m11) +
    (Matrix4::m22 * mat.m21) +
    (Matrix4::m23 * mat.m31);
    
    val[10] = (Matrix4::m20 * mat.m02) +
    (Matrix4::m21 * mat.m12) +
    (Matrix4::m22 * mat.m22) +
    (Matrix4::m23 * mat.m32);
    
    val[11] = (Matrix4::m20 * mat.m03) +
    (Matrix4::m21 * mat.m13) +
    (Matrix4::m22 * mat.m23) +
    (Matrix4::m23 * mat.m33);
    
    val[12] = (Matrix4::m30 * mat.m00) +
    (Matrix4::m31 * mat.m10) +
    (Matrix4::m32 * mat.m20) +
    (Matrix4::m33 * mat.m30);
    
    val[13] = (Matrix4::m30 * mat.m01) +
    (Matrix4::m31 * mat.m11) +
    (Matrix4::m32 * mat.m21) +
    (Matrix4::m33 * mat.m31);
    
    val[14] = (Matrix4::m30 * mat.m02) +
    (Matrix4::m31 * mat.m12) +
    (Matrix4::m32 * mat.m22) +
    (Matrix4::m33 * mat.m32);
    
    val[15] = (Matrix4::m30 * mat.m03) +
    (Matrix4::m31 * mat.m13) +
    (Matrix4::m32 * mat.m23) +
    (Matrix4::m33 * mat.m33);
    
    return Matrix4(val);
}

void Matrix4::operator*=(const Matrix4& mat)
{
    float val[16];
    val[0] = (Matrix4::m00 * mat.m00) +
    (Matrix4::m01 * mat.m10) +
    (Matrix4::m02 * mat.m20) +
    (Matrix4::m03 * mat.m30);
    
    val[1] = (Matrix4::m00 * mat.m01) +
    (Matrix4::m01 * mat.m11) +
    (Matrix4::m02 * mat.m21) +
    (Matrix4::m03 * mat.m31);
    
    val[2] = (Matrix4::m00 * mat.m02) +
    (Matrix4::m01 * mat.m12) +
    (Matrix4::m02 * mat.m22) +
    (Matrix4::m03 * mat.m32);
    
    val[3] = (Matrix4::m00 * mat.m03) +
    (Matrix4::m01 * mat.m13) +
    (Matrix4::m02 * mat.m23) +
    (Matrix4::m03 * mat.m33);
    
    val[4] = (Matrix4::m10 * mat.m00) +
    (Matrix4::m11 * mat.m10) +
    (Matrix4::m12 * mat.m20) +
    (Matrix4::m13 * mat.m30);
    
    val[5] = (Matrix4::m10 * mat.m01) +
    (Matrix4::m11 * mat.m11) +
    (Matrix4::m12 * mat.m21) +
    (Matrix4::m13 * mat.m31);
    
    val[6] = (Matrix4::m10 * mat.m02) +
    (Matrix4::m11 * mat.m12) +
    (Matrix4::m12 * mat.m22) +
    (Matrix4::m13 * mat.m32);
    
    val[7] = (Matrix4::m10 * mat.m03) +
    (Matrix4::m11 * mat.m13) +
    (Matrix4::m12 * mat.m23) +
    (Matrix4::m13 * mat.m33);
    
    val[8] = (Matrix4::m20 * mat.m00) +
    (Matrix4::m21 * mat.m10) +
    (Matrix4::m22 * mat.m20) +
    (Matrix4::m23 * mat.m30);
    
    val[9] = (Matrix4::m20 * mat.m01) +
    (Matrix4::m21 * mat.m11) +
    (Matrix4::m22 * mat.m21) +
    (Matrix4::m23 * mat.m31);
    
    val[10] = (Matrix4::m20 * mat.m02) +
    (Matrix4::m21 * mat.m12) +
    (Matrix4::m22 * mat.m22) +
    (Matrix4::m23 * mat.m32);
    
    val[11] = (Matrix4::m20 * mat.m03) +
    (Matrix4::m21 * mat.m13) +
    (Matrix4::m22 * mat.m23) +
    (Matrix4::m23 * mat.m33);
    
    val[12] = (Matrix4::m30 * mat.m00) +
    (Matrix4::m31 * mat.m10) +
    (Matrix4::m32 * mat.m20) +
    (Matrix4::m33 * mat.m30);
    
    val[13] = (Matrix4::m30 * mat.m01) +
    (Matrix4::m31 * mat.m11) +
    (Matrix4::m32 * mat.m21) +
    (Matrix4::m33 * mat.m31);
    
    val[14] = (Matrix4::m30 * mat.m02) +
    (Matrix4::m31 * mat.m12) +
    (Matrix4::m32 * mat.m22) +
    (Matrix4::m33 * mat.m32);
    
    val[15] = (Matrix4::m30 * mat.m03) +
    (Matrix4::m31 * mat.m13) +
    (Matrix4::m32 * mat.m23) +
    (Matrix4::m33 * mat.m33);
    
    Matrix4::m00 = val[0];
    Matrix4::m01 = val[1];
    Matrix4::m02 = val[2];
    Matrix4::m03 = val[3];
    Matrix4::m10 = val[4];
    Matrix4::m11 = val[5];
    Matrix4::m12 = val[6];
    Matrix4::m13 = val[7];
    Matrix4::m20 = val[8];
    Matrix4::m21 = val[9];
    Matrix4::m22 = val[10];
    Matrix4::m23 = val[11];
    Matrix4::m30 = val[12];
    Matrix4::m31 = val[13];
    Matrix4::m32 = val[14];
    Matrix4::m33 = val[15];
}

Matrix4 Matrix4::operator/(const Matrix4& mat)const
{
    float val[16];
    val[0] = (Matrix4::m00 / mat.m00) +
    (Matrix4::m01 / mat.m10) +
    (Matrix4::m02 / mat.m20) +
    (Matrix4::m03 / mat.m30);
    
    val[1] = (Matrix4::m00 / mat.m01) +
    (Matrix4::m01 / mat.m11) +
    (Matrix4::m02 / mat.m21) +
    (Matrix4::m03 / mat.m31);
    
    val[2] = (Matrix4::m00 / mat.m02) +
    (Matrix4::m01 / mat.m12) +
    (Matrix4::m02 / mat.m22) +
    (Matrix4::m03 / mat.m32);
    
    val[3] = (Matrix4::m00 / mat.m03) +
    (Matrix4::m01 / mat.m13) +
    (Matrix4::m02 / mat.m23) +
    (Matrix4::m03 / mat.m33);
    
    val[4] = (Matrix4::m10 / mat.m00) +
    (Matrix4::m11 / mat.m10) +
    (Matrix4::m12 / mat.m20) +
    (Matrix4::m13 / mat.m30);
    
    val[5] = (Matrix4::m10 / mat.m01) +
    (Matrix4::m11 / mat.m11) +
    (Matrix4::m12 / mat.m21) +
    (Matrix4::m13 / mat.m31);
    
    val[6] = (Matrix4::m10 / mat.m02) +
    (Matrix4::m11 / mat.m12) +
    (Matrix4::m12 / mat.m22) +
    (Matrix4::m13 / mat.m32);
    
    val[7] = (Matrix4::m10 / mat.m03) +
    (Matrix4::m11 / mat.m13) +
    (Matrix4::m12 / mat.m23) +
    (Matrix4::m13 / mat.m33);
    
    val[8] = (Matrix4::m20 / mat.m00) +
    (Matrix4::m21 / mat.m10) +
    (Matrix4::m22 / mat.m20) +
    (Matrix4::m23 / mat.m30);
    
    val[9] = (Matrix4::m20 / mat.m01) +
    (Matrix4::m21 / mat.m11) +
    (Matrix4::m22 / mat.m21) +
    (Matrix4::m23 / mat.m31);
    
    val[10] = (Matrix4::m20 / mat.m02) +
    (Matrix4::m21 / mat.m12) +
    (Matrix4::m22 / mat.m22) +
    (Matrix4::m23 / mat.m32);
    
    val[11] = (Matrix4::m20 / mat.m03) +
    (Matrix4::m21 / mat.m13) +
    (Matrix4::m22 / mat.m23) +
    (Matrix4::m23 / mat.m33);
    
    val[12] = (Matrix4::m30 / mat.m00) +
    (Matrix4::m31 / mat.m10) +
    (Matrix4::m32 / mat.m20) +
    (Matrix4::m33 / mat.m30);
    
    val[13] = (Matrix4::m30 / mat.m01) +
    (Matrix4::m31 / mat.m11) +
    (Matrix4::m32 / mat.m21) +
    (Matrix4::m33 / mat.m31);
    
    val[14] = (Matrix4::m30 / mat.m02) +
    (Matrix4::m31 / mat.m12) +
    (Matrix4::m32 / mat.m22) +
    (Matrix4::m33 / mat.m32);
    
    val[15] = (Matrix4::m30 / mat.m03) +
    (Matrix4::m31 / mat.m13) +
    (Matrix4::m32 / mat.m23) +
    (Matrix4::m33 / mat.m33);
    
    return Matrix4(val);
}

void Matrix4::operator/=(const Matrix4& mat)
{
    float val[16];
    val[0] = (Matrix4::m00 / mat.m00) +
    (Matrix4::m01 / mat.m10) +
    (Matrix4::m02 / mat.m20) +
    (Matrix4::m03 / mat.m30);
    
    val[1] = (Matrix4::m00 / mat.m01) +
    (Matrix4::m01 / mat.m11) +
    (Matrix4::m02 / mat.m21) +
    (Matrix4::m03 / mat.m31);
    
    val[2] = (Matrix4::m00 / mat.m02) +
    (Matrix4::m01 / mat.m12) +
    (Matrix4::m02 / mat.m22) +
    (Matrix4::m03 / mat.m32);
    
    val[3] = (Matrix4::m00 / mat.m03) +
    (Matrix4::m01 / mat.m13) +
    (Matrix4::m02 / mat.m23) +
    (Matrix4::m03 / mat.m33);
    
    val[4] = (Matrix4::m10 / mat.m00) +
    (Matrix4::m11 / mat.m10) +
    (Matrix4::m12 / mat.m20) +
    (Matrix4::m13 / mat.m30);
    
    val[5] = (Matrix4::m10 / mat.m01) +
    (Matrix4::m11 / mat.m11) +
    (Matrix4::m12 / mat.m21) +
    (Matrix4::m13 / mat.m31);
    
    val[6] = (Matrix4::m10 / mat.m02) +
    (Matrix4::m11 / mat.m12) +
    (Matrix4::m12 / mat.m22) +
    (Matrix4::m13 / mat.m32);
    
    val[7] = (Matrix4::m10 / mat.m03) +
    (Matrix4::m11 / mat.m13) +
    (Matrix4::m12 / mat.m23) +
    (Matrix4::m13 / mat.m33);
    
    val[8] = (Matrix4::m20 / mat.m00) +
    (Matrix4::m21 / mat.m10) +
    (Matrix4::m22 / mat.m20) +
    (Matrix4::m23 / mat.m30);
    
    val[9] = (Matrix4::m20 / mat.m01) +
    (Matrix4::m21 / mat.m11) +
    (Matrix4::m22 / mat.m21) +
    (Matrix4::m23 / mat.m31);
    
    val[10] = (Matrix4::m20 / mat.m02) +
    (Matrix4::m21 / mat.m12) +
    (Matrix4::m22 / mat.m22) +
    (Matrix4::m23 / mat.m32);
    
    val[11] = (Matrix4::m20 / mat.m03) +
    (Matrix4::m21 / mat.m13) +
    (Matrix4::m22 / mat.m23) +
    (Matrix4::m23 / mat.m33);
    
    val[12] = (Matrix4::m30 / mat.m00) +
    (Matrix4::m31 / mat.m10) +
    (Matrix4::m32 / mat.m20) +
    (Matrix4::m33 / mat.m30);
    
    val[13] = (Matrix4::m30 / mat.m01) +
    (Matrix4::m31 / mat.m11) +
    (Matrix4::m32 / mat.m21) +
    (Matrix4::m33 / mat.m31);
    
    val[14] = (Matrix4::m30 / mat.m02) +
    (Matrix4::m31 / mat.m12) +
    (Matrix4::m32 / mat.m22) +
    (Matrix4::m33 / mat.m32);
    
    val[15] = (Matrix4::m30 / mat.m03) +
    (Matrix4::m31 / mat.m13) +
    (Matrix4::m32 / mat.m23) +
    (Matrix4::m33 / mat.m33);
    
    Matrix4::m00 = val[0];
    Matrix4::m01 = val[1];
    Matrix4::m02 = val[2];
    Matrix4::m03 = val[3];
    Matrix4::m10 = val[4];
    Matrix4::m11 = val[5];
    Matrix4::m12 = val[6];
    Matrix4::m13 = val[7];
    Matrix4::m20 = val[8];
    Matrix4::m21 = val[9];
    Matrix4::m22 = val[10];
    Matrix4::m23 = val[11];
    Matrix4::m30 = val[12];
    Matrix4::m31 = val[13];
    Matrix4::m32 = val[14];
    Matrix4::m33 = val[15];
}

bool Matrix4::operator==(const Matrix4& mat)const
{
    return flt_equal(Matrix4::m00, mat.m00) &&
    flt_equal(Matrix4::m01, mat.m01) &&
    flt_equal(Matrix4::m02, mat.m02) &&
    flt_equal(Matrix4::m03, mat.m03) &&
    flt_equal(Matrix4::m10, mat.m10) &&
    flt_equal(Matrix4::m11, mat.m11) &&
    flt_equal(Matrix4::m12, mat.m12) &&
    flt_equal(Matrix4::m13, mat.m13) &&
    flt_equal(Matrix4::m20, mat.m20) &&
    flt_equal(Matrix4::m21, mat.m21) &&
    flt_equal(Matrix4::m22, mat.m22) &&
    flt_equal(Matrix4::m23, mat.m23) &&
    flt_equal(Matrix4::m30, mat.m30) &&
    flt_equal(Matrix4::m31, mat.m31) &&
    flt_equal(Matrix4::m32, mat.m32) &&
    flt_equal(Matrix4::m33, mat.m33);
}

bool Matrix4::operator!=(const Matrix4& mat)const
{
    return !(flt_equal(Matrix4::m00, mat.m00) &&
             flt_equal(Matrix4::m01, mat.m01) &&
             flt_equal(Matrix4::m02, mat.m02) &&
             flt_equal(Matrix4::m03, mat.m03) &&
             flt_equal(Matrix4::m10, mat.m10) &&
             flt_equal(Matrix4::m11, mat.m11) &&
             flt_equal(Matrix4::m12, mat.m12) &&
             flt_equal(Matrix4::m13, mat.m13) &&
             flt_equal(Matrix4::m20, mat.m20) &&
             flt_equal(Matrix4::m21, mat.m21) &&
             flt_equal(Matrix4::m22, mat.m22) &&
             flt_equal(Matrix4::m23, mat.m23) &&
             flt_equal(Matrix4::m30, mat.m30) &&
             flt_equal(Matrix4::m31, mat.m31) &&
             flt_equal(Matrix4::m32, mat.m32) &&
             flt_equal(Matrix4::m33, mat.m33));
}

Point3 Matrix4::operator*(const Point3& p)const
{
    float x = Matrix4::m00*p.x+Matrix4::m01*p.y+Matrix4::m02*p.z+Matrix4::m03;
    float y = Matrix4::m10*p.x+Matrix4::m11*p.y+Matrix4::m12*p.z+Matrix4::m13;
    float z = Matrix4::m20*p.x+Matrix4::m21*p.y+Matrix4::m22*p.z+Matrix4::m23;
    float w = Matrix4::m30*p.x+Matrix4::m31*p.y+Matrix4::m32*p.z+Matrix4::m33;
    
    if(w==1.0)
        return Point3(x,y,z);
    else
    {
        w = 1.0f/w;
        x*=w;
        y*=w;
        z*=w;
        return Point3(x,y,z);
    }
}

Vec3 Matrix4::operator*(const Vec3& v)const
{
    return Vec3(Matrix4::m00*v.x+Matrix4::m01*v.y+Matrix4::m02*v.z+Matrix4::m03,
                Matrix4::m10*v.x+Matrix4::m11*v.y+Matrix4::m12*v.z+Matrix4::m13,
                Matrix4::m20*v.x+Matrix4::m21*v.y+Matrix4::m22*v.z+Matrix4::m23
                );
}

Normal Matrix4::operator*(const Normal& n)const
{
    //TODO possible optimization by storing inverse matrix?
    Matrix4 inv;
    Matrix4::inverse(&inv);
    return Normal(inv.m00*n.x+inv.m01*n.y+inv.m02*n.z+inv.m03,
                  inv.m10*n.x+inv.m11*n.y+inv.m12*n.z+inv.m13,
                  inv.m20*n.x+inv.m21*n.y+inv.m22*n.z+inv.m23);
}

Ray Matrix4::operator*(const Ray& r)const
{
    Point3 origin = (*this)*r.origin;
    Vec3 direction = (*this)*r.direction;
    return Ray(origin,direction);
}

//♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥

void sum(const Matrix4* input1, const Matrix4* input2, Matrix4* output)
{
    output->m00 = input1->m00 + input2->m00;
    output->m01 = input1->m01 + input2->m01;
    output->m02 = input1->m02 + input2->m02;
    output->m03 = input1->m03 + input2->m03;
    output->m10 = input1->m10 + input2->m10;
    output->m11 = input1->m11 + input2->m11;
    output->m12 = input1->m12 + input2->m12;
    output->m13 = input1->m13 + input2->m13;
    output->m20 = input1->m20 + input2->m20;
    output->m21 = input1->m21 + input2->m21;
    output->m22 = input1->m22 + input2->m22;
    output->m23 = input1->m23 + input2->m23;
    output->m30 = input1->m30 + input2->m30;
    output->m31 = input1->m31 + input2->m31;
    output->m32 = input1->m32 + input2->m32;
    output->m33 = input1->m33 + input2->m33;
}

void sub(const Matrix4* input1, const Matrix4* input2, Matrix4* output)
{
    output->m00 = input1->m00 - input2->m00;
    output->m01 = input1->m01 - input2->m01;
    output->m02 = input1->m02 - input2->m02;
    output->m03 = input1->m03 - input2->m03;
    output->m10 = input1->m10 - input2->m10;
    output->m11 = input1->m11 - input2->m11;
    output->m12 = input1->m12 - input2->m12;
    output->m13 = input1->m13 - input2->m13;
    output->m20 = input1->m20 - input2->m20;
    output->m21 = input1->m21 - input2->m21;
    output->m22 = input1->m22 - input2->m22;
    output->m23 = input1->m23 - input2->m23;
    output->m30 = input1->m30 - input2->m30;
    output->m31 = input1->m31 - input2->m31;
    output->m32 = input1->m32 - input2->m32;
    output->m33 = input1->m33 - input2->m33;
}

void mul(const Matrix4* input1, const Matrix4* input2, Matrix4* output)
{
    output->m00 = (input1->m00 * input2->m00) +
    (input1->m01 * input2->m10) +
    (input1->m02 * input2->m20) +
    (input1->m03 * input2->m30);
    
    output->m01 = (input1->m00 * input2->m01) +
    (input1->m01 * input2->m11) +
    (input1->m02 * input2->m21) +
    (input1->m03 * input2->m31);
    
    output->m02 = (input1->m00 * input2->m02) +
    (input1->m01 * input2->m12) +
    (input1->m02 * input2->m22) +
    (input1->m03 * input2->m32);
    
    output->m03 = (input1->m00 * input2->m03) +
    (input1->m01 * input2->m13) +
    (input1->m02 * input2->m23) +
    (input1->m03 * input2->m33);
    
    output->m10 = (input1->m10 * input2->m00) +
    (input1->m11 * input2->m10) +
    (input1->m12 * input2->m20) +
    (input1->m13 * input2->m30);
    
    output->m11 = (input1->m10 * input2->m01) +
    (input1->m11 * input2->m11) +
    (input1->m12 * input2->m21) +
    (input1->m13 * input2->m31);
    
    output->m12 = (input1->m10 * input2->m02) +
    (input1->m11 * input2->m12) +
    (input1->m12 * input2->m22) +
    (input1->m13 * input2->m32);
    
    output->m13 = (input1->m10 * input2->m03) +
    (input1->m11 * input2->m13) +
    (input1->m12 * input2->m23) +
    (input1->m13 * input2->m33);
    
    output->m20 = (input1->m20 * input2->m00) +
    (input1->m21 * input2->m10) +
    (input1->m22 * input2->m20) +
    (input1->m23 * input2->m30);
    
    output->m21 = (input1->m20 * input2->m01) +
    (input1->m21 * input2->m11) +
    (input1->m22 * input2->m21) +
    (input1->m23 * input2->m31);
    
    output->m22 = (input1->m20 * input2->m02) +
    (input1->m21 * input2->m12) +
    (input1->m22 * input2->m22) +
    (input1->m23 * input2->m32);
    
    output->m23 = (input1->m20 * input2->m03) +
    (input1->m21 * input2->m13) +
    (input1->m22 * input2->m23) +
    (input1->m23 * input2->m33);
    
    output->m30 = (input1->m30 * input2->m00) +
    (input1->m31 * input2->m10) +
    (input1->m32 * input2->m20) +
    (input1->m33 * input2->m30);
    
    output->m31 = (input1->m30 * input2->m01) +
    (input1->m31 * input2->m11) +
    (input1->m32 * input2->m21) +
    (input1->m33 * input2->m31);
    
    output->m32 = (input1->m30 * input2->m02) +
    (input1->m31 * input2->m12) +
    (input1->m32 * input2->m22) +
    (input1->m33 * input2->m32);
    
    output->m33 = (input1->m30 * input2->m03) +
    (input1->m31 * input2->m13) +
    (input1->m32 * input2->m23) +
    (input1->m33 * input2->m33);
}

//- - - - - - - - - - - - - OLD AND UNTESTED - - - - - - - - - - - - - - - - - -

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
    
    output->m00 = column1.x;
    output->m01 = column2.x;
    output->m02 = column3.x;
    output->m03 = .0f;
    output->m10 = column1.y;
    output->m11 = column2.y;
    output->m12 = column3.y;
    output->m13 = .0f;
    output->m20 = column1.z;
    output->m21 = column2.z;
    output->m22 = column3.z;
    output->m23 = .0f;
    output->m30 = -a;
    output->m31 = -b;
    output->m32 = -c;
    output->m33 = 1.f;
    
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
    
    output->m00 = column1.x;
    output->m01 = column2.x;
    output->m02 = column3.x;
    output->m03 = .0f;
    output->m10 = column1.y;
    output->m11 = column2.y;
    output->m12 = column3.y;
    output->m13 = .0f;
    output->m20 = column1.z;
    output->m21 = column2.z;
    output->m22 = column3.z;
    output->m23 = .0f;
    output->m30 = a;
    output->m31 = b;
    output->m32 = c;
    output->m33 = 1.f;
    
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
    
    output->m00 = a;
    output->m01 = .0f;
    output->m02 = .0f;
    output->m03 = .0f;
    output->m10 = .0f;
    output->m11 = b;
    output->m12 = .0f;
    output->m13 = .0f;
    output->m20 = .0f;
    output->m21 = .0f;
    output->m22 = c;
    output->m23 = d;
    output->m30 = .0f;
    output->m31 = .0f;
    output->m32 = e;
    output->m33 = .0f;
    
    return;
}

void PerspectiveRightHand(float fX, float fY, float n, float f, Matrix4* out)
{
    //  [   A   0   0   0   ]
    //  [   0   B   0   0   ]
    //  [   0   0   C   D   ]
    //  [   0   0   E   0   ]
    
    float a = atanf(fX/2);
    float b = atanf(fY/2);
    float tmp = f - n;
    float c = -((f+n)/tmp);
    float d = -((2*n*f)/tmp);
    float e = -1;
    
    
    out->m00 = a;
    out->m01 = .0f;
    out->m02 = .0f;
    out->m03 = .0f;
    out->m10 = .0f;
    out->m11 = b;
    out->m12 = .0f;
    out->m13 = .0f;
    out->m20 = .0f;
    out->m21 = .0f;
    out->m22 = c;
    out->m23 = d;
    out->m30 = .0f;
    out->m31 = .0f;
    out->m32 = e;
    out->m33 = .0f;
    
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
    
    
    out->m00 = a;
    out->m01 = .0f;
    out->m02 = .0f;
    out->m03 = .0f;
    out->m10 = .0f;
    out->m11 = b;
    out->m12 = .0f;
    out->m13 = .0f;
    out->m20 = .0f;
    out->m21 = .0f;
    out->m22 = c;
    out->m23 = d;
    out->m30 = .0f;
    out->m31 = .0f;
    out->m32 = .0f;
    out->m33 = e;
    
    return;
    
}

void Translation(Vec3 *source, Matrix4* output)
{
    output->m00 = 1.0f;
    output->m01 = .0f;
    output->m02 = .0f;
    output->m03 = source->x;
    output->m10 = .0f;
    output->m11 = 1.f;
    output->m12 = .0f;
    output->m13 = source->y;
    output->m20 = .0f;
    output->m21 = .0f;
    output->m22 = 1.0f;
    output->m23 = source->z;
    output->m30 = .0f;
    output->m31 = .0f;
    output->m32 = .0f;
    output->m33 = 1.0f;
    
    return;
}

void Scale(Vec3 *source, Matrix4* output)
{
    output->m00 = source->x;
    output->m01 = .0f;
    output->m02 = .0f;
    output->m03 = .0f;
    output->m10 = .0f;
    output->m11 = source->y;
    output->m12 = .0f;
    output->m13 = .0f;
    output->m20 = .0f;
    output->m21 = .0f;
    output->m22 = source->z;
    output->m23 = .0f;
    output->m30 = .0f;
    output->m31 = .0f;
    output->m32 = .0f;
    output->m33 = 1.0f;
    
    return;
}

void YawPitchRollRotation(float yaw, float pitch, float roll, Matrix4* output)
{
    float quaternion[4];
    
    float halfroll = roll*.5f;
    float halfyaw = yaw*.5f;
    float halfpitch = pitch*.5f;
    
    float sinyaw = sinf(halfyaw);
    float cosyaw = cosf(halfyaw);
    float sinpitch = sinf(halfpitch);
    float cospitch = cosf(halfpitch);
    float sinroll = sinf(halfroll);
    float cosroll = cosf(halfroll);
    
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
    
    output->m00 = 1.f - (2.f * (yy + zz));
    output->m01 = 2.f * (xy + zw);
    output->m02 = 2.f * (zx - yw);
    output->m03 = .0f;
    output->m10 = 2.f * (xy - zw);
    output->m11 = 1.f - (2.f * (zz + xx));
    output->m12 = 0.f * (yz + xw);
    output->m13 = 0.f;
    output->m20= 2.f * (zx + yw);
    output->m21 = 2.f * (yz - xw);
    output->m22 = 1.f - (2.f * (yy + xx));
    output->m23 = .0f;
    output->m30 = .0f;
    output->m31 = .0f;
    output->m32 = .0f;
    output->m33 = 1.0f;
    
    return;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
