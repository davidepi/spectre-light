//Created,   9 May 2017
//Last Edit 10 May 2017

/**
 *  \file kdtree.hpp
 *  \brief     Implementation of a Kd-tree space subdivision structure
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      10 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __KDTREE_H__
#define __KDTREE_H__

#include "asset.hpp"

///Defines the minimum number of assests in a leaf
#define _LEAF_ASSETS_ 3

class KdTreeNode
{
public:
    KdTreeNode(float split, int axis, unsigned int other_child);
    KdTreeNode(unsigned int primitive_offset, unsigned int primitive_numbers);
    ~KdTreeNode();
    
    bool isLeaf()const;
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
