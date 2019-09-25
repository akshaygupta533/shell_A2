#include "header.h"

int compare (const void * a, const void * b)
{

  const output_jobs *A = a;
  const output_jobs *B = b;

  return ( B->time - A->time);
}

void generateoj(){
    oj_count=0;
    int i;
    for (i = 0; i < 40000; ++i)
    {
        if(process_names[i].str[0] != '\0' && process_names[i].status!=0)
        {
            oj[oj_count].status = process_names[i].status;
            strcpy(oj[oj_count].str,process_names[i].str);
            oj[oj_count].pid = i;
            oj[oj_count].time = time(NULL) - process_names[i].init;
            oj_count++;
        }
    }
    qsort (oj, oj_count, sizeof(output_jobs), compare);
}