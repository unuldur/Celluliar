//
// Created by PAYS on 13/10/2016.
//

#ifndef GAMEOFLIFE_TREENODE_H
#define GAMEOFLIFE_TREENODE_H

#include <string.h>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class TreeNode{
public:

    TreeNode(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se);

    TreeNode(bool living);

    static TreeNode* create();

    static TreeNode* create(bool living);

    static TreeNode* create(TreeNode* nw, TreeNode* ne, TreeNode* sw, TreeNode* se);

    TreeNode* nextGeneration();

    virtual ~TreeNode();

    int getByte(const int x,const int y, const int levelMax) const;

    TreeNode * setByte(const int x,const int y, const bool live=true) const;

    TreeNode *expandUniverse() const;

    TreeNode *emptyTree(const int lev) const;

    int getLevel() const;

    TreeNode *getNw() const;

    TreeNode *getNe() const;

    TreeNode *getSw() const;

    TreeNode *getSe() const;

    double getPopulation() const;

    string getThis() const;

    static std::unordered_map<size_t, TreeNode*> hashMap;

    std::size_t operator()(TreeNode const& treeNode) const noexcept;

    std::size_t hash() noexcept;

    bool operator==(const TreeNode &treeNode) const;

    static void initHash();

private:
    TreeNode* nw;
    TreeNode* ne;
    TreeNode* sw;
    TreeNode* se;
    bool living;
    double population;
    int level;
    size_t hash_value;
    TreeNode* next;

    TreeNode* oneGen(int bitmask) const;

    TreeNode* slowSimulation() const;

    TreeNode *centeredSubnode()const;

    TreeNode *centeredVertical(TreeNode *n, TreeNode *s) const;

    TreeNode *centeredHorizontal(TreeNode *pNode, TreeNode *pTreeNode)const;

    TreeNode *centeredSubSubnode()const;

    vector<string> getLignesTreeNode() const;

    TreeNode* init();




};


#endif //GAMEOFLIFE_TREENODE_H
