#ifndef MAIN_GUARD // include main guards
#define MAIN_GUARD

#include "libraries.h"

#define MAX_ARGS 128 // max arguments for a tokenised line
#define MAX_NAME 32 // max number of characters in prompt

char shell_name[MAX_NAME];
char *line;
char tokenArray[MAX_ARGS][MAX_ARGS];

void execute(char* line);

#endif // ending main headers guards