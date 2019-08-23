#include "header.h"

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
}