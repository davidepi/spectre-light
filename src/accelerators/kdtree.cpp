//author: Davide Pizzolotto
//license: GNU GPLv3

#include "kdtree.hpp"

#define KDNODE_ALLOC 1 //AT LEAST 1!!! otherwise when doubling the array size
//0 * 2 = guess what :^)

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
    KdTreeNode::asset_offset = primitive_offset;
    KdTreeNode::data = p_number;
    KdTreeNode::data |= 0x80000000;
}

bool KdTreeNode::isLeaf() const
{
    return KdTreeNode::data & 0x80000000;
}

char KdTreeNode::getAxis() const
{
    return (KdTreeNode::data & 0x60000000) >> 29;
}

float KdTreeNode::getSplit() const
{
    return split;
}

unsigned int KdTreeNode::getOtherChildOffset() const
{
    return KdTreeNode::data & 0x1FFFFFFF;
}

unsigned int KdTreeNode::getAssetOffset() const
{
    return KdTreeNode::asset_offset;
}

unsigned int KdTreeNode::getAssetsNumber() const
{
    return KdTreeNode::data & 0x7FFFFFFF;
}

// <><><><><><><>    KdTree Helpers

/**
 * \cond
 *  No documentation for these helper classes
 */

///Contains some private classes used as helper in the kd-tree construction
namespace KdHelpers
{
    //Like the KdTreeNode, but with extra variables.
    //This is used to build the tree in a 'canonical' way. Then, when ready,
    //everything is flattened into the KdTreeNode array
    struct KdTreeBuildNode
    {
        //where the assets are stored
        unsigned int offset_start;
        bool isLeaf;
        char split_axis;
        union
        {
            float split_position;
            unsigned int assets_number;
        };

        //children
        KdTreeBuildNode* left;
        KdTreeBuildNode* right;
    };

    //record a possible candidate for the split
    //only on the sides of the aabbs
    struct SplitCandidate
    {
        float pos; //the position of the split plane
        bool isLeftSide; //if the split plane is on the left of the aabb
        Asset* whoami;  //the asset proprietary of the aabb
    };

    //used to sort the splicandidate in the kdtree build
    bool compare_sc(const SplitCandidate s1, const SplitCandidate s2)
    {
        return s1.pos<s2.pos;
    }

    //helper structure for kd tree traversal
    struct KdTravNode
    {
        const KdTreeNode* node;
        float mint;
        float maxt;
    };
}

/**
 *  \endcond
 */

// <><><><><><><>    KdTree

KdTree::KdTree()
{
    KdTree::assetsList = (const Asset**)malloc(sizeof(Asset*)*KDNODE_ALLOC);
    KdTree::assets_number = 0;
    KdTree::assets_allocated = KDNODE_ALLOC;

    KdTree::nodesList = (KdTreeNode*)malloc(sizeof(KdTreeNode)*KDNODE_ALLOC);
    KdTree::nodes_index = 0;
    KdTree::nodes_allocated = KDNODE_ALLOC;

    if(KdTree::assetsList == NULL || KdTree::nodesList == NULL)
        Console.critical(MESSAGE_NOMEMORY("KdTree init"));
}

KdTree::~KdTree()
{
    free(assetsList);
    free(nodesList);
}

void KdTree::addAsset(const Asset* addme)
{
    if(assets_number == _MAX_ASSETS_)
        Console.severe(MESSAGE_MAXASSETNUMBER);
    if(assets_number == assets_allocated)
    {
        int allocNo = min(assets_allocated << 1, _MAX_ASSETS_);
        const Asset** tmp = (const Asset**)malloc(sizeof(Asset*)*(allocNo));
        if(tmp)
        {
            memcpy(tmp, assetsList, assets_allocated*sizeof(Asset*));
            assets_allocated = allocNo;
            free(KdTree::assetsList);
            KdTree::assetsList = tmp;
        }
        else
            Console.critical(MESSAGE_NOMEMORY("KdTree building"));
    }
    assetsList[assets_number++] = addme;
}

