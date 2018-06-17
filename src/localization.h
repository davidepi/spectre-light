/**
 *  \cond
 *  No documentation for the strings
 */

#ifndef __LOCALIZATION_H__
#define __LOCALIZATION_H__

//X is the caller, i.e. MESSAGE_NOMEMORY("KdTree building")
#define MESSAGE_NOMEMORY(X) "Out of memory [ " X " ]"

#define MESSAGE_MAXASSETNUMBER "Can't add more assets"

#define MESSAGE_MAXLIGHTSNUMBER "Reached the maximum number of lights for the"\
"current scene: %d"

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

#define MESSAGE_NORMALIZE_ZERO_NORMAL "Trying to normalize a zero-length normal"

#define MESSAGE_REFLECT_NONORMALIZED "Reflecting around a non normalized centre"

#define MESSAGE_REFRACT_NONORMALIZED "Refracting around a non normalized "\
                                     "interface"

#define MESSAGE_BSDF_NONORMALIZED "View vector(wo) in bsdf is not normalized"

#define MESSAGE_DIVISIONBY0 "Division by zero"

#define MESSAGE_WORLD_AABB_NULL_MATRIX "Trying to generate a world-space AABB "\
                                       "with a NULL matrix"

#define MESSAGE_LINEAR_EQUATION_IMPOSSIBLE "Trying to solve ax+b=0 with a=0"

#define MESSAGE_MISSING_CAMERA "Missing camera"

#define MESSAGE_MISSING_FILTER "Missing filter"

#define MESSAGE_MISSING_INTEGRATOR "Missing integrator"

#define MESSAGE_MISSING_SAMPLER "Missing sampler"

#define MESSAGE_WIDTH_MULTIPLE "Width must be a multiple of %d"

#define MESSAGE_RESOLUTION_CHANGED "Rendered image width should be a multiple "\
"of %d for performance reasons. Resolution has been adjusted to %dx%d"

#define MESSAGE_SPP_CHANGED "While using a Stratified Sampler, samples per " \
"pixel should be a perfect square. Using %d samples"

#define MESSAGE_NUMTHREADS "Using %d rendering threads"

#define MESSAGE_OUTPUT_ISFOLDER "Output file %s exists and is a folder"

#define MESSAGE_W_DENIED "The folder \"%s\" is not writable or does not exists"

#define MESSAGE_W_DENIED_RC "The output file was writable at startup, but now "\
                            "it is not anymore."

#define MESSAGE_DEGENERATE_SPHERE "Trying to create a degenerate sphere, with "\
                                  "radius less than or equal to zero"

#define MESSAGE_DEGENERATE_BOX "Trying to create a degenerate box, with edges "\
                                "less than or equal to zero"

#define MESSAGE_DEBUG "Debug (slow) mode"

#define MESSAGE_STARTED_PARSING "Parsing started..."

#define MESSAGE_ENDED_PARSING "Parsing ended (%d ms)"

#define MESSAGE_SPECTRUM_NAN "Spectrum contains one or more NaNs"

#define MESSAGE_SPECTRUM_INF "Spectrum contains one or more infinite values"

#define MESSAGE_SPECTRUM_NEG "Spectrum contains one or more negative values"

#define MESSAGE_RENDERTIME "Rendering ended (%s)"

#define MESSAGE_IMAGEO "Saving image..."

#define MESSAGE_BYE "Bye :)"

#define MESSAGE_INPUT_FILE "Write input file path or q to exit"

#define MESSAGE_COMPARE_INF "Comparing infinite values could lead to "\
"undefined results"

#define MESSAGE_IM_UNSUPPORTED "Output file format is not supported, the "\
"result will be a NetPBM image"

#define MESSAGE_IM_OUT "ImageMagick not found, output will be in NetPBM format. The image will be saved as %s"

#define MESSAGE_IM_CHANN "Unsupported number of channels in file %s"

#define MESSAGE_IM_NOFLOAT "Quantum type of ImageMagick is not a float. "\
"Read images will probably have wrong values"

//max 16 char, otherwise change comments in the utility.hpp, format_seconds func
#define MESSAGE_MORE_THAN_100_DAYS "more than 100d"

//max 16 char, otherwise change comments in the utility.hpp, format_seconds func
#define MESSAGE_LESS_THAN_1_SECOND "less than 1s"

#define MESSAGE_SINGLE_BRDF_WRONG "Added a BTDF where a BRDF was expected in "\
"class SingleBRDF"

#define MESSAGE_TEXTURE_NOT_FOUND "Texture %s not found in library"

#define MESSAGE_SHAPE_NOT_FOUND "Shape \"%s\" not found in any of the .obj parsed"

#define MESSAGE_INPUT_ERROR "Unable to open file %s: %s"

#define MESSAGE_TEXTURE_ERROR "Unable to load texture %s"

#define MESSAGE_TEXTURE_DUPLICATE "Texture %s is already in library and won't"\
" be added"

#define MESSAGE_TEXTURE_ERROR_2ND MESSAGE_TEXTURE_ERROR ". But the texture "\
"was readable when parsed"

#define MESSAGE_TEXTURE_NOT_FOUND_MTL "Texture %s not found in library; to be "\
"used in material %s"

#define MESSAGE_TEXTURE_POWER2 "Loaded texture %s width and height are not "\
"equal or not a power of two"

#define MESSAGE_METAL_NOT_SUPPORTED "Metal %c%c is not supported."\
" Using the default Au"

#define MESSAGE_SYNTAX_ERROR "Syntax error: Unexpected character %c"

#define MESSAGE_DUPLICATE_TEXTURE "Duplicate name for texture %s. The newest " \
"was not inserted into the library"

#define MESSAGE_DUPLICATE_MATERIAL "Duplicate name for material %s. The newest "\
"was not inserted into the library"

#define MESSAGE_DUPLICATE_SHAPE "Duplicate name for shape %s. Shape was not "\
"inserted"

#define MESSAGE_INDEX_OBJ "Error while parsing file %s. "\
"File file was malformed. Face at line %d refers to a non-existent index"

#define MESSAGE_OBJ_ERROR "Reading of file %s failed. The expected extension "\
"was .obj but instead the file extension is .%s. File has not been "\
"imported"

#define MESSAGE_NOT_OBJ "Expected .obj file, but found %s extension"

#define MESSAGE_MISSING_MATERIAL "Missing material %s for object %s"

#define MESSAGE_MISSING_MATERIAL_OVERRIDE MESSAGE_MISSING_MATERIAL " while "\
"overriding its materials"

#ifdef _WIN32
#define MESSAGE_WRONG_ABS_FILE_ARCH "Expected an absolute path for " \
"Windows but found an absolute path for Linux/MacOS (%s)"
#else
#define MESSAGE_WRONG_ABS_FILE_ARCH "Expected an absolute path for " \
"Linux/MacOS but found an absolute path for Windows (%s)"
#endif
#endif

/**
 *  \endcond
 */
