#include "header.h"

void pinfo(char** tokens){
    int tno=0;
        while(tokens[tno]!=NULL){
           tno++;
        }
    int pid;
    if(tno==1){
        pid = getpid();
    }
    else{
        pid=atoi(tokens[1]);
    }
    FILE *stat;
    FILE* exestat;
    char path[1000];
    char exepath[1000];
    strcpy(path,"/proc/");
    char temp[1000];
    sprintf(temp,"%d",pid);
    strcat(path,temp);
    DIR* dir = opendir(path);
    char status;
    char mem[100];
    strcpy(mem,"");
    if(dir){
        strcpy(temp,path);
        strcat(path,"/status");
        printf("pid -- %d\n",pid);
        stat = fopen(path,"r");
        if(!stat){
            perror("FileError");
        }
        char *line;
        size_t len = 0;
        ssize_t read;
        while ( getline(&line, &len, stat) > 0) {
            char **tokens = malloc(sizeof(char)*1000);
            char* str;
            int i=0;
            str = strtok(line," \t\n");
            while(1){
                if(str!=NULL){
                    tokens[i++] = str;
                }
                else{
                    tokens[i] = NULL;
                    break;
                }
                str = strtok(NULL," \t\n");
            }
            if(strcmp(tokens[0],"State:")==0){
                status = tokens[1][0];
            }
            if(strcmp(tokens[0],"VmSize:")==0){
                strcpy(mem,tokens[1]);
            }
        }
        fclose(stat);

        printf("Process Status -- %c\n",status);
        printf("memory -- %s\n",mem);
        strcat(temp,"/exe");
        if (readlink(temp, exepath, sizeof(exepath)) < 0)
            perror("readlink() error");
        else{
            // printf("%s\n",exepath);
            printf("Executable Path -- %s\n",getreldir(exepath,orgdir));
        }

    } 
    else
    {
        printf("No process with pid:%d\n",pid);
    }
    
}