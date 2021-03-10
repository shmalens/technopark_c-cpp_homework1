#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "composition.h"

composition_t *create_composition(const char *title, size_t title_len, size_t duration, unsigned int bpm) {
    if (title == NULL) {
        return NULL;
    }

    char *new_comp_title = malloc(sizeof(char) * title_len);
    if (new_comp_title == NULL) {
        return NULL;
    }

    composition_t *new_composition = malloc(sizeof(composition_t));
    new_comp_title = strncpy(new_comp_title, title, title_len);
    new_composition->title.title = new_comp_title;
    new_composition->title.len = title_len;
    new_composition->duration = duration;
    new_composition->bpm = bpm;

    return new_composition;
}

int delete_composition(composition_t *composition) {
    if (composition == NULL) {
        return -1;
    }

    free(composition->title.title);
    free(composition);
    return 0;
}

int print_composition(composition_t *composition) {
    if (composition == NULL) {
        return -1;
    }

    printf("Title: %s\n", composition->title.title);
    printf("Duration: %lu\n", (unsigned long)composition->duration);
    printf("BPM: %u\n", composition->bpm);
    return 0;
}

composition_t *composition_cpy(composition_t *src) {
    if (src == NULL) {
        return NULL;
    }

    composition_t *dest = create_composition(src->title.title, src->title.len, src->duration, src->bpm);
    if (dest == NULL) {
        return NULL;
    }

    return dest;
}
