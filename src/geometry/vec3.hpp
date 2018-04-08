//Created, October 2013
//Last Edit 21 Jan 2018

/**
 *  \file vec3.hpp
 *  \brief     Vec3 class definition, Normal class definition and their inline
 *             functions
 *  \details   A three components vector or normal class
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      21 Jan 2018
 *  \copyright GNU GPLv3
 */


#ifndef __VEC3_HPP__
#define __VEC3_HPP__

#include "utility/utility.hpp"
#include "geometry/vec2.hpp"
#include "utility/console.hpp"
#include <cstdio> //snprintf
#include <cmath> //std::sqrt
#include <cfloat> //FLT_EPSILON


//class Normal is defined after class Vec3. Since they are very similar, they
//share the same vec3.hpp and vec3.cpp files
class Normal;

/**
 *  \class Vec3 vec3.hpp "geometry/vec3.hpp"
 *  \brief A vector of three components
 *
 *  Vec3 class represents a vector in 3D space and it is used to represent
 *  a point in tridimensional cartesian space
 *
 *  A Vec3 consist of three coordinates, usually called x, y and z.
 */
class Vec3
{
public:

    /** \brief x component
     *
     * A single precision floating point representing the x component
     * of the vector
     */
    float x;

    /** \brief y component
     *
     * A single precision floating point representing the y component
     * of the vector
     */
    float y;

    /** \brief z component
     *
     * A single precision floating point representing the z component
     * of the vector
     */
    float z;

    /**  \brief Default Constructor
     *
     *  Construct a vector of three elements with x = 0, y = 0 and z = 0
     */
    Vec3();


    /**  \brief Constructor, given x,y and z
     *
     *  Construct a vector of three elements given x, y and z values
     *  \param[in] x A float representing the x component of the vector
     *  \param[in] y A float representing the y component of the vector
     *  \param[in] z A float representing the z component of the vector
     */
    Vec3(float x,float y,float z);

    /**  \brief Constructor, given equal components
     *
     *  Construct a vector of three elements with the same given value
     *
     *  \param[in] xyz A float representing the x, y and z components
     */
    Vec3(float xyz);

    /** \brief Constructor, given a Vec2 and the z value
     *
     *  Construct a vector of three elements given in input a vector of two
     *  elements, in Vec2 format, and the missing z paramter as a float
     *
     *  \param[in] xy A Vec2 representing the x and y components of the vector
     *  \param[in] z A float representing the z component of the vector
     */
    Vec3(Vec2 xy,float z);

    /**  \brief Constructor, given an array
     *
     *  Construct a vector of three elements given an input array
     *
     *  \param[in] xyz An input array of floats, containing x in the first
     *               position (0-based), y in the second and z in the third
     *  \warning It is not checked if \p xyz is a valid pointer nor if its
     *           length is correct
     */
    Vec3(const float* xyz);

    /**  \brief Constructor, given a Normal
     *
     *  Construct a vector given a Normal. The value of the new Vec3 are
     *  identical to the input Normal.
     *
     *  \param n A Normal object
     *  \note Since the Normal class is similar, but also subtle different from
     *        the Vec3 class, they are implemented as two different classes to
     *        avoid undesired casting. For this reason, this constructor is
     *        explicit
     */
    explicit Vec3(Normal n);

    ///Default destructor
    ~Vec3() = default;

    /** \brief Return the length of the vector
     *
     * \return A float representing the length of this vector
     * \sa lengthSquared()
     */
    float length()const;

    /** \brief Return the squared length of the vector
     *
     * \return A float representing the squared length of this vector
     * \sa length()
     */
    float lengthSquared()const;

    /**  \brief Compute the distance from another vector
     *
     *  Compute the euclidean distance between this vector and another one
     *  passed as input, corresponding to the length of the segment connecting
     *  them
     *
     *  \param[in] target A Vec3 representing the target vector from which the
     *             distance should be calculated
     *  \return A float representing the distance from the \p target vector
     */
    float distanceTo(const Vec3& target)const;

    /** \brief Normalize this vector
     *
     * \warning The input length is not checked, a 0-length vector will result
     *  in a division by zero error
     *  \sa is_normalized()
     */
    void normalize();

    /**  \brief Compute the dot product
     *
     *  Compute the dot product of this vector and another one. The dot product
     *  is defined as the cosine of the angle between two vectors.
     *
     *  \param[in] target The target Vec3 used to compute the dot product
     *  \return A float representing the dot product
     *  \sa cross(const Vec3* target, Vec3* output)const
     *  \sa dot(const Normal* target)const
     */
    float dot(const Vec3& target)const;

    /**  \brief Compute the dot product
     *
     *  Compute the dot product of this vector and a normal. The dot product
     *  is defined as the cosine of the angle between two vectors and, in this
     *  case, the second vector is represented by a normal.
     *
     *  \param[in] target The target normal used to compute the dot product
     *  \return A float representing the dot product
     *  \sa cross(const Vec3* target, Vec3* output)const
     *  \sa dot(const Vec3* target)const
     */
    float dot(const Normal& target)const;

