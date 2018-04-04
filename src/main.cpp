//author: Davide Pizzolotto
//license: GNU GPLv3

#include "utility/console.hpp"
#include "parsers/config_driver.hpp"
#include "renderer.hpp"

int main(int argc, char* argv[])
{
    ImageIO_init();
    Renderer* renderer;
    ConfigDriver parser;
    if(argc < 2)
        Console.critical("Input should be in the form: executable input_file");
    else
        parser.parse(argv[1],renderer);
//    return renderer->render(new Scene());
    return 0;
}
