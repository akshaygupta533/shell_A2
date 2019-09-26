#include "header.h"

void fg(char** tokens){
    int tno=0;
    while(tokens[tno]!=NULL)tno++;
    if(tno!=2){
        perror("Incorrect no. of arguments");
        return;
    }

    generateoj();
    int job = atoi(tokens[1]);
    if(job>oj_count||job<1){
        perror("No job with this no.");
        return;
    }
    pid_t pid = oj[job-1].pid;
    if(process_names[pid].status==2||process_names[pid].status==1){
        signal(SIGCHLD, SIG_IGN);
        signal(SIGINT,ctrl_c);
        signal(SIGTSTP,handle);
        globalPid = pid;
        process_names[pid].status = 1;
        process_names[pid].str[0] = '\0';
        kill(oj[job-1].pid,SIGCONT);
        // tcsetpgrp(0, pid);
        siginfo_t state;
        // waitpid(pid,&state,WUNTRACED);
        waitid(P_PID,pid, &state, (WUNTRACED|WNOWAIT));
    }
    signal(SIGCHLD, SIG_DFL);
    signal(SIGINT,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);

    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(0, getpid());
    signal(SIGTTOU, SIG_DFL);
}