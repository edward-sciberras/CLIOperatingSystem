#ifndef PIPE_GUARD // include main guards
#define PIPE_GUARD

#include "libraries.h"
#include "main.h"

pid_t pid1, pid2;

char lhs[MAX_ARGS], rhs[MAX_ARGS];

int fd[2];

int check_pipe(char* line);
void execute_pipe(char tokenArray[MAX_ARGS][MAX_ARGS]);

#endif // ending piping headers guards