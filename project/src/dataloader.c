#include <stdio.h>
#include <string.h>

#include "dataloader.h"
#include "composition.h"
#include "playlist.h"

static composition_t *read_comp_data(FILE *fd) {
    if (fd == NULL) {
        return NULL;
    }

    char title_buffer[MAX_TITLE_SIZE];
    size_t title_len = 0;
    if(fgets(title_buffer, MAX_TITLE_SIZE, fd) == 0) {
        return NULL;
    }
    title_len = strlen(title_buffer);
    title_buffer[title_len - 1] = '\0';

    unsigned long duration;
    if (fscanf(fd, "%lu\n", &duration) == 0) {
        return NULL;
    }

    unsigned int bpm;
    if (fscanf(fd, "%u\n", &bpm) == 0) {
        return NULL;
    }

    composition_t *tmp = create_composition(title_buffer, title_len, duration, bpm);
    if (tmp == NULL) {
        return NULL;
    }

    return tmp;
}

playlist_t *read_data(FILE *fd) {
    if (fd == NULL) {
        return NULL;
    }

    int amount;
    if (fscanf(fd, "%d\n", &amount) == 0) {
        return NULL;
    }

    if (amount <= 0) {
        return NULL;
    }

    playlist_t *new_playlist = create_playlist(amount);
    for (int i = 0; i < amount; ++i) {
        composition_t *tmp = read_comp_data(fd);
        if (tmp == NULL) {
            delete_playlist(new_playlist);
            return NULL;
        }

        int err = add_composition(new_playlist, tmp);
        if (err != 0) {
            delete_playlist(new_playlist);
            delete_composition(tmp);
            return NULL;
        }

        delete_composition(tmp);
    }

    return new_playlist;
}

int get_user_input(FILE *fd, size_t *len, size_t *duration, unsigned int *bpm) {
    if (fd == NULL) {
        return EMPTY_FILE_POINTER;
    }

    if (duration == NULL) {
        return EMPTY_DURATION_POINTER;
    }

    if (bpm == NULL) {
        return EMPTY_BPM_POINTER;
    }

    if (len == NULL) {
        return EMPTY_LEN_POINTER;
    }

    long buf_len;
    printf("Enter length of compilation (The number is greater than zero): ");
    int err = fscanf(fd, "%ld", &buf_len);
    if (err < 1 || buf_len <= 0) {
        return WRONG_COMPILATION_LEN;
    }
    *len = buf_len;

    long buf_hour;
    long buf_min;
    long buf_sec;
    printf("Enter duration (Usage hh:mm:ss, the numbers is greater than zero): ");
    err = fscanf(fd, "%ld%*c%ld%*c%ld", &buf_hour, &buf_min, &buf_sec);
    if (err < 3 || buf_hour < 0 || buf_min < 0 || buf_min > 60 || buf_sec < 0 || buf_sec > 60) {
        return WRONG_DURATION_INPUT;
    }
    *duration = (size_t) buf_hour * HOUR_MULTIPLIER + buf_min * MIN_MULTIPLIER + buf_sec;

    int buf_bpm;
    printf("Enter tempo (The number is greater than zero): ");
    err = fscanf(fd, "%d", &buf_bpm);
    if (err < 1 || buf_bpm < 0) {
        return WRONG_BPM_INPUT;
    }
    *bpm = buf_bpm;

    return 0;
}


