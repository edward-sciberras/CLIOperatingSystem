#include "redirection.h"

int check_redirection(char* line){
    if(strstr(line, ">>") != NULL){
        execute_redirection(tokenArray, 2);
        return 2;
    } else if(strchr(line, '>') != NULL){
        execute_redirection(tokenArray, 1);
        return 1;
    } else if(strchr(line, '<') != NULL){
        execute_redirection(tokenArray, 3);
        return 3;
    } else {
        return 0;
    }
}

void execute_redirection(char tokenArray[MAX_ARGS][MAX_ARGS], int operationNum){
    int direction_out = 0; 
    if(operationNum == 1){
        direction_out = 1; 
        split_args(tokenArray, lhs_red, rhs_red, ">");
    } else if(operationNum == 2){
        direction_out = 1; 
        split_args(tokenArray, lhs_red, rhs_red, ">>");
    } else if(operationNum == 3){
        split_args(tokenArray, lhs_red, rhs_red, "<");
    } else {
        return;
    }
    
    pid = fork();
    if(pid = -1){
        perror("Error when forking.\n");
    } else if(pid == 0) {
        if(direction_out == 1){
            FILE *fptr;
            if(operationNum == 1){
                if((fptr = fopen(rhs_red[0], "w")) == NULL){
                    perror("Error when opening file.\n");
                }  
            }

            if(operationNum == 2){
                if ((fptr = fopen(rhs_red[0], "a")) == NULL){
                    perror("Error when opening file.\n");
                }    
            }

            // the file is now set for the stdout
            dup2(fileno(fptr), STDOUT_FILENO);
            fclose(fptr);
            execute(lhs_red);
            return;
        }

        if(operationNum == 3){
            FILE *fptr;

            if(operationNum == 3){
                if((fptr = fopen(rhs_red[0], "r")) == NULL){
                    perror("Error when opening file.\n");
                }
            }

            // the file is now set for the stdin
            dup2(fileno(fptr),STDIN_FILENO);
            fclose(fptr);
            execute(lhs_red);
            return;
        }
    }
}

void split_args(char tokenArray[MAX_ARGS][MAX_ARGS], char* lhs, char* rhs, char *c){
    lhs[0] = '\0';
    rhs[0] = '\0';

    // getting number of arguments
    int argNum = 0;
    for(int i = 0; tokenArray[i][0] != '\0'; i++){
        argNum++;
    }

    // splitting the arguments
    for(int i = 0; i < argNum; i++){
        if(strcmp(tokenArray[i], c) == 0){
            // getting left hand side of pipe into array
            for(int j = 0; j < i; j++){
                strcat(lhs, tokenArray[j]);
                strcat(lhs, " ");
            }

            // getting right hand side of pipe into array
            for(int j = i + 1; j < argNum; j++){
                strcat(rhs, tokenArray[j]);
                strcat(rhs, " ");
            }
        }
    }
}