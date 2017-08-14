#ifndef __BVH_HPP__
#define __BVH_HPP__

#include "primitives/triangle.hpp"
#include <algorithm>
#include <vector>

///Alpha parameter for AAC. 0.4 for high quality trees, 0.3 for fast buildup
#define AAC_ALPHA 0.2
///Delta parameter for AAC. 20 for high quality trees, 4 for fast buildup
#define AAC_DELTA 20

class Bvh
{
    void buildTree(Shape* primitives, size_t obj_size, int len);
};


#endif
