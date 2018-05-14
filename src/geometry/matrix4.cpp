//author: Davide Pizzolotto
//license: GNU GPLv3

#include "matrix4.hpp"

#define CHAR_ARRAY_SIZE_PER_FLOAT 10

Matrix4::Matrix4(const float* v)
{
#ifdef DEBUG
    if(v != NULL)
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
#ifdef DEBUG
    }
    else
        Console.warning(MESSAGE_MATRIX4_NULLINIT);
#endif
}

std::string Matrix4::to_string() const
{
    std::ostringstream oss;
    oss << std::fixed;
    oss << "Matrix4[" << m00 << ", " << m01 << ", " << m02 << ", " << m03 <<
        "]\n";
    oss << "       [" << m10 << ", " << m11 << ", " << m12 << ", " << m13 <<
        "]\n";
    oss << "       [" << m20 << ", " << m21 << ", " << m22 << ", " << m23 <<
        "]\n";
    oss << "       [" << m30 << ", " << m31 << ", " << m32 << ", " << m33 <<
        "]\n";
    return oss.str();
}

void Matrix4::to_array(float* res) const
{
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
}

void Matrix4::set_zero()
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

void Matrix4::set_identity()
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

void Matrix4::set_translation(Vec3 direction)
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

void Matrix4::set_scale(float value)
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

void Matrix4::set_scale(Vec3 value)
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

void Matrix4::set_rotate_x(float value)
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

void Matrix4::set_rotate_y(float value)
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

void Matrix4::set_rotate_z(float value)
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

void Matrix4::set_lookAt_inverse(const Point3& pos, const Point3& eye,
                                 const Vec3& up)
{
    Vec3 newup = up;
    if(!(up.is_normalized()))
    {
        Console.warning(MESSAGE_UPVECTOR_NOTUNIT);
        newup.normalize();
    }
    Vec3 dir = eye-pos;
    dir.normalize();
    Vec3 left = cross(newup, dir);
    left.normalize();
    newup = cross(dir, left);

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
}

void Matrix4::transpose(Matrix4* output) const
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

