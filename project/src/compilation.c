#include <stdlib.h>
#include <stdio.h>

#include "compilation.h"
#include "composition.h"
#include "playlist.h"

static int check_composition(composition_t *comp, size_t limit, unsigned int bpm_limit) {
    if (comp == NULL) {
        return 0;
    }

    size_t low_duration_limit = ((int)limit - DURATION_DISPERSION <= 0) ? 0 : limit - DURATION_DISPERSION;
    size_t hight_duration_limit = limit + DURATION_DISPERSION;
    unsigned int low_bpm_limit = ((int)bpm_limit - BPM_DISPERSION <= 0) ? 0 : bpm_limit - BPM_DISPERSION;
    unsigned int hight_bpm_limit = bpm_limit + BPM_DISPERSION;

    size_t comparable_duration = comp->duration;
    size_t comparable_bpm = comp->bpm;

    if (comparable_duration < low_duration_limit || comparable_duration > hight_duration_limit) {
        return 0;
    }

    if (comparable_bpm < low_bpm_limit || comparable_bpm > hight_bpm_limit) {
        return 0;
    }

    return 1;
}

playlist_t *search(playlist_t *src, size_t limit, unsigned int bpm_limit) {
    if (src == NULL || src->compositions == NULL || src->len == 0) {
        return NULL;
    }



    playlist_t *search_res = create_playlist(0);
    for (size_t i = 0; i < src->len; ++i) {
        if (check_composition(src->compositions[i], limit, bpm_limit)) {
            add_composition(search_res, src->compositions[i]);
        }
    }

    return search_res;
}

playlist_t * gen_compilation(playlist_t *src, size_t amount, int seed) {
    if (src->len < amount) {
        return NULL;
    }

    srandom(seed);

    playlist_t *compilation = create_playlist(amount);
    for (size_t i = 0; i < amount; ) {
        unsigned long index = random() % src->len;
        if (src->compositions[index] != NULL) {
            add_composition(compilation, src->compositions[index]);
            delete_composition(src->compositions[index]);
            src->compositions[index] = NULL;
            ++i;
        }
    }

    return compilation;
}
