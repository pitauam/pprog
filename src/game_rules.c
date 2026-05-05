/**
 * @brief It defines the gamerules module
 *
 * @file game_rules.c
 * @version 0
 * @date 04-05-2026
 */

#include "game_rules.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#define N_CMDS 3      /*!< Number of commands*/


/**
   Private functions
*/

/**
 * @brief the command teleports the player and its followers to a random space
 * @author Santiago Pita
 *
 * @param game pointer to game
 */
void game_rules_teleport(Game *game);

/**
 * @brief the command deals 1 damage to the player
 * @author Santiago Pita
 *
 * @param game pointer to game
 */
void game_rules_random_damage(Game* game);

/**
 * @brief the command drops one random item from the player's inventory
 * @author Santiago Pita
 *
 * @param game pointer to game
 */
void game_rules_random_drop(Game* game);

/**
 * @brief the command updates links after killing an enemy (it can open or close them)
 * @author Santiago Pita
 *
 * @param game pointer to game
 */
void game_rules_update_links(Game *game);


/*
   Game actions implementation
*/

Status game_rules_update(Game *game) {
  CommandRules random_command; /*chooses a command to execute*/
  int random_number; /*this number decides whether a command is executed or not*/

  game_rules_update_links(game);

  /*random number between 0 and N_CMD to decide the command that will be executed*/

  random_number = rand() % 6;
  if (random_number != 0){
    /*1 out of 3 chance the command will execute*/
    return OK;
  }
  random_command  = rand() % N_CMDS;
  
  /*
  random_command = 2;
  */
  switch (random_command) {
    case TELEPORT:
      game_rules_teleport(game);
      break;

    case RANDOM_DAMAGE:
      game_rules_random_damage(game);
      break;

    case RANDOM_DROP:
      game_rules_random_drop(game);
      break;

    default:
      break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/


void game_rules_teleport(Game *game){
  Id future_id = NO_ID; /*Where I go*/
  Id space_id = NO_ID;  /*Where I am*/

  Character* chr=NULL;
  Id current_char_id = NO_ID, current_char_location = NO_ID, current_char_following = NO_ID;
  int i;
  Space* actual_space = NULL, *future_space = NULL;


  space_id = game_get_player_location(game);
  actual_space = game_get_space(game, space_id);
  if (NO_ID == space_id || !actual_space) {
    return;
  }

  future_id = game_get_random_space(game);
  future_space = game_get_space(game, future_id);
  if (NO_ID == space_id || !future_space) {
    return;
  }

  if (future_id != NO_ID) {

    game_set_player_location(game, future_id);
    game_set_message(game, "You were teleported to a random space!");
    space_set_discovered(game_get_space(game, future_id), TRUE);
    
    /*The reclutas will go with this player to the future_id space -> condiciones: MISMO ESPACIO, AMIGO, QUE ME SIGA (id de recluta == id jugador) y que esté VIVO*/

    /*Finds the character to move*/
    for (i = 0 ; i < game_get_number_of_characters(game); i++)
    {
      /*Passes through all the characters of the game*/
      current_char_id = game_get_character_id_at(game, i);
      chr = game_get_character(game, current_char_id);
      current_char_location = game_get_character_location(game, current_char_id);
      current_char_following = character_get_following(chr);

      if (current_char_id == NO_ID || !chr){
        return;
      }

      if (current_char_location == space_id && character_get_friendly(chr)==TRUE && current_char_following == player_get_id(game_get_player(game)) && character_get_health(chr) > 0 && current_char_location != NO_ID) { /*CUMPLE CONDICIONES*/
        /*2. Remove character from the space_id   and   3. Add character to the future_id*/
        
        if (space_remove_character(actual_space, current_char_id) == ERROR)
        {
          return;
        }

        if (space_add_character(future_space, current_char_id) == ERROR)
        {
          return;
        }
      }
    }
  }
  return;
}

void game_rules_random_damage(Game *game){
  Player *player = NULL;
  if (!game){
    return;
  }

  /*if the player moved in the last turn*/
  if (command_get_code(game_get_last_command(game)) == 2)
  {
    player = game_get_player(game);
    player_set_health(player, (player_get_health(player)-1));
    game_set_message(game, "You fell and sprained your ankle while moving! You lost 1 health point");
  }

  return;
}

void game_rules_random_drop(Game *game){
  Player *player = NULL;
  Id object_id = NO_ID;
  Id space_id = NO_ID;
  char message[256];

  player = game_get_player(game);

  /*if the player has 1 or less objects or if the last turn the player used a command that wasnt move*/
  if (!game || player_get_n_objects(player) <= 1 || command_get_code(game_get_last_command(game)) != 2){
    return;
  }

  object_id = player_get_object_id(player, 1);
  
  /*gets the id of the space where the player is*/
  space_id = game_get_player_location(game);
  if(space_id == NO_ID){
    return;
  }
  
  /*removes the object from the player*/
  player_remove_object(player, object_id);
  /*adds the object to the space*/
  space_add_object(game_get_space(game, space_id), object_id);
  
  strcpy(message, "You dropped your ");
  strcat(message, object_get_name(game_get_object(game, object_id)));

  game_set_message(game, message);

  return;
}

void game_rules_update_links(Game *game){

  if (!game){
    return;
  }




}