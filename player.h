/**
 * @brief Define el modulo player
 *
 * @file player.h
 * @author Mario Rodriguez
 * @version 0
 * @date 03-01-2026
 * @copyright GNU Public License
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

typedef struct _Player Player;

/**
 * @brief Crea un nuevo jugador, reservando la memoria e inicializando sus parametros
 * @author Mario Rodriguez
 *
 * @param id identificacion del nuevo jugador
 * @return un nuevo jugador, inicializado
 */
Player* player_create(Id id);

/**
 * @brief Destuye un jugador, liberando su memoria
 * @author Mario Rodriguez
 *
 * @param player puntero a la esturctura del jugador que se quiere destruir
 * @return OK si todo salio bien, ERROR si algo salio mal
 */
Status player_destroy(Player* player);

/**
 * @brief Consigue la id de un jugador
 * @author Mario Rodriguez
 *
 * @param player puntero a la esturctura del jugador
 * @return id del jugador
 */
Id player_get_id(Player* player);

/**
 * @brief Establece el nombre del jugador
 * @author Mario Rodriguez
 *
 * @param player puntero a la esturctura del jugador
 * @param name puntero al nombre del jugador
 * @return OK si todo salio bien, ERROR si algo salio mal
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief Consigue el nombre de un jugador
 * @author Mario Rodriguez
 *
 * @param player puntero a la esturctura del jugador
 * @return una cadena con el nombre del jugador
 */
const char* player_get_name(Player* player);

/**
 * @brief Establece la localizacion de un jugador
 * @author Mario Rodriguez
 *
 * @param player puntero a la esturctura del jugador
 * @param id id de la localizacion
 * @return OK si todo salio bien, ERROR si algo salio mal
 */
Status player_set_location(Player* player, Id id);

/**
 * @brief Consigue la localizacion de un jugador
 * @author Mario Rodriguez
 *
 * @param player puntero a la esturctura del jugador
 * @return la id del espacio en el que se encuentra
 */
Id player_get_location(Player* player);

/**
 * @brief Establece el objeto de un jugador
 * @author Mario Rodriguez
 *
 * @param player puntero a la esturctura del jugador
 * @param id id del objeto
 * @return OK si todo salio bien, ERROR si algo salio mal
 */
Status player_set_object(Player* player, Id id);

/**
 * @brief Establece la localizacion de un jugador
 * @author Mario Rodriguez
 *
 * @param player puntero a la esturctura del jugador
 * @return la id del objeto
 */
Id player_get_object(Player* player);

/**
 * @brief Imprime la informacion de player
 * @author Mario Rodriguez
 *
 * Esta funcion muestra el id-nombre-localizacion- y objeto del jugador si tiene uno
 * @param player puntero a la esturctura del jugador
 * @return OK si todo salio bien, ERROR si algo salio mal
 */
Status player_print(Player* player);
#endif
