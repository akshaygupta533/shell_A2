#include "header.h"
void ctrl_c(int status){
    // printf("%d",globalPid);
    if(globalPid!=0){
        kill(globalPid,9);
        strcpy(process_names[globalPid].str,globalProcessName);
        process_names[globalPid].init = time(NULL);
        process_names[globalPid].status = 0;
    }
    globalPid=0;
    write(STDIN_FILENO,"\n",1);
    return;
}
