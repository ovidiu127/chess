#define DEBUG

#include "gen.h"
#include "utils.h"
#include "board.h"
#include "move.h"
#include "piece.h"

position mainGame;

bool analizeCommand(const char* command){
	int c[]={command[0]-'a'+1,command[1]-'0',command[2]-'a'+1,command[3]-'0'};
	for(int i=0;i<4;++i){
		if(c[i]<1||c[i]>8){
			printf("Invalid command!\n");
			return false;
		}
	}
	return move(&mainGame,c);
}

void play(){
	initBoard(&mainGame);
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
			printBoard(&mainGame);
			printf("Score: %d\n",evalPosition(&mainGame));
			do{
				printf("%s to move: ",(mainGame.toMove==WHITE)?"WHITE":"BLACK");
				scanf("%4s",command);
				toLower(command);
			}while(!analizeCommand(command));
			
			mainGame.toMove=!mainGame.toMove;
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
			if(mainGame.toMove == color){
				printBoard(&mainGame);
				printf("Score: %d\n",evalPosition(&mainGame));
				do{
					printf("Your move: ");
					scanf("%4s",command);
					toLower(command);
				}while(!analizeCommand(command));
			}
			//computer's move
			else{
				genMove(&mainGame);
			}
			
			mainGame.toMove=!mainGame.toMove;
		}
	}
}
		
int main(){
	srand(time(0));

	setlocale(LC_CTYPE,"");
	play();
	return 0;
}