    /**  \brief Compute the cross product
     *
     *  Compute the cross product of this vector and another one. The cross
     *  product is defined as the vector normal to the plane containing the two
     *  input vectors
     *
     *  \param[in] target The target Vec3 used to compute the dot product
     *  \param[out] output The Vec3 that will be overwritten with the result
     *              of the cross product
     *  \sa dot(const Vec3* target)const
     */
    void cross(const Vec3& target, Vec3* output)const;

    /**  \brief Compute the cross product
     *
     *  Compute the cross product of this vector and another one. The cross
     *  product is defined as the vector normal to the plane containing the two
     *  input vectors
     *
     *  \param[in] target The target Vec3 used to compute the dot product
     *
     *  \return The Vec3 representing the cross product
     *  \sa dot(const Vec3* target)const
     */
    Vec3 cross(const Vec3& target)const;

    /**  \brief Check if the current vector is normalized
     *
     *  \return A boolean value indicating whether the vector is normalized or
     *          not
     *  \sa normalize()
     */
    bool is_normalized()const;

    /**  \brief Represent this vector with an array
     *
     *  Copy the components of this vector in an array of floats
     *
     *  \param[in] values  An array containing the x value of the vector in the
     *  first position (0-based), the y value in the second and the z value in
     *  the third
     *  \sa toString()
     */
    void toArray(float* values)const;

    /**  \brief Represent this vector with a C-string
     *
     *  Allocate in the heap a C-string and write the components of the vector
     *  as a string
     *
     *  \return An heap allocated char array containing the values of the
     *           vector
     *  \note A char* is allocated on heap and must be deleted
     *  \sa toArray()
     */
    char* toString()const;

    /**  \brief Clamp this vector by restricting it between two boundaries
     *
     *  Restrict the value of the vector in an interval defined by \p min as the
     *  minimum value and \p max as the maximum one
     *
     *  \param[in] min A Vec3 representing the minimum extent of the interval
     *  \param[in] max A Vec3 representing the maximum extent of the interval
     *  \sa saturate()
     */
    void clamp(const Vec3& min, const Vec3& max);

    /**  \brief Clamp this vector in the interval [0-1]
     *
     *  \sa clamp(const Vec3 min, const Vec3 max)
     */
    void saturate();

    /**  \brief Compute the maximum value between this vector and another one
     *
     *  Substitute the maximum value in x, y and z by choosing between the value
     *  of this vector and the one passed as argument
     *
     *  \param[in] vector2 A Vec3 used to compare and choose the x, y and z
     *             values
     *  \sa min(const Vec3 vector2)
     */
    void max(const Vec3& vector2);

    /**  \brief Compute the minimum value between this vector and another one
     *
     *  Substitute the minimum value in x, y and z by choosing between the value
     *  of this vector and the one passed as argument
     *
     *  \param[in] vector2 A Vec3 used to compare and choose the x, y and z
     *             values
     *  \sa max(const Vec3 vector2)
     */
    void min(const Vec3& vector2);

    /**  \brief Flip the vector according to a pivot
     *
     *  Given a vector as a centre of reflection transform this class in the
     *  reflected vector around that centre of reflection. The vector is
     *  pointing toward the centre of reflection. The resulting vector will not.
     *
     *  \param[in] centre A Vec3 representing the centre of reflection
     *  \sa reflect(const Normal centre)
     *  \sa refract(const Vec3 centre)
     */
    void reflect(const Vec3& centre);

    /**  \brief Flip the vector according to a pivot
     *
     *  Given a vector as a centre of reflection transform this class in the
     *  reflected vector around that centre of reflection. The vector is
     *  pointing toward the centre of reflection. The resulting vector will not.
     *
     *  \param[in] centre A Normal representing the centre of reflection
     *  \sa reflect(const Vec3 centre)
     *  \sa refract(const Normal centre)
     */
    void reflect(const Normal& centre);

    /**  \brief Generate the refracted vector
     *
     *  Given a vector that will be treated as a Normal, refract and transform
     *  this class in the refracted vector. The interface normal is the Vec3
     *  passed as input.
     *  If the refracted vector does not exists due to Total Internal Reflection
     *  the class is not transformed and false is returned
     *
     *  \warning Since this method will be used only in the Bdf class, source
     *  vector is assumed to be pointing away from the interface, and so the
     *  resulting transmitted vector
     *
     *  \param[in] interface A Vec3 representing the interface normal
     *  \param[in] eta The index of refraction used for refracting the vector
     *  \return true if the vector was successfully refracted, false otherwise
     *  \sa refract(const Normal& interface, float eta)
     *  \sa reflect(const Vec3 centre)
     */
    bool refract(const Vec3& interface, float eta);

    /**  \brief Generate the refracted vector
     *
     *  Given a Normal representing the interface of a material, refract and
     *  transform this class in the refracted vector.
     *  If the refracted vector does not exists due to Total Internal Reflection
     *  the class is not transformed and false is returned
     *
     *  \warning Since this method will be used only in the Bdf class, source
     *  vector is assumed to be pointing away from the interface, and so the
     *  resulting transmitted vector
     *
     *  \param[in] interface A Vec3 representing the interface normal
     *  \param[in] eta The index of refraction used for refracting the vector
     *  \return true if the vector was successfully refracted, false otherwise
     *  \sa refract(const Vec3& interface, float eta)
     *  \sa reflect(const Normal centre)
     */
    bool refract(const Normal& interface, float eta);

