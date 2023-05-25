#include "menu.h"

char menu(const char *text,const char *options){
    char ans[4];
    printf("%s",text);
    putchar('[');
    for(int i=0;options[i] != 0;++i){
        printf("%c/",options[i]);
    }
    printf("\b] ");
    fflush(stdout);

    while(1){
        avoidSpaces(stdin);
        fgets(ans,3,stdin);
        if(ans[1] == '\n' || ans[1] == 10){
            if(strchr(options,ans[0])){
                break;
            }
            else{
                printf("Invalid option!\n");
                putchar('[');
                for(int i=0;options[i] != 0;++i){
                    printf("%c/",options[i]);
                }
                printf("\b] ");
                fflush(stdout);
            }
        }
        else{
            skipLine(stdin);
            printf("Incorrect input!\n");
            putchar('[');
            for(int i=0;options[i] != 0;++i){
                printf("%c/",options[i]);
            }
            printf("\b] ");
            fflush(stdout);
        }
    }
    
    return ans[0];
}