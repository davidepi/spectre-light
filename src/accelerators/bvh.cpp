#include "bvh.hpp"

struct Node
{
    Triangle* t;
    uint32_t morton_x;
    uint32_t morton_y;
    uint32_t morton_z;
};

/* Morton code for 3D points, mix of
https://stackoverflow.com/questions/26856268
and
https://devblogs.nvidia.com/parallelforall/thinking-parallel-part-iii-tree-const
ruction-gpu/
*/

//maps [-FLT_MAX,FLT_MAX] to [0,UINT_MAX]
static inline uint64_t adjust(uint64_t val, char sign)
{
    return (((val & 0x7FFFFFFFL) ^ sign) - sign) + 0x7FFFFFFFL;
}

//expand the value so there is enough space for the others components
static inline uint64_t expand(uint64_t val)
{
    val = (val | (val << 16)) & 0x00FF0000FF0000FFU; //interleave by 16
    val = (val | (val <<  8)) & 0xF00F00F00F00F00FU; //interleave by 8
    val = (val | (val <<  4)) & 0x30C30C30C30C30C3U; //interleave by 4
    val = (val | (val <<  2)) & 0x9249249249249249U; //interleave by 2
    return val;
}

uint64_t mortonCode(float inx, float iny, float inz)
{

    //use x y z as weird integers, do not touch the values, use same bits
    unsigned x = reinterpret_cast<unsigned&>(inx);
    unsigned y = reinterpret_cast<unsigned&>(iny);
    unsigned z = reinterpret_cast<unsigned&>(inz);

    //extract the sign, this time change the bits to represent the truncated val
    char x_sign = (char)(static_cast<int>(x) > 0);
    char y_sign = (char)(static_cast<int>(y) > 0);
    char z_sign = (char)(static_cast<int>(z) > 0);

    uint64_t xx = expand(x);
    uint64_t yy = expand(y);
    uint64_t zz = expand(z);

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