    //------ Operators ---------------------------------------------------------

    ///The addition operation between two vectors
    Vec3 operator+(const Vec3&)const;
    ///The addition operation between a vector and a float
    Vec3 operator+(float)const;
    ///The addition operation between two vectors
    void operator+=(const Vec3&);
    ///The addition operation between a vector and a float
    void operator+=(float);
    ///The subtraction operation between two vectors
    Vec3 operator-(const Vec3&)const;
    ///The subtraction operation between a vector and a float
    Vec3 operator-(float)const;
    ///The subtraction operation between two vectors
    void operator-=(const Vec3&);
    ///The subtraction operation between a vector and a float
    void operator-=(float);
    ///The element-wise multiplication between two vectors
    Vec3 operator*(const Vec3&)const;
    ///The element-wise multiplication between a vector and a float
    Vec3 operator*(float)const;
    ///The element-wise multiplication between two vectors
    void operator*=(const Vec3&);
    ///The element-wise multiplication between a vector and a float
    void operator*=(float);
    ///The element-wise division between two vectors
    Vec3 operator/(const Vec3&)const;
    ///The element-wise division between a vector and a float
    Vec3 operator/(float)const;
    ///The element-wise division between two vectors
    void operator/=(const Vec3&);
    ///The element-wise division between a vector and a float
    void operator/=(float);
    ///The negative of this vector
    Vec3 operator!()const;
    ///The negative of this vector
    Vec3 operator-()const;
    ///Check if two vectors are equal
    bool operator==(const Vec3&)const;
    ///Check if two vector are different
    bool operator!=(const Vec3&)const;
    ///Return the nth component
    float& operator[](int);
    ///Return the nth component, const version
    float operator[](int)const;

    //--------------------------------------------------------------------------

};

/**
 *  \class Normal vec3.hpp "Geometry/vec3.hpp"
 *  \brief A normal composed by three components
 *
 *  Normal class represents a vector in 3D space and it is used to represent
 *  a 3D vector perpendicular to a surface
 *
 *  A Normal consist of three coordinates, usually called x, y and z.
 *  \note Despite the name, a Normal is not guaranteed to be normalized
 */
class Normal
{
public:

    /** \brief X component
     *
     * A single precision floating point representing the x component
     * of the normal
     */
    float x;

    /** \brief Y component
     *
     * A single precision floating point representing the y component
     * of the normal
     */
    float y;

    /** \brief Z component
     *
     * A single precision floating point representing the z component
     * of the normal
     */
    float z;

    /**  \brief Default Constructor
     *
     *  Construct a normal of three elements with x = 0, y = 0 and z = 0
     */
    Normal();

    /**  \brief Constructor, given x,y and z
     *
     *  Construct a normal of three elements given x, y and z values
     *
     *  \param[in] x A float representing the x component of the normal
     *  \param[in] y A float representing the y component of the normal
     *  \param[in] z A float representing the z component of the normal
     */
    Normal(float x,float y,float z);

    /**  \brief Constructor, given equal components
     *
     *  Construct a normal of three elements with the same given value
     *
     *  \param[in] xyz A float representing the x, y and z components
     */
    Normal(float xyz);

    /** \brief Constructor, given a Vec2 and the z value
     *
     *  Construct a normal of three elements given in input a vector of two
     *  elements, in Vec2 format, and the missing z paramter as a float
     *
     *  \param[in] xy A Vec2 representing the x and y components of the normal
     *  \param[in] z A float representing the z component of the normal
     */
    Normal(Vec2 xy,float z);

    /**  \brief Constructor, given an array
     *
     *  Construct a normal of three elements given an input array
     *
     *  \param[in] xyz An input array of floats, containing x in the first
     *               position (0-based), y in the second and z in the third
     *  \warning It is not checked if \p xyz is a valid pointer nor if its
     *           length is correct
     */
    Normal(const float* xyz);

    /**  \brief Constructor, given a Vec3
     *
     *  Construct a normal given a vector. The value of the new normal are
     *  identical to the input vector.
     *
     *  \param v A Vec3 object
     *  \note Since the Vec3 class is similar, but also subtle different from
     *        the Normal class, they are implemented as two different classes to
     *        avoid undesired casting. For this reason, this constructor is
     *        explicit
     */
    explicit Normal(const Vec3 v);

    ///Default destructor
    ~Normal() = default;

    /**  \brief Compute the dot product of this normal and another one.
     *
     *  The dot product is defined as the cosine of the angle between two
     *  normals.
     *
     *  \param[in] target The target Normal used to compute the dot product
     *  \return A float representing the dot product
     *  \sa dot(const Vec3* target)const
     */
    float dot(const Normal& target)const;

    /**  \brief Compute the dot product of this normal and a vector
     *
     *  The dot product is defined as the cosine of the angle between two
     *  vectors and, in this case, one vector is represented by a normal.
     *
     *  \param[in] target The target vector used to compute the dot product
     *  \return A float representing the dot product
     *  \sa dot(const Normal* target)const
     */
    float dot(const Vec3& target)const;

