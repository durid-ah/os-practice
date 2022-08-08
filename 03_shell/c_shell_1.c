#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 80 // Maximum length command
#define ARG_LENGTH (MAX_LINE / 2) + 1
#define MAX_HISTORY 10

struct Entry {
    int index;
    char* command;
    char* args[ARG_LENGTH];
};

struct History {
    int start;
    int end;
    int capacity;
    struct Entry history[MAX_HISTORY];
};

/**
 * @brief add a new entry into the history array, if there are already
 * `MAX_HISTORY` number of entries it will overwrite the oldest entry
 */
void add_entry(struct History *history, struct Entry *entry) {
    int idx = (history->start + history->capacity) % MAX_HISTORY;
    if (history->capacity < MAX_HISTORY) {
        history->capacity++;
        history->end = history->capacity;
    } else {
        history->start++;
        history->end++;
    }

    history->history[idx] = *entry;
}

/**
 * @brief print out all the entries in the history array
 */
void print_history(struct History *history) {
    int i = history->start;

    while (i < history->end) {
        printf("%d. %s\n", history->history[i % MAX_HISTORY].index, history->history[i % MAX_HISTORY].command);
        i = ++i;
    }   
}

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

void copy_args(char* from[], char* to) {
    for (size_t i = 0; i < ARG_LENGTH; i++)
    {
        // strncpy(to[i], from[i]);
    }
    
}


int main(void) {
    char* args[ARG_LENGTH];
    int should_run = 1; // flag to determine when to exit program

    struct History history = { 0, 1, 0 };

    int status = 0;
    while (should_run) {
        pid_t pid;
        char* str = (char *)malloc(MAX_LINE * sizeof(char));

        printf("osh > ");
        fflush(stdout);
        fgets(str, MAX_LINE, stdin);

        int arg_count = parse_input(str, args);        

        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork Failed");
        } else if (pid == 0) {
            // child
            int res = execvp(args[0], args);
            if (res == -1) {
                return 1;
            }

            return 0;
            
        } else {
            // parent
            pid_t s = wait(&status);
        }

    }
}