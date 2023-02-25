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

#define c2num(a) (a-'a'+1)

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

//king movement tracking
static bool wk=1,bk=1;

void avoidSpaces(){
	char c=getchar();
	while(isspace(c)){
		c=getchar();
	}
	ungetc(c,stdin);
}

int getPieceValue(unsigned piece){
	switch(piece){
		case wKING:
			return 900;
			break;
		case bKING:
			return -900;
			break;
		case wQUEEN:
			return 90;
			break;
		case bQUEEN:
			return -90;
			break;
		case wROOK:
			return 50;
			break;
		case bROOK:
			return -50;
			break;
		case wKNIGHT:
			return 30;
			break;
		case bKNIGHT:
			return -30;
			break;
		case wBISHOP:
			return 30;
			break;
		case bBISHOP:
			return -30;
			break;
		case wPAWN:
			return 10;
			break;
		case bPAWN:
			return -10;
			break;
		default:
			printf("Invalid piece!\n");
			return 0;
	}
}

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
	printf("Invalid piece code!\nThe program may not behave correctly!\n");
	return 1;
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

void printBoard(){
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


void toLower(char *s){
	while(*s){
		if(*s>='A'&&*s<='Z'){
			*s+=32;
		}
		++s;
	}
}

bool canPromote(int *c){
	int y2=c[3];
	return (y2==1||y2==8);
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
			printf("Invalid choice!\n");
			break;
		}
	}while(!ok);
}

bool canCastle(int *c){
	int x1=c[0],y1=c[1],x2=c[2];
	unsigned piece = board[y1][x1];
	if(piece == wKING){
		//check if the white king hasn't moved
		if(!wk){
			return false;
		}

		//check if castle position is valid
		if(x2!=c2num('g') && x2!=c2num('c')){
			return false;
		}

		//short castle
		if(x2==c2num('g')){
			//check if path is clear and if the rook is in place
			if(board[1][c2num('f')] || board[1][c2num('g')] || (board[1][c2num('h')]!=wROOK)){
				return false;
			}
		}

		//long castle
		else if(x2==c2num('c')){
			//check if path is clear and if the rook is in place
			if(board[1][c2num('b')] || board[1][c2num('c')] || board[1][c2num('d')] || (board[1][c2num('a')]!=wROOK)){
				return false;
			}
		}
	}
	else{
		//check if the black king hasn't moved
		if(!bk){
			return false;
		}
		
		//check if castle position is valid
		if(x2!=c2num('g') && x2!=c2num('c')){
			return false;
		}

		//short castle
		if(x2==c2num('g')){
			//check if path is clear and if the rook is in place
			if(board[8][c2num('f')] || board[8][c2num('g')] || (board[8][c2num('h')]!=bROOK)){
				return false;
			}
		}

		//long castle
		else if(x2==c2num('c')){
			//check if path is clear and if the rook is in place
			if(board[8][c2num('b')] || board[8][c2num('c')] || board[8][c2num('d')] || (board[8][c2num('a')]!=bROOK)){
				return false;
			}
		}
	}
	return true;
}

void castle(int x2, int y2){
	//white castle
	if(y2==1){
		//short castle
		if(x2==c2num('g')){
			board[1][c2num('e')]=0;
			board[1][c2num('h')]=0;

			board[1][c2num('g')]=wKING;
			board[1][c2num('f')]=wROOK;
		}
		//long castle
		else{
			board[1][c2num('e')]=0;
			board[1][c2num('a')]=0;

			board[1][c2num('c')]=wKING;
			board[1][c2num('d')]=wROOK;
		}
	}
	//black castle
	else{
		//short castle
		if(x2==c2num('g')){
			board[8][c2num('e')]=0;
			board[8][c2num('h')]=0;

			board[8][c2num('g')]=bKING;
			board[8][c2num('f')]=bROOK;
		}
		//long castle
		else{
			board[8][c2num('e')]=0;
			board[8][c2num('a')]=0;

			board[8][c2num('c')]=bKING;
			board[8][c2num('d')]=bROOK;
		}
	}
}

int takePiece(int x2,int y2){
	//check if the piece to be taken does not belong to the same player
	if(toMove==getPieceColor(board[y2][x2])){
		return INVALID;
	}
	return VALID;
}

int checkPath(int *c){
	int x1=c[0],y1=c[1],x2=c[2],y2=c[3];
	int bx,by,ex,ey;
	//check if the column x1 is clear
	if(x1==x2){
		int by=min(y1,y2),ey=max(y1,y2);
		for(int i=by+1;i<ey;++i){
			if(board[i][x1]){
				return INVALID;
			}
		}
	}
	//check if the row y1 is clear
	if(y1==y2){
		int bx=min(x1,x2),ex=max(x1,x2);
		for(int i=bx+1;i<ex;++i){
			if(board[y1][i]){
				return INVALID;
			}
		}
	}
	//check if the diagonal is clear
	else{
		bx=min(x1,x2),ex=max(x1,x2);
		by=min(y1,y2),ey=max(y1,y2);
		for(int i=bx+1, j=by+1; i<ex && j<ey; ++i, ++j){
			if(board[j][i]){
				return INVALID;
			}
		}
	}
	//capture the piece at the end of the path if exists
	if(board[y2][x2]){
		//if the piece at the end of the path belongs to the same player, the function will return INVALID
		return takePiece(x2,y2);
	}
	return VALID;
}