    /** \brief Returns the length of the normal
     *
     * \return A float representing the length of this normal
     * \sa lengthSquared()
     */
    float length() const;

    /** \brief Returns the squared length of the normal
     *
     * \return A float representing the squared length of this normal
     * \sa length()
     */
    float lengthSquared()const;

    /**  \brief Compute the distance to another normal
     *  Compute the euclidean distance between this normal and another one
     *  passed as input, corresponding to the length of the segment connecting
     *  them
     *
     *  \param[in] target A Normal representing the target normal from which the
     *             distance should be calculated
     *  \return A float representing the distance from the \p target normal
     */
    float distanceTo(const Normal& target)const;

    /** \brief Normalize this normal
     *  \note Despite the name, a Normal is not guaranteed to be normalized
     *  \warning The input length is not checked, a 0-length vector will result
     *  in a division by zero error
     *  \sa is_normalized()
     */
    void normalize();

    /**  \brief Check if the current normal is normalized
     *
     *  \return A boolean value indicating whether the normal is normalized or
     *          not
     *  \note Despite the name, a Normal is not guaranteed to be normalized
     *  \sa normalize()
     */
    bool is_normalized()const;

    /**  \brief Represent this normal with an array
     *
     *  Copy the components of this normal in an array of float, heap allocated
     *
     *  \param[in] values An array containing the x value of the normal in the
     *  first position (0-based), the y value in the second and the z value in
     *  the third
     *  \sa toString()
     */
    void toArray(float* values) const;

    /**  \brief Represent this normal with a C-string
     *
     *  Allocate in the heap a C-string and write the components of the normal
     *  as a string
     *
     *  \return An heap allocated char array containing the values of the
     *           normal
     *  \note The returned char* is allocated on heap and MUST be deleted
     *  \sa toArray()
     */
    char* toString() const;

    /**  \brief Clamp this normal by restricting it between two boundaries
     *
     *  Restrict the value of the normal in an interval defined by \p min as the
     *  minimum value and \p max as the maximum one
     *
     *  \param[in] min A Vec3 representing the minimum extent of the interval
     *  \param[in] max A Vec3 representing the maximum extent of the interval
     *  \sa saturate()
     */
    void clamp(const Vec3& min, const Vec3& max);

    /**  \brief Clamp this normal in the interval [0-1]
     *   \sa clamp(const Vec3* min, const Vec3* max)
     */
    void saturate();

    /**  \brief Compute the maximum value between this normal and another one
     *
     *  Substitute the maximum value in x, y and z by choosing between the value
     *  of this normal and the one passed as argument
     *
     *  \param[in] n A Normal used to compare and choose the x, y and z
     *             values
     *  \sa min(const Normal n)
     */
    void max(const Normal& n);

    /**  \brief Compute the minimum value between this normal and another one
     *
     *  Substitute the minimum value in x, y and z by choosing between the value
     *  of this normal and the one passed as argument
     *
     *  \param[in] n A Normal used to compare and choose the x, y and z
     *             values
     *  \sa max(const Normal n)
     */
    void min(const Normal& n);


    //------ Operators ---------------------------------------------------------

    ///The addition operation between two normals
    Normal operator+(const Normal&)const;
    ///The addition operation between a normal and a float
    Normal operator+(float)const;
    ///The addition operation between two normals
    void operator+=(const Normal&);
    ///The addition operation between a normal and a float
    void operator+=(float);
    ///The subtraction operation between two normals
    Normal operator-(const Normal&)const;
    ///The subtraction operation between a normal and a float
    Normal operator-(float)const;
    ///The subtraction operation between two normals
    void operator-=(const Normal&);
    ///The subtraction operation between a normal and a float
    void operator-=(float);
    ///The element-wise multiplication between two normals
    Normal operator*(const Normal&)const;
    ///The element-wise multiplication between a normal and a float
    Normal operator*(float)const;
    ///The element-wise multiplication between two normals
    void operator*=(const Normal&);
    ///The element-wise multiplication between a normal and a float
    void operator*=(float);
    ///The element-wise division between two normals
    Normal operator/(const Normal&)const;
    ///The element-wise division between a normal and a float
    Normal operator/(float)const;
    ///The element-wise division between two normals
    void operator/=(const Normal&);
    ///The element-wise division between a normal and a float
    void operator/=(float);
    ///The negative of this normal
    Normal operator!()const;
    ///The negative of this normal
    Normal operator-()const;
    ///Check if two normals are equal
    bool operator==(const Normal&)const;
    ///Check if two normals are different
    bool operator!=(const Normal&)const;
    ///Return the nth component
    float& operator[](int);
    ///Return the nth component, const version
    float operator[](int)const;

    //--------------------------------------------------------------------------
};


//++++++++++++++++++++++++++++//INLINE FUNCTIONS//++++++++++++++++++++++++++++//

/**  \brief Compute the dot product
 *
 *  Compute the dot product between two input vectors. The dot product
 *  is defined as the cosine of the angle between the two vectors.
 *
 *  \param[in] source The first Vec3 used to compute the dot product
 *  \param[in] target The second Vec3 used to compute the dot product
 *  \return A float representing the dot product
 *  \sa dot   (const Vec3   source, const Normal target)
 *  \sa dot   (const Normal source, const Vec3   target)
 *  \sa dot   (const Normal source, const Normal target)
 *  \sa cross (const Vec3   source, const Vec3   target)
 *  \sa absdot(const Vec3   source, const Vec3   target)
 */
