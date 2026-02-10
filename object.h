/**
 * @brief Defines the module "object"
 *
 * @file object.h
 * @author Santiago Pita
 * @version 0
 * @date 03-01-2026
 * @copyright GNU Public License
 */
#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object;

/**
 * @brief Creates a new object, allocating memory and initialazing all of its parameters
 * @author Santiago Pita
 *
 * @param id identification number of the object
 * @return a new initialized object
 */
Object* object_create(Id id);

/**
 * @brief Destroys an object, freeing its memory
 * @author Santiago Pita
 *
 * @param object pointer to the structure of the object to destroy
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status object_destroy(Object* object);

/**
 * @brief Gives the id of an object
 * @author Santiago Pita
 *
 * @param object pointer to the structure of the object
 * @return Object's id
 */
Id object_get_id(Object* object);

/**
 * @brief Sets the name of an object
 * @author Santiago Pita
 *
 * @param object pointer to the structure of the object
 * @param name pointer to the name of the object
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status object_set_name(Object* object, char* name);

/**
 * @brief Gives the id of an object
 * @author Santiago Pita
 *
 * @param object pointer to the structure of the object
 * @return a string with the name of an object
 */
const char* object_get_name(Object* object);

/**
 * @brief Prints the information of an object (shows its Id)
 * @author Santiago Pita
 *
 * 
 * @param object pointer to the structure of the object
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status object_print(Object* object);

#endif