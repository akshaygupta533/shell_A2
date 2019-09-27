#include "header.h"

int fl;



void exec(char ** arg,int bg_flag)
{
    globalProcessFlag=0;
	int i,background=bg_flag;
    int red=0,piping=0;
    red=checkRedirect(arg);
    piping=checkPiping(arg);

    if(piping && !red)
    {
        handlePipes(arg);
        return;
    }
    else if(piping && red)
    {
        handlePipesandRedirection(arg);
        return;
    }
    else if(red && !piping)
    {
        redirect(arg);
        return;
    }

	pid_t pid, wpid;
    int state;

    pid = fork();  

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
    else{
        signal(SIGINT,SIG_IGN);
        

        strcpy(globalProcessName,arg[0]);

        if(background==-1 ){
            signal(SIGCHLD, SIG_IGN);
            signal(SIGINT,ctrl_c);
            signal(SIGTSTP,handle);
            globalPid = pid;
            siginfo_t status;
            waitid(P_PID,pid, &status, (WUNTRACED|WNOWAIT));
            
        }
        // printf("%d\n", pid);
        else{
            signal(SIGCHLD, exitprocess);
            signal(SIGINT,SIG_IGN);
            signal(SIGTSTP,SIG_IGN);

            generateoj();
            printf("[%d] %d\n",oj_count+1,pid);
            globalPid=0;
        
            strcpy(process_names[pid].str,arg[0]);
            process_names[pid].status = 1;
            process_names[pid].init = time(NULL);
        }
    }
    // printf("%s\n", process_names[pid].str);
    signal(SIGINT,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGCHLD,SIG_DFL);

}