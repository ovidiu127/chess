#include "board.h"

int board[9][9];

extern piece pieces[32];

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
	board[8][1]=bROOK;pieces[0]=(piece){bROOK,1,8,ACTIVE};
	board[8][2]=bKNIGHT;pieces[1]=(piece){bKNIGHT,2,8,ACTIVE};
	board[8][3]=bBISHOP;pieces[2]=(piece){bBISHOP,3,8,ACTIVE};
	board[8][4]=bQUEEN;pieces[3]=(piece){bQUEEN,4,8,ACTIVE};
	board[8][5]=bKING;pieces[4]=(piece){bKING,5,8,ACTIVE};
	board[8][6]=bBISHOP;pieces[5]=(piece){bBISHOP,6,8,ACTIVE};
	board[8][7]=bKNIGHT;pieces[6]=(piece){bKNIGHT,7,8,ACTIVE};
	board[8][8]=bROOK;pieces[7]=(piece){bROOK,8,8,ACTIVE};
	for(int i=1;i<=8;++i){
		board[7][i]=bPAWN;pieces[7+i]=(piece){bPAWN,i,7,ACTIVE};
	}

	board[1][1]=wROOK;pieces[16]=(piece){wROOK,1,1,ACTIVE};
	board[1][2]=wKNIGHT;pieces[17]=(piece){wKNIGHT,2,1,ACTIVE};
	board[1][3]=wBISHOP;pieces[18]=(piece){wBISHOP,3,1,ACTIVE};
	board[1][4]=wQUEEN;pieces[19]=(piece){wQUEEN,4,1,ACTIVE};
	board[1][5]=wKING;pieces[20]=(piece){wKING,5,1,ACTIVE};
	board[1][6]=wBISHOP;pieces[21]=(piece){wBISHOP,6,1,ACTIVE};
	board[1][7]=wKNIGHT;pieces[22]=(piece){wKNIGHT,7,1,ACTIVE};
	board[1][8]=wROOK;pieces[23]=(piece){wROOK,8,1,ACTIVE};
	for(int i=1;i<=8;++i){
		board[2][i]=wPAWN;pieces[23+i]=(piece){wPAWN,i,2,ACTIVE};
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