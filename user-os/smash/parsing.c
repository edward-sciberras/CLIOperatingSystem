#include "parsing.h"

// used to remove character at given index
void remove_char(char *line, int index){
    for(int i = index; line[i] != '\0'; i++){
        // if the character to be removed is the last chacter then delete
        if(line[i+1] != '\0'){
            line[i] = line[i+1];
        } else {
            line[i] = '\0';
        }
    }
}

// used to empty given array
void empty(char temp[MAX_ARGS][MAX_ARGS]){
    for(int i = 0; i < MAX_ARGS; i++){
        for(int j = 0; j < MAX_ARGS; j++){
            // nested loop that sets all of 2d array to null terminator
            temp[i][j] = '\0';
        }
    }
}

// used to parse quotes during tokenisation
int parsing_quotes(int i, char *line, int count, int start, int index, char temp[MAX_ARGS][MAX_ARGS]){
    int j = 0;
    // starts loop from index of loop in tokeniseLine
    for(j = i; line[j] > 1; j++){
        // if theres a quote then remove
        if(line[j] == '\"'){
            remove_char(line, j);
            break;
        } else if(line[j] == '\\') { // if theres a backslash then remove
            remove_char(line, j);
            if(line[i] == '\0'){
                count = 0;
                for(int j = start; j <= i; j++){
                    temp[index][count] = line[j];
                    count++;
                }
            }
        } else if(line[j] == '$') { // if theres a dollar sign then remove
            remove_char(line, j);
            if(line[i] == '\0'){
                count = 0;
                for(int j = start; j <= i; j++){
                    temp[index][count] = line[j];
                    count++;
                }
            }
        }
    }

    i = j;
    return i;
}

void tokeniseLine(char *line, char temp[MAX_ARGS][MAX_ARGS]){
    int index = 0, start = 0, count = 0;

    // clearing array to be sure its empty
    empty(temp);

    for(int i = 0; line[i] > 1; i++){
        if(line[i] == '\"'){
            remove_char(line, i);
            i = parsing_quotes(i, line, count, start, index, temp);
            i--;

            if(line[i+1] == '\0'){
                count = 0;
                for(int j = start; j <= i; j++){
                    temp[index][count] = line[j];
                    count++;
                }
            }
        } else if( 
                  line[i] == ';' || 
                  line[i] == '\t' || 
                  line[i] == ' ') {
            count = 0;
            for(int j = start; j < i; j++){
                temp[index][count] = line[j];
                count++;
            }
            index++;
            start = i + 1;
        } else if(line[i + 1] == '\0') {
            count = 0;
            for(int j = start; j <= i; j++){
                temp[index][count] = line[j];
                count++;
            }
        }
    }
}