bool Matrix4::inverse(Matrix4* output) const
{
    float inv[16], det;

    inv[0] = Matrix4::m11*Matrix4::m22*Matrix4::m33-
             Matrix4::m11*Matrix4::m23*Matrix4::m32-
             Matrix4::m21*Matrix4::m12*Matrix4::m33+
             Matrix4::m21*Matrix4::m13*Matrix4::m32+
             Matrix4::m31*Matrix4::m12*Matrix4::m23-
             Matrix4::m31*Matrix4::m13*Matrix4::m22;

    inv[4] = -Matrix4::m10*Matrix4::m22*Matrix4::m33+
             Matrix4::m10*Matrix4::m23*Matrix4::m32+
             Matrix4::m20*Matrix4::m12*Matrix4::m33-
             Matrix4::m20*Matrix4::m13*Matrix4::m32-
             Matrix4::m30*Matrix4::m12*Matrix4::m23+
             Matrix4::m30*Matrix4::m13*Matrix4::m22;

    inv[8] = Matrix4::m10*Matrix4::m21*Matrix4::m33-
             Matrix4::m10*Matrix4::m23*Matrix4::m31-
             Matrix4::m20*Matrix4::m11*Matrix4::m33+
             Matrix4::m20*Matrix4::m13*Matrix4::m31+
             Matrix4::m30*Matrix4::m11*Matrix4::m23-
             Matrix4::m30*Matrix4::m13*Matrix4::m21;

    inv[12] = -Matrix4::m10*Matrix4::m21*Matrix4::m32+
              Matrix4::m10*Matrix4::m22*Matrix4::m31+
              Matrix4::m20*Matrix4::m11*Matrix4::m32-
              Matrix4::m20*Matrix4::m12*Matrix4::m31-
              Matrix4::m30*Matrix4::m11*Matrix4::m22+
              Matrix4::m30*Matrix4::m12*Matrix4::m21;

    inv[1] = -Matrix4::m01*Matrix4::m22*Matrix4::m33+
             Matrix4::m01*Matrix4::m23*Matrix4::m32+
             Matrix4::m21*Matrix4::m02*Matrix4::m33-
             Matrix4::m21*Matrix4::m03*Matrix4::m32-
             Matrix4::m31*Matrix4::m02*Matrix4::m23+
             Matrix4::m31*Matrix4::m03*Matrix4::m22;

    inv[5] = Matrix4::m00*Matrix4::m22*Matrix4::m33-
             Matrix4::m00*Matrix4::m23*Matrix4::m32-
             Matrix4::m20*Matrix4::m02*Matrix4::m33+
             Matrix4::m20*Matrix4::m03*Matrix4::m32+
             Matrix4::m30*Matrix4::m02*Matrix4::m23-
             Matrix4::m30*Matrix4::m03*Matrix4::m22;

    inv[9] = -Matrix4::m00*Matrix4::m21*Matrix4::m33+
             Matrix4::m00*Matrix4::m23*Matrix4::m31+
             Matrix4::m20*Matrix4::m01*Matrix4::m33-
             Matrix4::m20*Matrix4::m03*Matrix4::m31-
             Matrix4::m30*Matrix4::m01*Matrix4::m23+
             Matrix4::m30*Matrix4::m03*Matrix4::m21;

    inv[13] = Matrix4::m00*Matrix4::m21*Matrix4::m32-
              Matrix4::m00*Matrix4::m22*Matrix4::m31-
              Matrix4::m20*Matrix4::m01*Matrix4::m32+
              Matrix4::m20*Matrix4::m02*Matrix4::m31+
              Matrix4::m30*Matrix4::m01*Matrix4::m22-
              Matrix4::m30*Matrix4::m02*Matrix4::m21;

    inv[2] = Matrix4::m01*Matrix4::m12*Matrix4::m33-
             Matrix4::m01*Matrix4::m13*Matrix4::m32-
             Matrix4::m11*Matrix4::m02*Matrix4::m33+
             Matrix4::m11*Matrix4::m03*Matrix4::m32+
             Matrix4::m31*Matrix4::m02*Matrix4::m13-
             Matrix4::m31*Matrix4::m03*Matrix4::m12;

    inv[6] = -Matrix4::m00*Matrix4::m12*Matrix4::m33+
             Matrix4::m00*Matrix4::m13*Matrix4::m32+
             Matrix4::m10*Matrix4::m02*Matrix4::m33-
             Matrix4::m10*Matrix4::m03*Matrix4::m32-
             Matrix4::m30*Matrix4::m02*Matrix4::m13+
             Matrix4::m30*Matrix4::m03*Matrix4::m12;

    inv[10] = Matrix4::m00*Matrix4::m11*Matrix4::m33-
              Matrix4::m00*Matrix4::m13*Matrix4::m31-
              Matrix4::m10*Matrix4::m01*Matrix4::m33+
              Matrix4::m10*Matrix4::m03*Matrix4::m31+
              Matrix4::m30*Matrix4::m01*Matrix4::m13-
              Matrix4::m30*Matrix4::m03*Matrix4::m11;

    inv[14] = -Matrix4::m00*Matrix4::m11*Matrix4::m32+
              Matrix4::m00*Matrix4::m12*Matrix4::m31+
              Matrix4::m10*Matrix4::m01*Matrix4::m32-
              Matrix4::m10*Matrix4::m02*Matrix4::m31-
              Matrix4::m30*Matrix4::m01*Matrix4::m12+
              Matrix4::m30*Matrix4::m02*Matrix4::m11;

    inv[3] = -Matrix4::m01*Matrix4::m12*Matrix4::m23+
             Matrix4::m01*Matrix4::m13*Matrix4::m22+
             Matrix4::m11*Matrix4::m02*Matrix4::m23-
             Matrix4::m11*Matrix4::m03*Matrix4::m22-
             Matrix4::m21*Matrix4::m02*Matrix4::m13+
             Matrix4::m21*Matrix4::m03*Matrix4::m12;

    inv[7] = Matrix4::m00*Matrix4::m12*Matrix4::m23-
             Matrix4::m00*Matrix4::m13*Matrix4::m22-
             Matrix4::m10*Matrix4::m02*Matrix4::m23+
             Matrix4::m10*Matrix4::m03*Matrix4::m22+
             Matrix4::m20*Matrix4::m02*Matrix4::m13-
             Matrix4::m20*Matrix4::m03*Matrix4::m12;

    inv[11] = -Matrix4::m00*Matrix4::m11*Matrix4::m23+
              Matrix4::m00*Matrix4::m13*Matrix4::m21+
              Matrix4::m10*Matrix4::m01*Matrix4::m23-
              Matrix4::m10*Matrix4::m03*Matrix4::m21-
              Matrix4::m20*Matrix4::m01*Matrix4::m13+
              Matrix4::m20*Matrix4::m03*Matrix4::m11;

    inv[15] = Matrix4::m00*Matrix4::m11*Matrix4::m22-
              Matrix4::m00*Matrix4::m12*Matrix4::m21-
              Matrix4::m10*Matrix4::m01*Matrix4::m22+
              Matrix4::m10*Matrix4::m02*Matrix4::m21+
              Matrix4::m20*Matrix4::m01*Matrix4::m12-
              Matrix4::m20*Matrix4::m02*Matrix4::m11;

    det = Matrix4::m00*inv[0]+Matrix4::m01*inv[4]
          +Matrix4::m02*inv[8]+Matrix4::m03*inv[12];

    if(flt_equal(det, 0.0f))
        return false;

    det = 1.0f/det;

    output->m00 = inv[0]*det;
    output->m01 = inv[1]*det;
    output->m02 = inv[2]*det;
    output->m03 = inv[3]*det;
    output->m10 = inv[4]*det;
    output->m11 = inv[5]*det;
    output->m12 = inv[6]*det;
    output->m13 = inv[7]*det;
    output->m20 = inv[8]*det;
    output->m21 = inv[9]*det;
    output->m22 = inv[10]*det;
    output->m23 = inv[11]*det;
    output->m30 = inv[12]*det;
    output->m31 = inv[13]*det;
    output->m32 = inv[14]*det;
    output->m33 = inv[15]*det;

    return true;
}

