#ifndef DATALOADER_H
#define DATALOADER_H

#include <stdio.h>
#include "composition.h"
#include "playlist.h"

#define MAX_TITLE_SIZE 100
#define MIN_MULTIPLIER 60
#define HOUR_MULTIPLIER 3600

enum error_input {
    EMPTY_FILE_POINTER = 1,
    EMPTY_DURATION_POINTER,
    EMPTY_BPM_POINTER,
    EMPTY_LEN_POINTER,
    WRONG_COMPILATION_LEN,
    WRONG_DURATION_INPUT,
    WRONG_BPM_INPUT
};

playlist_t *read_data(FILE *fd);
int get_user_input(FILE *fd, size_t *len, size_t *duration, unsigned int *bpm);

#endif //DATALOADER_H
