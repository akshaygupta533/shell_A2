#include "header.h"


void jobs(char ** arg)
{
	int i;
	generateoj();
	int p=1;
	for(i=0;i<oj_count;i++)
	{
		if(oj[i].status == 1)
			printf("[%d] Running %s[%d]\n",p++,oj[i].str, oj[i].pid);
		else if(oj[i].status == 2)
			printf("[%d] Stopped %s[%d]\n",p++,oj[i].str, oj[i].pid);
	}
}