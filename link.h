/**
 * @brief Defines the link.h module
 *
 * @file link.h
 * @author Santiago Pita
 * @version 1
 * @date 23-03-2026
 */

#ifndef LINK_H
#define LINK_H


#include "types.h"


typedef struct _Link Link;

/**
 * @brief It creates a new link, allocating memory and initializing its members
 * @author Santiago Pita
 *
 * @param id the identification number for the new link
 * @return a new link, initialized with the id given
 */
Link* link_create(Id id);

/**
 * @brief It destroys a link, freeing the allocated memory
 * @author Santiago Pita
 *
 * @param link a pointer to the link that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_destroy(Link* link);

/**
 * @brief It sets the name of a link
 * @author Santiago Pita
 *
 * @param link a pointer to the link
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_name(Link* link, char* name);

/**
 * @brief It gets the name of a link
 * @author Santiago Pita
 *
 * @param link a pointer to the link
 * @return  a string with the name of the link
 */
const char* link_get_name(Link* link);

/**
 * @brief It sets the id of the space of origin
 * @author Santiago Pita
 *
 * @param link a pointer to the link
 * @param id the id number of the origin space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_origin(Link* link, Id id);

/**
 * @brief It gets the id of the space of origin
 * @author Santiago Pita
 *
 * @param link a pointer to the link
 * @return the id number of the origin space
 */
Id link_get_origin(Link* link);

/**
 * @brief It sets the id of the space of destination
 * @author Santiago Pita
 *
 * @param link a pointer to the link
 * @param id the id number of the destination space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_destination(Link* link, Id id);

/**
 * @brief It gets the id of the space of destination
 * @author Santiago Pita
 *
 * @param link a pointer to the link
 * @return the id number of the destination space
 */
Id link_get_destination(Link* link);

/**
 * @brief It sets the direction of the link between the origin and destination spaces
 * @author Santiago Pita
 *
 * @param link a pointer to the link
 * @param direction the direction of the link (N,S,E,W)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_direction(Link* link, Direction direction);

/**
 * @brief It gets the direction of the link between the origin and destination spaces
 * @author Santiago Pita
 *
 * @param link a pointer to the link
 * @return the direction of the link (N,S,E,W)
 */
Id link_get_direction(Link* link);

/**
 * @brief It sets the open parameter of the link to true or false
 * @author Santiago Pita
 *
 * @param link a pointer to the link
 * @param bool whether the link is open (true) or closed (false)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_open(Link* link, Bool bool);

/**
 * @brief It gets the open parameter of the link
 * @author Santiago Pita
 *
 * @param link a pointer to the link
 * @return whether the link is open (true) or closed (false)
 */
Bool link_get_open(Link* link);

/**
 * @brief It prints the link information
 * @author Santiago Pita
 *
 * This fucntion shows the id and name of the link, the origin and destination spaces and whether it is open or not.
 * @param link a pointer to the link
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_print(Link* space);

#endif