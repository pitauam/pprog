/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 2
 * @date 02-03-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

/**
   Private functions
*/

/**
 * @brief the command is unknown
 * @author Profesores PPROG
 *
 * @param game pointer to game
 */
void game_actions_unknown(Game *game);

/**
 * @brief it has selected exit
 * @author Profesores PPROG
 *
 * @param game pointer to game
 */
void game_actions_exit(Game *game);

/**
 * @brief moves to the next space at the south
 * @author Profesores PPROG
 *
 * @param game pointer to game
 */
void game_actions_next(Game *game);

/**
 * @brief goes back to the north
 * @author Profesores PPROG
 *
 * @param game pointer to game
 */
void game_actions_back(Game *game);

/**
 * @brief moves to the next space at the west
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 */
void game_actions_left(Game *game);

/**
 * @brief moves to the next space at the east
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 */
void game_actions_right(Game *game);

/**
 * @brief the player takes the object of the space
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 */
void game_actions_take(Game *game);

/**
 * @brief the player drops the object to the space
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 */
void game_actions_drop(Game *game);

/**
 * @brief lets the player attack
 * @author Santiago Pita
 *
 * @param game pointer to game
 */
void game_actions_attack(Game *game);

/**
 * @brief lets the player chat
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 */
void game_actions_chat(Game *game);
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

    case LEFT:
      game_actions_left(game);
      break;

    case RIGHT:
      game_actions_right(game);
      break;

    case ATTACK:
      game_actions_attack(game);
      break;

    case CHAT:
      game_actions_chat(game);
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
void game_actions_left(Game *game){
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_west(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

}

void game_actions_right(Game *game){
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_east(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }
}

void game_actions_take(Game *game){
  Id player_location = NO_ID;
  Id object_location = NO_ID;
  Id object_id = NO_ID;
  Object *object;
  Player *player;

  /*object = game_get_object(game, game_get_object_id_at(game, ))

  object_id = object_get_id(object);*/


  /*gets the id of the space where the player is*/
  player_location = game_get_player_location(game);
  if(player_location == NO_ID){
    return;
  }
  /*gets the id of the space where the object is*/
  object_location = game_get_object_location(game, object_id);

  /*checks if the player is in the same space as the object*/
  if(object_location != NO_ID && object_location == player_location){
    /*gets the object id*/
    object = game_get_object(game, object_id);
    /*sets the object to the player*/
    player = game_get_player(game);
    player_set_object(player, object_id);
    /*deletes the object from the space*/
    space_remove_object(game_get_space(game, player_location), NO_ID);

  }

  return;
}

void game_actions_drop(Game *game){
  Id space_id = NO_ID;
  Id object_id = NO_ID;
  Player* player;

  /*gets the id of the space where the player is*/
  space_id = game_get_player_location(game);
  if(space_id == NO_ID){
    return;
  }
  /*checks if the player has an object*/
  player = game_get_player(game);

  object_id = player_get_object(player);
  /*if the player has no object with him*/
  if(object_id != NO_ID ){
    /*places the object on the space*/
    game_set_object_location(game, space_id, object_id);
    /*deletes the object from the player*/
    player_set_object(player, NO_ID);    
  }
  return;
}

void game_actions_attack(Game *game){
  Id player_location; 
  Id character_at_player_location;
  Character *character = NULL; 
  Player *player = NULL;

  int character_health;
  int player_health;
  int random_number;

   if (!game) {return;}


  /*gets the id of the space where the player is located*/
  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {return;}
  /*gets the id of the character located at the same space as the player*/
  character_at_player_location = game_get_character_id(game, player_location);
  if (character_at_player_location == NO_ID) {return;}

  character = game_get_character(game, character_at_player_location);
  if (character == NULL) {return;}

  /*if character is friendly, return*/
  if (character_get_friendly(character) == TRUE) {return;}

  character_print(character);

  character_health = character_get_health(character);
  player_health = player_get_health(game_get_player(game));

  /*if character or player is dead, return*/
  if (character_health <= 0 || player_health <= 0) {return;}

  /*generates a random number between 0 and 9*/
  random_number = (rand() % 10);

  player = game_get_player(game);

  /*if the player loses*/
  if (random_number < 5)
  {
    player_set_health(player, player_health -1);
  }
  else 
  {
    character_set_health(character, character_health - 1);
  }

  if (character_get_health(character) <= 0)
  {
    /*character dies*/
    space_set_character(game_get_space(game, player_location), NO_ID);  
  }
  if (player_get_health(game_get_player(game)) <= 0)
  {
    /*player dies*/
    game_set_finished(game, TRUE); /*if player dies, game ends*/
  }

  return;
}


void game_actions_chat(Game *game){

  Id player_location; 
  Id character_at_player_location;
  Character *character = NULL; 

  if (!game) {return;}

  /*gets the id of the space where the player is located*/
  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {return;}
  /*gets the id of the character located at the same space as the player*/
  character_at_player_location = game_get_character_id(game, player_location);
  if (character_at_player_location == NO_ID) {return;}

  character = game_get_character(game, character_at_player_location);
  if (character == NULL) {return;}

  /*if character is not friendly, return*/
  if (character_get_friendly(character) == FALSE) {return;}

  character_print(character);
  return;
}
