#include "random_sampler.hpp"

RandomSampler::RandomSampler(int startx, int endx, int starty, int endy,
                                     int spp, const unsigned int* seed)
        : Sampler(startx,endx,starty,endy,spp,seed)
{
    RandomSampler::nextx = startx;
    RandomSampler::nexty = starty;
}

bool RandomSampler::getSamples(Sample *res)
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
