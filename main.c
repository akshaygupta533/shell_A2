#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "header.h"


int main(){
    signal(SIGINT,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    globalPid=0;
    char host[100];
    gethostname(host,100);
    char command[300];
    char cwd[1000];
    getcwd(orgdir,sizeof(cwd));
    char **tokens;
    int cno=0;
    char** commands;
    int tno = 0;
    history_commands = malloc(sizeof(char)*1000);
    int i;
    for ( i = 0; i < 20; i++)
    {
        history_commands[i] = NULL;
    }
    int hno;        
    while(1){
        start:
        getcwd(cwd,sizeof(cwd));
        char* reldir = getreldir(cwd,orgdir);
        printf("%s@%s:%s$ ",getlogin(),host,reldir);
        fgets(command,sizeof(command),stdin);
        command[strlen(command)-1] = '\0';
        commands = semicolonsep(command);
        // printf("%s %s\n",commands[0],commands[1]);
        if(commands==NULL)continue;
        hno=0;
        while(history_commands[hno]!=NULL)hno++;
        if(hno==20){
            for(i=0;i<19;i++){
                if(history_commands[i+1]==NULL)continue;
                history_commands[i] = strdup(history_commands[i+1]);
            };
            history_commands[19] = strdup(command);
        }
        else{
            history_commands[hno++] = strdup(command);
        }
        

        
        cno=0;
        while(commands[cno]!=NULL)
        {
            getcwd(cwd,sizeof(cwd));
            // printf("%s\n",cwd);
            char* reldir = getreldir(cwd,orgdir);
            tokens = commandtokenize(commands[cno]);
            tno=0;
            while(tokens[tno]!=NULL)tno++;
            if(tokens==NULL)continue;
      
            if (strcmp("cd",tokens[0])==0){
                changedir(tokens,reldir);
            }
            else if (strcmp("quit",tokens[0])==0){
                overkill();
                return 0;
            }
            else if(strcmp("pwd",tokens[0])==0){
                printf("%s\n",reldir);
            }
            else if(strcmp("echo",tokens[0])==0){
                echofunc(tokens);
            }
            else if(strcmp("ls",tokens[0])==0 && strcmp(tokens[tno-1],"&")!=0){
                strcpy(dir_before_ls,cwd);
                ls(tokens);
            }
            else if(strcmp("pinfo",tokens[0])==0){
                pinfo(tokens);
            }
            else if(strcmp("jobs",tokens[0])==0){
                jobs(tokens);
            }
            else if(strcmp("history",tokens[0])==0){
                historyfunc(tokens);
            }
            else if(strcmp("kjob",tokens[0])==0){
                kjob(tokens);
            }
            else if(strcmp("overkill",tokens[0])==0){
                overkill();
            }
            else if(strcmp("setenv",tokens[0])==0){
                cmd_setenv(tokens);
            }
            else if(strcmp("unsetenv",tokens[0])==0){
                cmd_unsetenv(tokens);
            }
            else if(strcmp("fg",tokens[0])==0){
                fg(tokens);
            }

            else{
                if(strcmp(tokens[tno-1],"&")==0){
                    tokens[--tno]=NULL;
                    exec(tokens,1);
                }
                else{
                    exec(tokens,-1);
                }
            }
            cno++;
        }
    }
    free(history_commands);
    return 0;
}