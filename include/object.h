/**
 * @brief Defines the module "object"
 *
 * @file object.h
 * @author Santiago Pita and Marta López
 * @version 0
 * @date 27-04-2026
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
 * @brief Gives the name of an object
 * @author Santiago Pita
 *
 * @param object pointer to the structure of the object
 * @return a string with the name of an object
 */
const char* object_get_name(Object* object);

/**
 * @brief Sets the description of an object
 * @author Fernando Pina
 *
 * @param object pointer to the structure of the object
 * @param desc pointer to the name of the object
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status object_set_desc(Object* object, char* desc);

/**
 * @brief Gives the description of an object
 * @author Fernando Pina
 *
 * @param object pointer to the structure of the object
 * @return a string with the name of an object
 */
const char* object_get_desc(Object* object);

/**
 * @brief Sets the health of the object
 * @author Marta López
 *
 * @param object pointer to the structure of the object
 * @param health the amount it takes or gives
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status object_set_health(Object* object, int health);

/**
 * @brief Gives the health of an object
 * @author Marta López
 *
 * @param object pointer to the structure of the object
 * @return the health of an object
 */
int object_get_health(Object* object);

/**
 * @brief Sets if an object is movable or not
 * @author Marta López
 *
 * @param object pointer to the structure of the object
 * @param movable true or false
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status object_set_movable(Object* object, Bool movable);

/**
 * @brief Gets if it's movable or not
 * @author Marta López
 *
 * @param object pointer to the structure of the object
 * @return TRUE if movable and FALSE if not
 */
Bool object_get_movable(Object* object);

/**
 * @brief Sets the dependency of the object
 * @author Marta López
 *
 * @param object pointer to the structure of the object
 * @param dependency id of the object that the object depends on
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status object_set_dependency(Object* object, Id dependency);

/**
 * @brief Gets the dependency of the object
 * @author Marta López
 *
 * @param object pointer to the structure of the object
 * @return Id of the dependency or NO_ID if error
 */
Id object_get_dependency(Object* object);

/**
 * @brief Sets if it's open to get it or closed
 * @author Marta López
 *
 * @param object pointer to the structure of the object
 * @param open id to define it
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status object_set_open(Object* object, Bool open);

/**
 * @brief Gets if it's open or not
 * @author Marta López
 *
 * @param object pointer to the structure of the object
 * @return TRUE if open and FALSE if not
 */
Id object_get_open(Object* object);

/**
 * @brief Sets the category of the object
 * @author Marta López
 *
 * @param object pointer to the structure of the object and category of the object
 * @return TRUE if open and FALSE if not
 */
Status object_set_category(Object* object, Category category);

/**
 * @brief Gets the category of the object
 * @author Marta López
 *
 * @param object pointer to the structure of the object
 * @return NO_CAT if error and Venom, Elixir, Strenght or Cursed depending on the object
 */
Category object_get_category(Object* object);

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