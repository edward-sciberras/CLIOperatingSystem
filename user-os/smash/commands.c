#include "commands.h"
#include "variables.h"
#include "main.h"

int stacksize = 0; // keeps track of size of directory stack

// used to exit shell
void check_exit(char *line){
    // checking if user inputted exit
    if(line != NULL && strcmp(line, "exit") == 0){
        // exit program
        printf("\n\nExiting.\n");
        exit(EXIT_SUCCESS);
    } else {
        return;
    }
}

// used to echo variables and text
void echo(char tokenArray[MAX_ARGS][MAX_ARGS]){
    // checking if user inputted echo
    if(strcmp(tokenArray[0], "echo") == 0){
        for(int i = 1; tokenArray[i][0] != '\0'; i++){
            // if the first character is a dollar sign
            if(tokenArray[i][0] == 36){ // ascii value for $
                // getting string without dollar sign and printing value
                char *noDollarSign;
                memcpy(noDollarSign, &tokenArray[i][1], strlen(tokenArray[i]));

                printf("%s \n", get_value(noDollarSign));
            } else {
                // if no dollar sign then print word normally
                printf("%s \n", tokenArray[i]);
            }
        }  
    }
}

// used to change directory of shell
void change_dir(char tokenArray[MAX_ARGS][MAX_ARGS]){
    // checking if user inputted cd
    if(strcmp(tokenArray[0], "cd") == 0){
        // checking if user wants to go to previous directory
        if(strcmp(tokenArray[1], "..") == 0){
            // changing directory to one below
            chdir("..");
            char cwd[CWD_SIZE];
            getcwd(cwd, sizeof(cwd));
            // resetting variables
            init_var("CWD", cwd);
        } else if(tokenArray[1][0] != '\0' && tokenArray[2][0] == '\0'){
            // changing dir to the argument that the user inputted
            chdir(tokenArray[1]);
            init_var("CWD", tokenArray[1]);
        } else {
            printf("Invalid number of arguments.\n");
        }
    }
}

// used to print all or user-specified variable
void show_var(char tokenArray[MAX_ARGS][MAX_ARGS]){
    if(strcmp(tokenArray[0], "showvar") == 0){
        // if there is one argument only for showvar
        if(tokenArray[1][0] != '\0' && tokenArray[2][0] == '\0'){
            printf("%s\n", get_value(&tokenArray[1][0]));
        } else if(tokenArray[1][0] == '\0'){
            // else print all
            for(int i = 0; i < varCount; i++){
                printf("[%s]: %s\n", variables[i].key, variables[i].data);
            }
        } else {
            printf("Invalid number of arguments.\n");
        }
    }
}

// used to promote shell variable to environmental scope
void export_var(char tokenArray[MAX_ARGS][MAX_ARGS]){
    // checking if the user inputted export and that there is only 1 variable
    if(strcmp(tokenArray[0], "export") == 0){
        if(tokenArray[1][0] != '\0' && tokenArray[2][0] == '\0'){
            // getting value of given key
            char *value = get_value(tokenArray[1]); 
            setenv(tokenArray[1], value, 1);
            char **vars = environ;
        } else {
            printf("\nInvalid number of arguments");
        }
    }
}

// used to show all or user-specified variable
void show_env_vars(char tokenArray[MAX_ARGS][MAX_ARGS]){
    // checking if user wants to show variables
    if(strcmp(tokenArray[0], "showenv") == 0){
        // if there is one argument only for showenv
        if(tokenArray[1][0] != '\0' && tokenArray[2][0] == '\0'){
            // printing specific environmental variable
            printf("%s\n", getenv(tokenArray[1]));
        } else if(tokenArray[1][0] == '\0') {
            // if no argument then print all
            char **vars = environ;
            for(; *vars; vars++){ // infinite loop till vars is null
                printf("%s\n", *vars);
            }
        } else {
            printf("Invalid number of arguments.\n");
        }
    }
}

// used to unset environmental variable
void unset_var(char tokenArray[MAX_ARGS][MAX_ARGS]){
    // checking is user inputted unset
    if(strcmp(tokenArray[0], "unset") == 0){
        // if there is one argument only for unset
        if(tokenArray[1][0] != '\0' && tokenArray[2][0] == '\0'){
            // remove variable from evironment
            unsetenv(tokenArray[1]);
            char **vars = environ;
        } else {
            printf("\nInvalid number of arguments");
        }
    }
}

// used to initialise directory stack
void init_stack(int cap){
    char cwd[cap];
    if(stacksize == 0){
        // increasing stacksize by 1 due to cwd being first entry
        stacksize++;
        // creating space in memory for stack
        directories = calloc((int)stacksize, sizeof(directories));
        //copying cwd for first entry
        strcpy(directories[stacksize-1].dir, getcwd(cwd, cap));
    }
}

// used to push new directory to stack
void pushd(char tokenArray[MAX_ARGS][MAX_ARGS]){
    // checking if user wants to push directory
    if(strcmp(tokenArray[0], "pushd") == 0){
        // if there is one argument only for pushd
        if(tokenArray[1][0] != '\0' && tokenArray[2][0] == '\0'){
            stacksize++;
            // increaseing space for new directory
            directories = realloc(directories, (int)sizeof(directories) + stacksize);
            // putting new directory into new space
            strcpy(directories[stacksize-1].dir, tokenArray[1]);

            printf("%s has been pushed.\n", directories[stacksize-1].dir);
            // changing directory to element at top of stack
            chdir(tokenArray[1]);
            init_var("CWD", tokenArray[1]);
        } else {
            printf("Invalid number of arguments.\n");
        }
    }
}

// used to pop the last item on the directory stack
void popd(char* line){
    if(line != NULL && strcmp(line, "popd") == 0){
        if(stacksize <= 1){
            printf("No directory can be popped.\n");
            return;
        } else {
            printf("Last element has been popped.\n");

            // decreasing stacksize and changing directory
            stacksize--;
            chdir(directories[stacksize].dir);
            return;
        }
    } else {
        return;
    }
}

// used to print all of stack
void print_stack(char* line){
    if(line != NULL && strcmp(line, "dirs") == 0){
        for(int i = 0; i < stacksize; i++){
            printf("%s\n", directories[i].dir);
        }
    } else {
        return;
    }
}

// used to show working directory
void show_pwd(char* line){
    if(line != NULL && strcmp(line, "pwd") == 0){
        printf("%s\n", directories[stacksize-1].dir);
    } else {
        return;
    }
}

// used to use external file as inputs for shell
void source(char tokenArray[MAX_ARGS][MAX_ARGS]){
    if(strcmp(tokenArray[0], "source") == 0){
        // there is one argument only for pushd
        if(tokenArray[1][0] != '\0' && tokenArray[2][0] == '\0'){
            int i = 0, sum = 0;
            FILE *fptr;

            char lines[MAX_ARGS][MAX_ARGS];
            // opening file
            if ((fptr = fopen(tokenArray[1], "r")) == NULL){
                printf("Error when trying to open file.\n");

                return;
            } 

            // looping through all file and storing lines into array
            while(fgets(lines[i], MAX_ARGS, fptr)){
                lines[i][strlen(lines[i])] = '\0';
                i++;
            }

            sum = i;
        
            // printing new array
            for(i = 0; i < sum; ++i){
                printf("%s", lines[i]);
            }

            // for(i = 0; i < sum; ++i){
            //     execute(lines[i]);
            // }

            fclose(fptr);
        } else {
            printf("\nInvalid number of arguments");
        }
    }
}