#include <stdio.h>
#include <stdlib.h>
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
#include "header.h"

typedef struct pipe{
	char ** command;
}ola;

ola pipe_array[1024];

void handlePipes(char** arg)
{
	int count=0;
	int fd1[2];
	int fd2[2];
	for (int i = 0; i < 1024; ++i)pipe_array[i].command = malloc(sizeof(char)*256);
	while(arg[count]!=NULL)count++;
	
	int i,checker=0;
	int index=0;
	pid_t pid;

	for(i=0;i<count;i++)
	{
		if(strcmp(arg[i],"|")!=0)pipe_array[index].command[checker++]=arg[i];
		else
		{
			pipe_array[index].command[checker] = NULL;
			index+=1;
			checker=0;
		}
	}
	pipe_array[index].command[checker] = NULL;
	int flag=0;
	for(i=0;i<=index;i++)
	{
		(flag==0)?(pipe(fd2)):(pipe(fd1));
		// for (int j = 0; pipe_array[i].command[j] != NULL; ++j)
		// {
		// 	printf("%d %d.%s\n",i, j ,pipe_array[i].command[j]);
		// }
		pid=fork();

		if(pid<0)
		{			
			perror("Failed to fork\n");
			return;
		}

		if(pid==0)
		{
			if(flag==0)
			{
				if(i!=index) dup2(fd2[1],1);
				
				if(i!=0) dup2(fd1[0],0);
			}
			
			else
			{
				if(i!=index)
				{
					dup2(fd1[1],1);
					dup2(fd2[0],0);
				}
				else
					dup2(fd2[0],0);
			}
			if(execvp(pipe_array[i].command[0],pipe_array[i].command)<0)
				kill(getpid(),SIGTERM);
		}

		if(flag!=0)
		{
			if(i!=index)
			{
				close(fd2[0]);
				close(fd1[1]);
			}
			else
				close(fd2[0]);		
		}
		else
		{
			if(i!=0)
				close(fd1[0]);
			if(i!=index)
				close(fd2[1]);
		}
		flag=!flag;
		waitpid(pid,NULL,0);
	}
}