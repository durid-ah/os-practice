#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 80 // Maximum length command

struct Entry {
    int index;
    char* command;
};

struct History {
    int start;
    int end;
    struct Entry history[10];
};

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

    return i;
}

int main(void) {
    char* args[MAX_LINE/2 + 1];
    int should_run = 1; // flag to determine when to exit program

    while (should_run) {
        pid_t pid;
        char str[MAX_LINE];

        printf("osh > ");
        fflush(stdout);
        fgets(str, MAX_LINE, stdin);

        int arg_count = parse_input(str, args);

        /**
         * fork
         * child invokes execvp()
         * if command included & parent will wait()
         */
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork Failed");
        } else if (pid == 0) {
            execvp(args[0], args);
            return 0;
        } else {
            wait(NULL);
            // parent
        }

    }
}