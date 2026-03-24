/**
 * @brief Implements the player module
 *
 * @file player.c
 * @author Mario Rodriguez
 * @version 1
 * @date 02-03-2026
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "inventory.h"

/**
 * @brief Player
 *
 * This structure conatins all the information of a player
 */
struct _Player {
    Id id; /*!< Id number of the player, must be unique */
    char name [WORD_SIZE +1]; /*!< Player's name */
    Id location; /*!< Id of the location */
    int health; /*!< Health of the player */
    char gdesc[7]; /*!< Gives a graphic description */
    Inventory *backpack; /*!< Inventory of the player */
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
  new_player->backpack = inventory_create();
  new_player->health = 5;
  new_player->gdesc[0] = '\0';

  return new_player;
}

Status player_destroy(Player* player) {
  
  if (!player) {
    return ERROR;
  }
  if(inventory_destroy(player->backpack)){
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

Status player_add_object(Player* player, Id id) {

  if (!player) {
    return ERROR;
  }
   if(inventory_add_object(player->backpack, id) == ERROR){
    return ERROR;
   }

  return OK;
}

Status player_remove_object(Player* player, Id id){

  if(!player|| !player->backpack || id == NO_ID){
    return ERROR;
  }

  if(inventory_remove_object(player->backpack, id) == ERROR){
    return ERROR;
   }

   return OK;
}

int player_get_n_objects(Player* player){
  if(!player || !player->backpack){
    return -1;
  }

  return inventory_get_n_objects(player->backpack);
}

Id player_get_object_id(Player* player, int pos){

    if (!player || !player->backpack|| pos < 0) {
      return NO_ID;
    }

    return inventory_get_object_id(player->backpack, pos);
}

Bool player_inventory_empty(Player* player) {

  if (!player || !player->backpack) {
    return TRUE;
  }

  if(inventory_get_n_objects(player->backpack) > 0){
    return FALSE;
  }
  
  return TRUE;
}

int player_inventory_size(Player *player){
   if (!player || !player->backpack){
    return -1;
   }

   return inventory_get_n_objects(player->backpack);
}
Status player_find_object(Player* player, Id id){

   if(!player || !player->backpack || id == NO_ID){
    return ERROR;
   }

   if(inventory_find_object(player->backpack, id) == TRUE){
    return OK;
   }

   return ERROR;
}


Status player_set_health(Player *player, int health){
    if(player == NULL || health < 0 || health > 100){
        return ERROR;
    }

    player->health = health;

    return OK;
}

int player_get_health(Player *player){
    if(player == NULL){
        return -1;
    }

    return player->health;
}

Status player_set_description(Player *player, char *descrp){
    if(player == NULL || descrp == NULL || strlen(descrp) > 6){
        return ERROR;
    }

    strcpy(player->gdesc, descrp);

    return OK;
}

const char *player_get_description(Player *player){
    if(player == NULL){
        return NULL;
    }

    return player->gdesc;
}
/**player_print prints the information of the player*/
Status player_print(Player* player) {
  Id idaux = NO_ID;

  /* Error Control */
  if (!player) {
    return ERROR;
  }

  /* 1. Prints the player's id name and health */
  fprintf(stdout, "--> player (Id: %ld; Name: %s; Health: %d)\n", player->id, player->name, player->health);

  /* 2. Prints the id and the location*/
  idaux = player_get_location(player);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> Location link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No location link.\n");
  }
  /* 3. Prints the object ID */
  idaux = player_get_object(player);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> Player carries object: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No object in the player.\n");
  }
  /* 3. Prints if the player has an object */
  if (player_get_description(player)) {
    fprintf(stdout, "---> Description: %s.\n", player->gdesc);
  } else {
    fprintf(stdout, "---> No description in the player.\n");
  }
  return OK;
}
