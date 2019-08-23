#include "header.h"

void echofunc(char **tokens){
    char strr[1000]="";
    int i=1;
    while(tokens[i]!=NULL){
        if(i!=1)
            strcat(strr," ");
        strcat(strr,tokens[i]);
        i++;
    }
    printf("%s\n",strr);
}