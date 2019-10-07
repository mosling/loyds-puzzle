#pragma once

#include <stdbool.h>
#include "localTypes.h"

typedef struct treeNode
{
    struct treeNode *parent;
    struct treeNode *child[4];
    CHAR configuration[16];
    CHAR position;
    CHAR lastTurn;
    UINT level;
} treeNode;

treeNode *addNewNode(treeNode *withParent);

treeNode *createChildNodes(treeNode *node);
treeNode *createNextLevelFor(treeNode *node, UINT level);
void searchSolution(treeNode *startNode, UINT maxLevel);

void showSolutionPath(treeNode *node);
bool isPathCyclic(treeNode *node, CPARAMETER);
