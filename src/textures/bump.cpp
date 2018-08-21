#include "bump.hpp"

void Bump::bump(const HitPoint* hp) const
{
    hp->shading = hp->geometric;
}
