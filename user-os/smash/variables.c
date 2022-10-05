#include "variables.h"

int varCount = 0;

// create or change data in variable 
void init_var(char *key, char *data){
    // checking there are no variables then reserve memory
    if(varCount == 0){
        varCount++; // incrementing the variable count by 1

        // allocating memory space for one variable
        variables = calloc((size_t)varCount, sizeof(VARIABLE)); 

        // inserting arguments into variable array
        strcpy(variables[varCount-1].key, key);
        strcpy(variables[varCount-1].data, data);

        return;
    }

    // checking if variable exists, if so then rewrite
    for(int i = 0; i < varCount; i++){
        if(strcmp(key, variables[i].key) == 0){ // checking if there is a variable with the same name
            strcpy(variables[i].data, data); // replacing variable data

            return;
        }
    }

    // creating new space for another variable
    variables = realloc(variables, (varCount) * sizeof(VARIABLE));

    // inserting arguments into variable array
    strcpy(variables[varCount-1].key, key);
    strcpy(variables[varCount-1].data, data);

    varCount++;

    return;
}

// initialising shell variables on start up
void init_shell_vars(){
    init_var("PATH", getenv("PATH"));
    init_var("PROMPT", "smash>> ");
    init_var("USER", getenv("USER"));
    init_var("HOME", getenv("HOME"));
    init_var("SHELL", getenv("SHELL")); 
    init_var("EXITCODE", "0");
    get_cwd();
    get_terminal();
}

// returns data from variable array using the key
char *get_value(char *key){
    // iterating through every element in the array
    for(int i = 0; i < varCount; i++){
        // if key is found then return value
        if(strcmp(key, variables[i].key) == 0){
            return variables[i].data;
        }
    }

    printf("\nElement not found in array.");
    return 0;
}

// getting path of cwd using in-built function
void get_cwd(){
    char cwd[CWD_SIZE];
    getcwd(cwd, sizeof(cwd));
    init_var("CWD", cwd);
}

// gets name of terminal using in-built function
void get_terminal(){
    char *ter;
    // gets name of terminal
    ter = ttyname(STDOUT_FILENO); // returns 1
    init_var("TERMINAL", ter);
}

// checks if there is variable declaration in tokens and declares if there is
void var_dec(char *line){
    int equalPos = 0; // index position of equal sign in line
    int len = strlen(line); // length of line
    int equal = '='; 

    // checking if equals is in line
    if(strchr(line, equal) == NULL){
        // if there is no equal then return
        return;
    } else {
        char *afterEqual = strchr(line, equal); // string after and including equal sign

        // stores value of variable without equal sign
        int afterEqualLen = strlen(afterEqual);
        char varValue[afterEqualLen - 1];
        memcpy(varValue, &afterEqual[1], afterEqualLen);

        // stores key of variable
        char *varKey = strtok(line, "=");

        init_var(varKey, varValue);

        return;
    }
}