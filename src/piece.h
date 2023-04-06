#ifndef __PIECE
#define __PIECE

#include "utils.h"
#include "types.h"
#include "move.h"

int getPieceValue(unsigned piece);

bool getPieceColor(unsigned piece);

moves* getMoves(position *game,int px,int py);

bool validPiece(unsigned piece);

void updateCoverage(position *game);

#endif