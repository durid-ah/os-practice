#include <stdio.h>
#include <string.h>

#define MAX_HISTORY 10

struct Entry {
    int index;
    char * arg_str;
    char** args;
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
    entry->index = idx + 1;
    if (history->capacity < MAX_HISTORY) {
        history->capacity++;
        history->end = history->capacity;
    } else {
        history->start++;
        history->end++;
        history->start = history->start % MAX_HISTORY;
        history->end = history->end % (MAX_HISTORY + 1);
        free(history->history[idx].args);
        free(history->history[idx].arg_str);
    }

    history->history[idx] = *entry;
}

void print_array(char** args) {
    size_t i = 0;
    char* val = args[i];
    while (val != NULL) {
        printf("%s ", val);
        i++;
        val = args[i];
    }
}

/**
 * @brief print out all the entries in the history array
 */
void print_history(struct History *history) {
    int i = history->start;

    while (i != history->end) {
        printf("%d. ", history->history[i % MAX_HISTORY].index);
        print_array(history->history[i % MAX_HISTORY].args);
        printf("\n");
        i = ++i;
    }
    
    fflush(stdout);
}

void free_history(struct History *history) {
    int i = history->start;

    while (i != history->end) {
        printf("%d. ", history->history[i % MAX_HISTORY].index);
        print_array(history->history[i % MAX_HISTORY].args);
        printf("\n");

        free(history->history[i].args);
        free(history->history[i].arg_str);

        ++i;
        i = i % MAX_HISTORY;
    }
    
    fflush(stdout);
}

