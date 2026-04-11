/**
 * @brief Defines the module "player"
 *
 * @file player.h
 * @author Mario Rodriguez
 * @version 0
 * @date 03-02-2026
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
 * @brief gets the name of the player
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
 * @brief Sets the maximum number of objects the player can carry in his backpack
 * @author Santiago Pita
 *
 * @param player pointer to the structure of the player
 * @param max_objects maximum backpack size
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status player_set_max_objects(Player *player, int max_objects);

/**
 * @brief Gives the location of the player
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @return Id of the location of the player
 */
Id player_get_location(Player* player);

/**
 * @brief adds an object to the players inventory
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @param id id of the object
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status player_add_object(Player* player, Id id);

/**
 * @brief removes an object from the players inventory
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @param id id of the object
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status player_remove_object(Player* player, Id id);

/**
 * @brief gets the number of objects in the backpack
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @return n_objects if everything goes well, -1 if something went wrong
 */
int player_get_n_objects(Player* player);

/**
 * @brief Gets the player object
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @return OK if everything goes well, ERROR if something went wrong
 */
Id player_get_object_id(Player* player, int pos);

/**
 * @brief Gets if the players inventory is empty
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @return TRUE if empty, FALSE otherwise
 */
Bool player_inventory_empty(Player* player);

/**
 * @brief Gets if the players inventory is full
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @return TRUE if full, FALSE otherwise
 */
Bool player_inventory_full(Player* player);

/**
 * @brief Finds id the player has an object with id(id)
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @param id id of the object
 * @return id of the object the player is carrying
 */
Status player_find_object(Player* player, Id id);

/**
 * @brief sets the desription of the player
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @param descrp description on the player
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status player_set_description(Player *player, char *descrp);

/**
 * @brief gets the description of the player
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @return a string with the player's description
 */
const char *player_get_description(Player *player);

/**
 * @brief sets the health of the player
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @param heatlh int with the hp of the player
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status player_set_health(Player *player, int health);

/**
 * @brief gets the health of the player
 * @author Mario Rodriguez
 *
 * @param player pointer to the structure of the player
 * @return int with the player's health
 */
int player_get_health(Player *player);

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