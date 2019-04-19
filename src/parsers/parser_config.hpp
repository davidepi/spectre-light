//Created,  31 Mar 2018
//Last Edit 19 Apr 2019

/**
 *  \file      parser_config.hpp
 *  \brief     Bridge between bison parser and the application
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      19 Apr 2019
 *  \copyright GNU GPLv3
 */


#ifndef __PARSER_CONFIG_HPP__
#define __PARSER_CONFIG_HPP__

//This magnificent bastard must come first, otherwise C++ linking is used anyway
extern "C" {
#include "parsers/parsed_structs.h"
}

#include "renderer.hpp"
#include "textures/texture_library.hpp"
#include "materials/material_library.hpp"
#include "utility/scene.hpp"

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
    ParserConfig(MaterialLibrary* matLib, TextureLibrary* texLib);

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

private:
    MaterialLibrary* mtllib;
    TextureLibrary* texlib;
};


#endif
