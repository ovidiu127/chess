#ifndef __MOVE
#define __MOVE

#include "utils.h"
#include "types.h"
#include "piece.h"

#define EN_PASSANT 'E'

bool canPromote(int *c);

void promote(position *game,int x2,int y2);

bool canCastle(position *game,int *c);

void castle(position *game,int x2, int y2);

bool canTakePiece(position *game,int *c);

void takePiece(position *game,int *c);

bool checkPath(position *game,int *c);

bool isLegal(position *game,int *c);

void makeMove(position *game,int *c);

bool move(position *game,int *c);

void applyMove(position *game,mov *m);

void clearMarks(position *game);

#endif