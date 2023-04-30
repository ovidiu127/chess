#include "utils.h"

void avoidSpaces(){
	char c=getchar();
	while(isspace(c)){
		c=getchar();
	}
	ungetc(c,stdin);
}

void toLower(char *s){
	while(*s){
		if(*s>='A'&&*s<='Z'){
			*s+=32;
		}
		++s;
	}
}

bool inBounds(int x,int y){
	return (x>=1 && x<=8 && y>=1 && y<=8);
}

void printbin(uint64_t n){
	for(int i=sizeof(n)*8-1;i>=0;--i){
		if((i+1)%8==0){
			putchar('\n');
		}
		putchar(n&(((uint64_t)1)<<i)?'1':'0');
	}
	putchar('\n');
}