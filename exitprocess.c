#include "header.h"

void exitprocess(int signum){
    pid_t proc_id = wait(NULL);
    if(proc_id>0){
        printf("\nProcess with id %d exited normally with status %d\n",proc_id,signum);
    }
}