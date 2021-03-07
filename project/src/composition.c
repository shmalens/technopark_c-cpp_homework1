#include <string.h>
#include <malloc.h>

#include "composition.h"

composition_t *create_composition(char *title_buf, size_t title_len, duration_t duration, unsigned bpm) {

    char *dest_title = malloc(sizeof(char) * title_len);
    if (dest_title == NULL) {
        return NULL;
    }

    composition_t *new_composition = malloc(sizeof(composition_t));
    if (new_composition == NULL) {
        free(dest_title);
        return NULL;
    }

    strncpy(dest_title, title_buf, title_len);
    new_composition->title.title = dest_title;
    new_composition->title.title_len = title_len;
    new_composition->duration = duration;
    new_composition->bpm = bpm;
    return new_composition;
}



int delete_composition(composition_t *removable) {
    if (removable == NULL) {
        return 1;
    }

    free(removable->title.title);
    free(removable);

    removable = NULL;
    return 0;
}

static int print_duration(const duration_t duration) {
    int bytes_written = 0;
    if (duration.hour > 0) {
        bytes_written += printf("%d hours ", duration.hour);
    }

    if (duration.min > 0) {
        bytes_written += printf("%d min ", duration.min);
    }

    if (duration.sec > 0) {
        bytes_written += printf("%d sec", duration.sec);
    }
    return bytes_written;
}

int print_composition(composition_t *comp) {
    if (comp == NULL) {
        return -1;
    }

    int bytes_writen = 0;
    bytes_writen += printf("Composition: %s\n", comp->title.title);
    bytes_writen += printf("Duration: ") + print_duration(comp->duration) + printf("\n");
    bytes_writen += printf("Tempo: %d bpm\n", comp->bpm);

    return bytes_writen;
}
