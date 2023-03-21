#include "gen.h"

int findMove(position *game,int depth,int maxDepth){
    if(depth>maxDepth){
        return evalPosition(game);
    }

    mov *bestMove=(mov*)malloc(sizeof(mov));
    moves *mvs;
    position *game1=(position*)malloc(sizeof(position));

    int ans=((game->toMove==BLACK)?1:-1)*INT_MAX;

    for(int i=1;i<=8;++i){
        for(int j=1;j<=8;++j){
            if(!validPiece(game->board[j][i]) || getPieceColor(game->board[j][i])!=game->toMove){
                continue;
            }
            mvs=getMoves(game,i,j);

            for(int d=0;d<mvs->dim;++d){
                *game1=*game;
                applyMove(game1,&mvs->m[d]);
                game1->toMove=!game1->toMove;
                int aux=findMove(game1,depth+1,maxDepth);
                if((game->toMove==WHITE && aux>ans) || (game->toMove==BLACK && aux<ans)){
                    ans=aux;
                    *bestMove=mvs->m[d];
                }
            }
            if(mvs!=NULL){
                if(mvs->dim!=0){
                    free(mvs->m);
                }
                free(mvs);
            }
        }
    }
    
    if(depth==0){
        applyMove(game,bestMove);
    }

    if(bestMove!=NULL){
        free(bestMove);
    }
    if(game1!=NULL){
        free(game1);
    }
    return ans;
}

void genMove(position *game,int difficulty){
    findMove(game,0,difficulty);
}