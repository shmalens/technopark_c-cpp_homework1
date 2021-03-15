#ifndef PROCESSING_H
#define PROCESSING_H

#include "playlist.h"

#define SEED 6339

enum input_block_errors {
    ERROR_READ_DATA = 1,
    ERROR_WRONG_INPUT,
};

playlist_t *data_processing(playlist_t *all_composition,
                            size_t duration,
                            size_t amount,
                            unsigned int bpm);

int data_input(FILE *fd,
               FILE *fd_input,
               playlist_t **all_composition,
               size_t *amount,
               size_t *duration,
               unsigned int *bpm);

void free_recourses(FILE *fd,
                    FILE *fd_input,
                    playlist_t *all_comp,
                    playlist_t *res_comp);

#endif //PROCESSING_H
