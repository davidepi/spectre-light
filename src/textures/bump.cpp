#include "bump.hpp"

void Bump::bump(const HitPoint* hp) const
{
    hp->normal_s = hp->normal_g;
}
