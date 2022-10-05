#include "main.h"
#include "linenoise.h"
#include "variables.h"
#include "parsing.h"
#include "commands.h"
#include "ext_commands.h"
#include "redirection.h"
#include "piping.h"

int main(int argc, const char *argv[], const char *envp[]){
    init_shell_vars(); // initialising environmental variables
    strcpy(shell_name, get_value("PROMPT")); // getting prompt text from environmental variables

    init_stack(MAX_STACK_CAP); // making directory stack

    // getting input from user and executing it
    while((line = linenoise(shell_name)) != NULL){
        execute(line);

        linenoiseFree(line); // emptying the line
    }

    return EXIT_SUCCESS;
}

// checks user input with all commands (internal and external)
void execute(char* line){
    tokeniseLine(line, tokenArray); // tokenising the user input
    check_exit(line); // checking if user wants to exit
    show_var(tokenArray); // checking if user wants to show variables
    echo(tokenArray); // checking if user wants to echo a string
    var_dec(line); // checking for variable declaration in user input
    change_dir(tokenArray); // checking if user wants to change directory
    show_env_vars(tokenArray); // checking if user wants all environmental variables
    export_var(tokenArray); // checking if user wants to export variable
    unset_var(tokenArray); // checking if user wants to unset variable
    print_stack(line); // checking if user wants to print stack
    pushd(tokenArray); // checking if user wants to push a directory
    popd(line); // checking if user wants to pop directory
    show_pwd(line); // checking if user wants to show current
    source(tokenArray); // checking if user wants to use source command
    // check_redirection(line); // checking is user wants to redirect a command
    check_pipe(line); // checking if user wants to use pipe command
    ext_command(tokenArray); // checking if users code is an external command
}