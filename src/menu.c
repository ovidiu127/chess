#include "menu.h"

char menu(const char *text,const char *options){
    char ans,ok = 0;
    printf("%s",text);
    putchar('[');
    for(int i=0;options[i] != 0;++i){
        printf("%c/",options[i]);
    }
    printf("\b] ");
    fflush(stdout);

    while(1){
        avoidSpaces(stdin);
        scanf("%c",&ans);
        if(strchr(options,ans)){
            ok = 1;
        }
        if(!ok){
            printf("Invalid option!\n");
            putchar('[');
            for(int i=0;options[i] != 0;++i){
                printf("%c/",options[i]);
            }
            printf("\b] ");
            fflush(stdout);
        }
        else{
            break;
        }
    }
    
    return ans;
}