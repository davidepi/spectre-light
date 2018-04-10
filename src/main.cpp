//author: Davide Pizzolotto
//license: GNU GPLv3

#include "utility/console.hpp"
#include "parsers/config_driver.hpp"
#include "renderer.hpp"

int main(int argc, char* argv[])
{
    ImageIO_init();
    Renderer* renderer = NULL;
    ConfigDriver parser;
    if(argc < 2)
        Console.critical("Input should be in the form: executable input_file");
    else
        renderer = parser.parse(argv[1]);
//    return renderer->render(new Scene());
    Console.critical("Rendering disabled, checkout master branch");
}
