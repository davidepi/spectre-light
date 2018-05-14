//Created, October 2013
//Last Edit 14 May 2018

/**
 *  \file matrix4.hpp
 *  \brief     Matrix4 class definition
 *  \details   Definition and implementation of a 4 by 4 matrix and some inline
 *             functions to perform addition, subtraction and multiplication
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      14 May 2018
 *  \copyright GNU GPLv3
 */


#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include "utility/utility.hpp"
#include "geometry/vec3.hpp"
#include "geometry/point3.hpp"
#include "geometry/ray.hpp"
#include "utility/console.hpp"
#include <cmath>
#include <string>
#include <sstream> //to_string
#include <cstdio>

/**
 *  \class Matrix4 matrix4.hpp "geometry/matrix4.hpp"
 *  \brief A 4 by 4 transformation matrix
 *
 *  The Matrix4 class represents a 4x4 transformation matrix in 3D space. A 4x4
 *  Matrix is usually used to perform transformations such as scaling, rotations
 *  or translations of a model.
 *  The matrix is 4x4 instead of 3x3 because some transformations requires an
 *  homogeneus space instead of a cartesian one
 *
 *  This Matrix4 consist of 16 distinct variables in form mXY where \e X is the
 *  row number 0-based and Y is the column number 0-based.
 */
class Matrix4
{
public:

    /// matrix[0][0]
    float m00;
    /// matrix[0][1]
    float m01;
    /// matrix[0][2]
    float m02;
    /// matrix[0][3]
    float m03;
    /// matrix[1][0]
    float m10;
    /// matrix[1][1]
    float m11;
    /// matrix[1][2]
    float m12;
    /// matrix[1][3]
    float m13;
    /// matrix[2][0]
    float m20;
    /// matrix[2][1]
    float m21;
    /// matrix[2][2]
    float m22;
    /// matrix[2][3]
    float m23;
    /// matrix[3][0]
    float m30;
    /// matrix[3][1]
    float m31;
    /// matrix[3][2]
    float m32;
    /// matrix[3][3]
    float m33;

    /** \brief Default constructor
     *
     *  Allocate a matrix of 4 by 4 single precision floating point, with
     *  undefined values
     *
     *  \warning values are NOT initialized
     */
    Matrix4() = default;

    /** \brief Construct a 4 by 4 matrix with the given array of floats
     *
     * \note The contents of the array values are assumed to be in row-major
     *       order
     *
     * \param[in] values An array of float containing the values of the matrix
     */
    Matrix4(const float* values);

    ///Default destructor
    ~Matrix4() = default;

    /**  \brief Represent the matrix with a std::string
     *
     *  Represents this matrix as a string. Note that the output string will
     *  contain multiple lines and end with a \n character
     *
     *  \return An std::string containing the values of the matrix
     *  \sa to_array()
     */
    std::string to_string() const;

    /**  \brief Represent this matrix with an array
     *
     *  Copy the components of this matrix in an unidimensional array of float,
     *  heap allocated
     *
     *  \param[out] values An array of 16 elements containing the values of the
     *              matrix in row major order
     *  \sa to_string()
     */
    void to_array(float* values) const;

    /** \brief Set this matrix to a zero-matrix
     *
     *  Fill this matrix with 0 values
     *  \sa set_identity()
     */
    void set_zero();

    /** \brief Set this matrix to the identity matrix
     *
     *  Set this matrix to the identity matrix (unit matrix), filled with
     *  1 values in the diagonal and 0 values everywhere else
     */
    void set_identity();

    /** \brief Set this matrix to a translation matrix
     *
     *  Set this matrix to a transformation matrix responsible of the
     *  translation. The input vector defines the magnitude and direction
     *  of the translation
     *
     *  \param[in] direction The vector representing the direction of the
     *             translation
     */
    void set_translation(Vec3 direction);

    /** \brief Set this matrix to a scale matrix
     *
     *  Set this matrix to a transformation matrix responsible of the
     *  uniform scaling. The input float defines the magnitude of the scaling
     *
     *  \param[in] value The float representing the magnitude of the
     *             scaling
     */
    void set_scale(float value);

    /** \brief Set this matrix to a scale matrix
     *
     *  Set this matrix to a transformation matrix responsible of the
     *  non-unfirom scaling. The input vector defines the magnitude of the
     *  scaling factor for each component
     *
     *  \param[in] value The vector representing the magnitude of the
     *             scaling for each component
     */
    void set_scale(Vec3 value);

    /** \brief Set this matrix to a rotation matrix
     *
     *  Set this matrix to a transformation matrix responsible of the rotation
     *  around the X axis. The input float defines the angle of rotation
     *  in radians
     *
     *  \param[in] value The angle of rotation in radians
     *
     *  \sa set_rotate_y(float value)
     *  \sa set_rotate_z(float value)
     */
    void set_rotate_x(float value);

    /** \brief set this matrix to a rotation matrix
     *
     *  Set this matrix to a transformation matrix responsible of the rotation
     *  around the Y axis. The input float defines the angle of rotation
     *  in radians
     *
     *  \param[in] value The angle of rotation in radians
     *
     *  \sa set_rotate_x(float value)
     *  \sa set_rotate_z(float value)
     */
    void set_rotate_y(float value);

