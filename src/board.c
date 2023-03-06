#include "board.h"

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
	game->board[8][1]=bROOK;game->pieces[BLACK][0]=(piece){bROOK,1,8,ACTIVE};
	game->board[8][2]=bKNIGHT;game->pieces[BLACK][1]=(piece){bKNIGHT,2,8,ACTIVE};
	game->board[8][3]=bBISHOP;game->pieces[BLACK][2]=(piece){bBISHOP,3,8,ACTIVE};
	game->board[8][4]=bQUEEN;game->pieces[BLACK][3]=(piece){bQUEEN,4,8,ACTIVE};
	game->board[8][5]=bKING;game->pieces[BLACK][4]=(piece){bKING,5,8,ACTIVE};
	game->board[8][6]=bBISHOP;game->pieces[BLACK][5]=(piece){bBISHOP,6,8,ACTIVE};
	game->board[8][7]=bKNIGHT;game->pieces[BLACK][6]=(piece){bKNIGHT,7,8,ACTIVE};
	game->board[8][8]=bROOK;game->pieces[BLACK][7]=(piece){bROOK,8,8,ACTIVE};
	for(int i=1;i<=8;++i){
		game->board[7][i]=bPAWN;game->pieces[BLACK][7+i]=(piece){bPAWN,i,7,ACTIVE};
	}

	game->board[1][1]=wROOK;game->pieces[WHITE][0]=(piece){wROOK,1,1,ACTIVE};
	game->board[1][2]=wKNIGHT;game->pieces[WHITE][1]=(piece){wKNIGHT,2,1,ACTIVE};
	game->board[1][3]=wBISHOP;game->pieces[WHITE][2]=(piece){wBISHOP,3,1,ACTIVE};
	game->board[1][4]=wQUEEN;game->pieces[WHITE][3]=(piece){wQUEEN,4,1,ACTIVE};
	game->board[1][5]=wKING;game->pieces[WHITE][4]=(piece){wKING,5,1,ACTIVE};
	game->board[1][6]=wBISHOP;game->pieces[WHITE][5]=(piece){wBISHOP,6,1,ACTIVE};
	game->board[1][7]=wKNIGHT;game->pieces[WHITE][6]=(piece){wKNIGHT,7,1,ACTIVE};
	game->board[1][8]=wROOK;game->pieces[WHITE][7]=(piece){wROOK,8,1,ACTIVE};
	for(int i=1;i<=8;++i){
		game->board[2][i]=wPAWN;game->pieces[WHITE][7+i]=(piece){wPAWN,i,2,ACTIVE};
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
				if(!game->board[i][j]){
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
				if(!game->board[i][j]){
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
}