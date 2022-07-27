#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_LINE 80 // Maximum length command

int parse_input(char input[], char* args[]) {
    input[strcspn(input, "\n")] = 0;
    // TODO: strtok_r? 
    char* arg = strtok(input, " ");
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

        int y = 0;
        while (y < arg_count) {
            printf("ret: %s \n", args[y]);
            y++;
        }


        /**
         * fork
         * child invokes execvp()
         * if command included & parent will wait()
         */
        // pid = fork();
        // if (pid < 0) {
        //     fprintf(stderr, "Fork Failes");
        // } else if (pid == 0) {
        //     // child
        // } else {
        //     // parent
        // }

    }
}