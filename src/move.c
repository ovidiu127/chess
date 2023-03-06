#include "move.h"

bool canPromote(int *c){
	int y2=c[3];
	return (y2==1||y2==8);
}

void promote(position *game,int x2,int y2){
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
			game->board[y2][x2]=(game->toMove==WHITE)?wQUEEN:bQUEEN;
			ok=1;
			break;
		
		case 'r':
			game->board[y2][x2]=(game->toMove==WHITE)?wROOK:bROOK;
			ok=1;
			break;
		
		case 'n':
			game->board[y2][x2]=(game->toMove==WHITE)?wKNIGHT:bKNIGHT;
			ok=1;
			break;
		
		case 'b':
			game->board[y2][x2]=(game->toMove==WHITE)?wBISHOP:bBISHOP;
			ok=1;
			break;
		
		default:
			printf("Invalid choice!\n");
			break;
		}
	}while(!ok);
}

bool canCastle(position *game,int *c){
	int x1=c[0],y1=c[1],x2=c[2];
	unsigned piece = game->board[y1][x1];
	if(piece == wKING){
		//check if the white king hasn't moved
		if(!game->wk){
			return false;
		}

		//check if castle position is valid
		if(x2!=c2num('g') && x2!=c2num('c')){
			return false;
		}

		//short castle
		if(x2==c2num('g')){
			//check if path is clear and if the rook is in place
			if(game->board[1][c2num('f')] || game->board[1][c2num('g')] || (game->board[1][c2num('h')]!=wROOK)){
				return false;
			}
		}

		//long castle
		else if(x2==c2num('c')){
			//check if path is clear and if the rook is in place
			if(game->board[1][c2num('b')] || game->board[1][c2num('c')] || game->board[1][c2num('d')] || (game->board[1][c2num('a')]!=wROOK)){
				return false;
			}
		}
	}
	else{
		//check if the black king hasn't moved
		if(!game->bk){
			return false;
		}
		
		//check if castle position is valid
		if(x2!=c2num('g') && x2!=c2num('c')){
			return false;
		}

		//short castle
		if(x2==c2num('g')){
			//check if path is clear and if the rook is in place
			if(game->board[8][c2num('f')] || game->board[8][c2num('g')] || (game->board[8][c2num('h')]!=bROOK)){
				return false;
			}
		}

		//long castle
		else if(x2==c2num('c')){
			//check if path is clear and if the rook is in place
			if(game->board[8][c2num('b')] || game->board[8][c2num('c')] || game->board[8][c2num('d')] || (game->board[8][c2num('a')]!=bROOK)){
				return false;
			}
		}
	}
	return true;
}

void castle(position *game,int x2, int y2){
	//white castle
	if(y2==1){
		//short castle
		if(x2==c2num('g')){
			game->board[1][c2num('e')]=0;
			game->board[1][c2num('h')]=0;

			game->board[1][c2num('g')]=wKING;
			game->board[1][c2num('f')]=wROOK;
		}
		//long castle
		else{
			game->board[1][c2num('e')]=0;
			game->board[1][c2num('a')]=0;

			game->board[1][c2num('c')]=wKING;
			game->board[1][c2num('d')]=wROOK;
		}
	}
	//black castle
	else{
		//short castle
		if(x2==c2num('g')){
			game->board[8][c2num('e')]=0;
			game->board[8][c2num('h')]=0;

			game->board[8][c2num('g')]=bKING;
			game->board[8][c2num('f')]=bROOK;
		}
		//long castle
		else{
			game->board[8][c2num('e')]=0;
			game->board[8][c2num('a')]=0;

			game->board[8][c2num('c')]=bKING;
			game->board[8][c2num('d')]=bROOK;
		}
	}
}

bool takePiece(position *game,int x2,int y2){
	//check if the piece to be taken does not belong to the same player
	if(game->toMove==getPieceColor(game->board[y2][x2])){
		return false;
	}
	for(int i=0;i<16;++i){
		if(game->pieces[game->toMove][i].x==x2 && game->pieces[game->toMove][i].y==y2){
			game->pieces[game->toMove][i].s=INACTIVE;
		}
	}
	return true;
}

