#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>

#define CELLS 9

int board[CELLS][CELLS] = {
    {6,2,4,5,3,9,1,8,7},
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
    bool is_valid;
    int index;
} thread_data;

int await_validate_threads(pthread_t workers[], int worker_count, thread_data results[]) {
    int row_number = 0;
    for(int i = 0; i < worker_count; i++) {
        pthread_join(workers[i], NULL);
        if (!results[i].is_valid) {
            row_number = i + 1;
        }
    }

    return row_number;
}

void *run_validator(pthread_attr_t attr[], pthread_t workers[], thread_data data[], int worker_count, void* (* validation_func)(void*)) {
    for(int i = 0; i < worker_count; i++) {
        data[i].is_valid = false;
        data[i].index = i;

        pthread_attr_init(&attr[i]);
        pthread_create(&workers[i],&attr[i], validation_func, &data[i]);
    }
}

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

void *validate_col(void* data) {
    thread_data* _data = (thread_data*)data;
    
    int count[9] = {0,0,0,0,0,0,0,0,0};
    int col = _data->index;

    for(int i = 0; i < CELLS; i++) {
        int entry = board[i][col];
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

void *validate_square(void* data) {
    thread_data* _data = (thread_data*)data;
    
    int count[9] = {0,0,0,0,0,0,0,0,0};
    int col = _data->index % 3;
    int row = _data->index / 3;
    
    int i_start = row * 3;
    int i_end = i_start + 3;

    int j_start = col * 3;
    int j_end = j_start + 3;


    for(int i = i_start; i < i_end; i++) {
        for(int j= j_start; j < j_end; j++) {
            int entry = board[i][j];
            if (entry == 0) {
                continue;
            } else if (count[entry - 1]) {
                _data->is_valid = false;
                return;
            } else {
                count[entry - 1] = 1;
            }
        }
    }

    _data->is_valid = true;
}

int main(void) {
    pthread_t workers[CELLS];
    pthread_attr_t attr[CELLS];

    thread_data rows[CELLS];
    run_validator(attr,workers, rows, CELLS, validate_row);
    int failed_row = await_validate_threads(workers, CELLS, rows);
    if (failed_row != 0) {
        printf("Validation failed at row: %d\n", failed_row);
        return -1;
    }

    thread_data cols[CELLS];
    run_validator(attr,workers, cols, CELLS, validate_col);
    int failed_col = await_validate_threads(workers, CELLS, cols);
    if (failed_col != 0) {
        printf("Validation failed at col: %d", failed_col);
        return -1;
    }

    thread_data squares[CELLS];
    run_validator(attr,workers, squares, CELLS, validate_square);
    int failed_square = await_validate_threads(workers, CELLS, squares);
     if (failed_square != 0) {
        printf("Validation failed at square: %d", failed_square);
        return -1;
    }
    
    return 0;
}