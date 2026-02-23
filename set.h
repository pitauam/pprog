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
 * @param value Id to find
 * @return OK if found, ERROR if not found
 */
Status set_find_id(Set* set, Id id); /*no se si poner Status o Id de return*/

/**
 * @brief Prints the Ids inside a set
 * @author Santiago Pita
 *
 * @param set pointer to the set structure
 * @param value Id to find
 * @return OK if found, ERROR if not found
 */
Status set_print(Set *set, FILE *pf); /*le paso FILE *pf o lo imrpimo en pantalla directamene?*/


/**
 * @brief gets the number of ids in a set
 * @author Santiago Pita
 *
 * @param set pointer to the set structure
 * @return number of sets it ok, -1 if error
 */
int set_get_n_ids(Set *set);


#endif
