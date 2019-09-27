
#include "header.h"

void redirect(char ** arg)
{
	char *input;
	input = (char *) malloc(sizeof(char)*1024);
	char* output;
	output = (char *) malloc(sizeof(char)*1024);
	char* command;
	command = (char *) malloc(sizeof(char)*1024);

	int i,j;
	int inp=0;
	int out=0;
	int Spout=0;
	pid_t pid = fork();
	if(pid==0)
	{
		i=0;
		while(arg[i]!=NULL)
		{
			if(arg[i] != NULL && strcmp(arg[i],"<")==0)
			{
				strcpy(input,arg[i+1]);
				arg[i] =  NULL;
				inp=1;
			}
			else if(arg[i] != NULL && strcmp(arg[i],">")==0)
			{
				strcpy(output,arg[i+1]);
				arg[i] =  NULL;
				out=1;
			}
			else if(arg[i] != NULL && strcmp(arg[i],">>")==0)
			{
				strcpy(output,arg[i+1]);
				arg[i] =  NULL;
				out=1;
				Spout=1;
			}
			i++;
		}

		if(inp)
		{
			int fd = open(input,O_RDONLY,0);
			if (fd<0)
			{
				perror("Could not open input file.");
			}else
			{
				dup2(fd,0);
				close(fd);
			}
		}

		if (out)
		{
			struct stat buffer;
			int fd;
			if(stat(output,&buffer)!=0)
			{
				fd = creat(output,0644);
			}
			else if(!Spout)
			{
				fd = open(output, O_WRONLY);
			}
			else if(Spout)
			{
				fd = open(output,  O_WRONLY | O_APPEND | O_CREAT, (S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR));	
			}
			if (fd<0)
				{
					perror("Could not open output file");
				}else
				{
					dup2(fd,1);
					close(fd);
				}
		}
		if (execvp(arg[0],arg) < 0)
		{
			printf("%s: Command doesn't exist.\n", arg[0]);	
		}
	}else
	{
		wait(NULL);
	}
	return;
}