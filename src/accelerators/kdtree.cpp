#include "kdtree.hpp"

//KdTreeNode member description
// union{ float split; uint32_t primitive_offset;}
// | - non-leaf -> split position along the axis
// | - leaf -> offset in the primitive array pointer

// data
//from most significant bit to least significant one
//[01 bit] - is leaf (could have been embedded into the axis bit...)
//                    |-> In this way I avoid two bitmasks to check if leaf
//[02 bit] - split axis{0:x, 1:y, 2:z, 3: unused}
//[29 bit] -| non-leaf -> pointer of the right nodes
//          | leaf     -> number of primitives

KdTreeNode::KdTreeNode(float split, int axis, unsigned int other_child)
{
#ifdef _LOW_LEVEL_CHECKS_
    critical(!(other_child < 0x20000000), "Too much nodes in the kdtree");
#endif
    KdTreeNode::data = other_child;
    if(axis == 1) // could have been done also with a shift... nvm
        /* This line goes bad if there is already something in the two most
           significant bits. However if they are not zero, the other_child
           variable would be too high and the application doomed anyway */
        KdTreeNode::data |= 0x20000000;
    else if(axis == 2)
        KdTreeNode::data |= 0x40000000;
    KdTreeNode::split = split;
}

KdTreeNode::KdTreeNode(unsigned int primitive_offset, unsigned int p_number)
{
#ifdef _LOW_LEVEL_CHECKS_
    critical(p_number>=0x20000000, "Too much primitives in one KdTreeNode");
#endif
    KdTreeNode::primitive_offset = primitive_offset;
    KdTreeNode::data = p_number;
    KdTreeNode::data |= 0x80000000;
    
}

KdTreeNode::~KdTreeNode()
{
    
}

bool KdTreeNode::isLeaf()const
{
    return KdTreeNode::data & 0x80000000;
}

int KdTreeNode::getAxis()const
{
    return (KdTreeNode::data & 0x60000000) >> 29;
}

unsigned int KdTreeNode::getOtherChildOffset()const
{
    return KdTreeNode::data & 0x1FFFFFFF;
}

unsigned int KdTreeNode::getPrimitiveOffset()const
{
    return KdTreeNode::primitive_offset;
}

unsigned int KdTreeNode::getPrimitiveNumber()const
{
    return KdTreeNode::data & 0x7FFFFFFF;
}

KdTree::KdTree()
{
    KdTree::tempList = new std::vector<Asset *>();
    KdTree::primitiveNumber = 0;
    //KdTreeNode::nodeList = malloc(
}
