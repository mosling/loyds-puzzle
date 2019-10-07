#include "configuration.h"

#include <stdio.h>
#include <string.h>

CHAR turnMatrix[16] = {3, 7, 7, 6, 0xb, 0xf, 0xf, 0xe, 0xb, 0xf, 0xf, 0xe, 9, 0xd, 0xd, 0xc};

bool isSolved(CPARAMETER)
{
    return 0 == strncmp(configuration, SOLUTION, FIELD);
}

bool isEqual(CONFIGURATION(c1), CONFIGURATION(c2))
{
    return 0 == strncmp(c1, c2, FIELD);
}

bool checkConfiguration(CPARAMETER)
{

    CHAR characters[FIELD];
    for (int i = 0; i < FIELD; ++i)
    {
        characters[i] = 0;
    }

    for (int i = 0; i < FIELD; ++i)
    {
        CHAR c = configuration[i];
        if (c < '0' || c > 'f' || (c > '9' && c < 'a'))
        {
            printf("character '%c' isn't in 1,...,9 and a,...,f -- please correct\n", c);
            return false;
        }
        if (c <= '9')
        {
            characters[c - '0']++;
        }
        else
        {
            characters[10 + c - 'a']++;
        }
    }

    bool returnValue = true;

    for (int n = 0; n < 10; ++n)
    {
        CHAR cStr = n < 10 ? '0' + n : 'a' + (n - 10);
        if (characters[n] == 0)
        {
            returnValue = false;
            printf("missing character '%c'\n", cStr);
        }

        if (characters[n] > 1)
        {
            returnValue = false;
            printf("duplicate character '%c' (%d times)\n", cStr, characters[n]);
        }
    }

    return returnValue;
}

CHAR findStartPosition(CPARAMETER)
{
    for (int i = 0; i < 16; ++i)
    {
        if (configuration[i] == '0')
        {
            return i;
        }
    }

    printf("Exception -- no postion contains the '0' character.\n");

    return -1;
}

CHAR getPossibleTurns(CHAR position)
{
    return turnMatrix[position];
}

void setConfiguration(CHAR target[16], CHAR source[16])
{
    strncpy(target, source, 16);
}

CHAR doTurn(CHAR turn, CHAR position, CPARAMETER, CONFIGURATION(nextConfiguration))
{
    setConfiguration(nextConfiguration, configuration);
    CHAR newPosition;

    switch (turn)
    {
    case 0:
        newPosition = position;
        break;
    case 1:
        newPosition = position + 1;
        break;
    case 2:
        newPosition = position + 4;
        break;
    case 4:
        newPosition = position - 1;
        break;
    case 8:
        newPosition = position - 4;
        break;
    default:
        printf("fatal error: no possible turn %d\n", turn);
        newPosition = position;
    }

    if (newPosition != position)
    {
        nextConfiguration[position] = configuration[newPosition];
        nextConfiguration[newPosition] = configuration[position];
    }

    return newPosition;
}

void showConfiguration(CONFIGURATION(c))
{
    printf("+---+---+---+---\n");
    printf("| %c | %c | %c | %c |\n", c[0], c[1], c[2], c[3]);
    printf("+---+---+---+---\n");
    printf("| %c | %c | %c | %c |\n", c[4], c[5], c[6], c[7]);
    printf("+---+---+---+---\n");
    printf("| %c | %c | %c | %c |\n", c[8], c[9], c[10], c[11]);
    printf("+---+---+---+---\n");
    printf("| %c | %c | %c | %c |\n", c[12], c[13], c[14], c[15]);
    printf("+---+---+---+---\n\n");
    fflush(stdout);
}
