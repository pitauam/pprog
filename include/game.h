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
#include "character.h"
#include "link.h"

#define MAX_SPACES 100
#define MAX_PLAYERS 8
#define MAX_OBJECTS 100
#define MAX_CHARACTERS 100
#define MAX_LINKS 400

#define PLAYER_ID 100

/*Defines the struct Game*/
typedef struct _Game Game;

/*Defines the struct InterfaceData*/
typedef struct _InterfaceData InterfaceData;

/**
 * @brief creates the game, initializing all the variables
 * @author Profesores PPROG
 *
 * @return OK, if everything goes well
 */
Game* game_create();

/**
 * @brief deletes the records of commands and deletes the spaces
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @return OK, if everything goes well or ERROR if something went wrong
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
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 * @return the id of the space where the player is
 */
Id game_get_player_location(Game *game);

/**
 * @brief Sets the id of the player location
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 * @param id id of the player location
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief Sets the player who has a turn in the game
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param player pointer to the player that will be stored in the game
 * @return OK if everything goes well or ERROR if there was some mistake
 */
Status game_set_player(Game *game, Player *player);

/**
 * @brief Gets the id of the space where the object is located
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param object_id id of the object to search
 * @return the id of the space where the object is located
 */
Id game_get_object_location(Game *game, Id object_id);

/**
 * @brief Sets the location of an object
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param new_space_id id of the space where the object will be added
 * @param object_id id of the object to add
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_object_location(Game *game, Id new_space_id, Id object_id);

/**
 * @brief Gets the last command
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @return the last command of the cmd
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

/**
 * @brief gets the pointer to the player
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @return pointer of the player if everything has gone correctly or NULL if something was wrong
 */
Player* game_get_player(Game *game);

/**
 * @brief adds an object to the array of pointers to object
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param object pointer to the new object
 * @return Ok if every thing has gone correctly or ERROR if something was wrong
 */
Status game_add_object(Game *game, Object *object);

/**
 * @brief adds a character to the array of pointers to characters
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param character pointer to the new character
 * @return Ok if every thing has gone correctly or ERROR if something was wrong
 */
Status game_add_character(Game *game, Character *character);

/**
 * @brief Gets the pointer of the object said id
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param id id of the object
 * @return pointer to the object or NULL if something went wrong
 */
Object *game_get_object(Game *game, Id id);

/**
 * @brief gets the total number of objects
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @return number of objects or -1 if something went wrong
 */
int game_get_number_of_objects(Game *game);

/**
 * @brief returns the id of an object in the position pos
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param pos position of the object
 * @return the id of the object in said position
 */
Id game_get_object_id(Game *game, int pos);

/**
 * @brief returns the name of an object
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param object pointer to the object
 * @return name of the object
 */
const char* game_get_object_name(Game *game, Object *object);

/**
 * @brief returns the id of a character in the given space
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param id id of the space where the character is
 * @return the id of the character in said space or NO_ID if there is no character
 */
Id game_get_character_id(Game *game, Id id);

/**
 * @brief Gets the id of the space where the character is located
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 * @param id id of the character
 * @return the id of the space where the character is located
*/
Id game_get_character_location(Game *game, Id id);

/**
 * @brief Gets the pointer to a character
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param id id the character
 * @return NULL if something goes wrong or the pointer of the character
 */
Character *game_get_character(Game *game, Id id);

/**
 * @brief gets the total number of characters
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @return number of characters or -1 if something went wrong
 */
int game_get_number_of_characters(Game *game);

/**
 * @brief gets the total number of spaces
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 * @return number of spaces or -1 if something went wrong
 */
int game_get_number_of_spaces(Game *game);

/**
 * @brief sets the mesage in game
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 * @param message of the game
 * @return OK if it went smoothly ERROR otherwise
 */
Status game_set_message(Game *game, const char* message);

/**
 * @brief gets the mesage in game
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 * @return the mesage if it went smoothly NULL otherwise
 */
const char* game_get_message(Game *game);

/**
 * @brief set the name of the messenger
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 * @param name of the messenger
 * @return OK if it went smoothly ERROR otherwise
 */
Status game_set_name_message(Game *game, const char* name);

/**
 * @brief gets the messenger's name
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 * @return the name if it went smoothly NULL otherwise
 */
const char* game_get_name_message(Game *game);

/**
 * @brief gets the id of the destination space
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param id_act id of the current space
 * @param link_direction direction of the link
 * @return the id of the destination space
 */
Id game_get_connection(Game *game, Id id_act, Direction link_direction);

/**
 * @brief gets the if the link is open or not
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param id_act id of the current space
 * @param link_direction direction of the link
 * @return whether the link is open or not
 */
Bool game_connection_is_open(Game *game, Id id_act, Direction link_direction);

/**
 * @brief It adds a link to the array of links
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param link a pointer to the link
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_link(Game *game, Link *link);

/**
 * @brief It gets the number of links in the game
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @return number of links in the game or -1 if there was an error
 */
int game_get_number_of_links(Game *game);

/**
 * @brief It creates a command in the game
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_command_create(Game* game);

/**
 * @brief It gets the current turn in the game
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @return turn of the game, or -1 if there was an error
 */
int game_get_turn(Game *game);

/**
 * @brief It changes the turn to make it the next one
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_next_turn(Game *game);


#endif