#include "bvh.hpp"
#ifdef __BMI2__
#include <x86intrin.h>
#endif
#ifdef WIN32 //BMI2 and windows
#include <immintrin.h>
#endif

//f(x) for AAC
#define AAC_FD ceil(powf(AAC_DELTA,1-AAC_ALPHA)*0.5*powf(AAC_DELTA,AAC_ALPHA))
#define AAC_F(X) ceil(powf(AAC_DELTA,1-AAC_ALPHA)*0.5*powf(X,AAC_ALPHA))

namespace bvhhelpers
{
    struct Primitive
    {
        int index; //index in the primitive array
        uint64_t morton;

    };
    bool operator<(Primitive& a, Primitive& b)
    {
        return a.morton < b.morton;
    }

    class BvhBuildNode
    {
    public:
        AABB bounding;
        BvhBuildNode* left;
        BvhBuildNode* right;
        uint32_t offset;
        int number;

        //init as interior node
        void interior(BvhBuildNode* l, BvhBuildNode* r)
        {
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

//combine more clusters in order to reach a defined value
//c[in] The clusters that will be combined
//n[in] The desired number of clusters
static void combineCluster(std::vector<BvhBuildNode*>*c, int n)
{
    uint32_t* closest = (uint32_t*)malloc(sizeof(uint32_t)*c->size());
    uint32_t left = 0xFFFFFFFF; //ensure segfault if this is not set
    uint32_t right = 0xFFFFFFFF;
    for(unsigned int i=0;i<c->size();c++)
    {
        //find best pair for this node
        closest[i] = findBestMatch(c,c->at(i));
    }
    while(c->size()>n)
    {
        float best = INFINITY;
        //find best of best-pairs
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

        //merge them together in a new node
        BvhBuildNode* node = new BvhBuildNode();
        node->interior(c->at(left),c->at(right));
        //replace one node with the new one, remove the other. Since I don't
        //care about order I can replace the second with the last and pop the
        //last one
        c->at(left) = node;
        c->at(right) = c->back();
        c->pop_back();

        //update new nodes closest, reflecting previous computations.
        //closest is never shrinked, so c->size()+1 is safe
        closest[right] = closest[c->size()+1];
        closest[left] = findBestMatch(c,c->at(left));

        //update closest node for the one referencing the old left and right
        for(unsigned int i=0;i<c->size();i++)
        {
            if(closest[i]==left || closest[i]==right)
                closest[i] = findBestMatch(c,c->at(i));
        }
    }
    free(closest);
}

//bisects the array of morton codes, when the flag change from 0 to 1
//mc[in] morton code array
//start[in] The start of the portion of codes to consider
//end[in] The end of the portion of codes to consider
//m[in] The morton code bit to consider
uint32_t makePartition(Primitive* mc, uint32_t start, uint32_t end, uint64_t m)
{

    //TODO: not enough primitives

    //delimiters used to fin when bit changes from 0 to 1.
    uint32_t left = start; //points always to 0
    uint32_t right = end; //points always to 1
    uint32_t cur = (left+right)>>1; //find the middle point
    while(cur>left)//divide et impera approach
    {
        if((mc[cur].morton & m)==0)
            left = cur;
        else
            right = cur;
        cur = (left+right)>>1;
    }
    return left;
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
        std::vector<BvhBuildNode*> tmp_cluster;
        tmp_cluster.push_back(node);
        combineCluster(&tmp_cluster,(int)AAC_FD);
        c->insert(c->end(),tmp_cluster.begin(),tmp_cluster.end());
    }
    else
    {
        std::vector<BvhBuildNode*>left;
        std::vector<BvhBuildNode*>right;
        uint32_t part = makePartition(p,offs,offs+len,bit);
        bit>>=1;
        traverseTree(sp,sz,p,offs,part-offs,bit,&left);
        traverseTree(sp,sz,p,part+1,len-part-offs,bit,&right);
        left.insert(left.end(),right.begin(),right.end());
        combineCluster(&left,AAC_F(len));
        c->insert(c->end(),left.begin(),left.end());
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
    traverseTree(shapes,size,prims,0,len,morton_flag,&clusters);
}