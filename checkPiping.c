#include "header.h"

int checkPiping(char ** arg)
{
	int i,j;
	int k=0;
	int length;
	for(i=0; arg[i] != NULL; i++)
	{	
		length=0;
		while(arg[i][length]!='\0')length++;
		for(j=0; j<length ; j++)
		{
			if(arg[i][j]=='|')
				return 1;
		}
	}
	return 0;		
}