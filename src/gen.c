#include "gen.h"

void genMove(position *game){
    static moves *mvs[2][16];
    for(int i=0;i<16;++i){
        if(mvs[game->toMove][i]!=NULL){
            free(mvs[game->toMove][i]->m);
            free(mvs[game->toMove][i]);
        }
        if(game->pieces[game->toMove][i].s==INACTIVE){
            continue;
        }
        mvs[game->toMove][i]=getMoves(game,game->pieces[game->toMove]+i);
    }
    int r;
    do{
        r=rand()%16;
        while(mvs[game->toMove][r]==NULL){
            r=rand()%16;
        }
    }while(mvs[game->toMove][r]->dim==0);
    int p=rand()%mvs[game->toMove][r]->dim;
    applyMove(game,mvs[game->toMove][r]->m+p);
}