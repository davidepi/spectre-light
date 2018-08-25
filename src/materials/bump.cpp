#include "bump.hpp"

void Bump::bump(const HitPoint* hp, ShadingSpace* matrix, Point3* point,
                Normal* normal) const
{
    *matrix = ShadingSpace(hp);
    *point = hp->point_h;
    *normal = matrix->n;
}
