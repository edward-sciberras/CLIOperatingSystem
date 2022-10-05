cmake_minimum_required(VERSION 3.15)
project(smash C)

add_executable(main main.c linenoise.c parsing.c variables.c commands.c ext_commands.c redirection.c piping.c)
