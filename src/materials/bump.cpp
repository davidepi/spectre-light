#include "bump.hpp"

void Bump::bump(const HitPoint* hp, ShadingSpace* matrix) const
{
    *matrix = ShadingSpace(hp);
}
