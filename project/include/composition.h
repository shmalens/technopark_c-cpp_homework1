#ifndef COMPOSITION
#define COMPOSITION

#include <stdio.h>

#define HOUR_MULTIPLIER 3600
#define MIN_MULTIPLIER 60
#define MAX_TITLE_LEN 100

typedef struct song_title{
    size_t title_len;
    char *title;
} song_title_t;

typedef struct duration {
    int hour;
    int min;
    int sec;
    int general_seconds;
} duration_t;

typedef struct composition {
    unsigned int bpm;
    duration_t duration;
    song_title_t title;
} composition_t;

composition_t *create_composition(char *title_buf, size_t title_len, duration_t duration, unsigned bpm);
int delete_composition(composition_t *removable);
int print_composition(composition_t *comp);

#endif //TP1DZ_COMPOSITION_H
