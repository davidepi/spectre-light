#include "bvh.hpp"

struct Node
{
    Triangle* t;
    uint32_t morton_x;
    uint32_t morton_y;
    uint32_t morton_z;
};

/* Morton code for 3D points, mix of
https://stackoverflow.com/questions/1024754/
and
https://devblogs.nvidia.com/parallelforall/thinking-parallel-part-iii-tree-const
ruction-gpu/
*/

//expand the value so there is enough space for the others components
static inline uint64_t expand(uint64_t val)
{
    //consider only 21 bit. 21x3 = 63
    val &= 0x1FFFFF;
    val = (val | val << 32) & 0x1F00000000FFFF;
    val = (val | val << 16) & 0x1F0000FF0000FF;
    val = (val | val << 8) & 0x100F00f00F00F00F;
    val = (val | val << 4) & 0x10C30C30C30C30C3;
    val = (val | val << 2) & 0x1249249249249249;
    return val;
}

uint64_t mortonCode(float inx, float iny, float inz)
{
    //convert float in range [0,1] to fixed point
    float x = inx*0x1FFFFFU;
    float y = iny*0x1FFFFFU;
    float z = inz*0x1FFFFFU;

    uint64_t xx = expand((uint64_t)x);
    uint64_t yy = expand((uint64_t)y);
    uint64_t zz = expand((uint64_t)z);

    return ((xx << 2) | (yy << 1) | zz);
}

//centroid calc
//float minx = min(min(in->a.p.x,in->b.p.x),in->c.p.x);
//float miny = min(min(in->a.p.y,in->b.p.y),in->c.p.y);
//float minz = min(min(in->a.p.z,in->b.p.z),in->c.p.z);
//float maxx = max(max(in->a.p.x,in->b.p.x),in->c.p.x);
//float maxy = max(max(in->a.p.y,in->b.p.y),in->c.p.y);
//float maxz = max(max(in->a.p.z,in->b.p.z),in->c.p.z);
//float x_centroid = (minx + (maxx-minx))*0.5f;
//float y_centroid = (miny + (maxy-miny))*0.5f;
//float z_centroid = (minz + (maxz-minz))*0.5f;