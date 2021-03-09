#include <stdlib.h>

#include "composition.h"
#include "playlist.h"

playlist_t *create_playlist(size_t start_capacity) {
    playlist_t *new_playlist = malloc(sizeof(playlist_t));
    if (new_playlist == NULL) {
        return NULL;
    }

    if (start_capacity == 0) {
        start_capacity += 1;
    }

    new_playlist->compositions = malloc(sizeof(composition_t *) * (start_capacity));
    if (new_playlist->compositions == NULL) {
        free(new_playlist);
        return NULL;
    }
    new_playlist->capacity = start_capacity;
    new_playlist->len = 0;
    return new_playlist;
}

int delete_playlist(playlist_t *playlist) {
    if (playlist == NULL) {
        return -1;
    }


    for (size_t i = 0; i < playlist->len; ++i) {
        if (playlist->compositions[i] != NULL) {
            delete_composition(playlist->compositions[i]);
        }
    }

    free(playlist->compositions);
    free(playlist);
    return 0;
}

static composition_t **resize_playlist(composition_t **src, size_t *capacity) {
    if (src == NULL) {
        return NULL;
    }

    composition_t **new_compositions = realloc(src, sizeof(composition_t *) * (*capacity * 2));
    if (new_compositions == NULL) {
        return NULL;
    }
    *capacity *= 2;
    return new_compositions;
}

int add_composition(playlist_t *playlist, composition_t *composition) {
    if (playlist == NULL || composition == NULL) {
        return -1;
    }

    if (playlist->len == playlist->capacity) {
        composition_t **resized = resize_playlist(playlist->compositions, &(playlist->capacity));
        if (resized == NULL) {
            return -2;
        }

        playlist->compositions = resized;
    }

    composition_t *new_composition = composition_cpy(composition);
    if (new_composition == NULL) {
        return -3;
    }

    playlist->compositions[playlist->len] = new_composition;
    playlist->len += 1;

    return 0;
}

int print_playlist(playlist_t *playlist) {
    if (playlist == NULL) {
        return -1;
    }

    for (size_t i = 0; i < playlist->len; ++i) {
        print_composition(playlist->compositions[i]);
    }

    return 0;
}