inline float dot   (const Vec3&   source, const Vec3&   target)
{
    return ((source.x * target.x) +
            (source.y * target.y) +
            (source.z * target.z));
}

/**  \brief Compute the dot product
 *
 *  Compute the dot product between a vector and a normal. The dot product
 *  is defined as the cosine of the angle between two vectors.
 *
 *  \param[in] source The Vec3 used to compute the dot product
 *  \param[in] target The Normal used to compute the dot product
 *  \return A float representing the dot product
 *  \sa dot   (const Vec3   source, const Vec3   target)
 *  \sa dot   (const Vec3   source, const Normal target)
 *  \sa dot   (const Normal source, const Vec3   target)
 *  \sa dot   (const Normal source, const Normal target)
 *  \sa cross (const Vec3   source, const Vec3   target)
 *  \sa absdot(const Vec3   source, const Normal target)
 */
inline float dot   (const Vec3&   source, const Normal& target)
{
    return ((source.x * target.x) +
            (source.y * target.y) +
            (source.z * target.z));
}

/**  \brief Compute the dot product
 *
 *  Compute the dot product between a vector and a normal. The dot product
 *  is defined as the cosine of the angle between two vectors.
 *
 *  \param[in] source The Normal used to compute the dot product
 *  \param[in] target The Vec3 used to compute the dot product
 *  \return A float representing the dot product
 *  \sa dot   (const Vec3   source, const Vec3   target)
 *  \sa dot   (const Vec3   source, const Normal target)
 *  \sa dot   (const Normal source, const Normal target)
 *  \sa cross (const Vec3   source, const Vec3   target)
 *  \sa absdot(const Normal source, const Vec3   target)
 */
inline float dot   (const Normal& source, const Vec3&   target)
{
    return ((source.x * target.x) +
            (source.y * target.y) +
            (source.z * target.z));
}

/**  \brief Compute the dot product
 *
 *  Compute the dot product between two normals. The dot product
 *  is defined as the cosine of the angle between the two normals.
 *
 *  \param[in] source The first Normal used to compute the dot product
 *  \param[in] target The second Normal used to compute the dot product
 *  \return A float representing the dot product
 *  \sa dot   (const Vec3   source, const Normal target)
 *  \sa dot   (const Normal source, const Vec3   target)
 *  \sa dot   (const Vec3   source, const Vec3   target)
 *  \sa cross (const Vec3   source, const Vec3   target)
 *  \sa absdot(const Normal source, const Normal target)
 */
inline float dot (const Normal& source, const Normal& target)
{
    return ((source.x * target.x) +
            (source.y * target.y) +
            (source.z * target.z));
}

/**  \brief Compute the abolute value of the dot product
 *
 *  Compute the abolute value of the dot product between two input vectors.
 *  The dot product is defined as the cosine of the angle between the two
 *  vectors.
 *
 *  \param[in] source The first Vec3 used to compute the dot product
 *  \param[in] target The second Vec3 used to compute the dot product
 *  \return A float representing the absolute value of the dot product
 *  \sa absdot(const Vec3   source, const Normal target)
 *  \sa absdot(const Normal source, const Vec3   target)
 *  \sa absdot(const Normal source, const Normal target)
 *  \sa cross (const Vec3   source, const Vec3   target)
 *  \sa dot   (const Vec3   source, const Vec3   target)
 */
inline float absdot(const Vec3& source, const Vec3& target)
{
    return fabsf(dot(source,target));
}

/**  \brief Compute the abolute value of the dot product
 *
 *  Compute the abolute value of the dot product between a vector and a normal.
 *  The dot product is defined as the cosine of the angle between two
 *  vectors.
 *
 *  \param[in] source The first Vec3 used to compute the dot product
 *  \param[in] target The Normal used to compute the dot product
 *  \return A float representing the absolute value of the dot product
 *  \sa absdot(const Vec3   source, const Vec3   target)
 *  \sa absdot(const Normal source, const Vec3   target)
 *  \sa absdot(const Normal source, const Normal target)
 *  \sa cross (const Vec3   source, const Vec3   target)
 *  \sa dot   (const Vec3   source, const Normal target)
 */
inline float absdot(const Vec3& source, const Normal& target)
{
    return fabsf(dot(source,target));
}

/**  \brief Compute the abolute value of the dot product
 *
 *  Compute the abolute value of the dot product between a vector and a normal.
 *  The dot product is defined as the cosine of the angle between two
 *  vectors.
 *
 *  \param[in] source The first Vec3 used to compute the dot product
 *  \param[in] target The Normal used to compute the dot product
 *  \return A float representing the absolute value of the dot product
 *  \sa absdot(const Vec3   source, const Vec3   target)
 *  \sa absdot(const Vec3   source, const Normal target)
 *  \sa absdot(const Normal source, const Normal target)
 *  \sa cross (const Vec3   source, const Vec3   target)
 *  \sa dot   (const Normal source, const Vec3   target)
 */
