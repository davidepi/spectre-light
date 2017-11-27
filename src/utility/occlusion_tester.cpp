//author: Davide Pizzolotto
//license: GNU GPLv3

#include "occlusion_tester.hpp"

OcclusionTester::OcclusionTester(const Scene *s)
{
    OcclusionTester::s = s;
    for(int i=0;i<DEFAULT_BOUNCES;i++)
        OcclusionTester::lasthit[i] = NULL;
}

bool OcclusionTester::isOccluded(const Ray *r, const float* d)
{
    HitPoint removeme;
    float newdistance = FLT_MAX;
    const Asset* lhit = OcclusionTester::lasthit[r->ricochet];
    if (lhit != NULL)
        if(lhit->intersect(r,&newdistance,&removeme))
        {
            if(newdistance+OCCLUSION_INTERSECT_ERROR<*d)
                return true;
        }
    if(s->k.intersect(r,&removeme))
    {
        OcclusionTester::lasthit[r->ricochet] = removeme.hit;
        newdistance = removeme.h.distanceTo(r->origin);
        return newdistance+OCCLUSION_INTERSECT_ERROR<*d;
    }
    else
        return false;
}
