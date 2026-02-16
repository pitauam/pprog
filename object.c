/**
 * @brief Implements the object module
 *
 * @file object.c
 * @author Santiago Pita
 * @version 0
 * @date 03-02-2026
 * @copyright GNU Public License
 */

#include "object.h"

#include <stdio.h>
#include <stdlib.h> /*pueden hacer falta*/
#include <string.h>

/**
 * @brief Object
 *
 * This structure contains all the information of an object
 */

struct _Object {
  Id id;                    /*!< Object's id, must be unique */
  char name[WORD_SIZE + 1]; /*!< Object's name */
};

/** object_create allocates memory and initializes all variables*/

Object* object_create(Id id) {
  Object* new_object = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  new_object = (Object*)calloc(1, sizeof(Object));
  if (new_object == NULL) {
    return NULL;
  }

  /* Initialization of an empty object*/
  new_object->id = id;
  new_object->name[0] = '\0';

  return new_object;
}

Status object_destroy(Object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  return OK;
}

Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

Status object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

Status object_print(Object* object) {
  /*Id idaux = NO_ID;*/

  /* Error Control */
  if (!object) {
    return ERROR;
  }

  /* 1. Prints object's id and name */
  fprintf(stdout, "--> object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}