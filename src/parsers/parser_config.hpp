//Created,  31 Mar 2018
//Last Edit 19 Sep 2018

/**
 *  \file      parser_config.hpp
 *  \brief     Bridge between bison parser and the application
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      19 Sep 2018
 *  \copyright GNU GPLv3
 */


#ifndef __PARSER_CONFIG_HPP__
#define __PARSER_CONFIG_HPP__

//This magnificent bastard must come first, otherwise C++ linking is used anyway
extern "C" {
#include "parsers/parsed_structs.h"
}

#include "renderer.hpp"
#include "utility/scene.hpp"
#include "utility/spectrum.hpp"
#include "geometry/point3.hpp"
#include "geometry/vec3.hpp"
#include "cameras/camera_orthographic.hpp"
#include "cameras/camera_perspective.hpp"
#include "cameras/camera360.hpp"
#include "samplers/filter_box.hpp"
#include "samplers/filter_tent.hpp"
#include "samplers/filter_gaussian.hpp"
#include "samplers/filter_mitchell.hpp"
#include "samplers/filter_lanczos.hpp"
#include "integrators/path_tracer.hpp"
#include "textures/texture_uniform.hpp"
#include "textures/texture_image.hpp"
#include "textures/texture_normal.hpp"
#include "materials/single_brdf.hpp"
#include "materials/multi_bsdf.hpp"
#include "materials/oren_nayar.hpp"
#include "materials/lambertian.hpp"
#include "materials/reflection.hpp"
#include "materials/refraction.hpp"
#include "materials/fresnel_conditions.hpp"
#include "materials/microfacet.hpp"
#include "materials/microfacet_distributions.hpp"
#include "materials/metals.hpp"
#include "materials/dual.hpp"
#include "parsers/parser_obj.hpp"
#include "primitives/mesh.hpp"
#include "primitives/sphere.hpp"
#include "lights/light_area.hpp"
#include "lights/light_omni.hpp"
#include "lights/light_spot.hpp"

/**
 *  \brief Parse an input file
 *
 *  This class is used to parse the main input file received from the user,
 *  describing the scene and the assets used. It automatically includes every
 *  dependency required by the file and allocates a Renderer class ready to
 *  generate the output image.
 *
 *  In particular, this class is a C++ bridge between the data definition of
 *  the parser_struct.c and parser_struct.h, and the bison/lex parsed defined
 *  in config_parser.y and config_lexer.l (and then transpiled to
 *  config_parser.tab.c, config_parser.tab.h and lex.yy.c). These classes
 *  produce raw values that must be put inside C++ classes, which is done by
 *  this bridge class
 *
 */
class ParserConfig
{
public:

    ///Default constructor
    ParserConfig() = default;

    ///Default destructor
    ~ParserConfig() = default;

    /**
    *  \brief Parse the file specified as parameter
    *
    *  Open a descriptor to the file passed as parameter and parse it and every
    *  subsequent dependency. If errors are encountered, depending on their
    *  gravity, it could even terminate the program. Returns an allocated
    *  Renderer ready to generate the output image
    *
    *  \note Note that the returned Renderer is heap allocated and requires a
    *  call to delete to avoid memory leaks. This is not a good practice but
    *  Renderer class depends on some user defined parameters for its
    *  construction
    *
    *  \param[in] filename The file that will be parsed
    *  \param[in,out] scene The scene that will be built, must be already
    *  allocated
    *  \return An heap allocated Renderer
    */
    CHECK_RETVAL_USED
    Renderer* parse(const char* filename, Scene* scene);
};


#endif
