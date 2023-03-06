#define DEBUG

#include "gen.h"
#include "utils.h"
#include "board.h"
#include "move.h"
#include "piece.h"

extern int board[9][9];

bool toMove=WHITE;

bool analizeCommand(const char* command){
	int c[]={command[0]-'a'+1,command[1]-'0',command[2]-'a'+1,command[3]-'0'};
	for(int i=0;i<4;++i){
		if(c[i]<1||c[i]>8){
			printf("Invalid command!\n");
			return false;
		}
	}
	return move(c);
}

void play(){
	initBoard();
	bool gameOver=0;
	char command[5];
	char mode;
	do{
		printf("Please choose mode:\n\t1) 1v1\n\t2) computer\n[1/2] ");
		avoidSpaces();
		mode=getchar();
	}while(mode != '1' && mode != '2');

	if(mode=='1'){
		while(!gameOver){
			printBoard(toMove);
			printf("Score: %d\n",evalBoard());
			do{
				printf("%s to move: ",(toMove==WHITE)?"WHITE":"BLACK");
				scanf("%4s",command);
				toLower(command);
			}while(!analizeCommand(command));
			
			toMove=!toMove;
		}
	}
	else{
		char color;
		do{
			printf("Please choose your color:\n\t0) BLACK\n\t1) WHITE\n[0/1] ");
			avoidSpaces();
			color=getchar();
		}while(color != '0' && color != '1');
		color-='0';

		while(!gameOver){
			//player's move
			if(toMove == color){
				printBoard(toMove);
				printf("Score: %d\n",evalBoard());
				do{
					printf("Your move: ");
					scanf("%4s",command);
					toLower(command);
				}while(!analizeCommand(command));
			}
			//computer's move
			else{
				genMove(toMove);
			}
			
			toMove=!toMove;
		}
	}
}
		
int main(){
	srand(time(0));

	setlocale(LC_CTYPE,"");
	play();
	return 0;
}