#include <stdio.h>

#include "composition.h"
#include "playlist.h"

int main() {
    composition_t *composition = create_composition("DDT", 4, 235, 80);
    if (composition == NULL) {
        return -1;
    }
    print_composition(composition);

    playlist_t *playlist = create_playlist(0);
    if (playlist == NULL) {
        return -1;
    }

    add_composition(playlist, composition);
    add_composition(playlist, composition);

    print_composition(playlist->compositions[playlist->len - 1]);
    print_composition(playlist->compositions[playlist->len - 2]);

    delete_composition(composition);
    delete_playlist(playlist);
    return 0;
};