#ifndef __STRATIFIED_SAMPLER_HPP__
#define __STRATIFIED_SAMPLER_HPP__

#include <cmath>
#include "sampler.hpp"

class StratifiedSampler : public Sampler
{
public:
    StratifiedSampler(int startx, int endx, int starty, int endy, int spp,
                              unsigned int* seed, bool random);
    ~StratifiedSampler();
    void getSamples(Sample* res);
private:
    int nextx;
    int nexty;
    int strata_x;
    int strata_y;
    bool randomized;
};

#endif
