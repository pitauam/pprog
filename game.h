/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "object.h"
#include "player.h"

#define MAX_SPACES 100

typedef struct _Game {
  Player *player;
  Object *object;
  Space *spaces[MAX_SPACES];
  int n_spaces;
  Command *last_cmd;
  Bool finished;
} Game;
/**
 * @brief creates the game, initializing all the variables
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @return OK, if everything goes well
 */
Status game_create(Game *game);

Status game_create_from_file(Game *game, char *filename);

/**
 * @brief deletes the records of commands and deletes the spaces
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_destroy(Game *game);

/**
 * @brief Gets the id of the space
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @param id id of the space
 * @return NULL if somethig goes wrong or the id of the space where the player is
 */
Space *game_get_space(Game *game, Id id);
/**
 * @brief Gets the id of the player location
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @return the id of the space where the player is
 */
Id game_get_player_location(Game *game);

/**
 * @brief Sets the id of the player location
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @param id id of the player location
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief Gets the id of the object location
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @return the id of the space where the object is
 */
Id game_get_object_location(Game *game);

/**
 * @brief Gets the id of the object location
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @param id id of the object location
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_object_location(Game *game, Id id);
/**
 * @brief Gets the last command
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @return the las command of the cmd
 */
Command* game_get_last_command(Game *game);

/**
 * @brief Sets the last command
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @param command pointer to command
 * @return Ok if everything has gone correctly
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief gets if the game is finished
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @return if the game is finished or not
 */
Bool game_get_finished(Game *game);

/**
 * @brief Sets if the game is finished or not
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @param finished structure finished
 * @return Ok if every thing has gone correctly
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief Prints the game
 * @author Profesores PPROG
 *
 * @param game pointer to game
 */
void game_print(Game *game);

/**
 * @brief Adds a new space
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @param space pointer to the new space
 * @return Ok if every thing has gone correctly or ERROR if something was wrong
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief gets the Id of the space where it is
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @param position the number corresponding to the place
 * @return Id of the place if every thing has gone correctly or NO_ID if something was wrong
 */
Id game_get_space_id_at(Game *game, int position);

#endif
