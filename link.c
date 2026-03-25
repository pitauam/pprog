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
#include <string.h>

struct _Link{
  Id id;                           /*!< Id number of the link, it must be unique */
  char name[WORD_SIZE + 1];        /*!< Name of the link */

  Id origin;                       /*!< Id of the previous space where the player came from */
  Id destination;                  /*!< Id of the destination space where the player is going to */
  Direction direction;             /*!< Direction of how the link is made, whether the connection is established from north, south, east or west */
  Bool open;                       /*!< Whether the connection between origin and destination spaces is open or not*/
};

Link* link_create(Id id){
  Link* new_link = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  new_link = (Link*)calloc(1, sizeof(Link));
  if (new_link == NULL) {
    return NULL;
  }

  /* Initialization of an empty link*/
  new_link->id = id;
  new_link->name[0] = '\0';
  new_link->origin = NO_ID;
  new_link->destination = NO_ID;
  new_link->direction = NO_DIR;  
  new_link->open = FALSE;           /*defaults to closed link*/

  return new_link;
}

Status link_destroy(Link* link){
    if (!link) {
    return ERROR;
    }

  free(link);

  return OK;
}

Status link_set_name(Link* link, char* name){
  if (!link || !name) {
    return ERROR;
  }

  if (!strcpy(link->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* link_get_name(Link* link){
  if (!link) {
    return NULL;
  }
  return link->name;
}

Status link_set_origin(Link* link, Id id){
  if (!link) {
    return ERROR;
  }
  link->origin = id;
  return OK;
}

Id link_get_origin(Link* link){
  if (!link) {
    return NO_ID;
  }
  return link->origin;
}

Status link_set_destination(Link* link, Id id){
  if (!link) {
    return ERROR;
  }
  link->destination = id;
  return OK;
}

Id link_get_destination(Link* link){
  if (!link) {
    return NO_ID;
  }
  return link->destination;
}

Status link_set_direction(Link* link, Direction direction){
  if (!link) {
    return ERROR;
  }
  link->direction = direction;
  return OK;
}

Id link_get_direction(Link* link){
  if (!link) {
    return NO_ID;
  }
  return link->direction;
}

Status link_set_open(Link* link, Bool bool){
  if (!link) {
    return ERROR;
  }
  link->open = bool;
  return OK;
}

Bool link_get_open(Link* link){
  if (!link) {
    return FALSE;
  }
  return link->open;
}

Status link_print(Link* link){
    Id idaux = NO_ID;
    Bool b;

    if (!link){
        return ERROR;
    }

    /* 1. Print the id and the name of the Link */
    fprintf(stdout, "--> Link (Id: %ld; Name: %s)\n", link->id, link->name);

    /* 2. For each direction, print its link */
    idaux = link_get_origin(link);
    if (idaux != NO_ID) {
      fprintf(stdout, "---> Origin link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No origin link.\n");
    }

    idaux = link_get_destination(link);
    if (idaux != NO_ID) {
        fprintf(stdout, "---> Destination link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No destination link.\n");
    }
  
    idaux = link_get_direction(link);
    if (idaux != NO_DIR) {
        fprintf(stdout, "---> Direction of the link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No direction in the link.\n");
    }

    b = link_get_open(link);
    if (b == TRUE) {
        fprintf(stdout, "---> Link is open\n");
    } else {
        fprintf(stdout, "---> Link is not open.\n");
    }

  return OK;
}
