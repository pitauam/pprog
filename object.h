/**
 * @brief Defines the module "object"
 *
 * @file object.h
 * @author Santiago Pita
 * @version 0
 * @date 03-01-2026
 * @copyright GNU Public License
 */
#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"

typedef struct _Object Object;

/**
 * @brief Creates a new object, allocating memory and initialazing all its parameters
 * @author Santiago Pita
 *
 * @param id identification number of the object
 * @return a new initialized object
 */
Object* object_create(Id id);

/**
 * @brief Destroys an object, freeing its memory
 * @author Santiago Pita
 *
 * @param object pointer to the structure of the object to destroy
 * @return OK if everything goes well, ERROR if something went wrong
 */
Status object_destroy(Object* object);

/**
 * @brief Consigue la id de un objeto
 * @author Santiago Pita
 *
 * @param object puntero a la esturctura del objeto
 * @return id del objeto
 */
Id object_get_id(Object* object);

/**
 * @brief Establece el nombre del objeto
 * @author Santiago Pita
 *
 * @param object puntero a la esturctura del objeto
 * @param name puntero al nombre del objeto
 * @return OK si todo salio bien, ERROR si algo salio mal
 */
Status object_set_name(Object* object, char* name);

/**
 * @brief Consigue el nombre de un objeto
 * @author Santiago Pita
 *
 * @param object puntero a la esturctura del objeto
 * @return una cadena con el nombre del objeto
 */
const char* object_get_name(Object* object);

/**
 * @brief Imprime la informacion de object
 * @author Santiago Pita
 *
 * Esta funcion muestra el id-nombre del objeto
 * @param object puntero a la esturctura del objeto
 * @return OK si todo salio bien, ERROR si algo salio mal
 */
Status object_print(Object* object);

#endif