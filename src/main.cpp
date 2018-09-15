//author: Davide Pizzolotto
//license: GNU GPLv3

#include "utility/console.hpp"
#include "parsers/parser_config.hpp"
#include "renderer.hpp"
#ifdef _WIN32
#include <conio.h>
#endif

int main(int argc, char* argv[])
{
    Renderer* renderer = NULL;
    ParserConfig* parser = new ParserConfig();
    Scene scene;
    if(argc < 2)
        Console.critical("Input should be in the form: executable input_file");
    else
        renderer = parser->parse(argv[1],&scene);
    delete parser;
    int retval = renderer->render(&scene);
    delete renderer;
#ifdef _WIN32
    //avoid autoclosing cmd
    std::cout << "Pres any key to exit" << std::endl;
    _getch();
#endif
    return retval;
}
