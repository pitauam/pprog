/**
 * @brief Set module
 *
 * @file set.h
 * @author Santiago Pita
 * @version 0
 * @date 17-02-2026
 */

#ifndef SET_H
#define SET_H

#include "types.h"
#include <stdio.h>

typedef struct _Set Set;

/**
 * @brief Creates a new set, allocating memory and initialazing all of its parameters
 * @author Santiago Pita
 *
 * @return a new initialized Set
 */
Set* set_create();


/**
 * @brief Destroys a new set, freeing its memory
 * @author Santiago Pita
 *
 * @param set pointer to the set structure to destroy
 * @return OK if success ERROR if error
 */
Status set_destroy(Set* set);


/**
 * @brief Adds a value to a set
 * @author Santiago Pita
 *
 * @param set pointer to the set structure
 * @param value Id to add 
 * @return OK if success ERROR if error
 */
Status set_add_value(Set* set, Id value);


/**
 * @brief Deletes a value from a set
 * @author Santiago Pita
 *
 * @param set pointer to the set structure
 * @param value Id to remove
 * @return OK if success ERROR if error
 */
Status set_del_value(Set* set, Id value);


/**
 * @brief Finds an id inside a set
 * @author Santiago Pita
 *
 * @param set pointer to the set structure
 * @param id Id to find
 * @return OK if found, ERROR if not found
 */
Status set_find_id(Set* set, Id id); 


/**
 * @brief Prints the Ids inside a set
 * @author Santiago Pita
 *
 * @param set pointer to the set structure
 * @return OK if print went well, ERROR if function couldn't print
 */
Status set_print(Set *set);


/**
 * @brief gets the number of ids in a set
 * @author Santiago Pita
 *
 * @param set pointer to the set structure
 * @return number of ids in the set, or -1 if error
 */
int set_get_n_ids(Set *set);

/**
 * @brief gets the id in a set position
 * @author Mario Rodriguez
 *
 * @param set pointer to the set structure
 * @param pos position in the array
 * @return gets the id of that pos
 */
Id set_get_id(Set *set, int pos);

#endif
