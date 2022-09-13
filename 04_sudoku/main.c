#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>

#define CELLS 9

int board[CELLS][CELLS] = {
    {6,2,4,5,3,9,1,1,7},
    {5,1,9,7,2,8,6,3,4},
    {8,3,7,6,1,4,2,9,5},
    {1,4,3,8,6,5,7,2,9},
    {9,5,8,2,4,7,3,6,1},
    {7,6,2,3,9,1,4,5,8},
    {3,7,1,9,5,6,8,4,2},
    {4,9,6,1,8,2,5,7,3},
    {2,8,5,4,7,3,9,1,6}
};


typedef struct thread_data {
    bool* is_valid;
    int index;
} thread_data;

void *validate_row(void* data) {
    thread_data* _data = (thread_data*)data;
    
    int count[9] = {0,0,0,0,0,0,0,0,0};
    int row = _data->index;

    for(int i = 0; i < CELLS; i++) {
        int entry = board[row][i];
        if (entry == 0) {
            continue;
        } else if (count[entry - 1]) {
            _data->is_valid = false;
            return;
        } else {
            count[entry - 1] = 1;
        }
    }

    _data->is_valid = true;
}

int main(void) {
    pthread_t workers[CELLS];
    pthread_attr_t attr[CELLS];

    thread_data rows[CELLS];
    for(int i = 0; i < CELLS; i++) {
        rows[i].is_valid = false;
        rows[i].index = i;

        pthread_attr_init(&attr[i]);
        pthread_create(&workers[i],&attr[i], validate_row, &rows[i]);
    }

    for(int i = 0; i < CELLS; i++) {
        pthread_join(workers[i], NULL);
        // TODO: Check if return value is valid;
    }

    return 0;
}