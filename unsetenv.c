#include "header.h"

void cmd_unsetenv(char **tokens){
    int tno=0;
    while(tokens[tno]!=NULL)tno++;
    if(tno!=2){
        perror("Incorrect no. of arguments");
    }

    if( unsetenv(tokens[1])!=0)
    {
        perror("Cannot unset ENV variable");
    }
}