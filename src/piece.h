#ifndef __PIECE
#define __PIECE

#include "utils.h"
#include "types.h"
#include "move.h"

int getPieceValue(unsigned piece);

bool getPieceColor(unsigned piece);

bool isValid(position *game,mov *m);

moves* getMoves(position *game,piece *p);

#endif