#include "light_sky.hpp"

Spectrum
LightSky::sample_surface(float r0, float r1, float r2, float r3, Ray* out,
                         float* pdf) const
{
    return {};
}

Spectrum
LightSky::sample_visible_surface(float r0, float r1, const Point3* position,
                                 Vec3* wi, float* pdf, float* distance) const
{
    //sample texture
    float texture_pdf;
    HitPoint sample;
    sample.uv = distribution->sample_continuous(r0, r1, &texture_pdf);
    if(texture_pdf == 0)
        return {};

    //convert the sample to spherical coords
    const float THETA = sample.uv.y*ONE_PI;
    const float PHI = sample.uv.x*2.f*ONE_PI;
    const float COST = cosf(THETA);
    const float SINT = sinf(THETA);
    const float COSP = cosf(PHI);
    const float SINP = sinf(PHI);
    *wi = light2world*Vec3(SINT*COSP, SINT*SINP, COST);

    //pdf
    if(SINT == 0)
        *pdf = 0.f;
    *pdf = texture_pdf/(2*ONE_PI*ONE_PI*SINT);

    Texel value = skytexture->map_value(&sample).bgra_texel;
    return {ColorRGB(value.r, value.g, value.b), true};
}

float LightSky::pdf(const Ray* ray) const
{
    return 0;
}

float LightSky::pdf(const Point3*, const Vec3* wiW) const
{
    Vec3 wiL = world2light**wiW;
    const float THETA = acosf(clamp(wiL.z, -1.f, 1.f));
    const float SINT = sinf(THETA);
    if(SINT == 0)
        return 0.f;
    float phi = atan2f(wiL.y, wiL.x);
    phi = phi<0?phi+2.f*ONE_PI:phi;
    Point2 sample(phi*INV_TWOPI, THETA*INV_PI);
    const float INV_TERM = 1.f/(2.f*ONE_PI*ONE_PI*SINT);
    sample.x *= INV_TERM;
    sample.y *= INV_TERM;
    return distribution->pdf(&sample);

}

bool LightSky::renderable() const
{
    return true;
}

LightSky::LightSky(const Texture* tex, float world_rad)
        :Light(0), //skydome does not use the intensity, so it is set to 0
         skytexture(tex)
{

    //create the light2world matrix
    light2world.set_rotate_z(tex->get_shift().x);
    //ignore vertical shift
    Matrix4 scale_dome;
    scale_dome.set_scale(world_rad);
    light2world *= scale_dome;
    light2world.inverse(&world2light);

    //create the distribution array (used for importance sampling the dome)
    const uint16_t SIDE = tex->get_side();
    float* distr_array = (float*)malloc(sizeof(float)*SIDE*SIDE);
    const float INV_SIDE = 1.f/SIDE;
    for(int y = 0; y<SIDE; y++)
    {
        const float YPART = y*INV_SIDE;
        const float SINT = sinf(ONE_PI*(YPART+.5f)*INV_SIDE);
        for(int x = 0; x<SIDE; x++)
        {
            const float XPART = x*INV_SIDE;
            HitPoint hp;
            hp.uv.x = XPART;
            hp.uv.y = YPART;
            Spectrum spectrum(skytexture->map_color(&hp), true);
            distr_array[y*SIDE+x] = spectrum.luminance()*SINT;
        }
    }
    distribution = new Distribution2D(distr_array, SIDE, SIDE);
    free(distr_array);
}

Spectrum LightSky::radiance_escaped(const Ray* ray) const
{
    Vec3 dir = (world2light*ray->direction).normalize();
    const float THETA = acosf(clamp(dir.z, -1.f, 1.f));
    float phi = atan2f(dir.y, dir.x);
    if(phi<0)
        phi += TWO_PI;
    HitPoint hp;
    hp.uv.x = phi*INV_TWOPI;
    hp.uv.y = THETA*INV_PI;
    return {skytexture->map_color(&hp), true};
}

LightSky::~LightSky()
{
    delete distribution;
}
