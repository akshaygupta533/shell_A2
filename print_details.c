#include "header.h"

void print_details(char * file_path){
    struct stat n_stat;
    if(stat(file_path,&n_stat) < 0){
        return;
    }


    printf( (n_stat.st_mode & __S_IFDIR) ? "d" : "-");
    printf( (n_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (n_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (n_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (n_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (n_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (n_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (n_stat.st_mode & S_IROTH) ? "r" : "-");
    printf( (n_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (n_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf(" ");
    printf("%d ",(int)n_stat.st_nlink);
    printf("%s ", getlogin());
    struct group *group;
    group= getgrgid(n_stat.st_gid);
    printf("%s ", group->gr_name);
    printf("\t%d ",(int)n_stat.st_size);

    time_t now;
    time(&now);
    int year;
    year = localtime(&now)->tm_year;
    struct tm *starttime;
    starttime = localtime(&n_stat.st_ctime);
    char mod[20];
    if(starttime->tm_year == year)
        strftime(mod,20,"%b %e %R",starttime);
    else
        strftime(mod,20,"%b %e %Y",starttime);
    printf("\t%s ",mod );     
}