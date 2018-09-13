#ifndef __TYPES_SAMPLER_H__
#define __TYPES_SAMPLER_H__

enum sampler_t
{
    RANDOM, 
    STRATIFIED
};

enum filter_t
{
    BOX,
    TENT,
    GAUSS,
    MITCHELL,
    LANCZOS
};

#endif
