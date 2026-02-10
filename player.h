/**
 * @brief Defines the module "player"
 *
 * @file player.h
 * @author Mario Rodriguez
 * @version 0
 * @date 03-01-2026
 * @copyright GNU Public License
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

typedef struct _Player Player;

/**
 * @brief Creates a new player, allocating memory and initialazing all of its parameters
 * @author Mario Rodriguez
 *
 * @param id identification number of the player
 * @return a new initialized player
 */
Player* player_create(Id id);

/**
 * @brief Destroys a player, freeing its memory
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player to destroy
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status player_destroy(Player* player);

/**
 * @brief Gives the id of a player
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @return Player's id
 */
Id player_get_id(Player* player);

/**
 * @brief Sets the name of a player
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @param name pointer to the name of the player
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief Gives the id of a player
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @return a string with the player's name
 */
const char* player_get_name(Player* player);

/**
 * @brief Sets the location of the player
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @param id Id of the location of the player
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status player_set_location(Player* player, Id id);

/**
 * @brief Gives the location of the player
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @return Id of the location of the player
 */
Id player_get_location(Player* player);

/**
 * @brief Sets an object to the player
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @param id id of the object
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status player_set_object(Player* player, Id id);

/**
 * @brief Sets the location of the player
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @return id of the player
 */
Id player_get_object(Player* player);

/**
 * @brief Prints information about the player
 * @author Mario Rodriguez
 *
 * This function shows the id-name-location and the object of the player if it has one
 * 
 * @param player pointer to the structure of the player
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status player_print(Player* player);
#endif
