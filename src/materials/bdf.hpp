//Created,   16 Jun 2017
//Last Edit  16 Jun 2017


#ifndef __BDF_HPP__
#define __BDF_HPP__
#include "color.hpp"
#include "vec3.hpp"
#include "console.hpp"

enum BdfFlags {BRDF = 0x0, BTDF = 0x1, DIFFUSE = 0x2, SPECULAR = 0x4};

class Bdf
{
public:

    Bdf(BdfFlags flags);
    ~Bdf();

    BdfFlags type;
    virtual Color df(const Vec3* wout, const Vec3* wincident)const = 0;
    virtual Color df_s(const Vec3* wo, Vec3* wi)const;
    inline bool isType(BdfFlags f)
    {
        return type & f;
    }
};

class Bsdf
{
public:
    Bsdf();
    ~Bsdf();
    void addBdf(Bdf addme);

private:
    char count;
    Bdf bdfs[_MAX_BDF_];
};

#endif
