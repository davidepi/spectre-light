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

char KdTreeNode::getAxis()const
{
    return (KdTreeNode::data & 0x60000000) >> 29;
}

float KdTreeNode::getSplit()const
{
    return split;
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

//Like the KdTreeNode, but with extra variables.
//This is used to build the tree in a 'canonical' way. Then, when ready,
//everything is flattened into the KdTreeNode array
class KdTreeBuildNode
{
public:
    KdTreeBuildNode(){};
    ~KdTreeBuildNode(){};
    
    //where the assets are stored
    Asset** assets_start;
    bool isLeaf;
    char split_axis;
    union
    {
        float split_position;
        unsigned int assets_number;
    };
    KdTreeBuildNode* left;
    KdTreeBuildNode* right;
};

struct SplitCandidate
{
    float pos;
    bool isLeftSide;
    Asset* whoami;
};

bool compare_sc(const SplitCandidate s1, const SplitCandidate s2)
{
    return s1.pos < s2.pos;
}

struct KdTravNode
{
    const KdTreeNode* node;
    float mint;
    float maxt;
};

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
            memcpy(tmp,assetsList,assets_allocated*sizeof(Asset*));
            assets_allocated=allocNo;
            free(KdTree::assetsList);
            KdTree::assetsList = tmp;
        }
        else
            critical("Out of memory [Kd-Tree building]");
    }
    assetsList[assets_number++] = addme;
}

void KdTree::finalize(void* n)
{
    KdTreeBuildNode* node = (KdTreeBuildNode*)n;
    if(nodes_index == nodes_allocated)
    {
        unsigned int allocNo = nodes_allocated<<1;
        KdTreeNode* tmp = (KdTreeNode*)malloc(sizeof(KdTreeNode)*(allocNo));
        if(tmp)
        {
            memcpy(tmp,nodesList,nodes_allocated*sizeof(KdTreeNode));
            nodes_allocated=allocNo;
            free(KdTree::nodesList);
            KdTree::nodesList = tmp;
        }
        else
            critical("Out of memory [Kd-Tree flattening]");
    }
    if(node->isLeaf)
    {
        nodesList[nodes_index++] = KdTreeNode((unsigned int)(node->assets_start-
                                                             assetsList),
                                              node->assets_number);
    }
    else
    {
        unsigned int myindex = nodes_index++;
        finalize(node->left);
        nodesList[myindex] = KdTreeNode(node->split_position,node->split_axis,
                                        nodes_index);
        finalize(node->right);
    }
    free(node);
}

void KdTree::buildTree()
{
    if(assets_number == 0)
        return;
    KdTreeBuildNode* node = new KdTreeBuildNode();
    scene_aabb = AABB(*(assetsList[0]->getAABB)());
    for(int i=1;i<assets_number;i++)
        scene_aabb.engulf(assetsList[i]->getAABB());
    Asset** alcopy = (Asset**)malloc(sizeof(Asset*)*KdTree::assets_number);
    memcpy(alcopy, KdTree::assetsList, KdTree::assets_number);
    unsigned int a_n = KdTree::assets_number; //assets_number will be set to 0
    KdTree::assets_number = 0;//and assets will be reinserted in order during
                              //building of the kd-tree
    SplitCandidate** sc = (SplitCandidate**)malloc(sizeof(SplitCandidate*)*3);
    sc[0] = (SplitCandidate*)malloc(sizeof(SplitCandidate)*2*a_n);
    sc[1] = (SplitCandidate*)malloc(sizeof(SplitCandidate)*2*a_n);
    sc[2] = (SplitCandidate*)malloc(sizeof(SplitCandidate)*2*a_n);
    
    build(node,0,sc,alcopy,a_n,scene_aabb);

    free(alcopy);
    free(sc[0]);
    free(sc[1]);
    free(sc[2]);
    free(sc);
    finalize(node); //copy tempbuilder to nodesList and the assets into assetsList
}

