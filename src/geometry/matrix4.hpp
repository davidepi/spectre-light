//Created, October 2013
//Last Edit  3 Mar 2016

/**
 *  \file matrix4.hpp
 *  \brief     Matrix4 class definition
 *  \details   Definition and implementation of a 4 by 4 matrix and some inline
 *             functions to perform addition, subtraction and multiplication
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      03 March 2016
 *  \warning   Since this is a low level class, some verification are skipped.
 *             More details are provided for every method
 *  \copyright GNU Public License.
 */


#ifndef __MATRIX4_H__
#define __MATRIX4_H__
#include "vec3.hpp"
#include <cmath>

/**
 *  \class Matrix4 matrix4.hpp "Geometry/matrix4.hpp"
 *  \brief A 4 by 4 transformation matrix
 *
 *  The Matrix4 class represents a 4x4 transformation matrix in 3D space. A 4x4
 *  Matrix is usually used to perform transformation such as scaling, rotating
 *  or translating a model (by performing these operations vertex by vertex).
 *  This class contains all the methods to generate such matrices, that can be
 *  further multiplied with the method "TransformCoordinate(...)" contained in
 *  the Vec3 class.
 *
 *  This Matrix4 consist of a multidimensional array containing floating point
 *  numbers.
 */
class Matrix4
{
public:
    float m[4][4];
    
    /** \brief Default constructor
     *  Construct a zero matrix 4 by 4 of single precision floating point
     */
    Matrix4();
    

    /** \brief  Construct an identity matrix of single precision floating point
     *   The "identity" parameter is left unused
     *  
     *  \param identity This parameter is left unused.
     */
    Matrix4(int identity);
    
    /** \brief Construct a 4 by 4 matrix with the given array of single 
     *         precision floating point numbers.
     *
     * \note The contents of the array values is assumed to be in row-major order
     *
     * \param values An array of float containing the values of the matrix
     */
    Matrix4(const float* values);
    
    ///Destructor
    ~Matrix4();
    
    /**  \brief Represent the matrix with a C-string
     *
     *  Allocate in the heap a C-string and write the components of the matrix
     *  as a string
     *
     *  \return An heap allocated char array containing the values of the
     *           matrix
     *  \note A char* is allocated on heap and must be deleted
     *  \sa toArray()
     */
    char* toString()const;
    
    /**  \brief Represent this matrix with an array
     *
     *  Copy the components of this matrix in an unidimensional array of float,
     *  heap allocated
     *
     *  \return  An heap allocated 0-based array containing the value of the
     *           matrix in row major order
     *  \note A float* is allocated on heap and must be deleted
     *  \sa toString()
     */
    float* toArray()const;
    
    /**  \brief Returns a new matrix that is the transpose of the current matrix
     *
     *  \param[out] output A pointer to the allocated area where the new matrix 
     *                     will be written
     */
    void transpose(Matrix4* output)const;
    
    /**  \brief Returns a new matrix that is the inverse of the current matrix
     *
     *   This method tries to invert the matrix (if it is invertible) and writes
     *   the resulting matrix in the input parameter. If the matrix is not
     *   invertible nothing is written and the function return false.
     *   The inverted matrix is calculated using the Gauss-Jordan elimination
     *
     *  \param[out] output A pointer to the allocated area where the new matrix 
     *                     will be written
     *  \return A boolean value indicating if the matrix has been inverted or
     *          not
     */
    bool inverse(Matrix4* output)const;

//♥ ♥ ♥ Operators ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥
    
    ///The addition operation between two matrices
    Matrix4 operator+(const Matrix4&)const;
    ///The subtraction operation between two matrices
    Matrix4 operator-(const Matrix4&)const;
    ///The multiplication operation between two matrices
    Matrix4 operator*(const Matrix4&)const;
    ///The division operation between two matrices
    Matrix4 operator/(const Matrix4&)const;
    ///The addition operation between two matrices
    void operator+=(const Matrix4&);
    ///The subtraction operation between two matrices
    void operator-=(const Matrix4&);
    ///The multiplication operation between two matrices
    void operator*=(const Matrix4&);
    ///The division operation between two matrices
    void operator/=(const Matrix4&);
    ///Checks if two matrices are equal
    bool operator==(const Matrix4&)const;
    ///Checks if two matrices are different
    bool operator!=(const Matrix4&)const;
    
//♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥
    
};

/**  /brief Sum two matrices together
 *  
 *  \param[in] input1 The left matrix to sum
 *  \param[in] input2 The right matrix to sum
 *  \param[out] output The resulting matrix
 */
void sum (const Matrix4* input1, const Matrix4* input2, Matrix4* output);

