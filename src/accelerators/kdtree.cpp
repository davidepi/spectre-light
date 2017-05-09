#include "kdtree.hpp"
KdTreeNode::KdTreeNode()
{
    
}

KdTreeNode::~KdTreeNode()
{
    
}

bool KdTreeNode::isLeaf()const
{
    return KdTreeNode::data & 0x80000000;
}

void KdTreeNode::setLeaf(bool leaf)
{
    if(leaf)
        KdTreeNode::data |= 0x4;
    else
        KdTreeNode::data &= 0xFFFFFFFB;
}

int KdTreeNode::getAxis()const
{
    return (KdTreeNode::data & 0x60000000) >> 29;
}

void KdTreeNode::setAxis(int axis)
{
    KdTreeNode::data &= 
    KdTreeNode::data |= (axis << 29);
        
}
