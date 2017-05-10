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

class KdTreeNode
{
public:
    KdTreeNode(float split, int axis, uint32_t other_child);
    KdTreeNode(uint32_t primitive_offset, uint32_t primitive_number);
    ~KdTreeNode();
    
    bool isLeaf()const;
    int getAxis()const;
    
private:
    //private members description in file kdtree.cpp
    union
    {
        float split;
        uint32_t primitive_offset;
    };
    uint32_t data;
};

#endif
