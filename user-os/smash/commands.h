#ifndef COMMANDS_GUARD // include guards
#define COMMANDS_GUARD

#include "main.h"

#define MAX_STACK_CAP 128

// struct for directory stack
typedef struct dirStack{
    char dir[MAX_STACK_CAP];
} DIRSTACK;

// array of directory struct 
DIRSTACK *directories;

void check_exit(char *line);
void echo(char tokenArray[MAX_ARGS][MAX_ARGS]);
void change_dir(char tokenArray[MAX_ARGS][MAX_ARGS]);
void show_var(char tokenArray[MAX_ARGS][MAX_ARGS]);
void export_var(char tokenArray[MAX_ARGS][MAX_ARGS]);
void show_env_vars(char tokenArray[MAX_ARGS][MAX_ARGS]);
void unset_var(char tokenArray[MAX_ARGS][MAX_ARGS]);
void init_stack(int cap);
void pushd(char tokenArray[MAX_ARGS][MAX_ARGS]);
void popd(char* line);
void print_stack(char* line);
void show_pwd(char *line);
void source(char tokenArray[MAX_ARGS][MAX_ARGS]);

extern char **environ;

#endif // ending command headers guards