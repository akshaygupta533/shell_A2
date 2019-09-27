#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>
#include <signal.h>
 #include <dirent.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

char** commandtokenize(char * cmd);
void changedir(char** tokens,char* cwd);
char* getreldir(char* orgdir, char* cwd);
char** semicolonsep(char * cmd);
void echofunc(char **tokens);
void ls(char **tokens);
char orgdir[1000];
char dir_before_ls[1000];
void print_details(char * file_path);
void pinfo(char** tokens);
char** history_commands;
void historyfunc(char **tokens);
void exec(char ** arg,int bg_flag);
void exitprocess(int signum);
void jobs(char ** arg);
void kjob(char ** arg);
pid_t globalPid;
char globalProcessName[1024];
int globalProcessFlag;
void generateoj();
void overkill();
void cmd_setenv(char **tokens);
void cmd_unsetenv(char **tokens);
void fg(char** tokens);
void bg(char** tokens);
int parent_flag;
void ctrl_c(int status);
void handle(int sig);
void redirect(char ** arg);
void redirect2(char ** arg);
void handlePipesandRedirection(char** arg);
void handlePipes(char** arg);
int checkRedirect(char ** arg);
int checkPiping(char ** arg);

typedef struct pro{
	int index;
	char str[1024];
	int status;
	time_t init;
}proc_names;

proc_names process_names[40000];

typedef struct jobs{
	int status;
	char str[1024];
	pid_t pid;
	int time;
}output_jobs;

output_jobs oj[1024];
int oj_count;

#endif