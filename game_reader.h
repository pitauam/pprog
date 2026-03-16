#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
 * @brief reeds the file and creates the game based on the information
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @param filename pointer to a tring with the file name
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Game* game_reader_create_from_file(char *filename);

#endif