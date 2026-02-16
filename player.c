/**
 * @brief Implements the player module
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
 * This structure conatins all the information of a player
 */
struct _Player 
{
    Id id; /*!< Id number of the player, must be unique */
    char name [WORD_SIZE +1]; /*!< Player's name */
    Id location; /*!< Id of the location */
    Id object; /*!< Id of the object */
};

/** player_create allocates memory and initializes all variables*/

Player* player_create(Id id) {
  Player* new_player = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  new_player = (Player*)calloc(1, sizeof(Player));
  if (new_player == NULL) {
    return NULL;
  }

  /* Initialization of an empty player*/
  new_player->id = id;
  new_player->name[0] = '\0';
  new_player->location = NO_ID;
  new_player->object = NO_ID;


  return new_player;
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

  if (!player) {
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

/**player_print prints the information of the player*/
Status player_print(Player* player) {
  Id idaux = NO_ID;

  /* Error Control */
  if (!player) {
    return ERROR;
  }

  /* 1. Prints the player's id and name */
  fprintf(stdout, "--> player (Id: %ld; Name: %s)\n", player->id, player->name);

  /* 2. Prints the id and the location*/
  idaux = player_get_location(player);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> Location link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No location link.\n");
  }
  /* 3. Prints if the player has an object */
  if (player_get_object(player)) {
    fprintf(stdout, "---> Object in the player.\n");
  } else {
    fprintf(stdout, "---> No object in the player.\n");
  }

  return OK;
}