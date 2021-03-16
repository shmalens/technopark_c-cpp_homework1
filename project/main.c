#include <stdio.h>

#include "playlist.h"
#include "processing.h"

#define USER_INPUT "./data/user_input.txt"
#define PATH "./data/compositions.txt"

enum errors {
    ERROR_FILE = 1,
    ERROR_DATA_INPUT,
    ERROR_DATA_PROCESSING
};

int main() {
    FILE *fd = fopen(PATH, "r");
    if (fd == NULL) {
        fprintf(stderr, "File open error\n");
        return ERROR_FILE;
    }

    FILE *fd_input = fopen(USER_INPUT, "r");
    if (fd_input == NULL) {
        free_recourses(fd, NULL, NULL, NULL);
        return ERROR_FILE;
    }

    playlist_t *all_composition = NULL;
    size_t amount = 0;
    size_t duration = 0;
    unsigned int bpm = 0;
    if (data_input(fd, fd_input, &all_composition, &amount, &duration, &bpm) != 0) {
        free_recourses(fd, fd_input, NULL, NULL);
        return ERROR_DATA_INPUT;
    }

    playlist_t *result_compilation = data_processing(all_composition, duration, amount, bpm);
    if (result_compilation == NULL) {
        free_recourses(fd, fd_input, all_composition, NULL);
        return ERROR_DATA_PROCESSING;
    }

    printf("Final selection\n");
    print_playlist(stdout, result_compilation);

    free_recourses(fd, fd_input, all_composition, result_compilation);
    return 0;
};