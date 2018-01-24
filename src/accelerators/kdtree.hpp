//Created,   9 May 2017
//Last Edit  9 Dec 2017

/**
 *  \file kdtree.hpp
 *  \brief     Implementation of a Kd-tree space subdivision structure
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      9 Dec 2017
 *  \copyright GNU GPLv3
 */


#ifndef __KDTREE_H__
#define __KDTREE_H__

#include "primitives/asset.hpp"
#include "utility/console.hpp"
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstdlib>

///Defines the minimum number of assests in a leaf
#define _LEAF_ASSETS_ 3
///Define the default cost of the intersection in the Surface Area Heuristic
#define SAH_INTERSECT 50
///Define the default cost of descending a node in the Surface Area Heuristic
#define SAH_DESCEND 1
///Define maximum depth of the kd-tree
#define KD_MAX_DEPTH 15

/**
 *  \class KdTreeNode kdtree.hpp accelerators/kdtree.hpp
 *  \brief Node composing the Kd-tree
 *
 *  KdTreeNode is a component of the KdTree. This class represents every node
 *  of the tree. It can be either a leaf or an internal node and once
 *  constructed in a way it is necessary to destroy and reconstruct it, in order
 *  to change its type. This class is built to maximize the speed, sacrificing
 *  its ease of use.
 *  The information contained in this class are: the split axis, position of
 *  the split plane and the position of the sibling if this node is internal;
 *  number of assets and offset in the assets array if this node is a
 *  leaf.
 *  The overall size of the class is 8 bytes, to maximize the number of nodes
 *  that can be fit into the cache.
 *
 *  This class goes along with the KdTree class, and usually provide offsets
 *  to locate the actual stored data in the KdTree class
 */
class KdTreeNode
{
public:
    
    /** Constructor, internal node
     *
     *  Construct this node as an internal node, by giving split position,
     *  split axis and its sibling.
     *
     *  The split axis values are 0 for \a x, 1 for \a y and 2 for \a z
     *
     *  \param[in] split A float representing the coordinate of the plane
     *  that will split the given axis in two
     *  \param[in] axis An integer representing the axis to split. 0 for the \a
     *  x axis, 1 for the \a y axis and 2 for the \a z axis. Every other value
     *  will split the \a x axis
     *  \param[in] other_child An unsigned int representing the offset of the
     *  node's sibling. In the KdTree class every node is in the same array
     *  and this value is the offset of the array base pointer
     *
     *  \warning Only 29 bits of the \p other_child value can be used, thus its
     *  maximum value is 536870911
     */
    KdTreeNode(float split, int axis, unsigned int other_child);
    
    /** Constructor, leaf node
     *
     *  Construct this node as a leaf node, by giving the number of assets
     *  stored in the leaf and an offset to the pointer. The actual storage
     *  is in the KdTree class and is, obviously, contiguous
     *
     *  \param[in] asset_offset an integer representing the offset in the
     *  assets array, in the KdTree class, that contains the first asset
     *  referenced by this leaf
     *  \param[in] assets_number How many assets are stored in this
     *  leaf, starting from the one referenced by the offset
     *
     *  \warning Only 29 bits of the \p assets_number value can be used,
     *  thus its maximum value is 536870911
     */
    KdTreeNode(unsigned int asset_offset, unsigned int assets_number);
    
    ///Default destructor
    ~KdTreeNode();
    
    /** \brief Check if this node is a leaf
     *
     *  Returns true if this node is a leaf, false otherwise
     *
     *  \return true if this node is a leaf, false otherwise
     */
    bool isLeaf()const;
    
    /** \brief Return the split axis of this node
     *
     *  If this node is an internal node, returns 0 if the split axis is the \a
     *  x axis, 1 if the split axis is the \a y axis, 2 if the split axis is the
     *  \a z axis
     *
     *  \return An integer which represent the split axis.
     *
     *  \warning If this node is a leaf the behaviour of this function is
     *  undefined
     */
    char getAxis()const;
    
