#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"
#include "game_reader.h"

/**
 * @brief loads the spaces of the game
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @param filename pointer to a tring with the file name
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_load_spaces(Game *game, char *filename);

/**
 * @brief reeds the file and creates the game based on the information
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @param filename pointer to a tring with the file name
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Game* game_create_from_file(char *filename);


#endif