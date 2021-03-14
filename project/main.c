#include <stdio.h>
#include <stdlib.h>

#include "playlist.h"
#include "dataloader.h"
#include "compilation.h"

#define USER_INPUT "./data/user_input.txt"
#define PATH "./data/compositions.txt"
#define SEED 6339

enum errors {
    ERROR_FILE,
    ERROR_READ_DATA,
    ERROR_WRONG_INPUT,
    ERROR_SEARCH,
    ERROR_COMPILATION_GEN
};

int main() {
    FILE *fd = fopen(PATH, "r");
    if (fd == NULL) {
        fprintf(stderr, "File open error\n");
        return ERROR_FILE;
    }

    FILE *fd_input = fopen(USER_INPUT, "r");
    if (fd_input == NULL) {
        fclose(fd);
        return ERROR_FILE;
    }

    playlist_t *all_composition = read_data(fd);
    if (all_composition == NULL) {
        fprintf(stderr, "Error reading playlist from file\n");
        fclose(fd);
        fclose(fd_input);
        return ERROR_READ_DATA;
    }

    size_t amount;
    size_t duration;
    unsigned int bpm;
    if (get_user_input(fd_input, &amount, &duration, &bpm) != 0) {
        fprintf(stderr, "Data entry error\n");
        delete_playlist(all_composition);
        fclose(fd);
        fclose(fd_input);
        return ERROR_WRONG_INPUT;
    }

    playlist_t *suitable_compositions = search(all_composition, duration, bpm);
    if (suitable_compositions == NULL) {
        fprintf(stderr, "Unable to create playlist\n");
        delete_playlist(all_composition);
        fclose(fd);
        fclose(fd_input);
        return ERROR_SEARCH;
    }

    playlist_t *result_compilation = gen_compilation(suitable_compositions, amount, SEED);
    if (result_compilation == NULL) {
        fprintf(stderr, "It is impossible to create a playlist from suitable\n");
        fclose(fd);
        delete_playlist(all_composition);
        delete_playlist(suitable_compositions);
        fclose(fd_input);
        return ERROR_COMPILATION_GEN;
    }

    printf("Final selection\n");
    print_playlist(stdout, result_compilation);

    fclose(fd);
    fclose(fd_input);
    delete_playlist(all_composition);
    delete_playlist(suitable_compositions);
    delete_playlist(result_compilation);
    return 0;
};