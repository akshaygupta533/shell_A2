#include "header.h"

void kjob(char ** arg)
{
	int tno=0;
    while(arg[tno]!=NULL)tno++;
    // printf("%d\n",tno);
    if(tno<=2){
        printf("Error: Incorrect Arguments\n");
		return;
    }
	int job = atoi(arg[1]);
	int signal = atoi(arg[2]);
	generateoj();
	pid_t pid;
	pid = oj[job-1].pid;
    if(job<1||job>oj_count){
		printf("Kill %d: Process not found\n", oj[job-1].pid);
        return;
    }
	if(oj[job-1].pid != 0)
	{
		if(signal==20){
			signal=19;
		}
		// printf("%d %d",pid,signal);
		kill(pid,signal);
		if (signal == 9)
			process_names[pid].status=0;
		else if( signal>=17 && signal<=24 && signal!=21 && signal!=22){
			process_names[pid].status=2;
		}
	}
	else
	{
		perror("Job not found");
	}	

}