Vec3 Matrix4::get_translation() const
{
    return Vec3(Matrix4::m03, Matrix4::m13, Matrix4::m23);
}

Vec3 Matrix4::get_scale() const
{
    const Vec3 x(Matrix4::m00, Matrix4::m10, Matrix4::m20);
    const Vec3 y(Matrix4::m01, Matrix4::m11, Matrix4::m21);
    const Vec3 z(Matrix4::m02, Matrix4::m12, Matrix4::m22);
    return Vec3(x.length(), y.length(), z.length());
}

//------ Operators -------------------------------------------------------------

Matrix4 Matrix4::operator+(const Matrix4& mat) const
{
    float val[16];
    val[0] = Matrix4::m00+mat.m00;
    val[1] = Matrix4::m01+mat.m01;
    val[2] = Matrix4::m02+mat.m02;
    val[3] = Matrix4::m03+mat.m03;
    val[4] = Matrix4::m10+mat.m10;
    val[5] = Matrix4::m11+mat.m11;
    val[6] = Matrix4::m12+mat.m12;
    val[7] = Matrix4::m13+mat.m13;
    val[8] = Matrix4::m20+mat.m20;
    val[9] = Matrix4::m21+mat.m21;
    val[10] = Matrix4::m22+mat.m22;
    val[11] = Matrix4::m23+mat.m23;
    val[12] = Matrix4::m30+mat.m30;
    val[13] = Matrix4::m31+mat.m31;
    val[14] = Matrix4::m32+mat.m32;
    val[15] = Matrix4::m33+mat.m33;

    return Matrix4(val);
}

