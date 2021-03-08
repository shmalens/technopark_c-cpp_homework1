#include <stdio.h>
#include <string.h>

#include "dataloader.h"
#include "composition.h"
#include "playlist.h"

composition_t *read_comp_data(FILE *fd) {
    if (fd == NULL) {
        return NULL;
    }

    char title_buffer[MAX_TITLE_SIZE];
    size_t title_len = 0;
    if(fgets(title_buffer, MAX_TITLE_SIZE, fd) == 0) {
        return NULL;
    }
    title_len = strlen(title_buffer);
    title_buffer[title_len - 1] = '\0';

    size_t duration;
    if (fscanf(fd, "%lu\n", &duration) == 0) {
        return NULL;
    }

    unsigned int bpm;
    if (fscanf(fd, "%u\n", &bpm) == 0) {
        return NULL;
    }

    composition_t *tmp = create_composition(title_buffer, title_len, duration, bpm);
    if (tmp == NULL) {
        return NULL;
    }

    return tmp;
}

playlist_t *read_data(FILE *fd) {
    if (fd == NULL) {
        return NULL;
    }

    int amount;
    if (fscanf(fd, "%d\n", &amount) == 0) {
        return NULL;
    }

    if (amount <= 0) {
        return NULL;
    }

    playlist_t *new_playlist = create_playlist(amount);
    for (int i = 0; i < amount; ++i) {
        composition_t *tmp = read_comp_data(fd);
        if (tmp == NULL) {
            delete_playlist(new_playlist);
            return NULL;
        }

        int err = add_composition(new_playlist, tmp);
        if (err != 0) {
            delete_playlist(new_playlist);
            delete_composition(tmp);
            return NULL;
        }

        delete_composition(tmp);
    }

    return new_playlist;
}


