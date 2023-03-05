#include "gen.h"

extern int board[9][9];

extern piece pieces[32];

void genMove(bool color){
    static moves *mvs[16];
    if(color==BLACK){
        int r=rand()%16;
        while(pieces[r].type!=bKNIGHT&&pieces[r].type!=bPAWN&&pieces[r].type!=bBISHOP){
            r=rand()%16;
        }
        mvs[r]=getMoves(pieces+r);
        int p=rand()%mvs[r]->dim;
        applyMove(mvs[r]->m+p);
        // free(m[r%16]);
    }
}