Matrix4 Matrix4::operator-(const Matrix4& mat) const
{
    float val[16];
    val[0] = Matrix4::m00-mat.m00;
    val[1] = Matrix4::m01-mat.m01;
    val[2] = Matrix4::m02-mat.m02;
    val[3] = Matrix4::m03-mat.m03;
    val[4] = Matrix4::m10-mat.m10;
    val[5] = Matrix4::m11-mat.m11;
    val[6] = Matrix4::m12-mat.m12;
    val[7] = Matrix4::m13-mat.m13;
    val[8] = Matrix4::m20-mat.m20;
    val[9] = Matrix4::m21-mat.m21;
    val[10] = Matrix4::m22-mat.m22;
    val[11] = Matrix4::m23-mat.m23;
    val[12] = Matrix4::m30-mat.m30;
    val[13] = Matrix4::m31-mat.m31;
    val[14] = Matrix4::m32-mat.m32;
    val[15] = Matrix4::m33-mat.m33;

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

Matrix4 Matrix4::operator*(const Matrix4& mat) const
{
    float val[16];
    val[0] = (Matrix4::m00*mat.m00)+
             (Matrix4::m01*mat.m10)+
             (Matrix4::m02*mat.m20)+
             (Matrix4::m03*mat.m30);

    val[1] = (Matrix4::m00*mat.m01)+
             (Matrix4::m01*mat.m11)+
             (Matrix4::m02*mat.m21)+
             (Matrix4::m03*mat.m31);

    val[2] = (Matrix4::m00*mat.m02)+
             (Matrix4::m01*mat.m12)+
             (Matrix4::m02*mat.m22)+
             (Matrix4::m03*mat.m32);

    val[3] = (Matrix4::m00*mat.m03)+
             (Matrix4::m01*mat.m13)+
             (Matrix4::m02*mat.m23)+
             (Matrix4::m03*mat.m33);

    val[4] = (Matrix4::m10*mat.m00)+
             (Matrix4::m11*mat.m10)+
             (Matrix4::m12*mat.m20)+
             (Matrix4::m13*mat.m30);

    val[5] = (Matrix4::m10*mat.m01)+
             (Matrix4::m11*mat.m11)+
             (Matrix4::m12*mat.m21)+
             (Matrix4::m13*mat.m31);

    val[6] = (Matrix4::m10*mat.m02)+
             (Matrix4::m11*mat.m12)+
             (Matrix4::m12*mat.m22)+
             (Matrix4::m13*mat.m32);

    val[7] = (Matrix4::m10*mat.m03)+
             (Matrix4::m11*mat.m13)+
             (Matrix4::m12*mat.m23)+
             (Matrix4::m13*mat.m33);

    val[8] = (Matrix4::m20*mat.m00)+
             (Matrix4::m21*mat.m10)+
             (Matrix4::m22*mat.m20)+
             (Matrix4::m23*mat.m30);

    val[9] = (Matrix4::m20*mat.m01)+
             (Matrix4::m21*mat.m11)+
             (Matrix4::m22*mat.m21)+
             (Matrix4::m23*mat.m31);

    val[10] = (Matrix4::m20*mat.m02)+
              (Matrix4::m21*mat.m12)+
              (Matrix4::m22*mat.m22)+
              (Matrix4::m23*mat.m32);

    val[11] = (Matrix4::m20*mat.m03)+
              (Matrix4::m21*mat.m13)+
              (Matrix4::m22*mat.m23)+
              (Matrix4::m23*mat.m33);

    val[12] = (Matrix4::m30*mat.m00)+
              (Matrix4::m31*mat.m10)+
              (Matrix4::m32*mat.m20)+
              (Matrix4::m33*mat.m30);

    val[13] = (Matrix4::m30*mat.m01)+
              (Matrix4::m31*mat.m11)+
              (Matrix4::m32*mat.m21)+
              (Matrix4::m33*mat.m31);

    val[14] = (Matrix4::m30*mat.m02)+
              (Matrix4::m31*mat.m12)+
              (Matrix4::m32*mat.m22)+
              (Matrix4::m33*mat.m32);

    val[15] = (Matrix4::m30*mat.m03)+
              (Matrix4::m31*mat.m13)+
              (Matrix4::m32*mat.m23)+
              (Matrix4::m33*mat.m33);

    return Matrix4(val);
}

void Matrix4::operator*=(const Matrix4& mat)
{
    float val[16];
    val[0] = (Matrix4::m00*mat.m00)+
             (Matrix4::m01*mat.m10)+
             (Matrix4::m02*mat.m20)+
             (Matrix4::m03*mat.m30);

    val[1] = (Matrix4::m00*mat.m01)+
             (Matrix4::m01*mat.m11)+
             (Matrix4::m02*mat.m21)+
             (Matrix4::m03*mat.m31);

    val[2] = (Matrix4::m00*mat.m02)+
             (Matrix4::m01*mat.m12)+
             (Matrix4::m02*mat.m22)+
             (Matrix4::m03*mat.m32);

    val[3] = (Matrix4::m00*mat.m03)+
             (Matrix4::m01*mat.m13)+
             (Matrix4::m02*mat.m23)+
             (Matrix4::m03*mat.m33);

    val[4] = (Matrix4::m10*mat.m00)+
             (Matrix4::m11*mat.m10)+
             (Matrix4::m12*mat.m20)+
             (Matrix4::m13*mat.m30);

    val[5] = (Matrix4::m10*mat.m01)+
             (Matrix4::m11*mat.m11)+
             (Matrix4::m12*mat.m21)+
             (Matrix4::m13*mat.m31);

    val[6] = (Matrix4::m10*mat.m02)+
             (Matrix4::m11*mat.m12)+
             (Matrix4::m12*mat.m22)+
             (Matrix4::m13*mat.m32);

    val[7] = (Matrix4::m10*mat.m03)+
             (Matrix4::m11*mat.m13)+
             (Matrix4::m12*mat.m23)+
             (Matrix4::m13*mat.m33);

    val[8] = (Matrix4::m20*mat.m00)+
             (Matrix4::m21*mat.m10)+
             (Matrix4::m22*mat.m20)+
             (Matrix4::m23*mat.m30);

    val[9] = (Matrix4::m20*mat.m01)+
             (Matrix4::m21*mat.m11)+
             (Matrix4::m22*mat.m21)+
             (Matrix4::m23*mat.m31);

    val[10] = (Matrix4::m20*mat.m02)+
              (Matrix4::m21*mat.m12)+
              (Matrix4::m22*mat.m22)+
              (Matrix4::m23*mat.m32);

    val[11] = (Matrix4::m20*mat.m03)+
              (Matrix4::m21*mat.m13)+
              (Matrix4::m22*mat.m23)+
              (Matrix4::m23*mat.m33);

    val[12] = (Matrix4::m30*mat.m00)+
              (Matrix4::m31*mat.m10)+
              (Matrix4::m32*mat.m20)+
              (Matrix4::m33*mat.m30);

    val[13] = (Matrix4::m30*mat.m01)+
              (Matrix4::m31*mat.m11)+
              (Matrix4::m32*mat.m21)+
              (Matrix4::m33*mat.m31);

    val[14] = (Matrix4::m30*mat.m02)+
              (Matrix4::m31*mat.m12)+
              (Matrix4::m32*mat.m22)+
              (Matrix4::m33*mat.m32);

    val[15] = (Matrix4::m30*mat.m03)+
              (Matrix4::m31*mat.m13)+
              (Matrix4::m32*mat.m23)+
              (Matrix4::m33*mat.m33);

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

bool Matrix4::operator==(const Matrix4& mat) const
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

bool Matrix4::operator!=(const Matrix4& mat) const
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

Point3 Matrix4::operator*(const Point3& p) const
{
    float x = Matrix4::m00*p.x+Matrix4::m01*p.y+Matrix4::m02*p.z+Matrix4::m03;
    float y = Matrix4::m10*p.x+Matrix4::m11*p.y+Matrix4::m12*p.z+Matrix4::m13;
    float z = Matrix4::m20*p.x+Matrix4::m21*p.y+Matrix4::m22*p.z+Matrix4::m23;
    float w = Matrix4::m30*p.x+Matrix4::m31*p.y+Matrix4::m32*p.z+Matrix4::m33;

    if(w == 1.f)
        return Point3(x, y, z);
    else
    {
        w = 1.0f/w;
        x *= w;
        y *= w;
        z *= w;
        return Point3(x, y, z);
    }
}

Vec3 Matrix4::operator*(const Vec3& v) const
{
    return Vec3(Matrix4::m00*v.x+Matrix4::m01*v.y+Matrix4::m02*v.z,
                Matrix4::m10*v.x+Matrix4::m11*v.y+Matrix4::m12*v.z,
                Matrix4::m20*v.x+Matrix4::m21*v.y+Matrix4::m22*v.z);
}

Ray Matrix4::operator*(const Ray& r) const
{
    Point3 origin = (*this)*r.origin;
    Vec3 direction = (*this)*r.direction;
    return Ray(origin, direction);
}

RayDiff Matrix4::operator*(const RayDiff& r) const
{
    Point3 o = (*this)*r.origin;
    Vec3 d = (*this)*r.direction;
    Point3 ox = (*this)*r.originX;
    Point3 oy = (*this)*r.originY;
    Vec3 dx = (*this)*r.directionX;
    Vec3 dy = (*this)*r.directionY;
    return RayDiff(o, d, ox, dx, oy, dy);
}

//------------------------------------------------------------------------------

Normal transform_normal(const Normal& n, const Matrix4* inv)
{
    return Normal(inv->m00*n.x+inv->m10*n.y+inv->m20*n.z,
                  inv->m01*n.x+inv->m11*n.y+inv->m21*n.z,
                  inv->m02*n.x+inv->m12*n.y+inv->m22*n.z);
}

void sum(const Matrix4* input1, const Matrix4* input2, Matrix4* output)
{
    output->m00 = input1->m00+input2->m00;
    output->m01 = input1->m01+input2->m01;
    output->m02 = input1->m02+input2->m02;
    output->m03 = input1->m03+input2->m03;
    output->m10 = input1->m10+input2->m10;
    output->m11 = input1->m11+input2->m11;
    output->m12 = input1->m12+input2->m12;
    output->m13 = input1->m13+input2->m13;
    output->m20 = input1->m20+input2->m20;
    output->m21 = input1->m21+input2->m21;
    output->m22 = input1->m22+input2->m22;
    output->m23 = input1->m23+input2->m23;
    output->m30 = input1->m30+input2->m30;
    output->m31 = input1->m31+input2->m31;
    output->m32 = input1->m32+input2->m32;
    output->m33 = input1->m33+input2->m33;
}

void sub(const Matrix4* input1, const Matrix4* input2, Matrix4* output)
{
    output->m00 = input1->m00-input2->m00;
    output->m01 = input1->m01-input2->m01;
    output->m02 = input1->m02-input2->m02;
    output->m03 = input1->m03-input2->m03;
    output->m10 = input1->m10-input2->m10;
    output->m11 = input1->m11-input2->m11;
    output->m12 = input1->m12-input2->m12;
    output->m13 = input1->m13-input2->m13;
    output->m20 = input1->m20-input2->m20;
    output->m21 = input1->m21-input2->m21;
    output->m22 = input1->m22-input2->m22;
    output->m23 = input1->m23-input2->m23;
    output->m30 = input1->m30-input2->m30;
    output->m31 = input1->m31-input2->m31;
    output->m32 = input1->m32-input2->m32;
    output->m33 = input1->m33-input2->m33;
}

void mul(const Matrix4* input1, const Matrix4* input2, Matrix4* output)
{
    output->m00 = (input1->m00*input2->m00)+
                  (input1->m01*input2->m10)+
                  (input1->m02*input2->m20)+
                  (input1->m03*input2->m30);

    output->m01 = (input1->m00*input2->m01)+
                  (input1->m01*input2->m11)+
                  (input1->m02*input2->m21)+
                  (input1->m03*input2->m31);

    output->m02 = (input1->m00*input2->m02)+
                  (input1->m01*input2->m12)+
                  (input1->m02*input2->m22)+
                  (input1->m03*input2->m32);

    output->m03 = (input1->m00*input2->m03)+
                  (input1->m01*input2->m13)+
                  (input1->m02*input2->m23)+
                  (input1->m03*input2->m33);

    output->m10 = (input1->m10*input2->m00)+
                  (input1->m11*input2->m10)+
                  (input1->m12*input2->m20)+
                  (input1->m13*input2->m30);

    output->m11 = (input1->m10*input2->m01)+
                  (input1->m11*input2->m11)+
                  (input1->m12*input2->m21)+
                  (input1->m13*input2->m31);

    output->m12 = (input1->m10*input2->m02)+
                  (input1->m11*input2->m12)+
                  (input1->m12*input2->m22)+
                  (input1->m13*input2->m32);

    output->m13 = (input1->m10*input2->m03)+
                  (input1->m11*input2->m13)+
                  (input1->m12*input2->m23)+
                  (input1->m13*input2->m33);

    output->m20 = (input1->m20*input2->m00)+
                  (input1->m21*input2->m10)+
                  (input1->m22*input2->m20)+
                  (input1->m23*input2->m30);

    output->m21 = (input1->m20*input2->m01)+
                  (input1->m21*input2->m11)+
                  (input1->m22*input2->m21)+
                  (input1->m23*input2->m31);

    output->m22 = (input1->m20*input2->m02)+
                  (input1->m21*input2->m12)+
                  (input1->m22*input2->m22)+
                  (input1->m23*input2->m32);

    output->m23 = (input1->m20*input2->m03)+
                  (input1->m21*input2->m13)+
                  (input1->m22*input2->m23)+
                  (input1->m23*input2->m33);

    output->m30 = (input1->m30*input2->m00)+
                  (input1->m31*input2->m10)+
                  (input1->m32*input2->m20)+
                  (input1->m33*input2->m30);

    output->m31 = (input1->m30*input2->m01)+
                  (input1->m31*input2->m11)+
                  (input1->m32*input2->m21)+
                  (input1->m33*input2->m31);

    output->m32 = (input1->m30*input2->m02)+
                  (input1->m31*input2->m12)+
                  (input1->m32*input2->m22)+
                  (input1->m33*input2->m32);

    output->m33 = (input1->m30*input2->m03)+
                  (input1->m31*input2->m13)+
                  (input1->m32*input2->m23)+
                  (input1->m33*input2->m33);
}
