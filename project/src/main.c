#include <stdio.h>
#include <stdlib.h>

#include "playlist.h"
#include "dataloader.h"
#include "compilation.h"

#define PATH "./data/compositions.txt"

int main() {
    FILE *fd = fopen(PATH, "r");

    playlist_t *tmp = read_data(fd);
    if (tmp == NULL) {
        fclose(fd);
        return -1;
    }

    print_playlist(tmp);
    printf("-------------------------------\n");

    playlist_t *s_tmp = search(tmp, 210, 100);
    if (s_tmp == NULL) {
        delete_playlist(tmp);
        fclose(fd);
        return -1;
    }
    print_playlist(s_tmp);

    printf("---------------------------------\n");
    playlist_t *c_tmp = gen_compilation(s_tmp, 4, 1);
    if (c_tmp == NULL) {
        fclose(fd);
        delete_playlist(tmp);
        delete_playlist(s_tmp);
        return -1;
    }
    print_playlist(c_tmp);


    fclose(fd);
    delete_playlist(tmp);
    delete_playlist(c_tmp);
    delete_playlist(s_tmp);


    return 0;
};
