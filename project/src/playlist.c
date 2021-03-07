#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "playlist.h"
#include "composition.h"

static playlist_t *delete_incomplete_playlist(playlist_t *playlist, int len) {
    if (playlist == NULL) {
        return NULL;
    }

    for (int j = 0; j < len; ++j) {
        delete_composition(playlist->playlist[j]);
        playlist->playlist[j] = NULL;
    }
    free(playlist->playlist);
    free(playlist);
    playlist = NULL;
    return NULL;
}

static int fill_playlist(FILE *fd, playlist_t *new_playlist) {
    // Читаем композиции
    for (int i = 0; i < new_playlist->len; ++i) {
        char title[MAX_TITLE_LEN];
        if(fgets(title, MAX_TITLE_LEN, fd) == NULL) {
            return i;
        }
        // Убираем \n в конце строки и получаем длину
        size_t title_len = strlen(title);
        title[title_len - 1] = '\0';

        duration_t duration;
        if(fscanf(fd, "%d%*c%d%*c%d\n", &duration.hour, &duration.min, &duration.sec) == 0) {
            return i;
        }
        duration.general_seconds = duration.hour * HOUR_MULTIPLIER + duration.min * MIN_MULTIPLIER + duration.sec;

        unsigned int bpm;
        if(fscanf(fd, "%d\n", &bpm) == 0) {
            return i;
        }

        // Добавляем в плейлист
        new_playlist->playlist[i] = create_composition(title, title_len, duration, bpm);
        if (new_playlist->playlist[i] == NULL) {
            return i;
        }
    }

    return 0;
}

playlist_t *create_playlist(FILE *fd) {
    if (fd == NULL) {
        return NULL;
    }

    // Читаем кол-во композиций в файле
    int playlist_length;
    if (fscanf(fd, "%d\n", &playlist_length) == 0) {
        return NULL;
    }

    // Выделяем память под плейлист, задаем ему длину и память под его композиции
    playlist_t *new_playlist = malloc(sizeof(playlist_t));
    if (new_playlist == NULL) {
        return NULL;
    }
    new_playlist->len = playlist_length;
    new_playlist->playlist = malloc(sizeof(composition_t) * playlist_length);
    if (new_playlist->playlist == NULL) {
        return delete_incomplete_playlist(new_playlist, 0);
    }

    int err = fill_playlist(fd, new_playlist);
    if (err != 0) {
        return delete_incomplete_playlist(new_playlist, err);
    }

    return new_playlist;
}

int delete_playlist(playlist_t *playlist) {
    if (playlist == NULL) {
        return -1;
    }

    for (int i = 0; i < playlist->len; ++i) {
        delete_composition(playlist->playlist[i]);
    }
    free(playlist->playlist);
    free(playlist);

    playlist = NULL;
    return 0;
}

int print_playlist(playlist_t *playlist) {
    if (playlist == NULL) {
        return -1;
    }

    int bytes_written = 0;
    for (int i = 0; i < playlist->len; ++i) {
        bytes_written += print_composition(playlist->playlist[i]);
    }
    return bytes_written;
}

