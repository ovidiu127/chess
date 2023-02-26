#include "gen.h"

extern int board[9][9];

pieceMoves moves[6];

const int knightX[]={-2,-2,-1,-1,1,1,2,2};
const int knightY[]={-1,1,-2,2,-2,2,-1,1};

void initMoves(){
    moves[0].x=(int*)knightX;
    moves[0].y=(int*)knightY;
    moves[0].n=8;
}

void genMove(bool color){

}