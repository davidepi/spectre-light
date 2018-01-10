#include "distributions.hpp"
#include <cstdio>
#include <cstdlib>
int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        fprintf(stderr,"Missing output path\n");
        exit(EXIT_FAILURE);
    }
    generate_filters_data(argv[1]);
    generate_primitives_data(argv[1]);
    return 0;
}
