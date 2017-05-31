#include "stratified_sampler.hpp"

StratifiedSampler::StratifiedSampler(int startx, int endx, int starty, int endy,
                                     int spp,const unsigned int* seed,bool rand)
: Sampler(startx,endx,starty,endy,spp,seed)
{
    StratifiedSampler::nextx = startx;
    StratifiedSampler::nexty = starty;
    StratifiedSampler::isRandomized = rand;
    StratifiedSampler::strata_x = (int)sqrtf(spp);
    StratifiedSampler::strata_y = StratifiedSampler::strata_x;
}

StratifiedSampler::~StratifiedSampler()
{
    
}

bool StratifiedSampler::getSamples(Sample *res)
{
    if(nexty==endy)
        return false;
    float dx = 1.0f/strata_x;
    float dy = 1.0f/strata_y;
    for(int y=0;y<strata_y;y++)
    {
        for(int x=0;x<strata_x;x++)
        {
            float randomization_x = isRandomized?rng.getNumberf():0.5f;
            float randomization_y = isRandomized?rng.getNumberf():0.5f;
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
