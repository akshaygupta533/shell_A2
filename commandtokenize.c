#include "header.h"

char** commandtokenize(char * cmd){
    if(cmd[0]=='\0')
        return NULL;
    char **tokens = malloc(sizeof(char)*1000);
    char* str;
    int i=0;
    str = strtok(cmd," \t\n");
    while(1){
        if(str!=NULL){
            tokens[i++] = str;
        }
        else{
            tokens[i] = NULL;
            return tokens;
        }
        str = strtok(NULL," \t\n");
    }
}