    /** \brief set this matrix to a rotation matrix
     *
     *  Set this matrix to a transformation matrix responsible of the rotation
     *  around the Z axis. The input float defines the angle of rotation
     *  in radians
     *
     *  \param[in] value The angle of rotation in radians
     *
     *  \sa set_rotate_x(float value)
     *  \sa set_rotate_y(float value)
     */
    void set_rotate_z(float value);

    /** \brief Set this matrix to an inverted LookAt matrix
     *
     *  Set this matrix to an inverse transformation LookAt matrix in a
     *  left handed system. This matrix is used to align the world with the
     *  camera (can be seen as a result of placing the camera inside a scene).
     *  This is done by transforming the camera space coordinates to world
     *  space (camera to world transformation)
     *
     *  /note Recall that in the left handed system the front direction is Z,
     *  and the up direction is Y instead of the usual Z-up Y-front
     *
     *  \param[in] pos The position of the camera
     *  \param[in] target The point the camera is looking at
     *  \param[in] up A vector representing the direction poiting upside the
     *  camera. With the camera parallel to the terrain, this will be (0,1,0)
     */
    void set_lookAt_inverse(const Point3& pos, const Point3& target,
                            const Vec3& up);

    /**  \brief Returns a new matrix that is the transpose of the current matrix
     *
     *  \param[out] output A pointer to the allocated area where the new matrix
     *                     will be written
     */
    void transpose(Matrix4* output) const;

    /**  \brief Returns a new matrix that is the inverse of the current matrix
     *
     *   This method tries to invert the matrix (if it is invertible) and writes
     *   the resulting matrix in the input parameter. If the matrix is not
     *   invertible nothing is written and the function returns false.
     *
     *  \param[out] output A pointer to the allocated area where the new matrix
     *                     will be written
     *  \return A boolean value indicating if the matrix has been inverted or
     *          not
     */
    bool inverse(Matrix4* output) const;

    /** \brief Extract the translation component from the matrix
     *
     *  If the Matrix4 was generated by a composition of scales, rotations and
     *  translations, this method extracts the translation component
     *
     *  \return A Vec3 representing the translation component of the matrix
     */
    Vec3 get_translation() const;

    /** \brief Extract the scale component from the matrix
     *
     *  If the Matrix4 was generated by a composition of scales, rotations and
     *  translations, this method extracts the scale component
     *
     *  \return A Vec3 representing the scale component of the matrix
     */
    Vec3 get_scale() const;


    //------ Operators ---------------------------------------------------------

    ///The addition operation between two matrices
    Matrix4 operator+(const Matrix4&) const;

    ///The subtraction operation between two matrices
    Matrix4 operator-(const Matrix4&) const;

    ///The multiplication operation between two matrices
    Matrix4 operator*(const Matrix4&) const;

    ///The addition operation between two matrices
    void operator+=(const Matrix4&);

    ///The subtraction operation between two matrices
    void operator-=(const Matrix4&);

    ///The multiplication operation between two matrices
    void operator*=(const Matrix4&);

    ///Checks if two matrices are equal
    bool operator==(const Matrix4&) const;

    ///Checks if two matrices are different
    bool operator!=(const Matrix4&) const;

    ///Apply the transformation matrix to the Point
    Point3 operator*(const Point3&) const;

    ///Apply the transformation matrix to the Vector
    Vec3 operator*(const Vec3&) const;

    ///Apply the transformation matrix to the Ray
    Ray operator*(const Ray&) const;

    ///Apply the transformation matrix to the RayDiff
    RayDiff operator*(const RayDiff&) const;


    //--------------------------------------------------------------------------

};

/** \brief Apply the transformation matrix to the Normal
 *
 *  Since transforming a normal implies a multiplication by the inverse of
 *  the transform matrix, and since this matrix is often stored somewhere,
 *  this method requires such a matrix as input instead of computing it
 *  every time
 *
 *  \param[in] n The normal that will be transformed
 *  \param[in] inverse The inverse of the transformation matrix used
 *  \return The transformed normal
*/
Normal transform_normal(const Normal& n, const Matrix4* inverse);

/**  /brief Sum two matrices together
 *
 *  \param[in] input1 The left matrix to sum
 *  \param[in] input2 The right matrix to sum
 *  \param[out] output The resulting matrix
 */
void sum(const Matrix4* input1, const Matrix4* input2, Matrix4* output);

/** \brief Subtract two matrices together
 *
 *  \param[in] input1 The subtracting left matrix
 *  \param[in] input2 The subtracting right matrix
 *  \param[out] output The resulting matrix
 */
void sub(const Matrix4* input1, const Matrix4* input2, Matrix4* output);

/**  \brief Multiply two matrices together
 *
 *  \param[in] input1 The left matrix to multiply
 *  \param[in] input2 The right matrix to multiply
 *  \param[out] output The resulting matrix
 */
void mul(const Matrix4* input1, const Matrix4* input2, Matrix4* output);

#endif
