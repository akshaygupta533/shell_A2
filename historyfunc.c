#include "header.h"

void historyfunc(char **tokens){
    int n;
    if(tokens[1]!=NULL){
        n=atoi(tokens[1]);
        if(n>10)n=10;
    }
    else{
        n=10;
    }
    int i;
    int hno=0;
    while(history_commands[hno]!=NULL)hno++;
    if(hno-1-n<0){
        i=0;
    }
    else{
        i = hno-n;
    }
    while( i<hno)
    {
        printf("%s\n",history_commands[i]);
        i++;
    }
    
}