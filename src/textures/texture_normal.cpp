//author: Davide Pizzolotto
//license: GNU GPLv3

#include "texture_normal.hpp"

TextureNormal::TextureNormal(const TextureImage* image)
{
    TextureNormal::image = image;
}

void
TextureNormal::bump(const HitPoint* hp, ShadingSpace* matrix, Point3* point,
                    Normal* normal) const
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
    x -= 1.f;
    y -= 1.f;
    z -= 1.f;

    Vec3 normal_shading(x, y, z);

    ShadingSpace old;
    old.s = hp->dpdu;
    old.n = (Normal)cross(hp->dpdu, hp->dpdv).normalize();
    old.t = cross(old.s, (Vec3)old.n).normalize();

    matrix->n = (Normal)(old.to_world(normal_shading)).normalize();
    matrix->s = (hp->dpdu-
                 (Vec3)(matrix->n*dot(matrix->n, hp->dpdu))).normalize();
    matrix->t = cross(Vec3(matrix->n), matrix->s).normalize();
    *normal = matrix->n;
    *point = hp->point_h;
}
