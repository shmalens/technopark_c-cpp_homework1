#ifndef DATALOADER_H
#define DATALOADER_H

#include "composition.h"
#include "playlist.h"

#define MAX_TITLE_SIZE 100

playlist_t *read_data(FILE *fd);

#endif //DATALOADER_H
