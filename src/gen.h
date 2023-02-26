#ifndef __GEN
#define __GEN

#include "utils.h"

typedef struct{
    int *x,*y;
    int n;
}pieceMoves;

void genMove(bool color);

#endif