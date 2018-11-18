#include "light_sky.hpp"

Spectrum
LightSky::sample_surface(float r0, float r1, float r2, float r3, Ray* out,
                         float* pdf) const
{
    return Spectrum();
}

Spectrum
LightSky::sample_visible_surface(float r0, float r1, const Point3* position,
                                 Vec3* wi, float* pdf, float* distance) const
{
    return Spectrum();
}

float LightSky::pdf(const Ray* ray) const
{
    return 0;
}

float LightSky::pdf(const Point3* p, const Vec3* wi) const
{
    return 0;
}

bool LightSky::renderable() const
{
    return true;
}

LightSky::LightSky(const TextureImage* tex, const Point3& scene_centre, float world_rad)
:Light(0),skytexture(tex),distribution(tex->get_side()*tex->get_side()) //skydome does not use the intensity, so it is set to 0
{

    //create the light2world matrix
    Matrix4 light2world;
    light2world.set_rotate_z(tex->get_shift().x);
    //TODO: assert that the texture is not shifted vertically
    Matrix4 scale_dome;
    scale_dome.set_scale(world_rad);
    light2world*=scale_dome;
    light2world.inverse(&world2light);

    //create the distribution array (used for importance sample the dome)
    const uint16_t SIDE = tex->get_side();
    const float INV_SIDE = 1.f/SIDE;
    for(int y = 0; y < SIDE; y++)
    {
        const float YPART = y*INV_SIDE;
        const float SINT = std::sinf(ONE_PI*(YPART+.5f)*INV_SIDE);
        for(int x = 0; x< SIDE; x++)
        {
            const float XPART = x*INV_SIDE;
            HitPoint hp;
            hp.uv.x = XPART;
            hp.uv.y = YPART;
            Texel value = skytexture->map_value(&hp).bgra_texel;
            Spectrum spectrum (ColorRGB(value.r, value.g, value.b), true);
            float luminance = spectrum.luminance();
            distribution.set(x, y, luminance*SINT);
        }
    }
}

Spectrum LightSky::radiance_escaped(const Ray* ray)const
{
    Vec3 dir = (world2light*ray->direction).normalize();
    const float THETA = std::acosf(clamp(dir.z, -1.f, 1.f));
    float phi = std::atan2f(dir.y, dir.x);
    if(phi<0)
        phi+=TWO_PI;
    HitPoint hp;
    hp.uv.x = phi*INV_TWOPI;
    hp.uv.y = THETA*INV_PI;
    Texel tex = skytexture->map_value(&hp).bgra_texel;
    return Spectrum(ColorRGB(tex.r, tex.g, tex.b), true);
}
