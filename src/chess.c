#define DEBUG

#include "gen.h"
#include "utils.h"
#include "board.h"
#include "move.h"
#include "piece.h"
#include "savegame.h"
#include "menu.h"

#include <string.h>

static match mainGame;

bool analizeCommand(const char* command,int mode){
	if(!strcmp(command,"undo")){
		getFromPast(&mainGame);
		return true;
	}
	if(!strcmp(command,"save")){
		char *file=malloc(20 * sizeof(char));
		if(file == NULL){
			perror("malloc()");
			exit(1);
		}

		printf("Enter the filename: ");
		scanf("%19s",file);
		skipLine();
		save(&mainGame,file);
		exit(0);
	}
	if(!strcmp(command,"exit")){
		exit(0);
	}
	int c[]={command[0] - 'a' + 1,command[1] - '0',command[2] - 'a' + 1,command[3] - '0'};
	for(int i=0;i < 4;++i){
		if(c[i] < 1 || c[i] > 8){
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
	bool gameOver=0;
	char command[5];
	bool state,check;
	char gameType;

	gameType = menu("Hello!\n\t1) Start a new game\n\t2) Load a game\n","12") - '0';

	//start new game
	if(gameType == 1){
		initMatch(&mainGame);
		initBoard(mainGame.current);
		addToPast(&mainGame);

		mainGame.mode = menu("Please choose mode:\n\t1) 1v1\n\t2) computer\n","12") - '0';

		if(mainGame.mode == 2){
			mainGame.color = menu("Please choose your color:\n\t0) BLACK\n\t1) WHITE\n","01") - '0';
			mainGame.difficulty = menu("Select difficulty ","1234") - '0';
		}
	}
	//load existing game
	else{
		char *file=malloc(20 * sizeof(char));
		if(file == NULL){
			perror("malloc()");
			exit(1);
		}

		printf("Enter the filename: ");
		scanf("%19s",file);
		skipLine();
		load(&mainGame,file);

		free(file);
	}

	if(mainGame.mode == 1){
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
				skipLine();
				toLower(command);
				state=analizeCommand(command,1);
				if(!state){
					printf("Illegal move or invalid command!\n");
				}
			}while(!state);
		}
	}
	else{
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
			if(mainGame.current->toMove == mainGame.color){
				printBoard(mainGame.current);
				printf("Score: %d\n",evalPosition(mainGame.current));
				printf("%s",check ? "Check!\n":"");
				
				do{
					printf("Your move: ");
					scanf("%4s",command);
					skipLine();
					toLower(command);
					state=analizeCommand(command,2);
					if(!state){
						printf("Illegal move or invalid command!\n");
					}
				}while(!state);
			}
			//computer's move
			else{
				genMove(mainGame.current,mainGame.difficulty);
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