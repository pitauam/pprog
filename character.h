/**
 * @brief Defines the module "character"
 *
 * @file character.h
 * @author Mario Rodriguez
 * @version 0
 * @date 17-02-2026
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

typedef struct _Character Character;

/**
 * @brief Creates a new Character, allocating memory and initialazing all of its parameters
 * @author Mario Rodriguez
 *
 * @param id identification number of the character
 * @return a new initialized character
 */
Character *character_create(Id id);

/**
 * @brief destroys a character, liberating its memory
 * @author Mario Rodriguez
 *
 * @param character pointer to the structure of a character
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status character_desrtoy(Character *character);
/**
 * @brief gets the id of a character
 * @author Mario Rodriguez
 *
 * @param character pointer to the structure of a character
 * @return the id of the character
 */
Id character_get_Id(Character *character);

/**
 * @brief Sets the name of a character
 * @author Mario Rodriguez
 *
 * @param character pointer to the structure of the character
 * @param name pointer to the name of the character
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status character_set_name(Character *character, char *name);

/**
 * @brief gets the name of the character
 * @author Mario Rodriguez
 *
 * @param character pointer to the structure of the character
 * @return a string with the character's name
 */
const char* character_get_name(Character *character);

/**
 * @brief sets the desription of the character
 * @author Mario Rodriguez
 *
 * @param character pointer to the structure of the character
 * @param descrp description on the character
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status character_set_description(Character *character, char *descrp);

/**
 * @brief gets the description of the character
 * @author Mario Rodriguez
 *
 * @param character pointer to the structure of the character
 * @return a string with the character's description
 */
const char *character_get_description(Character *character);

/**
 * @brief sets the health of the character
 * @author Mario Rodriguez
 *
 * @param character pointer to the structure of the character
 * @param heatlh int with the hp of the character
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status character_set_health(Character *character, int health);

/**
 * @brief gets the health of the character
 * @author Mario Rodriguez
 *
 * @param character pointer to the structure of the character
 * @return int with the player's health
 */
int character_get_health(Character *character);
/**
 * @brief sets if the character is friendly ot nor
 * @author Mario Rodriguez
 *
 * @param character pointer to the structure of the character
 * @param fiendly int with the state of the character
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status character_set_friendly(Character *character, int friendly);
/**
 * @brief gets if the character is friendly ot nor
 * @author Mario Rodriguez
 *
 * @param character pointer to the structure of the character
 * @param fiendly int with the state of the character
 * @return if its friendly
 */
Bool Character_get_friendly();

/**
 * @brief sets the message of the character
 * @author Mario Rodriguez
 *
 * @param character pointer to the structure of the character
 * @param message mesage of the character
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status character_set_message(Character *character, char *message);

const char *character_get_message(Character *character);




#endif