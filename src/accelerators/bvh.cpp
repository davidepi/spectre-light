//author: Davide Pizzolotto
//license: GNU GPLv3

#include <cmath>
#include "bvh.hpp"

#ifdef __BMI2__
#include <x86intrin.h> //for pdep
#endif

#ifdef _WIN32 //BMI2 and windows
#include <intrin.h> //for bsf
#include <immintrin.h> //for pdep
#endif

/**
 * \cond
 *  No documentation for these helper things
 */

//f(x) for AAC
#define AAC_FD ceilf(powf(AAC_DELTA,1-AAC_ALPHA)*0.5f*powf(AAC_DELTA,AAC_ALPHA))
#define AAC_F(X) ceilf(powf(AAC_DELTA,1-AAC_ALPHA)*0.5f*powf(X,AAC_ALPHA))

namespace bvhhelpers
{
    struct Primitive
    {
        int index; //index in the primitive array
        uint64_t morton;

        bool operator<(const Primitive& b) const
        {
            return Primitive::morton<b.morton;
        }

    };

    class BvhBuildNode
    {
    public:
        AABB bounding;
        BvhBuildNode* left;
        BvhBuildNode* right;
        uint32_t offset;
        int number;
        char split;

        //init as interior node
        void interior(BvhBuildNode* l, BvhBuildNode* r, char split_axis)
        {
            left = l;
            right = r;
            bounding.engulf(l->bounding);
            bounding.engulf(r->bounding);
            split = split_axis;
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

static inline char BSF(uint64_t val)
{
#ifdef _WIN32
    unsigned long out;
    _BitScanForward64(&out,val);
    return (char)out;
#else
    return (char)__builtin_ffsll(val);
#endif
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
static uint32_t findBestMatch(std::vector<BvhBuildNode*>* c, BvhBuildNode* b)
{
    float best_area = INFINITY;
    uint32_t retval = 0; //if size == 1 return myself
    for(unsigned int i = 0; i<c->size(); i++) //linear search
    {
        if(c->at(i) != b)
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
//return number of nodes created
static uint32_t combineCluster(std::vector<BvhBuildNode*>* c, int n, char axis)
{
    uint32_t created = 0;
    uint32_t* closest = (uint32_t*)malloc(sizeof(uint32_t)*c->size());
    uint32_t left = 0xFFFFFFFF; //ensure segfault if this is not set
    uint32_t right = 0xFFFFFFFF;
    if((int)c->size()>n) //calculate best pair only if needed
    {
        for(unsigned int i = 0; i<c->size(); i++)
        {
            //find best pair for this node
            BvhBuildNode* at = c->at(i);
            closest[i] = findBestMatch(c, at);
        }
    }
    while((int)c->size()>n)
    {
        float best = INFINITY;
        //find best of best-pairs
        for(unsigned int i = 0; i<c->size(); i++)
        {
            float val;
            val = (c->at(i)->bounding+c->at(closest[i])->bounding).surface();
            if(val<best)
            {
                best = val;
                left = i;
                right = closest[i];
            }
        }

        //merge them together in a new node
        BvhBuildNode* node = new BvhBuildNode();
        created++;
        node->interior(c->at(left), c->at(right), axis);
        //replace one node with the new one, remove the other. Since I don't
        //care about order I can replace the second with the last and pop the
        //last one
        c->at(left) = node;
        c->at(right) = c->back();
        c->pop_back();

        if((int)c->size()>n)
        {
            //update new nodes closest, reflecting previous computations.
            //closest is never shrinked, so c->size() is safe
            //c, instead, has already been shrinked so c->size() points to the
            //previous last element
            closest[right] = closest[c->size()];
            closest[left] = findBestMatch(c, c->at(left));

            //update closest node for the one referencing the old left and right
            for(unsigned int i = 0; i<c->size(); i++)
            {
                //first check. left and right intended to be the old nodes,
                //now removed. So I need to update the values
                if(closest[i] == left || closest[i] == right)
                    closest[i] = findBestMatch(c, c->at(i));

                //second check. If this point to c->size, the node removed at
                //the end, it should point to the ACTUAL node in right
                if(closest[i] == c->size())
                    closest[i] = right;
            }
        }
    }
    free(closest);
    return created;
}

//bisects the array of morton codes, when the flag change from 0 to 1
//mc[in] morton code array
//start[in] The start of the portion of codes to consider
//end[in] The end of the portion of codes to consider
//m[in] The morton code bit to consider
static uint32_t makePartition(Primitive* mc, uint32_t start, uint32_t end,
                              uint64_t m)
{
    //every bit considered is equal || morton code is 0
    if(((mc[start].morton & m) == (mc[end].morton & m)) || m == 0x0)
        return (start+((end-start) >> 1));

    //delimiters used to fin when bit changes from 0 to 1.
    uint32_t left = start; //points always to 0
    uint32_t right = end; //points always to 1
    uint32_t cur = (left+right) >> 1; //find the middle point
    while(cur>left)//divide et impera approach
    {
        if((mc[cur].morton & m) == 0)
            left = cur;
        else
            right = cur;
        cur = (left+right) >> 1;
    }
    return left;
}

//Algorithm 3 of the AAC paper, BuildTree(P)
//tris[in] The array of triangles
//p[in] The primitive array that matches sp element with their morton codes
//offs[in] offset of the primitive array
//len[in] how many elements of the primitive array will be considered
//c[out] cluster array
//bit[in] partition bit for morton code
//return number of nodes created
static uint32_t traverseTree(Triangle* tris, Primitive* p, uint32_t offs,
                             int len, uint64_t bit,
                             std::vector<BvhBuildNode*>* c)
{
    if(len == 0)
        return 0;
    uint32_t created = 0;
    char axis = BSF(bit)%3;
    if(len<AAC_DELTA)
    {
        AABB bounding;
        BvhBuildNode* node = new BvhBuildNode;
        created++;
        for(int i = 0; i<len; i++)
            bounding.engulf(tris[p[offs+i].index].compute_AABB());
        node->leaf(bounding, offs, len);
        std::vector<BvhBuildNode*> tmp_cluster;
        tmp_cluster.push_back(node);
        created += combineCluster(&tmp_cluster, (int)(AAC_FD), axis);
        c->insert(c->end(), tmp_cluster.begin(), tmp_cluster.end());
    }
    else
    {
        std::vector<BvhBuildNode*> left;
        std::vector<BvhBuildNode*> right;
        uint32_t part = makePartition(p, offs, offs+len-1, bit);
        bit >>= 1;
        created += traverseTree(tris, p, offs, part-offs, bit, &left);
        created += traverseTree(tris, p, part, offs+len-part, bit, &right);
        left.insert(left.end(), right.begin(), right.end());
        created += combineCluster(&left, (int)AAC_F((float)len), axis);
        c->insert(c->end(), left.begin(), left.end());
    }
    return created;
}

/**
 *  \endcond
 */

// <><><><><><><><> Bvh methods <><><><><><><><><><><><><><><><><><><><><><><><>

Bvh::~Bvh()
{
    free(nodesList);
}

void Bvh::buildTree(Triangle* tris, int len)
{
    Bvh::tris = tris;
    if(len<AAC_DELTA) //small mesh
    {
        Bvh::nodesList = (BvhNode*)malloc(sizeof(BvhNode));
        Bvh::nodesList[0].len = (uint8_t)len;
        Bvh::nodesList[0].offset = 0;
        Bvh::nodesList[0].bounding = AABB(); //init aabb to avoid wrong engulf
        for(int i = 0; i<len; i++)
            Bvh::nodesList[0].bounding.engulf(tris[i].compute_AABB());
        return;
    }
    Primitive* prims = (Primitive*)malloc(sizeof(Primitive)*len);
    Point3* centroids = (Point3*)malloc(sizeof(Point3)*len);
    AABB centroidaabb;
    for(int i = 0; i<len; i++) //calculate centroid AABB
    {
        prims[i].index = i;
        centroids[i] = tris[i].compute_AABB().center();
        centroidaabb.engulf(centroids+i);
    }
    //calculate reciprocal of the centroidaabb, used to map distance in [0-1]
    Vec3 centroidaabb_ext = (centroidaabb.bounds[1]-centroidaabb.bounds[0]);
    centroidaabb_ext.x = 1.f/centroidaabb_ext.x;
    centroidaabb_ext.y = 1.f/centroidaabb_ext.y;
    centroidaabb_ext.z = 1.f/centroidaabb_ext.z;
    for(int i = 0; i<len; i++) //maps triangle centroids in [0-1] wrt whole AABB
    {
        Vec3 distance = (centroids[i]-centroidaabb.bounds[0])*centroidaabb_ext;
        //calculate morton code
        prims[i].morton = mortonCode(distance.x, distance.y, distance.z);
    }

    free(centroids);
    std::sort(prims, prims+len);
    uint64_t morton_flag = 0x4000000000000000U;

    std::vector<BvhBuildNode*> clusters;
    uint32_t created;
    created = traverseTree(tris, prims, 0, len, morton_flag, &clusters);
    created += combineCluster(&clusters, 1, BSF(morton_flag)%3);
    //bvh completed

    //flatten the tree into an array, like the kdtree one
    Bvh::nodesList = (BvhNode*)malloc(created*sizeof(BvhNode));
    if(clusters.size()>1)
    {
        fprintf(stderr, "Node number error"); //TODO removeme
    }
    uint32_t index = 0;

    flatten(clusters.at(0), &index);

    //reorder the Triangle* array
    //this is actually horrible but I don't want to deallocate array under
    //the hood. I really hope that memcpying the whole array is smh fast
    Triangle* tmp = (Triangle*)malloc(sizeof(Triangle)*len);
    memcpy((void*)tmp, (void*)tris,
           sizeof(Triangle)*len);//create reference copy
    for(int i = 0; i<len; i++)
    {
        tris[i].a = tmp[prims[i].index].a; //copy from the reference
        tris[i].b = tmp[prims[i].index].b;
        tris[i].c = tmp[prims[i].index].c;
    }
    free(tmp);
    free(prims);
}

void Bvh::flatten(void* n, uint32_t* index)
{
    BvhBuildNode* node = (BvhBuildNode*)n;
    if(node->left == NULL) //leaf
    {
        nodesList[*index].bounding = node->bounding;
        nodesList[*index].offset = node->offset;
        nodesList[*index].len = (uint8_t)node->number;
        (*index)++;
    }
    else
    {
        //record my position for later use and update it, so I can call the
        //recursive step
        uint32_t myindex = (*index)++;

        //left node is right after the parent, right node is somewhere else
        flatten(node->left, index);

        //I processed all the left nodes, so now I know the right node position
        nodesList[myindex].bounding = node->bounding;
        nodesList[myindex].sibling = *index;
        nodesList[myindex].len = 0;
        nodesList[myindex].axis = (uint8_t)(node->split);
        flatten(node->right, index);
    }
    delete (node);
}

///Max depth of the Bvh tree
#define BVH_MAX_DEPTH 32

bool Bvh::intersect(const Ray* r, float* distance, HitPoint* h,
                    const MaskBoolean* mask) const
{
    RayProperties rp(*r);
    float dmin;
    float dmax;
    bool found = false;

    BvhNode* jobs[BVH_MAX_DEPTH];
    unsigned char jobs_stack_top = 0;
    BvhNode* node = Bvh::nodesList;
    while(node != NULL)
    {
        if(node->bounding.intersect(r, &rp, &dmin, &dmax) &&
           !(found && dmin>*distance))//already found a closer one
        {
            if(node->len>0) //is leaf
            {
                for(int i = 0; i<node->len; i++)
                {
                    unsigned int tmp_index = node->offset+i;
                    if(Bvh::tris[tmp_index].intersect(r, distance, h, mask))
                    {
                        h->index = tmp_index;
                        found = true;
                    }
                }
                if(jobs_stack_top>0)
                    node = jobs[--jobs_stack_top];
                else
                    break;
            }
            else //interior node
            {
                if(*(&rp.isXInvNeg+node->axis))//better try the other side first
                {
                    jobs[jobs_stack_top++] = node+1;
                    node = nodesList+node->sibling;
                }
                else
                {
                    jobs[jobs_stack_top++] = nodesList+node->sibling;
                    node = node+1;
                }
            }
        }
        else //try next node
        if(jobs_stack_top>0)
            node = jobs[--jobs_stack_top];
        else
            break;
    }

    return found;
}
