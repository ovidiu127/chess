#ifndef __BOARD
#define __BOARD

#include "utils.h"
#include "piece.h"
#include "types.h"

void initMatch(match *g);

void addToPast(match *g);

void getFromPast(match *g);

int evalPosition(position *game);

void initBoard(position *game);

void printBoard(position *game);

#endif