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
                         const ShadingSpace* matrix, bool matchSpec) const
{
    if(mask.is_masked(h))
        return first->value(woW, h, wiW, matrix, matchSpec);
    else
        return second->value(woW, h, wiW, matrix, matchSpec);
}

Spectrum DualBsdf::sample_value(float r0, float r1, float r2, const Vec3* woW,
                                const HitPoint* h, const ShadingSpace* matrix,
                                Vec3* wiW, float* pdf, bool matchSpec,
                                bool* matchedSpec) const
{
    if(mask.is_masked(h))
        return first->sample_value(r0, r1, r2, woW, h, matrix, wiW, pdf,
                                   matchSpec, matchedSpec);
    else
        return second->sample_value(r0, r1, r2, woW, h, matrix, wiW, pdf,
                                    matchSpec, matchedSpec);
}

float
DualBsdf::pdf(const Vec3* woW, const HitPoint* h, const ShadingSpace* matrix,
              const Vec3* wiW, bool matchSpec) const
{
    if(mask.is_masked(h))
        return first->pdf(woW, h, matrix, wiW, matchSpec);
    else
        return second->pdf(woW, h, matrix, wiW, matchSpec);
}

void DualBsdf::gen_shading_matrix(const HitPoint* hp, ShadingSpace* matrix)
const
{
    if(mask.is_masked(hp))
        first->gen_shading_matrix(hp, matrix);
    else
        second->gen_shading_matrix(hp, matrix);
}
