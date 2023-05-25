#ifndef __MOVE
#define __MOVE

#include "utils.h"
#include "types.h"
#include "piece.h"
#include "menu.h"

#define EN_PASSANT 'E'

bool canPromote(mov *m);

void promote(position *game,int x2,int y2,int computerMove);

bool canCastle(position *game,mov *m);

void castle(position *game,int x2, int y2);

bool canTakePiece(position *game,mov *m);

void takePiece(position *game,mov *m);

bool checkPath(position *game,mov *m);

bool isLegal(position *game,mov *m);

void makeMove(position *game,mov *m);

bool move(position *game,mov *m,int legalCheck);

void clearMarks(position *game);

uint16_t getCapturedPiece(position *game,mov *m);

#endif