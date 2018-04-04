//author: Davide Pizzolotto
//license: GNU GPLv3

#include "sampler_random.hpp"

SamplerRandom::SamplerRandom(int startx, int endx, int starty, int endy,
                                     int spp, const unsigned int* seed)
        : Sampler(startx,endx,starty,endy,spp,seed)
{
    SamplerRandom::nextx = startx;
    SamplerRandom::nexty = starty;
}

bool SamplerRandom::get_samples(Sample *res)
{
    if(nexty==endy)
        return false;
    for(int i=0;i<spp;i++)
    {
        res->posx = nextx+rng.getNumber();
        res->posy = nexty+rng.getNumber();
        res++;
    }
    if(++nextx==endx)
    {
        nextx=startx;
        nexty++;
    }
    return true;
}
