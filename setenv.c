#include "header.h"

void cmd_setenv(char **tokens){
    int tno=0;
    while(tokens[tno]!=NULL)tno++;
    if(tno!=2 && tno!=3){
        perror("Incorrect no. of arguments");
        return;
    }
    char value[1024];
    if(tno==2)strcpy(value,"\0");
    else strcpy(value,tokens[2]);

    if( setenv(tokens[1],value,1)!=0)
    {
        perror("Cannot set ENV variable");
    }
}