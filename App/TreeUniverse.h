//
// Created by PAYS on 16/10/2016.
//

#ifndef GAMEOFLIFE_TREEUNIVERSE_H
#define GAMEOFLIFE_TREEUNIVERSE_H


#include "TreeNode.h"

class TreeUniverse {
public:
    TreeUniverse();

    virtual ~TreeUniverse();

    void runStep();
    void setByte(const int x,const int y, const bool live=true);
    int getByte(const int x,const int y, const int levelMax=-1) const;
    int getLevel() const ;

    TreeNode *getRoot() const;

private:
    TreeNode* root;
};


#endif //GAMEOFLIFE_TREEUNIVERSE_H