/** \brief Subtract two matrices together
 *
 *  \param[in] input1 The subtracting left matrix
 *  \param[in] input2 The subtracting right matrix
 *  \param[out] output The resulting matrix
 */
void sub (const Matrix4* input1, const Matrix4* input2, Matrix4* output);

/**  \brief Multiply two matrices together
 *
 *  \param[in] input1 The left matrix to multiply
 *  \param[in] input2 The right matrix to multiply
 *  \param[out] output The resulting matrix
 */
void mull(const Matrix4* input1, const Matrix4* input2, Matrix4* output);

__attribute__((deprecated))
/** \brief Creates a View Space transform matrix with a Left Hand coordinate 
 *         system
 *
 *  \deprecated Embedded into \a Transform class
 *  \param[in] target A Vec3 containing the target point of the camera view
 *  \param[in] position A Vec3 containing the position of the camera
 *  \param[in] up A Vec3 containing the up vector for the camera, 
 *                usually v(0,1,0)
 *  \param[out] output The resulting Matrix4
 */
void viewLeftHand(Vec3* target, Vec3* position, Vec3* up, Matrix4* output);

__attribute__((deprecated))
/** \brief Creates a View Space transform matrix with a Right Hand coordinate 
 *         system
 *  
 *  \deprecated Embedded into \a Transform class
 *  \param[in] target A Vec3 containing the target point of the camera view
 *  \param[in] position A Vec3 containing the position of the camera
 *  \param[in] up A Vec3 containing the up vector for the camera, usually
 *                v(0,1,0)
 *  \param[out] output The resulting Matrix4
 */
void viewRightHand(Vec3* target, Vec3* position, Vec3* up, Matrix4* output);

__attribute__((deprecated))
/** \brief Creates a Perspective transform matrix with a Left Hand coordinate 
 *         system
 *
 *  \deprecated Embedded into \a Transform class
 *  \param[in] fov A float representing the field of view of the camera
 *  \param[in] aspectRatio A float representing the aspect ratio of the screen
 *  \param[in] nearPlane A float representing the z value of the near plane
 *  \param[in] farPlane A float representing the z value of the far plane
 *  \param[out] output The resulting matrix
 */
void PerspectiveLeftHand(float fov, float aspectRatio, float nearPlane,
                         float farPlane, Matrix4* output);

__attribute__((deprecated))
/** \brief Creates a Perspective transform matrix with a Right Hand coordinate 
 *         system
 *
 *  \deprecated Embedded into \a Transform class
 *  \param[in] fovX A float representing the x-axis field of view of the camera
 *  \param[in] fovY A float representing the y-axis field of view of the camera
 *  \param[in] nearPlane A float representing the z value of the near plane
 *  \param[in] farPlane A float representing the z value of the far plane
 *  \param[out] output The resulting matrix
 */
void PerspectiveRightHand(float fovX, float fovY, float nearPlane,
                          float farPlane, Matrix4* output);

__attribute__((deprecated))
/** \brief Creates an Orthographic transform matrix with a Right Hand coordinate
 *         system
 *
 *  \deprecated Embedded into \a Transform class
 *  \param[in] width A float representing the height of the screen
 *  \param[in] height A float representing the width of the screen
 *  \param[in] nearPlane A float representing the z value of the near plane
 *  \param[in] farPlane A float representing the z value of the far plane
 *  \param[out] output The resulting matrix
 */
void OrthographicRightHand(float width, float height, float nearPlane,
                          float farPlane, Matrix4* output);

__attribute__((deprecated))
/** \brief Creates a Translation matrix
 *
 *  \deprecated Embedded into \a Transform class
 *  \param[in] source A Vec3 containing the translation value of the object
 *  \param[out] output The resulting matrix
 */
void Translation(Vec3* source, Matrix4* output);

__attribute__((deprecated))
/** \brief Creates a Rotation matrix
 *
 *  \deprecated Embedded into \a Transform class
 *  \param[in] yaw A float containing the yaw value of the rotation 
 *                  (Z-rotation)
 *  \param[in] pitch A float containing the pitch value of the rotation 
 *                  (Y-rotation)
 *  \param[in] roll A float containing the roll value of the rotation 
 *                  (X-rotation)
 *  \param[out] output The resulting matrix
 */
void YawPitchRollRotation(float yaw, float pitch, float roll, Matrix4* output);

__attribute__((deprecated))
/** \brief Creates a Scaling matrix
 *
 *  \deprecated Embedded into \a Transform class
 *  \param[in] source A Vec3 containing the scaling value of the object
 *  \param[out] output The resulting matrix
 */
void Scale(Vec3* source, Matrix4* output);

#endif