void KdTree::finalize(void* n)
{
    using KdHelpers::KdTreeBuildNode;
    KdTreeBuildNode* node = (KdTreeBuildNode*)n;
    if(nodes_index == nodes_allocated)
    {
        unsigned int allocNo = nodes_allocated << 1;
        KdTreeNode* tmp = (KdTreeNode*)malloc(sizeof(KdTreeNode)*(allocNo));
        if(tmp)
        {
            memcpy(tmp, nodesList, nodes_allocated*sizeof(KdTreeNode));
            nodes_allocated = allocNo;
            free(KdTree::nodesList);
            KdTree::nodesList = tmp;
        }
        else
            Console.critical(MESSAGE_NOMEMORY("KdTree flattening"));
    }
    if(node->isLeaf)
    {
        nodesList[nodes_index++] = KdTreeNode(node->offset_start,
                                              node->assets_number);
    }
    else
    {
        //record my position for later use and update it, so I can call the
        //recursive step
        unsigned int myindex = nodes_index++;

        //left node is right after the parent, right node is somewhere else
        finalize(node->left);

        //I processed all the left nodes, so now I know the right node position
        nodesList[myindex] = KdTreeNode(node->split_position, node->split_axis,
                                        nodes_index);
        finalize(node->right);
    }
    free(node);
}

void KdTree::buildTree()
{
    using KdHelpers::KdTreeBuildNode;
    using KdHelpers::SplitCandidate;

    if(assets_number == 0)
        return;
    KdTreeBuildNode* node = (KdTreeBuildNode*)malloc(sizeof(KdTreeBuildNode));

    //get the aabb for the whole scene
    scene_aabb = AABB(*(assetsList[0]->get_AABB)());
    for(int i = 1; i<assets_number; i++)
        scene_aabb.engulf(assetsList[i]->get_AABB());

    //copy the assets, since the original array will be rewritten in a
    //different order
    Asset** alcopy = (Asset**)malloc(sizeof(Asset*)*KdTree::assets_number);
    memcpy(alcopy, KdTree::assetsList, sizeof(Asset*)*KdTree::assets_number);
    unsigned int a_n = KdTree::assets_number; //assets_number will be set to 0
    KdTree::assets_number = 0;//and assets will be reinserted in order during
    //building of the kd-tree

    //allocate the array of possible candidates. sc[axis][candidate]
    SplitCandidate** sc = (SplitCandidate**)malloc(sizeof(SplitCandidate*)*3);
    sc[0] = (SplitCandidate*)malloc(sizeof(SplitCandidate)*2*a_n);
    sc[1] = (SplitCandidate*)malloc(sizeof(SplitCandidate)*2*a_n);
    sc[2] = (SplitCandidate*)malloc(sizeof(SplitCandidate)*2*a_n);

    build(node, 0, sc, alcopy, a_n, scene_aabb);

    free(alcopy);
    free(sc[0]);
    free(sc[1]);
    free(sc[2]);
    free(sc);
    finalize(node); //copy tempbuilder into nodesList and assets into assetsList

    //free unused memory for KdTreeNode array
    KdTreeNode* tmpnodes = (KdTreeNode*)malloc(sizeof(KdTreeNode)*nodes_index);
    memcpy(tmpnodes, nodesList, sizeof(KdTreeNode)*nodes_index);
    nodes_allocated = nodes_index;
    free(nodesList);
    nodesList = tmpnodes;
}

