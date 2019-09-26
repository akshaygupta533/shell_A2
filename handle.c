#include "header.h"

void handle(int sig)
{
    if(globalPid!=0){
        kill(globalPid,SIGSTOP);
        strcpy(process_names[globalPid].str,globalProcessName);
        process_names[globalPid].init = time(NULL);
        process_names[globalPid].status = 2;
    }
    globalPid=0;
    return;
}