void KdTree::build(void* n, char depth, void* s_c, Asset** a_l,
                   unsigned int a_n, const AABB area)
{
    //based on pbrt's algorithm
    
    KdTreeBuildNode* node = (KdTreeBuildNode*)n;
    //terminate recursion
    if(depth==KD_MAX_DEPTH || a_n <= _LEAF_ASSETS_)
    {
        node->assets_start = KdTree::assetsList+KdTree::assets_number;
        node->assets_number = a_n;
        for(int i=0;i<a_n;i++)
            KdTree::addAsset(a_l[i]);
        node->isLeaf = true;
        node->left = NULL;
        node->right = NULL;
        return;
    }
    SplitCandidate** sc = (SplitCandidate**)s_c;
    int best_axis = -1;
    int best_split = -1;
    float best_cost = INFINITY;
    float old_cost = SAH_INTERSECT*(float)a_n;
    float total_area = area.surface();
    Vec3 aabb_diagonal = area.bounds[1] - area.bounds[0];
    float inv_area = 1.f/total_area;
    
    int axis = area.longest_axis();
    int isSearching = 3;
    
    while(isSearching)
    {
        for(int i=0;i<a_n;i++)
        {
            sc[axis][i<<1].pos = a_l[i]->getAABB()->bounds[0][axis];
            sc[axis][i<<1].whoami = a_l[i];
            sc[axis][i<<1].isLeftSide = true;
            sc[axis][(i<<1)+1].pos = a_l[i]->getAABB()->bounds[1][axis];
            sc[axis][(i<<1)+1].whoami = a_l[i];
            sc[axis][(i<<1)+1].isLeftSide = false;
        }
        std::sort(&(sc[axis][0]),&(sc[axis][2*a_n]),compare_sc);
        
        unsigned int below = 0,above = a_n;
        for(int i=0;i<2*a_n;i++)
        {
            bool isAABBRightSide = !(sc[axis][i].isLeftSide);
            if(isAABBRightSide)
                --above;
            if(sc[axis][i].pos > area.bounds[0][axis] &&
               sc[axis][i].pos < area.bounds[1][axis])
            {
                char otheraxis1 = (axis+1)%3;
                char otheraxis2 = (axis+2)%3;
                float belowSA=2*(aabb_diagonal[otheraxis1]*
                                 aabb_diagonal[otheraxis2]
                                 +(sc[axis][i].pos - area.bounds[0][axis])*
                                 (aabb_diagonal[otheraxis1]
                                  +aabb_diagonal[otheraxis2]));
                float aboveSA=2*(aabb_diagonal[otheraxis1]*
                                 aabb_diagonal[otheraxis2]
                                 +(sc[axis][i].pos - area.bounds[1][axis])*
                                 (aabb_diagonal[otheraxis1]
                                  +aabb_diagonal[otheraxis2]));
                float pb = belowSA * inv_area;
                float pa = aboveSA * inv_area;
                float bonus = (above == 0 || below == 0) ? KD_BONUS_VAL : 0;
                float cost =  SAH_DESCEND +
                              SAH_INTERSECT * bonus * (pb * below + pa * above);
                if(cost < best_cost)
                {
                    best_cost = cost;
                    best_axis = axis;
                    best_split = i;
                }
            }
            if(!isAABBRightSide)
                ++below;
        }
        if(best_axis == -1)
        {
            isSearching--;
            axis = (axis+1)%3;
        }
    }
    if((best_cost > 4.0 * old_cost && a_n < 16) || best_axis == -1)
    {
        node->assets_start = KdTree::assetsList+KdTree::assets_number;
        node->assets_number = a_n;
        for(int i=0;i<a_n;i++)
            KdTree::addAsset(a_l[i]);
        node->isLeaf = true;
        node->left = NULL;
        node->right = NULL;
        return;
        return;
    }
    KdTreeBuildNode* left = (KdTreeBuildNode*)malloc(sizeof(KdTreeBuildNode));
    KdTreeBuildNode* right = (KdTreeBuildNode*)malloc(sizeof(KdTreeBuildNode));
    Asset** as_below = (Asset**)malloc(sizeof(Asset*)*a_n);
    Asset** as_above = (Asset**)malloc(sizeof(Asset*)*a_n*(KD_MAX_DEPTH+1));
    
    unsigned int as_below_index = 0;
    unsigned int as_above_index = 0;
    for(int i=0;i<best_split;i++)
        if(sc[best_axis][i].isLeftSide)
            as_below[as_below_index++] = sc[best_axis][i].whoami;
    for(int i=best_split+1;i<2*a_n;i++)
        if(!(sc[best_axis][i].isLeftSide))
           as_above[as_above_index++] = sc[best_axis][i].whoami;
    
    node->isLeaf = false;
    node->split_axis = (char)best_axis;
    node->split_position = sc[best_axis][best_split].pos;
    node->left = left;
    node->right = right;
    
    Point3 tmp = (area.bounds[1]);
    *(&(tmp.x)+best_axis) = node->split_position;
    AABB area_left(&(area.bounds[0]),&tmp);
    AABB area_right(&tmp,&(area.bounds[1]));
    
    build(left, depth+1, sc, as_below, as_below_index, area_left);
    free(as_below);
    build(right, depth+1, sc, as_above, as_above_index, area_right);
    free(as_above);
}

