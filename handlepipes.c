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
	int i=0;
	while (i < 1024){
		pipe_array[i].command = malloc(sizeof(char)*256);
		i++;
	}
	
	int checker=0;
	int index=0;
	pid_t pid;

	i=0;
	while(i<count)
	{
		if(strcmp(arg[i],"|")!=0)pipe_array[index].command[checker++]=arg[i];
		else
		{
			pipe_array[index].command[checker] = NULL;
			index+=1;
			checker=0;
		}
		i++;
	}

	pipe_array[index].command[checker] = NULL;
	int flag=0;
	i=0;
	while(i<=index)
	{
		if(flag==0) (pipe(fd2));
		else (pipe(fd1));
		
		pid=fork();

		if(pid==0)
		{
			if(!flag)
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

		else if(pid<0)
		{			
			perror("Failed to fork\n");
			return;
		}


		if(flag)
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
		i++;
	}
}