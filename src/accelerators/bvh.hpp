#ifndef __BVH_HPP__
#define __BVH_HPP__

#include "primitives/triangle.hpp"
#include <algorithm>
#include <vector>

///Alpha parameter for AAC. 0.4 for high quality trees, 0.3 for fast buildup
#define AAC_ALPHA 0.2
///Delta parameter for AAC. 20 for high quality trees, 4 for fast buildup
#define AAC_DELTA 20

struct BvhNode
{
    AABB bounding;
    union
    {
        uint32_t offset;
        uint32_t sibling;
    };
    uint8_t len;
    uint8_t pad[3]; //compiler should do this automagically
};

class Bvh
{
public:
    ~Bvh();
    void buildTree(Triangle* t, int len);

private:
    void flatten(void*,uint32_t*);

    BvhNode* nodesList;
};


#endif
