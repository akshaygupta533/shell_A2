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
    if(job<1||job>oj_count){
		printf("Kill %d: Process not found\n", pid);
        return;
    }
	if(oj[job-1].pid != 0)
	{
		pid = oj[job-1].pid;
		int check = kill(pid,signal);
		if(check<0)
		printf("Kill %d: Process not found\n", pid);
		if(check>=0 && signal == 9)
		process_names[pid].status=0;
		if(check>=0 && (signal == 17 ||signal == 18 ||signal == 19 ||signal == 20 ||signal == 23 ||signal == 24))
		process_names[pid].status=2	;
	}else
	{
		perror("Job not found");
	}	

}