#include "header.h"

void overkill(){
    generateoj();
    int i;
    for (i=0;i<oj_count;i++){
        kill(oj[i].pid,9);
        process_names[oj[i].pid].status=0;
    }
}