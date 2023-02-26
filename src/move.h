#ifndef __MOVE
#define __MOVE

#include "utils.h"
#include "piece.h"

bool canPromote(int *c);

void promote(int x2,int y2);

bool canCastle(int *c);

void castle(int x2, int y2);

int takePiece(int x2,int y2);

int checkPath(int *c);

int isLegal(int *c);

void makeMove(int *c);

int move(int *c);

#endif