inline float absdot(const Normal& source, const Vec3& target)
{
    return fabsf(dot(source,target));
}

/**  \brief Compute the abolute value of the dot product
 *
 *  Compute the abolute value of the dot product between two input normals.
 *  The dot product is defined as the cosine of the angle between the two
 *  normals.
 *
 *  \param[in] source The first Normal used to compute the dot product
 *  \param[in] target The second Normal used to compute the dot product
 *  \return A float representing the absolute value of the dot product
 *  \sa absdot(const Vec3   source, const Vec3   target)
 *  \sa absdot(const Vec3   source, const Normal target)
 *  \sa absdot(const Normal source, const Vec3   target)
 *  \sa cross (const Vec3   source, const Vec3   target)
 *  \sa dot   (const Normal source, const Normal target)
 */
inline float absdot(const Normal& source, const Normal& target)
{
    return fabsf(dot(source,target));
}

/**  \brief Compute the cross product
 *
 *  Compute the cross product of two vectors. The cross
 *  product is defined as the vector normal to the plane containing the two
 *  input vectors
 *
 *  \param[in] source The first Vec3 used to compute the dot product
 *  \param[in] target The second Vec3 used to compute the dot product
 *  \return A Vec3 representing the cross product
 *  \sa dot   (const Vec3 source, const Vec3 target)
 */
inline Vec3  cross (const Vec3& source, const Vec3& target)
{
    return Vec3(source.y * target.z - source.z * target.y,
                source.z * target.x - source.x * target.z,
                source.x * target.y - source.y * target.x);
}

/** \brief Normalize this vector
 *
 *  \param[in] v A pointer to the Vec3 that will be normalized
 *  \warning The input length is not checked, a 0-length vector will result
 *  in a division by zero error
 *  \return A normalized version of this vector
 */
inline Vec3 normalize(const Vec3& v)
{
    float len;
    float len2;
    len2 = v.x * v.x + v.y * v.y + v.z * v.z;
    if(len2>1.f-1E-5f && len2<1.f+1E-5f) //already normalized
        return v;
    else
        len = sqrtf(len2);
#ifdef DEBUG
    if(len==0)
    {
        Console.critical(MESSAGE_NORMALIZE_ZERO);
        return Vec3();
    }
#endif
    len = 1/len;
    return Vec3(v.x * len,
                v.y * len,
                v.z * len);
}

/** \brief Normalize the input normal
 *
 *  \param[in] n The Normal that will be normalized
 *  \warning The input length is not checked, a 0-length normal will result
 *  in a division by zero error
 */
inline Normal normalize(const Normal& n)
{
    float len;
    float len2;
    len2 = n.x * n.x + n.y * n.y + n.z * n.z;
    if(len2>1.f-1E-5f && len2<1.f+1E-5f) //already normalized
        return n;
    else
        len = sqrtf(len2);
#ifdef DEBUG
    if(len==0)
    {
        Console.critical(MESSAGE_NORMALIZE_ZERO_NORMAL);
        return Normal();
    }
#endif
    len = 1/len;
    return Normal(n.x * len,
                  n.y * len,
                  n.z * len);
}

/**  \brief Compute the distance between two vectors
 *
 *  Compute the euclidean distance between two vectors, defined as the length of
 *  the segment connecting them
 *
 *  \param[in] vec1 A Vec3 representing the vector from which the
 *             distance should be calculated
 *  \param[in] vec2 A Vec3 representing the vector to which the
 *             distance should be calculated
 *  \return A float representing the distance from \p vec1 to \p vec2
 */
inline float distance(const Vec3& vec1, const Vec3& vec2)
{
    float x = vec2.x - vec1.x;
    float y = vec2.y - vec1.y;
    float z = vec2.z - vec1.z;

    return std::sqrt((x * x) + (y * y) + (z*z));
}

/**  \brief Compute the distance between two normals
 *
 *  Compute the euclidean distance between two normals, as the length of the
 *  segment connecting them
 *
 *  \param[in] n1 A Normal representing the normal from which the
 *             distance should be calculated
 *  \param[in] n2 A Normal representing the normal to which the
 *             distance should be calculated
 *  \return A float representing the distance from \p n1 to \p n2
 */
inline float distance(const Normal& n1, const Normal& n2)
{
    float x = n2.x - n1.x;
    float y = n2.y - n1.y;
    float z = n2.z - n1.z;

    return std::sqrt((x * x) + (y * y) + (z*z));
}

/** \brief Clamp the input vector by restricting it between two boundaries
 *
 *  Restrict the value of the vector in an interval defined by \p min as the
 *  minimum value and \p max as the maximum one
 *
 *  \param[in] vector The Vec3 that will be clamped
 *  \param[in] min A Vec3 representing the minimum extent of the interval
 *  \param[in] max A Vec3 representing the maximum extent of the interval
 *  \return The clamped Vec3
 *  \sa saturate(const Vec3 vector)
 */
