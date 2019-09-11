//
// Created by PAYS on 13/10/2016.
//

#include <sstream>

#include <list>
#include "TreeNode.h"


//Init hashMap
std::unordered_map<size_t, TreeNode*> TreeNode::hashMap = {};

TreeNode::TreeNode(bool living) : living(living),nw(nullptr),ne(nullptr),sw(nullptr),se(nullptr), next(nullptr), hash_value(0) {
    level = 0;
    population = living ? 1 : 0;
}

TreeNode::TreeNode(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se) :  sw(sw), ne(ne), nw(nw), se(se), next(nullptr), hash_value(0){
    population = nw->population + ne->population + sw->population + se->population;
    living = population != 0;
    level = nw->level + 1;
}

TreeNode::~TreeNode() {
    /*
     * TODO delete just when there are no reference on here
    delete nw;
    delete ne;
    delete sw;
    delete se;
    */
}

TreeNode* TreeNode::oneGen(int bitmask) const{
    if(bitmask == 0)
    {
        return create(false);
    }
    int self = (bitmask >> 5) & 1;
    bitmask &= 0x757;
    int nbNeighbours = 0;
    while (bitmask != 0)
    {
        nbNeighbours++;
        bitmask &= (bitmask - 1);
    }
    return create(nbNeighbours == 3 || (nbNeighbours == 2 && self != 0));
}

TreeNode* TreeNode::slowSimulation() const{
    int allbits = 0 ;
    for (int y=-2; y<2; y++)
        for (int x=-2; x<2; x++)
            allbits = (allbits << 1) + getByte(x, y, level) ;
    return create(oneGen(allbits>>5), oneGen(allbits>>4),
                  oneGen(allbits>>1), oneGen(allbits)) ;
}

TreeNode* TreeNode::centeredSubnode() const{
    return create(nw->se, ne->sw, sw->ne, se->nw) ;
}

TreeNode* TreeNode::centeredVertical(TreeNode* n,TreeNode* s) const
{
    return create(n->sw->se, n->se->sw, s->nw->ne, s->ne->nw) ;
}

TreeNode *TreeNode::centeredHorizontal(TreeNode *w, TreeNode *e) const{
    return create(w->ne->se, e->nw->sw, w->se->ne, e->sw->nw) ;
}

TreeNode *TreeNode::centeredSubSubnode() const{
    return create(nw->se->se, ne->sw->sw, sw->ne->ne, se->nw->nw) ;

}

TreeNode* TreeNode::nextGeneration(){
    if(next != nullptr)
        return next;
    if(population == 0)
    {
        return nw;
    }
    if(level == 2)
    {
        return slowSimulation();
    }
    TreeNode* n00 = nw->centeredSubnode();
    TreeNode* n01 = centeredHorizontal(nw, ne);
    TreeNode* n02 = ne->centeredSubnode();
    TreeNode* n10 = centeredVertical(nw, sw);
    TreeNode* n11 = centeredSubSubnode();
    TreeNode* n12 = centeredVertical(ne, se);
    TreeNode* n20 = sw->centeredSubnode();
    TreeNode* n21 = centeredHorizontal(sw, se);
    TreeNode* n22 = se->centeredSubnode() ;
    next = create((create(n00, n01, n10, n11))->nextGeneration(),
                        (create(n01, n02, n11, n12))->nextGeneration(),
                        (create(n10, n11, n20, n21))->nextGeneration(),
                        (create(n11, n12, n21, n22))->nextGeneration()) ;
    return next;
}


TreeNode *TreeNode::expandUniverse() const{
    TreeNode* border = emptyTree(level-1) ;
    return create(create(border, border, border, nw),
                            create(border, border, ne, border),
                            create(border, sw, border, border),
                            create(se, border, border, border)) ;
}

TreeNode *TreeNode::emptyTree(const int lev) const{
    if (lev == 0)
        return create(false) ;
    TreeNode* n = emptyTree(lev-1) ;
    return create(n, n, n, n) ;
}

