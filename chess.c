/*
chess pieces unicodes
*/
#define bKING 	0x2654
#define bQUEEN 	0x2655
#define bROOK	0x2656
#define bBISHOP	0x2657
#define bKNIGHT	0x2658
#define bPAWN	0x2659
#define wKING	0x265A
#define wQUEEN	0x265B
#define wROOK	0x265C
#define wBISHOP	0x265D
#define wKNIGHT	0x265E
#define wPAWN	0x265F

#define bSQUARE	0x25A0
#define wSQUARE	0x25A1

#define WHITE 0
#define BLACK 1

#define clear() printf("\x1b[H\x1b[J")

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <stdint.h>
#include <stdbool.h>

uint16_t board[9][9];

void initBoard(){
	/*
	initial chess board definition
	*/
	board[1][1]=bROOK;
	board[1][2]=bKNIGHT;
	board[1][3]=bBISHOP;
	board[1][4]=bQUEEN;
	board[1][5]=bKING;
	board[1][6]=bBISHOP;
	board[1][7]=bKNIGHT;
	board[1][8]=bROOK;
	for(int i=1;i<9;++i){
		board[2][i]=bPAWN;
	}

	board[8][1]=wROOK;
	board[8][2]=wKNIGHT;
	board[8][3]=wBISHOP;
	board[8][4]=wQUEEN;
	board[8][5]=wKING;
	board[8][6]=wBISHOP;
	board[8][7]=wKNIGHT;
	board[8][8]=wROOK;
	for(int i=1;i<9;++i){
		board[7][i]=wPAWN;
	}
}

void printBoard(){
	clear();
	//board coordinates
	printf("  ");
	for(int j=0;j<8;++j){
		printf(" %c",'a'+j);
	}
	printf("\n\n");
	for(int i=1;i<9;++i){
		//board coordinates
		printf("%d ",i);
		for(int j=1;j<9;++j){
			//if a place is empty, we put an empty square
			if(!board[i][j]){
				printf(" %lc",((i+j)%2==1)?wSQUARE:bSQUARE);
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
	for(int j=0;j<8;++j){
		printf(" %c",'a'+j);
	}
	putchar('\n');
}

void analizeCommand(const char* command, int* a){
	
}

void play(){
	initBoard();
	bool gameOver=0;
	bool toMove=WHITE;
	char command[5];
	while(!gameOver){
		printBoard();
		printf("%s to move: ",(toMove==WHITE)?"WHITE":"BLACK");
		scanf("%4s",command);

		toMove=!toMove;
	}
}
		
int main(){
	setlocale(LC_CTYPE,"");
	play();
	return 0;
}