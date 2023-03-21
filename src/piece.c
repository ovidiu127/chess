#include "piece.h"

moves* getMoves(position *game,int px,int py){
	int j=0;
	mov *ax;
	moves* ans=(moves*)malloc(sizeof(moves));
	if(ans==NULL){
		printf("Malloc failed!\n%s:%d\n",__FILE__,__LINE__);
		exit(EXIT_FAILURE);
	}
	
	ans->m=(mov*)malloc(64*sizeof(mov));
	if(ans->m==NULL){
		printf("Malloc failed!\n%s:%d\n",__FILE__,__LINE__);
		exit(EXIT_FAILURE);
	}

	const int Kx[]={-1,-1,-1, 0,0, 1,1,1};
	const int Ky[]={-1, 0, 1,-1,1,-1,0,1};
	const int Nx[]={-2,-2,-1,-1,1,1,2,2};
	const int Ny[]={-1,1,-2,2,-2,2,-1,1};
	const int Bx[]={1,1,-1,-1};
	const int By[]={1,-1,-1,1};
	const int Rx[]={0,0,1,-1};
	const int Ry[]={1,-1,0,0};
	const int Qx[]={0,0,1,-1,1,1,-1,-1};
	const int Qy[]={1,-1,0,0,1,-1,-1,1};
	const int bPx[]={1,0,-1,0};
	const int bPy[]={-1,-1,-1,-2};
	const int wPx[]={1,0,-1,0};
	const int wPy[]={1,1,1,2};

	switch(game->board[py][px]){
	case wKING:
	case bKING:
		for(int i=0;i<8;++i){
			ax=&((mov){px,py,Kx[i],Ky[i]});
			if(isLegal(game,ax)){
				ans->m[j++]=(mov){Kx[i],Ky[i]};
			}
		}
		break;
	case wKNIGHT:
	case bKNIGHT:
		for(int i=0;i<8;++i){
			ax=&((mov){px,py,Nx[i],Ny[i]});
			if(isLegal(game,ax)){
				ans->m[j++]=(mov){px,py,Nx[i],Ny[i]};
			}
		}
		break;
	case wBISHOP:
	case bBISHOP:
		for(int i=0;i<4;++i){
			for(int k=0;k<8;++k){
				ax=&((mov){px,py,Bx[i]*k,By[i]*k});
				if(isLegal(game,ax)){
					ans->m[j++]=(mov){px,py,Bx[i]*k,By[i]*k};
				}
				else{
					break;
				}
			}
		}
		break;
	case wROOK:
	case bROOK:
		for(int i=0;i<4;++i){
			for(int k=0;k<8;++k){
				ax=&((mov){px,py,Rx[i]*k,Ry[i]*k});
				if(isLegal(game,ax)){
					ans->m[j++]=(mov){px,py,Rx[i]*k,Ry[i]*k};
				}
				else{
					break;
				}
			}
		}
		break;
	case wQUEEN:
	case bQUEEN:
		for(int i=0;i<8;++i){
			for(int k=0;k<8;++k){
				ax=&((mov){px,py,Qx[i]*k,Qy[i]*k});
				if(isLegal(game,ax)){
					ans->m[j++]=(mov){px,py,Qx[i]*k,Qy[i]*k};
				}
				else{
					break;
				}
			}
		}
		break;
	case bPAWN:
		for(int i=0;i<4;++i){
			ax=&((mov){px,py,bPx[i],bPy[i]});
			if(isLegal(game,ax)){
				ans->m[j++]=(mov){px,py,bPx[i],bPy[i]};
			}
		}
		break;
	case wPAWN:
		for(int i=0;i<4;++i){
			ax=&((mov){px,py,wPx[i],wPy[i]});
			if(isLegal(game,ax)){
				ans->m[j++]=(mov){px,py,wPx[i],wPy[i]};
			}
		}
		break;
	default:
		printf("Not a valid piece!\n");
		return NULL;
	}
	ans->m=(mov*)realloc(ans->m,j*sizeof(mov));
	ans->dim=j;
	return ans;
}

int getPieceValue(unsigned piece){
	switch(piece){
		case wKING:
			return 900;
		case bKING:
			return -900;
		case wQUEEN:
			return 90;
		case bQUEEN:
			return -90;
		case wROOK:
			return 50;
		case bROOK:
			return -50;
		case wKNIGHT:
			return 30;
		case bKNIGHT:
			return -30;
		case wBISHOP:
			return 30;
		case bBISHOP:
			return -30;
		case wPAWN:
			return 10;
		case bPAWN:
			return -10;
		default:
			return 0;
	}
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
	#ifdef DEBUG
	printf("\nShouldn't have reached this point in getPieceColor()\nPlease check that the square is not empty!\n");
	exit(1);
	#endif
	return 1;
}

bool validPiece(unsigned piece){
	return piece >= bKING;
}