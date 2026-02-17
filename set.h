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
 * @param value number to add 
 * @return OK if success ERROR if error
 */
Status set_add_value(Set* set, Id value);

Status set_del_value(Set* set, Id value);

Id set_find_id(Set* set, Id id);

Status set_print(Set *set);


#endif
