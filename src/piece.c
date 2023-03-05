#include "piece.h"

piece pieces[32];

bool isValid(mov *m){
    int x=m->p->x+m->x, y=m->p->y+m->y;
    if(x<1 || x>8 || y<1 || y>8){
        return false;
    }
    int c[]={m->p->x,m->p->y,x,y};
	#ifdef DEBUG
	printf("check %c:%d -> %c:%d legal:%d\n",c[0]+'a'-1,c[1],c[2]+'a'-1,c[3],isLegal(c));
	#endif
    return isLegal(c);
}

//generates only knight moves
moves* getMoves(piece *p){
	int j;
	mov *ax;
	moves* ans=(moves*)malloc(sizeof(moves));
	switch(p->type){
	case wKNIGHT:
	case bKNIGHT:
		ans->m=(mov*)malloc(8*sizeof(mov));
		if(!ans){
			printf("Malloc failed!\n%s:%d\n",__FILE__,__LINE__);
			assert(0);
		}
		j=0;
		int Nx[]={-2,-2,-1,-1,1,1,2,2};
		int Ny[]={-1,1,-2,2,-2,2,-1,1};
		for(int i=0;i<8;++i){
			ax=&((mov){Nx[i],Ny[i],p});
			if(isValid(ax)){
				ans->m[j++]=(mov){Nx[i],Ny[i],p};
			}
		}
		ans->m=(mov*)realloc(ans->m,j*sizeof(mov));
		ans->dim=j;
		break;
	case wBISHOP:
	case bBISHOP:
		ans->m=(mov*)malloc(8*sizeof(mov));
		if(!ans){
			printf("Malloc failed!\n%s:%d\n",__FILE__,__LINE__);
			assert(0);
		}
		j=0;
		int Bx[]={1,1,-1,-1};
		int By[]={1,-1,-1,1};
		for(int i=0;i<4;++i){
			for(int k=0;k<8;++k){
				ax=&((mov){Bx[i]*k,By[i]*k,p});
				if(isValid(ax)){
					ans->m[j++]=(mov){Nx[i]*k,Ny[i]*k,p};
				}
				else{
					break;
				}
			}
		}
		ans->m=(mov*)realloc(ans->m,j*sizeof(mov));
		ans->dim=j;
		break;
	case bPAWN:
		ans->m=(mov*)malloc(3*sizeof(mov));
		if(!ans){
			printf("Malloc failed!\n%s:%d\n",__FILE__,__LINE__);
			assert(0);
		}
		j=0;
		int bPx[]={1,0,-1,0};
		int bPy[]={-1,-1,-1,-2};
		for(int i=0;i<4;++i){
			ax=&((mov){bPx[i],bPy[i],p});
			if(isValid(ax)){
				ans->m[j++]=(mov){bPx[i],bPy[i],p};
			}
		}
		ans->m=(mov*)realloc(ans->m,j*sizeof(mov));
		ans->dim=j;
		break;
	case wPAWN:
		ans->m=(mov*)malloc(3*sizeof(mov));
		if(!ans){
			printf("Malloc failed!\n%s:%d\n",__FILE__,__LINE__);
			assert(0);
		}
		j=0;
		int wPx[]={1,0,-1,0};
		int wPy[]={1,1,1,2};
		for(int i=0;i<4;++i){
			ax=&((mov){wPx[i],wPy[i],p});
			if(isValid(ax)){
				ans->m[j++]=(mov){wPx[i],wPy[i],p};
			}
		}
		ans->m=(mov*)realloc(ans->m,j*sizeof(mov));
		ans->dim=j;
		break;
	default:
		printf("Not a valid piece!\n");
		return NULL;
	}
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