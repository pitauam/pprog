/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG
 * @version 1
 * @date 09-02-2026
 * @copyright GNU Public License
 */

#include "space.h"
#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space {
  Id id;                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  Id north;                 /*!< Id of the space at the north */
  Id south;                 /*!< Id of the space at the south */
  Id east;                  /*!< Id of the space at the east */
  Id west;                  /*!< Id of the space at the west */
  Set *objects;         /*!< Stores the Id of an object. NO_ID (-1) means there is no object in the player*/
};

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Space* space_create(Id id) {
  Space* new_space = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  new_space = (Space*)calloc(1, sizeof(Space));
  if (new_space == NULL) {
    return NULL;
  }

  /* Initialization of an empty space*/
  new_space->id = id;
  new_space->name[0] = '\0';
  new_space->north = NO_ID;
  new_space->south = NO_ID;
  new_space->east = NO_ID;
  new_space->west = NO_ID;
  new_space->objects = set_create();

  return new_space;
}

Status space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  free(space->objects);
  free(space);

  return OK;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

Status space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

Status space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

Status space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

Status space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

Status space_add_object(Space* space, Id id) {
  if (space == NULL || space->objects == NULL || id == NO_ID) {
    return ERROR;
  }
  if(set_find_id(space->objects, id)){
    return ERROR;
  }
  set_add_value(space->objects, id);

  return OK;
}
Status space_remove_object(Space* space, Id id) {
  if (space == NULL || space->objects == NULL || id == NO_ID) {
    return ERROR;
  }
  if(set_find_id(space->objects, id)){
    set_del_value(space->objects, id);
    return OK;
  }

  return ERROR;
}

Set* space_get_objects(Space* space) {
  if (space == NULL || space->objects == NULL) {
    return NULL;
  }

  return space->objects;
}

Status space_print(Space* space) {
  Id idaux = NO_ID;
  int i;
  /* Error Control */
  if (!space) {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 2. For each direction, print its link */
  idaux = space_get_north(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Print if there is an object in the space or not */
  if (space_get_objects(space) == NULL) {
    for(i=0; i< set_get_n_ids(space->objects); i++){
      fprintf(stdout, "---> Object%d: %ld.\n", i+1, space->id);
    }
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}
