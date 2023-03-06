#include "gen.h"

extern int board[9][9];

extern piece pieces[2][16];

void genMove(bool color){
    static moves *mvs[2][16];
    for(int i=0;i<16;++i){
        if(mvs[color][i]!=NULL){
            free(mvs[color][i]->m);
            free(mvs[color][i]);
        }
        if(pieces[color][i].s==INACTIVE){
            continue;
        }
        mvs[color][i]=getMoves(pieces[color]+i);
    }
    int r;
    do{
        r=rand()%16;
        while(mvs[color][r]==NULL){
            r=rand()%16;
        }
    }while(mvs[color][r]->dim==0);
    int p=rand()%mvs[color][r]->dim;
    applyMove(mvs[color][r]->m+p);
}