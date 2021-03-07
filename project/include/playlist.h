#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "composition.h"

typedef struct playlist {
    composition_t **playlist;
    int len;
} playlist_t;

playlist_t *create_playlist(FILE *fd);
int delete_playlist(playlist_t *playlist);
int print_playlist(playlist_t *playlist);

#endif //PLAYLIST_H
