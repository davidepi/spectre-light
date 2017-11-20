/**
 *  \cond
 *  No documentation for the strings
 */

#ifndef __LOCALIZATION_H__
#define __LOCALIZATION_H__

//X is the caller, i.e. MESSAGE_NOMEMORY("KdTree building")
#define MESSAGE_NOMEMORY(X) "Out of memory [ " X " ]"

#define MESSAGE_MAXASSETNUMBER "Can't add more assets"

#define MESSAGE_MAXTRISNUMBER "Reached the limit of triangles per mesh"

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

#define MESSAGE_REFRACT_NONORMALIZED "Refracting around a non normalized "\
                                     "interface"

#define MESSAGE_DIVISIONBY0 "Division by zero"

#define MESSAGE_WORLD_AABB_NULL_MATRIX "Trying to generate a world-space AABB "\
                                       "with a NULL matrix"

#define MESSAGE_LINEAR_EQUATION_IMPOSSIBLE "Trying to solve ax+b=0 with a=0"

#define MESSAGE_MISSING_CAMERA "Missing camera"

#define MESSAGE_MISSING_FILTER "Missing filter"

#define MESSAGE_MISSING_INTEGRATOR "Missing integrator"

#define MESSAGE_MISSING_SAMPLER "Missing sampler"

#define MESSAGE_WIDTH_MULTIPLE "Width must be a multiple of %d"

#define MESSAGE_CHANGED_SPP "Samples per pixel should be a perfect square."\
                            " Using %d samples"

#define MESSAGE_NUMTHREADS "Using %d rendering threads"

#define MESSAGE_W_DENIED "The folder \"%s\" is not writable or does not exists"

#define MESSAGE_W_DENIED_RC "The output file was writable at startup, but now "\
                            "it is not anymore."

#define MESSAGE_DEGENERATE_SPHERE "Trying to create a degenerate sphere, with "\
                                  "radius less than or equal to zero"

#define MESSAGE_DEGENERATE_BOX "Trying to create a degenerate box, with edges "\
                                "less than or equal to zero"

#define MESSAGE_STARTED_PARSING "Parsing started..."

#define MESSAGE_ENDED_PARSING "Parsing ended (%d ms)"

#define MESSAGE_SPECTRUM_NAN "Spectrum contains one or more NaNs"

#define MESSAGE_SPECTRUM_INF "Spectrum contains one or more infinite values"

#define MESSAGE_SPECTRUM_NEG "Spectrum contains one or more negative values"

#define MESSAGE_RENDERTIME "Rendering ended (%s)"

#define MESSAGE_IMAGEO "Saving image..."

#define MESSAGE_BYE "Bye :)"

#endif


/**
 *  \endcond
 */
