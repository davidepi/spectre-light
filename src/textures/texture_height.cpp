#include "texture_height.hpp"

TextureHeight::TextureHeight(const TextureImage* image, ImageChannel channel)
        :channel(channel)
{
    TextureHeight::image = image;
}

void TextureHeight::gradient(const HitPoint* hp, float* u, float* v) const
{

    Texel tex;
    uint8_t original;
    uint8_t shifted_u;
    uint8_t shifted_v;
    HitPoint shifted = *hp;
    constexpr const float INV255 = 1.f/255.f;

    tex = image->map_value(hp).bgra_texel;
#ifndef IS_BIG_ENDIAN
    original = *(&(tex.a)+channel);
#else
    original = *(&(tex.b)+channel);
#endif

    float epsilon_u = 0.5f*(fabsf(hp->du.x)+fabsf(hp->du.y));
    if(epsilon_u == 0)
        epsilon_u = 0.01f;
    shifted.point_h = hp->point_h+hp->dpdu*epsilon_u;
    shifted.uv = hp->uv;
    shifted.uv.x += epsilon_u;

    tex = image->map_value(&shifted).bgra_texel;
#ifndef IS_BIG_ENDIAN
    shifted_u = *(&(tex.a)+channel);
#else
    shifted_u = *(&(tex.b)+channel);
#endif

    float epsilon_v = 0.5f*(fabsf(hp->dv.x)+fabsf(hp->dv.y));
    if(epsilon_v == 0.f)
        epsilon_v = 0.01f;
    shifted.point_h = hp->point_h+hp->dpdv*epsilon_v;
    shifted.uv = hp->uv;
    shifted.uv.y += epsilon_v;

    tex = image->map_value(&shifted).bgra_texel;
#ifndef IS_BIG_ENDIAN
    shifted_v = *(&(tex.a)+channel);
#else
    shifted_v = *(&(tex.b)+channel);
#endif

    *u = (shifted_u-original)*INV255/epsilon_u;
    *v = (shifted_v-original)*INV255/epsilon_v;
}

void
TextureHeight::bump(const HitPoint* hp, ShadingSpace* matrix,
                    Normal* normal) const
{
    float u, v;
    gradient(hp, &u, &v);

    Vec3 dpdu = hp->dpdu+(Vec3)(hp->normal_h*(u-dot(hp->normal_h, hp->dpdu)));
    Vec3 dpdv = hp->dpdv+(Vec3)(hp->normal_h*(v-dot(hp->normal_h, hp->dpdv)));
    matrix->n = (Normal)cross(dpdu, dpdv).normalize();
    matrix->s = (dpdu-(Vec3)(matrix->n)*dot(dpdu, matrix->n)).normalize();
    matrix->t = cross(Vec3(matrix->n), matrix->s).normalize();
    if(dot(matrix->n, hp->normal_h)<0)
        matrix->n *= -1;
    *normal = matrix->n;
}
