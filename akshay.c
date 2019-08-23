#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>
#include <signal.h>
 #include <dirent.h>
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

char** commandtokenize(char * cmd);
void changedir(char** tokens,char* cwd);
char* getreldir(char* orgdir, char* cwd);
char** semicolonsep(char * cmd);
void echofunc(char **tokens);
void ls(char **tokens);
char orgdir[1000];
char dir_before_ls[1000];
void print_details(char * file_path);
void pinfo(char** tokens);
char** history_commands;
void historyfunc(char **tokens);
void exec(char ** arg,int bg_flag);
void exitprocess(int signum);


#endif#include <stdio.h>
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

void ctrl_c(int status){
    return;
}

int main(){
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
    signal(SIGINT,ctrl_c);
    
    
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
            else if (strcmp("exit",tokens[0])==0){
                return 0;
            }
            else if(strcmp("pwd",tokens[0])==0){
                printf("%s\n",reldir);
            }
            else if(strcmp("echo",tokens[0])==0){
                echofunc(tokens);
            }
            else if(strcmp("ls",tokens[0])==0){
                strcpy(dir_before_ls,cwd);
                ls(tokens);
            }
            else if(strcmp("pinfo",tokens[0])==0){
                pinfo(tokens);
            }
            else if(strcmp("history",tokens[0])==0){
                historyfunc(tokens);
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
}#include "header.h"

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
}#include "header.h"

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
}#include "header.h"

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
}#include "header.h"

void exec(char ** arg,int bg_flag)
{
	pid_t pid, wpid;
    int state;
    pid = fork();
    signal(SIGCHLD, exitprocess);
    int flag=0;
    if (pid < 0) {
    	perror("ERROR");
    	flag=1;
    }
    else if(pid==0) 
    {
    	int x = execvp(arg[0], arg);
        if(x < 0)
        {
            perror("ERROR");
        	flag=1;
        }
        exit(0);
    }
    if(bg_flag==-1)
    {
        wpid = waitpid (pid, &state, WUNTRACED);
		while(1)
		{
        	if(!WIFEXITED(state) && !WIFSIGNALED(state)) 
           		wpid = waitpid (pid, &state, WUNTRACED);
        	else
        		break;
        }
    }
    else{
        printf("%d\n",pid);
    }
    // printf("%d\n", pid);
    // strcpy(process_names[pid].str,arg[0]);
    // printf("%s\n", process_names[pid].str);
}#include "header.h"

void exitprocess(int signum){
    pid_t proc_id = wait(NULL);
    if(proc_id>0){
        printf("Process with id %d exited normally with status %d\n",proc_id,signum);
    }
}#include "header.h"

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
}#include "header.h"

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
    
}#include "header.h"

