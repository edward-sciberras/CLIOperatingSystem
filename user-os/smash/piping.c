#include "piping.h"
#include "main.h"

int pipeSymbol = '|';

// used to check if line includes pipe symbol
int check_pipe(char* line){
    if(strchr(line, pipeSymbol) == NULL){
        return 0;
    } else {
        execute_pipe(tokenArray);

        return 1;
    }
}

// used to execute pipe commands
void execute_pipe(char tokenArray[MAX_ARGS][MAX_ARGS]){
    // getting number of arguments
    int argNum = 0;
    for(int i = 0; tokenArray[i][0] != '\0'; i++){
        argNum++;
    }

    // splitting the arguments
    for(int i = 0; i < argNum; i++){
        if(strcmp(tokenArray[i], "|") == 0){
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

    if(pipe(fd) == -1){
        perror("\nError when piping.");
    }

    pid1 = fork();
    if(pid1 < 0){
        perror("\nError when forking.");
    } else if (pid1 == 0){
        // setting output of child process  
        dup2(fd[1], STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]); // remains open even after dup

        execute(lhs);
    }

    pid2 = fork();
    if(pid2 < 0){
        perror("\nError when forking.");
    } else if(pid2 == 0) {
        // set the input of process to the output of previous process
        dup2(fd[0], STDIN_FILENO);

        close(fd[0]);
        close(fd[1]); // remains open even after dup

        execute(rhs);
    }

    close(fd[0]);
    close(fd[1]);

    // waiting for processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}