void KdTree::build(void* n, char depth, void* s_c, Asset** a_l,
                   unsigned int a_n, AABB area)
{
    using KdHelpers::KdTreeBuildNode;
    using KdHelpers::SplitCandidate;

    KdTreeBuildNode* node = (KdTreeBuildNode*)n;

    //terminate recursion if max depth or too few assets
    if(depth == KD_MAX_DEPTH || a_n<=_LEAF_ASSETS_)
    {
        node->offset_start = KdTree::assets_number;
        node->assets_number = a_n;

        //assets are added in order to the Class assets array
        //now i can reference them with a pointer to the first and the number
        //of assets for the leaf
        for(unsigned int i = 0; i<a_n; i++)
            KdTree::addAsset(a_l[i]);
        node->isLeaf = true;
        node->left = NULL;
        node->right = NULL;
        return;
    }

    //set variables
    SplitCandidate** sc = (SplitCandidate**)s_c;
    unsigned char best_axis = 0xFF;
    int best_split = -1; //the offset in the sc structure for the best split
    float best_cost = INFINITY;
    float old_cost = SAH_INTERSECT*(float)a_n;
    float total_area = area.surface();
    Vec3 aabb_diagonal = area.bounds[1]-area.bounds[0];
    float inv_area = 1.f/total_area;

    //usually this is the best split candidate, being the longest axis
    unsigned char axis = area.longest_axis();
    int isSearching = 3; //number of axis attemped. In the worst case
    //bail out of the while at 0

    //repeat for every axis, to find best splitting pane
    while(isSearching)
    {
        //for each asset add left and right side of the aabbs as split panes
        for(unsigned int i = 0; i<a_n; i++)
        {
            sc[axis][i << 1].pos = a_l[i]->get_AABB()->bounds[0][axis];
            sc[axis][i << 1].whoami = a_l[i];
            sc[axis][i << 1].isLeftSide = true;
            sc[axis][(i << 1)+1].pos = a_l[i]->get_AABB()->bounds[1][axis];
            sc[axis][(i << 1)+1].whoami = a_l[i];
            sc[axis][(i << 1)+1].isLeftSide = false;
        }

        //sort them asc
        std::sort(&(sc[axis][0]), &(sc[axis][2*a_n]), KdHelpers::compare_sc);

        //count of the assets on both sides of every candidate split
        unsigned int left_a = 0, right_a = a_n;
        for(unsigned int i = 0; i<2*a_n; i++)
        {
            bool isAABBRightSide = !(sc[axis][i].isLeftSide);
            if(isAABBRightSide) //update assets count
                right_a--;
            if(sc[axis][i].pos>area.bounds[0][axis] &&
               sc[axis][i].pos<area.bounds[1][axis]) //if inside aabb
            {
                char otheraxis1 = (axis+1)%3;
                char otheraxis2 = (axis+2)%3;

                float area_candidate_left =
                        2*(aabb_diagonal[otheraxis1]*aabb_diagonal[otheraxis2]
                           +(sc[axis][i].pos-area.bounds[0][axis])*
                            (aabb_diagonal[otheraxis1]+
                             aabb_diagonal[otheraxis2]));

                float area_candidate_right =
                        2*(aabb_diagonal[otheraxis1]*aabb_diagonal[otheraxis2]
                           +(area.bounds[1][axis]-sc[axis][i].pos)*
                            (aabb_diagonal[otheraxis1]+
                             aabb_diagonal[otheraxis2]));

                float al = area_candidate_left*inv_area;
                float ar = area_candidate_right*inv_area;
                //bonus is used to prefer nodes with 0 assets -> discard rays
                float bonus = (left_a == 0 || right_a == 0)?1.0f:0.0f;
                float cost = SAH_DESCEND+ //search Surface Area Heuristic
                             SAH_INTERSECT*(1.0f-bonus)*(al*left_a+ar*right_a);
                if(cost<best_cost)
                {
                    best_cost = cost;
                    best_axis = axis;
                    best_split = i;
                }
            }
            if(!isAABBRightSide) //update assets count
                left_a++;
        }
        if(best_axis == 0xFF) //nothing useful found
        {
            isSearching--;  //try with another axis
            axis = (axis+1)%3;
        }
        else
            break;
    }

    //best cost sucks, better not to split at all -> make a leaf
    if((best_cost>4.f*old_cost && a_n<16) || best_axis == 0xFF)
    {
        node->offset_start = KdTree::assets_number;
        node->assets_number = a_n;
        for(unsigned int i = 0; i<a_n; i++)
            KdTree::addAsset(a_l[i]);
        node->isLeaf = true;
        node->left = NULL;
        node->right = NULL;
        return;
    }

    //child nodes
    KdTreeBuildNode* left = (KdTreeBuildNode*)malloc(sizeof(KdTreeBuildNode));
    KdTreeBuildNode* right = (KdTreeBuildNode*)malloc(sizeof(KdTreeBuildNode));

    //subset containing the now splitted assets
    Asset** as_left = (Asset**)malloc(sizeof(Asset*)*a_n);
    Asset** as_right = (Asset**)malloc(sizeof(Asset*)*a_n*(KD_MAX_DEPTH+1));

    //assign the assets to the right array, depending if left/right of plane
    unsigned int as_left_index = 0;
    unsigned int as_right_index = 0;
    for(int i = 0; i<best_split; i++)
        if(sc[best_axis][i].isLeftSide)
            as_left[as_left_index++] = sc[best_axis][i].whoami;
    for(unsigned int i = best_split+1; i<2*a_n; i++)
        if(!(sc[best_axis][i].isLeftSide))
            as_right[as_right_index++] = sc[best_axis][i].whoami;

    //setup internal node and child
    node->isLeaf = false;
    node->split_axis = (char)best_axis;
    node->split_position = sc[best_axis][best_split].pos;
    node->left = left;
    node->right = right;

    //update newly split area
    AABB area_left(area);
    AABB area_right(area);
    *(&(area_left.bounds[1].x)+axis) = sc[best_axis][best_split].pos;
    *(&(area_right.bounds[0].x)+axis) = sc[best_axis][best_split].pos;

    //recursive step
    build(left, depth+1, sc, as_left, as_left_index, area_left);
    free(as_left);
    build(right, depth+1, sc, as_right, as_right_index, area_right);
    free(as_right);
}

