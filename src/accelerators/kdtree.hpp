//Created,   9 May 2017
//Last Edit  9 May 2017

/**
 *  \file kdtree.hpp
 *  \brief     Implementation of a Kd-tree space subdivision structure
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      9 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __KDTREE_H__
#define __KDTREE_H__

#include "asset.hpp"

class KdTreeNode
{
public:
    KdTreeNode();
    ~KdTreeNode();
    
    bool isLeaf()const;
    void setLeaf(bool leaf);
    int getAxis()const;
    void setAxis(int axis);
    
private:
    //split position along the axis
    float split;
    //from most significative bit to least significative one
    //[1 bit] - leaf or not
    //[2 bit] - split axis {0:x, 1:y, 2:z}
    //[29 bit] - index of the array containing primitives
    uint32_t data;
};

#endif
