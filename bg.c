#include "header.h"

void bg(char** tokens){
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
    if(process_names[pid].status==2){
        process_names[pid].status = 1;
        kill(oj[job-1].pid,SIGCONT);
        // tcsetpgrp(0, pid);
    }
}