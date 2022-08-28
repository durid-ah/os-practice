#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "history.h"

#define MAX_LINE 80 // Maximum length command
#define ARG_LENGTH (MAX_LINE / 2) + 1

int parse_input(char input[], char* args[]) {
    
    // remove trailing \n
    input[strcspn(input, "\n")] = 0;    
    // get the command
    char* arg = strtok(input, " ");
    // get the other args
    int i = 0;
    while (arg != NULL) {
        args[i] = arg;
        arg = strtok(NULL, " ");
        i++;
    }

    args[i] = NULL;
    return i;
}


int main(void) {
    int should_run = 1; // flag to determine when to exit program

    struct History history = { 0, 1, 0 };

    int status = 0;
    while (should_run) {
        pid_t pid;
        char* str = (char *)malloc(MAX_LINE * sizeof(char));

        printf("osh > ");
        fflush(stdout);
        fgets(str, MAX_LINE, stdin);

        struct Entry entry;
        entry.arg_str = str;
        entry.args = (char **)malloc(ARG_LENGTH * sizeof(char*));
        int arg_count = parse_input(entry.arg_str, entry.args);
        add_entry(&history, &entry);

        if (strcmp(entry.args[0], "durid") == 0) {
            break;
        }

        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork Failed");
        } else if (pid == 0) {
            // child
            if (strcmp(entry.args[0],"history") == 0) {
                print_history(&history);
                return 0;
            } 

            int res = execvp(entry.args[0], entry.args);
            if (res == -1) {
                return 1;
            }

            return 0;
            
        } else {
            // parent
            pid_t s = wait(&status);
        }
    }

    free_history(&history);
}