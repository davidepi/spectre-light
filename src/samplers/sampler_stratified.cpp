//author: Davide Pizzolotto
//license: GNU GPLv3

#include "sampler_stratified.hpp"

SamplerStratified::SamplerStratified(int startx, int endx, int starty, int endy,
                                     int spp,const unsigned int* seed,bool rand)
: Sampler(startx,endx,starty,endy,spp,seed)
{
    SamplerStratified::nextx = startx;
    SamplerStratified::nexty = starty;
    SamplerStratified::randomized = rand;
    SamplerStratified::strata_x = (int) sqrtf(spp);
    SamplerStratified::strata_y = SamplerStratified::strata_x;
}

bool SamplerStratified::get_samples(Sample *res)
{
    if(nexty==endy)
        return false;
    float dx = 1.0f/strata_x;
    float dy = 1.0f/strata_y;
    for(int y=0;y<strata_y;y++)
    {
        for(int x=0;x<strata_x;x++)
        {
            float randomization_x = randomized?rng.getNumber():0.5f;
            float randomization_y = randomized?rng.getNumber():0.5f;
            res->posx = (nextx)+((x+randomization_x)*dx);
            res->posy = (nexty)+((y+randomization_y)*dy);
            res++;
        }
    }
    if(++nextx==endx)
    {
        nextx=startx;
        nexty++;
    }
    return true;
}
