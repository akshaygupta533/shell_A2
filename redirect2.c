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
#include <fcntl.h>
#include "header.h"

void redirect2(char ** arg)
{
	char *input,*output,*command;
	input = (char *) malloc(sizeof(char)*1024);
	output = (char *) malloc(sizeof(char)*1024);
	command = (char *) malloc(sizeof(char)*1024);

	int i,j,inp=0,out=0,Spout=0;
	pid_t pid = 0;
	if(pid==0)
	{
		for(i=0;arg[i]!=NULL;i++)
		{
			if(arg[i] != NULL && strcmp(arg[i],"<")==0)
			{
				strcpy(input,arg[i+1]);
				arg[i] =  NULL;
				inp=1;
			}
			if(arg[i] != NULL && strcmp(arg[i],">")==0)
			{
				strcpy(output,arg[i+1]);
				arg[i] =  NULL;
				out=1;
			}
			if(arg[i] != NULL && strcmp(arg[i],">>")==0)
			{
				strcpy(output,arg[i+1]);
				arg[i] =  NULL;
				out=1;
				Spout=1;
			}
		}

		if(!inp==0)
		{
			int fd;
			fd=open(input,O_RDONLY,0);
			if (fd<0)
			{
				perror("Could not open input file.");
			}else
			{
				dup2(fd,0);
				close(fd);
			}
		}

		if (!out==0)
		{
			struct stat buffer;
			if(stat(output,&buffer)!=0)
			{
				int fd;
				fd = creat(output,0644);
				if (fd<0)
				{
					perror("Could not create output file");
				}else
				{
					dup2(fd,1);
					close(fd);	
				}
			}
			else
				if(Spout==0)
			{
				int fd;	
				fd = open(output, O_WRONLY);
				if (fd<0)
				{
					perror("Could not open output file");
				}else
				{
					dup2(fd,1);
					close(fd);
				}
			}
			else
				if(Spout==1)
			{
				int fd;	
				fd = open(output, O_WRONLY|O_APPEND);
				if (fd<0)
				{
					perror("Could not open output file");
				}else
				{
					dup2(fd,1);
					close(fd);
				}	
			}
		}
		if (execvp(arg[0],arg) < 0)
		{
			printf("%s: Command doesn't exist.\n", arg[0]);	
		}
	}
	return;
}