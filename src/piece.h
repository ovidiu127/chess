#ifndef __PIECE
#define __PIECE

#include "utils.h"
#include "types.h"
#include "move.h"

int getPieceValue(unsigned piece);

bool getPieceColor(unsigned piece);

bool isValid(mov *m);

moves* getMoves(piece *p);

#endif