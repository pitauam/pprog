/**
 * @brief Implements the link module
 *
 * @file link.c
 * @author Santiago Pita
 * @version 1
 * @date 23-03-2026
 */

#include "link.h"

#include <stdio.h>
#include <stdlib.h>

struct _Link{
  Id id;                           /*!< Id number of the link, it must be unique */
  char name[WORD_SIZE + 1];        /*!< Name of the link */

  Id origin;                       /*!< Id of the previous space where the player came from */
  Id destination;                  /*!< Id of the destination space where the player is going to */
  Direction direction;             /*!< Direction of how the link is made, whether the connection is established from north, south, east or west */
  Bool open;                       /*!< Whether the connection between origin and destination spaces is open or not*/
};

Link* link_create(Id id);

Status link_destroy(Link* link);

Status link_set_name(Link* link, char* name);

const char* link_get_name(Link* link);

Status link_set_origin(Link* link, Id id);

Id link_get_origin(Link* link);

Status link_set_destination(Link* link, Id id);

Id link_get_destination(Link* link);

Status link_set_direction(Link* link, Direction direction);

Id link_get_direction(Link* link);

Status link_set_open(Link* link, Bool bool);

Id link_get_open(Link* link);
