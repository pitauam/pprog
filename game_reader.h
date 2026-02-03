#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

Status game_load_spaces(Game *game, char *filename);

Status game_create_from_file(Game *game, char *filename);


#endif