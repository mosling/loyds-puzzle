#include "loydTree.h"
#include "configuration.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

treeNode *addNewNode(treeNode *withParent)
{
    treeNode *tn = (treeNode *)malloc(sizeof(treeNode));
    tn->parent = withParent;
    tn->lastTurn = 0;
    for (int i=0; i < 4; ++i)
    {
        tn->child[i] = NULL;
    }
    if (NULL != withParent)
    {
        tn->level = withParent->level + 1;
    }
    else
    {
        tn->level = 0;
    }

    return tn;
}

treeNode *createChildNodes(treeNode *node)
{
    CHAR turns = getPossibleTurns(node->position);
    CHAR turnMask = 1;
    CONFIGURATION(queryConfiguration);

    for (int i = 0; i < 4; ++i)
    {
        if (turns & turnMask)
        {
            CHAR newPosition = doTurn(turnMask, node->position, node->configuration, queryConfiguration);
            if (!isPathCyclic(node, queryConfiguration))
            {
                treeNode *newNode = addNewNode(node);
                setConfiguration(newNode->configuration, queryConfiguration);
                newNode->lastTurn = turnMask;
                newNode->position = newPosition;
                node->child[i] = newNode;
            
                if (isSolved(queryConfiguration))
                {
                    return newNode;
                }
            }
        }
        turnMask <<= 1;
    }

    return NULL;
}

void searchSolution(treeNode *startNode, UINT maxLevel)
{
    treeNode *solution = NULL;

    for (UINT level=0; level < maxLevel; ++level)
    {
        printf ("create next level for %u\n", level);
        fflush(stdout);

        solution = createNextLevelFor(startNode, level);
        printf("\n");

        if (NULL != solution)
        {
            printf("find solution at level %u\n", level + 1);
            showSolutionPath(solution);
            break;
        }
    }

    if (NULL == solution)
    {
        printf ("no solution found in the area of %u turns\n", maxLevel);
    }
}

treeNode *createNextLevelFor(treeNode *node, UINT level)
{
    treeNode *solution = NULL;
     
    if (node->level == level)
    {
        solution = createChildNodes(node);
        if (NULL != solution)
        {
            return solution;
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        if (node->child[i] != NULL && node->level < level)
        {
           solution = createNextLevelFor(node->child[i], level);
           if (NULL != solution)
           { 
               break;
           }
        }
    }

    return solution;
}

// check all nodes above the given node if the configuration equal 
// to the given configuration
bool isPathCyclic(treeNode *node, CPARAMETER)
{
    if (isEqual(node->configuration, configuration))
    {
        return true;
    }
    else if (node->parent != NULL)
    {
        return isPathCyclic(node->parent, configuration);
    }

    return false;
}

char *showTurn(UINT turn)
{
    switch (turn)
    {
        case 0: return "hold"; 
        case 1: return "left";
        case 2: return "down";
        case 4: return "right";
        case 8: return "up";
        default: return "wrong";
    }
}

void showSolutionPath(treeNode *node)
{
    if (NULL == node)
    {
        return;
    }

    showConfiguration(node->configuration);
    printf("turn(%s)\n", showTurn(node->lastTurn));
    showSolutionPath(node->parent);
}
