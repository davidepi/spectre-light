//Created,   16 Jun 2017
//Last Edit  22 Jun 2017


#ifndef __BDF_HPP__
#define __BDF_HPP__

#include "shape.hpp"
#include "color.hpp"
#include "vec3.hpp"
#include "console.hpp"

enum BdfFlags {BRDF = 0x1, BTDF = 0x2, DIFFUSE = 0x4, SPECULAR = 0x8};

class Bdf
{
public:

    Bdf(BdfFlags flags);
    ~Bdf();

    virtual Bdf* clone()const = 0;
    virtual Color df(const Vec3* wout, const Vec3* wincident)const = 0;
    virtual Color df_s(const Vec3* wo, Vec3* wi)const;
    BdfFlags getFlags()const;
    inline bool isType(BdfFlags f)
    {
        return type & f;
    }

private:
    BdfFlags type;
};

class Bsdf
{
public:
    Bsdf();
    ~Bsdf();
    //bdf is copied
    void addBdf(const Bdf& addme);
    Color df(const Vec3* wo, const HitPoint* h, Vec3* wi)const;

private:
    char count;
    Bdf* bdfs[_MAX_BDF_];
    Normal n;
    Vec3 right;
    Vec3 cross;
};

#endif
