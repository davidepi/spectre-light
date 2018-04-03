//author: Davide Pizzolotto
//license: GNU GPLv3

#include "utility/console.hpp"
#include "parsers/config_driver.hpp"
#include "renderer.hpp"
#ifdef IMAGEMAGICK
#include <Magick++.h>
#include <type_traits> //std::is_floating_point
#endif

int main(int argc, char* argv[])
{
#ifdef IMAGEMAGICK
    Magick::InitializeMagick(IMAGEMAGICK);
    std::is_floating_point<Magick::Quantum> is_fp;
    if(!is_fp.value)
        Console.severe(MESSAGE_IM_NOFLOAT);
#endif
    Renderer* renderer;
    ConfigDriver parser;
    if(argc < 2)
        Console.critical("Input should be in the form: executable input_file");
    else
        parser.parse(argv[1],renderer);
//    return renderer->render(new Scene());
    return 0;
}
