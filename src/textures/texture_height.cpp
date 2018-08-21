//
// Created by Davide Pizzolotto on 18/08/21.
//

#include "texture_height.hpp"

TextureHeight::TextureHeight(const TextureImage* image, ImageChannel channel)
        :channel(channel)
{
    TextureHeight::image = image;
}

void TextureHeight::bump(const HitPoint* hp) const
{
    float deltau = 0.5f*(fabsf(hp->du.x)+fabsf(hp->du.y));
    float deltav = 0.5f*(fabsf(hp->dv.x)+fabsf(hp->dv.y));
    if(deltau == 0)
        deltau += 1e-2f;
    if(deltav == 0)
        deltav += 1e-2f;
    float uvu = hp->uv.x+deltau;
    float uvv = hp->uv.y+deltav;
    Normal nn = (Normal)(cross(hp->geometric.dpdu, hp->geometric.dpdv));

    HitPoint shift_u;
    shift_u.uv = Point2(uvu, hp->uv.y);
    shift_u.du = hp->du;
    shift_u.dv = hp->dv;

    HitPoint shift_v;
    shift_v.uv = Point2(hp->uv.x, uvv);
    shift_v.du = hp->du;
    shift_v.dv = hp->dv;

    Texel tex;
    uint8_t original;
    uint8_t shifted_u;
    uint8_t shifted_v;

    tex = image->map_value(hp).bgra_texel;
#ifndef IS_BIG_ENDIAN
    original = *(&(tex.a)+channel);
#else
    original = *(&(tex.b)+channel);
#endif

    tex = image->map_value(&shift_u).bgra_texel;
#ifndef IS_BIG_ENDIAN
    shifted_u = *(&(tex.a)+channel);
#else
    shifted_u = *(&(tex.b)+channel);
#endif

    tex = image->map_value(&shift_v).bgra_texel;
#ifndef IS_BIG_ENDIAN
    shifted_v = *(&(tex.a)+channel);
#else
    shifted_v = *(&(tex.b)+channel);
#endif

    hp->shading.dpdu = hp->geometric.dpdu+
                       (Vec3)(hp->geometric.n*(shifted_u-original)/deltau);
    hp->shading.dpdv = hp->geometric.dpdv+
                       (Vec3)(hp->geometric.n*(shifted_v-original)/deltav);
    hp->shading.n = (Normal)cross(hp->shading.dpdu, hp->shading.dpdv);
    hp->shading.n.normalize();
}
