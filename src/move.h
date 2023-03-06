#ifndef __MOVE
#define __MOVE

#include "utils.h"
#include "types.h"
#include "piece.h"

bool canPromote(int *c);

void promote(position *game,int x2,int y2);

bool canCastle(position *game,int *c);

void castle(position *game,int x2, int y2);

bool takePiece(position *game,int x2,int y2);

bool checkPath(position *game,int *c);

bool isLegal(position *game,int *c);

void makeMove(position *game,int *c);

bool move(position *game,int *c);

void applyMove(position *game,mov *m);

#endif