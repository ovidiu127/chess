#include "board.h"

int board[9][9];

int evalBoard(){
	int score=0;

	for(int i=1;i<=8;++i){
		for(int j=1;j<=8;++j){
			if(board[i][j]){
				score+=getPieceValue(board[i][j]);
			}
		}
	}

	return score;
}

void initBoard(){
	/*
	initial chess board definition
	*/
	board[8][1]=bROOK;
	board[8][2]=bKNIGHT;
	board[8][3]=bBISHOP;
	board[8][4]=bQUEEN;
	board[8][5]=bKING;
	board[8][6]=bBISHOP;
	board[8][7]=bKNIGHT;
	board[8][8]=bROOK;
	for(int i=1;i<=8;++i){
		board[7][i]=bPAWN;
	}

	board[1][1]=wROOK;
	board[1][2]=wKNIGHT;
	board[1][3]=wBISHOP;
	board[1][4]=wQUEEN;
	board[1][5]=wKING;
	board[1][6]=wBISHOP;
	board[1][7]=wKNIGHT;
	board[1][8]=wROOK;
	for(int i=1;i<=8;++i){
		board[2][i]=wPAWN;
	}
}

void printBoard(bool toMove){
	clear();
	if(toMove==BLACK){
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
				if(!board[i][j]){
					printf(" %lc",((i+j)%2==0)?wSQUARE:bSQUARE);
				}
				else{
					printf(" %lc",board[i][j]);
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
				if(!board[i][j]){
					printf(" %lc",((i+j)%2==0)?wSQUARE:bSQUARE);
				}
				else{
					printf(" %lc",board[i][j]);
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