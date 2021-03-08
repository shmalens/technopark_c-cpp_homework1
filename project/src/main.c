#include <stdio.h>

#include "composition.h"
#include "playlist.h"
#include "dataloader.h"

#define PATH "./data/compositions.txt"

int main() {
    /*composition_t *composition = create_composition("DDT", 4, 235, 80);
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
    add_composition(playlist, composition);
    add_composition(playlist, composition);

    print_playlist(playlist);

    delete_composition(composition);
    delete_playlist(playlist);*/

    FILE *fd = fopen(PATH, "r");

    playlist_t *tmp = read_data(fd);
    if (tmp == NULL) {
        fclose(fd);
        return -1;
    }

    print_playlist(tmp);

    fclose(fd);
    delete_playlist(tmp);
    return 0;
};