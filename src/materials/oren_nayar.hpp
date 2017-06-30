
#ifndef __OREN_NAYAR_HPP__
#define __OREN_NAYAR_HPP__


#include "bdf.hpp"
#include "color.hpp"
#include "vec3.hpp"

class OrenNayar : public Bdf
{
public:
    OrenNayar(Color diffuse, float sigma);
    Color df(const Vec3* wout, const Vec3* wincident)const;
    Bdf* clone()const;

private:
    Color diffuse;
    float A;
    float B;
};


#endif
