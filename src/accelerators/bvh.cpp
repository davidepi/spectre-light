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
        int number;

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
        void leaf(AABB& box, uint32_t offset, int numbers)
        {
            left = NULL;
            right = NULL;
            BvhBuildNode::offset = offset;
            BvhBuildNode::number = numbers;
            bounding.engulf(box);
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

//given a cluster and an element, find the index of the closest node to that
//element in the cluster
static uint32_t findBestMatch(std::vector<BvhBuildNode*>*c, BvhBuildNode* b)
{
    float best_area = INFINITY;
    uint32_t retval = 0xFFFFFFFF;
    for(unsigned int i=0;i<c->size();i++) //linear search
    {
        if(c->at(i)!=b)
        {
            AABB unionbox = c->at(i)->bounding+b->bounding;
            float val = unionbox.surface();
            if(val<best_area)
            {
                retval = i;
                best_area = val;
            }
        }
    }
    return retval;
}

static std::vector<BvhBuildNode*>* combineCluster(std::vector<BvhBuildNode*>*c,
uint32_t n)
{
    uint32_t* closest = (uint32_t*)malloc(sizeof(uint32_t)*c->size());
    uint32_t left;
    uint32_t right;
    for(unsigned int i=0;i<c->size();c++)
    {
        //find best pair for this node
        closest[i] = findBestMatch(c,c->at(i));
    }
    while(c->size()>n)
    {
        float best = INFINITY;
        //find best surface for the best pair of nodes
        for(unsigned int i=0;i<c->size();i++)
        {
            float val;
            val = (c->at(i)->bounding + c->at(closest[i])->bounding).surface();
            if(val<best)
            {
                best = val;
                left = i;
                right = closest[i];
            }
        }

        //TODO: new cluster
    }
}

//Algorithm 3 of the AAC paper, BuildTree(P)
//sp[in] the original array of shapes
//sz[in] the size of the shapes (since it could be derived)
//p[in] The primitive array that matches sp element with their morton codes
//offs[in] offset of the primitive array
//len[in] how many elements of the primitive array will be considered
//c[out] cluster array
//bit[in] partition bit for morton code
static void traverseTree(Shape* sp, size_t sz, Primitive* p, uint32_t offs, int len,
                         uint64_t bit, std::vector<BvhBuildNode*>* c)
{
    if(len < AAC_DELTA)
    {
        AABB bounding;
        BvhBuildNode* node = new BvhBuildNode;
        for(int i=0;i<len;i++)
            //offset and len refers to the Primitive* array, Shape* is in a
            //totally different order, this is the reason of this pointer calc.
            bounding.engulf((sp+p[offs+i].index*sz)->computeAABB());
        node->leaf(bounding,offs,len);
        c->push_back(node);

        //TODO: combine cluster
    }
    else
    {

    }
}

void Bvh::buildTree(Shape* shapes, size_t size, int len)
{
    Primitive* prims = (Primitive*)malloc(sizeof(Primitive)*len);
    Point3* centroids = (Point3*)malloc(sizeof(Point3)*len);
    AABB centroidaabb;
    for(int i=0;i<len;i++) //calculate centroid AABB
    {
        prims[i].index=i;
        centroids[i] = (shapes+(i*size))->computeAABB().center();
        centroidaabb.engulf(centroids+i);
    }
    //calculate reciprocal of the centroidaabb, used to map distance in [0-1]
    Vec3 centroidaabb_ext=(centroidaabb.bounds[1]-centroidaabb.bounds[0]);
    centroidaabb_ext.x = 1.f/centroidaabb_ext.x;
    centroidaabb_ext.y = 1.f/centroidaabb_ext.y;
    centroidaabb_ext.z = 1.f/centroidaabb_ext.z;
    for(int i=0;i<len;i++) //maps triangle centroids in [0-1] wrt whole AABB
    {
        Vec3 distance = (centroids[i]-centroidaabb.bounds[0])*centroidaabb_ext;
        //calculate morton code
        prims[i].morton = mortonCode(distance.x,distance.y,distance.z);
    }

    free(centroids);
    std::sort(prims,prims+len);
    uint64_t morton_flag = 0x4000000000000000U;

    std::vector<BvhBuildNode*> clusters;
}