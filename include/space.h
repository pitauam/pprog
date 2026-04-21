/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 2
 * @date 24-02-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space* space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space* space);

/**
 * @brief It gets the id of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space* space);

/**
 * @brief It sets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief It gets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
const char* space_get_name(Space* space);

/**
 * @brief It adds a object to the space
 * @author Mario Rodriguez
 *
 * @param space a pointer to the space
 * @param id an Id, specifying if in the space there is an object (Id) or not (NO_ID)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_add_object(Space* space, Id id);

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
 * @brief It removes an object from the space
 * @author Mario Rodriguez
 *
 * @param space a pointer to the space
 * @param id Id of the object that will be deleted
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_remove_object(Space* space, Id id);

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
 * @brief It finds the id of an object in a space
 * @author Mario Rodriguez
 *
 * @param space a pointer to the space
 * @param id id of the object you want to find
 * @return True if it finds the object, otherwise False
 */
Bool space_find_object(Space* space, Id id);

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
 * @brief It gets the number of the objects of the space
 * @author Mario Rodriguez
 *
 * @param space a pointer to the space
 * @return an int with the number of objects in the space
 */
int space_get_n_objects(Space* space);

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
 * @author Profesores PPROG
 *
 * This fucntion shows the id and name of the space, the spaces that surrounds it and wheter it has an object or not.
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space* space);

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
 * @brief It gets the graphic description of a space
 * @author Santiago Pita
 *
 * @param space a pointer to the space
 * @param line index of the line to be returned (0 to 4)
 * @return graphic description, or NULL if there isn't one
 */
char* space_get_gdesc_line(Space *space, int line);

#endif