inline Vec3 clamp(const Vec3& vector, const Vec3& min, const Vec3& max)
{
    float x,y,z;
    if (vector.x < min.x) x = min.x;
    else if (vector.x > max.x) x = max.x;
    else x = vector.x;
    if (vector.y < min.y) y = min.y;
    else if (vector.y > max.y) y = max.y;
    else y = vector.y;
    if (vector.z < min.z) z = min.z;
    else if (vector.z > max.z) z = max.z;
    else z = vector.z;
    return Vec3(x,y,z);
}

/** \brief Clamp this vector in the interval [0-1]
 *
 *  \param[in] vector The Vec3 that will be clamped
 *  \return The clamped Vec3
 *  \sa clamp(const Vec3 vector, const Vec3 min, const Vec3 max)
 */
inline Vec3 saturate(const Vec3& vector)
{
    float x,y,z;
    if (vector.x < .0f) x = .0f;
    else if (vector.x > 1.0f) x = 1.0f;
    else x = vector.x;
    if (vector.y < .0f) y = .0f;
    else if (vector.y > 1.0f) y = 1.0f;
    else y = vector.y;
    if (vector.z < .0f) z = .0f;
    else if (vector.z > 1.0f) z = 1.0f;
    else z = vector.z;
    return Vec3(x,y,z);
}

/** \brief Clamp the input normal by restricting it between two boundaries
 *
 *  Restrict the value of the normal in an interval defined by \p min as the
 *  minimum value and \p max as the maximum one
 *
 *  \param[in] n The Normal that will be clamped
 *  \param[in] min A Vec3 representing the minimum extent of the interval
 *  \param[in] max A Vec3 representing the maximum extent of the interval
 *  \return The clamped normal
 *  \sa saturate(const Normal n)
 */
inline Normal clamp(const Normal& n, const Vec3& min, const Vec3& max)
{
    float x,y,z;
    if (n.x < min.x) x = min.x;
    else if (n.x > max.x) x = max.x;
    else x = n.x;
    if (n.y < min.y) y = min.y;
    else if (n.y > max.y) y = max.y;
    else y = n.y;
    if (n.z < min.z) z = min.z;
    else if (n.z > max.z) z = max.z;
    else z = n.z;
    return Normal(x,y,z);
}

/** \brief Clamp this normal in the interval [0-1]
 *
 *  \param[in] n The Normal that will be clamped
 *  \return The clamped normal
 *  \sa clamp(const Normal n, const Vec3 min, const Vec3 max)
 */
inline Normal saturate(const Normal& n)
{
    float x,y,z;
    if (n.x < .0f) x = .0f;
    else if (n.x > 1.0f) x = 1.0f;
    else x = n.x;
    if (n.y < .0f) y = .0f;
    else if (n.y > 1.0f) y = 1.0f;
    else y = n.y;
    if (n.z < .0f) z = .0f;
    else if (n.z > 1.0f) z = 1.0f;
    else z = n.z;
    return Normal(x,y,z);
}

/** \brief Compute the maximum value between two vectors
 *
 *  Return a vector containing the maximum value in x, y and z by choosing
 *  between the value of the two input vectors
 *
 *  \param[in] v1 A Vec3 used to compare and choose the x, y and z values
 *  \param[in] v2 A Vec3 used to compare and choose the x, y and z values
 *  \return A Vec3 containing the maximum value of the two input vectors
 *  \sa min(const Vec3 v1, const Vec3 v2)
 */
inline Vec3 max(const Vec3& v1, const Vec3& v2)
{
    return Vec3(max(v1.x,v2.x),max(v1.y,v2.y),max(v1.z,v2.z));
}

/** \brief Compute the minimum value between two vectors
 *
 *  Return a vector containing the minimum value in x, y and z by choosing
 *  between the value of the two input vectors
 *
 *  \param[in] v1 A Vec3 used to compare and choose the x, y and z values
 *  \param[in] v2 A Vec3 used to compare and choose the x, y and z values
 *  \return A Vec3 containing the minimum value of the two input vectors
 *  \sa max(const Vec3 v1, const Vec3 v2)
 */
inline Vec3 min(const Vec3& v1, const Vec3& v2)
{
    return Vec3(min(v1.x,v2.x),min(v1.y,v2.y),min(v1.z,v2.z));
}

/** \brief Compute the maximum value between two normals
 *
 *  Return a normal containing the maximum value in x, y and z by choosing
 *  between the value of the two input normal
 *
 *  \param[in] n1 A Normal used to compare and choose the x, y and z values
 *  \param[in] n2 A Normal used to compare and choose the x, y and z values
 *  \return A Normal containing the maximum value of the two input normals
 *  \sa min(const Normal n1, const Normal n2)
 */
inline Normal max(const Normal& n1, const Normal& n2)
{
    return Normal(max(n1.x,n2.x),max(n1.y,n2.y),max(n1.z,n2.z));
}


/** \brief Compute the minimum value between two normals
 *
 *  Return a normal containing the minimum value in x, y and z by choosing
 *  between the value of the two input normals
 *
 *  \param[in] n1 A Normal used to compare and choose the x, y and z values
 *  \param[in] n2 A Normal used to compare and choose the x, y and z values
 *  \return A Normal containing the minimum value of the two input normals
 *  \sa min(const Normal v1, const Normal v2)
 */
