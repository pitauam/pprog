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


Status player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }
  
  free(player);
  return OK;
}

Id player_get_id(Player* player) {

  if (!player) {
    return NO_ID;
  }
  return player->id;
}


Status player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }
  return OK;
}


const char* player_get_name(Player* player) {

  if (!player) {
    return NULL;
  }
  return player->name;
}


Status player_set_location(Player* player, Id id) {

  if (!player || id == NO_ID) {
    return ERROR;
  }
  player->location = id;
  return OK;
}


Id player_get_location(Player* player) {

  if (!player) {
    return NO_ID;
  }
  return player->location;
}


Status player_set_object(Player* player, Id id) {

  if (!player || id == NO_ID) {
    return ERROR;
  }
  player->object = id;
  return OK;
}


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