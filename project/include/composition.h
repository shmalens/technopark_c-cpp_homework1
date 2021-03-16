#ifndef COMPOSITION_H
#define COMPOSITION_H

#include <stdio.h>

typedef struct title {
    char *title;
    size_t len;
} title_t;

typedef struct composition {
    title_t title;
    size_t duration;
    unsigned int bpm;
} composition_t;

composition_t *create_composition(const char *title, size_t title_len, size_t duration, unsigned int bpm);
int delete_composition(composition_t *composition);
int print_composition(FILE *fd, composition_t *composition);
composition_t *composition_cpy(composition_t *src);

#endif //COMPOSITION_H
