#include "bvh.hpp"
#ifdef __BMI2__
#include <x86intrin.h>
#endif
#ifdef WIN32 //BMI2 and windows
#include <immintrin.h>
#endif

//f(x) for AAC
#define AAC_FDELTA powf(AAC_DELTA,1-AAC_ALPHA)*0.5*powf(AAC_DELTA,AAC_ALPHA)
#define AAC_F(X) powf(AAC_DELTA,1-AAC_ALPHA)*0.5*powf(X,AAC_ALPHA)

namespace bvhhelpers
{
    struct Primitive
    {
        int index; //index in the primitive array
        uint64_t morton;
        bool operator<(Primitive& b)const
        {
            return Primitive::morton < b.morton;
        }
    };

    class BvhBuildNode
    {
    public:
        AABB bounding;
        BvhBuildNode* left;
        BvhBuildNode* right;
        char split_axis;
        uint32_t offset;
        uint32_t number;

        //init as interior node
        void interior(BvhBuildNode* l, BvhBuildNode* r, char axis)
        {
            split_axis = axis;
            left = l;
            right = r;
            bounding.engulf(l->bounding);
            bounding.engulf(r->bounding);
        }

        //init as leaf node
        void leaf(Shape* sp, uint32_t offset, uint32_t numbers)
        {
            left = NULL;
            right = NULL;
            BvhBuildNode::offset = offset;
            BvhBuildNode::number = numbers;
            for(uint32_t i=offset;i<numbers;i++)
                bounding.engulf((sp+i)->computeAABB());
        }
    };
}

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

static uint64_t mortonCode(float inx, float iny, float inz)
{
    //convert floats in range [0,1] to fixed point
    float x = inx*0x1FFFFFU;
    float y = iny*0x1FFFFFU;
    float z = inz*0x1FFFFFU;

#ifndef __BMI2__ //not Intel >haswell or AMD >ryzord. Probably also on windows

    uint64_t xx = expand((uint64_t)x);
    uint64_t yy = expand((uint64_t)y);
    uint64_t zz = expand((uint64_t)z);

    return (xx | (yy << 1) | (zz << 2));

#else //Haswell and ryzord or newer

    return _pdep_u64((uint64_t)x,0x9249249249249249U) |
           _pdep_u64((uint64_t)y,0x2492492492492492U) |
           _pdep_u64((uint64_t)z,0x4924924924924924U);
#endif
}

using bvhhelpers::BvhBuildNode;
using bvhhelpers::Primitive;

void Bvh::buildTree(Shape* shapes, int size)
{
    Primitive* prims = (Primitive*)malloc(sizeof(Primitive)*size);
    Point3* centroids = (Point3*)malloc(sizeof(Point3)*size);
    AABB centroidaabb;
    for(int i=0;i<size;i++) //calculate centroid AABB
    {
        prims[i].index=i;
        centroids[i] = shapes[i].computeAABB().center();
        centroidaabb.engulf(centroids+i);
    }
    //calculate reciprocal of the centroidaabb, used to map distance in [0-1]
    Vec3 centroidaabb_ext=(centroidaabb.bounds[1]-centroidaabb.bounds[0]);
    centroidaabb_ext.x = 1.f/centroidaabb_ext.x;
    centroidaabb_ext.y = 1.f/centroidaabb_ext.y;
    centroidaabb_ext.z = 1.f/centroidaabb_ext.z;
    for(int i=0;i<size;i++) //maps triangle centroids in [0-1] wrt whole AABB
    {
        Vec3 distance = (centroids[i]-centroidaabb.bounds[0])*centroidaabb_ext;
        //calculate morton code
        prims[i].morton = mortonCode(distance.x,distance.y,distance.z);
    }

    free(centroids);
    std::sort(prims,prims+size);
    uint64_t morton_flag = 0x4000000000000000U;
}