#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <stdio.h>
#include "composition.h"

typedef struct playlist {
    composition_t **compositions;
    size_t len;
    size_t capacity;
} playlist_t;

enum add_comp_errors {
    EMPTY_PLAYLIST_POINTER = 1,
    EMPTY_COMPOSITION_POINTER,
    RESIZING_ERROR,
    COMP_COPY_ERROR
};

playlist_t *create_playlist(size_t start_capacity);
int delete_playlist(playlist_t *playlist);
int add_composition(playlist_t *playlist, composition_t *composition);
int print_playlist(FILE *fd, playlist_t *playlist);
playlist_t *copy_playlist(playlist_t *src);

#endif //PLAYLIST_H
