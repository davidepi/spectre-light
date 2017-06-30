//Created,   7 Jun 2017
//Last Edit  7 Jun 2017


#ifndef __LAMBERTIAN_HPP__
#define __LAMBERTIAN_HPP__
#include "settings.h"
#include "bdf.hpp"
#include "color.hpp"
#include "vec3.hpp"
#include "console.hpp"

class Lambertian : public Bdf
{
public:
    Lambertian(Color scattered_spectrum);
    Bdf* clone()const;
    Color df(const Vec3* wout, const Vec3* wincident)const;
private:
    Color diffuse;
};

#endif
