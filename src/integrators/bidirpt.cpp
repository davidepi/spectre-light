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
    unsigned char lp_size = 0;
    PVertex ep[DEFAULT_BOUNCES/2+1]; //eye path(the +1 is the point on the film)
    unsigned char ep_size = 0;
    Color L;
    int nlights = sc->lightSize();
    float rand[(DEFAULT_BOUNCES+1)*3];
    sam->getRandomNumbers(rand,DEFAULT_BOUNCES*3);

    //init light path. lp[0] is the point on the light surface
    int sampledlight = min((int)(rand[0]*nlights),nlights-1);
    lp[0].hit.hit = sc->getLights()[sampledlight];
    lp[0].isSpecular = false;
    Normal n;
    lp[0].l = ((const AreaLight*)(lp[0].hit.hit))->radiance_e(rand[1],rand[2],
                                                                &lp[0].hit.h,
                                                                &lp[0].dir,
                                                                &n,
                                                                &lp[0].pdf);
    lp[0].l *= absdot(n,lp[0].dir)/lp[0].pdf;
    //construct light path
    for(unsigned char i=1;i<DEFAULT_BOUNCES/2;i++)
    {
        //TODO: russian roulette
        //compute current point, given previous point and direction
        Ray r(lp[i-1].hit.h,lp[i-1].dir);
        if(!sc->k.intersect(&r,&lp[i].hit)) //ray escaped scene
            break;
        //sample direction for next point
        Vec3 wi = -lp[i-1].dir;
        const Bsdf* mat = lp[i].hit.hit->getMaterial();
        BdfFlags matched;
        lp[i].l = lp[i-1].l * mat->df_s(rand[i*3],rand[i*3+1],rand[i*3+2],&wi,
                                      &lp[i].hit,&lp[i].dir, &lp[i].pdf,
                                      BdfFlags(ALL), &matched);
        //record if sampled bdf was specular
        lp[i].isSpecular = matched&SPECULAR?true:false;
        lp_size++;
        lp[i].l *= absdot(lp[i].hit.n,lp[i].dir)/lp[i].pdf;
    }
    lp_size++;

    //init eye path. ep[0] is the point on camera and won't be used. It is here
    //just to avoid an array out of bounds
    ep[0].dir = r->direction;
    ep[0].l = Color(1.0f);
    ep[1].hit = *hp;
    sam->getRandomNumbers(rand,(DEFAULT_BOUNCES+1)*3);
    for(unsigned char i=1;i<DEFAULT_BOUNCES/2+1;i++)
    {
        const Bsdf* mat = ep[i].hit.hit->getMaterial();
        Vec3 wo = -ep[i-1].dir;
        BdfFlags matched;
        ep[i].l = ep[i-1].l * mat->df_s(rand[i*3],rand[i*3+1],rand[i*3+2],
                                        &wo,&ep[i].hit,&ep[i].dir,&ep[i].pdf,
                                        BdfFlags(ALL),&matched);
        if(ep[i].pdf==0 || ep[i].l.isBlack())
            break;
        ep_size++;
        ep[i].isSpecular = matched&SPECULAR?true:false;
        ep[i].l *= absdot(ep[i].hit.n,ep[i].dir)/ep[i].pdf;
        if(i+1==DEFAULT_BOUNCES/2+1)//ep[i+1] out of array
            break;
        else
        {
            Ray next(ep[i].hit.h,ep[i].dir);
            if(!sc->k.intersect(&next, &ep[i+1].hit))
                break; //ray escaped
        }
    }
    ep_size++;
    Color retval(0.f);
    return retval;
}
