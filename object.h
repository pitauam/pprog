/**
 * @brief Define el modulo object
 *
 * @file object.h
 * @author Santiago Pita
 * @version 0
 * @date 03-01-2026
 * @copyright GNU Public License
 */
#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object;

/**
 * @brief Crea un nuevo objeto, reservando la memoria e inicializando sus parametros
 * @author Santiago Pita
 *
 * @param id identificacion del nuevo objeto
 * @return un nuevo objeto, inicializado
 */
Object* object_create(Id id);

/**
 * @brief Destuye un objeto, liberando su memoria
 * @author Santiago Pita
 *
 * @param object puntero a la esturctura del objeto que se quiere destruir
 * @return OK si todo salio bien, ERROR si algo salio mal
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