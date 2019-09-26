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

int checkRedirect(char ** arg)
{
	int i,j;
	int k=0;
	for(i=0; arg[i] != NULL; i++)
	{	
		for(j=0; arg[i][j] != '\0' ; j++)
		{
			if(arg[i][j]=='>' || arg[i][j]=='<' || arg[i][j+1]=='>')
				return 1;
		}
	}
	return 0;		
}