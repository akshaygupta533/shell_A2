#include "header.h"

void changedir(char** tokens,char* reldir){
    // printf("%s",dir);
    int tno = 0;
    while(tokens[tno]!=NULL)tno++;
    if(tno>2){
        printf("bash: cd: too many arguments\n");
        return;
    }
    if(tno==1){
        chdir(orgdir);
        return;
    }
    if(strcmp(tokens[1],"~")==0){
        chdir(orgdir);
        return;
    }
    if(chdir(tokens[1])!=0)
        printf("No such directory!\n");
}