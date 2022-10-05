#ifndef VAR_GUARD // include guards
#define VAR_GUARD

#include "libraries.h"

#define VAR_SIZE 2048 // largest value for variable key and data
#define CWD_SIZE 128

void init_var(char *key, char *data);
void init_shell_vars();
char *get_value(char *name);
void get_cwd();
void get_terminal();
void var_dec(char *line);
void print_vars();

// variable struct with attributes
typedef struct variable{
    char key[VAR_SIZE];
    char data[VAR_SIZE];
} VARIABLE;

VARIABLE *variables; // creating an array of variable struct
int varCount; // number of variables in session

#endif // ending variable headers guards