/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Samuel Manzorro, Paula de la Fuente, Santiago Pita
 * @version 4
 * @date 24-04-2026
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _Space {
  Id id;                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  char gdesc[GDESC_HEIGHT][GDESC_WIDTH]; /*!< Description of the space */
  Set *objects;             /*!< Set of objects in the space */
  Set *characters;           /*Stores the ID of the character(s) in the space, or NO_ID if there is no character*/
  Bool discovered;          /*!< Whether the space is discovered or not*/
};


Space* space_create(Id id) {
  Space* newSpace = NULL;
  int i = 0;

  if (id == NO_ID) 
  {
    return NULL;
  }

  newSpace = (Space*)calloc(1, sizeof(Space));
  if (newSpace == NULL)
  {
    return NULL;
  }
  
  newSpace->id = id;
  newSpace->name[0] = '\0';

  for (i = 0; i < GDESC_HEIGHT; i++)
  {
    strcpy(newSpace->gdesc[i], "       ");
  }

  newSpace->objects = set_create();
  if (newSpace->objects == NULL)
  {
    free(newSpace);
    return NULL;
  }

  newSpace->characters = set_create();
  if (newSpace->characters == NULL)
  {
    free(newSpace);
    return NULL;
  }

  newSpace->discovered = FALSE;

  return newSpace;
}

Status space_destroy(Space* space) {
  if (!space)
  {
    return ERROR;
  }

  set_destroy(space->objects);
  set_destroy(space->characters);

  free(space);

  return OK;
}

Id space_get_id(Space* space) {
  if (!space)
  {
    return NO_ID;
  }

  return space->id;
}

Status space_set_name(Space* space, char* name) {
  if (!space || !name)
  {
    return ERROR;
  }

  if (!strcpy(space->name, name))
  {
    return ERROR;
  }
  
  return OK;
}

const char* space_get_name(Space* space) {
  if (!space)
  {
    return NULL;
  }
  
  return space->name;
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
Bool space_find_object(Space* space, Id object_id) {
  if (!space ||object_id == NO_ID)
  {
    return FALSE;
  }

  return set_find_id(space->objects, object_id);
}

Status space_add_object(Space* space, Id object_id) {

  if (!space || object_id == NO_ID || space->objects == NULL)
  {
    return ERROR;
  }

  /* Verify that the object exists already in the space so that we don't repeat. */
  if (space_find_object(space, object_id))
  {
    return ERROR;
  }

  return set_add_value(space->objects, object_id);
}

Status space_remove_object(Space* space, Id object_id) {

  if (!space ||object_id == NO_ID)
  {
    return ERROR;
  }

  if (space_find_object(space, object_id))
  {
    return set_del_value(space->objects, object_id);
  }

  return ERROR;
}


Set *space_get_objects(Space *space) {
  if (!space)
  {
    return NULL;
  }
  
  return space->objects;
}

Status space_set_discovered(Space* space, Bool discovered) {
  if(!space)
  {
    return ERROR;
  }

  space->discovered = discovered;
  return OK;
}

Bool space_is_discovered(Space* space) {
  if(!space)
  {
    return FALSE; 
  }

  return space->discovered;
}

int space_get_n_objects(Space* space){

  if(space == NULL){
    return -1;
  }

  return set_get_n_ids(space->objects);
}


Status space_add_character(Space* space, Id id) {
  if (space == NULL || id == NO_ID || space->characters == NULL) {
    return ERROR;
  }
  if(set_find_id(space->characters, id)){
    return ERROR;
  }
  set_add_value(space->characters, id);

  return OK;
}

Status space_remove_character(Space* space, Id id) {
  if (space == NULL || space->characters == NULL || id == NO_ID) {
    return ERROR;
  }
  if(set_find_id(space->characters, id)){
    set_del_value(space->characters, id);
    return OK;
  }

  return ERROR;
}

Bool space_find_character(Space* space, Id id){
  if (space == NULL || space->characters == NULL || id == NO_ID) {
    return FALSE;
  }

  if(set_find_id(space->characters, id) == ERROR){
    return FALSE;
  }

  return TRUE;
}

int space_get_n_characters(Space* space){

  if(space == NULL){
    return -1;
  }

  return set_get_n_ids(space->characters);
}


Status space_print(Space* space) {
  Id idaux = NO_ID;
  int i = 0;

  if (!space)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  fprintf(stdout, "---> Graphic description:\n");
  for (i = 0; i < GDESC_WIDTH; i++)
  {
    fprintf(stdout, "   [%s]\n", space->gdesc[i]);
  }

  set_print(space->objects);
  set_print(space->characters);


  idaux = space_is_discovered(space);
  if (idaux == TRUE) {
    fprintf(stdout, "---> Space is discovered.\n");
  } else {
    fprintf (stdout, "---> Space is not discovered.\n");
  }

  return OK;
}


Set *space_get_characters(Space *space) {
  if (!space)
  {
    return NULL;
  }
  
  return space->characters;
}

Id space_get_character_id_at(Space *space, int i) {
  if (!space || i < 0){
    return NO_ID;
  }

  return set_get_id(space->characters, i);
}