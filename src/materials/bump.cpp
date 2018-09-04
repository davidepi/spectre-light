#include "bump.hpp"

void Bump::bump(const HitPoint* hp, ShadingSpace* matrix, Normal* normal) const
{
    *matrix = ShadingSpace(hp);
    *normal = matrix->n;
}