bool checkPath(position *game,int *c){
	int x1=c[0],y1=c[1],x2=c[2],y2=c[3];
	int bx,by,ex,ey;
	//check if the column x1 is clear
	if(x1==x2){
		int by=min(y1,y2),ey=max(y1,y2);
		for(int i=by+1;i<ey;++i){
			if(game->board[i][x1]){
				return false;
			}
		}
	}
	//check if the row y1 is clear
	if(y1==y2){
		int bx=min(x1,x2),ex=max(x1,x2);
		for(int i=bx+1;i<ex;++i){
			if(game->board[y1][i]){
				return false;
			}
		}
	}
	//check if the diagonal is clear
	else{
		bx=min(x1,x2),ex=max(x1,x2);
		by=min(y1,y2),ey=max(y1,y2);
		for(int i=bx+1, j=by+1; i<ex && j<ey; ++i, ++j){
			if(game->board[j][i]){
				return false;
			}
		}
	}
	//capture the piece at the end of the path if exists
	if(game->board[y2][x2]){
		//if the piece at the end of the path belongs to the same player, the function will return false
		return takePiece(game,x2,y2);
	}
	return true;
}

bool isLegal(position *game,int *c){
	int x1=c[0],y1=c[1],x2=c[2],y2=c[3];
	#ifdef DEBUG
	// printf("x1:%d y1:%d x2:%d y2:%d\n",x1,y1,x2,y2);
	#endif

	//check if the piece moves from its square
	if(x1==x2 && y1==y2){
		return false;
	}
	switch (game->board[y1][x1])
	{
	case bPAWN:
		if(x1!=x2){
			//if the pawn moves diagonally
			if(abs(x1-x2)==1){
				//check if there is a piece to be taken
				if(!game->board[y2][x2]){
					return false;
				}
				//check if the capture is valid
				if(!takePiece(game,x2,y2)){
					return false;
				}
			}
			else{
				return false;
			}
		}
		else{
			//check if the square ahead is empty
			if(game->board[y2][x2]){
				return false;
			}
		}

		//check if the pawn goes the right direction
		if(y2>y1){
			return false;
		}

		//if pawn is in its initial position, it can move up to 2 squares
		if(y1==7){
			if(abs(y2-y1)>2){
				return false;
			}
		}
		else{
			if(abs(y2-y1)>1){
				return false;
			}
		}
		return true;
	
	case bKNIGHT:
		//knights always change their row and column,
		if(x1==x2||y1==y2){
			return false;
		}
		//check if the dest sqr is empty or piece can be captured
		if(game->board[y2][x2]){
			if(!takePiece(game,x2,y2)){
				return false;
			}
		}
		//and move 3 squares in total
		if(abs(x1-x2)+abs(y1-y2)!=3){
			return false;
		}
		return true;
	
	case bBISHOP:
		//check if the 2 coordiantes are on the same diagonal
		if(abs(x1-x2)!=abs(y1-y2)){
			return false;
		}

		//check if the path is clear
		if(!checkPath(game,c))return false;
		return true;

	case bROOK:
		//rooks remain either on the same row or col
		if(x1!=x2 && y1!=y2){
			return false;
		}
		//check if the path is clear
		if(!checkPath(game,c))return false;
		return true;

	case bKING:
		//if the king moves more than one sqr
		if(abs(x1-x2)>1 || abs(y1-y2)>1){
			if(!canCastle(game,c)){
				return false;
			}
		}
		//check if the dest sqr is empty or piece can be captured
		if(game->board[y2][x2]){
			if(!takePiece(game,x2,y2)){
				return false;
			}
		}
		return true;
	
	case bQUEEN:
		//if the queen leaves both its row and col
		if(x1!=x2 && y1!=y2){
			//check if it goes diagonally
			if(abs(x1-x2)!=abs(y1-y2)){
				return false;
			}
		}
		//check if the path is clear
		if(!checkPath(game,c))return false;
		return true;

	case wPAWN:
		if(x1!=x2){
			//if the pawn moves diagonally
			if(abs(x1-x2)==1){
				//check if there is a piece to be taken
				if(!game->board[y2][x2]){
					return false;
				}
				//check if the capture is valid
				if(!takePiece(game,x2,y2)){
					return false;
				}
			}
			else{
				return false;
			}
		}
		else{
			//check if the square ahead is empty
			if(game->board[y2][x2]){
				return false;
			}
		}

		//check if the pawn goes the right direction
		if(y2<y1){
			return false;
		}

		//if pawn is in its initial position, it can move up to 2 squares
		if(y1==2){
			if(abs(y1-y2)>2){
				return false;
			}
		}
		else{
			if(abs(y1-y2)>1){
				return false;
			}
		}
		return true;

	case wKNIGHT:
		//knights always change their row and column,
		if(x1==x2||y1==y2){
			return false;
		}
		//check if the dest sqr is empty or piece can be captured
		if(game->board[y2][x2]){
			if(!takePiece(game,x2,y2)){
				return false;
			}
		}
		//and move 3 squares in total
		if(abs(x1-x2)+abs(y1-y2)!=3){
			return false;
		}
		return true;

	case wBISHOP:
		//check if the 2 coordiantes are on the same diagonal
		if(abs(x1-x2)!=abs(y1-y2)){
			return false;
		}

		//check if the path is clear
		if(!checkPath(game,c))return false;
		return true;

	case wROOK:
		//rooks remain either on the same row or col
		if(x1!=x2 && y1!=y2){
			return false;
		}
		//check if the path is clear
		if(!checkPath(game,c))return false;
		return true;
	
	case wKING:
		//if the king moves more than one sqr
		if(abs(x1-x2)>1 || abs(y1-y2)>1){
			if(!canCastle(game,c)){
				return false;
			}
		}
		//check if the dest sqr is empty or piece can be captured
		if(game->board[y2][x2]){
			if(!takePiece(game,x2,y2)){
				return false;
			}
		}
		return true;
	
	case wQUEEN:
		//if the queen leaves both its row and col
		if(x1!=x2 && y1!=y2){
			//check if it goes diagonally
			if(abs(x1-x2)!=abs(y1-y2)){
				return false;
			}
		}
		if(!checkPath(game,c))return false;
		return true;
	
	default:
		#ifdef DEBUG
		printf("Invalid piece!\n");
		#endif

		return false;
	}
}

