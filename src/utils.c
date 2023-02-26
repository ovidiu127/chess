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