#ifndef COMPILATION_H
#define COMPILATION_H

#include <stddef.h>
#include "playlist.h"

#define DURATION_DISPERSION 10
#define BPM_DISPERSION 2

playlist_t *search(playlist_t *src, size_t limit, unsigned int bpm);
playlist_t * gen_compilation(playlist_t *src, size_t amount, int seed);

#endif //COMPILATION_H
