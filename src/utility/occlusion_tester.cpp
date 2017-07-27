#include "occlusion_tester.hpp"

OcclusionTester::OcclusionTester(const Scene *s)
{
    OcclusionTester::s = s;
    OcclusionTester::lasthit = NULL;
}

bool OcclusionTester::isOccluded(const Ray *r, float* d)
{
    HitPoint removeme;
    float newdistance = FLT_MAX;
    if (lasthit != NULL)
        if(lasthit->intersect(r,&newdistance,&removeme))
        {
            if(newdistance+OCCLUSION_INTERSECT_ERROR<*d)
                return true;
        }
    if(s->k.intersect(r,&removeme))
    {
        lasthit = removeme.hit;
        newdistance = removeme.h.distanceTo(r->origin);
        return newdistance+OCCLUSION_INTERSECT_ERROR<*d;
    }
    else
        return false;
}
