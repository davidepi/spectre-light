//created 4 oct 18
#ifndef __LIGHT_SUN_HPP__
#define __LIGHT_SUN_HPP__

#include "lights/light.hpp"
#include "utility/date.hpp"
#include "utility/spectrum.hpp"

class LightSun : public Light
{
public:
    LightSun(const Spectrum& intensity, Date time, float latitude,
             float longitude, float elevation = 0.01);

    Spectrum sample_surface(float r0, float r1, float r2, float r3, Ray* out,
                            float* pdf) const override;

    Spectrum
    sample_visible_surface(float r0, float r1, const Point3* position, Vec3* wi,
                           float* pdf, float* distance) const override;

    float pdf(const Ray* ray) const override;

    float pdf(const Point3* p, const Vec3* wi) const override;

    bool renderable() const override;
};


#endif
