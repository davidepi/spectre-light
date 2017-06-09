#ifndef __FRESNEL_CONDITIONS_HPP__
#define __FRESNEL_CONDITIONS_HPP__

#include "color.hpp"
#include "utility.hpp"

class FresnelConditions
{
public:
    virtual Color eval(float cosin)const = 0;
};

class Conductor : public FresnelConditions
{
public:
    Conductor(Color refraction, Color absorption);
    ~Conductor();
    Color eval(float cosin)const;
private:
    Color refraction_index;
    Color absorption;
};

class Dielectric : public FresnelConditions
{
public:
    Dielectric(float refractioni, float refractiont);
    ~Dielectric();
    Color eval(float cosin)const;

private:
    float etai;
    float etat;
};

#endif
