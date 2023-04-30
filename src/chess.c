#define DEBUG

#include "gen.h"
#include "utils.h"
#include "board.h"
#include "move.h"
#include "piece.h"

#include <string.h>

match mainGame;

bool analizeCommand(const char* command,int mode){
	if(!strcmp(command,"undo")){
		getFromPast(&mainGame);
		return true;
	}
	int c[]={command[0]-'a'+1,command[1]-'0',command[2]-'a'+1,command[3]-'0'};
	for(int i=0;i<4;++i){
		if(c[i]<1||c[i]>8){
			printf("Invalid command!\n");
			return false;
		}
	}
	mov m={c[0],c[1],c[2]-c[0],c[3]-c[1],0};
	if(move(mainGame.current,&m,1) == 1){
		mainGame.current->toMove=!mainGame.current->toMove;
		addToPast(&mainGame);
		return true;
	}
	return false;
}

void play(){
	initMatch(&mainGame);
	initBoard(mainGame.current);
	addToPast(&mainGame);

	bool gameOver=0;
	char command[5];
	char mode;
	bool state,check;
	do{
		printf("Please choose mode:\n\t1) 1v1\n\t2) computer\n[1/2] ");
		avoidSpaces();
		mode=getchar();
	}while(mode != '1' && mode != '2');

	if(mode=='1'){
		while(!gameOver){
			printBoard(mainGame.current);
			printf("Score: %d\n",evalPosition(mainGame.current));

			check = getBit(mainGame.current->coverage[!mainGame.current->toMove],
						(mainGame.current->kingPosition[mainGame.current->toMove].y - 1) * 8 +
						(mainGame.current->kingPosition[mainGame.current->toMove].x - 1),
						uint64_t);
			gameOver = endGame(mainGame.current);
			if(gameOver){
				if(check){
					printf("%s wins!\n",(mainGame.current->toMove == WHITE) ? "BLACK" : "WHITE");
				}
				else{
					printf("Draw!\n");
				}
				return;
			}

			printf("%s",check ? "Check!\n":"");
			do{
				printf("%s to move: ",
						(mainGame.current->toMove == WHITE) ? "WHITE" : "BLACK");

				scanf("%4s",command);
				toLower(command);
				state=analizeCommand(command,1);
				if(!state){
					printf("Illegal move or invalid command!\n");
				}
			}while(!state);
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

		int difficulty;
		do{
			printf("Select difficulty [1-4]:");
			avoidSpaces();
			scanf("%d",&difficulty);
		}while(difficulty<1 || difficulty >4);

		while(!gameOver){
			check = getBit(mainGame.current->coverage[!mainGame.current->toMove],
						(mainGame.current->kingPosition[mainGame.current->toMove].y - 1) * 8 +
						(mainGame.current->kingPosition[mainGame.current->toMove].x - 1),
						uint64_t);
			gameOver = endGame(mainGame.current);
			if(gameOver){
				if(check){
					printf("%s wins!\n",(mainGame.current->toMove == WHITE) ? "BLACK" : "WHITE");
				}
				else{
					printf("Draw!\n");
				}
				return;
			}
			//player's move
			if(mainGame.current->toMove == color){
				printBoard(mainGame.current);
				printf("Score: %d\n",evalPosition(mainGame.current));
				printf("%s",check ? "Check!\n":"");
				
				do{
					printf("Your move: ");
					scanf("%4s",command);
					toLower(command);
					state=analizeCommand(command,2);
					if(!state){
						printf("Illegal move or invalid command!\n");
					}
				}while(!state);
			}
			//computer's move
			else{
				genMove(mainGame.current,difficulty);
				mainGame.current->toMove=!mainGame.current->toMove;
			}
		}
	}
}
		
int main(){
	srand(time(0));

	setlocale(LC_CTYPE,"");
	
	clear();
	play();
	return 0;
}