bool KdTree::intersect(const Ray* r, Asset* h)const
{
    RayProperties rp;
    rp.inverseX = 1.0f/r->direction.x;
    rp.inverseY = 1.0f/r->direction.y;
    rp.inverseZ = 1.0f/r->direction.z;
    rp.isXInvNeg = rp.inverseX < 0?true:false;
    rp.isYInvNeg = rp.inverseY < 0?true:false;
    rp.isZInvNeg = rp.inverseZ < 0?true:false;
    float mint, maxt;
    if(!scene_aabb.intersect(r, &rp, &mint, &maxt))
        return false;
    
    KdTravNode jobs[KD_MAX_DEPTH];
    int jobs_stack_top = 0;
    bool found = false;
    
    const KdTreeNode* n = nodesList;
    while(nodesList != NULL)
    {
        if(r->maxext < mint)
            break;
        if(!n->isLeaf())
        {
            char axis = n->getAxis();
            float planet = n->getSplit()-r->origin[axis]**(&(rp.inverseX)+axis);
            const KdTreeNode* left;
            const KdTreeNode* right;
            int leftBelow = (r->origin[axis] < n->getSplit() ||
                             (r->origin[axis] == n->getSplit() &&
                              r->direction[axis] <= 0));
            if(leftBelow)
            {
                left = n+1;
                right = &nodesList[n->getOtherChildOffset()];
            }
            else
            {
                left = &nodesList[n->getOtherChildOffset()];
                right = n+1;
            }
            
            if (planet > maxt || planet <= 0)
                n = left;
            else if (planet < mint)
                n = right;
            else
            {
                jobs[jobs_stack_top].node = right;
                jobs[jobs_stack_top].mint = planet;
                jobs[jobs_stack_top++].maxt = maxt;
                n = left;
                maxt = planet;
            }
        }
        else
        {
            //assets number
            unsigned int a_n = n->getAssetsNumber();
            Asset* current_asset;
            float res1, res2;
            for(unsigned int i=0;i<a_n;i++)
            {
                current_asset = assetsList[n->getAssetOffset()+i];
                if(current_asset->intersectFast(r, &rp, &res1, &res2))
                   if(current_asset->intersect(r,&res1,&res2))
                   {
                       found = true;
                       h = current_asset;
                   }
            }
            
            if(jobs_stack_top>0)
            {
                n = jobs[--jobs_stack_top].node;
                mint = jobs[jobs_stack_top].mint;
                maxt = jobs[jobs_stack_top].maxt;
            }
            else
                break;
        }
    }
    return found;
}
