#include "move.h"

extern bool toMove;
extern int board[9][9];

//king movement tracking
static bool wk=1,bk=1;

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
	// printf("x1:%d y1:%d x2:%d y2:%d\n",x1,y1,x2,y2);
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
			if(abs(y2-y1)>2){
				return INVALID;
			}
		}
		else{
			if(abs(y2-y1)>1){
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
			if(abs(y1-y2)>2){
				return INVALID;
			}
		}
		else{
			if(abs(y1-y2)>1){
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