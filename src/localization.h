/**
 *  \cond
 *  No documentation for the strings
 */

#ifndef __LOCALIZATION_H__
#define __LOCALIZATION_H__

//X is the caller, i.e. MESSAGE_NOMEMORY("KdTree building")
#define MESSAGE_NOMEMORY(X) "Out of memory [ " X " ]"

#define MESSAGE_MAXASSETNUMBER "Can't add more assets"

#define MESSAGE_MISSING_EXTENSION "Missing extension in filename."\
                                  " File will be saved as .ppm"

#define MESSAGE_MATRIX4_NULLINIT "Initializing a Matrix4 with a NULL pointer "\
                                 "to array. Matrix4 was left uninitialized"

#define MESSAGE_UPVECTOR_NOTUNIT "Up camera vector is not normalized." \
                                 "Normalizing now."

#define MESSAGE_NAN(X) "Trying to construct a " X " with a NaN value"

#define MESSAGE_INFINITY(X) "Trying to construct a " X " with an infinity value"

#define MESSAGE_NULLPOINTER(X) "Initializing a " X " with a NULL pointer to "\
                         "array. " X " was created with the default constructor"

#define MESSAGE_NORMALIZE_ZERO "Trying to normalize a zero-length vector"

#define MESSAGE_REFLECT_NONORMALIZED "Reflecting around a non normalized centre"

#define MESSAGE_DIVISIONBY0 "Division by zero"

#define MESSAGE_WORLD_AABB_NULL_MATRIX "Trying to generate a world-space AABB "\
                                       "with a NULL matrix"

#define MESSAGE_LINEAR_EQUATION_IMPOSSIBLE "Trying to solve ax+b=0 with a=0"

#define MESSAGE_MISSING_CAMERA "Missing camera"

#define MESSAGE_MISSING_FILTER "Missing filter"

#define MESSAGE_WIDTH_MULTIPLE "Width must be a multiple of %d"

#define MESSAGE_NUMTHREADS "Using %d rendering threads"

#endif


/**
 *  \endcond
 */
