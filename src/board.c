#include "board.h"

void initMatch(match *g){
	g->current=malloc(sizeof(position));
	g->no=0;
	g->dim=64;
	g->past=malloc(g->dim * sizeof(position));
	if(g->past == NULL){
		perror("malloc()");
		exit(1);
	}
}

void addToPast(match *g){
	g->past[g->no]=*g->current;
	++g->no;
	if(g->no == g->dim){
		g->dim += 64;
		g->past=realloc(g->past, g->dim * sizeof(position));
		if(g->past == NULL){
			perror("realloc()");
			exit(1);
		}
	}
}

void getFromPast(match *g){
	if(g->no > 1){
		--g->no;
	}
	if(g->no >= 1){
		*g->current=g->past[g->no - 1];
	}
}

int evalPosition(position *game){
	int score=0;

	for(int i=1;i<=8;++i){
		for(int j=1;j<=8;++j){
			if(game->board[i][j]){
				score+=getPieceValue(game->board[i][j]);
			}
		}
	}

	return score;
}

void initBoard(position *game){
	// initial chess board definition
	game->board[8][1]=bROOK;
	game->board[8][2]=bKNIGHT;
	game->board[8][3]=bBISHOP;
	game->board[8][4]=bQUEEN;
	game->board[8][5]=bKING;
	game->board[8][6]=bBISHOP;
	game->board[8][7]=bKNIGHT;
	game->board[8][8]=bROOK;
	for(int i=1;i<=8;++i){
		game->board[7][i]=bPAWN;
	}

	game->board[1][1]=wROOK;
	game->board[1][2]=wKNIGHT;
	game->board[1][3]=wBISHOP;
	game->board[1][4]=wQUEEN;
	game->board[1][5]=wKING;
	game->board[1][6]=wBISHOP;
	game->board[1][7]=wKNIGHT;
	game->board[1][8]=wROOK;
	for(int i=1;i<=8;++i){
		game->board[2][i]=wPAWN;
	}
	game->toMove=WHITE;
	game->bk=game->wk=1;
}

void printBoard(position *game){
	clear();
	if(game->toMove==BLACK){
		//board coordinates
		printf("  ");
		for(int j=7;j>=0;--j){
			printf(" %c",'a'+j);
		}
		printf("\n\n");
		for(int i=1;i<=8;++i){
			//board coordinates
			printf("%d ",i);
			for(int j=8;j>=1;--j){
				//if a place is empty, we put an empty square
				if(game->board[i][j]<bKING){
					printf(" %lc",((i+j)%2==0)?wSQUARE:bSQUARE);
				}
				else{
					printf(" %lc",game->board[i][j]);
				}
			}
			//board coordinates
			printf("  %d\n",i);
		}
		//board coordinates
		printf("\n  ");
		for(int j=7;j>=0;--j){
			printf(" %c",'a'+j);
		}
		putchar('\n');
	}
	else{
		//board coordinates
		printf("  ");
		for(int j=0;j<=7;++j){
			printf(" %c",'a'+j);
		}
		printf("\n\n");
		for(int i=8;i>=1;--i){
			//board coordinates
			printf("%d ",i);
			for(int j=1;j<=8;++j){
				//if a place is empty, we put an empty square
				if(game->board[i][j]<bKING){
					printf(" %lc",((i+j)%2==0)?wSQUARE:bSQUARE);
				}
				else{
					printf(" %lc",game->board[i][j]);
				}
			}
			//board coordinates
			printf("  %d\n",i);
		}
		//board coordinates
		printf("\n  ");
		for(int j=0;j<=7;++j){
			printf(" %c",'a'+j);
		}
		putchar('\n');
	}
	
	//print the coverage
	#ifdef DEBUG
	printf("0x%llX 0x%llX\n",game->coverage[WHITE],game->coverage[BLACK]);
	for(int i=7;i>=0;--i){
		for(int j=0;j<8;++j){
			putchar(getBit(game->coverage[WHITE],i*8+j,uint64_t)+'0');
		}
		putchar('\n');
	}
	putchar('\n');
	for(int i=7;i>=0;--i){
		for(int j=0;j<8;++j){
			putchar(getBit(game->coverage[BLACK],i*8+j,uint64_t)+'0');
		}
		putchar('\n');
	}
	#endif
}