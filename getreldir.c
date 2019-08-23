#include "header.h"

char* getreldir(char* cwd,char* orgdir){
    int leno = strlen(orgdir);
    char* final = malloc(sizeof(char)*100);
    int lenc = strlen(cwd);
    if(lenc<leno){
        strcpy(final,cwd);
        return final;
    }
    int i;
    for(i=0;i<lenc-leno;i++){
        cwd[i] = cwd[i+leno];
    } 
    cwd[i] = '\0';
    strcpy(final,"~");
    strcat(final,cwd);
    return final;
}