#ifndef __OBJ_PARSER_HPP__
#define __OBJ_PARSER_HPP__

#include <string>
#include "obj_parser.tab.hh"

#define YY_DECL \
yy::ObjParser::symbol_type yylex(ObjDriver& driver)
YY_DECL;

class ObjDriver
{
public:
    ObjDriver() = default;
    virtual ~ObjDriver() = default;

    void scan_begin();
    void scan_end();
    int parse(const std::string& f)
    {
        file = f;
        scan_begin();
        yy::ObjParser parser(*this);
        parser.parse();
        scan_end();
    }
    std::string file;
    void error(const yy::location& l, const std::string& m)
    {
        std::cerr<<l<<": "<<m<<std::endl;
    }
    void error(const std::string& m)
    {
        std::cerr<<m<<std::endl;
    }
};

#endif
