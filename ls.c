#include "header.h"

void ls(char **tokens){

        int tno=0;
        while(tokens[tno]!=NULL){
           tno++;
        }
        char cwd[1000];
        int hidden_flag=0;
        int list_flag=0;
        int i;
        char** lsdirs = malloc(sizeof(char)*1000);
        int dir=0;
        for(i=1;i<tno;i++){
            if( strcmp(tokens[i],"-al")==0 || strcmp(tokens[i],"-a")==0 || strcmp(tokens[i],"-la")==0 )
                hidden_flag=1;

            if( strcmp(tokens[i],"-al")==0 || strcmp(tokens[i],"-l")==0 || strcmp(tokens[i],"-la")==0 )
                list_flag=1;
                
            if( strcmp(tokens[i],"-al")!=0 && strcmp(tokens[i],"-l")!=0 && strcmp(tokens[i],"-la")!=0 && strcmp(tokens[i],"-a")!=0 ){
                lsdirs[dir++]=tokens[i];
            }
                
        }
    int n;

    struct dirent **namelist;
    // printf("%d\n",dir);
    if(dir==0){
        n = scandir(".", &namelist, NULL, alphasort);
        
        if (n < 0)
            perror("scandir");
        else {                        
            while (n--) {
                getcwd(cwd,sizeof(cwd));
                strcat(cwd,"/");
                strcat(cwd,namelist[n]->d_name);
                if(hidden_flag==0 && namelist[n]->d_name[0]!='.'){
                    if(list_flag==1){
                        print_details(cwd);
                        printf("\t%s\n", namelist[n]->d_name);
                    }
                    else{
                        printf("%s\n", namelist[n]->d_name);
                    }
                }
                else if(hidden_flag==1){
                    if(list_flag==1){
                        print_details(cwd);
                    printf("\t%s\n", namelist[n]->d_name);
                    }
                    else{
                    printf("%s\n", namelist[n]->d_name);
                    }
                }
                free(namelist[n]);
            }
            free(namelist);
        }
        return;
    }
    while(dir>0)   
    { //  struct dirent **namelist;
        dir--;
        // printf("%s %d\n",lsdirs[0],dir);

        n = scandir(lsdirs[dir], &namelist, NULL, alphasort);
        
        if (n < 0)
            perror("scandir");
        else {
            chdir(lsdirs[dir]);
            printf("%s:\n",lsdirs[dir]);
            
            while (n--) {
                getcwd(cwd,sizeof(cwd));
                strcat(cwd,"/");
                strcat(cwd,namelist[n]->d_name);
                if(hidden_flag==0 && namelist[n]->d_name[0]!='.'){
                    if(list_flag==1){
                        print_details(cwd);
                    printf("\t%s\n", namelist[n]->d_name);
                    }
                    else{
                    printf("%s\n", namelist[n]->d_name);
                    }
                }
                else if(hidden_flag==1){
                    if(list_flag==1){
                        print_details(cwd);
                    printf("\t%s\n", namelist[n]->d_name);
                    }
                    else{
                    printf("%s\n", namelist[n]->d_name);
                    }
                }
                free(namelist[n]);
            }
            printf("\n");
            free(namelist);
            chdir(dir_before_ls);
        }
        // dir--;
    }
}