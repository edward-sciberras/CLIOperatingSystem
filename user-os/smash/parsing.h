#ifndef PARSING_GUARD // include parsing guards
#define PARSING_GUARD

#include "libraries.h"
#include "main.h"

void remove_char(char *line, int index);
void empty(char temp[MAX_ARGS][MAX_ARGS]);
int parsing_quotes(int i, char *line, int count, int start, int index, char temp[MAX_ARGS][MAX_ARGS]);
void tokeniseLine(char *line, char temp[MAX_ARGS][MAX_ARGS]);

#endif // ending parsing headers guards