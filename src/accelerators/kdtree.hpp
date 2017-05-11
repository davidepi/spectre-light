//Created,   9 May 2017
//Last Edit 11 May 2017

/**
 *  \file kdtree.hpp
 *  \brief     Implementation of a Kd-tree space subdivision structure
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      11 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __KDTREE_H__
#define __KDTREE_H__

#include "asset.hpp"

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
 *  number of primitives and offset in the primitives array if this node is a
 *  leaf.
 *  The overall size of the class is 8 bytes, to maximize the number of nodes
 *  that can be fit into the cache.
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
     *  Construct this node as a leaf node, by giving the number of primitives
     *  stored in the leaf and an offset to the pointer. The actual storage 
     *  is in the KdTree class and is, obviously, contiguous
     *
     *  \param[in] primitive_offset an integer representing the offset in the
     *  primitive array, in the KdTree class, that contains the first primitive
     *  referenced by this leaf
     *  \param[in] primitive_numbers How many primitives are stored in this
     *  leaf, starting from the one referenced by the offset
     *
     *  \warning Only 29 bits of the \p primitive_numbers value can be used,
     *  thus its maximum value is 536870911
     */
    KdTreeNode(unsigned int primitive_offset, unsigned int primitive_numbers);
    
    ///Default destructor
    ~KdTreeNode();
    
    /* \brief Check if this node is a leaf
     *  
     *  Returns true if this node is a leaf, false otherwise
     *
     *  \return true if this node is a leaf, false otherwise
     */
    bool isLeaf()const;
    
    /* \brief Return the split axis of this node
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
    
    unsigned int getOtherChildOffset()const;
    unsigned int getPrimitiveNumber()const;
    unsigned int getPrimitiveOffset()const;
    
private:
    //private members description in file kdtree.cpp
    union
    {
        float split;
        uint32_t primitive_offset;
    };
    uint32_t data;
};

class KdTree
{
public:
    KdTree();
    ~KdTree();
    void addAsset(Asset* addme);
    void finalize();
    
private:
    void build(unsigned int node, char depth, unsigned int primitive_offset,
               unsigned int primitive_number);
    char maximum_depth;
    
    Asset** primitiveList;
    unsigned int primitive_number;
    unsigned int primitive_allocated;
    
    KdTreeNode* nodeList;
    unsigned int node_index;
    unsigned int nodes_allocated;
};

#endif
