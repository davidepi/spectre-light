#include "occlusion_tester.hpp"

OcclusionTester::OcclusionTester(const Scene *s)
{
    OcclusionTester::s = s;
    OcclusionTester::lasthit = NULL;
}

bool OcclusionTester::isOccluded(const Ray *r, const Asset *expected, float* d)
{
    float newdistance;
    HitPoint removeme;//TODO: this can be removed, but a huge refactor is needed
    if(lasthit!=NULL && lasthit!=expected) //cached asset. if this is the
    {                                      //expected, the condition is not
        if(lasthit->intersect(r,&newdistance,&removeme))//sufficient to say that
            return true;                   //there are no occlusion
    }
    if(s->k.intersect(r,&removeme))
    {
        lasthit = removeme.hit;
        newdistance = removeme.h.distanceTo(r->origin);
        if (lasthit == expected || newdistance>=*d)
            return false;
        else
            return true;
    }
    else
        return false;
}