void makeMove(position *game,int *c){
	int x1=c[0],y1=c[1],x2=c[2],y2=c[3];
	//make the move
	game->board[y2][x2]=game->board[y1][x1];
	game->board[y1][x1]=0;
}

bool move(position *game,int *c){
	int x1=c[0],y1=c[1],x2=c[2],y2=c[3];

	//check if the piece is of right color
	#ifdef DEBUG
	printf("toMove: %d pieceColor: %d\n",toMove,getPieceColor(board[y1][x1]));
	#endif
	if(!(game->toMove==getPieceColor(game->board[y1][x1]))){
		printf("You cannot move that piece!\nTry again!\n");
		return false;
	}

	//check if move is legal
	if(!isLegal(game,c)){
		printf("Illegal move!\n");
		return false;
	}

	switch (game->board[y1][x1])
	{
	case wPAWN:
		if(canPromote(c)){
			promote(game,x2,y2);
			game->board[y1][x1]=0;
		}
		else{
			makeMove(game,c);
		}
		break;
	case bPAWN:
		if(canPromote(c)){
			promote(game,x2,y2);
			game->board[y1][x1]=0;
		}
		else{
			makeMove(game,c);
		}
		break;
	case wKING:
		//if the king moves more than 1 sqr
		if(abs(x2-x1)>1 || abs(y2-y1)>1){
			castle(game,x2,y2);
		}
		else{
			makeMove(game,c);
		}
		game->wk=0;
		break;
	case bKING:
		//if the king moves more than 1 sqr
		if(abs(x2-x1)>1 || abs(y2-y1)>1){
			castle(game,x2,y2);
		}
		else{
			makeMove(game,c);
		}
		game->bk=0;
		break;
	default:
		makeMove(game,c);
		break;
	}

	return true;
}

void applyMove(position *game,mov *m){
	int c[]={m->p->x,m->p->y,m->p->x+m->x,m->p->y+m->y};
	move(game,c);
	m->p->x+=m->x;
	m->p->y+=m->y;
}