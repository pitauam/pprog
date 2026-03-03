#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
 * @brief loads the spaces of the game
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @param filename pointer to a tring with the file name
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_load_spaces(Game *game, char *filename);

/**
 * @brief reeds the file and creates the game based on the information
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @param filename pointer to a tring with the file name
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Game* game_reader_create_from_file(char *filename);

/**
 * @brief loads the spaces of the game
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 * @param filename pointer to a tring with the file name
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_load_objects(Game *game, char *filename);

#endif