#include "header.h"

char** semicolonsep(char * cmd){
    if(cmd[0]=='\0')
        return NULL;
    char **commands = malloc(sizeof(char)*1000);
    char* str;
    int i=0;
    str = strtok(cmd,";");
    while(1){
        if(str!=NULL){
            commands[i++] = str;
        }
        else{
            commands[i] = NULL;
            return commands;
        }
        str = strtok(NULL,";");
    }
}