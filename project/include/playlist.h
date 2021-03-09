#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "composition.h"

typedef struct playlist {
    composition_t **compositions;
    size_t len;
    size_t capacity;
} playlist_t;

playlist_t *create_playlist(size_t start_capacity);
int delete_playlist(playlist_t *playlist);
int add_composition(playlist_t *playlist, composition_t *composition);
int print_playlist(playlist_t *playlist);
playlist_t *copy_playlist(playlist_t *src);

#endif //PLAYLIST_H