bool KdTree::intersect(const Ray* r, HitPoint* h) const
{
    using KdHelpers::KdTravNode;

    //setup all the divisions since they won't change for this ray
    RayProperties rp(*r);
    float mint, maxt;

    //if the scene is not insersected end here
    if(!scene_aabb.intersect(r, &rp, &mint, &maxt))
        return false;
    //stack of nodes to process, used to traverse the tree breadth-first
    KdTravNode jobs[KD_MAX_DEPTH];
    int jobs_stack_top = 0;
    bool found = false;
    float bestdistance = FLT_MAX;

    const KdTreeNode* n = nodesList;
    while(n != NULL)
    {
        if(bestdistance<mint) //a closer intersection has been found
            break;

        if(!n->isLeaf()) //if internal node
        {
            char axis = n->getAxis();
            //get plane distance
            float planet = (n->getSplit()-r->origin[axis]);
            planet *= *(&(rp.inverseX)+axis);
            const KdTreeNode* left;
            const KdTreeNode* right;

            //find the order in which the ray encounters the children
            bool leftBelow = (r->origin[axis]<n->getSplit()) ||
                             (r->origin[axis] == n->getSplit() &&
                              r->direction[axis]<=0);
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

            //special cases, only 1 node needs to be processed
            if(planet>maxt || planet<=0)
                n = left;
            else if(planet<mint)
                n = right;
            else //put the right node in the todo list, process the left one
            {
                jobs[jobs_stack_top].node = right;
                jobs[jobs_stack_top].mint = planet;
                jobs[jobs_stack_top++].maxt = maxt;
                n = left;
                maxt = planet;
            }
        }
        else //if leaf
        {
            //assets number
            unsigned int a_n = n->getAssetsNumber();
            const Asset* current_asset;
            float res1, res2;

            //try to intersect every asset
            for(unsigned int i = 0; i<a_n; i++)
            {
                current_asset = assetsList[n->getAssetOffset()+i];

                //firstly try with the aabb since it's faster
                if(current_asset->intersect_AABB(r, &rp, &res1, &res2))
                {
                    //then try with the actual asset
                    if(res1<bestdistance && //don't try if AABB > best distance
                       current_asset->intersect(r, &bestdistance, h))
                    {
                        found = true; //record current intersection
                        h->asset_h = current_asset;
                    }
                }
            }

            //try another node in the todo queue, maybe a closer intersection
            //can be found
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
