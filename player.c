/**
 * @brief Implementa el modulo player
 *
 * @file player.c
 * @author Mario Rodriguez
 * @version 0
 * @date 03-02-2026
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"

/**
 * @brief Player
 *
 * Esta estructura contiene toda la informacion de player
 */
struct _Player 
{
    Id id; /*!< numero de id del jugador, tiene que ser unico */
    char name [WORD_SIZE +1]; /*!< nombre del jugador */
    Id location; /*!< Id de la localizacion */
    Bool object; /*!< tiene objeto o no*/
};

/** player_create reserva la memoria e inicializa las variables*/

Player* player_create(Id id) {
  Player* newPlayer = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  newPlayer = (Player*)calloc(1, sizeof(Player));
  if (newPlayer == NULL) {
    return NULL;
  }

  /* Icializacion de un jugador nuevo*/
  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->location = NO_ID;
  newPlayer->object = NO_ID;


  return newPlayer;
}

/** player_destroy elimina la memoria destruyendo al jugador*/
Status player_destroy(Player* player) {
  /*error control*/
  if (!player) {
    return ERROR;
  }
  /*libera la memoria*/
  free(player);
  return OK;
}
/** player_get_id consigue la id del jugador*/
Id player_get_id(Player* player) {
  /*error control*/
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

/** player_set_id establece la id del jugador*/
Status player_set_name(Player* player, char* name) {
  /*error control*/
  if (!player || !name) {
    return ERROR;
  }
  /*copia el nombre*/
  if (!strcpy(player->name, name)) {
    return ERROR;
  }
  return OK;
}

/** player_get_name consigue el nombre del jugador*/
const char* player_get_name(Player* player) {
  /*error control*/
  if (!player) {
    return NULL;
  }
  return player->name;
}

/** player_set_location establece la localizacion del jugador*/
Status player_set_location(Player* player, Id id) {
  /*error control*/
  if (!player || id == NO_ID) {
    return ERROR;
  }
  player->location = id;
  return OK;
}

/** player_get_location consigue la localizacion del jugador*/
Id player_get_location(Player* player) {
  /*error control*/
  if (!player) {
    return NO_ID;
  }
  return player->location;
}

/** player_set_object establece el objeto del jugador*/
Status player_set_object(Player* player, Id id) {
  /*error control*/
  if (!player || id == NO_ID) {
    return ERROR;
  }
  player->object = id;
  return OK;
}

/** player_get_object consigue el id del objeto del jugador*/
Id player_get_object(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->object;
}

/**player_print imprime la informacion de player*/
Status player_print(Player* player) {
  Id idaux = NO_ID;

  /* Error Control */
  if (!player) {
    return ERROR;
  }

  /* 1. Imprime el nombre y el id del jugador */
  fprintf(stdout, "--> player (Id: %ld; Name: %s)\n", player->id, player->name);

  /* 2. imprime el id de la localizacion*/
  idaux = player_get_location(player);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> Location link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No location link.\n");
  }
  /* 3. Imprime si el jugador tiene un objeto */
  if (player_get_object(player)) {
    fprintf(stdout, "---> Object in the player.\n");
  } else {
    fprintf(stdout, "---> No object in the player.\n");
  }

  return OK;
}