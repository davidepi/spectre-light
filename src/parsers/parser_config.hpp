//created 16-9-18

#ifndef __PARSER_CONFIG_HPP__
#define __PARSER_CONFIG_HPP__

#include "parsers/parsed_structs.h"
#include "renderer.hpp"
#include "utility/scene.hpp"

class ParserConfig
{
public:
    Renderer* parse(const char* filename, Scene* scene);
};

#endif
