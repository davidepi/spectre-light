#include "kdtree.hpp"
#define KDNODE_ALLOC 0

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
    KdTreeNode::asset_offset = primitive_offset;
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

unsigned int KdTreeNode::getAssetOffset()const
{
    return KdTreeNode::asset_offset;
}

unsigned int KdTreeNode::getAssetsNumber()const
{
    return KdTreeNode::data & 0x7FFFFFFF;
}

// <><><><><><><>    KdTreeBuildNode

KdTreeBuildNode::KdTreeBuildNode(float s, int a, unsigned int o_c)
: KdTreeNode(s,a,o_c)
{
    
}

KdTreeBuildNode::KdTreeBuildNode(unsigned int assets_number)
: KdTreeNode(0,assets_number)
{
    
}

KdTreeBuildNode::~KdTreeBuildNode()
{
    
}

void KdTreeBuildNode::addAsset(Asset* a)
{
    KdTreeBuildNode::container.push_back(a);
}

Asset* KdTreeBuildNode::retrieveLastAsset()
{
    Asset* retval = KdTreeBuildNode::container.back();
    KdTreeBuildNode::container.pop_back();
    return retval;
}

Asset* KdTreeBuildNode::retrieveAsset(int n)
{
    Asset* retval = KdTreeBuildNode::container.at(n);
    //not very efficient, but this class is used just for building the tree.
    KdTreeBuildNode::container.erase(KdTreeBuildNode::container.begin()+n);
    return retval;
}


// <><><><><><><>    KdTree

KdTree::KdTree()
{
    KdTree::assetsList = (Asset**)malloc(sizeof(Asset*)*KDNODE_ALLOC);
    KdTree::assets_number = 0;
    KdTree::assets_allocated = KDNODE_ALLOC;
    
    KdTree::nodesList=(KdTreeNode*)malloc(sizeof(KdTreeNode)* KDNODE_ALLOC);
    KdTree::nodes_index = 0;
    KdTree::nodes_allocated = KDNODE_ALLOC;
    
    if(KdTree::assetsList == NULL || KdTree::nodesList == NULL)
        critical("Out of memory [Kd-Tree init]");
}

KdTree::~KdTree()
{
    free(assetsList);
    free(nodesList);
}

void KdTree::addAsset(Asset *addme)
{
    if(nodes_index == nodes_allocated)
    {
        unsigned int allocNo = max(assets_allocated<<1,_MAX_ASSETS_);
        Asset** tmp = (Asset**)malloc(sizeof(Asset*)*(allocNo));
        if(tmp)
        {
            memcpy(tmp,assetsList,assets_allocated*sizeof(KdTreeNode));
            assets_allocated=allocNo;
            free(KdTree::assetsList);
            KdTree::assetsList = tmp;
        }
        else
            critical("Out of memory [Kd-Tree building]");
    }
    assetsList[assets_number++] = addme;
}

void KdTree::finalize()
{
    //TODO: copy tempbuilder to nodesList
}

void KdTree::buildTree()
{
    if(assets_number == 0)
        return;
    tempbuilder = new std::vector<KdTreeBuildNode>();
    AABB tmp = AABB(*(assetsList[0]->getAABB)());
    for(int i=1;i<assets_number;i++)
        tmp.engulf(assetsList[i]->getAABB());
    //build
    finalize(); //copy tempbuilder to nodesList and the assets into assetsList
    delete tempbuilder;
}

void KdTree::build(unsigned int node, char depth, unsigned int a_n,
                   AABB area)
{
    //terminate recursion
    if(depth==maximum_depth || a_n <= _LEAF_ASSETS_)
    {
        //nodesList[node] = KdTreeNode(p_start,p_num); //this is a leaf
        return;
    }
    else
    {
        //TODO: split + recursive step
    }
}
