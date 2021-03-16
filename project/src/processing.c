#include "compilation.h"
#include "dataloader.h"
#include "playlist.h"
#include "processing.h"

playlist_t *data_processing(playlist_t *all_composition, size_t duration, size_t amount, unsigned int bpm) {
    if (all_composition == NULL) {
        return NULL;
    }

    playlist_t *suitable_compositions = search(all_composition, duration, bpm);
    if (suitable_compositions == NULL) {
        fprintf(stderr, "Unable to create playlist\n");
        return NULL;
    }

    playlist_t *result_compilation = gen_compilation(suitable_compositions, amount, SEED);
    if (result_compilation == NULL) {
        fprintf(stderr, "It is impossible to create a playlist from suitable\n");
        delete_playlist(suitable_compositions);
        return NULL;
    }

    delete_playlist(suitable_compositions);
    return result_compilation;
}

int data_input(FILE *fd,
               FILE *fd_input,
               playlist_t **all_composition,
               size_t *amount,
               size_t *duration,
               unsigned int *bpm) {
    if (fd == NULL) {
        return ERROR_READ_DATA;
    }

    if (fd_input == NULL) {
        return ERROR_READ_DATA;
    }

    *all_composition = read_data(fd);
    if (*all_composition == NULL) {
        fprintf(stderr, "Error reading playlist from file\n");
        return ERROR_READ_DATA;
    }

    if (get_user_input(fd_input, amount, duration, bpm) != 0) {
        fprintf(stderr, "Data entry error\n");
        delete_playlist(*all_composition);
        *all_composition = NULL;
        return ERROR_WRONG_INPUT;
    }

    return 0;
}

void free_recourses(FILE *fd,
                    FILE *fd_input,
                    playlist_t *all_comp,
                    playlist_t *res_comp) {
    if (fd != NULL) {
        fclose(fd);
    }

    if (fd_input != NULL) {
        fclose(fd_input);
    }

    if (all_comp != NULL) {
        delete_playlist(all_comp);
    }

    if (res_comp != NULL) {
        delete_playlist(res_comp);
    }
}