    /** \brief Return the split value of this node
     *
     *  If this node is an internal node, returns a floating point representing
     *  the position of the plane, perpendicular to  a determined axis, which
     *  splits the scene in two
     *
     *  \return A floating point representing the split position
     *
     *  \warning If this node is a leaf the behaviour of this function is
     *  undefined
     */
    float getSplit()const;
    
    /** \brief Return the pointer to the sibling of this node
     *
     *  If this node is an internal node, returns the offset of the Node array
     *  to locate the sibling of this node
     *
     *  \return The offset of the sibling of this node
     *
     *  \warning If this node is a leaf the behaviour of this function is
     *  undefined
     */
    unsigned int getOtherChildOffset()const;
    
    /** \brief Return the number of assets referenced by the leaf
     *
     *  Return the number of assets that should be considered as
     *  "belonging" to this leaf, starting from the one referenced by the
     *  offset
     *
     *  \return An integer representing the number of assets
     *
     *  \warning If this node is an internal node the behaviour of this function
     *  is undefined
     */
    unsigned int getAssetsNumber()const;
    
    /** \brief Return the offset of the first asset referenced
     *
     *  Return an offset that, once added to the pointer referencing the
     *  array of assets in the KdTree class, should return the first
     *  asset contained in this leaf
     *
     *  \return An integer representing the offset of the first primitive
     *
     *  \warning If this node is an internal node the behaviour of this function
     *  is undefined
     */
    unsigned int getAssetOffset()const;
    
private:
    //private members description in file kdtree.cpp
    union
    {
        float split;
        uint32_t asset_offset;
    };
    uint32_t data;
};

/** \class KdTree kdtree.hpp accelerators/kdtree.hpp
 *  \brief Fast intersection structure
 *
 *  KdTree is a space partitioning data structure, used to improve the speed
 *  of the intersection routines between a Ray and a Shape. This class contains
 *  pointers to assets and with the exposed methods is able to return if
 *  there is an intersection and the hit asset for a given ray
 */
class KdTree
{
public:
    
    ///Default constructor
    KdTree();
    
    ///Default destructor
    ~KdTree();
    
    /** \brief Add an asset to this kd-tree
     *
     *  Add an asset to the ones managed by the kd-tree. The kd-tree stores and
     *  manages only the pointer and the world-space aabb exposed by the asset
     *  class.
     *
     *  \param[in] addme The asset that will be managed by this kd-tree
     */
    void addAsset(const Asset* addme);
    
    /** \brief Build the kd-tree
     *
     *  Recursively construct the optimal kd-tree for the assets added with the
     *  KdTree::addAsset method
     */
    void buildTree();
    
    /** \brief Find the closest intersection to a ray
     *
     *  Find the closest intersection of this ray, with the assets added through
     *  the KdTree::addAsset method, in an efficient way.
     *
     *  \note Remember to build the tree first, or the intersections will always
     *  fail
     *
     *  \param[in] r The ray used for the intersection test
     *  \param[out] hit The hit asset
     *  \return true if there is an intersection, false otherwise
     */
    bool intersect(const Ray* r, HitPoint* hit)const;
    
private:
    
    //recursive step for the build
    void build(void* node, char depth, void* split_candidates,
               Asset** assets_list, unsigned int assets_number, AABB area);
    
    //flatten out the tree into an array
    void finalize(void* node);
    
    //the aabb containing every asset of this kd-tree
    AABB scene_aabb;
    
    //the list of assets managed by this kd-tree
    const Asset** assetsList;
    
    //the number of assets managed and the index of the next insertion
    int assets_number;
    
    //the allocated size of the assetsList array
    int assets_allocated;
    
    //the list of nodes managed by this kd-tree
    KdTreeNode* nodesList;
    
    //the number of nodes managed and the index of the next node inserted
    int nodes_index;
    
    //the allocated size of the nodesList array
    int nodes_allocated;
};

#endif
