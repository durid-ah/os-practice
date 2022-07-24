#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80 // Maximum length command

int main(void) {
    char* args[MAX_LINE/2 + 1];
    int should_run = 1; // flag to determine when to exit program

    while (should_run) {
        printf("osh >");
        fflush(stdout);

        /**
         * fork
         * child invokes execvp()
         * if command included & parent will wait()
         */
    }
}