//
// Created by davide on 12/08/18.
//

#include "texture_normal.hpp"

TextureNormal::TextureNormal(const TextureImage* image)
{
    TextureNormal::image = image;
}

void TextureNormal::bump(const HitPoint* hp, ShadingSpace* matrix) const
{
    constexpr const float INV255 = 1.f/255.f;
    TexelUnion res = image->map_value(hp);
    float x = res.bgra_texel.r;
    float y = res.bgra_texel.g;
    float z = res.bgra_texel.b;
    x *= INV255;
    y *= INV255;
    z *= INV255;
    x *= 2.f;
    y *= 2.f;
    z *= 2.f;
    x *= 1.f;
    y *= 1.f;
    z *= 1.f;

    Vec3 normal(x, y, z);

    ShadingSpace old;
    old.s = hp->dpdu;
    old.n = (Normal)cross(hp->dpdu, hp->dpdv);
    old.n.normalize();
    old.t = cross(old.s, (Vec3)old.n);
    old.t.normalize();

    matrix->n = (Normal)(old.to_world(normal));
    matrix->n.normalize();
    matrix->s = (hp->dpdu-(Vec3)(matrix->n*dot(matrix->n, hp->dpdu)));
    matrix->s.normalize();
    matrix->t = cross(Vec3(matrix->n), matrix->s);
    matrix->t.normalize();
}
