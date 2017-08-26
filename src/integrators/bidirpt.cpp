#include "bidirpt.hpp"

struct PVertex
{
    HitPoint hit;
    Vec3 dir;
    bool isSpecular;
    float pdf;
    Color l;
};

Color Bdpt::radiance(const Scene* sc, const HitPoint* hp,
               const Ray* r, Sampler* sam,OcclusionTester *ot)const
{
    PVertex lp[DEFAULT_BOUNCES/2]; //light path
    char lp_size = 0;
    PVertex ep[DEFAULT_BOUNCES/2]; //eye path
    char ep_size = 0;
    Color L;
    int nlights = sc->lightSize();
    float rand[DEFAULT_BOUNCES*3];
    sam->getRandomNumbers(rand,DEFAULT_BOUNCES*3);

    //init light path. lp[0] is the point on the light surface
    int sampledlight = min((int)(rand[0]*nlights),nlights-1);
    lp[0].hit.hit = sc->getLights()[sampledlight];
    lp[0].isSpecular = false;
    lp[0].l = ((const AreaLight*)(lp[0].hit.hit))->radiance_e(rand[1],rand[2],
                                                                &lp[0].hit.h,
                                                                &lp[0].dir,
                                                                &lp[0].pdf);
    //construct light path
    for(char i=1;i<DEFAULT_BOUNCES/2;i++)
    {
        //TODO: russian roulette
        //compute current point, given previous point and direction
        Ray r(lp[i-1].hit.h,lp[i-1].dir);
        if(!sc->k.intersect(&r,&lp[i].hit)) //ray escaped scene
            break;
        //sample direction for next point
        Vec3 wo = -lp[i-1].dir;
        const Bsdf* mat = lp[i].hit.hit->getMaterial();
        BdfFlags matched;
        lp[i].l = mat->df_s(rand[i*3],rand[i*3+1],rand[i*3+2],&wo,&lp[i].hit,
                            &lp[i].dir, &lp[i].pdf, BdfFlags(ALL), &matched);
        //record if sampled bdf was specular
        lp[i].isSpecular = matched&SPECULAR?true:false;
        lp_size = i;
    }

    //init eye path. ep[0] is the point seen from the eye, ep[0].dir is the
    //light path from ep[0] to the eye
    ep[0].hit = *hp;
    ep[0].dir = -r->direction;
    sam->getRandomNumbers(rand,DEFAULT_BOUNCES/2*3);
    for(char i=1;i<DEFAULT_BOUNCES/2;i++)
    {
        //set previous hit point radiance
        const Bsdf* mat = ep[i-1].hit.hit->getMaterial();
        BdfFlags matched;
        ep[i-1].l = mat->df_s(rand[(i-1)*3],rand[(i-1)*3+1],rand[(i-1)*3+2],
                              &ep[i-1].dir,&ep[i-1].hit,&ep[i].dir,&ep[i-1].pdf,
                              BdfFlags(ALL), &matched);
        ep[i-1].isSpecular = matched&SPECULAR?true:false;

        //TODO: russian roulette

        Ray r(ep[i-1].hit.h,ep[i].dir);
        if(!sc->k.intersect(&r,&ep[i].hit))
            break; //ray escaped scene

        ep_size = i;
        ep[i].dir = -ep[i].dir; //since I need point to eye directions
    }
    //set last vertex, since for each run of the last loop I set i-1 and a
    //single variable of i
    if(ep_size==DEFAULT_BOUNCES/2-1)
    {
        Vec3 wi;
        const Bsdf* mat = ep[ep_size].hit.hit->getMaterial();
        BdfFlags matched;
        ep[ep_size].l = mat->df_s(rand[(DEFAULT_BOUNCES/2-1)*3],
                                  rand[(DEFAULT_BOUNCES/2-1)*3+1],
                                  rand[(DEFAULT_BOUNCES/2-1)*3+2],
                                  &ep[ep_size].dir,&ep[ep_size].hit,
                                  &wi,&ep[ep_size].pdf, BdfFlags(ALL),
                                  &matched);
        ep[ep_size].isSpecular = matched&SPECULAR?true:false;
    }

    return Color();

}