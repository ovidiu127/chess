#ifndef __MOVE
#define __MOVE

#include "utils.h"
#include "types.h"
#include "piece.h"

bool canPromote(int *c);

void promote(int x2,int y2);

bool canCastle(int *c);

void castle(int x2, int y2);

bool takePiece(int x2,int y2);

bool checkPath(int *c);

bool isLegal(int *c);

void makeMove(int *c);

bool move(int *c);

void applyMove(mov *m);

#endif