#ifndef HEADER_H_
#define HEADER_H_
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define ANDT_RL_BUFFSIZE 1024

#define ANDT_TOK_BUFFSIZE 64
#define ANDT_DELIMITATORS " \t\r\n\a"

extern char *builtin_str[];
extern int (*builtin_func[])(char **);
void andt_loop();
char *andt_read_line();
char **andt_split_line(char *line);
int andt_launch(char **arg);
int andt_num_builtins();
int andt_execute(char **args);
//builtins	//basic
int andt_cd(char **args);
int andt_help(char **args);
int andt_exit(char **args);
//builtins	//extra
int andt_pwd(char **args);
int andt_clear(char **args);
int andt_echo(char **args);
int andt_ls(char **args);

#endif

