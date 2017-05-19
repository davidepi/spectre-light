#include "stratified_sampler.hpp"
StratifiedSampler::StratifiedSampler(int startx, int endx, int starty, int endy,
                                     int spp,unsigned int* seed, bool random)
: Sampler(startx,endx,starty,endy,spp,seed)
{
    StratifiedSampler::nextx = startx;
    StratifiedSampler::nexty = starty;
    StratifiedSampler::randomized = random;
    StratifiedSampler::strata_x = (int)sqrtf(spp);
    StratifiedSampler::strata_y = StratifiedSampler::strata_x;
}

StratifiedSampler::~StratifiedSampler()
{
    
}

void StratifiedSampler::getSamples(Sample *res)
{
    float dx = 1.0f/strata_x;
    float dy = 1.0f/strata_y;
    for(int y=0;y<strata_y;y++)
    {
        for(int x=0;x<strata_x;x++)
        {
            float randomization_x = randomized?rng.getNumberf():0.5f;
            float randomization_y = randomized?rng.getNumberf():0.5f;
            res[y*x+x].posx = (nextx)+((x+randomization_x)*dx);
            res[y*x+x].posy = (nexty)+((y+randomization_y)*dy);
        }
    }
    nextx++;
    nexty++;
}
