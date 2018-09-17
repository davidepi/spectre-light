#include "parser_config.hpp"

extern "C" {void parse_config(FILE*,struct ParsedScene*);}

Renderer* ParserConfig::parse(const char* filename, Scene* scene)
{
    ParsedScene parsed;
    init_ParsedScene(&parsed);
    FILE* fin = fopen(filename, "r");
    parse_config(fin, &parsed);
    fclose(fin);
    deinit_ParsedScene(&parsed);
    return NULL;
}
