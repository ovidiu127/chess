#ifndef __BOARD
#define __BOARD

#include "utils.h"
#include "piece.h"
#include "types.h"

int evalPosition(position *game);

void initBoard(position *game);

void printBoard(position *game);

#endif