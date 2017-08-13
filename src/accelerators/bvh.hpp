#ifndef __BVH_HPP__
#define __BVH_HPP__

#include "primitives/triangle.hpp"
#include <algorithm>

class Bvh
{
    void buildTree(Triangle* primitives, int size);
};


#endif
