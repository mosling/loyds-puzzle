#pragma once

#include <stdbool.h>
#include "localTypes.h"

void showConfiguration(CHAR configuration[16]);

bool isSolved(CHAR configuration[16]);
bool isEqual(CONFIGURATION(c1), CONFIGURATION(c2) );
void setConfiguration(CHAR target[16], CHAR source[16]);

bool checkConfiguration(CHAR configuration[16]);
CHAR findStartPosition(CHAR configuration[16]);
CHAR getPossibleTurns(CHAR position);

CHAR  doTurn(CHAR turn, CHAR position, CPARAMETER, CONFIGURATION(nextConfiguration));
