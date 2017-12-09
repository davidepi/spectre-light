//Created,  11 Aug 2017
//Last Edit  9 Dec 2017

/**
 *  \file bvh.hpp
 *  \brief     Implementation of a bvh acceleration structure, specific for tris
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      9 Dec 2017
 *  \copyright GNU GPLv3
 */


#ifndef __BVH_HPP__
#define __BVH_HPP__

#include "primitives/triangle.hpp"
#include <algorithm>
#include <vector>

///Alpha parameter for AAC. 0.4 for high quality trees, 0.3 for fast buildup
#define AAC_ALPHA 0.3f
///Delta parameter for AAC. 20 for high quality trees, 4 for fast buildup
#define AAC_DELTA 4

/** \struct BvhNode
 *  \brief Node composing  the Bvh
 *
 *  BvhNode represent a node of the Bvh. The Bvh, like the KdTree is flattened
 *  so every node contain its left child on the next position in the array, and
 *  the offset of the right child is given by the \p sibling member. This node
 *  can be either a leaf or an internal node, and this is determine by the value
 *  of the \p len member.
 *  As a leaf, this node reference a particular position of the Triangle* array
 *  passed in the buildTree(), and the next \p len primitives in this array are
 *  contained in the leaf.
 *  As an internal node, the information carried are the offset of the sibling
 *  in the private array of the Bvh and the split axis. The split axis is
 *  used to know which of the two childer should be intersected first, in order
 *  to speed up the bvh traversal
 */
struct BvhNode
{
    ///The bounding box representing the area managed by this node
    AABB bounding;
    union
    {
        ///The offset of the Triangle* array. Only if leaf node
        uint32_t offset;

        ///The sibling of this node. Only if internal node
        uint32_t sibling;
    };

    ///Number of primitives if leaf node, 0 otherwise
    uint8_t len;

    ///Axis considered when grouping. Used for faster traversal
    uint8_t axis;

    ///Padding to reach 32 bytes. Some compilers add this automatically
    uint8_t pad[2]; //compiler should do this automagically
};

/** \class Bvh bvh.hpp accelerators/bvh.hpp
 *  \brief Fast intersection structure
 *
 *  Like the KdTree the bvh is used to speed up intersection. This particular
 *  version is created using a Triangle* array since it will be used to speed up
 *  the intersection of Mesh objects. The BVH is built using the bottom-up
 *  Approximate Agglomerative Clustering technique
 */
class Bvh
{
public:

    ///Default destructor
    ~Bvh();

    /** \brief Build the bvh
     *
     *  Build the Bvh using the Approximate Agglomerative Clustering technique.
     *  This method uses the morton code to find the nearest neighbour of each
     *  Triangle and then groups together the one that will generate the
     *  smallest surface area with the AABB
     *
     *  \param[in] t The array of triangles for which the bvh is built
     *  \param[in] len The number of triangles
     */
    void buildTree(Triangle* t, int len);

    /** \brief Find the closest intersection to a ray
     *
     *  Find the closest intersection of this ray, with the Triangle* array
     *  passed as input in the buildTree() method, in an efficient way
     *
     *  \param[in] r The ray used for the intersection test
     *  \param[in,out] distance As input, the already-found intersection
     *  distance, that will be updated if a closer intersection is found
     *  \param[out] h The hit triangle
     *  \return true if there is an intersection, false otherwise
     */
    bool intersect(const Ray* r, float* distance, HitPoint* h)const;

private:

    //transform the temp build structure in the flattened one
    void flatten(void*,uint32_t*);

    //The flattened tree
    BvhNode* nodesList;

    //A pointer to the array of triangles around which the bvh is built
    Triangle* tris;
};

#endif
