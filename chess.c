/*
chess pieces unicodes
*/

#define DEBUG

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

#define WHITE 1
#define BLACK 0

#define INVALID -1
#define VALID	0

#define min(a,b)	((a<b)?a:b)
#define max(a,b)	((a>b)?a:b)

#define clear() 	printf("\x1b[H\x1b[J")

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

static uint16_t board[9][9];
static bool toMove=WHITE;

bool getPieceColor(unsigned piece){
	if(	piece==bKING||
		piece==bQUEEN||
		piece==bKNIGHT||
		piece==bBISHOP||
		piece==bROOK||
		piece==bPAWN){
		return BLACK;
	}

	if(	piece==wKING||
		piece==wQUEEN||
		piece==wKNIGHT||
		piece==wBISHOP||
		piece==wROOK||
		piece==wPAWN){
		return WHITE;
	}
	perror("Invalid piece code!\nThe program may not behave correctly!\n");
	return 1;
}

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
	if(toMove==WHITE){
		//board coordinates
		printf("  ");
		for(int j=0;j<8;++j){
			printf(" %c",'a'+j);
		}
		printf("\n\n");
		for(int i=1;i<=8;++i){
			//board coordinates
			printf("%d ",i);
			for(int j=1;j<=8;++j){
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
	else{
		//board coordinates
		printf("  ");
		for(int j=7;j>=0;--j){
			printf(" %c",'a'+j);
		}
		printf("\n\n");
		for(int i=8;i>=1;--i){
			//board coordinates
			printf("%d ",i);
			for(int j=8;j>=1;--j){
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
		for(int j=7;j>=0;--j){
			printf(" %c",'a'+j);
		}
		putchar('\n');
	}
}


void toLower(char *s){
	while(*s){
		if(*s>='A'&&*s<='Z'){
			*s+=32;
		}
		++s;
	}
}

bool canPromote(int *c){
	int x1=c[0],y1=c[1],x2=c[2],y2=c[3];
	return (y2==1||y2==8);
}

void avoidSpaces(){
	char c=getchar();
	while(isspace(c)){
		c=getchar();
	}
	ungetc(c,stdin);
}

void promote(int x2,int y2){
	bool ok=0;
	do{
		printf("Promote pawn to [Q/R/N/B]:");
		avoidSpaces();
		char promote=getchar();
		if(promote>='A' && promote<='Z'){
			promote+=32;
		}
		switch (promote)
		{
		case 'q':
			board[y2][x2]=(toMove==WHITE)?wQUEEN:bQUEEN;
			ok=1;
			break;
		
		case 'r':
			board[y2][x2]=(toMove==WHITE)?wROOK:bROOK;
			ok=1;
			break;
		
		case 'n':
			board[y2][x2]=(toMove==WHITE)?wKNIGHT:bKNIGHT;
			ok=1;
			break;
		
		case 'b':
			board[y2][x2]=(toMove==WHITE)?wBISHOP:bBISHOP;
			ok=1;
			break;
		
		default:
			perror("Invalid choice!\n");
			break;
		}
	}while(!ok);
}

int takePiece(int x2,int y2){
	if(toMove==getPieceColor(board[y2][x2])){
		return INVALID;
	}
	return VALID;
}

int checkPath(int *c){
	int x1=c[0],y1=c[1],x2=c[2],y2=c[3];
	int bx,by,ex,ey;
	if(x1==x2){
		int by=min(y1,y2),ey=max(y1,y2);
		for(int i=by+1;i<ey;++i){
			if(board[i][x1]){
				return INVALID;
			}
		}
	}
	if(y1==y2){
		int bx=min(x1,x2),ex=max(x1,x2);
		for(int i=bx+1;i<ex;++i){
			if(board[y1][i]){
				return INVALID;
			}
		}
	}
	else{
		bx=min(x1,x2),ex=max(x1,x2);
		by=min(y1,y2),ey=max(y1,y2);
		for(int i=bx+1, j=by+1; i<ex && j<ey; ++i, ++j){
			if(board[j][i]){
				return INVALID;
			}
		}
	}
	if(board[y2][x2]){
		return takePiece(x2,y2);
	}
	return VALID;
}

int isLegal(int *c){
	int x1=c[0],y1=c[1],x2=c[2],y2=c[3];
	#ifdef DEBUG
	printf("x1:%d y1:%d x2:%d y2:%d\n",x1,y1,x2,y2);
	#endif
	if(x1==x2 && y1==y2){
		return INVALID;
	}
	switch (board[y1][x1])
	{
	case bPAWN:
		if(x1!=x2){
			if(abs(x1-x2)==1){
				if(takePiece(x2,y2)==INVALID){
					return INVALID;
				}
			}
			else{
				return INVALID;
			}
		}
		else{
			if(board[y2][x2]){
				return INVALID;
			}
		}

		if(y2<y1){
			return INVALID;
		}
		if(y1==2){
			if(y2-y1>2){
				return INVALID;
			}
		}
		else{
			if(y2-y1>1){
				return INVALID;
			}
		}
		return VALID;
		break;
	
	case bKNIGHT:
		if(x1==x2||y1==y2){
			return INVALID;
		}
		if(abs(x1-x2)+abs(y1-y2)!=3){
			return INVALID;
		}
		return VALID;
		break;
	
	case bBISHOP:
		if(abs(x1-x2)!=abs(y1-y2)){
			return INVALID;
		}
		if(checkPath(c)==INVALID)return INVALID;
		return VALID;
		break;

	case bROOK:
		if(x1!=x2 && y1!=y2){
			return INVALID;
		}
		if(checkPath(c)==INVALID)return INVALID;
		return VALID;
		break;

	case bKING:
		if(abs(x1-x2)>1 || abs(y1-y2)>1){
			return INVALID;
		}
		return VALID;
		break;
	
	case bQUEEN:
		if(x1!=x2 && y1!=y2){
			if(abs(x1-x2)!=abs(y1-y2)){
				return INVALID;
			}
		}
		if(checkPath(c)==INVALID)return INVALID;
		return VALID;
		break;

	case wPAWN:
		if(x1!=x2){
			if(abs(x1-x2)==1){
				if(takePiece(x2,y2)==INVALID){
					return INVALID;
				}
			}
			else{
				return INVALID;
			}
		}
		else{
			if(board[y2][x2]){
				return INVALID;
			}
		}

		if(y2>y1){
			return INVALID;
		}
		if(y1==7){
			if(y1-y2>2){
				return INVALID;
			}
		}
		else{
			if(y1-y2>1){
				return INVALID;
			}
		}
		return VALID;
		break;

	case wKNIGHT:
		if(x1==x2||y1==y2){
			return INVALID;
		}
		if(abs(x1-x2)+abs(y1-y2)!=3){
			return INVALID;
		}
		return VALID;
		break;

	case wBISHOP:
		if(abs(x1-x2)!=abs(y1-y2)){
			return INVALID;
		}
		if(checkPath(c)==INVALID)return INVALID;
		return VALID;
		break;

	case wROOK:
		if(x1!=x2 && y1!=y2){
			return INVALID;
		}
		if(checkPath(c)==INVALID)return INVALID;
		return VALID;
		break;
	
	case wKING:
		if(abs(x1-x2)>1 || abs(y1-y2)>1){
			return INVALID;
		}
		return VALID;
		break;
	
	case wQUEEN:
		if(x1!=x2 && y1!=y2){
			if(abs(x1-x2)!=abs(y1-y2)){
				return INVALID;
			}
		}
		if(checkPath(c)==INVALID)return INVALID;
		return VALID;
		break;
	
	default:
		perror("Invalid piece!\n");
		return INVALID;
		break;
	}
}

int move(int *c){
	int x1=c[0],y1=c[1],x2=c[2],y2=c[3];

	//check if the piece is of right color
	#ifdef DEBUG
	printf("toMove: %d pieceColor: %d\n",toMove,getPieceColor(board[y1][x1]));
	#endif
	if(!(toMove==getPieceColor(board[y1][x1]))){
		printf("You cannot move that piece!\nTry again!\n");
		return INVALID;
	}

	//check if move is legal
	if(isLegal(c)==INVALID){
		perror("Illegal move!\n");
		return INVALID;
	}

	//check if a pawn can promote
	if((board[y1][x1]==wPAWN || board[y1][x1]==bPAWN) && canPromote(c)){
		promote(x2,y2);
		board[y1][x1]=0;
	}
	else{
		//make the move
		board[y2][x2]=board[y1][x1];
		board[y1][x1]=0;
	}

	return VALID;
}

int analizeCommand(const char* command){
	int c[]={command[0]-'a'+1,command[1]-'0',command[2]-'a'+1,command[3]-'0'};
	for(int i=0;i<4;++i){
		if(c[i]<1||c[i]>8){
			printf("Invalid command!\n");
			return INVALID;
		}
	}
	return move(c);
}

void play(){
	initBoard();
	bool gameOver=0;
	char command[5];
	while(!gameOver){
		printBoard();
		do{
			printf("%s to move: ",(toMove==WHITE)?"WHITE":"BLACK");
			scanf("%4s",command);
			toLower(command);
		}while(analizeCommand(command)==INVALID);
		
		toMove=!toMove;
	}
}
		
int main(){
	setlocale(LC_CTYPE,"");
	play();
	return 0;
}