int isLegal(int *c){
	int x1=c[0],y1=c[1],x2=c[2],y2=c[3];
	#ifdef DEBUG
	printf("x1:%d y1:%d x2:%d y2:%d\n",x1,y1,x2,y2);
	#endif

	//check if the piece moves from its square
	if(x1==x2 && y1==y2){
		return INVALID;
	}
	switch (board[y1][x1])
	{
	case bPAWN:
		if(x1!=x2){
			//if the pawn moves diagonally
			if(abs(x1-x2)==1){
				//check if the capture is valid
				if(takePiece(x2,y2)==INVALID){
					return INVALID;
				}
			}
			else{
				return INVALID;
			}
		}
		else{
			//check if the square ahead is empty
			if(board[y2][x2]){
				return INVALID;
			}
		}

		//check if the pawn goes the right direction
		if(y2>y1){
			return INVALID;
		}

		//if pawn is in its initial position, it can move up to 2 squares
		if(y1==7){
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
		//knights always change their row and column,
		if(x1==x2||y1==y2){
			return INVALID;
		}
		//and move 3 squares in total
		if(abs(x1-x2)+abs(y1-y2)!=3){
			return INVALID;
		}
		return VALID;
		break;
	
	case bBISHOP:
		//check if the 2 coordiantes are on the same diagonal
		if(abs(x1-x2)!=abs(y1-y2)){
			return INVALID;
		}

		//check if the path is clear
		if(checkPath(c)==INVALID)return INVALID;
		return VALID;
		break;

	case bROOK:
		//rooks remain either on the same row or col
		if(x1!=x2 && y1!=y2){
			return INVALID;
		}
		//check if the path is clear
		if(checkPath(c)==INVALID)return INVALID;
		return VALID;
		break;

	case bKING:
		//if the king moves more than one sqr
		if(abs(x1-x2)>1 || abs(y1-y2)>1){
			if(!canCastle(c)){
				return INVALID;
			}
		}
		return VALID;
		break;
	
	case bQUEEN:
		//if the queen leaves both its row and col
		if(x1!=x2 && y1!=y2){
			//check if it goes diagonally
			if(abs(x1-x2)!=abs(y1-y2)){
				return INVALID;
			}
		}
		//check if the path is clear
		if(checkPath(c)==INVALID)return INVALID;
		return VALID;
		break;

	case wPAWN:
		if(x1!=x2){
			//if the pawn moves diagonally
			if(abs(x1-x2)==1){
				//check if the capture is valid
				if(takePiece(x2,y2)==INVALID){
					return INVALID;
				}
			}
			else{
				return INVALID;
			}
		}
		else{
			//check if the square ahead is empty
			if(board[y2][x2]){
				return INVALID;
			}
		}

		//check if the pawn goes the right direction
		if(y2<y1){
			return INVALID;
		}

		//if pawn is in its initial position, it can move up to 2 squares
		if(y1==2){
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
		//knights always change their row and column,
		if(x1==x2||y1==y2){
			return INVALID;
		}
		//and move 3 squares in total
		if(abs(x1-x2)+abs(y1-y2)!=3){
			return INVALID;
		}
		return VALID;
		break;

	case wBISHOP:
		//check if the 2 coordiantes are on the same diagonal
		if(abs(x1-x2)!=abs(y1-y2)){
			return INVALID;
		}

		//check if the path is clear
		if(checkPath(c)==INVALID)return INVALID;
		return VALID;
		break;

	case wROOK:
		//rooks remain either on the same row or col
		if(x1!=x2 && y1!=y2){
			return INVALID;
		}
		//check if the path is clear
		if(checkPath(c)==INVALID)return INVALID;
		return VALID;
		break;
	
	case wKING:
		//if the king moves more than one sqr
		if(abs(x1-x2)>1 || abs(y1-y2)>1){
			if(!wk){
				return INVALID;
			}
			if(!canCastle(c)){
				return INVALID;
			}
		}
		return VALID;
		break;
	
	case wQUEEN:
		//if the queen leaves both its row and col
		if(x1!=x2 && y1!=y2){
			//check if it goes diagonally
			if(abs(x1-x2)!=abs(y1-y2)){
				return INVALID;
			}
		}
		if(checkPath(c)==INVALID)return INVALID;
		return VALID;
		break;
	
	default:
		printf("Invalid piece!\n");
		return INVALID;
		break;
	}
}

void makeMove(int *c){
	int x1=c[0],y1=c[1],x2=c[2],y2=c[3];
	//make the move
	board[y2][x2]=board[y1][x1];
	board[y1][x1]=0;
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
		printf("Illegal move!\n");
		return INVALID;
	}

	switch (board[y1][x1])
	{
	case wPAWN:
		if(canPromote(c)){
			promote(x2,y2);
			board[y1][x1]=0;
		}
		else{
			makeMove(c);
		}
		break;
	case bPAWN:
		if(canPromote(c)){
			promote(x2,y2);
			board[y1][x1]=0;
		}
		else{
			makeMove(c);
		}
		break;
	case wKING:
		//if the king moves more than 1 sqr
		if(abs(x2-x1)>1 || abs(y2-y1)>1){
			castle(x2,y2);
		}
		else{
			makeMove(c);
		}
		wk=0;
		break;
	case bKING:
		//if the king moves more than 1 sqr
		if(abs(x2-x1)>1 || abs(y2-y1)>1){
			castle(x2,y2);
		}
		else{
			makeMove(c);
		}
		bk=0;
		break;
	default:
		makeMove(c);
		break;
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
		printf("Score: %d\n",evalBoard());
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