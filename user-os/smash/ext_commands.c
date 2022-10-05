#include "ext_commands.h"
#include "main.h"
#include "variables.h"

int success = 0, errNumber = 0;
char loc[2048] = "\0";

void ext_command(char tokenArray[MAX_ARGS][MAX_ARGS]){
    pid_t pid;
    pid = fork();

    if(pid == 0){
        init_shell_vars();

        // getting path of new file
        strcat(loc, getenv("CWD"));
        strcat(loc, "/");
        strcat(loc, tokenArray[0]);
    }

    // if -1 then theres an error
    // runs the external command as an argument with arguments that are needed
    success = execlp(tokenArray[0], tokenArray[0], tokenArray[1], NULL);

    if(success < 0){
        strcat(loc, " ");

        // stores -1 if failture
        success = system(loc);

        if(success == -1){
            perror("\nUnrecognised external command.");
            return;
        }
    } else if(pid > 0) {
        // waiting for chill process to terminate
        waitpid(pid, &errNumber, 0);

        if(WIFEXITED(errNumber)){
            errNumber = WEXITSTATUS(errNumber);

            if(errNumber == 1){
                perror("\nUnrecognised external command.");
                return;
            }
        }
    } else {
        perror("\nUnrecognised external command.");
        return;
    }
}