inline Normal min(const Normal& n1, const Normal& n2)
{
    return Normal(min(n1.x,n2.x),min(n1.y,n2.y),min(n1.z,n2.z));
}

/**  \brief Flip the vector according to a pivot
 *
 *  Given a vector as a centre of reflection computes the reflected vector
 *  around the centre of reflection. The source vector is condidered as
 *  pointing toward the centre of reflection. The resulting vector will not.
 *
 *  \param[in] source The vector to flip
 *  \param[in] centre A Vec3 representing the centre of reflection
 *  \return The reflected vector
 *  \sa reflect(const Vec3 source, const Vec3 centre)
 */
inline Vec3 reflect(const Vec3& source, const Vec3& centre)
{
#ifdef DEBUG
    if(!centre.is_normalized())
        Console.warning(MESSAGE_REFLECT_NONORMALIZED);
#endif
    float dot = source.dot(centre);
    return Vec3(source.x - ((2 * dot) * centre.x),
                source.y - ((2 * dot) * centre.y),
                source.z - ((2 * dot) * centre.z));
}

/**  \brief Flip the vector according to a pivot
 *
 *  Given a vector as a centre of reflection computes the reflected vector
 *  around the centre of reflection. The source vector is condidered as
 *  pointing toward the centre of reflection. The resulting vector will not.
 *
 *  \param[in] source The vector to flip
 *  \param[in] centre A Normal representing the centre of reflection
 *  \return The reflected vector
 *  \sa reflect(const Vec3 source, const Normal centre)
 */
inline Vec3 reflect(const Vec3& source, const Normal& centre)
{
#ifdef DEBUG
    if(!centre.is_normalized())
        Console.warning(MESSAGE_REFLECT_NONORMALIZED);
#endif
    float dot = source.dot(centre);
    return Vec3(source.x - ((2 * dot) * centre.x),
                source.y - ((2 * dot) * centre.y),
                source.z - ((2 * dot) * centre.z));
}

/**  \brief Generate the refracted vector
 *
 *  Given a vector that will be treated as a Normal, refract and transform
 *  the input vector in the refracted vector. The interface normal is the Vec3
 *  passed as input.
 *  If the refracted vector does not exists due to Total Internal Reflection
 *  (0,0,0) is returned
 *
 *  \warning Since this method will be used only in the Bdf class, source vector
 *  is assumed to be pointing away from the interface, and so the resulting
 *  transmitted vector
 *
 *  \param[in] source The Vec3 that will be transformed
 *  \param[in] interface A Vec3 representing the interface normal
 *  \param[in] eta The index of refraction used for refracting the vector
 *  \return The refracted vector, a zero length vector otherwise
 *  \sa refract(const Vec3 source, const Normal interface, float eta)
 *  \sa reflect(const Vec3 source, const Vec3 centre)
 */
inline Vec3 refract(const Vec3& source, const Vec3& interface, float eta)
{
#ifdef DEBUG
    if(!interface.is_normalized())
        Console.warning(MESSAGE_REFRACT_NONORMALIZED);
#endif
    const float cosi = dot(source,interface); //cos incident
    const float sin2i = max(0.f,(1.f-cosi*cosi));
    const float sin2t = sin2i*eta*eta;
    if(sin2t>1.f) //bail out if tir
        return Vec3(0.f,0.f,0.f);
    else
    {
        Vec3 retval;
        const float cos2t = 1.f - sin2t; //cos2t transmitted
        const float cost = sqrtf(cos2t);
        retval = -source*eta;
        retval += interface*(cosi*eta-cost);
        return retval;
    }
}

/**  \brief Generate the refracted vector
 *
 *  Given a vector that will be treated as a Normal, refract and transform
 *  the input vector in the refracted vector. The interface normal is the Vec3
 *  passed as input.
 *  If the refracted vector does not exists due to Total Internal Reflection
 *  (0,0,0) is returned
 *
 *  \warning Since this method will be used only in the Bdf class, source vector
 *  is assumed to be pointing away from the interface, and so the resulting
 *  transmitted vector
 *
 *  \param[in] source The Vec3 that will be transformed
 *  \param[in] interface A Vec3 representing the interface normal
 *  \param[in] eta The index of refraction used for refracting the vector
 *  \return The refracted vector, a zero length vector otherwise
 *  \sa refract(const Vec3 source, const Vec3 interface, float eta)
 *  \sa reflect(const Vec3 source, const Vec3 centre)
 */
inline Vec3 refract(const Vec3& source, const Normal& interface, float eta)
{
#ifdef DEBUG
    if(!interface.is_normalized())
        Console.warning(MESSAGE_REFRACT_NONORMALIZED);
#endif
    const float cosi = dot(source,interface); //cos incident
    const float sin2i = max(0.f,(1.f-cosi*cosi));
    const float sin2t = sin2i*eta*eta;
    if(sin2t>1.f) //bail out if tir
        return Vec3(0.f,0.f,0.f);
    else
    {
        Vec3 retval;
        const float cos2t = 1.f - sin2t; //cos2t transmitted
        const float cost = sqrtf(cos2t);
        retval = -source*eta;
        retval += (Vec3)(interface*(cosi*eta-cost));
        return retval;
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

#endif
