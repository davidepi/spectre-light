#ifndef __FRESNEL_CONDITIONS_HPP__
#define __FRESNEL_CONDITIONS_HPP__

#include "color.hpp"

class FresnelConditions
{
public:
    virtual Color eval(float cosin)const = 0;
};

class Conductor : public FresnelConditions
{
public:
    Conductor(float refraction, float absorption);
    ~Conductor();
    Color eval(float cosin);
private:
    float refraction_index;
    float absorption;
};

#endif
