/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG
 * @version 3
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "space.h"
#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GDESC_WIDTH (9+1) /*+1 to store the '\0' character*/
#define GDESC_HEIGHT 5

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space {
  Id id;                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the space */

  /*
  Id north;                 
  Id south;                 
  Id east;                  
  Id west;                  
  */

  Set *objects;             /*!< Stores the Id of an object. NO_ID (-1) means there is no object*/
  Id character;             /*Stores the ID of the character in the space, or NO_ID if there is no character*/
  char gdesc[GDESC_HEIGHT][GDESC_WIDTH];         /*Stores the graphic description of a space (5x9 characters)*/
};

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Space* space_create(Id id) {
  Space* new_space = NULL;
  int i;

  /* Error control */
  if (id == NO_ID) return NULL;

  new_space = (Space*)calloc(1, sizeof(Space));
  if (new_space == NULL) {
    return NULL;
  }

  /* Initialization of an empty space*/
  new_space->id = id;
  new_space->name[0] = '\0';
  new_space->character = NO_ID;
  new_space->objects = set_create();
  for (i = 0; i < GDESC_HEIGHT; i++)
  {
    new_space->gdesc[i][0] = '\0'; /*initializes graphic description*/
  } 

  return new_space;
}

Status space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  set_destroy(space->objects);
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
/*
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
*/

Status space_add_object(Space* space, Id id) {
  if (space == NULL || id == NO_ID) {
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

Bool space_get_object(Space* space){
  if (space == NULL || space->objects == NULL) {
    return FALSE;
  }

  if (set_get_n_ids(space->objects) > 0) return TRUE;
  return FALSE;
}

Bool space_find_object(Space* space, Id id){
  if (space == NULL || space->objects == NULL || id == NO_ID) {
    return FALSE;
  }

  if(set_find_id(space->objects, id) == ERROR){
    return FALSE;
  }

  return TRUE;
}

Id space_get_character(Space* space){
  if (space == NULL || space->character == NO_ID) {
    return NO_ID;
  }

  return space->character;
}
Status space_set_character(Space* space, Id id) {
  if (!space) {
    return ERROR;
  }
  space->character = id;
  return OK;
}


int space_get_n_objects(Space* space){

  if(space == NULL){
    return -1;
  }

  return set_get_n_ids(space->objects);
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
  if (space_get_object(space) == TRUE) {
    for(i=0; i< set_get_n_ids(space->objects); i++){
      fprintf(stdout, "---> Object%d: %ld.\n", i+1, space->id);
    }
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}

Status space_set_gdesc(Space *space, char *gdesc) {
  int i;
  int j;
  int string_index;
  
  if (!space || !gdesc) return ERROR;

  for (i = 0; i < GDESC_HEIGHT; i++)
  {
    for (j = 0; j < GDESC_WIDTH - 1; j++)
    {
      string_index = (i * (GDESC_WIDTH - 1)) + j;
      space->gdesc[i][j] = gdesc[string_index];
    }
    space->gdesc[i][GDESC_WIDTH - 1] = '\0';
  }
  return OK;
}

char* space_get_gdesc_line(Space *space, int line) {
  if (!space || line < 0 || line >= GDESC_HEIGHT) {return NULL;}
  
  return space->gdesc[line]; 
}
