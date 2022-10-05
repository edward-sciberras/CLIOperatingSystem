#ifndef REDIRECTION_GUARD // include main guards
#define REDIRECTION_GUARD

#include "libraries.h"
#include "main.h"

char lhs_red[MAX_ARGS], rhs_red[MAX_ARGS];

pid_t pid;

void split_args(char tokenArray[MAX_ARGS][MAX_ARGS], char* lhs, char* rhs, char *c);
int check_redirection(char* line);
void execute_redirection(char tokenArray[MAX_ARGS][MAX_ARGS], int operationNum);

#endif // ending redirection headers guards