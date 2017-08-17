#include "utility/parser.hpp"
#include "utility/console.hpp"

int main(int argc, char* argv[])
{
    Parser p;
    Settings s;
    if(argc < 2)
        Console.critical("Input should be in the form: executable input_file");
    else
        s = p.parse(argv[1]);
    free(s.output);
    return 0;
}