int TreeNode::getByte(const int x, const int y, const int levelMax) const{
    if(level == 0 or levelMax == 0)
    {
        return living ? 1 : 0;
    }
    int offset = 1 << (level -2);
    if (x < 0) {
        if (y < 0) {
            return nw->getByte(x + offset, y + offset, levelMax - 1);
        } else {
            return sw->getByte(x + offset, y - offset, levelMax - 1);
        }
    } else {
        if (y < 0) {
            return ne->getByte(x - offset, y + offset, levelMax - 1);
        } else {
            return se->getByte(x - offset, y - offset, levelMax - 1);
        }
    }
}

TreeNode *TreeNode::setByte(const int x,const int y, const bool live) const{
    if(level == 0)
    {
        return create(live);
    }
    int offset = 1 << (level -2);
    if (x < 0) {
        if (y < 0) {
            return create(nw->setByte(x + offset, y + offset, live),ne,sw,se);
        } else {
            return create(nw,ne,sw->setByte(x + offset, y - offset, live),se);
        }
    } else {
        if (y < 0) {
            return create(nw,ne->setByte(x - offset, y + offset, live),sw,se);
        } else {
            return create(nw,ne,sw,se->setByte(x - offset, y - offset, live));
        }
    }
}

int TreeNode::getLevel() const {
    return level;
}

TreeNode *TreeNode::getNw() const {
    return nw;
}

TreeNode *TreeNode::getNe() const {
    return ne;
}

TreeNode *TreeNode::getSw() const {
    return sw;
}

TreeNode *TreeNode::getSe() const {
    return se;
}

double TreeNode::getPopulation() const {
    return population;
}

TreeNode *TreeNode::init()
{
    size_t h = hash();
    TreeNode* tn = hashMap[h];
    if(tn == nullptr){
        hashMap[h] = this;
        return this;
    }
    return this;
}

TreeNode *TreeNode::create() {
    return (new TreeNode(false))->emptyTree(3);
}

TreeNode *TreeNode::create(bool living){
    return (new TreeNode(living))->init();
}

TreeNode *TreeNode::create(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se){
    return (new TreeNode(nw,ne,sw,se))->init();
}



vector<string> TreeNode::getLignesTreeNode() const
{
    vector<string> my;
    if(level == 0)
    {
        living?my.push_back("1"):my.push_back("0");
        return my;
    }
    vector<string> snw = nw->getLignesTreeNode();
    vector<string> sne = ne->getLignesTreeNode();
    vector<string> ssw = sw->getLignesTreeNode();
    vector<string> sse = se->getLignesTreeNode();

    int nb = snw.size();
    for (int i = 0; i < nb; ++i) {
        my.push_back(snw[i]+sne[i]);
    }
    for (int i = 0; i < nb; ++i) {
        my.push_back(ssw[i]+sse[i]);
    }
    return my;

}



string TreeNode::getThis() const {
    vector<string> myVec = getLignesTreeNode();
    string my ="";
    int taille = myVec.size();
    for (int i = 0; i < taille; ++i) {
        my += myVec[i]+"\n";
    }
    return my;
}

size_t TreeNode::operator()(const TreeNode &treeNode) const noexcept
{
    if (treeNode.level == 0)
        return treeNode.population;
    size_t h1 = operator()(treeNode.nw);
    size_t h2 = operator()(treeNode.ne);
    size_t h3 = operator()(treeNode.se);
    size_t h4 = operator()(treeNode.sw);
    return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
}

size_t TreeNode::hash() noexcept
{
    if(hash_value > 0)
        return hash_value;
    if (level == 0)
        return population;
    size_t h1 = nw->hash();
    size_t h2 = ne->hash();
    size_t h3 = sw->hash();
    size_t h4 = se->hash();
    hash_value = h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    return hash_value;
}

bool TreeNode::operator==(const TreeNode &treeNode) const
{
    if (level != treeNode.level)
        return false ;
    if (level == 0)
        return living == treeNode.living ;
    return nw == treeNode.nw && ne == treeNode.ne && sw == treeNode.sw && se == treeNode.se ;
}

void TreeNode::initHash()
{
    TreeNode::hashMap = {};
}



