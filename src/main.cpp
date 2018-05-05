//author: Davide Pizzolotto
//license: GNU GPLv3

#include "utility/console.hpp"
#include "parsers/config_driver.hpp"
#include "renderer.hpp"

int main(int argc, char* argv[])
{
    ImageIO_init();
    Renderer* renderer = NULL;
    ConfigDriver* parser = new ConfigDriver();
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
    getchar();
#endif
    return retval;
}