void ls(char **tokens){

        int tno=0;
        while(tokens[tno]!=NULL){
           tno++;
        }
        char cwd[1000];
        int hidden_flag=0;
        int list_flag=0;
        int i;
        char** lsdirs = malloc(sizeof(char)*1000);
        int dir=0;
        for(i=1;i<tno;i++){
            if( strcmp(tokens[i],"-al")==0 || strcmp(tokens[i],"-a")==0 || strcmp(tokens[i],"-la")==0 )
                hidden_flag=1;

            if( strcmp(tokens[i],"-al")==0 || strcmp(tokens[i],"-l")==0 || strcmp(tokens[i],"-la")==0 )
                list_flag=1;
                
            if( strcmp(tokens[i],"-al")!=0 && strcmp(tokens[i],"-l")!=0 && strcmp(tokens[i],"-la")!=0 && strcmp(tokens[i],"-a")!=0 ){
                lsdirs[dir++]=tokens[i];
            }
                
        }
    int n;

    struct dirent **namelist;
    // printf("%d\n",dir);
    if(dir==0){
        n = scandir(".", &namelist, NULL, alphasort);
        
        if (n < 0)
            perror("scandir");
        else {                        
            while (n--) {
                getcwd(cwd,sizeof(cwd));
                strcat(cwd,"/");
                strcat(cwd,namelist[n]->d_name);
                if(hidden_flag==0 && namelist[n]->d_name[0]!='.'){
                    if(list_flag==1){
                        print_details(cwd);
                        printf("\t%s\n", namelist[n]->d_name);
                    }
                    else{
                        printf("%s\n", namelist[n]->d_name);
                    }
                }
                else if(hidden_flag==1){
                    if(list_flag==1){
                        print_details(cwd);
                    printf("\t%s\n", namelist[n]->d_name);
                    }
                    else{
                    printf("%s\n", namelist[n]->d_name);
                    }
                }
                free(namelist[n]);
            }
            free(namelist);
        }
        return;
    }
    while(dir>0)   
    { //  struct dirent **namelist;
        dir--;
        // printf("%s %d\n",lsdirs[0],dir);

        n = scandir(lsdirs[dir], &namelist, NULL, alphasort);
        
        if (n < 0)
            perror("scandir");
        else {
            chdir(lsdirs[dir]);
            printf("%s:\n",lsdirs[dir]);
            
            while (n--) {
                getcwd(cwd,sizeof(cwd));
                strcat(cwd,"/");
                strcat(cwd,namelist[n]->d_name);
                if(hidden_flag==0 && namelist[n]->d_name[0]!='.'){
                    if(list_flag==1){
                        print_details(cwd);
                    printf("\t%s\n", namelist[n]->d_name);
                    }
                    else{
                    printf("%s\n", namelist[n]->d_name);
                    }
                }
                else if(hidden_flag==1){
                    if(list_flag==1){
                        print_details(cwd);
                    printf("\t%s\n", namelist[n]->d_name);
                    }
                    else{
                    printf("%s\n", namelist[n]->d_name);
                    }
                }
                free(namelist[n]);
            }
            printf("\n");
            free(namelist);
            chdir(dir_before_ls);
        }
        // dir--;
    }
}#include <stdio.h>
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

void ctrl_c(int status){
    return;
}

int main(){
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
    signal(SIGINT,ctrl_c);
    
    
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
            else if (strcmp("exit",tokens[0])==0){
                return 0;
            }
            else if(strcmp("pwd",tokens[0])==0){
                printf("%s\n",reldir);
            }
            else if(strcmp("echo",tokens[0])==0){
                echofunc(tokens);
            }
            else if(strcmp("ls",tokens[0])==0){
                strcpy(dir_before_ls,cwd);
                ls(tokens);
            }
            else if(strcmp("pinfo",tokens[0])==0){
                pinfo(tokens);
            }
            else if(strcmp("history",tokens[0])==0){
                historyfunc(tokens);
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
}#include "header.h"

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
    
}#include "header.h"

void print_details(char * file_path){
    struct stat n_stat;
    if(stat(file_path,&n_stat) < 0){
        return;
    }


    printf( (n_stat.st_mode & __S_IFDIR) ? "d" : "-");
    printf( (n_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (n_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (n_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (n_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (n_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (n_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (n_stat.st_mode & S_IROTH) ? "r" : "-");
    printf( (n_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (n_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf(" ");
    printf("%d ",(int)n_stat.st_nlink);
    printf("%s ", getlogin());
    struct group *group;
    group= getgrgid(n_stat.st_gid);
    printf("%s ", group->gr_name);
    printf("\t%d ",(int)n_stat.st_size);

    time_t now;
    time(&now);
    int year;
    year = localtime(&now)->tm_year;
    struct tm *starttime;
    starttime = localtime(&n_stat.st_ctime);
    char mod[20];
    if(starttime->tm_year == year)
        strftime(mod,20,"%b %e %R",starttime);
    else
        strftime(mod,20,"%b %e %Y",starttime);
    printf("\t%s ",mod );     
}#include "header.h"

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