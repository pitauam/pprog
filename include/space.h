/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Samuel Manzorro, Paula de la Fuente, Santiago Pita, Mario Rodriguez
 * @version 4
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "object.h"
#include "set.h"
#include "character.h"


#define GDESC_WIDTH (9+1) /*+1 to store the '\0' character*/
#define GDESC_HEIGHT 5
#define GDESC_SIZE1 5
#define GDESC_SIZE2 10


typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Samuel Manzorro
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space* space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Samuel Manzorro
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space* space);

/**
 * @brief It gets the id of a space
 * @author Samuel Manzorro
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space* space);

/**
 * @brief It sets the name of a space
 * @author Samuel Manzorro
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief It gets the name of a space
 * @author Samuel Manzorro
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
const char* space_get_name(Space* space);

/**
 * @brief It sets the graphic description of a space
 * @author Santiago Pita
 *
 * @param space a pointer to the space
 * @param gdesc graphic description
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_gdesc(Space *space, char *gdesc);

/**
 * @brief It tells if the space has an object or not
 * @author Samuel Manzorro
 * 
 * @param space a pointer to the space
 * @param object_id the id of the object to be found
 * @return TRUE, if the object is in the space, FALSE in other cases
 */
Bool space_find_object(Space* space, Id object_id);

/**
 * @brief It adds an object to the space
 * @author Samuel Manzorro
 * 
 * @param space a pointer to the space
 * @param object_id the id of the object to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_add_object(Space* space, Id object_id);

/**
 * @brief It deletes an object from the space
 * @author Samuel Manzorro
 * 
 * @param space a pointer to the space
 * @param object_id the id of the object to be deleted
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_remove_object(Space* space, Id object_id);


/**
 * @brief It gets the set of objects in the space
 * @author Samuel Manzorro
 * 
 * @param space a pointer to the space
 * @return the set of objects in the space
 */
Set *space_get_objects(Space *space);

/**
 * @brief It sets a space to be discovered or not
 * @author Paula de la Fuente
 *
 * @param space a pointer to the space
 * @param discovered whether the space is discovered or not
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_discovered(Space* space, Bool discovered);

/**
 * @brief It gets whether a space is discovered or not
 * @author Paula de la Fuente
 *
 * @param space a pointer to the space
 * @return TRUE if the space is discovered, FALSE if not
 */
Bool space_is_discovered(Space* space);

/**
 * @brief It gets the number of the objects of the space
 * @author Mario Rodriguez
 *
 * @param space a pointer to the space
 * @return an int with the number of objects in the space
 */
int space_get_n_objects(Space* space);

/**
 * @brief It gets the graphic description of a space
 * @author Santiago Pita
 *
 * @param space a pointer to the space
 * @param line index of the line to be returned (0 to 4)
 * @return graphic description, or NULL if there isn't one
 */
char* space_get_gdesc_line(Space *space, int line);


/**
 * @brief It adds a character to the space
 * @author Santiago Pita
 *
 * @param space a pointer to the space
 * @param id an Id, specifying if in the space there is a character (Id) or not (NO_ID)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_add_character(Space* space, Id id);

/**
 * @brief It removes a character from the space
 * @author Santiago Pita
 *
 * @param space a pointer to the space
 * @param id Id of the character that will be deleted
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_remove_character(Space* space, Id id);

/**
 * @brief It finds the id of a character in a space
 * @author Santiago Pita
 *
 * @param space a pointer to the space
 * @param id id of the character to find
 * @return True if it finds the character, otherwise False
 */
Bool space_find_character(Space* space, Id id);

/**
 * @brief It gets the number of the characters of the space
 * @author Santiago Pita
 *
 * @param space a pointer to the space
 * @return an int with the number of characters in the space
 */
int space_get_n_characters(Space* space);

/**
 * @brief It prints the space information
 * @author Samuel Manzorro
 *
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space* space);

/**
 * @brief returns the set of characters in a space
 * @author Santiago Pita
 *
 * @param space a pointer to the space
 * @return set of characters
 */
Set *space_get_characters(Space *space);

/**
 * @brief returns the character in the i position inside a space
 * @author Santiago Pita
 *
 * @param space a pointer to the space
 * @param i index of the position
 * @return id of the character in that position
 */

Id space_get_character_id_at(Space *space, int i);


#endif
