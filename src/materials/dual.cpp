//author: Davide Pizzolotto
//license: GNU GPLv3

#include "dual.hpp"

DualBsdf::DualBsdf(const Bsdf* first, const Bsdf* second, const MaskBoolean&
mask):mask(mask)
{
    DualBsdf::first = first;
    DualBsdf::second = second;
}


Spectrum DualBsdf::value(const Vec3* woW, const HitPoint* h, const Vec3* wiW,
                         bool matchSpec) const
{
    if(mask.is_masked(h))
        return first->value(woW, h, wiW, matchSpec);
    else
        return second->value(woW, h, wiW, matchSpec);
}

Spectrum DualBsdf::sample_value(float r0, float r1, float r2, const Vec3* woW,
                                const HitPoint* h, Vec3* wiW, float* pdf,
                                bool matchSpec, bool* matchedSpec) const
{
    if(mask.is_masked(h))
        return first->sample_value(r0, r1, r2, woW, h, wiW, pdf, matchSpec,
                                   matchedSpec);
    else
        return second->sample_value(r0, r1, r2, woW, h, wiW, pdf, matchSpec,
                                    matchedSpec);
}

float DualBsdf::pdf(const Vec3* woW, const HitPoint* h, const Vec3* wiW,
                    bool matchSpec) const
{
    if(mask.is_masked(h))
        return first->pdf(woW, h, wiW, matchSpec);
    else
        return second->pdf(woW, h, wiW, matchSpec);
}
