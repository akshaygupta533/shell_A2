#include "header.h"

int fl;

void handle(int sig)
{
    fl=1;
    kill(globalPid,SIGSTOP);
    strcpy(process_names[globalPid].str,globalProcessName);
    process_names[globalPid].init = time(NULL);
    process_names[globalPid].status = 2;
    globalPid=0;
}

void exec(char ** arg,int bg_flag)
{
    fl=0;
    globalProcessFlag=0;
	int i,background=bg_flag;
    int red=0,piping=0;
    // red=checkRedirect(arg);
    // piping=checkPiping(arg);

    // if(piping && red)
    // {
    //     handlePipesandRedirection(arg);
    //     return;
    // }

    // if(piping)
    // {
    //     handlePipes(arg);
    //     return;
    // }

    // if(red)
    // {
    //     redirect(arg);
    //     return;
    // }

	pid_t pid, wpid;
    int state;

    pid = fork();
    globalPid = pid;
    strcpy(globalProcessName,arg[0]);
    signal(SIGTSTP,handle);
    signal(SIGCHLD, exitprocess);

    if (background==1 && pid!=0){
        generateoj();
        printf("[%d] %d\n",oj_count+1,pid);
    }
    // if(background==-1)
    //     signal(SIGINT,SIG_DFL);

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
    if(background==-1 && fl==0)
    {
        wpid = waitpid(pid, &state, WUNTRACED);
    }
    // printf("%d\n", pid);
    if(background != -1)
    {
        strcpy(process_names[pid].str,arg[0]);
        process_names[pid].status = 1;
        process_names[pid].init = time(NULL);
    }
    // printf("%s\n", process_names[pid].str);
}