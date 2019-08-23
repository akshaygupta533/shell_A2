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


#endif