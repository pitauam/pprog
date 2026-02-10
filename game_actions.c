/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

void game_actions_unknown(Game *game);

void game_actions_exit(Game *game);

void game_actions_next(Game *game);

void game_actions_back(Game *game);

void game_actions_take(Game *game);

void game_actions_drop(Game *game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);
      break;

    case EXIT:
      game_actions_exit(game);
      break;

    case NEXT:
      game_actions_next(game);
      break;

    case BACK:
      game_actions_back(game);
      break;

    case TAKE:
      game_actions_take(game);
      break;
    
    case DROP:
      game_actions_drop(game);
      break;

    default:
      break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_next(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_take(Game *game){
  Id player_location = NO_ID;
  Id object_location = NO_ID;
  Id object_id = NO_ID;

  /*gets the id of the space where the player is*/
  player_location = game_get_player_location(game);
  if(player_location == NO_ID){
    return;
  }
  /*gets the id of the space where the object is*/
  object_location = game_get_object_location(game);

  /*checks if the player is in the same space as the object*/
  if(object_location != NO_ID && object_location == player_location){
    /*gets the object id*/
    object_id = object_get_id(game->object);
    /*sets the object to the player*/
    player_set_object(game->player, object_id);
    /*deletes the object from the space*/
    space_set_object(game_get_space(game, player_location), NO_ID);

  }

  return;
}


void game_actions_drop(Game *game){
  Id space_id = NO_ID;
  Id object_id = NO_ID;

  /*gets the id of the space where the player is*/
  space_id = game_get_player_location(game);
  if(space_id == NO_ID){
    return;
  }
  /*checks if the player has an object*/
  object_id = player_get_object(game->player);
  /*if the player has no object with him*/
  if(object_id != NO_ID ){
    /*places the object on the space*/
    /*space_set_object(game_get_space(game, space_id), object_id); 
    quito esta linea porque la otra funcion
    es mas eficiente y no da error*/
    game_set_object_location(game, space_id);
    /*deletes the object from the player*/
    player_set_object(game->player, NO_ID);    
  }
  return;
}