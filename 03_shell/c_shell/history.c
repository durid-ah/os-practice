#include <stdio.h>
#include <string.h>

#define MAX_HISTORY 10

struct Entry {
    int index;
    char* command;
    char* args;
};

struct History {
    int start;
    int end;
    int capacity;
    struct Entry history[MAX_HISTORY];
};


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

void print_history(struct History *history) {
    int i = history->start;

    while (i < history->end) {
        printf("%d. %s\n", history->history[i % MAX_HISTORY].index, history->history[i % MAX_HISTORY].command);
        i = ++i;
    }
    
}

int main(void) {
    struct History history = {0, 0, 0};

    for (size_t i = 0; i < 21; i++)
    {
        struct Entry nentry = {i + 1, "stuff", NULL};
        add_entry(&history, &nentry);
    }   

    print_history(&history);
}