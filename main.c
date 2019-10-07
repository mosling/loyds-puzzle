#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include "configuration.h"
#include "loydTree.h"

int main(int argc, char **argv)
{
    if (argc < 2 || strlen(argv[1]) < 16)
    {
        printf("%s <start configuration> [maxLevel=20]\n");
        printf("   configuration is given by 16 characters\n");
        return 1;
    }

    UINT maxLevel = 20;
    if (argc > 2)
    {
        maxLevel = strtol(argv[2], NULL, 10);
        if (errno == ERANGE)
        {
            printf("range error, got for %s\n", argv[2]);
            errno = 0;
        }
    }

    CHAR startConfiguration[16];
    strncpy(startConfiguration, argv[1], 16);

    if (!checkConfiguration(startConfiguration))
    {
        return 2;
    }

    treeNode *treeRoot = addNewNode(NULL);
    treeRoot->position = findStartPosition(startConfiguration);
    setConfiguration(treeRoot->configuration, startConfiguration);

    searchSolution(treeRoot, maxLevel);
}