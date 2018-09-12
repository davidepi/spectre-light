//author: Davide Pizzolotto
//license: GNU GPLv3

#include "occlusion_tester.hpp"

OcclusionTester::OcclusionTester(const Scene* scene)
{
    OcclusionTester::scene = scene;
    for(int i = 0; i<DEFAULT_BOUNCES; i++)
        OcclusionTester::lasthit[i] = NULL;
}

bool OcclusionTester::is_occluded(const Ray* r, float distance)
{
    HitPoint removeme;
    float newdistance = FLT_MAX;
    const Asset* lhit = OcclusionTester::lasthit[r->ricochet];
    if(lhit != NULL)
        if(lhit->intersect(r, &newdistance, &removeme))
        {
            if(newdistance+SELF_INTERSECT_ERROR<distance)
                return true;
        }
    if(scene->k.intersect(r, &removeme))
    {
        OcclusionTester::lasthit[r->ricochet] = removeme.asset_h;
        newdistance = removeme.point_h.distance(r->origin);
        return newdistance+SELF_INTERSECT_ERROR<distance;
    }
    else
        return false;
}
