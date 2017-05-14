//Created,   9 May 2017
//Last Edit 13 May 2017

/**
 *  \file kdtree.hpp
 *  \brief     Implementation of a Kd-tree space subdivision structure
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      13 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __KDTREE_H__
#define __KDTREE_H__

#include "asset.hpp"
#include <vector>

///Defines the minimum number of assests in a leaf
#define _LEAF_ASSETS_ 3

/**
 *  \class KdTreeNode kdtree.hpp accelerators/kdtree.hpp
 * 
 *  KdTreeNode is a component of the KdTree. This class represents every node
 *  of the tree. It can be either a leaf or an internal node and once 
 *  constructed in a way it is necessary to destroy and reconstruct it, in order
 *  to change its type. This class is built to maximize the speed, sacrificing
 *  its ease of use.
 *  The information contained in this class are: the split axis, position of
 *  the split plane and the position of the sibling if this node is internal;
 *  number of assetss and offset in the assets array if this node is a
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
     *  x axis, 1 for the \a y axis and 2 for the \z axis. Every other value
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
    int getAxis()const;
    
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


/** 
 *  \class KdTreeBuildNode kdtree.hpp accelerators/kdtree.hpp
 *
 *  Just like the KdTreeNode class, but with the assets stored in the node.
 *  The only differente between this class and KdTreeNode is the fact that this
 *  one stores the assets in an std::vector inside the node, KdTreeNode stores
 *  them as an offset of a linear array allocated in KdTree.
 *  Since the assets will be reorganized during the kd-tree building, firstly
 *  they are stored inside every node, and when the tree is built, they can be
 *  layed out in a linear array and every KdTreeBuildNode can be replaced by the
 *  corresponding KdTreeNode
 */
class KdTreeBuildNode : public KdTreeNode
{
public:
    
    ///Constructor, see KdTreeNode::KdTreeNode()
    KdTreeBuildNode(float split, int axis, unsigned int other_child);
    
    ///Constructor, see KdTreeNode::KdTreeNode()
    KdTreeBuildNode(unsigned int assets_number);
    
    ///Destructor
    ~KdTreeBuildNode();
    
    /** \brief Add an asset to this node
     *
     *  Add an asset to the ones managed by this node
     *
     *  \param[in] a The asset that will be added to the node
     */
    void addAsset(Asset* a);
    
    /** \brief Retrieve the last asset
     *
     *  Return the last asset from the one referenced by this node, and removes
     *  it from the node
     *
     *  \return The last asset referenced by this node
     */
    Asset* retrieveLastAsset();
    
    /** \brief Retrieve the nth asset
     *
     *  Return the asset at a specific index, from the one referenced by this
     *  node, and then removes it.
     *
     *  \param[in] n The index of the asset that will be retrieved
     *  \return The asset at the specified index
     */
    Asset* retrieveAsset(int n);
    
private:
    //where the assets are stored
    std::vector<Asset*> container;
};

class KdTree
{
public:
    KdTree();
    ~KdTree();
    void addAsset(Asset* addme);
    void buildTree();
    
private:
    void build(unsigned int node, char depth, unsigned int assets_number,
               AABB area);
    void finalize();
    char maximum_depth;
    
    Asset** assetsList;
    unsigned int assets_number;
    unsigned int assets_allocated;
    
    KdTreeNode* nodesList;
    unsigned int nodes_index;
    unsigned int nodes_allocated;
    
    std::vector<KdTreeBuildNode>* tempbuilder;
};

#endif
