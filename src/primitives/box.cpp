//author: Davide Pizzolotto
//license: GNU GPLv3

#include "box.hpp"

AABB Box::compute_AABB() const
{
    const Point3 min(0, 0, 0);
    const Point3 max(1, 1, 1);
    return AABB(&min, &max);
}

AABB Box::compute_AABB(const Matrix4* transform) const
{
#ifdef DEBUG
    if(transform == NULL)
    {
        Console.severe(MESSAGE_WORLD_AABB_NULL_MATRIX);
        return AABB();
    }
#endif

    //transforming min and max is not enough for rotation, i.e. in 90 deg rot
    const Point3 p0 = *transform*Point3(0, 0, 0);
    const Point3 p1 = *transform*Point3(1, 0, 0);
    const Point3 p2 = *transform*Point3(1, 1, 0);
    const Point3 p3 = *transform*Point3(0, 1, 0);
    const Point3 p4 = *transform*Point3(0, 0, 1);
    const Point3 p5 = *transform*Point3(1, 0, 1);
    const Point3 p6 = *transform*Point3(1, 1, 1);
    const Point3 p7 = *transform*Point3(0, 1, 1);

    const Point3 pmi = min(
            min(min(min(min(min(min(p0, p1), p2), p3), p4), p5), p6), p7);
    const Point3 pma = max(
            max(max(max(max(max(max(p0, p1), p2), p3), p4), p5), p6), p7);

    return AABB(pmi, pma);
}

int Box::get_faces_number() const
{
    return 6;
}

float Box::surface() const
{
    return 6;
}

float Box::surface(const Matrix4* transform) const
{
    Vec3 scale = transform->get_scale();
    float la = 2*(scale.x+scale.z)*scale.y;
    return la+2*scale.x*scale.z;
}

bool Box::intersect(const Ray* r, float* distance, HitPoint* h,
                    const MaskBoolean* mask) const
{
    bool inside = false;
    float mint;
    float maxt;
    char axis = 0; //used for normal identification

    //x plane
    float invr = 1.0f/r->direction.x;
    float near = (-r->origin.x)*invr;
    float far = (1.f-r->origin.x)*invr;
    if(near>far)
        swap(&near, &far);
    mint = near;
    maxt = far;

    //y plane
    invr = 1.0f/r->direction.y;
    near = (-r->origin.y)*invr;
    far = (1.f-r->origin.y)*invr;
    if(near>far)
        swap(&near, &far);
    if(near>mint)
    {
        mint = near;
        axis = 1;
    }
    maxt = far<maxt?far:maxt;
    if(mint>maxt)
        return false;

    //z plane
    invr = 1.0f/r->direction.z;
    near = (-r->origin.z)*invr;
    far = (1.f-r->origin.z)*invr;
    if(near>far)
        swap(&near, &far);
    if(near>mint)
    {
        mint = near;
        axis = 2;
    }
    maxt = far<maxt?far:maxt;
    if(mint>maxt)
        return false;
    float tmpdistance;
    if(mint>SELF_INTERSECT_ERROR)
        tmpdistance = mint;
    else if(maxt>SELF_INTERSECT_ERROR)
    {
        inside = true;
        tmpdistance = maxt;
    }
    else
        return false;
    if(tmpdistance>*distance || mask->is_masked(h))
        return false;
    else
    {
        *distance = tmpdistance;
        h->point_h = r->apply(*distance);
        h->normal_g = Normal();
        h->normal_g[axis] = (float)(-sign(r->direction[axis]));
        if(inside)
            h->normal_g[axis] *= -1;
        if(h->normal_g.z != 0)
            h->dpdu = Vec3(h->normal_g.z, 0, 0);
        else
            h->dpdu = Vec3(-h->normal_g.y, h->normal_g.x, 0);
        h->index = 0;
        return true;
        //TODO: missing uv generation, and masking should be done after uvs
    }
}

void Box::get_densities_array(const Matrix4* transform, float* array) const
{
    Vec3 scale = transform->get_scale();
    array[0] = scale.x*scale.y;
    array[1] = array[0]*2;
    array[2] = array[1]+(scale.x*scale.z);
    array[3] = array[2]+(scale.x*scale.z);
    array[4] = array[3]+(scale.z*scale.y);
    array[5] = array[4]+(scale.z*scale.y);
}

void Box::sample_point(float r0, float r1, const float* densities, Point3* p,
                       Normal* n) const
{
    //works like the Mesh::getRandomPoint
    //
    // useless drawing referring to the old implementation, but I like it :)
    //
    //   top  botm  front back  left  right
    // |-----|-----|-----|-----|-----|-----|
    // |  y  |  y  |  z  |  z  |  y  |  y  |
    // |-----|-----|-----|-----|-----|-----|
    //    x     x     x     x     z     z
    //
    //The actual interpolation is:
    // - interpolate the sample from 0 to the total surface of the box
    // - find in which face the sample fall using the densities array
    // - from the interpolated sample remove the previous densities and sample
    // - one dimension of the face
    // - use the other sample to sample the other dimension
    // - dimensions can be viewed on the previous schema. The first one is the
    //   one outside the square

    //cd[5] contains the total surface in world space units
    float res = lerp(r0, 0, densities[5]);
    if(res<densities[0])
    {
        //top
        p->x = inverse_lerp(res, 0, densities[0]);
        p->y = r1;
        p->z = 1;
        n->x = 0;
        n->y = 0;
        n->z = 1;
    }
    else if(res<densities[1])
    {
        //bottom
        p->x = inverse_lerp(res-densities[0], 0, densities[1]-densities[0]);
        p->y = r1;
        p->z = 0;
        n->x = 0;
        n->y = 0;
        n->z = -1;
    }
    else if(res<densities[2])
    {
        //front
        p->x = inverse_lerp(res-densities[1], 0, densities[2]-densities[1]);
        p->y = 0;
        p->z = r1;
        n->x = 0;
        n->y = -1;
        n->z = 0;
    }
    else if(res<densities[3])
    {
        //back
        p->x = inverse_lerp(res-densities[2], 0, densities[3]-densities[2]);
        p->y = 1;
        p->z = r1;
        n->x = 0;
        n->y = 1;
        n->z = 0;
    }
    else if(res<densities[4])
    {
        //left
        p->x = 0;
        p->y = r1;
        p->z = inverse_lerp(res-densities[3], 0, densities[4]-densities[3]);
        n->x = -1;
        n->y = 0;
        n->z = 0;
    }
    else
    {
        //right
        p->x = 1;
        p->y = r1;
        p->z = inverse_lerp(res-densities[4], 0, densities[5]-densities[4]);
        n->x = 1;
        n->y = 0;
        n->z = 0;
    }
}
