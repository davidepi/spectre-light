#include "microfacet_distributions.hpp"

float MicrofacetDist::G(const Vec3* wo, const Vec3* wi, const Vec3* wh)const
{
    const float cosh = fabsf(wh->z);
    const float partial = 2*cosh/absdot(*wo,*wh);
    return min(1.f,min(partial*fabsf(wo->z),partial*fabsf(wi->z)));
}

float MicrofacetDist::pdf(const Vec3* wo, const Vec3* wh, const Vec3* wi)const
{
    return this->D(wh)*fabsf(wh->z);
}

Blinn::Blinn(float exponent)
{
    Blinn::exponent = exponent;
}

float Blinn::D(const Vec3* h)const
{
    //phong = 1/(pi*alpha2)*((h dot n)^(2/alpha2 - 2))
    //assuming exponent = 2/alpha2 - 2, the result is the following
    return (exponent+2)*INV_TWOPI*powf(fabsf(h->z),exponent);
}

void Blinn::sampleWh(const Vec3* wo,float r0,float r1,Vec3* wh)const
{
    const float cost = powf(r0,(1.f/(Blinn::exponent+1)));
    const float sint = sqrtf(1.f-cost*cost);
    const float phi = r1*TWO_PI;
    *wh = Vec3(sint*cosf(phi),sint*sinf(phi),cost);
    if(wo->z*wh->z<0) *wh = -*wh;
}

float Blinn::pdf(const Vec3* wo, const Vec3* wh, const Vec3* wi)const
{
    float dotwoh = dot(*wo,*wh);
    if(dotwoh>0.f)
    {
        const float cost = fabsf(wh->z);
        return ((Blinn::exponent+1)*powf(cost,exponent))/(FOUR_PI*2.f*dotwoh);
    }
    else
        return 0.f;
}

Beckmann::Beckmann(float roughness)
{
    Beckmann::a = roughness;
}

float Beckmann::D(const Vec3* h)const
{
    const float cost2 = h->z*h->z;
    const float sint2 = 1.f-cost2;
    const float a2 = Beckmann::a*Beckmann::a;
    return 1.f/(M_PI*cost2*cost2*a2)*expf(-(sint2/cost2)/a2);
}

float Beckmann::G(const Vec3* wo, const Vec3* wi, const Vec3* wh)const
{
    return Beckmann::G1(wo)*Beckmann::G1(wi);
}

float Beckmann::G1(const Vec3* v)const
{
    const float cos = fabsf(v->z);
    const float c = cos/(sqrtf(1.f-cos*cos)*Beckmann::a);
    if(c>=1.6)
        return 1.f;
    else
        return (3.535f*c+2.181f*c*c)/(1+2.276*c+2.577*c*c);
        
}

void Beckmann::sampleWh(const Vec3 *wo, float r0, float r1, Vec3 *wh)const
{
    //sampling algorithm for beckmann and GGX
    //https://agraphicsguy.wordpress.com/2015/11/01/sampling-microfacet-brdf
    //theta = arccos(1/sqrt(1-a2*log(1-r0)));
    const float l = log(1.f-r0);
    const float sqrt = 1.f-(Beckmann::a*Beckmann::a*l);
    const float cost = 1.f/sqrtf(sqrt);
    const float sint = sqrtf(1.f-cost*cost);
    const float phi = TWO_PI*r1;
    *wh = Vec3(sint*cosf(phi),sint*sinf(phi),cost);
    if(wo->z*wh->z<0) *wh = -*wh;
}

GGXiso::GGXiso(float roughness)
{
    GGXiso::a2 = roughness*roughness;
}

float GGXiso::D(const Vec3 *h)const
{
    float squared_term = 1+(h->z*h->z)*(a2-1);
    squared_term*=squared_term;
    return a2*INV_PI*(1.f/squared_term);
}

float GGXiso::G(const Vec3 *wo, const Vec3 *wi, const Vec3 *wh)const
{
    return GGXiso::G1(wo)*GGXiso::G1(wi);
}

float GGXiso::G1(const Vec3* v)const
{
    const float cos = v->z;
    return (2*cos)/(cos+sqrtf(a2+(1-a2)*cos*cos));
}

void GGXiso::sampleWh(const Vec3 *wo, float r0, float r1, Vec3 *wh)const
{
    const float cos2t = (1.f-r0)/(r0*(a2-1)+1);
    const float cost = sqrtf(cos2t);
    const float sint = sqrtf(1.f-cos2t);
    const float phi = TWO_PI*r1;
    *wh = Vec3(sint*cosf(phi),sint*sinf(phi),cost);
    if(wo->z*wh->z<0) *wh = -*wh;
}

GGXaniso::GGXaniso(float ax, float ay)
{
    GGXaniso::ax = ax;
    GGXaniso::ay = ay;
}

float GGXaniso::D(const Vec3 *h)const
{
    const float inv_cos2 = 1.f/(h->z*h->z);
    const float sin2 = 1.f-(h->z*h->z);
    const float inv_sin2 = 1.f/sin2;
    const float tan2 = sin2*inv_cos2;
    const float inv_ax = 1.f/ax;
    const float inv_ay = 1.f/ay;
    //cosphi = h->x/sintheta due to the chose shading space
    const float cosphi2 = h->x*h->x*inv_sin2;
    //cosphi = h->x/sintheta due to the chose shading space
    const float sinphi2 = h->y*h->y*inv_sin2;
    
    float sq_term = 1+(((cosphi2*inv_ax*inv_ax)+(sinphi2*inv_ay*inv_ay))*tan2);
    sq_term*=sq_term;
    
    return INV_PI*inv_ax*inv_ay*inv_cos2*inv_cos2*(1.f/sq_term);
}

static inline float lambdaGGXaniso(const Vec3* v,float ax, float ay)
{
    const float cos = v->z;
    const float sin = sqrtf(1.f-cos*cos);
    const float sin2 = sin*sin;
    const float tan = fabsf(sin/cos);
    if(std::isinf(tan))
        return 0.f;
    const float cos2phi = (v->x*v->x)/sin2;
    const float sin2phi = (v->y*v->y)/sin2;
    const float alpha = sqrtf(cos2phi*ax*ax+sin2phi*ay*ay);
    return (-1+sqrtf(1.f+(tan*tan*alpha*alpha)))*0.5f;
}

float GGXaniso::G(const Vec3* wo, const Vec3* wi, const Vec3* wh)const
{
    //this one is taken from pbrtv3
    return 1.f/(1+lambdaGGXaniso(wo,ax,ay)+lambdaGGXaniso(wi,ax,ay));
}

void GGXaniso::sampleWh(const Vec3 *wo, float r0, float r1, Vec3 *wh)const
{
    //again, anisotropic equations are taken from pbrtv3
    float phi = atanf(ay/ax*tanf(TWO_PI*r1+.5f*M_PI));
    if(r1 > .5f) phi += M_PI;
    const float sinphi = std::sin(phi);
    const float cosphi = std::cos(phi);
    const float ax2 = ax * ax;
    const float ay2 = ay * ay;
    const float a2 = 1/(cosphi*cosphi/ax2+sinphi*sinphi/ay2);
    const float tantheta2 = a2*r0/(1-r0);
    const float cost = 1.f/sqrtf(1.f + tantheta2);
    const float sint = (1.f-cost*cost);
    *wh = Vec3(sint*cosf(phi),sint*sinf(phi),cost);
    if(wo->z*wh->z<0) *wh = -*wh;
}
