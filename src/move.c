#include "move.h"

static position auxil;

bool canPromote(mov *m){
	int y2=m->py+m->y;
	return (y2==1||y2==8);
}

void promote(position *game,int x2,int y2,int computerMove){
	if(computerMove){
		game->board[y2][x2]=(game->toMove==WHITE)?wQUEEN:bQUEEN;
		return;
	}

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

bool canCastle(position *game,mov *m){
	int x1=m->px,y1=m->py,x2=m->px+m->x;
	unsigned piece = game->board[y1][x1];
	if(piece == wKING){
		//check if the white king hasn't moved
		if(!game->kingCastle[WHITE]){
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
		if(!game->kingCastle[BLACK]){
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

bool canTakePiece(position *game,mov *m){
	int x2=m->px+m->x,y2=m->py+m->y;

	//check for En Passant captures
	if(game->board[y2][x2]==EN_PASSANT){
		return true;
	}

	//check if the piece to be taken does not belong to the same player
	return game->toMove!=getPieceColor(game->board[y2][x2]);
}

void takePiece(position *game,mov *m){
	int x1=m->px,y1=m->py,x2=m->px+m->x,y2=m->py+m->y;

	//check for En Passant captures
	if(game->board[y1][x1]==bPAWN || game->board[y1][x1]==wPAWN){
		if(game->board[y2][x2]==EN_PASSANT){
			game->board[y2][x2]=0;
			y2+=(game->board[y1][x1]==bPAWN)?1:-1;
			game->board[y2][x2]=0;
		}
	}
}

bool checkPath(position *game,mov *m){
	int x1=m->px,y1=m->py,x2=m->px+m->x,y2=m->py+m->y;
	int sx,sy;

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
	else if(y1==y2){
		int bx=min(x1,x2),ex=max(x1,x2);
		for(int i=bx+1;i<ex;++i){
			if(game->board[y1][i]){
				return false;
			}
		}
	}

	//check if the diagonal is clear
	else{
		sx=(x2-x1)/abs(x2-x1),
		sy=(y2-y1)/abs(y2-y1);

		for(int i=x1+sx, j=y1+sy; x2!=i && y2!=j; i+=sx, j+=sy){
			if(game->board[j][i]){
				return false;
			}
		}
	}

	//capture the piece at the end of the path if exists
	if(game->board[y2][x2]){
		//if the piece at the end of the path belongs to the same player, the function will return false
		return canTakePiece(game,m);
	}
	return true;
}

bool isLegal(position *game,mov *m){
	int x1=m->px,y1=m->py,x2=m->px+m->x,y2=m->py+m->y;

	//check if coordinates are in boundaries
	if(!inBounds(x1,y1) || !inBounds(x2,y2)){
		return false;
	}

	//check if the piece moves from its square
	if(x1==x2 && y1==y2){
		return false;
	}

	//check if the player has the right to move the piece
	if(!(game->toMove==getPieceColor(game->board[y1][x1]))){
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
				if(!canTakePiece(game,m)){
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

		break;

	case bKNIGHT:
		//knights always change their row and column,
		if(x1==x2||y1==y2){
			return false;
		}

		//check if the dest sqr is empty or piece can be captured
		if(game->board[y2][x2]){
			if(!canTakePiece(game,m)){
				return false;
			}
		}

		//and move 3 squares in total
		if(abs(x1-x2)+abs(y1-y2)!=3){
			return false;
		}

		break;

	case bBISHOP:
		//check if the 2 coordiantes are on the same diagonal
		if(abs(x1-x2)!=abs(y1-y2)){
			return false;
		}

		//check if the path is clear
		if(!checkPath(game,m)){
			return false;
		}

		break;

	case bROOK:
		//rooks remain either on the same row or col
		if(x1!=x2 && y1!=y2){
			return false;
		}

		//check if the path is clear
		if(!checkPath(game,m))return false;

		break;

	case bKING:
		// //check if the destination is safe
		// if(getBit(game->coverage[WHITE],(y2-1)*8+(x2-1),uint64_t)){
		// 	return false;
		// }

		//if the king moves more than one sqr
		if(abs(x1-x2)>1 || abs(y1-y2)>1){
			if(!canCastle(game,m)){
				return false;
			}
		}

		//check if the dest sqr is empty or piece can be captured
		if(game->board[y2][x2]){
			if(!canTakePiece(game,m)){
				return false;
			}
		}

		break;

	case bQUEEN:
		//if the queen leaves both its row and col
		if(x1!=x2 && y1!=y2){
			//check if it goes diagonally
			if(abs(x1-x2)!=abs(y1-y2)){
				return false;
			}
		}

		//check if the path is clear
		if(!checkPath(game,m))return false;

		break;

	case wPAWN:
		if(x1!=x2){
			//if the pawn moves diagonally
			if(abs(x1-x2)==1){
				//check if there is a piece to be taken
				if(!game->board[y2][x2]){
					return false;
				}

				//check if the capture is valid
				if(!canTakePiece(game,m)){
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

		break;

	case wKNIGHT:
		//knights always change their row and column,
		if(x1==x2||y1==y2){
			return false;
		}

		//check if the dest sqr is empty or piece can be captured
		if(game->board[y2][x2]){
			if(!canTakePiece(game,m)){
				return false;
			}
		}

		//and move 3 squares in total
		if(abs(x1-x2)+abs(y1-y2)!=3){
			return false;
		}

		break;

	case wBISHOP:
		//check if the 2 coordiantes are on the same diagonal
		if(abs(x1-x2)!=abs(y1-y2)){
			return false;
		}

		//check if the path is clear
		if(!checkPath(game,m)){
			return false;
		}

		break;

	case wROOK:
		//rooks remain either on the same row or col
		if(x1!=x2 && y1!=y2){
			return false;
		}

		//check if the path is clear
		if(!checkPath(game,m))return false;

		break;

	case wKING:
		// //check if the destination is safe
		// if(getBit(game->coverage[BLACK],(y2-1)*8+(x2-1),uint64_t)){
		// 	return false;
		// }

		//if the king moves more than one sqr
		if(abs(x1-x2)>1 || abs(y1-y2)>1){
			if(!canCastle(game,m)){
				return false;
			}
		}

		//check if the dest sqr is empty or piece can be captured
		if(game->board[y2][x2]){
			if(!canTakePiece(game,m)){
				return false;
			}
		}

		break;

	case wQUEEN:
		//if the queen leaves both its row and col
		if(x1!=x2 && y1!=y2){
			//check if it goes diagonally
			if(abs(x1-x2)!=abs(y1-y2)){
				return false;
			}
		}

		if(!checkPath(game,m))return false;

		break;

	default:
		#ifdef DEBUG
		printf("Invalid piece!\n");
		#endif

		return false;
	}

	//check if final position is safe for the king
	auxil = *game;
	move(&auxil,m,0);
	//get opponent's coverage
	uint64_t cov = getCoverage(&auxil,!game->toMove);
	//check if your king is checked by the opponent (i.e. is located in the opponent's coverage)
	if(getBit(cov,(auxil.kingPosition[game->toMove].y-1) * 8 + (auxil.kingPosition[game->toMove].x-1),uint64_t)){
		return false;
	}

	return true;
}

void makeMove(position *game,mov *m){
	int x1=m->px,y1=m->py,x2=m->px+m->x,y2=m->py+m->y;

	//make the move
	game->board[y2][x2]=game->board[y1][x1];
	game->board[y1][x1]=0;
}

void clearMarks(position *game){
	for(int i=1;i<=8;++i){
		for(int j=1;j<=8;++j){
			if(game->board[i][j]>0 && game->board[i][j]<bKING){
				game->board[i][j]=0;
			}
		}
	}
}

bool move(position *game,mov *m,int legalCheck){
	int x1=m->px,y1=m->py,x2=m->px+m->x,y2=m->py+m->y;

	//check if the piece is of right color
	#ifdef DEBUG
	printf("toMove: %d pieceColor: %d\n",toMove,getPieceColor(board[y1][x1]));
	#endif

	//check if move is legal
	if(legalCheck){
		if(!isLegal(game,m)){
			return false;
		}
	}

	//check if there is a piece to be taken
	if(game->board[y2][x2]){
		takePiece(game,m);
	}

	clearMarks(game);

	switch (game->board[y1][x1])
	{
	case wPAWN:
		if(canPromote(m)){
			//if (computer-move) do not ask for input
			promote(game,x2,y2,m->computerMove);
			game->board[y1][x1]=0;
		}
		else{
			makeMove(game,m);
			//check if the pawn has moved 2 squares (for En Passant)
			if(abs(y2-y1)==2){
				game->board[y2-1][x2]=EN_PASSANT;
			}
		}
		break;
	case bPAWN:
		if(canPromote(m)){
			//if (computer-move) do not ask for input
			promote(game,x2,y2,m->computerMove);
			game->board[y1][x1]=0;
		}
		else{
			makeMove(game,m);
			// check if the pawn has moved 2 squares (for En Passant)
			if(abs(y2-y1)==2){
				game->board[y2+1][x2]=EN_PASSANT;
			}
		}
		break;
	case wKING:
		//if the king moves more than 1 sqr
		if(abs(x2-x1)>1 || abs(y2-y1)>1){
			castle(game,x2,y2);
		}
		else{
			makeMove(game,m);
		}
		game->kingCastle[WHITE]=0;
		game->kingPosition[WHITE].y=y2;
		game->kingPosition[WHITE].x=x2;
		break;
	case bKING:
		//if the king moves more than 1 sqr
		if(abs(x2-x1)>1 || abs(y2-y1)>1){
			castle(game,x2,y2);
		}
		else{
			makeMove(game,m);
		}
		game->kingCastle[BLACK]=0;
		game->kingPosition[BLACK].y=y2;
		game->kingPosition[BLACK].x=x2;
		break;
	default:
		makeMove(game,m);
		break;
	}

	//for current player
	game->coverage[WHITE]=getCoverage(game,WHITE);
	//for oponent
	game->coverage[BLACK]=getCoverage(game,BLACK);

	return true;
}

uint16_t getCapturedPiece(position *game,mov *m){
	int x2=m->px+m->x,y2=m->py+m->y;

	return game->board[y2][x2];
}