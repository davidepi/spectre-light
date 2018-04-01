//created 31 mar 2018

#ifndef __CONFIG_DRIVER_HPP__
#define __CONFIG_DRIVER_HPP__

#include <string>
#include "config_parser.tab.hh"

#define YY_DECL \
yy::ConfigParser::symbol_type yylex(ConfigDriver& driver)
YY_DECL;

class ConfigDriver
{
public:
    ConfigDriver() = default;
    virtual ~ConfigDriver() = default;
    
    void scan_begin();
    void scan_end();
    int parse(const std::string& f)
    {
        file = f;
        scan_begin();
        yy::ConfigParser parser(*this);
        parser.parse();
        scan_end();
        return 1;
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
