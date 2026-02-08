/**
 * @brief Implementa el modulo object
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
 * Esta estructura guarda toda la informacin de un objeto
 */

struct _Object {
  Id id;                    /*!< Id del objeto, tiene que ser unico */
  char name[WORD_SIZE + 1]; /*!< nombre del objeto */
};

/** object_create reserva la memoria e inicializa todas las variables*/

Object* object_create(Id id) {
  Object* newObject = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  newObject = (Object*)calloc(1, sizeof(Object));
  if (newObject == NULL) {
    return NULL;
  }

  /* Inicializacion de un objeto vacio*/
  newObject->id = id;
  newObject->name[0] = '\0';

  return newObject;
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

  /* 1. Imprime el id y el nombre del objeto */
  fprintf(stdout, "--> object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}

