#include <stdio.h>

#include "composition.h"
#include "playlist.h"

#define TITLE "Pink Floyd - Another brick in the wall"
#define TITLE_LEN 38 + 1
#define HOURS 0
#define MIN 3
#define SEC 50
#define GENERAL_SEC 230
#define TEMPO 130

int main() {
    /*duration_t test_duration = {.hour = HOURS, .min = MIN, .sec = SEC, .general_seconds = GENERAL_SEC};
    char test_title[] = TITLE;
    size_t test_title_len = TITLE_LEN;
    unsigned int test_tempo = TEMPO;

    composition_t *test_composition = create_composition(test_title, test_title_len, test_duration, test_tempo);
    if (test_composition == NULL) {
        printf("Error creating composition\n");
        return -1;
    }

    int written_bytes = print_composition(test_composition);
    printf("bytes written: %d\n", written_bytes);

    delete_composition(test_composition);*/
    FILE *fd = fopen("./data/compositions.txt", "r");
    if (fd == NULL) {
        return -1;
    }

    playlist_t *playlist = create_playlist(fd);
    if (playlist == NULL) {
        fprintf(stderr, "Error creating playlist\n");
        fclose(fd);
        return -1;
    }

    print_playlist(playlist);

    delete_playlist(playlist);
    fclose(fd);
    return 0;
}
