#ifndef __REFRACTION_HPP__
#define __REFRACTION_HPP__

#include "bdf.hpp"
#include "color.hpp"
#include "vec3.hpp"
#include "fresnel_conditions.hpp"

class Refraction : public Bdf
{
public:
    Refraction(Color specular, float eta_incident, float eta_transmitted);
    Bdf* clone()const;
    Color df(const Vec3* wout, const Vec3* wincident)const;
    Color df_s(const Vec3* wo, Vec3* wi)const;

private:
    Color specular;
    float eta_i;
    float eta_t;
    Dielectric d;
};

#endif
