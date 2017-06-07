//Created,   7 Jun 2017
//Last Edit  7 Jun 2017


#ifndef __BDF_HPP__
#define __BDF_HPP__
#include "color.hpp"
#include "vec3.hpp"

enum BdfFlags {BRDF = 0x0, BTDF = 0x1, DIFFUSE = 0x2, SPECULAR = 0x4};

class Bdf
{
public:

    Bdf(BdfFlags flags);
    ~Bdf();

    BdfFlags type;
    virtual Color df(const Vec3* wout, const Vec3* wincident)const = 0;

    inline bool isType(BdfFlags f)
    {
        return type & f;
    }
};

#endif
