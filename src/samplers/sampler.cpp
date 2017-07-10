#include "sampler.hpp"
Sampler::Sampler(int startx, int endx, int starty, int endy, int spp,
                 const unsigned int* seed) : rng(seed)
{
    Sampler::startx = startx;
    Sampler::endx = endx;
    Sampler::starty = starty;
    Sampler::endy  = endy;
    Sampler::spp = spp;
}

float Sampler::getRandomNumber()
{
    return rng.getNumberf();
}