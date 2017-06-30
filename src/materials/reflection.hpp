#ifndef __REFLECTION_HPP__
#define __REFLECTION_HPP__

#include "bdf.hpp"
#include "fresnel_conditions.hpp"
#include "color.hpp"
#include "vec3.hpp"

class Reflection : public Bdf
{
public:
    Reflection(Color specular, FresnelConditions* fc);
    Bdf* clone()const;
    Color df(const Vec3* wout, const Vec3* wincident)const;
    Color df_s(const Vec3* wo, Vec3* wi)const;

private:
    Color specular;
    FresnelConditions* fc;
};


#endif
