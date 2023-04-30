#ifndef __PIECE
#define __PIECE

#include "utils.h"
#include "types.h"
#include "move.h"

int getPieceValue(unsigned piece);

bool getPieceColor(unsigned piece);

moves* getMoves(position *game,int px,int py);

bool validPiece(unsigned piece);

uint64_t getCoverage(position *game,bool color);

bool endGame(position *game);

#endif