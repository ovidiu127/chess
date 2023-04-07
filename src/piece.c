#include "piece.h"

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
const int bPx[]={1,-1,0,0};
const int bPy[]={-1,-1,-1,-2};
const int wPx[]={1,-1,0,0};
const int wPy[]={1,1,1,2};

void updateCoverage(position *game){
	int x,y;

	game->coverage[game->toMove]=0;
	for(int i=1;i<=8;++i){
		for(int j=1;j<=8;++j){
			if(!validPiece(game->board[j][i])){
				continue;
			}
			if(getPieceColor(game->board[j][i])!=game->toMove){
				continue;
			}
			switch(game->board[j][i]){
			case wKING:
			case bKING:
				for(int k=0;k<8;++k){
					x=i+Kx[k], y=j+Ky[k];
					if(inBounds(x,y)){
						setBit(game->coverage[game->toMove],(j+Ky[k]-1)*8+(i+Kx[k])-1,uint64_t);
						#ifdef DEBUG
						printf("%lc %c %d %c %d bit:%d\n",game->board[j][i],i+'a'-1,j,i+Kx[k]+'a'-1,j+Ky[k],(j+Ky[k]-1)*8+(i+Kx[k])-1);
						printbin(game->coverage[game->toMove]);
						#endif
					}
				}
				break;
			case wKNIGHT:
			case bKNIGHT:
				for(int k=0;k<8;++k){
					x=i+Nx[k], y=j+Ny[k];
					if(inBounds(x,y)){
						setBit(game->coverage[game->toMove],(j+Ny[k]-1)*8+(i+Nx[k])-1,uint64_t);
						#ifdef DEBUG
						printf("%lc %c %d %c %d bit:%d\n",game->board[j][i],i+'a'-1,j,i+Nx[k]+'a'-1,j+Ny[k],(j+Ny[k]-1)*8+(i+Nx[k])-1);
						printbin(game->coverage[game->toMove]);
						#endif
					}
				}
				break;
			case wBISHOP:
			case bBISHOP:
				for(int l=0;l<4;++l){
					for(int k=1;k<8;++k){
						x=i+Bx[l]*k, y=j+By[l]*k;
						if(inBounds(x,y)){
							setBit(game->coverage[game->toMove],(j+By[l]*k-1)*8+(i+Bx[l]*k-1),uint64_t);
							#ifdef DEBUG
							printf("%lc %c %d %c %d bit:%d\n",game->board[j][i],i+'a'-1,j,i+Bx[l]*k+'a'-1,j+By[l]*k,(j+By[l]*k-1)*8+(i+Bx[l]*k-1));
							printbin(game->coverage[game->toMove]);
							#endif
							if(game->board[y][x]>=bKING){
								break;
							}
						}
						else{
							break;
						}
					}
				}
				break;
			case wROOK:
			case bROOK:
				for(int l=0;l<4;++l){
					for(int k=1;k<8;++k){
						x=i+Rx[l]*k, y=j+Ry[l]*k;
						if(inBounds(x,y)){
							setBit(game->coverage[game->toMove],(j+Ry[l]*k-1)*8+(i+Rx[l]*k-1),uint64_t);
							#ifdef DEBUG
							printf("%lc %c %d %c %d bit:%d\n",game->board[j][i],i+'a'-1,j,i+Rx[l]*k+'a'-1,j+Ry[l]*k,(j+Ry[l]*k-1)*8+(i+Rx[l]*k-1));
							printbin(game->coverage[game->toMove]);
							#endif
							if(game->board[y][x]>=bKING){
								break;
							}
						}
						else{
							break;
						}
					}
				}
				break;
			case wQUEEN:
			case bQUEEN:
				for(int l=0;l<8;++l){
					for(int k=1;k<8;++k){
						x=i+Qx[l]*k, y=j+Qy[l]*k;
						if(inBounds(x,y)){
							setBit(game->coverage[game->toMove],(j+Qy[l]*k-1)*8+(i+Qx[l]*k-1),uint64_t);
							#ifdef DEBUG
							printf("%lc %c %d %c %d bit:%d\n",game->board[j][i],i+'a'-1,j,i+Qx[l]*k+'a'-1,j+Qy[l]*k,(j+Qy[l]*k-1)*8+(i+Qx[l]*k-1));
							printbin(game->coverage[game->toMove]);
							#endif
							if(game->board[y][x]>=bKING){
								break;
							}
						}
						else{
							break;
						}
					}
				}
				break;
			case bPAWN:
				for(int k=0;k<2;++k){
					x=i+bPx[k], y=j+bPy[k];
					if(inBounds(x,y)){
						setBit(game->coverage[game->toMove],(j+bPy[k]-1)*8+(i+bPx[k]-1),uint64_t);
						#ifdef DEBUG
						printf("%lc %c %d %c %d bit:%d\n",game->board[j][i],i+'a'-1,j,i+bPx[k]+'a'-1,j+bPy[k],(j+bPy[k]-1)*8+(i+bPx[k]-1));
						printbin(game->coverage[game->toMove]);
						#endif
					}
				}
				break;
			case wPAWN:
				for(int k=0;k<2;++k){
					x=i+wPx[k], y=j+wPy[k];
					if(inBounds(x,y)){
						setBit(game->coverage[game->toMove],(j+wPy[k]-1)*8+(i+wPx[k]-1),uint64_t);
						#ifdef DEBUG
						printf("%lc %c %d %c %d bit:%d\n",game->board[j][i],i+'a'-1,j,i+wPx[k]+'a'-1,j+wPy[k],(j+wPy[k]-1)*8+(i+wPx[k]-1));
						printbin(game->coverage[game->toMove]);
						#endif
					}
				}
				break;
			#ifdef DEBUG
			default:
				printf("Not a valid piece!%s:%d\n",__FILE__,__LINE__);
				exit(1);
			#endif
			}
		}
	}
}

moves* getMoves(position *game,int px,int py){
	int j=0;
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

	switch(game->board[py][px]){
	case wKING:
	case bKING:
		for(int i=0;i<8;++i){
			if(isLegal(game,&((mov){px,py,Kx[i],Ky[i]}))){
				ans->m[j++]=(mov){Kx[i],Ky[i]};
			}
		}
		break;
	case wKNIGHT:
	case bKNIGHT:
		for(int i=0;i<8;++i){
			if(isLegal(game,&((mov){px,py,Nx[i],Ny[i]}))){
				ans->m[j++]=(mov){px,py,Nx[i],Ny[i]};
			}
		}
		break;
	case wBISHOP:
	case bBISHOP:
		for(int i=0;i<4;++i){
			for(int k=1;k<8;++k){
				if(isLegal(game,&((mov){px,py,Bx[i]*k,By[i]*k}))){
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
			for(int k=1;k<8;++k){
				if(isLegal(game,&((mov){px,py,Rx[i]*k,Ry[i]*k}))){
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
			for(int k=1;k<8;++k){
				if(isLegal(game,&((mov){px,py,Qx[i]*k,Qy[i]*k}))){
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
			if(isLegal(game,&((mov){px,py,bPx[i],bPy[i]}))){
				ans->m[j++]=(mov){px,py,bPx[i],bPy[i]};
			}
		}
		break;
	case wPAWN:
		for(int i=0;i<4;++i){
			if(isLegal(game,&((mov){px,py,wPx[i],wPy[i]}))){
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