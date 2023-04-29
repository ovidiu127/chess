#ifndef __GEN
#define __GEN

#include "utils.h"
#include "piece.h"
#include "move.h"
#include "board.h"

#include <limits.h>

int findMove(position *game,int depth,int maxDepth);

void genMove(position *game,int difficulty);

#endif