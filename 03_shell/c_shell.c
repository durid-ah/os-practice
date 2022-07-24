#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_LINE 80 // Maximum length command

void parse_input(char* input[], char* args[]) {
    printf("%s", *input);
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

        parse_input(&str, &args);
        // str[strcspn(str, "\n")] = 0;
        // char* arg = strtok(str, " ");

        // while (arg != NULL) {
        //     printf("'%s'\n", arg);
        //     arg = strtok(NULL, " ");
        // }

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